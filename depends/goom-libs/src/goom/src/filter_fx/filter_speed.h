#pragma once

#include "goom_config.h"

#include <algorithm>
#include <cstdint>

namespace GOOM::FILTER_FX
{

class Vitesse
{
public:
  static constexpr uint32_t STOP_SPEED        = 0U;
  static constexpr uint32_t SLOWEST_SPEED     = STOP_SPEED + 1U;
  static constexpr uint32_t SLOW_SPEED        = STOP_SPEED + 2U;
  static constexpr uint32_t CALM_SPEED        = STOP_SPEED + 4U;
  static constexpr uint32_t FAST_SPEED        = STOP_SPEED + 5U;
  static constexpr uint32_t FASTER_SPEED      = STOP_SPEED + 6U;
  static constexpr uint32_t EVEN_FASTER_SPEED = STOP_SPEED + 7U;
  static constexpr uint32_t MAXIMUM_SPEED     = STOP_SPEED + 10U;
  static constexpr uint32_t DEFAULT_SPEED     = SLOWEST_SPEED;

  [[nodiscard]] constexpr auto GetVitesse() const noexcept -> uint32_t;
  constexpr auto SetVitesse(uint32_t val) noexcept -> void;
  constexpr auto SetDefault() noexcept -> void;
  constexpr auto GoSlowerBy(uint32_t amount) noexcept -> void;
  [[nodiscard]] constexpr static auto GetFasterBy(uint32_t speed, uint32_t amount) noexcept
      -> uint32_t;
  [[nodiscard]] constexpr static auto GetSlowerBy(uint32_t speed, uint32_t amount) noexcept
      -> uint32_t;

  [[nodiscard]] constexpr auto GetReverseVitesse() const noexcept -> bool;
  constexpr auto SetReverseVitesse(bool val) noexcept -> void;
  constexpr auto ToggleReverseVitesse() noexcept -> void;

  [[nodiscard]] constexpr static auto IsFasterThan(uint32_t speed, uint32_t otherSpeed) noexcept
      -> bool;
  [[nodiscard]] constexpr auto IsFasterThan(uint32_t otherSpeed) const noexcept -> bool;
  [[nodiscard]] constexpr static auto IsSlowerThan(uint32_t speed, uint32_t otherSpeed) noexcept
      -> bool;
  [[nodiscard]] constexpr auto IsSlowerThan(uint32_t otherSpeed) const noexcept -> bool;

  [[nodiscard]] constexpr auto GetRelativeSpeed() const noexcept -> float;

private:
  uint32_t m_vitesse    = DEFAULT_SPEED;
  bool m_reverseVitesse = true;
};

constexpr auto Vitesse::SetDefault() noexcept -> void
{
  m_vitesse        = DEFAULT_SPEED;
  m_reverseVitesse = true;
}

constexpr auto Vitesse::GetReverseVitesse() const noexcept -> bool
{
  return m_reverseVitesse;
}

constexpr auto Vitesse::SetReverseVitesse(const bool val) noexcept -> void
{
  m_reverseVitesse = val;
}

constexpr auto Vitesse::ToggleReverseVitesse() noexcept -> void
{
  m_reverseVitesse = not m_reverseVitesse;
}

constexpr auto Vitesse::GetVitesse() const noexcept -> uint32_t
{
  return m_vitesse;
}

constexpr auto Vitesse::SetVitesse(const uint32_t val) noexcept -> void
{
  Expects(not IsFasterThan(val, MAXIMUM_SPEED));
  Expects(not IsSlowerThan(val, STOP_SPEED));

  m_vitesse = val;
}

constexpr auto Vitesse::GoSlowerBy(const uint32_t amount) noexcept -> void
{
  if (amount > m_vitesse)
  {
    m_vitesse = STOP_SPEED;
    return;
  }
  m_vitesse -= amount;

  Ensures(not IsFasterThan(m_vitesse, MAXIMUM_SPEED));
  Ensures(not IsSlowerThan(m_vitesse, STOP_SPEED));
}

constexpr auto Vitesse::GetFasterBy(const uint32_t speed, const uint32_t amount) noexcept
    -> uint32_t
{
  return std::min(speed + amount, MAXIMUM_SPEED);
}

constexpr auto Vitesse::GetSlowerBy(const uint32_t speed, const uint32_t amount) noexcept
    -> uint32_t
{
  if (amount >= speed)
  {
    return STOP_SPEED;
  }
  return speed - amount;
}

constexpr auto Vitesse::IsFasterThan(const uint32_t speed, const uint32_t otherSpeed) noexcept
    -> bool
{
  return speed > otherSpeed;
}

constexpr auto Vitesse::IsFasterThan(const uint32_t otherSpeed) const noexcept -> bool
{
  return IsFasterThan(m_vitesse, otherSpeed);
}

constexpr auto Vitesse::IsSlowerThan(const uint32_t speed, const uint32_t otherSpeed) noexcept
    -> bool
{
  return speed < otherSpeed;
}

constexpr auto Vitesse::IsSlowerThan(const uint32_t otherSpeed) const noexcept -> bool
{
  return IsSlowerThan(m_vitesse, otherSpeed);
}

constexpr auto Vitesse::GetRelativeSpeed() const noexcept -> float
{
  const auto relativeSpeed = static_cast<float>(m_vitesse) / static_cast<float>(MAXIMUM_SPEED);

  return m_reverseVitesse ? -relativeSpeed : +relativeSpeed;
}

} // namespace GOOM::FILTER_FX
