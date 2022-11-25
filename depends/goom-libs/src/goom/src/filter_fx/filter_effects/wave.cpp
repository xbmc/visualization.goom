#include "wave.h"

#include "goom_config.h"
#include "utils/name_value_pairs.h"

namespace GOOM::FILTER_FX::FILTER_EFFECTS
{

using UTILS::NameValuePairs;
using UTILS::MATH::IGoomRand;

static constexpr auto DEFAULT_WAVE_EFFECT  = Wave::WaveEffect::WAVE_SIN_EFFECT;
static constexpr auto DEFAULT_ANGLE_EFFECT = Wave::AngleEffect::SQ_DIST;

static constexpr auto DEFAULT_SQ_DIST_POWER = 1.0F;
static constexpr auto SQ_DIST_POWER_RANGE   = IGoomRand::NumberRange<float>{0.15F, 1.1F};

static constexpr auto DEFAULT_PERIODIC_FACTOR         = 1.0F;
static constexpr auto DEFAULT_SIN_COS_PERIODIC_FACTOR = 0.5F;
static constexpr auto PERIODIC_FACTOR_RANGE           = IGoomRand::NumberRange<float>{0.5F, 1.0F};
static constexpr auto SIN_COS_PERIODIC_FACTOR_RANGE   = IGoomRand::NumberRange<float>{0.1F, 0.9F};

static constexpr auto DEFAULT_FREQ_FACTOR = 20.0F;
static constexpr auto FREQ_FACTOR_RANGE   = IGoomRand::NumberRange<float>{1.0F, 50.0F};

static constexpr auto DEFAULT_AMPLITUDE = 0.01F;
static constexpr auto AMPLITUDE_RANGE   = IGoomRand::NumberRange<float>{0.001F, 0.25F};

static constexpr auto DEFAULT_REDUCER_COEFF   = 1.0F;
static constexpr auto REDUCER_COEFF_RANGE     = IGoomRand::NumberRange<float>{0.95F, 1.5F};
static constexpr auto TAN_REDUCER_COEFF_RANGE = IGoomRand::NumberRange<float>{4.0F, 10.0F};

// These give weird but interesting wave results
static constexpr auto SMALL_FREQ_FACTOR_RANGE   = IGoomRand::NumberRange<float>{0.001F, 0.1F};
static constexpr auto BIG_AMPLITUDE_RANGE       = IGoomRand::NumberRange<float>{1.0F, 50.0F};
static constexpr auto BIG_PERIODIC_FACTOR_RANGE = IGoomRand::NumberRange<float>{50.0F, 100.0F};
static constexpr auto BIG_SIN_COS_PERIODIC_FACTOR_RANGE =
    IGoomRand::NumberRange<float>{10.0F, 90.0F};

static constexpr auto PROB_ALLOW_STRANGE_WAVE_VALUES          = 0.1F;
static constexpr auto PROB_WAVE_XY_EFFECTS_EQUAL              = 0.75F;
static constexpr auto PROB_NO_PERIODIC_FACTOR                 = 0.2F;
static constexpr auto PROB_PERIODIC_FACTOR_USES_X_WAVE_EFFECT = 0.9F;
static constexpr auto PROB_ATAN_ANGLE_EFFECT                  = 0.5F;

static constexpr auto WAVE_SIN_EFFECT_WEIGHT      = 200.0F;
static constexpr auto WAVE_COS_EFFECT_WEIGHT      = 200.0F;
static constexpr auto WAVE_SIN_COS_EFFECT_WEIGHT  = 150.0F;
static constexpr auto WAVE_TAN_EFFECT_WEIGHT      = 010.0F;
static constexpr auto WAVE_TAN_SIN_EFFECT_WEIGHT  = 010.0F;
static constexpr auto CWAVE_TAN_COS_EFFECT_WEIGHT = 010.0F;
static constexpr auto WAVE_COT_EFFECT_WEIGHT      = 001.0F;
static constexpr auto WAVE_COT_SIN_EFFECT_WEIGHT  = 001.0F;
static constexpr auto WAVE_COT_COS_EFFECT_WEIGHT  = 001.0F;


Wave::Wave(const Modes mode, const IGoomRand& goomRand)
  : m_mode{mode},
    m_goomRand{goomRand},
    m_weightedEffects{
      goomRand,
      {
        {    WaveEffect::WAVE_SIN_EFFECT,      WAVE_SIN_EFFECT_WEIGHT},
        {    WaveEffect::WAVE_COS_EFFECT,      WAVE_COS_EFFECT_WEIGHT},
        {WaveEffect::WAVE_SIN_COS_EFFECT,  WAVE_SIN_COS_EFFECT_WEIGHT},
        {    WaveEffect::WAVE_TAN_EFFECT,      WAVE_TAN_EFFECT_WEIGHT},
        {WaveEffect::WAVE_TAN_SIN_EFFECT,  WAVE_TAN_SIN_EFFECT_WEIGHT},
        {WaveEffect::WAVE_TAN_COS_EFFECT, CWAVE_TAN_COS_EFFECT_WEIGHT},
        {    WaveEffect::WAVE_COT_EFFECT,      WAVE_COT_EFFECT_WEIGHT},
        {WaveEffect::WAVE_COT_SIN_EFFECT,  WAVE_COT_SIN_EFFECT_WEIGHT},
        {WaveEffect::WAVE_COT_COS_EFFECT,  WAVE_COT_COS_EFFECT_WEIGHT},
      }
    },
    m_params{DEFAULT_WAVE_EFFECT,
             DEFAULT_WAVE_EFFECT,
             DEFAULT_ANGLE_EFFECT,
             DEFAULT_SQ_DIST_POWER,
             DEFAULT_FREQ_FACTOR,
             DEFAULT_AMPLITUDE,
             DEFAULT_PERIODIC_FACTOR,
             DEFAULT_REDUCER_COEFF}
{
}

auto Wave::SetRandomParams() noexcept -> void
{
  if (m_mode == Modes::MODE0)
  {
    SetMode0RandomParams();
  }
  else
  {
    SetMode1RandomParams();
  }
}

auto Wave::SetMode0RandomParams() noexcept -> void
{
  SetWaveModeSettings(
      FREQ_FACTOR_RANGE, AMPLITUDE_RANGE, PERIODIC_FACTOR_RANGE, SIN_COS_PERIODIC_FACTOR_RANGE);
}

auto Wave::SetMode1RandomParams() noexcept -> void
{
  if (m_goomRand.ProbabilityOf(PROB_ALLOW_STRANGE_WAVE_VALUES))
  {
    SetWaveModeSettings(SMALL_FREQ_FACTOR_RANGE,
                        BIG_AMPLITUDE_RANGE,
                        BIG_PERIODIC_FACTOR_RANGE,
                        BIG_SIN_COS_PERIODIC_FACTOR_RANGE);
  }
  else
  {
    SetWaveModeSettings(
        FREQ_FACTOR_RANGE, AMPLITUDE_RANGE, PERIODIC_FACTOR_RANGE, SIN_COS_PERIODIC_FACTOR_RANGE);
  }
}

auto Wave::SetWaveModeSettings(
    const IGoomRand::NumberRange<float>& freqFactorRange,
    const IGoomRand::NumberRange<float>& amplitudeRange,
    const IGoomRand::NumberRange<float>& periodicFactorRange,
    const IGoomRand::NumberRange<float>& sinCosPeriodicFactorRange) noexcept -> void
{
  const auto waveEffectsEqual = m_goomRand.ProbabilityOf(PROB_WAVE_XY_EFFECTS_EQUAL);

  const auto xWaveEffect = m_weightedEffects.GetRandomWeighted();
  const auto yWaveEffect = waveEffectsEqual ? xWaveEffect : m_weightedEffects.GetRandomWeighted();

  const auto angleEffect = m_goomRand.ProbabilityOf(PROB_ATAN_ANGLE_EFFECT)
                               ? Wave::AngleEffect::ATAN
                               : Wave::AngleEffect::SQ_DIST;
  const auto sqDistPower = m_goomRand.GetRandInRange(SQ_DIST_POWER_RANGE);

  const auto periodicFactor =
      GetPeriodicFactor(xWaveEffect, yWaveEffect, periodicFactorRange, sinCosPeriodicFactorRange);
  const auto freqFactor   = m_goomRand.GetRandInRange(freqFactorRange);
  const auto amplitude    = m_goomRand.GetRandInRange(amplitudeRange);
  const auto reducerCoeff = GetReducerCoeff(xWaveEffect, yWaveEffect, periodicFactor);

  SetParams({xWaveEffect,
             yWaveEffect,
             angleEffect,
             sqDistPower,
             freqFactor,
             amplitude,
             periodicFactor,
             reducerCoeff});

  Ensures(GetZoomInCoefficientsViewport().GetViewportWidth() == NormalizedCoords::COORD_WIDTH);
}

inline auto Wave::GetReducerCoeff(const WaveEffect xWaveEffect,
                                  [[maybe_unused]] const WaveEffect yWaveEffect,
                                  const float periodicFactor) const noexcept -> float
{
  switch (xWaveEffect)
  {
    case WaveEffect::WAVE_SIN_EFFECT:
    case WaveEffect::WAVE_COS_EFFECT:
    case WaveEffect::WAVE_SIN_COS_EFFECT:
      return m_goomRand.GetRandInRange(REDUCER_COEFF_RANGE);
    case WaveEffect::WAVE_TAN_EFFECT:
    case WaveEffect::WAVE_COT_EFFECT:
      return m_goomRand.GetRandInRange(TAN_REDUCER_COEFF_RANGE);
    case WaveEffect::WAVE_TAN_SIN_EFFECT:
    case WaveEffect::WAVE_TAN_COS_EFFECT:
    case WaveEffect::WAVE_COT_SIN_EFFECT:
    case WaveEffect::WAVE_COT_COS_EFFECT:
      return STD20::lerp(m_goomRand.GetRandInRange(TAN_REDUCER_COEFF_RANGE),
                         m_goomRand.GetRandInRange(REDUCER_COEFF_RANGE),
                         periodicFactor);
    default:
      FailFast();
      return 0.0F;
  }
}

inline auto Wave::GetPeriodicFactor(
    const WaveEffect xWaveEffect,
    const WaveEffect yWaveEffect,
    const IGoomRand::NumberRange<float>& periodicFactorRange,
    const IGoomRand::NumberRange<float>& sinCosPeriodicFactorRange) const noexcept -> float
{
  if (m_goomRand.ProbabilityOf(PROB_NO_PERIODIC_FACTOR))
  {
    return xWaveEffect == WaveEffect::WAVE_SIN_COS_EFFECT ? DEFAULT_SIN_COS_PERIODIC_FACTOR
                                                          : DEFAULT_PERIODIC_FACTOR;
  }
  if (m_goomRand.ProbabilityOf(PROB_PERIODIC_FACTOR_USES_X_WAVE_EFFECT))
  {
    return m_goomRand.GetRandInRange(xWaveEffect == WaveEffect::WAVE_SIN_COS_EFFECT
                                         ? sinCosPeriodicFactorRange
                                         : periodicFactorRange);
  }

  return m_goomRand.GetRandInRange(yWaveEffect == WaveEffect::WAVE_SIN_COS_EFFECT
                                       ? sinCosPeriodicFactorRange
                                       : periodicFactorRange);
}

auto Wave::GetPeriodicPart(const WaveEffect waveEffect,
                           const float angle,
                           const float periodicFactor) noexcept -> float
{
  switch (waveEffect)
  {
    case WaveEffect::WAVE_SIN_EFFECT:
      return periodicFactor * std::sin(angle);
    case WaveEffect::WAVE_COS_EFFECT:
      return periodicFactor * std::cos(angle);
    case WaveEffect::WAVE_SIN_COS_EFFECT:
      return periodicFactor * STD20::lerp(std::sin(angle), std::cos(angle), periodicFactor);
    case WaveEffect::WAVE_TAN_EFFECT:
      return periodicFactor * std::tan(angle);
    case WaveEffect::WAVE_TAN_SIN_EFFECT:
      return periodicFactor * STD20::lerp(std::tan(angle), std::sin(angle), periodicFactor);
    case WaveEffect::WAVE_TAN_COS_EFFECT:
      return periodicFactor * STD20::lerp(std::tan(angle), std::cos(angle), periodicFactor);
    case WaveEffect::WAVE_COT_EFFECT:
      return periodicFactor * std::tan(UTILS::MATH::HALF_PI - angle);
    case WaveEffect::WAVE_COT_SIN_EFFECT:
      return periodicFactor *
             STD20::lerp(std::tan(UTILS::MATH::HALF_PI - angle), std::sin(angle), periodicFactor);
    case WaveEffect::WAVE_COT_COS_EFFECT:
      return periodicFactor *
             STD20::lerp(std::tan(UTILS::MATH::HALF_PI - angle), std::cos(angle), periodicFactor);
    default:
      FailFast();
      return 0.0F;
  }
}

auto Wave::GetZoomInCoefficientsEffectNameValueParams() const noexcept -> NameValuePairs
{
  return NameValuePairs();
}

} // namespace GOOM::FILTER_FX::FILTER_EFFECTS
