#include "t_values.h"

#include "mathutils.h"

#undef NDEBUG
#include <cassert>

#if __cplusplus <= 201402L
namespace GOOM
{
namespace UTILS
{
#else
namespace GOOM::UTILS
{
#endif

void TValue::SetStepSize(const float val)
{
  assert(val >= 0.0F);
  m_stepSize = val;
  m_currentStep = m_currentStep < 0.0 ? -m_stepSize : +m_stepSize;
}

void TValue::Increment()
{
  switch (m_stepType)
  {
    case StepType::SINGLE_CYCLE:
      if (m_t > 1.0 + SMALL_FLOAT)
      {
        return;
      }
      m_t += m_currentStep;
      break;
    case StepType::CONTINUOUS_REPEATABLE:
      m_t += m_currentStep;
      if (m_t > 1.0 + SMALL_FLOAT)
      {
        m_t = 0.0;
        return;
      }
      break;
    case StepType::CONTINUOUS_REVERSIBLE:
      m_t += m_currentStep;
      if (m_t > 1.0 + SMALL_FLOAT)
      {
        m_t = 1.0;
        m_currentStep = -m_stepSize;
        assert(m_currentStep <= 0.0);
      }
      else if (m_t < 0.0 - SMALL_FLOAT)
      {
        m_t = 0.0;
        m_currentStep = +m_stepSize;
        assert(m_currentStep >= 0.0);
      }
      break;
  }
}

#if __cplusplus <= 201402L
} // namespace UTILS
} // namespace GOOM
#else
} // namespace GOOM::UTILS
#endif
