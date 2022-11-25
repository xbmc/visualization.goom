#pragma once

#include "goom_graphic.h"

namespace GOOM::VISUAL_FX::LINES
{

enum class LineType
{
  CIRCLE = 0, // (param = radius)
  H_LINE, // (param = y)
  V_LINE, // (param = x)
  _num // must be last - gives number of enums
};

struct LineParams
{
  LineType lineType;
  float param;
  Pixel color;
  float amplitude;
};


} // namespace GOOM::VISUAL_FX::LINES
