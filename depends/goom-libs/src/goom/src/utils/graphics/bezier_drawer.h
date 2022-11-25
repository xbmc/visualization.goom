#pragma once

#include "draw/goom_draw.h"
#include "goom_graphic.h"
#include "point2d.h"
#include "small_image_bitmaps.h"

#include <bezier/bezier.h>
#include <cstdint>
#include <functional>

namespace GOOM::UTILS::GRAPHICS
{

class BezierDrawer
{
public:
  explicit BezierDrawer(DRAW::IGoomDraw& goomDraw, const SmallImageBitmaps& smallBitmaps) noexcept
    : m_goomDraw{goomDraw}, m_smallBitmaps{smallBitmaps}
  {
  }

  [[nodiscard]] auto GetScreenWidth() const -> uint32_t
  {
    return m_goomDraw.GetScreenWidth();
  }
  [[nodiscard]] auto GetScreenHeight() const -> uint32_t
  {
    return m_goomDraw.GetScreenHeight();
  }

  using GetColorFunc = std::function<Pixel(float t)>;
  void SetLineColorFunc(const GetColorFunc& lineColorFunc) { m_lineColorFunc = lineColorFunc; };
  void SetDotColorFunc(const GetColorFunc& dotColorFunc) { m_dotColorFunc = dotColorFunc; }

  void Draw(const Bezier::Bezier<3>& bezier, float colorT0, float colorT1);

  [[nodiscard]] auto GetLineThickness() const -> uint8_t { return m_lineThickness; }
  void SetLineThickness(const uint8_t mLineThickness) { m_lineThickness = mLineThickness; }

  [[nodiscard]] auto GetNumBezierSteps() const -> size_t { return m_numBezierSteps; }
  void SetNumBezierSteps(const size_t mNumBezierSteps) { m_numBezierSteps = mNumBezierSteps; }

  [[nodiscard]] auto GetDotEveryNumBezierSteps() const -> size_t
  {
    return m_dotEveryNumBezierSteps;
  }
  void SetDotEveryNumBezierSteps(const size_t mDotEveryNumBezierSteps)
  {
    m_dotEveryNumBezierSteps = mDotEveryNumBezierSteps;
  }

private:
  DRAW::IGoomDraw& m_goomDraw;
  const SmallImageBitmaps& m_smallBitmaps;
  GetColorFunc m_lineColorFunc{};
  GetColorFunc m_dotColorFunc{};

  static constexpr uint8_t DEFAULT_LINE_THICKNESS            = 1;
  uint8_t m_lineThickness                                    = DEFAULT_LINE_THICKNESS;
  static constexpr size_t DEFAULT_NUM_BEZIER_STEPS           = 50;
  size_t m_numBezierSteps                                    = DEFAULT_NUM_BEZIER_STEPS;
  static constexpr size_t DEFAULT_DOT_EVERY_NUM_BEZIER_STEPS = 10;
  size_t m_dotEveryNumBezierSteps                            = DEFAULT_DOT_EVERY_NUM_BEZIER_STEPS;

  static constexpr size_t MIN_DOT_DIAMETER       = 5;
  static constexpr size_t MAX_DOT_DIAMETER       = 21;
  static constexpr uint32_t DEFAULT_DOT_DIAMETER = 19;
  uint32_t m_dotDiameter                         = DEFAULT_DOT_DIAMETER;
  void DrawDot(Point2dInt centre, uint32_t diameter, const Pixel& color);
  SmallImageBitmaps::ImageNames m_currentBitmapName{SmallImageBitmaps::ImageNames::SPHERE};
  [[nodiscard]] auto GetImageBitmap(size_t size) const -> const ImageBitmap&;
};

} // namespace GOOM::UTILS::GRAPHICS
