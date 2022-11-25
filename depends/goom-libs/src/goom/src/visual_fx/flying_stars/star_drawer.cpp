#include "star_drawer.h"

#include "color/color_utils.h"
#include "draw/goom_draw.h"
#include "goom_config.h"
#include "goom_graphic.h"
#include "utils/graphics/image_bitmaps.h"
#include "utils/graphics/small_image_bitmaps.h"
#include "utils/math/goom_rand_base.h"
#include "utils/t_values.h"

namespace GOOM::VISUAL_FX::FLYING_STARS
{

using COLOR::GetColorMultiply;
using DRAW::IGoomDraw;
using DRAW::MultiplePixels;
using UTILS::TValue;
using UTILS::GRAPHICS::ImageBitmap;
using UTILS::GRAPHICS::SmallImageBitmaps;
using UTILS::MATH::IGoomRand;

StarDrawer::StarDrawer(IGoomDraw& draw,
                       const IGoomRand& goomRand,
                       const SmallImageBitmaps& smallBitmaps,
                       const GetMixedColorsFunc& getMixedColorsFunc) noexcept
  : m_draw{draw},
    m_goomRand{goomRand},
    m_smallBitmaps{smallBitmaps},
    m_getMixedColorsFunc{getMixedColorsFunc},
    m_drawFuncs{{{
        {DrawElementTypes::CIRCLES,
         [this](const Point2dInt point1,
                const Point2dInt point2,
                const uint32_t size,
                const DRAW::MultiplePixels& colors)
         { DrawParticleCircle(point1, point2, size, colors); }},
        {DrawElementTypes::LINES,
         [this](const Point2dInt point1,
                const Point2dInt point2,
                const uint32_t size,
                const DRAW::MultiplePixels& colors)
         { DrawParticleLine(point1, point2, size, colors); }},
        {DrawElementTypes::DOTS,
         [this](const Point2dInt point1,
                const Point2dInt point2,
                const uint32_t size,
                const DRAW::MultiplePixels& colors)
         { DrawParticleDot(point1, point2, size, colors); }},
        {DrawElementTypes::CIRCLES_AND_LINES,
         [](const Point2dInt, const Point2dInt, const uint32_t, const DRAW::MultiplePixels&)
         { FailFast(); }},
    }}}
{
}

auto StarDrawer::DrawStar(const Star& star,
                          const float speedFactor,
                          const DrawFunc& drawFunc) noexcept -> void
{
  const auto tAge                   = star.GetAge() / star.GetMaxAge();
  static constexpr auto EXTRA_T_AGE = 0.5F;
  const auto tAgeMax                = std::min(tAge + EXTRA_T_AGE, 1.0F);

  const auto brightness              = GetBrightness(tAge);
  const auto partMultiplier          = GetPartMultiplier();
  const auto [numParts, elementSize] = GetNumPartsAndElementSize(tAge);

  auto tAgePart     = TValue{TValue::StepType::SINGLE_CYCLE, numParts};
  const auto point0 = star.GetStartPos().ToInt();

  auto point1 = point0;
  for (auto j = 1U; j <= numParts; ++j)
  {
    const auto thisPartFraction = static_cast<float>(j) / static_cast<float>(numParts);
    const auto thisPartVelocity = partMultiplier * (thisPartFraction * star.GetVelocity());
    const auto twistFrequency   = speedFactor * thisPartVelocity;

    const auto point2 = point0 - GetPointVelocity(twistFrequency, thisPartVelocity);

    const auto t                  = STD20::lerp(tAge, tAgeMax, tAgePart());
    const auto thisPartBrightness = thisPartFraction * brightness;
    const auto thisPartColors     = m_getMixedColorsFunc(thisPartBrightness, star, t);

    drawFunc(point1, point2, elementSize, thisPartColors);

    point1 = point2;
    tAgePart.Increment();
  }
}

inline auto StarDrawer::GetPointVelocity(const Vec2dFlt& twistFrequency,
                                         const Vec2dFlt& velocity) noexcept -> Vec2dInt
{
  static constexpr auto HALF = 0.5F;
  return {static_cast<int32_t>(HALF * (1.0F + std::sin(twistFrequency.x)) * velocity.x),
          static_cast<int32_t>(HALF * (1.0F + std::cos(twistFrequency.y)) * velocity.y)};
}

inline auto StarDrawer::GetBrightness(const float tAge) noexcept -> float
{
  static constexpr auto BRIGHTNESS_FACTOR = 10.0F;
  static constexpr auto BRIGHTNESS_MIN    = 0.2F;
  const auto ageBrightness                = (0.8F * std::fabs(0.10F - tAge)) / 0.25F;

  return BRIGHTNESS_FACTOR * (BRIGHTNESS_MIN + ageBrightness);
}

inline auto StarDrawer::GetPartMultiplier() const noexcept -> float
{
  if (m_currentActualDrawElement == DrawElementTypes::LINES)
  {
    return m_goomRand.GetRandInRange(1.0F, GetLineMaxPartMultiplier());
  }

  return m_goomRand.GetRandInRange(1.0F, GetMaxPartMultiplier());
}

inline auto StarDrawer::GetMaxPartMultiplier() const noexcept -> float
{
  static constexpr auto MAX_MULTIPLIER = 20.0F;

  switch (m_drawMode)
  {
    case DrawModes::CLEAN:
    case DrawModes::SUPER_CLEAN:
      return 1.0F + UTILS::MATH::SMALL_FLOAT;
    case DrawModes::MESSY:
      return MAX_MULTIPLIER;
    default:
      FailFast();
      return 0.0F;
  }
}

inline auto StarDrawer::GetLineMaxPartMultiplier() const noexcept -> float
{
  static constexpr auto LINE_MAX_MULTIPLIER = 4.0F;

  switch (m_drawMode)
  {
    case DrawModes::SUPER_CLEAN:
      return 1.0F + UTILS::MATH::SMALL_FLOAT;
    case DrawModes::CLEAN:
    case DrawModes::MESSY:
      return LINE_MAX_MULTIPLIER;
    default:
      FailFast();
      return 0.0F;
  }
}

inline auto StarDrawer::GetNumPartsAndElementSize(const float tAge) const noexcept
    -> std::pair<uint32_t, uint32_t>
{
  if (static constexpr auto T_OLD_AGE = 0.95F; tAge > T_OLD_AGE)
  {
    return {m_currentMaxNumParts, m_goomRand.GetRandInRange(MIN_DOT_SIZE, MAX_DOT_SIZE + 1)};
  }

  static constexpr auto MIN_ELEMENT_SIZE = 1U;
  const auto numParts =
      MIN_NUM_PARTS +
      static_cast<uint32_t>(
          std::lround((1.0F - tAge) * static_cast<float>(m_currentMaxNumParts - MIN_NUM_PARTS)));

  return {numParts, MIN_ELEMENT_SIZE};
}

inline auto StarDrawer::DrawParticleCircle(const Point2dInt point1,
                                           [[maybe_unused]] const Point2dInt point2,
                                           const uint32_t elementSize,
                                           const MultiplePixels& colors) noexcept -> void
{
  m_draw.Circle(point1, static_cast<int>(elementSize), colors);
}

inline auto StarDrawer::DrawParticleLine(const Point2dInt point1,
                                         const Point2dInt point2,
                                         const uint32_t elementSize,
                                         const MultiplePixels& colors) noexcept -> void
{
  m_draw.Line(point1, point2, colors, static_cast<uint8_t>(elementSize));
}

inline auto StarDrawer::DrawParticleDot(const Point2dInt point1,
                                        [[maybe_unused]] const Point2dInt point2,
                                        const uint32_t elementSize,
                                        const MultiplePixels& colors) noexcept -> void
{
  const auto getMainColor =
      [&colors]([[maybe_unused]] const size_t x, [[maybe_unused]] const size_t y, const Pixel& bgnd)
  { return GetColorMultiply(bgnd, colors[0]); };
  const auto getLowColor =
      [&colors]([[maybe_unused]] const size_t x, [[maybe_unused]] const size_t y, const Pixel& bgnd)
  { return GetColorMultiply(bgnd, colors[1]); };

  const auto& bitmap   = GetImageBitmap(elementSize);
  const auto getColors = std::vector<IGoomDraw::GetBitmapColorFunc>{getMainColor, getLowColor};
  m_draw.Bitmap(point1, bitmap, getColors);
}

inline auto StarDrawer::GetImageBitmap(const uint32_t size) const noexcept -> const ImageBitmap&
{
  return m_smallBitmaps.GetImageBitmap(SmallImageBitmaps::ImageNames::CIRCLE,
                                       std::clamp(size, MIN_DOT_SIZE, MAX_DOT_SIZE));
}

} //namespace GOOM::VISUAL_FX::FLYING_STARS
