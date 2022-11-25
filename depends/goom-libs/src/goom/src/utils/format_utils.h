#pragma once

#include "goom_config.h"
#include "goom_graphic.h"
#include "point2d.h"

#include <format>
#include <string>

namespace GOOM::UTILS
{

template<typename TPoint>
[[nodiscard]] inline auto fmt_pt(const char* const fmtStr, const TPoint& point)
{
  const auto format = std20::format("({}, {})", fmtStr, fmtStr);
  return fmt::vformat(format, std20::make_format_args(point.x, point.y));
}

[[nodiscard]] inline auto fmt_rgba(const char* const fmtStr, const Pixel& pixel)
{
  const auto format = std20::format("({}, {}, {}, {})", fmtStr, fmtStr, fmtStr, fmtStr);
  return fmt::vformat(format, std20::make_format_args(pixel.R(), pixel.G(), pixel.B(), pixel.A()));
}

[[nodiscard]] inline auto fmt_rgb_f(const char* const fmtStr, const Pixel& pixel)
{
  const auto *const bestFmtStr = std::string(fmtStr) == "{}" ? "{:.2f}" : fmtStr;
  const auto format = std20::format("({}, {}, {})", bestFmtStr, bestFmtStr, bestFmtStr);
  return fmt::vformat(format, std20::make_format_args(pixel.RFlt(), pixel.GFlt(), pixel.BFlt()));
}

} // namespace GOOM::UTILS
