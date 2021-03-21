#ifndef VISUALIZATION_GOOM_TIMER_H
#define VISUALIZATION_GOOM_TIMER_H

#include "goom/v2d.h"

#include <cstdint>

#if __cplusplus <= 201402L
namespace GOOM
{
namespace UTILS
{
#else
namespace GOOM::UTILS
{
#endif

class Timer
{
public:
  Timer() noexcept = default;
  explicit Timer(uint32_t numCount) noexcept;

  auto GetTimeLimit() const -> uint32_t;
  void SetTimeLimit(uint32_t val);

  void ResetToZero();
  void SetToFinished();
  void Increment();
  auto Finished() const -> bool;
  auto GetCurrentCount() const -> uint32_t;

private:
  uint32_t m_numCount{};
  uint32_t m_count{};
};

inline Timer::Timer(const uint32_t numCount) noexcept : m_numCount{numCount}
{
}

inline auto Timer::GetCurrentCount() const -> uint32_t
{
  return m_count;
}

inline auto Timer::GetTimeLimit() const -> uint32_t
{
  return m_numCount;
}

inline void Timer::SetTimeLimit(const uint32_t val)
{
  m_numCount = val;
  m_count = 0;
}

inline auto Timer::Finished() const -> bool
{
  return m_count >= m_numCount;
}

inline void Timer::ResetToZero()
{
  m_count = 0;
}

inline void Timer::SetToFinished()
{
  m_count = m_numCount;
}

inline void Timer::Increment()
{
  if (Finished())
  {
    return;
  }

  m_count++;
}

#if __cplusplus <= 201402L
} // namespace UTILS
} // namespace GOOM
#else
} // namespace GOOM::UTILS
#endif
#endif //VISUALIZATION_GOOM_TIMER_H
