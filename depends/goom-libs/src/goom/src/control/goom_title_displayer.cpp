#include "goom_title_displayer.h"

//#undef NO_LOGGING

#include "color/color_maps.h"
#include "color/random_color_maps.h"
#include "draw/goom_draw.h"
#include "draw/text_draw.h"
#include "logging.h"
#include "goom_config.h"
#include "goom_graphic.h"
#include "utils/math/goom_rand_base.h"
#include "utils/math/misc.h"
#include "utils/text/drawable_text.h"

#include <cstdint>
#include <memory>
#include <string>

namespace GOOM::CONTROL
{

using COLOR::IColorMap;
using COLOR::RandomColorMaps;
using DRAW::IGoomDraw;
using DRAW::TextDraw;
using UTILS::Logging; // NOLINT(misc-unused-using-decls)
using UTILS::MATH::GetFltFraction;
using UTILS::MATH::I_HALF;
using UTILS::MATH::IGoomRand;
using UTILS::TEXT::GetLeftAlignedPenForCentringStringAt;
using UTILS::TEXT::GetLinesOfWords;

static constexpr auto INITIAL_PHASE_T_MIX   = 0.1F;
static constexpr auto BASE_BRIGHTNESS       = 9.0F;
static constexpr auto MAX_BRIGHTNESS_FACTOR = 2.0F;

static constexpr auto MAX_LINE_LENGTH                     = 40U;
static constexpr auto FONT_SIZE_FRACTION_OF_SCREEN_HEIGHT = 0.05F;
static constexpr auto MAX_FONT_SIZE_MULTIPLIER            = 10.0F;
static constexpr auto SPACE_FACTOR                        = 0.056F;
static constexpr auto OUTLINE_FONT_WIDTH                  = 4;
static constexpr auto TIME_TO_START_FINAL_SOLID_COLOR     = 10;
static constexpr auto FINAL_PHASE_MIX_FACTOR              = 0.2F;
static constexpr auto FINAL_PHASE_INTERIOR_COLOR          = Pixel{210U, 210U, 210U, 255U};

// To normalize: turn on logging in TextDraw, get width of prepared text for a
// sample text for each font, then normalize with 'verdana' as 1.0.
//
const std::vector<GoomTitleDisplayer::FontInfo> GoomTitleDisplayer::FONT_INFO = {
    {  "AeroviasBrasilNF.ttf", 1.34F},
    { "AlexBrush-Regular.ttf", 1.25F},
    {   "AvenueX-Regular.otf", 1.01F},
    {        "CelticHand.ttf", 0.99F},
    {         "CheapSign.ttf", 1.26F},
    {         "EatAtJoes.ttf", 0.90F},
    {"GreatVibes-Regular.ttf", 1.29F},
    {          "KellsFLF.ttf", 1.23F},
    {     "Rubik-Regular.ttf",  1.1F},
    {           "verdana.ttf",  1.0F},
};

inline auto GoomTitleDisplayer::GetSelectedFontPath() const -> std::string
{
  return m_fontDirectory + PATH_SEP + FONT_INFO.at(m_fontInfoIndex).fontFilename;
}

inline auto GoomTitleDisplayer::GetSelectedFontSize() const -> int32_t
{
  const auto& fontInfo   = FONT_INFO.at(m_fontInfoIndex);
  const auto maxFontSize = static_cast<int32_t>(
      (FONT_SIZE_FRACTION_OF_SCREEN_HEIGHT * static_cast<float>(m_screenHeight)) *
      fontInfo.fontSizeNormalizeFactor);
  return maxFontSize;
}

GoomTitleDisplayer::GoomTitleDisplayer(IGoomDraw& draw,
                                       const IGoomRand& goomRand,
                                       const std::string& fontDirectory)
  : m_goomRand{goomRand},
    m_textDraw{std::make_unique<TextDraw>(draw)},
    m_screenWidth{draw.GetScreenDimensions().GetIntWidth()},
    m_screenHeight{draw.GetScreenDimensions().GetIntHeight()},
    m_fontDirectory{fontDirectory}
{
  m_textDraw->SetFontFile(GetSelectedFontPath());
  m_textDraw->SetFontSize(GetSelectedFontSize());
  m_textDraw->SetOutlineWidth(OUTLINE_FONT_WIDTH);
  m_textDraw->SetAlignment(TextDraw::TextAlignment::LEFT);
}

void GoomTitleDisplayer::DrawMovingText(const std::string& title)
{
  --m_timeLeftOfTitleDisplay;

  UpdatePositionIncrements(title);
  UpdateColorMaps();
  UpdateFontSize();
  UpdateTextPosition();
  DrawText(title);
}

inline void GoomTitleDisplayer::UpdatePositionIncrements(const std::string& title)
{
  if (m_timeLeftOfTitleDisplay == TIME_TO_START_FINAL_PHASE)
  {
    m_finalPhaseIncrements = GetFinalPhaseIncrements(title.substr(0, 1));
  }
}

inline void GoomTitleDisplayer::UpdateColorMaps()
{
  if (m_timeLeftOfTitleDisplay == TIME_TO_START_FINAL_PHASE)
  {
    SetFinalPhaseColorMaps();
  }
}

inline void GoomTitleDisplayer::UpdateFontSize()
{
  if (m_timeLeftOfTitleDisplay < 0)
  {
    return;
  }

  if (m_timeLeftOfTitleDisplay < TIME_TO_START_FINAL_PHASE)
  {
    m_textDraw->SetFontSize(GetFinalPhaseFontSize(m_timeLeftOfTitleDisplay));
  }
}

inline void GoomTitleDisplayer::UpdateTextPosition()
{
  if (m_timeLeftOfTitleDisplay < 0)
  {
    return;
  }

  m_xPos += GetXIncrement();
  m_yPos += GetYIncrement();
}

inline void GoomTitleDisplayer::SetFinalPhaseColorMaps()
{
  const auto randomColorMaps = RandomColorMaps{m_goomRand};
  m_textColorMap        = &randomColorMaps.GetRandomColorMap(COLOR::ColorMapGroup::DIVERGING_BLACK);
  m_textOutlineColorMap = &randomColorMaps.GetRandomColorMap(COLOR::ColorMapGroup::HEAT);
  m_charColorMap        = &randomColorMaps.GetRandomColorMap(COLOR::ColorMapGroup::DIVERGING_BLACK);
}

inline auto GoomTitleDisplayer::GetFinalPhaseFontSize(const int32_t timeLeftOfTitleDisplay) const
    -> int32_t
{
  const auto fractionOfTimeLeft = GetFltFraction(timeLeftOfTitleDisplay, TIME_TO_START_FINAL_PHASE);
  const auto t                  = 1.0F - std::pow(fractionOfTimeLeft, 0.7F);
  const auto fontSizeMultiplier = STD20::lerp(1.0F, MAX_FONT_SIZE_MULTIPLIER, t);
  return static_cast<int32_t>(fontSizeMultiplier * static_cast<float>(GetSelectedFontSize()));
}

auto GoomTitleDisplayer::GetFinalPhaseIncrements(const std::string& title) -> FinalPhaseIncrements
{
  const auto [finalXPos, finalYPos] = GetFinalPhaseCentrePenPos(title);
  return {(finalXPos - m_xPos) / static_cast<float>(TIME_TO_START_FINAL_PHASE),
          (finalYPos - m_yPos) / static_cast<float>(TIME_TO_START_FINAL_PHASE)};
}

inline auto GoomTitleDisplayer::GetFinalPhaseCentrePenPos(const std::string& str) -> Point2dFlt
{
  const auto screenCentre = Point2dInt{I_HALF * m_screenWidth, I_HALF * m_screenHeight};
  const auto fontSize     = GetFinalPhaseFontSize(0);
  return GetLeftAlignedPenForCentringStringAt(*m_textDraw, str, fontSize, screenCentre).ToFlt();
}

void GoomTitleDisplayer::DrawText(const std::string& text)
{
  if ((m_xPos < 0.0F) || (m_xPos >= static_cast<float>(m_screenWidth)))
  {
    return;
  }
  if ((m_yPos < 0.0F) || (m_yPos >= static_cast<float>(m_screenHeight)))
  {
    return;
  }

  const auto colorT            = GetColorT();
  const auto fontCharColorMixT = GetFontCharColorMixT();
  const auto textBrightness    = GetTextBrightness();

  const auto getFontColor = [this, &colorT, &textBrightness, &fontCharColorMixT](
                                [[maybe_unused]] const size_t textIndexOfChar,
                                const Point2dInt point,
                                const int32_t width,
                                const int32_t height)
  {
    const auto color = GetInteriorColor(colorT, fontCharColorMixT, point, width, height);
    return m_textColorAdjust.GetAdjustment(textBrightness, color);
  };

  const auto getOutlineFontColor = [this, &colorT, &textBrightness, &fontCharColorMixT](
                                       [[maybe_unused]] const size_t textIndexOfChar,
                                       const Point2dInt point,
                                       [[maybe_unused]] const int32_t width,
                                       [[maybe_unused]] const int32_t height)
  {
    const auto color = GetOutlineColor(colorT, fontCharColorMixT, point.x, width);
    return m_textColorAdjust.GetAdjustment(textBrightness, color);
  };

  const auto charSpacing = GetCharSpacing();

  const auto drawStr = [this, &charSpacing, &getFontColor, &getOutlineFontColor](
                           const std::string& str, const Point2dInt point)
  {
    m_textDraw->SetText(str);
    m_textDraw->SetFontColorFunc(getFontColor);
    m_textDraw->SetOutlineFontColorFunc(getOutlineFontColor);
    m_textDraw->SetCharSpacing(charSpacing);
    m_textDraw->Prepare();
    m_textDraw->Draw(point);
  };

  const auto textStrings = GetLinesOfWords(text, MAX_LINE_LENGTH);
  const auto lineSpacing = m_textDraw->GetFontSize() + m_textDraw->GetLineSpacing();
  auto y                 = static_cast<int32_t>(std::round(m_yPos));
  for (const auto& str : textStrings)
  {
    drawStr(str, {static_cast<int32_t>(std::round(m_xPos)), y});
    y += lineSpacing;
  }
}

inline auto GoomTitleDisplayer::GetInteriorColor(const float fontColorT,
                                                 const float fontCharColorMixT,
                                                 const Point2dInt point,
                                                 const int32_t charWidth,
                                                 const int32_t charHeight) const -> Pixel
{
  if (IsInitialPhase())
  {
    return GetInitialPhaseInteriorColor(fontColorT);
  }

  if (IsMiddlePhase())
  {
    return GetMiddlePhaseInteriorColor(fontColorT, fontCharColorMixT, point, charWidth, charHeight);
  }

  return GetFinalPhaseInteriorColor(fontCharColorMixT, point, charWidth, charHeight);
}

inline auto GoomTitleDisplayer::GetInitialPhaseInteriorColor(const float fontColorT) const -> Pixel
{
  return m_textColorMap->GetColor(fontColorT);
}

inline auto GoomTitleDisplayer::GetMiddlePhaseInteriorColor(const float fontColorT,
                                                            const float fontCharColorMixT,
                                                            const Point2dInt point,
                                                            const int32_t charWidth,
                                                            const int32_t charHeight) const -> Pixel
{
  const auto fontColor  = m_textColorMap->GetColor(fontColorT);
  const auto charColor1 = m_charColorMap->GetColor(GetFltFraction(point.x, charWidth));
  const auto charColor2 = m_textOutlineColorMap->GetColor(GetFltFraction(point.y, charHeight));
  static constexpr auto CHAR_COLOR_MIX = 0.5F;
  const auto charColor = IColorMap::GetColorMix(charColor1, charColor2, CHAR_COLOR_MIX);

  return IColorMap::GetColorMix(fontColor, charColor, fontCharColorMixT);
}

inline auto GoomTitleDisplayer::GetFinalPhaseInteriorColor(const float fontCharColorMixT,
                                                           const Point2dInt point,
                                                           const int32_t charWidth,
                                                           const int32_t charHeight) const -> Pixel
{
  const auto fontColor  = m_textColorMap->GetColor(fontCharColorMixT);
  const auto charColor1 = m_charColorMap->GetColor(GetFltFraction(point.x, charWidth));
  const auto charColor2 = m_textOutlineColorMap->GetColor(GetFltFraction(point.y, charHeight));
  static constexpr auto CHAR_COLOR_MIX = 0.8F;
  const auto charColor  = IColorMap::GetColorMix(charColor1, charColor2, CHAR_COLOR_MIX);
  const auto finalColor = IColorMap::GetColorMix(fontColor, charColor, fontCharColorMixT);

  if (m_timeLeftOfTitleDisplay > TIME_TO_START_FINAL_SOLID_COLOR)
  {
    return finalColor;
  }

  const auto tLeft = m_timeLeftOfTitleDisplay <= 0
                         ? 0.0F
                         : static_cast<float>(m_timeLeftOfTitleDisplay) /
                               static_cast<float>(TIME_TO_START_FINAL_SOLID_COLOR);

  const auto tMix = FINAL_PHASE_MIX_FACTOR + (tLeft * (1.0F - FINAL_PHASE_MIX_FACTOR));

  return IColorMap::GetColorMix(FINAL_PHASE_INTERIOR_COLOR, finalColor, tMix);
}

inline auto GoomTitleDisplayer::GetOutlineColor(float fontColorT,
                                                float fontCharColorMixT,
                                                int32_t x,
                                                int32_t charWidth) const -> Pixel
{
  if (IsFinalPhase())
  {
    return m_textOutlineColorMap->GetColor(fontColorT);
  }

  const auto outlineFontColor =
      (not IsMiddlePhase()) ? WHITE_PIXEL : m_textOutlineColorMap->GetColor(fontColorT);

  const auto charColor = m_textOutlineColorMap->GetColor(GetFltFraction(x, charWidth));
  return IColorMap::GetColorMix(outlineFontColor, charColor, fontCharColorMixT);
}

inline auto GoomTitleDisplayer::GetColorT() const -> float
{
  if (m_timeLeftOfTitleDisplay <= 0)
  {
    return 0.0F;
  }

  return GetFltFraction(m_timeLeftOfTitleDisplay, MAX_TEXT_DISPLAY_TIME);
}

inline auto GoomTitleDisplayer::GetTextBrightness() const -> float
{
  if (IsInitialPhase())
  {
    return BASE_BRIGHTNESS;
  }
  if (IsMiddlePhase())
  {
    return BASE_BRIGHTNESS;
  }

  if (m_timeLeftOfTitleDisplay <= 0)
  {
    return BASE_BRIGHTNESS * MAX_BRIGHTNESS_FACTOR;
  }

  const auto fractionOfTimeLeft =
      GetFltFraction(m_timeLeftOfTitleDisplay, TIME_TO_START_FINAL_PHASE);
  return BASE_BRIGHTNESS * (MAX_BRIGHTNESS_FACTOR - fractionOfTimeLeft);
}

inline auto GoomTitleDisplayer::GetFontCharColorMixT() const -> float
{
  if (IsInitialPhase())
  {
    return INITIAL_PHASE_T_MIX;
  }
  if (IsMiddlePhase())
  {
    return GetFltFraction(m_timeLeftOfTitleDisplay, TIME_TO_START_MIDDLE_PHASE);
  }
  if (m_timeLeftOfTitleDisplay <= 0)
  {
    return 0.0F;
  }

  return GetFltFraction(m_timeLeftOfTitleDisplay, TIME_TO_START_FINAL_PHASE);
}

auto GoomTitleDisplayer::GetCharSpacing() const -> float
{
  if (IsInitialPhase())
  {
    return 0.0F;
  }

  const auto timeGone = static_cast<float>(
      m_timeLeftOfTitleDisplay <= 0 ? TIME_TO_START_MIDDLE_PHASE
                                    : (TIME_TO_START_MIDDLE_PHASE - m_timeLeftOfTitleDisplay));

  return SPACE_FACTOR * timeGone;
}

auto GoomTitleDisplayer::GetXIncrement() const -> float
{
  if (IsInitialPhase())
  {
    return INITIAL_PHASE_X_INCREMENT;
  }
  if (IsMiddlePhase())
  {
    return MIDDLE_PHASE_X_INCREMENT;
  }

  return m_finalPhaseIncrements.xIncrement;
}

auto GoomTitleDisplayer::GetYIncrement() const -> float
{
  if (IsInitialPhase())
  {
    return INITIAL_PHASE_Y_INCREMENT;
  }
  if (IsMiddlePhase())
  {
    return MIDDLE_PHASE_Y_INCREMENT;
  }

  return m_finalPhaseIncrements.yIncrement;
}

} // namespace GOOM::CONTROL
