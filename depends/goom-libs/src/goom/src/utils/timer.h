#pragma once

#include "goom_config.h"

#include <cstdint>
#include <functional>

namespace GOOM::UTILS
{

class Timer
{
public:
  Timer() noexcept = delete;
  explicit Timer(uint32_t numCount, bool setToFinished = false) noexcept;

  [[nodiscard]] auto GetTimeLimit() const noexcept -> uint32_t;
  auto SetTimeLimit(uint32_t val, bool setToFinished = false) noexcept -> void;
  auto ResetToZero() noexcept -> void;
  auto SetToFinished() noexcept -> void;

  auto Increment() noexcept -> void;
  [[nodiscard]] auto JustFinished() const noexcept -> bool;
  [[nodiscard]] auto Finished() const noexcept -> bool;
  [[nodiscard]] auto GetCurrentCount() const noexcept -> uint64_t;

private:
  uint32_t m_numCount;
  uint64_t m_count;
};

class OnOffTimer
{
public:
  struct TimerCounts
  {
    uint32_t numOnCount;
    uint32_t numOnCountAfterFailedOff;
    uint32_t numOffCount;
    uint32_t numOffCountAfterFailedOn;
  };
  explicit OnOffTimer(const TimerCounts& timerCounts) noexcept;

  using Action = std::function<bool()>; // return true if action succeeded.
  auto SetActions(const Action& onAction, const Action& offAction) noexcept -> void;

  auto StartOnTimer() noexcept -> void;
  auto StartOffTimer() noexcept -> void;

  auto Stop() noexcept -> void;

  auto Increment() noexcept -> void;
  auto TryToChangeState() noexcept -> void;

private:
  TimerCounts m_timerCounts;
  Timer m_onTimer{m_timerCounts.numOnCount, true};
  Timer m_offTimer{m_timerCounts.numOffCount, true};
  Action m_onAction  = nullptr;
  Action m_offAction = nullptr;
  enum class TimerState
  {
    NO_TIMERS_ACTIVE,
    ON_TIMER_ACTIVE,
    OFF_TIMER_ACTIVE,
  };
  TimerState m_timerState = TimerState::NO_TIMERS_ACTIVE;
  auto ChangeStateToOff() -> void;
  auto ChangeStateToOn() -> void;
};

inline Timer::Timer(const uint32_t numCount, const bool setToFinished) noexcept
  : m_numCount{numCount}, m_count(setToFinished ? m_numCount : 0)
{
}

inline auto Timer::GetCurrentCount() const noexcept -> uint64_t
{
  return m_count;
}

inline auto Timer::GetTimeLimit() const noexcept -> uint32_t
{
  return m_numCount;
}

inline auto Timer::SetTimeLimit(const uint32_t val, const bool setToFinished) noexcept -> void
{
  m_numCount = val;

  if (setToFinished)
  {
    SetToFinished();
  }
  else
  {
    ResetToZero();
  }
}

inline auto Timer::JustFinished() const noexcept -> bool
{
  return m_count == m_numCount;
}

inline auto Timer::Finished() const noexcept -> bool
{
  return m_count >= m_numCount;
}

inline auto Timer::ResetToZero() noexcept -> void
{
  m_count = 0;
}

inline auto Timer::SetToFinished() noexcept -> void
{
  m_count = m_numCount;
}

inline auto Timer::Increment() noexcept -> void
{
  ++m_count;
}

inline OnOffTimer::OnOffTimer(const TimerCounts& timerCounts) noexcept : m_timerCounts{timerCounts}
{
}

inline auto OnOffTimer::SetActions(const Action& onAction, const Action& offAction) noexcept -> void
{
  m_onAction  = onAction;
  m_offAction = offAction;
}

inline auto OnOffTimer::StartOnTimer() noexcept -> void
{
  Expects(m_timerState == TimerState::NO_TIMERS_ACTIVE);
  Expects(m_onTimer.Finished());
  Expects(m_offTimer.Finished());
  Expects(m_onAction != nullptr);
  Expects(m_offAction != nullptr);

  m_timerState = TimerState::ON_TIMER_ACTIVE;
  m_onTimer.ResetToZero();

  Ensures(not m_onTimer.Finished());
  Ensures(m_offTimer.Finished());
}

inline auto OnOffTimer::StartOffTimer() noexcept -> void
{
  Expects(m_timerState == TimerState::NO_TIMERS_ACTIVE);
  Expects(m_onTimer.Finished());
  Expects(m_offTimer.Finished());
  Expects(m_onAction != nullptr);
  Expects(m_offAction != nullptr);

  m_timerState = TimerState::OFF_TIMER_ACTIVE;
  m_offTimer.ResetToZero();

  Ensures(not m_offTimer.Finished());
  Ensures(m_onTimer.Finished());
}

inline auto OnOffTimer::Stop() noexcept -> void
{
  if (TimerState::ON_TIMER_ACTIVE == m_timerState)
  {
    m_offAction();
  }
  else if (TimerState::OFF_TIMER_ACTIVE == m_timerState)
  {
    m_onAction();
  }
  m_timerState = TimerState::NO_TIMERS_ACTIVE;
  m_onTimer.SetToFinished();
  m_offTimer.SetToFinished();

  Ensures(m_onTimer.Finished());
  Ensures(m_offTimer.Finished());
  Ensures(m_timerState == TimerState::NO_TIMERS_ACTIVE);
}

inline auto OnOffTimer::TryToChangeState() noexcept -> void
{
  if (TimerState::ON_TIMER_ACTIVE == m_timerState)
  {
    ChangeStateToOff();
  }
  else if (TimerState::OFF_TIMER_ACTIVE == m_timerState)
  {
    ChangeStateToOn();
  }
}

inline auto OnOffTimer::Increment() noexcept -> void
{
  if (TimerState::ON_TIMER_ACTIVE == m_timerState)
  {
    Expects(m_offTimer.Finished());
    m_onTimer.Increment();
    if (m_onTimer.Finished())
    {
      ChangeStateToOff();
    }
  }
  else if (TimerState::OFF_TIMER_ACTIVE == m_timerState)
  {
    Expects(m_onTimer.Finished());
    m_offTimer.Increment();
    if (m_offTimer.Finished())
    {
      ChangeStateToOn();
    }
  }
}

inline auto OnOffTimer::ChangeStateToOff() -> void
{
  Expects(m_offTimer.Finished());

  if (not m_offAction())
  {
    m_onTimer.SetTimeLimit(m_timerCounts.numOnCountAfterFailedOff);
    Ensures(not m_onTimer.Finished());
    Ensures(m_offTimer.Finished());
    return;
  }

  m_onTimer.SetToFinished();
  m_offTimer.SetTimeLimit(m_timerCounts.numOffCount);
  m_timerState = TimerState::OFF_TIMER_ACTIVE;

  Ensures(not m_offTimer.Finished());
  Ensures(m_onTimer.Finished());
}

inline auto OnOffTimer::ChangeStateToOn() -> void
{
  Expects(m_onTimer.Finished());

  if (not m_onAction())
  {
    m_offTimer.SetTimeLimit(m_timerCounts.numOffCountAfterFailedOn);
    Ensures(not m_offTimer.Finished());
    Ensures(m_onTimer.Finished());
    return;
  }

  m_offTimer.SetToFinished();
  m_onTimer.SetTimeLimit(m_timerCounts.numOnCount);
  m_timerState = TimerState::ON_TIMER_ACTIVE;

  Ensures(not m_onTimer.Finished());
  Ensures(m_offTimer.Finished());
}

} // namespace GOOM::UTILS
