#pragma once

#include "date_utils.h"
#include "goom_config.h"

#include <chrono>
#include <cstdint>
#include <limits>
#include <string>

namespace GOOM::UTILS
{

class Stopwatch
{
  using ChronoTimePoint = std::chrono::time_point<std::chrono::steady_clock>;

public:
  Stopwatch() noexcept = default;

  auto DoUpperLimitOfTimeIntervalCheck(bool val) -> void;
  auto SetUpperLimitOfTimeIntervalInMsSinceLastMarked(float val) -> void;
  auto SetStartDelayAdjustInMs(float val) -> void;
  auto SetDuration(uint32_t durationInMs) noexcept -> void;

  auto StartNow() noexcept -> void;
  auto MarkTimeNow() noexcept -> void;

  struct TimeValues
  {
    float timeElapsedInMs        = 0.0F;
    float timeRemainingInMs      = 0.0F;
    float timeRemainingAsPercent = 0.0F;
  };
  [[nodiscard]] auto AreTimesValid() const noexcept -> bool;
  [[nodiscard]] auto GetTimeValues() const noexcept -> const TimeValues&;

  [[nodiscard]] auto GetDurationInMs() const noexcept -> float;
  [[nodiscard]] auto GetActualDurationInMs() const noexcept -> float;
  [[nodiscard]] auto GetStartTimeAsStr() const noexcept -> std::string;
  [[nodiscard]] auto GetLastMarkedTimeAsStr() const noexcept -> std::string;

private:
  float m_durationInMs = 0.0F;
  ChronoTimePoint m_startTime{};
  ChronoTimePoint m_lastMarkedTime{};
  float m_startDelayAdjustInMs                        = 0.0F;
  bool m_doUpperLimitOfTimeIntervalCheck              = false;
  float m_upperLimitOfTimeIntervalInMsSinceLastMarked = std::numeric_limits<float>::max();
  [[nodiscard]] auto IsValidTimeIntervalSinceLastMarked(float timeIntervalInMs) const noexcept
      -> bool;
  bool m_valid = false;
  TimeValues m_timeValues{};
};

inline auto Stopwatch::DoUpperLimitOfTimeIntervalCheck(const bool val) -> void
{
  m_doUpperLimitOfTimeIntervalCheck = val;
}

inline auto Stopwatch::SetUpperLimitOfTimeIntervalInMsSinceLastMarked(const float val) -> void
{
  m_upperLimitOfTimeIntervalInMsSinceLastMarked = val;
}

inline auto Stopwatch::SetStartDelayAdjustInMs(const float val) -> void
{
  m_startDelayAdjustInMs = val;
}

inline auto Stopwatch::SetDuration(const uint32_t durationInMs) noexcept -> void
{
  Expects(durationInMs > 0U);

  m_durationInMs = static_cast<float>(durationInMs);
  m_valid        = true;
}

inline auto Stopwatch::StartNow() noexcept -> void
{
  m_startTime = std::chrono::steady_clock::now() -
                std::chrono::milliseconds(static_cast<int32_t>(m_startDelayAdjustInMs));
  m_valid                             = m_durationInMs > 0;
  m_timeValues.timeElapsedInMs        = 0.0F;
  m_timeValues.timeRemainingInMs      = m_durationInMs;
  m_timeValues.timeRemainingAsPercent = 100.0F;
}

inline auto Stopwatch::MarkTimeNow() noexcept -> void
{
  Expects(m_startTime != ChronoTimePoint{});

  m_lastMarkedTime = std::chrono::steady_clock::now();

  if (not m_valid)
  {
    return;
  }

  auto newTimeElapsedInMs = static_cast<float>(
      std::chrono::duration_cast<std::chrono::milliseconds>(m_lastMarkedTime - m_startTime)
          .count());
  auto newTimeRemainingInMs = m_durationInMs - newTimeElapsedInMs;

  if (not IsValidTimeIntervalSinceLastMarked(newTimeElapsedInMs - m_timeValues.timeElapsedInMs))
  {
    // The new time interval was too big. Give up.
    m_valid = false;
    return;
  }

  if (newTimeElapsedInMs > m_durationInMs)
  {
    // Because we allow adjusting the start time, 'timeElapsed' maybe bigger than duration.
    newTimeElapsedInMs   = m_durationInMs;
    newTimeRemainingInMs = 0.0F;
  }

  Expects(newTimeElapsedInMs <= m_durationInMs);
  m_timeValues.timeElapsedInMs        = newTimeElapsedInMs;
  m_timeValues.timeRemainingInMs      = newTimeRemainingInMs;
  m_timeValues.timeRemainingAsPercent = (100.0F * m_timeValues.timeRemainingInMs) / m_durationInMs;
}

inline auto Stopwatch::IsValidTimeIntervalSinceLastMarked(
    const float timeIntervalInMs) const noexcept -> bool
{
  if (not m_doUpperLimitOfTimeIntervalCheck)
  {
    return true;
  }

  return timeIntervalInMs <= m_upperLimitOfTimeIntervalInMsSinceLastMarked;
}

inline auto Stopwatch::AreTimesValid() const noexcept -> bool
{
  return m_valid;
}

inline auto Stopwatch::GetTimeValues() const noexcept -> const TimeValues&
{
  return m_timeValues;
}

inline auto Stopwatch::GetDurationInMs() const noexcept -> float
{
  return m_durationInMs;
}

inline auto Stopwatch::GetActualDurationInMs() const noexcept -> float
{
  return static_cast<float>(
      std::chrono::duration_cast<std::chrono::milliseconds>(m_lastMarkedTime - m_startTime)
          .count());
}

inline auto Stopwatch::GetStartTimeAsStr() const noexcept -> std::string
{
  return GetSteadyClockAsString(m_startTime);
}

inline auto Stopwatch::GetLastMarkedTimeAsStr() const noexcept -> std::string
{
  return GetSteadyClockAsString(m_lastMarkedTime);
}

} // namespace GOOM::UTILS
