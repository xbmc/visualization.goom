#define _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING

#include "text_draw.h"

//#define NO_FREETYPE_INSTALLED
//#undef NO_LOGGING

#include "color/color_utils.h"
#include "goom_config.h"
#include "goom_draw.h"
#include "goom_graphic.h"
#include "logging.h"
#include "spimpl.h"
#include "utils/math/misc.h"

#include <codecvt>
#include <format>
#include <fstream>
#include <locale>

#ifndef NO_FREETYPE_INSTALLED
#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_STROKER_H
#endif

namespace GOOM::DRAW
{

using COLOR::GetColorBlend;
using UTILS::Logging; // NOLINT(misc-unused-using-decls)
using UTILS::MATH::I_HALF;

#ifdef NO_FREETYPE_INSTALLED
class TextDraw::TextDrawImpl
{
public:
  explicit TextDrawImpl(IGoomDraw& draw) noexcept;
  TextDrawImpl(const TextDrawImpl&) noexcept = delete;
  TextDrawImpl(TextDrawImpl&&) noexcept      = delete;
  ~TextDrawImpl() noexcept;
  auto operator=(const TextDrawImpl&) -> TextDrawImpl& = delete;
  auto operator=(TextDrawImpl&&) -> TextDrawImpl&      = delete;

  [[nodiscard]] auto GetAlignment() const noexcept -> TextAlignment;
  auto SetAlignment(TextAlignment alignment) noexcept -> void;
  [[nodiscard]] auto GetFontFile() const noexcept -> const std::string&;
  auto SetFontFile(const std::string& filename) noexcept -> void;
  [[nodiscard]] auto GetFontSize() const noexcept -> int32_t;
  auto SetFontSize(int32_t val) noexcept -> void;
  [[nodiscard]] auto GetLineSpacing() const noexcept -> int32_t;
  auto SetOutlineWidth(float val) noexcept -> void;
  [[nodiscard]] auto GetCharSpacing() const noexcept -> float;
  auto SetCharSpacing(float val) noexcept -> void;

  auto SetFontColorFunc(const FontColorFunc& func) noexcept -> void;
  auto SetOutlineFontColorFunc(const FontColorFunc& func) noexcept -> void;

  auto SetParallelRender(bool val) noexcept -> void;

  auto SetText(const std::string& str) noexcept -> void;

  auto Prepare() noexcept -> void;
  [[nodiscard]] auto GetPreparedTextBoundingRect() const noexcept -> Rect;
  [[nodiscard]] auto GetBearingX() const noexcept -> int;
  [[nodiscard]] auto GetBearingY() const noexcept -> int;

  auto Draw(Point2dInt pen) noexcept -> void;
  auto Draw(Point2dInt pen, Point2dInt& nextPen) noexcept -> void;

private:
  std::string m_fontFilename{};
};

TextDraw::TextDrawImpl::TextDrawImpl(IGoomDraw&) noexcept
{
}

TextDraw::TextDrawImpl::~TextDrawImpl() noexcept
{
}

auto TextDraw::TextDrawImpl::GetAlignment() const noexcept -> TextAlignment
{
  return TextAlignment::LEFT;
}

auto TextDraw::TextDrawImpl::SetAlignment(const TextAlignment) noexcept -> void
{
}

auto TextDraw::TextDrawImpl::GetFontFile() const noexcept -> const std::string&
{
  return m_fontFilename;
}

auto TextDraw::TextDrawImpl::SetFontFile(const std::string& filename) noexcept -> void
{
  m_fontFilename = filename;
}

auto TextDraw::TextDrawImpl::GetFontSize() const noexcept -> int32_t
{
  return 0;
}

auto TextDraw::TextDrawImpl::SetFontSize(const int32_t) noexcept -> void
{
}

auto TextDraw::TextDrawImpl::GetLineSpacing() const noexcept -> int32_t
{
  return 0;
}

auto TextDraw::TextDrawImpl::SetOutlineWidth(const float) noexcept -> void
{
}

inline auto TextDraw::TextDrawImpl::GetCharSpacing() const noexcept -> float
{
  return 0.0F;
}

auto TextDraw::TextDrawImpl::SetCharSpacing(const float) noexcept -> void
{
}

auto TextDraw::TextDrawImpl::SetParallelRender(const bool) noexcept -> void
{
}

auto TextDraw::TextDrawImpl::SetText(const std::string&) noexcept -> void
{
}

auto TextDraw::TextDrawImpl::SetFontColorFunc(const FontColorFunc&) noexcept -> void
{
}

auto TextDraw::TextDrawImpl::SetOutlineFontColorFunc(const FontColorFunc&) noexcept -> void
{
}

auto TextDraw::TextDrawImpl::Prepare() noexcept -> void
{
}

inline auto TextDraw::TextDrawImpl::Draw(const Point2dInt) noexcept -> void
{
}

auto TextDraw::TextDrawImpl::Draw(const Point2dInt, Point2dInt&) noexcept -> void
{
}

inline auto TextDraw::TextDrawImpl::GetPreparedTextBoundingRect() const noexcept -> TextDraw::Rect
{
  return Rect{};
}

inline auto TextDraw::TextDrawImpl::GetBearingX() const noexcept -> int32_t
{
  return 1;
}

inline auto TextDraw::TextDrawImpl::GetBearingY() const noexcept -> int32_t
{
  return 1;
}
#endif

#ifndef NO_FREETYPE_INSTALLED
static constexpr auto FREE_TYPE_UNITS_PER_PIXEL = 64;

class TextDraw::TextDrawImpl
{
public:
  explicit TextDrawImpl(IGoomDraw& draw) noexcept;
  TextDrawImpl(const TextDrawImpl&) noexcept = delete;
  TextDrawImpl(TextDrawImpl&&) noexcept      = delete;
  ~TextDrawImpl() noexcept;
  auto operator=(const TextDrawImpl&) -> TextDrawImpl& = delete;
  auto operator=(TextDrawImpl&&) -> TextDrawImpl&      = delete;

  [[nodiscard]] auto GetAlignment() const noexcept -> TextAlignment;
  auto SetAlignment(TextAlignment alignment) noexcept -> void;
  [[nodiscard]] auto GetFontFile() const noexcept -> const std::string&;
  auto SetFontFile(const std::string& filename) -> void;
  [[nodiscard]] auto GetFontSize() const noexcept -> int32_t;
  auto SetFontSize(int32_t val) -> void;
  [[nodiscard]] auto GetLineSpacing() const noexcept -> int32_t;
  auto SetOutlineWidth(float val) noexcept -> void;
  [[nodiscard]] auto GetCharSpacing() const noexcept -> float;
  auto SetCharSpacing(float val) noexcept -> void;

  auto SetFontColorFunc(const FontColorFunc& func) noexcept -> void;
  auto SetOutlineFontColorFunc(const FontColorFunc& func) noexcept -> void;

  auto SetParallelRender(bool val) noexcept -> void;

  auto SetText(const std::string& str) noexcept -> void;

  auto Prepare() -> void;
  [[nodiscard]] auto GetPreparedTextBoundingRect() const noexcept -> Rect;
  [[nodiscard]] auto GetBearingX() const noexcept -> int;
  [[nodiscard]] auto GetBearingY() const noexcept -> int;

  auto Draw(Point2dInt pen) -> void;
  auto Draw(Point2dInt pen, Point2dInt& nextPen) -> void;

private:
  IGoomDraw& m_draw;
  FT_Library m_library{};
  static constexpr int32_t DEFAULT_FONT_SIZE       = 100;
  int32_t m_fontSize                               = DEFAULT_FONT_SIZE;
  static constexpr uint32_t DEFAULT_HORIZONTAL_RES = 90;
  uint32_t m_horizontalResolution                  = DEFAULT_HORIZONTAL_RES;
  static constexpr uint32_t DEFAULT_VERTICAL_RES   = 90;
  uint32_t m_verticalResolution                    = DEFAULT_VERTICAL_RES;
  static constexpr float DEFAULT_OUTLINE_WIDTH     = 3.0F;
  float m_outlineWidth                             = DEFAULT_OUTLINE_WIDTH;
  float m_charSpacing                              = 0.0F;
  std::string m_fontFilename{};
  std::vector<unsigned char> m_fontBuffer{};
  bool m_useParallelRender = true;
  std::string m_theText{};
  TextAlignment m_textAlignment{TextAlignment::LEFT};
  FT_Face m_face{};
  auto SetFaceFontSize() -> void;

  FontColorFunc m_getFontColor{};
  FontColorFunc m_getOutlineFontColor{};

  [[nodiscard]] static constexpr auto ToStdPixelCoord(int32_t freeTypeCoord) noexcept -> int;
  [[nodiscard]] static constexpr auto ToFreeTypeCoord(int32_t stdPixelCoord) noexcept -> int;
  [[nodiscard]] static auto ToFreeTypeCoord(float stdPixelCoord) noexcept -> int;
  struct Vec2;
  struct Span;
  using SpanArray = std::vector<Span>;

  struct RectImpl : public Rect
  {
    RectImpl() noexcept = default;
    RectImpl(int32_t left, int32_t top, int32_t right, int32_t bottom) noexcept;
    RectImpl(const RectImpl&) noexcept                   = default;
    RectImpl(RectImpl&&) noexcept                        = default;
    ~RectImpl() noexcept                                 = default;
    auto operator=(const RectImpl&) noexcept -> RectImpl = delete;
    auto operator=(RectImpl&&) noexcept -> RectImpl      = delete;

    auto Include(const Vec2& span) noexcept -> void;
  };

  // NOLINTBEGIN: Stop gcc-12 'inline' warning
  struct Spans
  {
    ~Spans() noexcept;
    SpanArray stdSpans{};
    SpanArray outlineSpans{};
    size_t textIndexOfChar{};
    RectImpl rect{};
    int32_t advance{};
    int32_t bearingX{};
    int32_t bearingY{};
  };
  // NOLINTEND

  std::vector<Spans> m_textSpans{};
  Rect m_textBoundingRect{};
  [[nodiscard]] static auto GetBoundingRect(const SpanArray& stdSpans,
                                            const SpanArray& outlineSpans) noexcept -> RectImpl;
  [[nodiscard]] auto GetSpans(size_t textIndexOfChar) const -> Spans;
  [[nodiscard]] auto GetStdSpans() const noexcept -> SpanArray;
  [[nodiscard]] auto GetOutlineSpans() const -> SpanArray;
  auto RenderSpans(FT_Outline* outline, SpanArray* spans) const noexcept -> void;
  static auto RasterCallback(int32_t y, int32_t count, const FT_Span* spans, void* user) noexcept
      -> void;

  [[nodiscard]] auto GetStartXPen(int32_t xPen) const -> int;
  [[nodiscard]] static auto GetStartYPen(int32_t yPen) noexcept -> int;
  auto WriteGlyph(const Spans& spans, int32_t xPen, int32_t yPen) noexcept -> void;
  auto WriteSpansToImage(const SpanArray& spanArray,
                         const RectImpl& rect,
                         int32_t xPen,
                         int32_t yPen,
                         size_t textIndexOfChar,
                         const FontColorFunc& getColor) noexcept -> void;
  auto WriteXSpan(const Span& span,
                  const RectImpl& rect,
                  int32_t xPen,
                  int32_t yPos,
                  size_t textIndexOfChar,
                  const FontColorFunc& getColor) noexcept -> void;
};
#endif

TextDraw::TextDraw(IGoomDraw& draw) noexcept : m_pimpl{spimpl::make_unique_impl<TextDrawImpl>(draw)}
{
}

auto TextDraw::GetAlignment() const noexcept -> TextAlignment
{
  return m_pimpl->GetAlignment();
}

auto TextDraw::SetAlignment(const TextAlignment alignment) noexcept -> void
{
  m_pimpl->SetAlignment(alignment);
}

auto TextDraw::GetFontFile() const noexcept -> const std::string&
{
  return m_pimpl->GetFontFile();
}

auto TextDraw::SetFontFile(const std::string& filename) -> void
{
  m_pimpl->SetFontFile(filename);
}

auto TextDraw::GetFontSize() const noexcept -> int32_t
{
  return m_pimpl->GetFontSize();
}

auto TextDraw::SetFontSize(const int32_t val) -> void
{
  m_pimpl->SetFontSize(val);
}

auto TextDraw::GetLineSpacing() const noexcept -> int32_t
{
  return m_pimpl->GetLineSpacing();
}

auto TextDraw::SetOutlineWidth(const float val) noexcept -> void
{
  m_pimpl->SetOutlineWidth(val);
}

auto TextDraw::GetCharSpacing() const noexcept -> float
{
  return m_pimpl->GetCharSpacing();
}

auto TextDraw::SetCharSpacing(const float val) noexcept -> void
{
  m_pimpl->SetCharSpacing(val);
}

auto TextDraw::SetParallelRender(const bool val) noexcept -> void
{
  m_pimpl->SetParallelRender(val);
}

auto TextDraw::SetText(const std::string& str) noexcept -> void
{
  m_pimpl->SetText(str);
}

auto TextDraw::SetFontColorFunc(const FontColorFunc& func) noexcept -> void
{
  m_pimpl->SetFontColorFunc(func);
}

auto TextDraw::SetOutlineFontColorFunc(const FontColorFunc& func) noexcept -> void
{
  m_pimpl->SetOutlineFontColorFunc(func);
}

auto TextDraw::Prepare() -> void
{
  m_pimpl->Prepare();
}

auto TextDraw::GetPreparedTextBoundingRect() const noexcept -> TextDraw::Rect
{
  return m_pimpl->GetPreparedTextBoundingRect();
}

auto TextDraw::GetBearingX() const noexcept -> int32_t
{
  return m_pimpl->GetBearingX();
}

auto TextDraw::GetBearingY() const noexcept -> int32_t
{
  return m_pimpl->GetBearingY();
}

auto TextDraw::Draw(const Point2dInt pen) -> void
{
  m_pimpl->Draw(pen);
}

auto TextDraw::Draw(const Point2dInt pen, Point2dInt& nextPen) -> void
{
  m_pimpl->Draw(pen, nextPen);
}

#ifndef NO_FREETYPE_INSTALLED
TextDraw::TextDrawImpl::TextDrawImpl(IGoomDraw& draw) noexcept : m_draw{draw}
{
  ::FT_Init_FreeType(&m_library);
}

TextDraw::TextDrawImpl::~TextDrawImpl() noexcept
{
  ::FT_Done_FreeType(m_library);
}

TextDraw::TextDrawImpl::Spans::~Spans() noexcept = default;

inline auto TextDraw::TextDrawImpl::GetAlignment() const noexcept -> TextAlignment
{
  return m_textAlignment;
}

inline auto TextDraw::TextDrawImpl::SetAlignment(const TextAlignment alignment) noexcept -> void
{
  m_textAlignment = alignment;
}

inline auto TextDraw::TextDrawImpl::GetFontFile() const noexcept -> const std::string&
{
  return m_fontFilename;
}

auto TextDraw::TextDrawImpl::SetFontFile(const std::string& filename) -> void
{
  m_fontFilename = filename;
  LogInfo("Setting font file '{}'.", m_fontFilename); // NOLINT

  auto fontFile = std::ifstream{m_fontFilename, std::ios::binary};
  if (!fontFile)
  {
    throw std::runtime_error(std20::format("Could not open font file \"{}\".", m_fontFilename));
  }

  fontFile.seekg(0, std::ios::end);
  const auto fontFileSize = fontFile.tellg();
  fontFile.seekg(0);
  m_fontBuffer.resize(static_cast<size_t>(fontFileSize));
  fontFile.read(reinterpret_cast<char*>(m_fontBuffer.data()), fontFileSize);

  // Create a face from a memory buffer.  Be sure not to delete the memory buffer
  // until we are done using that font as FreeType will reference it directly.
  ::FT_New_Memory_Face(
      m_library, m_fontBuffer.data(), static_cast<FT_Long>(m_fontBuffer.size()), 0, &m_face);

  SetFaceFontSize();
}

inline auto TextDraw::TextDrawImpl::SetFaceFontSize() -> void
{
  if (::FT_Set_Char_Size(m_face,
                         ToFreeTypeCoord(m_fontSize),
                         ToFreeTypeCoord(m_fontSize),
                         m_horizontalResolution,
                         m_verticalResolution) != 0)
  {
    throw std::logic_error(std20::format("Could not set face font size to {}.", m_fontSize));
  }
}

inline auto TextDraw::TextDrawImpl::GetFontSize() const noexcept -> int32_t
{
  return m_fontSize;
}

inline auto TextDraw::TextDrawImpl::SetFontSize(const int32_t val) -> void
{
  Expects(val > 0);

  m_fontSize = val;
  LogInfo("Setting font size {}.", m_fontSize); // NOLINT
  if (m_face != nullptr)
  {
    SetFaceFontSize();
  }
}

inline auto TextDraw::TextDrawImpl::GetLineSpacing() const noexcept -> int32_t
{
  return m_face->height / static_cast<FT_Short>(FREE_TYPE_UNITS_PER_PIXEL);
}

inline auto TextDraw::TextDrawImpl::SetOutlineWidth(const float val) noexcept -> void
{
  Expects(val > 0.0F);

  m_outlineWidth = val;
}

inline auto TextDraw::TextDrawImpl::GetCharSpacing() const noexcept -> float
{
  return m_charSpacing;
}

inline auto TextDraw::TextDrawImpl::SetCharSpacing(const float val) noexcept -> void
{
  Expects(val >= 0.0F);

  m_charSpacing = val;
}

inline auto TextDraw::TextDrawImpl::SetParallelRender(const bool val) noexcept -> void
{
  m_useParallelRender = val;
}

inline auto TextDraw::TextDrawImpl::SetText(const std::string& str) noexcept -> void
{
  Expects(not str.empty());

  m_theText = str;
  LogInfo("Setting font text '{}'.", m_theText); // NOLINT
}

inline auto TextDraw::TextDrawImpl::SetFontColorFunc(const FontColorFunc& func) noexcept -> void
{
  m_getFontColor = func;
}

inline auto TextDraw::TextDrawImpl::SetOutlineFontColorFunc(const FontColorFunc& func) noexcept
    -> void
{
  m_getOutlineFontColor = func;
}

auto TextDraw::TextDrawImpl::Prepare() -> void
{
  Expects(m_face != nullptr);

  m_textSpans.resize(0);

  auto xMax = 0;
  auto yMin = std::numeric_limits<int32_t>::max();
  auto yMax = 0;

  std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> conv{};
  const std::u32string utf32Text = conv.from_bytes(m_theText);

  for (auto i = 0U; i < utf32Text.size(); ++i)
  {
    // Load the glyph we are looking for.
    if (const auto gIndex = ::FT_Get_Char_Index(m_face, static_cast<FT_ULong>(utf32Text[i]));
        ::FT_Load_Glyph(m_face, gIndex, FT_LOAD_NO_BITMAP) != 0)
    {
      throw std::runtime_error(
          std20::format("Could not load font char '{}' and glyph index {}.", m_theText[i], gIndex));
    }

    // Need an outline for this to work.
    if (m_face->glyph->format != FT_GLYPH_FORMAT_OUTLINE)
    {
      throw std::logic_error(
          std20::format("Not a correct font format: {}.", m_face->glyph->format));
    }

    const auto spans = GetSpans(i);
    m_textSpans.emplace_back(spans);

    xMax += spans.advance;
    yMin = std::min(yMin, spans.rect.yMin);
    yMax = std::max(yMax, spans.rect.yMax);
  }

  m_textBoundingRect.xMin = 0;
  m_textBoundingRect.xMax = xMax;
  m_textBoundingRect.yMin = yMin;
  m_textBoundingRect.yMax = yMax;

  LogInfo("Font bounding rectangle: {}, {}, {}, {}, m_textSpans.size = {}.",
          m_textBoundingRect.xMin,
          m_textBoundingRect.xMax,
          m_textBoundingRect.yMin,
          m_textBoundingRect.yMax,
          m_textSpans.size()); // NOLINT
}

auto TextDraw::TextDrawImpl::GetStartXPen(const int32_t xPen) const -> int
{
  switch (m_textAlignment)
  {
    case TextAlignment::LEFT:
      return xPen;
    case TextAlignment::CENTER:
      return xPen -
             (I_HALF * (GetPreparedTextBoundingRect().xMax - GetPreparedTextBoundingRect().xMin));
    case TextAlignment::RIGHT:
      return xPen - (GetPreparedTextBoundingRect().xMax - GetPreparedTextBoundingRect().xMin);
    default:
      throw std::logic_error("Unknown TextAlignment value.");
  }
}

inline auto TextDraw::TextDrawImpl::GetStartYPen(const int32_t yPen) noexcept -> int
{
  return yPen;
}

inline auto TextDraw::TextDrawImpl::Draw(const Point2dInt pen) -> void
{
  auto nextPoint = Point2dInt{};
  Draw(pen, nextPoint);
}

auto TextDraw::TextDrawImpl::Draw(const Point2dInt pen, Point2dInt& nextPen) -> void
{
  Expects(not m_textSpans.empty());

  nextPen.x = GetStartXPen(pen.x);
  nextPen.y = GetStartYPen(pen.y);

  for (const auto& span : m_textSpans)
  {
    WriteGlyph(span, nextPen.x, m_draw.GetScreenDimensions().GetIntHeight() - nextPen.y);
    nextPen.x += span.advance;
  }
}

// A horizontal pixel span generated by the FreeType renderer.
struct TextDraw::TextDrawImpl::Vec2
{
  Vec2(const int32_t xVal, const int32_t yVal) noexcept : x{xVal}, y{yVal} {}
  int32_t x;
  int32_t y;
};

inline TextDraw::TextDrawImpl::RectImpl::RectImpl(const int32_t left,
                                                  const int32_t top,
                                                  const int32_t right,
                                                  const int32_t bottom) noexcept
{
  xMin = left;
  xMax = right;
  yMin = top;
  yMax = bottom;
}

inline auto TextDraw::TextDrawImpl::RectImpl::Include(const Vec2& span) noexcept -> void
{
  xMin = std::min(xMin, span.x);
  yMin = std::min(yMin, span.y);
  xMax = std::max(xMax, span.x);
  yMax = std::max(yMax, span.y);
}

struct TextDraw::TextDrawImpl::Span
{
  Span(const int32_t xVal,
       const int32_t yVal,
       const int32_t widthVal,
       const int32_t coverageVal) noexcept
    : x{xVal}, y{yVal}, width{widthVal}, coverage{coverageVal}
  {
  }

  int32_t x;
  int32_t y;
  int32_t width;
  int32_t coverage;
};

// Render the specified character as a colored glyph with a colored outline.
inline auto TextDraw::TextDrawImpl::WriteGlyph(const Spans& spans,
                                               const int32_t xPen,
                                               const int32_t yPen) noexcept -> void
{
  // Loop over the outline spans and just draw them into the image.
  WriteSpansToImage(
      spans.outlineSpans, spans.rect, xPen, yPen, spans.textIndexOfChar, m_getOutlineFontColor);

  // Then loop over the regular glyph spans and blend them into the image.
  WriteSpansToImage(spans.stdSpans, spans.rect, xPen, yPen, spans.textIndexOfChar, m_getFontColor);
}

auto TextDraw::TextDrawImpl::WriteSpansToImage(const SpanArray& spanArray,
                                               const RectImpl& rect,
                                               const int32_t xPen,
                                               const int32_t yPen,
                                               const size_t textIndexOfChar,
                                               const FontColorFunc& getColor) noexcept -> void
{
  const auto writeSpan =
      [this, &spanArray, &xPen, &yPen, &rect, &getColor, &textIndexOfChar](const size_t i)
  {
    const auto& span = spanArray.at(i);

    const auto yPos = m_draw.GetScreenDimensions().GetIntHeight() - (yPen + span.y);
    if ((yPos < 0) or (yPos >= m_draw.GetScreenDimensions().GetIntHeight()))
    {
      return;
    }

    WriteXSpan(span, rect, xPen, yPos, textIndexOfChar, getColor);
  };

  static constexpr auto MIN_PARALLEL_SPAN_ARRAY_SIZE = 20;
  if (m_useParallelRender && (spanArray.size() >= MIN_PARALLEL_SPAN_ARRAY_SIZE))
  {
    LogInfo("WriteSpansToImage using parallel."); // NOLINT
    m_draw.GetParallel().ForLoop(spanArray.size(), writeSpan);
  }
  else
  {
    LogInfo("WriteSpansToImage NOT using parallel."); // NOLINT
    for (auto i = 0U; i < spanArray.size(); ++i)
    {
      writeSpan(i);
    }
  }
}

auto TextDraw::TextDrawImpl::WriteXSpan(const Span& span,
                                        const RectImpl& rect,
                                        const int32_t xPen,
                                        const int32_t yPos,
                                        const size_t textIndexOfChar,
                                        const FontColorFunc& getColor) noexcept -> void
{
  const auto xPos0    = xPen + (span.x - rect.xMin);
  const auto xf0      = span.x - rect.xMin;
  const auto coverage = static_cast<uint8_t>(span.coverage);
  for (auto width = 0; width < span.width; ++width)
  {
    const auto xPos = xPos0 + width;
    if ((xPos < 0) or (xPos >= m_draw.GetScreenDimensions().GetIntWidth()))
    {
      continue;
    }

    const auto pen       = Point2dInt{xf0 + width, rect.Height() - (span.y - rect.yMin)};
    const auto color     = getColor(textIndexOfChar, pen, rect.Width(), rect.Height());
    const auto srceColor = Pixel{
        {/*.r = */ color.R(), /*.g = */ color.G(), /*.b = */ color.B(), /*.a = */ coverage}
    };
    const auto destColor = m_draw.GetPixel({xPos, yPos});

    m_draw.DrawPixelsUnblended({xPos, yPos}, {GetColorBlend(srceColor, destColor)});
  }
}

constexpr auto TextDraw::TextDrawImpl::ToStdPixelCoord(const int32_t freeTypeCoord) noexcept
    -> int32_t
{
  return freeTypeCoord / FREE_TYPE_UNITS_PER_PIXEL;
}

constexpr auto TextDraw::TextDrawImpl::ToFreeTypeCoord(const int32_t stdPixelCoord) noexcept
    -> int32_t
{
  return stdPixelCoord * FREE_TYPE_UNITS_PER_PIXEL;
}

inline auto TextDraw::TextDrawImpl::ToFreeTypeCoord(const float stdPixelCoord) noexcept
    -> int32_t
{
  return static_cast<int32_t>(
      std::lround(stdPixelCoord * static_cast<float>(FREE_TYPE_UNITS_PER_PIXEL)));
}

// Each time the renderer calls us back we just push another span entry on our list.
auto TextDraw::TextDrawImpl::RasterCallback(const int32_t y,
                                            const int32_t count,
                                            const FT_Span* const spans,
                                            void* const user) noexcept -> void
{
  auto* const userSpans = static_cast<SpanArray*>(user);
  for (auto i = 0; i < count; ++i)
  {
    userSpans->push_back(Span{spans[i].x, y, spans[i].len, spans[i].coverage});
  }
}

// Set up the raster parameters and render the outline.
auto TextDraw::TextDrawImpl::RenderSpans(FT_Outline* const outline,
                                         SpanArray* const spans) const noexcept -> void
{
  auto params = FT_Raster_Params{};
  ::memset(&params, 0, sizeof(params));
  params.flags      = FT_RASTER_FLAG_AA | FT_RASTER_FLAG_DIRECT;
  params.gray_spans = RasterCallback;
  params.user       = spans;

  ::FT_Outline_Render(m_library, outline, &params);
}

auto TextDraw::TextDrawImpl::GetSpans(const size_t textIndexOfChar) const -> Spans
{
  const auto stdSpans = GetStdSpans();
  const auto advance  = ToStdPixelCoord(static_cast<int32_t>(m_face->glyph->advance.x)) +
                       static_cast<int>(m_charSpacing * static_cast<float>(m_fontSize));
  const auto metrics = m_face->glyph->metrics;
  if (stdSpans.empty())
  {
    return Spans{
        /*.stdSpans = */ stdSpans,
        /*.outlineSpans = */ SpanArray{},
        /*.textIndexOfChar = */ textIndexOfChar,
        /*.rect = */ RectImpl{},
        /*.advance = */ advance,
        /*.bearingX = */ ToStdPixelCoord(static_cast<int32_t>(metrics.horiBearingX)),
        /*.bearingY = */ ToStdPixelCoord(static_cast<int32_t>(metrics.horiBearingY)),
    };
  }

  const auto outlineSpans = GetOutlineSpans();
  return Spans{
      /*.stdSpans = */ stdSpans,
      /*.outlineSpans = */ outlineSpans,
      /*.textIndexOfChar = */ textIndexOfChar,
      /*.rect = */ GetBoundingRect(stdSpans, outlineSpans),
      /*.advance = */ advance,
      /*.bearingX = */ ToStdPixelCoord(static_cast<int32_t>(metrics.horiBearingX)),
      /*.bearingY = */ ToStdPixelCoord(static_cast<int32_t>(metrics.horiBearingY)),
  };
}

inline auto TextDraw::TextDrawImpl::GetStdSpans() const noexcept -> SpanArray
{
  auto spans = SpanArray{};

  RenderSpans(&m_face->glyph->outline, &spans);

  return spans;
}

auto TextDraw::TextDrawImpl::GetOutlineSpans() const -> SpanArray
{
  // Set up a stroker.
  FT_Stroker stroker{};
  ::FT_Stroker_New(m_library, &stroker);
  ::FT_Stroker_Set(stroker,
                   ToFreeTypeCoord(m_outlineWidth),
                   FT_STROKER_LINECAP_ROUND,
                   FT_STROKER_LINEJOIN_ROUND,
                   0);

  auto* glyph = FT_Glyph{};
  if (::FT_Get_Glyph(m_face->glyph, &glyph) != 0)
  {
    throw std::runtime_error("Could not get glyph for outline spans.");
  }

  // Next we need the spans for the outline.
  ::FT_Glyph_StrokeBorder(&glyph, stroker, 0, 1);

  // Again, this needs to be an outline to work.
  if (glyph->format != FT_GLYPH_FORMAT_OUTLINE)
  {
    throw std::runtime_error("Glyph does not have outline format.");
  }

  // Render the outline spans to the span list
  auto* const outline = &reinterpret_cast<FT_OutlineGlyph>(glyph)->outline;
  auto outlineSpans   = SpanArray{};
  RenderSpans(outline, &outlineSpans);
  if (outlineSpans.empty())
  {
    throw std::logic_error("Rendered outline spans are empty.");
  }

  // Clean up afterwards.
  ::FT_Stroker_Done(stroker);
  ::FT_Done_Glyph(glyph);

  return outlineSpans;
}

inline auto TextDraw::TextDrawImpl::GetPreparedTextBoundingRect() const noexcept -> TextDraw::Rect
{
  return m_textBoundingRect;
}

inline auto TextDraw::TextDrawImpl::GetBearingX() const noexcept -> int32_t
{
  return m_textSpans.front().bearingX;
}

inline auto TextDraw::TextDrawImpl::GetBearingY() const noexcept -> int32_t
{
  return m_textSpans.front().bearingY;
}

auto TextDraw::TextDrawImpl::GetBoundingRect(const SpanArray& stdSpans,
                                             const SpanArray& outlineSpans) noexcept -> RectImpl
{
  auto rect =
      RectImpl{stdSpans.front().x, stdSpans.front().y, stdSpans.front().x, stdSpans.front().y};

  for (const auto& span : stdSpans)
  {
    rect.Include(Vec2{span.x, span.y});
    rect.Include(Vec2{span.x + (span.width - 1), span.y});
  }
  for (const auto& span : outlineSpans)
  {
    rect.Include(Vec2{span.x, span.y});
    rect.Include(Vec2{span.x + (span.width - 1), span.y});
  }

  return rect;
}
#endif

} // namespace GOOM::DRAW
