#include "catch2/catch.hpp"
#include "utils/enum_utils.h"
#include "utils/math/goom_rand.h"

#include <cstdint>
#include <format>
#include <map>
#include <string>

namespace GOOM::UNIT_TESTS
{

using UTILS::EnumToString;
using UTILS::NUM;
using UTILS::MATH::ConditionalWeights;
using UTILS::MATH::GoomRand;
using UTILS::MATH::Weights;

enum class Events
{
  EVENT1,
  EVENT2,
  EVENT3,
  EVENT4,
  _num // unused, and marks the enum end
};
using EventCounts = std::array<uint32_t, NUM<Events>>;

static constexpr size_t NUM_LOOPS = 10000000;
static constexpr double DBL_NUM_LOOPS = NUM_LOOPS;

[[nodiscard]] static auto GetWeightedCounts(const Weights<Events>& weights) -> EventCounts
{
  EventCounts eventCounts{};
  for (size_t i = 0; i < NUM_LOOPS; ++i)
  {
    const Events event = weights.GetRandomWeighted();
    ++eventCounts.at(static_cast<size_t>(event));
  }

  return eventCounts;
}

[[nodiscard]] static auto GetConditionalWeightedCounts(const Events givenEvent,
                                                       const ConditionalWeights<Events>& weights)
    -> EventCounts
{
  EventCounts eventCounts{};
  for (size_t i = 0; i < NUM_LOOPS; ++i)
  {
    const Events event = weights.GetRandomWeighted(givenEvent);
    ++eventCounts.at(static_cast<size_t>(event));
  }

  return eventCounts;
}

TEST_CASE("Weighted Events")
{
  const GoomRand goomRand{};
  const typename Weights<Events>::EventWeightPairs weightPairs = {
      {Events::EVENT1, 05.0F},
      {Events::EVENT2, 02.0F},
      {Events::EVENT3, 10.0F},
      {Events::EVENT4, 06.0F},
  };
  const Weights<Events> weightedEvents{goomRand, weightPairs};
  static constexpr double EXPECTED_SUM = 23.0;

  SECTION("Unconditional weights")
  {
    const auto sumOfWeights = static_cast<double>(weightedEvents.GetSumOfWeights());
    REQUIRE(sumOfWeights == Approx(EXPECTED_SUM));

    const EventCounts eventCounts = GetWeightedCounts(weightedEvents);

    for (size_t i = 0; i < NUM<Events>; ++i)
    {
      const auto fEventCount = static_cast<double>(eventCounts.at(i));
      const auto fEventWeight =
          static_cast<double>(weightedEvents.GetWeight(static_cast<Events>(i)));

      const double countFraction = fEventCount / DBL_NUM_LOOPS;
      const double eventFraction = fEventWeight / sumOfWeights;

      UNSCOPED_INFO(std20::format("i = {}, countFraction = {}, eventFraction = {}", i,
                                  countFraction, eventFraction));
      REQUIRE(countFraction == Approx(eventFraction).epsilon(0.005));
    }
  }

  SECTION("Conditional weights")
  {
    static constexpr Events GIVEN_EVENT = Events::EVENT3;

    const std::map<Events, float> event3WeightMultipliers = {
        {Events::EVENT1, 1.0F},
        {Events::EVENT2, 0.0F},
        {Events::EVENT3, 2.0F},
        {Events::EVENT4, 1.0F},
    };
    const ConditionalWeights<Events>::EventWeightMultiplierPairs weightMultipliers = {
        {GIVEN_EVENT, event3WeightMultipliers}
    };
    const ConditionalWeights<Events> conditionalWeightedEvents{goomRand, weightPairs,
                                                               weightMultipliers};
    const auto conditionalSumOfWeights =
        static_cast<double>(conditionalWeightedEvents.GetSumOfWeights(GIVEN_EVENT));
    static constexpr double EXPECTED_SUM_FOR_GIVEN = 5.0 + 2.0 * 10.0 + 6.0;
    REQUIRE(conditionalSumOfWeights == Approx(EXPECTED_SUM_FOR_GIVEN));

    const EventCounts conditionalEventCounts =
        GetConditionalWeightedCounts(GIVEN_EVENT, conditionalWeightedEvents);

    for (size_t i = 0; i < NUM<Events>; ++i)
    {
      const auto fConditionalEventCount = static_cast<double>(conditionalEventCounts.at(i));
      const double conditionalCountFraction = fConditionalEventCount / DBL_NUM_LOOPS;

      UNSCOPED_INFO(std20::format("i:{}, fConditionalEventCount = {}", i, fConditionalEventCount));
      UNSCOPED_INFO(std20::format("i:{}, NUM_LOOPS = {}", i, NUM_LOOPS));
      UNSCOPED_INFO(
          std20::format("i:{}, conditionalCountFraction = {}", i, conditionalCountFraction));

      const auto fConditionalEventWeight = static_cast<double>(
          conditionalWeightedEvents.GetWeight(GIVEN_EVENT, static_cast<Events>(i)));
      const double conditionalEventFraction = fConditionalEventWeight / conditionalSumOfWeights;
      UNSCOPED_INFO(std20::format("i:{}, fConditionalEventWeight({}) = {}", i,
                                  EnumToString(GIVEN_EVENT), fConditionalEventWeight));
      UNSCOPED_INFO(std20::format("i:{}, conditionalSumOfWeights({}) = {}", i,
                                  EnumToString(GIVEN_EVENT), conditionalSumOfWeights));
      UNSCOPED_INFO(
          std20::format("i:{}, conditionalEventFraction = {}", i, conditionalEventFraction));

      REQUIRE(conditionalCountFraction == Approx(conditionalEventFraction).epsilon(0.005));
    }
  }

  SECTION("DisallowEventsSameAsGiven = true")
  {
    static constexpr Events GIVEN_EVENT = Events::EVENT3;

    const ConditionalWeights<Events> conditionalWeightedEvents{goomRand, weightPairs, true};

    const EventCounts conditionalEventCounts =
        GetConditionalWeightedCounts(GIVEN_EVENT, conditionalWeightedEvents);

    REQUIRE(conditionalEventCounts.at(static_cast<size_t>(GIVEN_EVENT)) == 0);
  }
}

TEST_CASE("Weighted Events Corner Cases")
{
  const GoomRand goomRand{};
  const Weights<Events> weightedEvents{
      goomRand,
      {
        {Events::EVENT1, 0.0F},
        {Events::EVENT2, 1.0F},
        {Events::EVENT3, 0.0F},
        {Events::EVENT4, 0.0F},
        }
  };

  SECTION("Unconditional weights")
  {
    const auto sumOfWeights = static_cast<double>(weightedEvents.GetSumOfWeights());
    REQUIRE(sumOfWeights == Approx(1.0F));

    const EventCounts eventCounts = GetWeightedCounts(weightedEvents);

    for (size_t i = 0; i < NUM<Events>; ++i)
    {
      if (static_cast<Events>(i) != Events::EVENT2)
      {
        REQUIRE(eventCounts.at(i) == 0);
      }
      else
      {
        REQUIRE(eventCounts.at(i) == NUM_LOOPS);
      }
    }
  }
}

/*** Catch2 can't catch 'assert' calls.
TEST_CASE("Weighted Events Exceptions")
{
  const GoomRand goomRand{};

  REQUIRE_THROWS_WITH(Weights<Events>(goomRand, {}).GetNumElements() > 0,
                      "Sum of weights is zero.");

  const typename Weights<Events>::EventWeightPairs weightPairs1 = {
      {Events::EVENT1, 0.0F},
      {Events::EVENT2, 0.0F},
      {Events::EVENT3, 0.0F},
      {Events::EVENT4, 0.0F},
  };
  REQUIRE_THROWS_WITH(Weights<Events>(goomRand, weightPairs1).GetNumElements() > 0,
                      "Sum of weights is zero.");

  const typename Weights<Events>::EventWeightPairs weightPairs2 = {
      {Events::EVENT1, 0.0F},
      {Events::EVENT3, 0.0F},
  };
  REQUIRE_THROWS_WITH(Weights<Events>(goomRand, weightPairs2).GetNumElements() > 0,
                      "Sum of weights is zero.");
}

TEST_CASE("Conditional Weighted Events Exceptions")
{
  const GoomRand goomRand{};

  const typename Weights<Events>::EventWeightPairs weightPairs1 = {
      {Events::EVENT1, 05.0F},
      {Events::EVENT2, 02.0F},
      {Events::EVENT3, 10.0F},
      {Events::EVENT4, 06.0F},
  };
  const std::map<Events, float> event3WeightMultipliers1 = {
      {Events::EVENT1, 0.0F},
      {Events::EVENT2, 0.0F},
      {Events::EVENT3, 0.0F},
      {Events::EVENT4, 0.0F},
  };
  static constexpr Events GIVEN_EVENT = Events::EVENT3;
  const ConditionalWeights<Events>::EventWeightMultiplierPairs weightMultipliers1 = {
      {GIVEN_EVENT, event3WeightMultipliers1}
  };

  REQUIRE_THROWS_WITH(ConditionalWeights<Events>(goomRand, weightPairs1, weightMultipliers1)
                              .GetSumOfWeights(GIVEN_EVENT) > 0,
                      "Sum of weights is zero.");

  const typename Weights<Events>::EventWeightPairs weightPairs2 = {
      {Events::EVENT1, 05.0F},
      {Events::EVENT3, 10.0F},
  };
  const std::map<Events, float> event3WeightMultipliers2 = {
      {Events::EVENT1, 0.0F},
      {Events::EVENT2, 1.0F},
      {Events::EVENT3, 0.0F},
      {Events::EVENT4, 1.0F},
  };
  const ConditionalWeights<Events>::EventWeightMultiplierPairs weightMultipliers2 = {
      {GIVEN_EVENT, event3WeightMultipliers2}
  };

  REQUIRE_THROWS_WITH(ConditionalWeights<Events>(goomRand, weightPairs2, weightMultipliers2)
                              .GetSumOfWeights(GIVEN_EVENT) == 0.0F,
                      "Sum of weights is zero.");
}
***/

} // namespace GOOM::UNIT_TESTS
