#include "tentacle3d.h"

//#undef NO_LOGGING

#include "color/color_maps.h"
#include "color/color_utils.h"
#include "draw/goom_draw.h"
#include "logging.h"
#include "tentacle2d.h"
#include "utils/math/misc.h"

#include <memory>
#include <tuple>
#include <vector>

namespace GOOM::VISUAL_FX::TENTACLES
{

using COLOR::GetBrighterColor;
using COLOR::IColorMap;
using COLOR::RandomColorMaps;
using DRAW::GetLowColor;
using DRAW::GetMainColor;
using DRAW::MultiplePixels;
using UTILS::Logging; // NOLINT(misc-unused-using-decls)
using UTILS::MATH::IGoomRand;
using UTILS::MATH::Sq;

static constexpr auto PROB_LOW_MIX_SAME      = 0.5F;
static constexpr auto MAIN_BRIGHTNESS_FACTOR = 0.5F;
static constexpr auto LOW_BRIGHTNESS_FACTOR  = 1.0F;

Tentacle3D::Tentacle3D(std::unique_ptr<Tentacle2D> tentacle, const IGoomRand& goomRand) noexcept
  : m_goomRand{goomRand}, m_tentacle{std::move(tentacle)}
{
}

Tentacle3D::~Tentacle3D() noexcept = default;

auto Tentacle3D::SetWeightedColorMaps(
    const IVisualFx::WeightedColorMaps& weightedColorMaps) noexcept -> void
{
  m_mainColorMaps = weightedColorMaps.mainColorMaps;
  m_lowColorMaps  = weightedColorMaps.lowColorMaps;

  m_colorMapsManager.UpdateColorMapInfo(m_mainColorMapID,
                                        {m_mainColorMaps, RandomColorMaps::ALL_COLOR_MAP_TYPES});

  m_colorMapsManager.UpdateColorMapInfo(m_lowColorMapID,
                                        {m_lowColorMaps, RandomColorMaps::ALL_COLOR_MAP_TYPES});

  ChangeColorMaps();
}

auto Tentacle3D::ChangeColorMaps() -> void
{
  m_colorMapsManager.ChangeColorMapNow(m_mainColorMapID);
  m_colorMapsManager.ChangeColorMapNow(m_lowColorMapID);

  m_mainColorSegmentMixT =
      m_goomRand.GetRandInRange(MIN_COLOR_SEGMENT_MIX_T, MAX_COLOR_SEGMENT_MIX_T);

  m_lowColorSegmentMixT =
      m_goomRand.ProbabilityOf(PROB_LOW_MIX_SAME)
          ? m_mainColorSegmentMixT
          : m_goomRand.GetRandInRange(MIN_COLOR_SEGMENT_MIX_T, MAX_COLOR_SEGMENT_MIX_T);
}

auto Tentacle3D::GetMixedColors(const float t,
                                const MultiplePixels& dominantColors,
                                const float brightness) const -> MultiplePixels
{
  const auto mixedColors = GetMixedColors(t, dominantColors);

  return {
      m_colorAdjust.GetAdjustment(MAIN_BRIGHTNESS_FACTOR * brightness, GetMainColor(mixedColors)),
      m_colorAdjust.GetAdjustment(LOW_BRIGHTNESS_FACTOR * brightness, GetLowColor(mixedColors))};
}

auto Tentacle3D::GetMixedColors(const float t, const MultiplePixels& dominantColors) const
    -> MultiplePixels
{
  const auto mainSegmentColor = m_colorMapsManager.GetColorMap(m_mainColorMapID).GetColor(t);
  const auto lowSegmentColor  = m_colorMapsManager.GetColorMap(m_lowColorMapID).GetColor(t);

  auto mixedColors = MultiplePixels{
      IColorMap::GetColorMix(
          GetMainColor(dominantColors), mainSegmentColor, m_mainColorSegmentMixT),
      IColorMap::GetColorMix(GetLowColor(dominantColors), lowSegmentColor, m_lowColorSegmentMixT)};

  if (static constexpr auto T_CUT_OFF = 0.7F;
      (std::abs(GetStartPos().x) <= START_SMALL_X) or (t > T_CUT_OFF))
  {
    const auto brightnessCut = 0.8F * Sq(Sq(t));
    return {GetBrighterColor(brightnessCut, GetMainColor(mixedColors)),
            GetBrighterColor(brightnessCut, GetLowColor(mixedColors))};
  }

  return mixedColors;
}

auto Tentacle3D::SetEndPosOffset(const V3dFlt& val) noexcept -> void
{
  m_previousEndPosOffset = GetCurrentEndPostOffset();
  m_endPosOffset         = val;
  m_endPosOffsetT.Reset();
}

inline auto Tentacle3D::GetCurrentEndPostOffset() const noexcept -> V3dFlt
{
  return lerp(m_previousEndPosOffset, m_endPosOffset, m_endPosOffsetT());
}

auto Tentacle3D::GetTentacleVertices(const V3dFlt& startPosOffset) const -> std::vector<V3dFlt>
{
  const auto& [xVec2D, yVec2D] = m_tentacle->GetDampedXAndYVectors();

  const auto numPoints = xVec2D.size();
  auto vec3d           = std::vector<V3dFlt>(numPoints);

  const auto endPosOffset = GetCurrentEndPostOffset();

  const auto x0 = m_startPos.x + startPosOffset.x;
  const auto xn = m_endPos.x + endPosOffset.x;
  const auto y0 = m_startPos.y + startPosOffset.y + static_cast<float>(yVec2D[0]);
  const auto yn = m_endPos.y + endPosOffset.y + static_cast<float>(yVec2D[0]);
  const auto z0 = Z_START_POS + startPosOffset.z + static_cast<float>(xVec2D[0]);

  const auto xStep = (xn - x0) / static_cast<float>(numPoints - 1);
  const auto yStep = (yn - y0) / static_cast<float>(numPoints - 1);

  auto x = x0;
  auto y = y0;
  for (auto i = 0U; i < numPoints; ++i)
  {
    vec3d[i].x = x;
    vec3d[i].y = y + static_cast<float>(yVec2D[i]);
    vec3d[i].z = z0 + static_cast<float>(xVec2D[i]);

    x += xStep;
    y += yStep;
  }

  return vec3d;
}

} // namespace GOOM::VISUAL_FX::TENTACLES
