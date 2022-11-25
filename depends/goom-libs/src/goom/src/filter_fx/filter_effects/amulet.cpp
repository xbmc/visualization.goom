#include "amulet.h"

#include "goom_config.h"
#include "utils/name_value_pairs.h"

namespace GOOM::FILTER_FX::FILTER_EFFECTS
{

using UTILS::NameValuePairs;
using UTILS::MATH::IGoomRand;

static constexpr auto DEFAULT_AMPLITUDE = 1.0F;
static constexpr auto AMPLITUDE_RANGE   = IGoomRand::NumberRange<float>{0.1F, 1.51F};

static constexpr auto PROB_XY_AMPLITUDES_EQUAL = 0.98F;

Amulet::Amulet(const IGoomRand& goomRand) noexcept
  : m_goomRand{goomRand}, m_params{DEFAULT_AMPLITUDE, DEFAULT_AMPLITUDE}
{
}

auto Amulet::SetRandomParams() noexcept -> void
{
  const auto xAmplitude = m_goomRand.GetRandInRange(AMPLITUDE_RANGE);
  const auto yAmplitude = m_goomRand.ProbabilityOf(PROB_XY_AMPLITUDES_EQUAL)
                              ? xAmplitude
                              : m_goomRand.GetRandInRange(AMPLITUDE_RANGE);

  SetParams({xAmplitude, yAmplitude});

  Ensures(GetZoomInCoefficientsViewport().GetViewportWidth() == NormalizedCoords::COORD_WIDTH);
}

auto Amulet::GetZoomInCoefficientsEffectNameValueParams() const noexcept -> NameValuePairs
{
  return NameValuePairs();
}

} // namespace GOOM::FILTER_FX::FILTER_EFFECTS
