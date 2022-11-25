#pragma once

#include "point2d.h"
#include "spimpl.h"

#include <cstdint>
#include <functional>
#include <memory>

namespace GOOM
{

class Pixel;

namespace DRAW
{

class IGoomDraw;

class TextDraw
{
public:
  explicit TextDraw(IGoomDraw& draw) noexcept;

  enum class TextAlignment
  {
    LEFT,
    CENTER,
    RIGHT
  };
  [[nodiscard]] auto GetAlignment() const noexcept -> TextAlignment;
  auto SetAlignment(TextAlignment alignment) noexcept -> void;

  [[nodiscard]] auto GetFontSize() const noexcept -> int32_t;
  auto SetFontSize(int32_t val) -> void;
  [[nodiscard]] auto GetLineSpacing() const noexcept -> int32_t;
  auto SetOutlineWidth(float val) noexcept -> void;
  [[nodiscard]] auto GetCharSpacing() const noexcept -> float;
  auto SetCharSpacing(float val) noexcept -> void;
  [[nodiscard]] auto GetFontFile() const noexcept -> const std::string&;
  auto SetFontFile(const std::string& filename) -> void;

  using FontColorFunc =
      std::function<Pixel(size_t textIndexOfChar, Point2dInt pen, int32_t width, int32_t height)>;
  auto SetFontColorFunc(const FontColorFunc& func) noexcept -> void;
  auto SetOutlineFontColorFunc(const FontColorFunc& func) noexcept -> void;

  auto SetParallelRender(bool val) noexcept -> void;

  auto SetText(const std::string& str) noexcept -> void;
  auto Prepare() -> void;

  struct Rect
  {
    int32_t xMin{};
    int32_t xMax{};
    int32_t yMin{};
    int32_t yMax{};
    [[nodiscard]] auto Width() const noexcept -> int32_t { return (xMax - xMin) + 1; }
    [[nodiscard]] auto Height() const noexcept -> int32_t { return (yMax - yMin) + 1; }
  };
  [[nodiscard]] auto GetPreparedTextBoundingRect() const noexcept -> Rect;
  [[nodiscard]] auto GetBearingX() const noexcept -> int;
  [[nodiscard]] auto GetBearingY() const noexcept -> int;

  auto Draw(Point2dInt pen) -> void;
  auto Draw(Point2dInt pen, Point2dInt& nextPen) -> void;

private:
  class TextDrawImpl;
  spimpl::unique_impl_ptr<TextDrawImpl> m_pimpl;
};

} // namespace DRAW
} // namespace GOOM
