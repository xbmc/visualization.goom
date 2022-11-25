#include "drawable_text.h"

//#undef NO_LOGGING

#include "draw/text_draw.h"
#include "logging.h"
#include "point2d.h"
#include "utils/strutils.h"

#include <string>
#include <vector>

namespace GOOM::UTILS::TEXT
{

using namespace std::string_literals;
using DRAW::TextDraw;
using MATH::I_HALF;

auto GetLinesOfWords(const std::string& text, const uint32_t maxLineLength)
    -> std::vector<std::string>
{
  if (text.length() <= maxLineLength)
  {
    return {text};
  }

  const auto words = StringSplit(text, " ");
  auto textLines   = std::vector<std::string>{};
  auto str         = ""s;

  for (const auto& word : words)
  {
    str += word + " ";
    if (str.length() > maxLineLength)
    {
      textLines.emplace_back(str);
      str = "";
    }
  }

  if (!str.empty())
  {
    textLines.emplace_back(str);
  }

  return textLines;
}

auto GetLeftAlignedPenForCentringStringAt(TextDraw& textDraw,
                                          const std::string& text,
                                          const int32_t fontSize,
                                          const Point2dInt& centreAt) -> Point2dInt
{
  const auto oldFontSize    = textDraw.GetFontSize();
  const auto oldCharSpacing = textDraw.GetCharSpacing();

  textDraw.SetFontSize(fontSize);
  textDraw.SetCharSpacing(0.0F);
  textDraw.SetText(text);

  textDraw.Prepare();

  const auto strRect    = textDraw.GetPreparedTextBoundingRect();
  const auto bearingX   = textDraw.GetBearingX();
  const auto bearingY   = textDraw.GetBearingY();
  const auto textWidth  = (strRect.xMax - strRect.xMin) + 1;
  const auto textHeight = (strRect.yMax - strRect.yMin) + 1;

  LogInfo("font size = {}", textDraw.GetFontSize());
  LogInfo("charSpacing = {}", textDraw.GetCharSpacing());
  LogInfo("alignment = {}", textDraw.GetAlignment());
  LogInfo("text = {}", text);
  LogInfo("textWidth = {}, textHeight = {}", textWidth, textHeight);
  LogInfo("bearingX = {}, bearingY = {}", bearingX, bearingY);
  LogInfo("centre pen = ({},{})",
          centreAt.x - (I_HALF * (textWidth - bearingX)),
          centreAt.y - ((I_HALF * textHeight) - bearingY));

  textDraw.SetCharSpacing(oldCharSpacing);
  textDraw.SetFontSize(oldFontSize);

  return {centreAt.x - (I_HALF * (textWidth - bearingX)),
          centreAt.y - ((I_HALF * textHeight) - bearingY)};
}

} // namespace GOOM::UTILS::TEXT
