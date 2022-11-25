#pragma once

#include "draw/goom_draw.h"
#include "stars.h"
#include "utils/enum_utils.h"
#include "utils/graphics/small_image_bitmaps.h"
#include "utils/math/goom_rand_base.h"

#include <cstdint>
#include <functional>

namespace GOOM::VISUAL_FX::FLYING_STARS
{

class StarDrawer
{
public:
  using GetMixedColorsFunc =
      std::function<DRAW::MultiplePixels(float brightness, const Star& star, float t)>;

  StarDrawer(DRAW::IGoomDraw& draw,
             const UTILS::MATH::IGoomRand& goomRand,
             const UTILS::GRAPHICS::SmallImageBitmaps& smallBitmaps,
             const GetMixedColorsFunc& getMixedColorsFunc) noexcept;

  auto ChangeDrawMode() noexcept -> void;

  auto DrawStar(const Star& star, float speedFactor) noexcept -> void;

private:
  DRAW::IGoomDraw& m_draw;
  const UTILS::MATH::IGoomRand& m_goomRand;
  const UTILS::GRAPHICS::SmallImageBitmaps& m_smallBitmaps;
  const GetMixedColorsFunc m_getMixedColorsFunc;

  enum class DrawElementTypes
  {
    CIRCLES,
    LINES,
    DOTS,
    CIRCLES_AND_LINES,
    _num // unused, and marks the enum end
  };
  static constexpr float DRAW_ELEMENT_TYPES_DOTS_WEIGHT              = 30.0F;
  static constexpr float DRAW_ELEMENT_TYPES_CIRCLES_WEIGHT           = 20.0F;
  static constexpr float DRAW_ELEMENT_TYPES_LINES_WEIGHT             = 10.0F;
  static constexpr float DRAW_ELEMENT_TYPES_CIRCLES_AND_LINES_WEIGHT = 15.0F;
  const UTILS::MATH::Weights<DrawElementTypes> m_drawElementWeights{
      m_goomRand,
      {
        {DrawElementTypes::DOTS, DRAW_ELEMENT_TYPES_DOTS_WEIGHT},
        {DrawElementTypes::CIRCLES, DRAW_ELEMENT_TYPES_CIRCLES_WEIGHT},
        {DrawElementTypes::LINES, DRAW_ELEMENT_TYPES_LINES_WEIGHT},
        {DrawElementTypes::CIRCLES_AND_LINES, DRAW_ELEMENT_TYPES_CIRCLES_AND_LINES_WEIGHT},
        }
  };
  DrawElementTypes m_requestedDrawElement = m_drawElementWeights.GetRandomWeighted();
  DrawElementTypes m_currentActualDrawElement{};
  auto UpdateActualDrawElement() noexcept -> void;
  enum class DrawModes
  {
    CLEAN,
    SUPER_CLEAN,
    MESSY,
    _num // unused, and marks the enum end
  };
  static constexpr float DRAW_MODES_CLEAN_WEIGHT       = 20.0F;
  static constexpr float DRAW_MODES_SUPER_CLEAN_WEIGHT = 10.0F;
  static constexpr float DRAW_MODES_MESSY              = 30.0F;
  const UTILS::MATH::Weights<DrawModes> m_drawModeWeights{
      m_goomRand,
      {
        {DrawModes::CLEAN, DRAW_MODES_CLEAN_WEIGHT},
        {DrawModes::SUPER_CLEAN, DRAW_MODES_SUPER_CLEAN_WEIGHT},
        {DrawModes::MESSY, DRAW_MODES_MESSY},
        }
  };
  DrawModes m_drawMode                             = m_drawModeWeights.GetRandomWeighted();
  static constexpr uint32_t MIN_NUM_PARTS          = 2;
  static constexpr uint32_t MAX_NUM_PARTS          = 10;
  static constexpr uint32_t MAX_NUM_PARTS_FOR_LINE = 2;
  uint32_t m_currentMaxNumParts                    = MAX_NUM_PARTS;
  auto ChangeMaxNumParts() noexcept -> void;

  static constexpr uint32_t MIN_DOT_SIZE = 3;
  static constexpr uint32_t MAX_DOT_SIZE = 5;
  static_assert(MAX_DOT_SIZE <= UTILS::GRAPHICS::SmallImageBitmaps::MAX_IMAGE_SIZE,
                "Max dot size mismatch.");
  [[nodiscard]] auto GetImageBitmap(uint32_t size) const noexcept
      -> const UTILS::GRAPHICS::ImageBitmap&;

  using DrawFunc = std::function<void(Point2dInt point1,
                                      Point2dInt point2,
                                      uint32_t elementSize,
                                      const DRAW::MultiplePixels& colors)>;
  const UTILS::EnumMap<DrawElementTypes, DrawFunc> m_drawFuncs;
  auto DrawStar(const Star& star, float speedFactor, const DrawFunc& drawFunc) noexcept -> void;
  [[nodiscard]] auto GetNumPartsAndElementSize(float tAge) const noexcept
      -> std::pair<uint32_t, uint32_t>;
  [[nodiscard]] auto GetPartMultiplier() const noexcept -> float;
  [[nodiscard]] auto GetMaxPartMultiplier() const noexcept -> float;
  [[nodiscard]] auto GetLineMaxPartMultiplier() const noexcept -> float;
  [[nodiscard]] static auto GetBrightness(float tAge) noexcept -> float;
  [[nodiscard]] static auto GetPointVelocity(const Vec2dFlt& twistFrequency,
                                             const Vec2dFlt& velocity) noexcept -> Vec2dInt;
  auto DrawParticleCircle(Point2dInt point1,
                          Point2dInt point2,
                          uint32_t elementSize,
                          const DRAW::MultiplePixels& colors) noexcept -> void;
  auto DrawParticleLine(Point2dInt point1,
                        Point2dInt point2,
                        uint32_t elementSize,
                        const DRAW::MultiplePixels& colors) noexcept -> void;
  auto DrawParticleDot(Point2dInt point1,
                       Point2dInt point2,
                       uint32_t elementSize,
                       const DRAW::MultiplePixels& colors) noexcept -> void;
};

inline auto StarDrawer::ChangeDrawMode() noexcept -> void
{
  m_drawMode             = m_drawModeWeights.GetRandomWeighted();
  m_requestedDrawElement = m_drawElementWeights.GetRandomWeighted();
}

inline auto StarDrawer::UpdateActualDrawElement() noexcept -> void
{
  if (m_requestedDrawElement != DrawElementTypes::CIRCLES_AND_LINES)
  {
    m_currentActualDrawElement = m_requestedDrawElement;
  }
  else
  {
    static constexpr auto PROB_CIRCLES = 0.5F;
    m_currentActualDrawElement = m_goomRand.ProbabilityOf(PROB_CIRCLES) ? DrawElementTypes::CIRCLES
                                                                        : DrawElementTypes::LINES;
  }
}

inline auto StarDrawer::ChangeMaxNumParts() noexcept -> void
{
  m_currentMaxNumParts = m_currentActualDrawElement == DrawElementTypes::LINES
                             ? MAX_NUM_PARTS_FOR_LINE
                             : MAX_NUM_PARTS;
}

inline auto StarDrawer::DrawStar(const Star& star, const float speedFactor) noexcept -> void
{
  UpdateActualDrawElement();
  ChangeMaxNumParts();
  DrawStar(star, speedFactor, m_drawFuncs[m_currentActualDrawElement]);
}

} //namespace GOOM::VISUAL_FX::FLYING_STARS
