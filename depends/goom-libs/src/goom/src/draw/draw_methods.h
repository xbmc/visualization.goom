#pragma once

#include "goom_config.h"
#include "goom_graphic.h"
#include "goom_types.h"

#include <cstdint>
#include <functional>
#include <vector>

namespace GOOM::DRAW
{

using DrawPixelsToDeviceFunc =
    std::function<void(int32_t x, int32_t y, const std::vector<Pixel>& newColors)>;

class DrawMethods
{
public:
  DrawMethods(const Dimensions& dimensions, const DrawPixelsToDeviceFunc& func) noexcept;

  auto DrawCircle(int32_t x0, int32_t y0, int32_t radius, const Pixel& color) noexcept -> void;
  auto DrawCircle(int32_t x0, int32_t y0, int32_t radius, const std::vector<Pixel>& colors) noexcept
      -> void;
  auto DrawFilledCircle(int32_t x0,
                        int32_t y0,
                        int32_t radius,
                        const std::vector<Pixel>& colors) noexcept -> void;

  auto DrawLine(int32_t x1,
                int32_t y1,
                int32_t x2,
                int32_t y2,
                const Pixel& color,
                uint8_t thickness) noexcept -> void;
  auto DrawLine(int32_t x1,
                int32_t y1,
                int32_t x2,
                int32_t y2,
                const std::vector<Pixel>& colors,
                uint8_t thickness) noexcept -> void;

  auto DrawPixels(int32_t x, int32_t y, const std::vector<Pixel>& newColors) noexcept -> void;

private:
  const Dimensions m_dimensions;
  const DrawPixelsToDeviceFunc m_drawPixelsToDevice;

  using PlotCirclePointsFunc = std::function<void(int32_t x1, int32_t y1, int32_t x2, int32_t y2)>;
  static auto DrawBresenhamCircle(int32_t x0,
                                  int32_t y0,
                                  int32_t radius,
                                  const PlotCirclePointsFunc& plotter) noexcept -> void;

  auto DrawHorizontalLine(int32_t x1,
                          int32_t y,
                          int32_t x2,
                          const std::vector<Pixel>& colors) noexcept -> void;
  auto DrawThickLine(int32_t x1,
                     int32_t y1,
                     int32_t x2,
                     int32_t y2,
                     const std::vector<Pixel>& colors,
                     uint8_t thickness) noexcept -> void;
  auto DrawWuLine(int32_t x1,
                  int32_t y1,
                  int32_t x2,
                  int32_t y2,
                  const std::vector<Pixel>& colors) noexcept -> void;
  using PlotPointFunc = const std::function<void(int32_t x, int32_t y, float brightness)>;
  static auto WuLine(float x0, float y0, float x1, float y1, const PlotPointFunc& plot) noexcept
      -> void;
};

inline auto DrawMethods::DrawPixels(const int32_t x,
                                    const int32_t y,
                                    const std::vector<Pixel>& newColors) noexcept -> void
{
  Expects(x >= 0);
  Expects(y >= 0);
  Expects(static_cast<uint32_t>(x) < m_dimensions.GetWidth());
  Expects(static_cast<uint32_t>(y) < m_dimensions.GetHeight());

  m_drawPixelsToDevice(x, y, newColors);
}

} // namespace GOOM::DRAW
