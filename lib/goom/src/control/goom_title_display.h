#ifndef VISUALIZATION_GOOM_GOOM_TITLE_DISPLAY_H
#define VISUALIZATION_GOOM_GOOM_TITLE_DISPLAY_H

#include "goom_graphic.h"
#include "goomutils/colorutils.h"

#include <cstdint>
#include <memory>
#include <string>
#include <vector>

namespace GOOM
{

class IGoomDraw;

namespace DRAW
{
class TextDraw;
}
namespace UTILS
{
class IColorMap;
}

namespace CONTROL
{

class GoomTitleDisplay
{
public:
  GoomTitleDisplay() noexcept = delete;
  ~GoomTitleDisplay() noexcept;
  GoomTitleDisplay(int32_t xStart,
                   int32_t yStart,
                   const std::string& fontDirectory,
                   const IGoomDraw* draw);
  GoomTitleDisplay(const GoomTitleDisplay&) noexcept = delete;
  GoomTitleDisplay(GoomTitleDisplay&&) noexcept = delete;
  auto operator=(const GoomTitleDisplay&) -> GoomTitleDisplay& = delete;
  auto operator=(GoomTitleDisplay&&) -> GoomTitleDisplay& = delete;

  auto IsInitialPhase() const -> bool;
  auto IsMiddlePhase() const -> bool;
  auto IsFinalPhase() const -> bool;
  auto IsFinished() const -> bool;

  void Draw(const std::string& title);

private:
  static constexpr int MAX_TEXT_DISPLAY_TIME = 200;
  static constexpr int TIME_TO_START_MIDDLE_PHASE = 100;
  static constexpr int TIME_TO_START_FINAL_PHASE = 50;
  static constexpr int32_t TIME_TO_START_FINAL_FADE = 15;
  float m_xPos;
  float m_yPos;
  int32_t m_timeLeftOfTitleDisplay = MAX_TEXT_DISPLAY_TIME;
  const std::unique_ptr<DRAW::TextDraw> m_textDraw;
  const uint32_t m_screenHeight;
  const std::string m_fontDirectory;
  struct FontInfo
  {
    std::string fontFilename;
    float fontSizeNormalizeFactor;
  };
  static const std::vector<FontInfo> s_fontInfo;
  const size_t m_fontInfoIndex;
  [[nodiscard]] auto GetSelectedFontPath() const -> std::string;
  [[nodiscard]] auto GetSelectedFontSize() const -> int32_t;
  const UTILS::IColorMap* m_textColorMap;
  const UTILS::IColorMap* m_textOutlineColorMap;
  const UTILS::IColorMap* m_charColorMap;
  void DrawText(const std::string& str);
  auto GetCharSpacing() const -> float;
  auto GetXIncrement() const -> float;
  auto GetYIncrement() const -> float;
  auto GetBrightness() const -> float;
  static constexpr float TEXT_GAMMA = 1.0F / 1.0F;
  static constexpr float TEXT_GAMMA_BRIGHTNESS_THRESHOLD = 0.01F;
  UTILS::GammaCorrection m_textGammaCorrect{TEXT_GAMMA, TEXT_GAMMA_BRIGHTNESS_THRESHOLD};
  auto GetTextGammaCorrection(float brightness, const Pixel& color) const -> Pixel;
};

inline auto GoomTitleDisplay::IsInitialPhase() const -> bool
{
  return m_timeLeftOfTitleDisplay > TIME_TO_START_MIDDLE_PHASE;
}

inline auto GoomTitleDisplay::IsMiddlePhase() const -> bool
{
  return TIME_TO_START_MIDDLE_PHASE >= m_timeLeftOfTitleDisplay &&
         m_timeLeftOfTitleDisplay > TIME_TO_START_FINAL_PHASE;
}

inline auto GoomTitleDisplay::IsFinalPhase() const -> bool
{
  return m_timeLeftOfTitleDisplay <= TIME_TO_START_FINAL_PHASE;
}

inline auto GoomTitleDisplay::IsFinished() const -> bool
{
  return m_timeLeftOfTitleDisplay <= 0;
}

} // namespace CONTROL
} // namespace GOOM

#endif //VISUALIZATION_GOOM_GOOM_TITLE_DISPLAY_H
