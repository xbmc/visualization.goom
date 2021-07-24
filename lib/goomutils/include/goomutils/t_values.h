#ifndef VISUALIZATION_GOOM_T_VALUES_H
#define VISUALIZATION_GOOM_T_VALUES_H

#include "mathutils.h"

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


class TValue
{
public:
  enum class StepType
  {
    CONTINUOUS_REPEATABLE,
    CONTINUOUS_REVERSIBLE,
    SINGLE_CYCLE,
  };
  explicit TValue(StepType stepType, float stepSize) noexcept;
  explicit TValue(StepType stepType, uint32_t numSteps) noexcept;

  static constexpr float MAX_T_VALUE = 1.0F + SMALL_FLOAT;

  auto GetStepType() const -> StepType;
  auto GetStepSize() const -> float;
  void SetStepSize(float val);

  auto operator()() const -> float;
  auto GetCurrentStep() const -> float;
  void Increment();
  auto IsStopped() const -> bool;
  void Reset(float t = 0.0);

private:
  const StepType m_stepType;
  float m_stepSize;
  float m_currentStep;
  float m_t{};
};

inline TValue::TValue(TValue::StepType stepType, const float stepSize) noexcept
  : m_stepType{stepType}, m_stepSize{stepSize}, m_currentStep{m_stepSize}
{
}

inline TValue::TValue(TValue::StepType stepType, const uint32_t numSteps) noexcept
  : m_stepType{stepType}, m_stepSize{1.0F / static_cast<float>(numSteps)}, m_currentStep{m_stepSize}
{
}

inline auto TValue::GetStepType() const -> StepType
{
  return m_stepType;
}

inline auto TValue::GetStepSize() const -> float
{
  return m_stepSize;
}

inline auto TValue::operator()() const -> float
{
  return m_t;
}

inline auto TValue::GetCurrentStep() const -> float
{
  return m_currentStep;
}

inline auto TValue::IsStopped() const -> bool
{
  if (m_stepType != StepType::SINGLE_CYCLE)
  {
    return false;
  }
  return m_t >= MAX_T_VALUE;
}

inline void TValue::Reset(const float t)
{
  m_t = t;
  m_currentStep = m_stepSize;
}

#if __cplusplus <= 201402L
} // namespace UTILS
} // namespace GOOM
#else
} // namespace GOOM::UTILS
#endif
#endif //VISUALIZATION_GOOM_T_VALUES_H
