#pragma once

#include "draw/text_draw.h"
#include "point2d.h"

#include <cstdint>
#include <string>
#include <vector>

namespace GOOM::UTILS::TEXT
{

[[nodiscard]] auto GetLinesOfWords(const std::string& text, uint32_t maxLineLength)
    -> std::vector<std::string>;

[[nodiscard]] auto GetLeftAlignedPenForCentringStringAt(DRAW::TextDraw& textDraw,
                                                        const std::string& text,
                                                        int32_t fontSize,
                                                        const Point2dInt& centreAt) -> Point2dInt;

} // namespace GOOM::UTILS::TEXT
