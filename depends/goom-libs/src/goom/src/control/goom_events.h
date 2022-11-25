#pragma once

#include "utils/enum_utils.h"
#include "utils/math/goom_rand_base.h"

#include <array>

namespace GOOM::CONTROL
{

class GoomEvents
{
public:
  explicit GoomEvents(const UTILS::MATH::IGoomRand& goomRand);
  GoomEvents(const GoomEvents&) noexcept           = delete;
  GoomEvents(GoomEvents&&) noexcept                = delete;
  ~GoomEvents()                                    = default;
  auto operator=(const GoomEvents&) -> GoomEvents& = delete;
  auto operator=(GoomEvents&&) -> GoomEvents&      = delete;

  enum class GoomEvent
  {
    CHANGE_FILTER_MODE = 0,
    CHANGE_STATE,
    CHANGE_TO_MEGA_LENT_MODE,
    FILTER_REVERSE_ON,
    FILTER_REVERSE_OFF_AND_STOP_SPEED,
    FILTER_VITESSE_STOP_SPEED_MINUS1,
    FILTER_VITESSE_STOP_SPEED,
    FILTER_CHANGE_VITESSE_AND_TOGGLE_REVERSE,
    FILTER_TOGGLE_ROTATION,
    FILTER_INCREASE_ROTATION,
    FILTER_DECREASE_ROTATION,
    FILTER_STOP_ROTATION,
    _num // unused, and marks the enum end
  };

  [[nodiscard]] auto Happens(GoomEvent event) const -> bool;

private:
  const UTILS::MATH::IGoomRand& m_goomRand;
  static constexpr size_t NUM_GOOM_EVENTS = UTILS::NUM<GoomEvent>;
  struct WeightedEvent
  {
    GoomEvent event;
    float probability;
  };
  const std::array<WeightedEvent, NUM_GOOM_EVENTS> m_weightedEvents;
};

} // namespace GOOM::CONTROL
