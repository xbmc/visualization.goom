#include "xy_lerp_effect.h"

// #undef NO_LOGGING

#include "logging.h"
#include "utils/enum_utils.h"
#include "utils/name_value_pairs.h"

namespace GOOM::FILTER_FX::AFTER_EFFECTS
{

using UTILS::GetFullParamGroup;
using UTILS::GetPair;
using UTILS::EnumToString;
using UTILS::Logging; // NOLINT(misc-unused-using-decls)
using UTILS::NameValuePairs;
using UTILS::MATH::IGoomRand;

static constexpr auto DEFAULT_T_FREQ   = 1.0F;
static constexpr auto T_FREQ_RANGE     = IGoomRand::NumberRange<float>{1.0F, 10.0F};
static constexpr auto PROB_FLIP_Y_SIGN = 0.5F;
static constexpr auto PROB_FLIP_XY     = 0.5F;

static constexpr auto MODE0_WEIGHT = 10.0F;
static constexpr auto MODE1_WEIGHT = 10.0F;
static constexpr auto MODE2_WEIGHT = 10.0F;
static constexpr auto MODE3_WEIGHT = 10000000000.0F;

XYLerpEffect::XYLerpEffect(const IGoomRand& goomRand)
  : m_goomRand{goomRand},
    m_modeWeights{
        m_goomRand,
        {
            {Modes::MODE0, MODE0_WEIGHT},
            {Modes::MODE1, MODE1_WEIGHT},
            {Modes::MODE2, MODE2_WEIGHT},
            {Modes::MODE3, MODE3_WEIGHT},
        }
    },
    m_params{Modes::MODE0, DEFAULT_T_FREQ, +1.0F, false}
{
}

auto XYLerpEffect::SetRandomParams() -> void
{
  const auto mode  = m_modeWeights.GetRandomWeighted();
  const auto tFreq = m_goomRand.GetRandInRange(T_FREQ_RANGE);
  const auto ySign  = m_goomRand.ProbabilityOf(PROB_FLIP_Y_SIGN) ? -1.0F : +1.0F;
  const auto flipXY = m_goomRand.ProbabilityOf(GetFlipYProbability(mode));

  SetParams({mode, tFreq, ySign, flipXY});
}

inline auto XYLerpEffect::GetFlipYProbability(const Modes mode) -> float
{
  if ((mode == Modes::MODE0) or (mode == Modes::MODE1))
  {
    return 0.0F;
  }

  return PROB_FLIP_XY;
}

auto XYLerpEffect::GetNameValueParams(const std::string& paramGroup) const -> NameValuePairs
{
  const auto fullParamGroup = GetFullParamGroup({paramGroup, "xy lerp effect"});
  return {
      GetPair(fullParamGroup, "mode", EnumToString(m_params.mode)),
      GetPair(fullParamGroup, "tFreq", m_params.tFreq),
      GetPair(fullParamGroup, "ySign", m_params.ySign),
      GetPair(fullParamGroup, "flipXY", m_params.flipXY),
  };
}

} // namespace GOOM::FILTER_FX::AFTER_EFFECTS
