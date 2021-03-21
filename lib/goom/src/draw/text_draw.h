#ifndef VISUALIZATION_GOOM_TEXT_DRAW_H
#define VISUALIZATION_GOOM_TEXT_DRAW_H

#include <cstdint>
#include <functional>
#include <memory>
#include <string>

#if __cplusplus <= 201402L
namespace GOOM
{

class IGoomDraw;
class Pixel;

namespace DRAW
{
#else
namespace GOOM::DRAW
{
#endif

class TextDraw
{
public:
  explicit TextDraw(const IGoomDraw* draw) noexcept;
  TextDraw(const TextDraw&) noexcept = delete;
  TextDraw(TextDraw&&) noexcept = delete;
  ~TextDraw() noexcept;
  auto operator=(const TextDraw&) noexcept -> TextDraw& = delete;
  auto operator=(TextDraw&&) noexcept -> TextDraw& = delete;

  enum class TextAlignment
  {
    LEFT,
    CENTER,
    RIGHT
  };
  void SetAlignment(TextAlignment a);

  void SetFontSize(int32_t val);
  void SetOutlineWidth(float val);
  void SetCharSpacing(float val);
  [[nodiscard]] auto GetFontFile() const -> const std::string&;
  void SetFontFile(const std::string& filename);
  void SetText(const std::string& str);

  using FontColorFunc = std::function<Pixel(
      size_t textIndexOfChar, int32_t x, int32_t y, int32_t width, int32_t height)>;
  void SetFontColorFunc(const FontColorFunc& f);
  void SetOutlineFontColorFunc(const FontColorFunc& f);

  void Prepare();

  struct Rect
  {
    int32_t xmin{};
    int32_t xmax{};
    int32_t ymin{};
    int32_t ymax{};
    [[nodiscard]] auto Width() const -> int32_t { return xmax - xmin + 1; }
    [[nodiscard]] auto Height() const -> int32_t { return ymax - ymin + 1; }
  };
  [[nodiscard]] auto GetPreparedTextBoundingRect() const -> Rect;
  [[nodiscard]] auto GetBearingX() const -> int;
  [[nodiscard]] auto GetBearingY() const -> int;

  void Draw(int32_t xPen, int32_t yPen);
  void Draw(int32_t xPen, int32_t yPen, int32_t& xNext, int32_t& yNext);

private:
  class TextDrawImpl;
  std::unique_ptr<TextDrawImpl> m_textDrawImpl;
};

#if __cplusplus <= 201402L
} // namespace DRAW
} // namespace GOOM
#else
} // namespace GOOM::DRAW
#endif

#endif
