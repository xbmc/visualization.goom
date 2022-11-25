#pragma once

#include "goom_config.h"
#include "math/misc.h"

#include <cstdint>

namespace GOOM::UTILS
{

class StepSpeed
{
public:
  StepSpeed(uint32_t minNumSteps, uint32_t maxNumSteps, float initialSpeed);

  auto SetMinMaxNumSteps(uint32_t minNumSteps, uint32_t maxNumSteps) -> void;
  auto SetSpeed(float val) -> void;

  [[nodiscard]] auto GetCurrentNumSteps() const -> uint32_t;

  template<typename T>
  auto ApplySpeed(T& obj) -> void;

private:
  uint32_t m_minNumSteps;
  uint32_t m_maxNumSteps;
  float m_tMinMaxLerp;
  uint32_t m_currentNumSteps = 0U;
  auto SetCurrentNumSteps() -> void;
};

inline StepSpeed::StepSpeed(const uint32_t minNumSteps,
                            const uint32_t maxNumSteps,
                            const float initialSpeed)
  : m_minNumSteps{minNumSteps}, m_maxNumSteps{maxNumSteps}, m_tMinMaxLerp{initialSpeed}
{
  Expects(0 < minNumSteps);
  Expects(minNumSteps < maxNumSteps);
  Expects(0.0F <= initialSpeed);

  SetCurrentNumSteps();
}

inline auto StepSpeed::SetMinMaxNumSteps(const uint32_t minNumSteps, const uint32_t maxNumSteps)
    -> void
{
  Expects(0 < minNumSteps);
  Expects(minNumSteps < maxNumSteps);
  m_minNumSteps = minNumSteps;
  m_maxNumSteps = maxNumSteps;
  SetCurrentNumSteps();
}

inline auto StepSpeed::SetSpeed(const float val) -> void
{
  Expects(0.0F <= val);
  Expects(val <= 1.0F);
  m_tMinMaxLerp = val;
  SetCurrentNumSteps();
}

inline auto StepSpeed::SetCurrentNumSteps() -> void
{
  m_currentNumSteps = STD20::lerp(m_maxNumSteps, m_minNumSteps, m_tMinMaxLerp);
}

inline auto StepSpeed::GetCurrentNumSteps() const -> uint32_t
{
  return m_currentNumSteps;
}

template<typename T>
inline auto StepSpeed::ApplySpeed(T& obj) -> void
{
  obj.SetNumSteps(m_currentNumSteps);
}

} // namespace GOOM::UTILS
