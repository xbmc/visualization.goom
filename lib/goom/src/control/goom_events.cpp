#include "goom_events.h"

#include "goomutils/goomrand.h"

#if __cplusplus <= 201402L
namespace GOOM
{
namespace CONTROL
{
#else
namespace GOOM::CONTROL
{
#endif

using UTILS::ProbabilityOfMInN;

GoomEvents::GoomEvents() noexcept
  : //@formatter:off
    // clang-format off
    m_weightedEvents{{
      { /*.event = */GoomEvent::CHANGE_FILTER_MODE,                         /*.m = */1, /*.outOf = */ 20 },
      { /*.event = */GoomEvent::CHANGE_STATE,                               /*.m = */1, /*.outOf = */  2 },
      { /*.event = */GoomEvent::CHANGE_TO_MEGA_LENT_MODE,                   /*.m = */1, /*.outOf = */700 },
      { /*.event = */GoomEvent::CHANGE_LINE_CIRCLE_AMPLITUDE,               /*.m = */1, /*.outOf = */  3 },
      { /*.event = */GoomEvent::CHANGE_LINE_CIRCLE_PARAMS,                  /*.m = */1, /*.outOf = */  2 },
      { /*.event = */GoomEvent::CHANGE_H_LINE_PARAMS,                       /*.m = */3, /*.outOf = */  4 },
      { /*.event = */GoomEvent::CHANGE_V_LINE_PARAMS,                       /*.m = */2, /*.outOf = */  3 },
      { /*.event = */GoomEvent::REDUCE_LINE_MODE,                           /*.m = */1, /*.outOf = */  5 },
      { /*.event = */GoomEvent::UPDATE_LINE_MODE,                           /*.m = */1, /*.outOf = */  4 },
      { /*.event = */GoomEvent::CHANGE_LINE_TO_BLACK,                       /*.m = */1, /*.outOf = */  2 },
      { /*.event = */GoomEvent::CHANGE_GOOM_LINE,                           /*.m = */1, /*.outOf = */  3 },
      { /*.event = */GoomEvent::FILTER_REVERSE_ON,                          /*.m = */1, /*.outOf = */ 10 },
      { /*.event = */GoomEvent::FILTER_REVERSE_OFF_AND_STOP_SPEED,          /*.m = */1, /*.outOf = */  5 },
      { /*.event = */GoomEvent::FILTER_VITESSE_STOP_SPEED_MINUS1,           /*.m = */1, /*.outOf = */  5 },
      { /*.event = */GoomEvent::FILTER_VITESSE_STOP_SPEED,                  /*.m = */1, /*.outOf = */ 10 },
      { /*.event = */GoomEvent::FILTER_CHANGE_VITESSE_AND_TOGGLE_REVERSE,   /*.m = */1, /*.outOf = */ 20 },
      { /*.event = */GoomEvent::TURN_OFF_NOISE,                             /*.m = */4, /*.outOf = */  5 },
      { /*.event = */GoomEvent::FILTER_TOGGLE_ROTATION,                     /*.m =*/ 5, /*.outOf = */ 40 },
      { /*.event = */GoomEvent::FILTER_INCREASE_ROTATION,                   /*.m =*/10, /*.outOf = */ 40 },
      { /*.event = */GoomEvent::FILTER_DECREASE_ROTATION,                   /*.m =*/35, /*.outOf = */ 40 },
      { /*.event = */GoomEvent::FILTER_STOP_ROTATION,                       /*.m =*/20, /*.outOf = */ 40 },
      { /*.event = */GoomEvent::IFS_RENEW,                                  /*.m = */2, /*.outOf = */  3 },
      { /*.event = */GoomEvent::CHANGE_BLOCKY_WAVY_TO_ON,                   /*.m = */5, /*.outOf = */ 20 },
      { /*.event = */GoomEvent::CHANGE_ZOOM_FILTER_ALLOW_OVEREXPOSED_TO_ON, /*.m = */8, /*.outOf = */ 10 },
    }},
    m_weightedLineEvents{{
      { LinesFx::LineType::circle, 10 },
      { LinesFx::LineType::hline,   2 },
      { LinesFx::LineType::vline,   2 },
    }},
    // clang-format on
    //@formatter:on
    m_lineTypeWeights{{m_weightedLineEvents.begin(), m_weightedLineEvents.end()}}
{
}

auto GoomEvents::Happens(const GoomEvent event) -> bool
{
  const WeightedEvent& weightedEvent = m_weightedEvents[static_cast<size_t>(event)];
  return ProbabilityOfMInN(weightedEvent.m, weightedEvent.outOf);
}

#if __cplusplus <= 201402L
} // namespace CONTROL
} // namespace GOOM
#else
} // namespace GOOM::CONTROL
#endif
