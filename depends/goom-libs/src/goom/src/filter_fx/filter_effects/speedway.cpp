#include "speedway.h"

#include "goom_config.h"
#include "filter_fx/common_types.h"
#include "utils/name_value_pairs.h"

namespace GOOM::FILTER_FX::FILTER_EFFECTS
{

using UTILS::NameValuePairs;
using UTILS::MATH::IGoomRand;

static constexpr auto X_DEFAULT_AMPLITUDE = 4.0F;
static constexpr auto Y_DEFAULT_AMPLITUDE = 1.0F;
static constexpr auto AMPLITUDE_RANGE     = AmplitudeRange{
        {+01.0F, +08.0F},
        {-10.0F, +10.0F},
};

static constexpr auto PROB_AMPLITUDE_EQUAL = 0.5F;

Speedway::Speedway(const Modes mode, const IGoomRand& goomRand) noexcept
  : m_mode{mode}, m_goomRand{goomRand}, m_params{X_DEFAULT_AMPLITUDE, Y_DEFAULT_AMPLITUDE}
{
}

auto Speedway::SetRandomParams() noexcept -> void
{
  switch (m_mode)
  {
    case Modes::MODE0:
      SetMode0RandomParams();
      break;
    case Modes::MODE1:
      SetMode1RandomParams();
      break;
    case Modes::MODE2:
      SetMode2RandomParams();
      break;
    default:
      FailFast();
  }
}

auto Speedway::SetMode0RandomParams() noexcept -> void
{
  const auto xAmplitude = m_goomRand.GetRandInRange(AMPLITUDE_RANGE.xRange);
  const auto yAmplitude = m_goomRand.ProbabilityOf(PROB_AMPLITUDE_EQUAL) ? +1.0F : -1.0F;

  SetParams({xAmplitude, yAmplitude});
}

auto Speedway::SetMode1RandomParams() noexcept -> void
{
  const auto xAmplitude = m_goomRand.GetRandInRange(AMPLITUDE_RANGE.xRange);
  const auto yAmplitude = m_goomRand.ProbabilityOf(PROB_AMPLITUDE_EQUAL)
                              ? xAmplitude
                              : m_goomRand.GetRandInRange(AMPLITUDE_RANGE.yRange);

  SetParams({xAmplitude, yAmplitude});
}

auto Speedway::SetMode2RandomParams() noexcept -> void
{
  const auto xAmplitude = m_goomRand.GetRandInRange(AMPLITUDE_RANGE.xRange);
  const auto yAmplitude = m_goomRand.ProbabilityOf(PROB_AMPLITUDE_EQUAL)
                              ? xAmplitude
                              : m_goomRand.GetRandInRange(AMPLITUDE_RANGE.yRange);

  SetParams({xAmplitude, yAmplitude});

  Ensures(GetZoomInCoefficientsViewport().GetViewportWidth() == NormalizedCoords::COORD_WIDTH);
}

auto Speedway::GetZoomInCoefficientsEffectNameValueParams() const noexcept -> NameValuePairs
{
  return NameValuePairs();
}

} // namespace GOOM::FILTER_FX::FILTER_EFFECTS
