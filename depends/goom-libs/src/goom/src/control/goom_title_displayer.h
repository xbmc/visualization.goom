#pragma once

#include "color/color_adjustment.h"
#include "color/color_maps.h"
#include "color/random_color_maps.h"
#include "goom_graphic.h"
#include "point2d.h"
#include "utils/math/goom_rand_base.h"
#include "utils/propagate_const.h"

#include <cstdint>
#include <memory>
#include <vector>

namespace GOOM
{

namespace DRAW
{
class IGoomDraw;
class TextDraw;
}

namespace CONTROL
{

class GoomTitleDisplayer
{
public:
  GoomTitleDisplayer() noexcept = delete;
  GoomTitleDisplayer(DRAW::IGoomDraw& draw,
                     const UTILS::MATH::IGoomRand& goomRand,
                     const std::string& fontDirectory);

  void SetInitialPosition(int32_t xStart, int32_t yStart);

  [[nodiscard]] auto IsInitialPhase() const -> bool;
  [[nodiscard]] auto IsMiddlePhase() const -> bool;
  [[nodiscard]] auto IsFinalPhase() const -> bool;
  [[nodiscard]] auto IsFinished() const -> bool;

  void DrawMovingText(const std::string& title);
  void DrawStaticText(const std::string& title);

private:
  const UTILS::MATH::IGoomRand& m_goomRand;
  static constexpr int32_t MAX_TEXT_DISPLAY_TIME      = 200;
  static constexpr int32_t TIME_TO_START_MIDDLE_PHASE = 100;
  static constexpr int32_t TIME_TO_START_FINAL_PHASE  = 50;
  float m_xPos                                        = 0.0F;
  float m_yPos                                        = 0.0F;
  int32_t m_timeLeftOfTitleDisplay                    = MAX_TEXT_DISPLAY_TIME;
  std::experimental::propagate_const<std::unique_ptr<DRAW::TextDraw>> m_textDraw;
  const int32_t m_screenWidth;
  const int32_t m_screenHeight;
  const std::string m_fontDirectory;
  struct FontInfo
  {
    std::string fontFilename;
    float fontSizeNormalizeFactor;
  };
  static const std::vector<FontInfo> FONT_INFO;
  const size_t m_fontInfoIndex{
      m_goomRand.GetRandInRange(0U, static_cast<uint32_t>(FONT_INFO.size()))};
  [[nodiscard]] auto GetSelectedFontPath() const -> std::string;
  [[nodiscard]] auto GetSelectedFontSize() const -> int32_t;

  const COLOR::IColorMap* m_textColorMap{&COLOR::RandomColorMaps::GetRandomColorMap(m_goomRand)};
  const COLOR::IColorMap* m_textOutlineColorMap{
      &COLOR::RandomColorMaps::GetRandomColorMap(m_goomRand)};
  const COLOR::IColorMap* m_charColorMap{&COLOR::RandomColorMaps::GetRandomColorMap(
      m_goomRand, COLOR::ColorMapGroup::DIVERGING_BLACK)};
  void DrawText(const std::string& text);
  [[nodiscard]] auto GetColorT() const -> float;
  [[nodiscard]] auto GetFontCharColorMixT() const -> float;
  [[nodiscard]] auto GetTextBrightness() const -> float;
  [[nodiscard]] auto GetInteriorColor(float fontColorT,
                                      float fontCharColorMixT,
                                      Point2dInt point,
                                      int32_t charWidth,
                                      int32_t charHeight) const -> Pixel;
  [[nodiscard]] auto GetInitialPhaseInteriorColor(float fontColorT) const -> Pixel;
  [[nodiscard]] auto GetMiddlePhaseInteriorColor(float fontColorT,
                                                 float fontCharColorMixT,
                                                 Point2dInt point,
                                                 int32_t charWidth,
                                                 int32_t charHeight) const -> Pixel;
  [[nodiscard]] auto GetFinalPhaseInteriorColor(float fontCharColorMixT,
                                                Point2dInt point,
                                                int32_t charWidth,
                                                int32_t charHeight) const -> Pixel;
  [[nodiscard]] auto GetOutlineColor(float fontColorT,
                                     float fontCharColorMixT,
                                     int32_t x,
                                     int32_t charWidth) const -> Pixel;

  [[nodiscard]] auto GetCharSpacing() const -> float;
  void UpdateColorMaps();
  void UpdateFontSize();
  void UpdatePositionIncrements(const std::string& title);
  void UpdateTextPosition();
  void SetFinalPhaseColorMaps();
  [[nodiscard]] auto GetFinalPhaseFontSize(int32_t timeLeftOfTitleDisplay) const -> int32_t;
  static constexpr float INITIAL_PHASE_X_INCREMENT = 0.01F;
  static constexpr float INITIAL_PHASE_Y_INCREMENT = 0.0F;
  static constexpr float MIDDLE_PHASE_X_INCREMENT  = 1.0F;
  static constexpr float MIDDLE_PHASE_Y_INCREMENT  = 0.0F;
  struct FinalPhaseIncrements
  {
    float xIncrement = 0.0F;
    float yIncrement = 0.0F;
  };
  FinalPhaseIncrements m_finalPhaseIncrements{};
  [[nodiscard]] auto GetFinalPhaseIncrements(const std::string& title) -> FinalPhaseIncrements;
  [[nodiscard]] auto GetXIncrement() const -> float;
  [[nodiscard]] auto GetYIncrement() const -> float;
  [[nodiscard]] auto GetFinalPhaseCentrePenPos(const std::string& str) -> Point2dFlt;

  static constexpr float TEXT_GAMMA = 1.0F / 2.0F;
  COLOR::ColorAdjustment m_textColorAdjust{TEXT_GAMMA,
                                           COLOR::ColorAdjustment::INCREASED_CHROMA_FACTOR};
};

inline void GoomTitleDisplayer::DrawStaticText(const std::string& title)
{
  DrawText(title);
}

inline void GoomTitleDisplayer::SetInitialPosition(const int32_t xStart, const int32_t yStart)
{
  m_xPos = static_cast<float>(xStart);
  m_yPos = static_cast<float>(yStart);
}

inline auto GoomTitleDisplayer::IsInitialPhase() const -> bool
{
  return m_timeLeftOfTitleDisplay > TIME_TO_START_MIDDLE_PHASE;
}

inline auto GoomTitleDisplayer::IsMiddlePhase() const -> bool
{
  return (TIME_TO_START_MIDDLE_PHASE >= m_timeLeftOfTitleDisplay) &&
         (m_timeLeftOfTitleDisplay > TIME_TO_START_FINAL_PHASE);
}

inline auto GoomTitleDisplayer::IsFinalPhase() const -> bool
{
  return m_timeLeftOfTitleDisplay <= TIME_TO_START_FINAL_PHASE;
}

inline auto GoomTitleDisplayer::IsFinished() const -> bool
{
  static constexpr auto LINGER_TIME = 10;
  return m_timeLeftOfTitleDisplay <= -LINGER_TIME;
}

} // namespace CONTROL
} // namespace GOOM
