#include "catch2/catch.hpp"
#include "utils/math/misc.h"
#include "utils/t_values.h"

#include <vector>

namespace GOOM::UNIT_TESTS
{

using UTILS::TValue;
using UTILS::MATH::SMALL_FLOAT;

TEST_CASE("TValue SINGLE_CYCLE")
{
  static constexpr uint32_t NUM_STEPS = 10;
  TValue tValue{TValue::StepType::SINGLE_CYCLE, NUM_STEPS};

  static constexpr float STEP_SIZE = 1.0F / static_cast<float>(NUM_STEPS);
  REQUIRE(tValue.GetStepSize() == Approx(STEP_SIZE));

  // Zero steps
  REQUIRE(tValue() == Approx(0.0F));

  // One step
  tValue.Increment();
  REQUIRE(tValue() == Approx(STEP_SIZE));

  while (!tValue.IsStopped())
  {
    tValue.Increment();
  }
  REQUIRE(tValue() >= 1.0F);
}

TEST_CASE("TValue CONTINUOUS_REPEATABLE")
{
  static constexpr uint32_t NUM_STEPS = 10;
  TValue tValue{TValue::StepType::CONTINUOUS_REPEATABLE, NUM_STEPS};

  static constexpr float STEP_SIZE = 1.0F / static_cast<float>(NUM_STEPS);
  REQUIRE(tValue.GetStepSize() == Approx(STEP_SIZE));

  // Zero steps
  REQUIRE(tValue() == Approx(0.0F));

  // One step
  tValue.Increment();
  REQUIRE(tValue() == Approx(STEP_SIZE));

  // Step till 1.0
  for (size_t i = 1; i < NUM_STEPS; ++i)
  {
    tValue.Increment();
  }
  REQUIRE(tValue() == Approx(1.0F));

  // Should go back to start
  tValue.Increment();
  REQUIRE(tValue() == Approx(0.0F));
}

TEST_CASE("TValue CONTINUOUS_REVERSIBLE")
{
  static constexpr uint32_t NUM_STEPS = 10;
  TValue tValue{TValue::StepType::CONTINUOUS_REVERSIBLE, NUM_STEPS};

  static constexpr float STEP_SIZE = 1.0F / static_cast<float>(NUM_STEPS);
  REQUIRE(tValue.GetStepSize() == Approx(STEP_SIZE));

  // Zero steps
  REQUIRE(tValue() == Approx(0.0F));

  // One step
  tValue.Increment();
  REQUIRE(tValue() == Approx(STEP_SIZE));

  // Step till 1.0
  for (size_t i = 1; i < NUM_STEPS; ++i)
  {
    tValue.Increment();
  }
  REQUIRE(tValue() == Approx(1.0F));

  // Back down
  tValue.Increment();
  REQUIRE(tValue() == Approx(1.0F - STEP_SIZE));

  // Keep going down
  for (size_t i = 1; i < NUM_STEPS; ++i)
  {
    tValue.Increment();
  }
  REQUIRE(tValue() == Approx(0.0F).margin(SMALL_FLOAT));

  // Back up
  tValue.Increment();
  REQUIRE(tValue() == Approx(STEP_SIZE));
}

void GotoUpToValue(const float t, TValue& tValue)
{
  while (tValue() < t)
  {
    tValue.Increment();
  }
}

void GotoDownToValue(const float t, TValue& tValue)
{
  while (tValue() > t)
  {
    tValue.Increment();
  }
}

void CheckIsDelayed(TValue& tValue, const uint32_t delayTime, const float delayT)
{
  for (size_t i = 0; i < delayTime; ++i)
  {
    INFO("i: " << i << ", delayTime = " << delayTime << ", delayT = " << delayT);

    REQUIRE(tValue.IsDelayed());

    if (i == (delayTime - 1))
    {
      REQUIRE(tValue.DelayJustFinishing());
    }

    tValue.Increment();
    REQUIRE(tValue() == Approx(delayT).margin(SMALL_FLOAT));
  }
}

TEST_CASE("TValue CONTINUOUS_REPEATABLE with delay")
{
  static constexpr uint32_t NUM_STEPS = 10;
  static constexpr uint32_t T_DELAY_TIME = 6;
  static constexpr float MID_DELAY_T = 0.5F;
  TValue tValue{TValue::StepType::CONTINUOUS_REPEATABLE,
                NUM_STEPS,
                {{0.0F, T_DELAY_TIME}, {MID_DELAY_T, T_DELAY_TIME}, {1.0F, T_DELAY_TIME}}};
  REQUIRE((NUM_STEPS % 2) == 0);
  REQUIRE((T_DELAY_TIME % 2) == 0);

  static constexpr float STEP_SIZE = 1.0F / static_cast<float>(NUM_STEPS);
  REQUIRE(tValue.GetStepSize() == Approx(STEP_SIZE));

  // Zero steps
  REQUIRE(tValue() == Approx(0.0F));

  // Should be delayed here
  tValue.Increment();
  CheckIsDelayed(tValue, T_DELAY_TIME - 1, 0.0F);
  REQUIRE(!tValue.IsDelayed());

  GotoUpToValue(MID_DELAY_T, tValue);
  REQUIRE(tValue() == Approx(MID_DELAY_T));

  // Should be delayed here
  tValue.Increment();
  CheckIsDelayed(tValue, T_DELAY_TIME - 1, MID_DELAY_T);
  REQUIRE(!tValue.IsDelayed());

  // Normal incrementing up
  float val = MID_DELAY_T;
  for (size_t i = 0; i < NUM_STEPS / 2; ++i)
  {
    tValue.Increment();
    val += STEP_SIZE;
    INFO("Step = " << i << " val = " << val);
    REQUIRE(tValue() == Approx(val));
  }

  // Should be delayed here
  tValue.Increment();
  CheckIsDelayed(tValue, T_DELAY_TIME - 1, 1.0F);
  REQUIRE(!tValue.IsDelayed());

  // Back to the start
  tValue.Increment();
  REQUIRE(tValue() == Approx(0.0F));
}

TEST_CASE("TValue CONTINUOUS_REVERSIBLE with delay")
{
  static constexpr uint32_t NUM_STEPS = 10;
  static constexpr uint32_t T_DELAY_TIME = 6;
  static constexpr float MID_DELAY_T = 0.5F;
  TValue tValue{TValue::StepType::CONTINUOUS_REVERSIBLE,
                NUM_STEPS,
                {{0.0F, T_DELAY_TIME}, {MID_DELAY_T, T_DELAY_TIME}, {1.0F, T_DELAY_TIME}}};
  REQUIRE((NUM_STEPS % 2) == 0);
  REQUIRE((T_DELAY_TIME % 2) == 0);
  REQUIRE(tValue() == Approx(0.0F));

  static constexpr float STEP_SIZE = 1.0F / static_cast<float>(NUM_STEPS);
  REQUIRE(tValue.GetStepSize() == Approx(STEP_SIZE));
  REQUIRE(tValue.GetCurrentStep() > 0.0F);

  // Should be delayed here
  tValue.Increment();
  CheckIsDelayed(tValue, T_DELAY_TIME - 1, 0.0F);
  REQUIRE(!tValue.IsDelayed());

  GotoUpToValue(MID_DELAY_T, tValue);
  REQUIRE(tValue() == Approx(MID_DELAY_T));

  // Should be delayed here
  tValue.Increment();
  CheckIsDelayed(tValue, T_DELAY_TIME - 1, MID_DELAY_T);
  REQUIRE(!tValue.IsDelayed());

  // Normal incrementing
  float val = MID_DELAY_T;
  for (size_t i = 0; i < NUM_STEPS / 2; ++i)
  {
    tValue.Increment();
    val += STEP_SIZE;
    REQUIRE(tValue() == Approx(val));
  }

  // Should be delayed here
  tValue.Increment();
  CheckIsDelayed(tValue, T_DELAY_TIME - 1, 1.0F);
  REQUIRE(!tValue.IsDelayed());

  // Back down
  tValue.Increment();
  REQUIRE(tValue.GetCurrentStep() < 0.0F);
  REQUIRE(tValue() == Approx(1.0F - STEP_SIZE));

  GotoDownToValue(MID_DELAY_T, tValue);
  REQUIRE(tValue() == Approx(MID_DELAY_T));

  // Should be delayed here
  tValue.Increment();
  CheckIsDelayed(tValue, T_DELAY_TIME - 1, MID_DELAY_T);
  REQUIRE(!tValue.IsDelayed());

  // Normal incrementing - going down
  val = MID_DELAY_T;
  for (size_t i = 0; i < NUM_STEPS / 2; ++i)
  {
    tValue.Increment();
    val -= STEP_SIZE;
    REQUIRE(tValue() == Approx(val).margin(SMALL_FLOAT));
  }
  REQUIRE(tValue() == Approx(0.0F).margin(SMALL_FLOAT));
  REQUIRE(tValue.GetCurrentStep() < 0.0F);

  // Should be delayed here
  tValue.Increment();
  REQUIRE(tValue() == Approx(0.0F).margin(SMALL_FLOAT));
  REQUIRE(tValue.GetCurrentStep() < 0.0F);
  CheckIsDelayed(tValue, T_DELAY_TIME - 1, 0.0F);
  REQUIRE(!tValue.IsDelayed());

  // Normal incrementing - going back up
  tValue.Increment();
  REQUIRE(tValue.GetCurrentStep() > 0.0F);
  REQUIRE(tValue() == Approx(STEP_SIZE));
}

} // namespace GOOM::UNIT_TESTS
