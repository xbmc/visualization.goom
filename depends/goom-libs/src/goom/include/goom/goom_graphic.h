#pragma once

#include "goom_config.h"
#include "goom_types.h"

#include <array>
#include <cstdint>
#include <limits>
#include <string>
#include <tuple>
#include <vector>

namespace GOOM
{

struct GoomShaderEffects
{
  float exposure                = 0.0F;
  float brightness              = 0.0F;
  float contrast                = 0.0F;
  float contrastMinChannelValue = 0.0F; // negative gives interesting effects
  float hueShiftLerpT           = 0.0F;
  float srceHueShift            = 0.0F;
  float destHueShift            = 0.0F;
};

template<class T>
struct channel_limits // NOLINT(readability-identifier-naming)
{
  [[nodiscard]] static constexpr auto min() noexcept -> T { return T(); }
  [[nodiscard]] static constexpr auto max() noexcept -> T { return T(); }
};
template<>
struct channel_limits<uint8_t>
{
  [[nodiscard]] static constexpr auto min() noexcept -> uint8_t { return 0; }
  [[nodiscard]] static constexpr auto max() noexcept -> uint8_t
  {
    return std::numeric_limits<uint8_t>::max();
  }
};
template<>
struct channel_limits<uint16_t>
{
  [[nodiscard]] static constexpr auto min() noexcept -> uint16_t
  {
    return channel_limits<uint8_t>::min();
  }
  [[nodiscard]] static constexpr auto max() noexcept -> uint16_t
  {
    return channel_limits<uint8_t>::max();
  }
};
template<>
struct channel_limits<uint32_t>
{
  [[nodiscard]] static constexpr auto min() noexcept -> uint32_t
  {
    return channel_limits<uint8_t>::min();
  }
  [[nodiscard]] static constexpr auto max() noexcept -> uint32_t
  {
    return channel_limits<uint8_t>::max();
  }
};
template<>
struct channel_limits<int32_t>
{
  [[nodiscard]] static constexpr auto min() noexcept -> int32_t
  {
    return channel_limits<uint8_t>::min();
  }
  [[nodiscard]] static constexpr auto max() noexcept -> int32_t
  {
    return channel_limits<uint8_t>::max();
  }
};
template<>
struct channel_limits<float>
{
  [[nodiscard]] static constexpr auto min() noexcept -> float
  {
    return channel_limits<uint8_t>::min();
  }
  [[nodiscard]] static constexpr auto max() noexcept -> float
  {
    return channel_limits<uint8_t>::max();
  }
};

using PixelChannelType = uint16_t;
using PixelIntType     = uint64_t;

inline constexpr auto MAX_CHANNEL_VALUE_HDR = 30U * 1024U;

inline constexpr auto MAX_COLOR_VAL = channel_limits<PixelChannelType>::max();
inline constexpr auto MAX_ALPHA     = MAX_COLOR_VAL;

static_assert(MAX_CHANNEL_VALUE_HDR <= std::numeric_limits<PixelChannelType>::max(),
              "Invalid MAX_CHANNEL_VALUE_HDR");

// TODO(glk) - maybe should be template: Pixel<uint8_t>, Pixel<uint16_t>
class Pixel // NOLINT: union hard to fix here
{
public:
  struct RGB
  {
    PixelChannelType red   = 0U;
    PixelChannelType green = 0U;
    PixelChannelType blue  = 0U;
    PixelChannelType alpha = MAX_ALPHA;
  };

  constexpr Pixel() noexcept;
  constexpr explicit Pixel(const RGB& color) noexcept;
  constexpr Pixel(PixelChannelType red,
                  PixelChannelType green,
                  PixelChannelType blue,
                  PixelChannelType alpha) noexcept;

  [[nodiscard]] constexpr auto R() const noexcept -> PixelChannelType;
  [[nodiscard]] constexpr auto G() const noexcept -> PixelChannelType;
  [[nodiscard]] constexpr auto B() const noexcept -> PixelChannelType;
  [[nodiscard]] constexpr auto A() const noexcept -> PixelChannelType;

  constexpr auto SetR(PixelChannelType val) noexcept -> void;
  constexpr auto SetG(PixelChannelType val) noexcept -> void;
  constexpr auto SetB(PixelChannelType val) noexcept -> void;
  constexpr auto SetA(PixelChannelType val) noexcept -> void;

  [[nodiscard]] constexpr auto RFlt() const noexcept -> float;
  [[nodiscard]] constexpr auto GFlt() const noexcept -> float;
  [[nodiscard]] constexpr auto BFlt() const noexcept -> float;

  [[nodiscard]] constexpr auto Rgba() const noexcept -> PixelIntType;

  [[nodiscard]] constexpr auto IsBlack() const noexcept -> bool;

  constexpr friend auto operator==(const Pixel& pixel1, const Pixel& pixel2) noexcept -> bool;

private:
#ifdef COLOR_BGRA
  struct Channels
  {
    PixelChannelType r = 0;
    PixelChannelType g = 0;
    PixelChannelType b = 0;
    PixelChannelType a = 0;
  };
#else
  struct Channels
  {
    PixelChannelType a = 0;
    PixelChannelType r = 0;
    PixelChannelType g = 0;
    PixelChannelType b = 0;
  };
#endif /* COLOR_BGRA */

  union Color
  {
    Channels channels{};
    PixelIntType intVal;
  };
  Color m_color{};
};

struct FXBuffSettings
{
  static constexpr float INITIAL_BUFF_INTENSITY = 0.5F;
  float buffIntensity                           = INITIAL_BUFF_INTENSITY;
};

class PixelBuffer
{
  using Buffer = std::vector<Pixel>;

public:
  PixelBuffer() noexcept = delete;
  explicit PixelBuffer(const Dimensions& dimensions) noexcept;
  PixelBuffer(const PixelBuffer&)                    = delete;
  PixelBuffer(PixelBuffer&&)                         = delete;
  auto operator=(const PixelBuffer&) -> PixelBuffer& = delete;
  auto operator=(PixelBuffer&&) -> PixelBuffer&      = delete;
  ~PixelBuffer() noexcept;

  auto Resize(const Dimensions& dimensions) noexcept -> void;

  [[nodiscard]] auto GetWidth() const noexcept -> uint32_t;
  [[nodiscard]] auto GetHeight() const noexcept -> uint32_t;

  auto Fill(const Pixel& pixel) noexcept -> void;
  auto CopyTo(PixelBuffer& pixelBuffer) const noexcept -> void;
  [[nodiscard]] static auto GetIntBufferSize(const Dimensions& dimensions) noexcept -> size_t;
  [[nodiscard]] auto GetIntBuff() const noexcept -> const PixelIntType*;

  [[nodiscard]] auto operator()(size_t x, size_t y) const noexcept -> const Pixel&;
  [[nodiscard]] auto operator()(int32_t x, int32_t y) const noexcept -> const Pixel&;
  [[nodiscard]] auto operator()(size_t x, size_t y) noexcept -> Pixel&;
  [[nodiscard]] auto operator()(int32_t x, int32_t y) noexcept -> Pixel&;

  // Fastest access.
  [[nodiscard]] auto GetBuffPos(size_t x, size_t y) const noexcept -> size_t;
  [[nodiscard]] auto GetBuffPos(int32_t x, int32_t y) const noexcept -> size_t;
  [[nodiscard]] auto GetPixel(size_t buffPos) const noexcept -> const Pixel&;
  [[nodiscard]] auto GetPixel(size_t buffPos) noexcept -> Pixel&;

  using iterator       = Buffer::iterator; // NOLINT(readability-identifier-naming)
  using const_iterator = Buffer::const_iterator; // NOLINT(readability-identifier-naming)
  [[nodiscard]] auto GetRowIter(size_t y) noexcept -> std::tuple<iterator, iterator>;
  [[nodiscard]] auto GetRowIter(size_t y) const noexcept
      -> std::tuple<const_iterator, const_iterator>;

  static constexpr size_t NUM_NBRS = 4;
  [[nodiscard]] auto Get4RHBNeighbours(size_t x, size_t y) const noexcept
      -> std::array<Pixel, NUM_NBRS>;
  [[nodiscard]] auto Get4RHBNeighbours(int32_t x, int32_t y) const noexcept
      -> std::array<Pixel, NUM_NBRS>;

private:
  uint32_t m_width;
  uint32_t m_height;
  uint32_t m_xMax = m_width - 1;
  uint32_t m_yMax = m_height - 1;
  Buffer m_buff;
};

static_assert(sizeof(Pixel) == sizeof(PixelIntType), "Invalid Pixel size.");

constexpr Pixel::Pixel() noexcept : m_color{Channels{}}
{
}

constexpr Pixel::Pixel(const RGB& color) noexcept
  : m_color{
        {color.red, color.green, color.blue, color.alpha}
}
{
}

constexpr Pixel::Pixel(const PixelChannelType red,
                       const PixelChannelType green,
                       const PixelChannelType blue,
                       const PixelChannelType alpha) noexcept
  : m_color{
        {red, green, blue, alpha}
}
{
}

static inline constexpr auto BLACK_PIXEL = Pixel{0U, 0U, 0U, MAX_ALPHA};
static inline constexpr auto WHITE_PIXEL =
    Pixel{MAX_COLOR_VAL, MAX_COLOR_VAL, MAX_COLOR_VAL, MAX_ALPHA};

constexpr auto operator==(const Pixel& pixel1, const Pixel& pixel2) noexcept -> bool
{
  return pixel1.m_color.intVal == pixel2.m_color.intVal; // NOLINT: union hard to fix here
}

constexpr auto Pixel::R() const noexcept -> PixelChannelType
{
  return m_color.channels.r; // NOLINT: union hard to fix here
}

constexpr auto Pixel::SetR(const PixelChannelType val) noexcept -> void
{
  m_color.channels.r = val; // NOLINT: union hard to fix here
}

constexpr auto Pixel::G() const noexcept -> PixelChannelType
{
  return m_color.channels.g; // NOLINT: union hard to fix here
}

constexpr auto Pixel::SetG(const PixelChannelType val) noexcept -> void
{
  m_color.channels.g = val; // NOLINT: union hard to fix here
}

constexpr auto Pixel::B() const noexcept -> PixelChannelType
{
  return m_color.channels.b; // NOLINT: union hard to fix here
}

constexpr auto Pixel::SetB(const PixelChannelType val) noexcept -> void
{
  m_color.channels.b = val; // NOLINT: union hard to fix here
}

constexpr auto Pixel::A() const noexcept -> PixelChannelType
{
  return m_color.channels.a; // NOLINT: union hard to fix here
}

constexpr auto Pixel::SetA(const PixelChannelType val) noexcept -> void
{
  m_color.channels.a = val; // NOLINT: union hard to fix here
}

constexpr auto Pixel::RFlt() const noexcept -> float
{
  return static_cast<float>(R()) / channel_limits<float>::max();
}

constexpr auto Pixel::GFlt() const noexcept -> float
{
  return static_cast<float>(G()) / channel_limits<float>::max();
}

constexpr auto Pixel::BFlt() const noexcept -> float
{
  return static_cast<float>(B()) / channel_limits<float>::max();
}

constexpr auto Pixel::Rgba() const noexcept -> PixelIntType
{
  return m_color.intVal; // NOLINT: union hard to fix here
}

constexpr auto Pixel::IsBlack() const noexcept -> bool
{
  return 0 == m_color.intVal; // NOLINT: union hard to fix here
}

inline auto PixelBuffer::GetWidth() const noexcept -> uint32_t
{
  return m_width;
}

inline auto PixelBuffer::GetHeight() const noexcept -> uint32_t
{
  return m_height;
}

inline auto PixelBuffer::Fill(const Pixel& pixel) noexcept -> void
{
  std::fill(begin(m_buff), end(m_buff), pixel);
}

inline auto PixelBuffer::GetIntBufferSize(const Dimensions& dimensions) noexcept -> size_t
{
  return static_cast<size_t>(dimensions.GetSize()) * sizeof(Pixel);
}

inline auto PixelBuffer::GetIntBuff() const noexcept -> const PixelIntType*
{
  return reinterpret_cast<const PixelIntType*>(m_buff.data());
}

inline auto PixelBuffer::CopyTo(PixelBuffer& pixelBuffer) const noexcept -> void
{
  std::copy(cbegin(m_buff), cend(m_buff), begin(pixelBuffer.m_buff));
}

inline auto PixelBuffer::operator()(const size_t x, const size_t y) const noexcept -> const Pixel&
{
  return GetPixel(GetBuffPos(x, y));
}

inline auto PixelBuffer::operator()(const int32_t x, const int32_t y) const noexcept -> const Pixel&
{
  return GetPixel(GetBuffPos(x, y));
}

inline auto PixelBuffer::operator()(const size_t x, const size_t y) noexcept -> Pixel&
{
  return GetPixel(GetBuffPos(x, y));
}

inline auto PixelBuffer::operator()(const int32_t x, const int32_t y) noexcept -> Pixel&
{
  return GetPixel(GetBuffPos(x, y));
}

inline auto PixelBuffer::GetBuffPos(const size_t x, const size_t y) const noexcept -> size_t
{
  return (y * m_width) + x;
}

inline auto PixelBuffer::GetBuffPos(const int32_t x, const int32_t y) const noexcept -> size_t
{
  return (static_cast<size_t>(y) * m_width) + static_cast<size_t>(x);
}

inline auto PixelBuffer::GetPixel(const size_t buffPos) const noexcept -> const Pixel&
{
#ifdef GOOM_DEBUG
  return m_buff.at(buffPos);
#else
  return m_buff[buffPos];
#endif
}

inline auto PixelBuffer::GetPixel(const size_t buffPos) noexcept -> Pixel&
{
#ifdef GOOM_DEBUG
  return m_buff.at(buffPos);
#else
  return m_buff[buffPos];
#endif
}

inline auto PixelBuffer::GetRowIter(const size_t y) noexcept
    -> std::tuple<PixelBuffer::iterator, PixelBuffer::iterator>
{
  const auto rowPos = static_cast<int32_t>(y * m_width);
  return std::make_tuple(begin(m_buff) + rowPos,
                         begin(m_buff) + rowPos + static_cast<int32_t>(m_width));
}

inline auto PixelBuffer::GetRowIter(const size_t y) const noexcept
    -> std::tuple<PixelBuffer::const_iterator, PixelBuffer::const_iterator>
{
  const auto rowPos = static_cast<int32_t>(y * m_width);
  return std::make_tuple(cbegin(m_buff) + rowPos,
                         cbegin(m_buff) + rowPos + static_cast<int32_t>(m_width));
}

inline auto PixelBuffer::Get4RHBNeighbours(const int32_t x, const int32_t y) const noexcept
    -> std::array<Pixel, NUM_NBRS>
{
  return Get4RHBNeighbours(static_cast<size_t>(x), static_cast<size_t>(y));
}

inline auto PixelBuffer::Get4RHBNeighbours(const size_t x, const size_t y) const noexcept
    -> std::array<Pixel, NUM_NBRS>
{
  Expects(x < m_xMax);
  Expects(y < m_yMax);

  const auto xPos = (y * m_width) + x;

  // This is a serious hotspot so the following ugly access optimization
  // saves a few milliseconds per update.

  /** Simple, clean code, but slightly slower.
  return {
      {
        m_buff[xPos],
        m_buff[xPos + 1],
        m_buff[xPos + m_width],
        m_buff[xPos + m_width + 1]
      }
  };
   **/

  // Ugly code, but slightly faster.
  struct TwoPixels
  {
    Pixel pixel1;
    Pixel pixel2;
  };
  std::array<Pixel, NUM_NBRS> neighbours;

  // NOLINTBEGIN: Optimization
  *reinterpret_cast<TwoPixels*>(&(neighbours[0])) =
      *reinterpret_cast<const TwoPixels*>(&(m_buff[xPos]));
  *reinterpret_cast<TwoPixels*>(&(neighbours[2])) =
      *reinterpret_cast<const TwoPixels*>(&(m_buff[xPos + m_width]));
  // NOLINTEND

  return neighbours;
}

} // namespace GOOM
