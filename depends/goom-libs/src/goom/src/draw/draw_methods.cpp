// NOLINTBEGIN: Not my code

#include "draw_methods.h"

#include "color/color_utils.h"
#include "goom_config.h"
#include "goom_graphic.h"
#include "thick_lines.h"

#include <cmath>
#include <cstddef>
#include <cstdint>
#include <vector>

namespace GOOM::DRAW
{

using COLOR::GetBrighterColor;

DrawMethods::DrawMethods(const Dimensions& dimensions, const DrawPixelsToDeviceFunc& func) noexcept
  : m_dimensions{dimensions}, m_drawPixelsToDevice{func}
{
}

auto DrawMethods::DrawCircle(const int32_t x0,
                             const int32_t y0,
                             const int32_t radius,
                             const Pixel& color) noexcept -> void
{
  const std::vector<Pixel> colors{color};
  DrawCircle(x0, y0, radius, colors);
}

// Function for circle-generation using Bresenham's algorithm
auto DrawMethods::DrawBresenhamCircle(const int32_t x0,
                                      const int32_t y0,
                                      const int32_t radius,
                                      const PlotCirclePointsFunc& plotter) noexcept -> void
{
  const auto drawCircle8 = [&](const int32_t xc, int32_t const yc, const int32_t x, const int32_t y)
  {
    plotter(xc - x, yc + y, xc + x, yc + y);
    plotter(xc - x, yc - y, xc + x, yc - y);
    plotter(xc - y, yc + x, xc + y, yc + x);
    plotter(xc - y, yc - x, xc + y, yc - x);
  };

  int32_t x = 0;
  int32_t y = radius;

  drawCircle8(x0, y0, x, y);

  int32_t d = 3 - (2 * radius);
  while (y >= x)
  {
    ++x;

    if (d > 0)
    {
      --y;
      d += (4 * (x - y)) + 10;
    }
    else
    {
      d += (4 * x) + 6;
    }
    drawCircle8(x0, y0, x, y);
  }
}

auto DrawMethods::DrawCircle(const int32_t x0,
                             const int32_t y0,
                             const int32_t radius,
                             const std::vector<Pixel>& colors) noexcept -> void
{
  auto plotter =
      [this, &colors](const int32_t x1, const int32_t y1, const int32_t x2, const int32_t y2)
  {
    if ((static_cast<uint32_t>(x1) >= m_dimensions.GetWidth()) ||
        (static_cast<uint32_t>(y1) >= m_dimensions.GetHeight()))
    {
      return;
    }
    if ((static_cast<uint32_t>(x2) >= m_dimensions.GetWidth()) ||
        (static_cast<uint32_t>(y2) >= m_dimensions.GetHeight()))
    {
      return;
    }
    DrawPixels(x1, y1, colors);
    if ((x1 == x2) && (y1 == y2))
    {
      return;
    }
    DrawPixels(x2, y2, colors);
  };

  DrawBresenhamCircle(x0, y0, radius, plotter);
}

auto DrawMethods::DrawHorizontalLine(const int32_t x1,
                                     const int32_t y,
                                     const int32_t x2,
                                     const std::vector<Pixel>& colors) noexcept -> void
{
  const int32_t xEnd = x1 == x2 ? x1 : x2;
  for (int32_t x = x1; x <= xEnd; ++x)
  {
    DrawPixels(x, y, colors);
  }
}


auto DrawMethods::DrawFilledCircle(const int32_t x0,
                                   const int32_t y0,
                                   const int32_t radius,
                                   const std::vector<Pixel>& colors) noexcept -> void
{
  auto plotter =
      [this, &colors](
          const int32_t x1, const int32_t y1, const int32_t x2, [[maybe_unused]] const int32_t y2)
  {
    Expects(y1 == y2);
    DrawHorizontalLine(x1, y1, x2, colors);
  };

  DrawBresenhamCircle(x0, y0, radius, plotter);
}

auto DrawMethods::DrawLine(const int32_t x1,
                           const int32_t y1,
                           const int32_t x2,
                           const int32_t y2,
                           const Pixel& color,
                           const uint8_t thickness) noexcept -> void
{
  const std::vector<Pixel> colors{color};
  DrawLine(x1, y1, x2, y2, colors, thickness);
}

auto DrawMethods::DrawLine(const int32_t x1,
                           const int32_t y1,
                           const int32_t x2,
                           const int32_t y2,
                           const std::vector<Pixel>& colors,
                           const uint8_t thickness) noexcept -> void
{
  if (1 == thickness)
  {
    DrawWuLine(x1, y1, x2, y2, colors);
  }
  else
  {
    DrawThickLine(x1, y1, x2, y2, colors, thickness);
  }
}

auto DrawMethods::DrawWuLine(const int32_t x1,
                             const int32_t y1,
                             const int32_t x2,
                             const int32_t y2,
                             const std::vector<Pixel>& colors) noexcept -> void
{
  if ((y1 < 0) || (y2 < 0) || (x1 < 0) || (x2 < 0) ||
      (y1 >= static_cast<int>(m_dimensions.GetHeight())) ||
      (y2 >= static_cast<int>(m_dimensions.GetHeight())) ||
      (x1 >= static_cast<int>(m_dimensions.GetWidth())) ||
      (x2 >= static_cast<int>(m_dimensions.GetWidth())))
  {
    return;
  }

  std::vector<Pixel> tempColors = colors;
  auto plot = [this, &colors, &tempColors](const int32_t x, const int32_t y, const float brightness)
  {
    // TODO(glk) Don't repeat this?
    if ((static_cast<uint32_t>(x) >= m_dimensions.GetWidth()) ||
        (static_cast<uint32_t>(y) >= m_dimensions.GetHeight()))
    {
      return;
    }
    static constexpr float TOLERANCE = 0.001F;
    if (brightness < TOLERANCE)
    {
      return;
    }
    if (brightness >= (1.0F - TOLERANCE))
    {
      DrawPixels(x, y, colors);
    }
    else
    {
      for (size_t i = 0; i < colors.size(); ++i)
      {
        tempColors[i] = GetBrighterColor(brightness, colors[i]);
      }
      DrawPixels(x, y, tempColors);
    }
  };

  WuLine(static_cast<float>(x1),
         static_cast<float>(y1),
         static_cast<float>(x2),
         static_cast<float>(y2),
         plot);
}

// The Xiaolin Wu anti-aliased draw line.
// From https://rosettacode.org/wiki/Xiaolin_Wu%27s_line_algorithm#C.2B.2B
//
auto DrawMethods::WuLine(float x0, float y0, float x1, float y1, const PlotPointFunc& plot) noexcept
    -> void
{
  const auto iPart  = [](const float x) { return static_cast<int>(std::floor(x)); };
  const auto fRound = [](const float x) { return std::round(x); };
  const auto fPart  = [](const float x) { return x - std::floor(x); };
  const auto rFPart = [=](const float x) { return 1 - fPart(x); };

  const bool steep = std::abs(y1 - y0) > std::abs(x1 - x0);
  if (steep)
  {
    std::swap(x0, y0);
    std::swap(x1, y1);
  }
  if (x0 > x1)
  {
    std::swap(x0, x1);
    std::swap(y0, y1);
  }

  const float dx       = x1 - x0; // because of above swap, must be >= 0
  const float dy       = y1 - y0;
  const float gradient = (dx < 0.001F) ? 1 : (dy / dx);

  int32_t xpx11;
  float interY;
  {
    const float xEnd = fRound(x0);
    const float yEnd = y0 + (gradient * (xEnd - x0));
    const float xGap = rFPart(x0 + 0.5F);
    xpx11            = static_cast<int>(xEnd);
    const int32_t ypx11 = iPart(yEnd);
    if (steep)
    {
      plot(ypx11, xpx11, rFPart(yEnd) * xGap);
      plot(ypx11 + 1, xpx11, fPart(yEnd) * xGap);
    }
    else
    {
      plot(xpx11, ypx11, rFPart(yEnd) * xGap);
      plot(xpx11, ypx11 + 1, fPart(yEnd) * xGap);
    }
    interY = yEnd + gradient;
  }

  int32_t xpx12;
  {
    const float xEnd = fRound(x1);
    const float yEnd = y1 + (gradient * (xEnd - x1));
    const float xGap = rFPart(x1 + 0.5F);
    xpx12            = static_cast<int>(xEnd);
    const int32_t ypx12 = iPart(yEnd);
    if (steep)
    {
      plot(ypx12, xpx12, rFPart(yEnd) * xGap);
      plot(ypx12 + 1, xpx12, fPart(yEnd) * xGap);
    }
    else
    {
      plot(xpx12, ypx12, rFPart(yEnd) * xGap);
      plot(xpx12, ypx12 + 1, fPart(yEnd) * xGap);
    }
  }

  if (steep)
  {
    for (int32_t x = xpx11 + 1; x < xpx12; ++x)
    {
      plot(iPart(interY), x, rFPart(interY));
      plot(iPart(interY) + 1, x, fPart(interY));
      interY += gradient;
    }
  }
  else
  {
    for (int32_t x = xpx11 + 1; x < xpx12; ++x)
    {
      plot(x, iPart(interY), rFPart(interY));
      plot(x, iPart(interY) + 1, fPart(interY));
      interY += gradient;
    }
  }
}

auto DrawMethods::DrawThickLine(const int32_t x1,
                                const int32_t y1,
                                const int32_t x2,
                                const int32_t y2,
                                const std::vector<Pixel>& colors,
                                const uint8_t thickness) noexcept -> void
{
  Expects(thickness > 1);

  if ((y1 < 0) || (y2 < 0) || (x1 < 0) || (x2 < 0) ||
      (y1 >= static_cast<int>(m_dimensions.GetHeight())) ||
      (y2 >= static_cast<int>(m_dimensions.GetHeight())) ||
      (x1 >= static_cast<int>(m_dimensions.GetWidth())) ||
      (x2 >= static_cast<int>(m_dimensions.GetWidth())))
  {
    return;
  }

  const float brightness = (0.8F * 2.0F) / static_cast<float>(thickness);

  std::vector<Pixel> tempColors = colors;
  const auto plot = [this, &colors, &tempColors, &brightness](const int32_t x, const int32_t y)
  {
    // TODO(glk) Don't repeat this?
    if ((static_cast<uint32_t>(x) >= m_dimensions.GetWidth()) ||
        (static_cast<uint32_t>(y) >= m_dimensions.GetHeight()))
    {
      return;
    }
    static constexpr float TOLERANCE = 0.001F;
    if (brightness >= (1.0F - TOLERANCE))
    {
      DrawPixels(x, y, colors);
    }
    else
    {
      for (size_t i = 0; i < colors.size(); ++i)
      {
        tempColors[i] = GetBrighterColor(brightness, colors[i]);
      }
      DrawPixels(x, y, tempColors);
    }
  };

  auto getWidth = [&thickness]([[maybe_unused]] const int32_t pointNum,
                               [[maybe_unused]] const int32_t lineLength)
  { return static_cast<double>(thickness); };

  DrawVariableThicknessLine(plot, x1, y1, x2, y2, getWidth, getWidth);
}

} // namespace GOOM::DRAW

// NOLINTEND
