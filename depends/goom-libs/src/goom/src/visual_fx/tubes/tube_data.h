#pragma once

#include "draw/goom_draw.h"
#include "point2d.h"
#include "utils/graphics/small_image_bitmaps.h"

#include <cstdint>
#include <functional>
#include <memory>

namespace GOOM
{

namespace COLOR
{
class RandomColorMaps;
}

namespace UTILS::MATH
{
class IGoomRand;
}

namespace VISUAL_FX::TUBES
{

using DrawLineFunc   = std::function<void(
    Point2dInt point1, Point2dInt point2, const DRAW::MultiplePixels& colors, uint8_t thickness)>;
using DrawCircleFunc = std::function<void(
    Point2dInt point, int radius, const DRAW::MultiplePixels& colors, uint8_t thickness)>;
using DrawSmallImageFunc =
    std::function<void(Point2dInt midPoint,
                       UTILS::GRAPHICS::SmallImageBitmaps::ImageNames imageName,
                       uint32_t size,
                       const DRAW::MultiplePixels& colors)>;

// NOLINTBEGIN: Stop gcc-12 'inline' warning
struct TubeDrawFuncs
{
  ~TubeDrawFuncs() noexcept;
  DrawLineFunc drawLine;
  DrawCircleFunc drawCircle;
  DrawSmallImageFunc drawSmallImage;
};
// NOLINTEND

// NOLINTBEGIN: Stop gcc-12 'inline' warning
struct TubeData
{
  ~TubeData() noexcept;
  uint32_t tubeId;
  TubeDrawFuncs drawFuncs;
  uint32_t screenWidth;
  uint32_t screenHeight;
  const UTILS::MATH::IGoomRand& goomRand;
  std::shared_ptr<const COLOR::RandomColorMaps> mainColorMaps;
  std::shared_ptr<const COLOR::RandomColorMaps> lowColorMaps;
  float radiusEdgeOffset;
  float brightnessFactor;
};
// NOLINTEND

} // namespace VISUAL_FX::TUBES
} // namespace GOOM
