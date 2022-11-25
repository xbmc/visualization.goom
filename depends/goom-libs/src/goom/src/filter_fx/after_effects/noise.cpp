#include "noise.h"

#include "utils/name_value_pairs.h"

namespace GOOM::FILTER_FX::AFTER_EFFECTS
{

using UTILS::GetFullParamGroup;
using UTILS::GetPair;
using UTILS::NameValuePairs;
using UTILS::MATH::IGoomRand;

static constexpr auto DEFAULT_NOISE_FACTOR = 0.01F;
static constexpr auto NOISE_FACTOR_RANGE   = IGoomRand::NumberRange<float>{0.001F, 0.100F};

Noise::Noise(const IGoomRand& goomRand) noexcept
  : m_goomRand{goomRand}, m_params{DEFAULT_NOISE_FACTOR}
{
}

auto Noise::SetRandomParams() -> void
{
  SetParams({m_goomRand.GetRandInRange(NOISE_FACTOR_RANGE)});
}

auto Noise::GetNameValueParams(const std::string& paramGroup) const -> NameValuePairs
{
  const auto fullParamGroup = GetFullParamGroup({paramGroup, "noise"});
  return {
      GetPair(fullParamGroup, "noise factor", m_params.noiseFactor),
  };
}

} // namespace GOOM::FILTER_FX::AFTER_EFFECTS
