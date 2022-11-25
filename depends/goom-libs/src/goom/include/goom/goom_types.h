#pragma once

#include "goom_config.h"

#include <cstdint>

namespace GOOM
{

template<typename T>
using Ptr = T*;

class Dimensions
{
public:
  constexpr Dimensions(uint32_t width, uint32_t height) noexcept;

  [[nodiscard]] constexpr auto GetWidth() const noexcept -> uint32_t;
  [[nodiscard]] constexpr auto GetHeight() const noexcept -> uint32_t;
  [[nodiscard]] constexpr auto GetSize() const noexcept -> uint32_t;

  [[nodiscard]] constexpr auto GetIntWidth() const noexcept -> int32_t;
  [[nodiscard]] constexpr auto GetIntHeight() const noexcept -> int32_t;

private:
  uint32_t m_width;
  uint32_t m_height;
};

// NOLINTNEXTLINE(bugprone-easily-swappable-parameters)
constexpr Dimensions::Dimensions(const uint32_t width, const uint32_t height) noexcept
  : m_width{width}, m_height{height}
{
  Expects(width > 0);
  Expects(height > 0);
}

[[nodiscard]] constexpr auto Dimensions::GetWidth() const noexcept -> uint32_t
{
  return m_width;
}

[[nodiscard]] constexpr auto Dimensions::GetHeight() const noexcept -> uint32_t
{
  return m_height;
}

[[nodiscard]] constexpr auto Dimensions::GetSize() const noexcept -> uint32_t
{
  return m_width * m_height;
}

[[nodiscard]] constexpr auto Dimensions::GetIntWidth() const noexcept -> int32_t
{
  return static_cast<int32_t>(m_width);
}

[[nodiscard]] constexpr auto Dimensions::GetIntHeight() const noexcept -> int32_t
{
  return static_cast<int32_t>(m_height);
}

} // namespace GOOM
