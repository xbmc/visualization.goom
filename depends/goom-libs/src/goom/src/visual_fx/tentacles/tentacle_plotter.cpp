#include "tentacle_plotter.h"

//#undef NO_LOGGING

#include "draw/goom_draw.h"
#include "logging.h"
#include "point2d.h"
#include "utils/graphics/line_clipper.h"
#include "utils/math/goom_rand_base.h"
#include "utils/math/misc.h"
#include "utils/t_values.h"

namespace GOOM::VISUAL_FX::TENTACLES
{

using DRAW::IGoomDraw;
using DRAW::MultiplePixels;
using UTILS::Logging; // NOLINT(misc-unused-using-decls)
using UTILS::TValue;
using UTILS::GRAPHICS::LineClipper;
using UTILS::MATH::IGoomRand;

static constexpr auto BRIGHTNESS                   = 3.0F;
static constexpr auto NORMAL_BRIGHTNESS_CUT        = 1.0F;
static constexpr auto AT_START_HEAD_BRIGHTNESS_CUT = 0.2F;

TentaclePlotter::TentaclePlotter(IGoomDraw& draw, const IGoomRand& goomRand) noexcept
  : m_draw{draw}, m_goomRand{goomRand}
{
}

auto TentaclePlotter::Plot3D(const Tentacle3D& tentacle) noexcept -> void
{
  const auto brightness = GetBrightness(tentacle);
  const auto points3D   = tentacle.GetTentacleVertices(m_cameraPosition);

  PlotPoints(tentacle, brightness, points3D);
}

inline auto TentaclePlotter::PlotPoints(const Tentacle3D& tentacle,
                                        const float brightness,
                                        const std::vector<V3dFlt>& points3D) -> void
{
  const auto lines2D  = GetPerspectiveProjection(points3D);
  const auto numLines = static_cast<uint32_t>(lines2D.size());
  auto t              = TValue{TValue::StepType::SINGLE_CYCLE, numLines};

  for (const auto& line : lines2D)
  {
    DrawNode(tentacle, t(), line, brightness);
    t.Increment();
  }
}

inline auto TentaclePlotter::DrawNode(const Tentacle3D& tentacle,
                                      const float t,
                                      const Line2DInt& line,
                                      const float brightness) -> void
{
  const auto colors = tentacle.GetMixedColors(t, m_dominantColors, brightness);

  m_draw.Line(line.point1, line.point2, colors, m_lineThickness);
}

inline auto TentaclePlotter::GetBrightness(const Tentacle3D& tentacle) -> float
{
  return BRIGHTNESS * GetBrightnessCut(tentacle);
}

inline auto TentaclePlotter::GetBrightnessCut(const Tentacle3D& tentacle) -> float
{
  return NORMAL_BRIGHTNESS_CUT;
  if (std::abs(tentacle.GetStartPos().x) < Tentacle3D::START_SMALL_X)
  {
    return AT_START_HEAD_BRIGHTNESS_CUT;
  }
  return NORMAL_BRIGHTNESS_CUT;
}

auto TentaclePlotter::GetPerspectiveProjection(const std::vector<V3dFlt>& points3D) const
    -> std::vector<Line2DInt>
{
  auto lines2D = std::vector<Line2DInt>{};

  const auto numPoints = points3D.size();
  auto pointFlt1       = Point2dFlt{};
  bool havePoint1      = false;

  for (auto i = 0U; i < numPoints; ++i)
  {
    if (static constexpr auto MIN_Z = 2.0F; points3D[i].z <= MIN_Z)
    {
      havePoint1 = false;
      continue;
    }

    const auto pointFlt = GetPerspectivePoint(points3D[i]);

    if (not havePoint1)
    {
      pointFlt1  = pointFlt;
      havePoint1 = true;
      continue;
    }

    const auto clippedLine = m_lineClipper.GetClippedLine({pointFlt1, pointFlt});
    if (clippedLine.clipResult == LineClipper::ClipResult::REJECTED)
    {
      pointFlt1  = pointFlt;
      havePoint1 = true;
      continue;
    }

    const auto line2D = Line2DInt{clippedLine.line.point1.ToInt(), clippedLine.line.point2.ToInt()};
    if (line2D.point1 == line2D.point2)
    {
      pointFlt1  = clippedLine.line.point2;
      havePoint1 = true;
      continue;
    }

    lines2D.emplace_back(line2D);

    pointFlt1  = clippedLine.line.point2;
    havePoint1 = true;
  }

  return lines2D;
}

inline auto TentaclePlotter::GetPerspectivePoint(const V3dFlt& point3D) const -> Point2dFlt
{
  const auto perspectiveFactor = PROJECTION_DISTANCE / point3D.z;
  const auto xProj             = perspectiveFactor * point3D.x;
  const auto yProj             = perspectiveFactor * point3D.y;

  return Point2dFlt{xProj, -yProj} + m_screenMidPoint;
}

} // namespace GOOM::VISUAL_FX::TENTACLES
