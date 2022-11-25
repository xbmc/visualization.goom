#include "bezier_drawer.h"

#include "color/color_utils.h"
#include "image_bitmaps.h"
#include "point2d.h"

namespace GOOM::UTILS::GRAPHICS
{

using COLOR::GetBrighterColor;

inline auto BezierDrawer::GetImageBitmap(const size_t size) const -> const ImageBitmap&
{
  return m_smallBitmaps.GetImageBitmap(m_currentBitmapName,
                                       std::clamp(size, MIN_DOT_DIAMETER, MAX_DOT_DIAMETER));
}

void BezierDrawer::Draw(const Bezier::Bezier<3>& bezier, const float colorT0, const float colorT1)
{
  const auto colorTStep = (colorT1 - colorT0) / static_cast<float>(m_numBezierSteps - 1);

  const auto tStep = 1.0F / static_cast<float>(m_numBezierSteps - 1);
  auto colorT      = colorT0 + colorTStep;
  auto t           = tStep;
  auto point0      = Point2dInt{static_cast<int32_t>(bezier.valueAt(0.0F, 0)),
                           static_cast<int32_t>(bezier.valueAt(0.0F, 1))};

  for (auto i = 1U; i < m_numBezierSteps; ++i)
  {
    const auto point1 = Point2dInt{static_cast<int32_t>(bezier.valueAt(t, 0)),
                                   static_cast<int32_t>(bezier.valueAt(t, 1))};

    const auto lineColor = GetBrighterColor(10.F, m_lineColorFunc(colorT));
    m_goomDraw.Line(point0, point1, lineColor, m_lineThickness);

    if (0 == (i % m_dotEveryNumBezierSteps))
    {
      const auto dotColor = GetBrighterColor(10.F, m_dotColorFunc(colorT));
      DrawDot(point1, m_dotDiameter, dotColor);
    }

    point0 = point1;
    t += tStep;
    colorT += colorTStep;
  }
}

void BezierDrawer::DrawDot(const Point2dInt centre, const uint32_t diameter, const Pixel& color)
{
  const auto getColor =
      [&color]([[maybe_unused]] const size_t x, [[maybe_unused]] const size_t y, const Pixel& bgnd)
  {
    if (0 == bgnd.A())
    {
      return BLACK_PIXEL;
    }
    return color;
  };

  m_goomDraw.Bitmap(centre, GetImageBitmap(diameter), getColor);
}

} // namespace GOOM::UTILS::GRAPHICS
