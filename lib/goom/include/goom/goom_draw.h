#ifndef VISUALIZATION_GOOM_GOOM_DRAW_H
#define VISUALIZATION_GOOM_GOOM_DRAW_H

#include "draw_methods.h"
#include "goom_config.h"
#include "goom_graphic.h"
#include "goomutils/parallel_utils.h"

#include <cstddef>
#include <cstdint>
#include <vector>

namespace GOOM
{

class IGoomDraw
{
public:
  IGoomDraw() noexcept = delete;
  IGoomDraw(uint32_t screenWidth,
            uint32_t screenHeight,
            const DrawMethods::DrawPixelFunc& drawPixelFunc);
  IGoomDraw(const IGoomDraw&) noexcept = delete;
  IGoomDraw(IGoomDraw&&) noexcept = delete;
  virtual ~IGoomDraw() noexcept;
  auto operator=(const IGoomDraw&) -> IGoomDraw& = delete;
  auto operator=(IGoomDraw&&) -> IGoomDraw& = delete;

  [[nodiscard]] auto GetScreenWidth() const -> uint32_t;
  [[nodiscard]] auto GetScreenHeight() const -> uint32_t;

  [[nodiscard]] auto GetAllowOverexposed() const -> bool;
  void SetAllowOverexposed(bool val);

  [[nodiscard]] auto GetBuffIntensity() const -> float;
  void SetBuffIntensity(float val);

  void Circle(int x0, int y0, int radius, const Pixel& color) const;
  void Circle(int x0, int y0, int radius, const std::vector<Pixel>& colors) const;

  void Line(int x1, int y1, int x2, int y2, const Pixel& color, uint8_t thickness) const;
  void Line(
      int x1, int y1, int x2, int y2, const std::vector<Pixel>& colors, uint8_t thickness) const;

  using GetBitmapColorFunc = std::function<auto(size_t x, size_t y, const Pixel& b)->Pixel>;
  void Bitmap(int xCentre,
              int yCentre,
              const PixelBuffer& bitmap,
              const GetBitmapColorFunc& getColor) const;
  void Bitmap(int xCentre,
              int yCentre,
              const PixelBuffer& bitmap,
              const GetBitmapColorFunc& getColor,
              bool allowOverexposed) const;
  void Bitmap(int xCentre,
              int yCentre,
              const PixelBuffer& bitmap,
              const std::vector<GetBitmapColorFunc>& getColors) const;
  void Bitmap(int xCentre,
              int yCentre,
              const PixelBuffer& bitmap,
              const std::vector<GetBitmapColorFunc>& getColors,
              bool allowOverexposed) const;

  [[nodiscard]] virtual auto GetPixel(int32_t x, int32_t y) const -> Pixel = 0;
  void DrawPixels(int32_t x, int32_t y, const std::vector<Pixel>& colors) const;
  void DrawPixels(int32_t x,
                  int32_t y,
                  const std::vector<Pixel>& colors,
                  bool allowOverexposed) const;
  virtual void DrawPixelsUnblended(int32_t x,
                                   int32_t y,
                                   const std::vector<Pixel>& colors) const = 0;

protected:
  [[nodiscard]] auto GetIntBuffIntensity() const -> uint32_t;
  [[nodiscard]] auto GetParallel() const -> GOOM::UTILS::Parallel&;

private:
  const uint32_t m_screenWidth;
  const uint32_t m_screenHeight;
  DrawMethods m_drawMethods;
  bool m_allowOverexposed = true;
  float m_buffIntensity = 0.5;
  uint32_t m_intBuffIntensity;
  mutable GOOM::UTILS::Parallel m_parallel;
};

inline auto IGoomDraw::GetScreenWidth() const -> uint32_t
{
  return m_screenWidth;
}

inline auto IGoomDraw::GetScreenHeight() const -> uint32_t
{
  return m_screenHeight;
}

inline auto IGoomDraw::GetAllowOverexposed() const -> bool
{
  return m_allowOverexposed;
}

inline void IGoomDraw::SetAllowOverexposed(const bool val)
{
  m_allowOverexposed = val;
  m_drawMethods.SetAllowOverexposed(val);
}

inline auto IGoomDraw::GetBuffIntensity() const -> float
{
  return m_buffIntensity;
}

inline void IGoomDraw::SetBuffIntensity(const float val)
{
  m_buffIntensity = val;
  m_intBuffIntensity = static_cast<uint32_t>(channel_limits<float>::max() * m_buffIntensity);
}

inline auto IGoomDraw::GetIntBuffIntensity() const -> uint32_t
{
  return m_intBuffIntensity;
}

inline auto IGoomDraw::GetParallel() const -> GOOM::UTILS::Parallel&
{
  return m_parallel;
}

inline void IGoomDraw::Circle(const int x0,
                              const int y0,
                              const int radius,
                              const Pixel& color) const
{
  Circle(x0, y0, radius, std::vector<Pixel>{color});
}

inline void IGoomDraw::Circle(const int x0,
                              const int y0,
                              const int radius,
                              const std::vector<Pixel>& colors) const
{
  m_drawMethods.DrawCircle(x0, y0, radius, colors);
}

inline void IGoomDraw::Line(const int x1,
                            const int y1,
                            const int x2,
                            const int y2,
                            const Pixel& color,
                            const uint8_t thickness) const
{
  Line(x1, y1, x2, y2, std::vector<Pixel>{color}, thickness);
}

inline void IGoomDraw::Line(const int x1,
                            const int y1,
                            const int x2,
                            const int y2,
                            const std::vector<Pixel>& colors,
                            const uint8_t thickness) const
{
  m_drawMethods.DrawLine(x1, y1, x2, y2, colors, thickness);
}

inline void IGoomDraw::Bitmap(const int xCentre,
                              const int yCentre,
                              const PixelBuffer& bitmap,
                              const GetBitmapColorFunc& getColor) const
{
  Bitmap(xCentre, yCentre, bitmap, getColor, GetAllowOverexposed());
}

inline void IGoomDraw::Bitmap(const int xCentre,
                              const int yCentre,
                              const PixelBuffer& bitmap,
                              const GetBitmapColorFunc& getColor,
                              const bool allowOverexposed) const
{
  Bitmap(xCentre, yCentre, bitmap, std::vector<GetBitmapColorFunc>{getColor}, allowOverexposed);
}

inline void IGoomDraw::Bitmap(const int xCentre,
                              const int yCentre,
                              const PixelBuffer& bitmap,
                              const std::vector<GetBitmapColorFunc>& getColors) const
{
  Bitmap(xCentre, yCentre, bitmap, getColors, GetAllowOverexposed());
}

inline void IGoomDraw::DrawPixels(const int32_t x,
                                  const int32_t y,
                                  const std::vector<Pixel>& colors) const
{
  DrawPixels(x, y, colors, GetAllowOverexposed());
}

inline void IGoomDraw::DrawPixels(const int32_t x,
                                  const int32_t y,
                                  const std::vector<Pixel>& colors,
                                  const bool allowOverexposed) const
{
  m_drawMethods.DrawPixels(x, y, colors, allowOverexposed);
}

} // namespace GOOM

#endif /* VISUALIZATION_GOOM_GOOM_DRAW_H */
