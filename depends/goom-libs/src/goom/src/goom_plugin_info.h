#pragma once

#include "control/goom_sound_events.h"
#include "goom_types.h"

#include <cstdint>
#include <memory>

namespace GOOM
{

class PluginInfo
{
public:
  PluginInfo() noexcept = delete;
  PluginInfo(const Dimensions& dimensions, const CONTROL::GoomSoundEvents& soundEvents) noexcept;
  PluginInfo(const PluginInfo&) noexcept           = delete;
  PluginInfo(PluginInfo&&) noexcept                = delete;
  virtual ~PluginInfo() noexcept                   = default;
  auto operator=(const PluginInfo&) -> PluginInfo& = delete;
  auto operator=(PluginInfo&&) -> PluginInfo&      = delete;

  [[nodiscard]] auto GetScreenDimensions() const -> const Dimensions&;
  [[nodiscard]] auto GetScreenWidth() const noexcept -> uint32_t;
  [[nodiscard]] auto GetScreenHeight() const noexcept -> uint32_t;
  [[nodiscard]] auto GetScreenSize() const noexcept -> uint32_t;
  [[nodiscard]] auto GetSoundEvents() const -> const CONTROL::GoomSoundEvents&;

private:
  const Dimensions m_dimensions;
  const CONTROL::GoomSoundEvents& m_soundEvents;
};

inline PluginInfo::PluginInfo(const Dimensions& dimensions,
                              const CONTROL::GoomSoundEvents& soundEvents) noexcept
  : m_dimensions{dimensions}, m_soundEvents{soundEvents}
{
}

inline auto PluginInfo::GetScreenDimensions() const -> const Dimensions&
{
  return m_dimensions;
}

inline auto PluginInfo::GetScreenWidth() const noexcept -> uint32_t
{
  return m_dimensions.GetWidth();
}

inline auto PluginInfo::GetScreenHeight() const noexcept -> uint32_t
{
  return m_dimensions.GetHeight();
}

inline auto PluginInfo::GetScreenSize() const noexcept -> uint32_t
{
  return m_dimensions.GetSize();
}

inline auto PluginInfo::GetSoundEvents() const -> const CONTROL::GoomSoundEvents&
{
  return m_soundEvents;
}

} // namespace GOOM
