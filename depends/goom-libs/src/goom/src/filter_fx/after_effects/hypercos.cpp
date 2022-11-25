#include "hypercos.h"

#include "filter_fx/common_types.h"
#include "goom_config.h"
#include "utils/enum_utils.h"
#include "utils/math/misc.h"
#include "utils/name_value_pairs.h"

namespace GOOM::FILTER_FX::AFTER_EFFECTS
{

using UTILS::GetFullParamGroup;
using UTILS::GetPair;
using UTILS::NameValuePairs;
using UTILS::NUM;
using UTILS::MATH::IGoomRand;
using UTILS::MATH::PI;

// Hypercos:
// applique une surcouche de hypercos effect
// applies an overlay of hypercos effect
static constexpr auto DEFAULT_OVERLAY = HypercosOverlay::NONE;
static constexpr auto DEFAULT_EFFECT  = Hypercos::HypercosEffect::NONE;
static constexpr auto DEFAULT_REVERSE = false;

static constexpr auto X_DEFAULT_FREQUENCY_FACTOR = 10.0F;
static constexpr auto Y_DEFAULT_FREQUENCY_FACTOR = 10.0F;
static constexpr auto FREQUENCY_FACTOR_RANGE     = IGoomRand::NumberRange<float>{5.0F, 100.0F};
static constexpr auto BIG_FREQUENCY_FACTOR_RANGE = IGoomRand::NumberRange<float>{5.0F, 500.0F};
static constexpr auto VERY_BIG_FREQUENCY_FACTOR_RANGE =
    IGoomRand::NumberRange<float>{1000.0F, 10000.0F};

static constexpr auto X_DEFAULT_AMPLITUDE = 1.0F / 120.0F;
static constexpr auto Y_DEFAULT_AMPLITUDE = 1.0F / 120.0F;
static constexpr auto AMPLITUDE_RANGE =
    IGoomRand::NumberRange<float>{0.1F * X_DEFAULT_AMPLITUDE, 1.1F * X_DEFAULT_AMPLITUDE};
static constexpr auto BIG_AMPLITUDE_RANGE =
    IGoomRand::NumberRange<float>{0.1F * X_DEFAULT_AMPLITUDE, 10.1F * X_DEFAULT_AMPLITUDE};

static constexpr auto PROB_FREQUENCY_FACTORS_EQUAL = 0.5F;
static constexpr auto PROB_REVERSE                 = 0.5F;
static constexpr auto PROB_AMPLITUDES_EQUAL        = 0.5F;
static constexpr auto PROB_BIG_AMPLITUDE_RANGE     = 0.2F;

// clang-format off
static constexpr auto DEFAULT_PARAMS = Hypercos::Params{
    DEFAULT_OVERLAY,
    DEFAULT_EFFECT,
    DEFAULT_REVERSE,
    {X_DEFAULT_FREQUENCY_FACTOR, Y_DEFAULT_FREQUENCY_FACTOR},
    {X_DEFAULT_AMPLITUDE, Y_DEFAULT_AMPLITUDE}
};
// clang-format on

static constexpr auto HYPERCOS_EFFECT_NONE_WEIGHT               = 00.0F;
static constexpr auto HYPERCOS_EFFECT_SIN_CURL_SWIRL_WEIGHT     = 15.0F;
static constexpr auto HYPERCOS_EFFECT_COS_CURL_SWIRL_WEIGHT     = 15.0F;
static constexpr auto HYPERCOS_EFFECT_SIN_COS_CURL_SWIRL_WEIGHT = 15.0F;
static constexpr auto HYPERCOS_EFFECT_COS_SIN_CURL_SWIRL_WEIGHT = 15.0F;
static constexpr auto HYPERCOS_EFFECT_SIN_TAN_CURL_SWIRL_WEIGHT = 05.0F;
static constexpr auto HYPERCOS_EFFECT_COS_TAN_CURL_SWIRL_WEIGHT = 05.0F;
static constexpr auto HYPERCOS_EFFECT_SIN_RECTANGULAR_WEIGHT    = 05.0F;
static constexpr auto HYPERCOS_EFFECT_COS_RECTANGULAR_WEIGHT    = 05.0F;
static constexpr auto HYPERCOS_EFFECT_SIN_OF_COS_SWIRL_WEIGHT   = 15.0F;
static constexpr auto HYPERCOS_EFFECT_COS_OF_SIN_SWIRL_WEIGHT   = 15.0F;

Hypercos::Hypercos(const IGoomRand& goomRand) noexcept
  : m_goomRand{goomRand},
    m_params{DEFAULT_PARAMS},
    m_hypercosOverlayWeights{
        m_goomRand,
        {
            { HypercosEffect::NONE,               HYPERCOS_EFFECT_NONE_WEIGHT },
            { HypercosEffect::SIN_CURL_SWIRL,     HYPERCOS_EFFECT_SIN_CURL_SWIRL_WEIGHT },
            { HypercosEffect::COS_CURL_SWIRL,     HYPERCOS_EFFECT_COS_CURL_SWIRL_WEIGHT },
            { HypercosEffect::SIN_COS_CURL_SWIRL, HYPERCOS_EFFECT_SIN_COS_CURL_SWIRL_WEIGHT },
            { HypercosEffect::COS_SIN_CURL_SWIRL, HYPERCOS_EFFECT_COS_SIN_CURL_SWIRL_WEIGHT },
            { HypercosEffect::SIN_TAN_CURL_SWIRL, HYPERCOS_EFFECT_SIN_TAN_CURL_SWIRL_WEIGHT },
            { HypercosEffect::COS_TAN_CURL_SWIRL, HYPERCOS_EFFECT_COS_TAN_CURL_SWIRL_WEIGHT },
            { HypercosEffect::SIN_RECTANGULAR,    HYPERCOS_EFFECT_SIN_RECTANGULAR_WEIGHT },
            { HypercosEffect::COS_RECTANGULAR,    HYPERCOS_EFFECT_COS_RECTANGULAR_WEIGHT },
            { HypercosEffect::SIN_OF_COS_SWIRL,   HYPERCOS_EFFECT_SIN_OF_COS_SWIRL_WEIGHT },
            { HypercosEffect::COS_OF_SIN_SWIRL,   HYPERCOS_EFFECT_COS_OF_SIN_SWIRL_WEIGHT },
        }
    }
{
}

auto Hypercos::SetDefaultParams() -> void
{
  SetParams(DEFAULT_PARAMS);
}

auto Hypercos::SetMode0RandomParams() -> void
{
  const auto hypercosMax =
      STD20::lerp(FREQUENCY_FACTOR_RANGE.min, FREQUENCY_FACTOR_RANGE.max, 0.15F);

  SetHypercosEffect(
      HypercosOverlay::MODE0, {FREQUENCY_FACTOR_RANGE.min, hypercosMax}, AMPLITUDE_RANGE);
}

auto Hypercos::SetMode1RandomParams() -> void
{
  const auto hypercosMin =
      STD20::lerp(FREQUENCY_FACTOR_RANGE.min, FREQUENCY_FACTOR_RANGE.max, 0.20F);

  SetHypercosEffect(
      HypercosOverlay::MODE1, {hypercosMin, FREQUENCY_FACTOR_RANGE.max}, AMPLITUDE_RANGE);
}

auto Hypercos::SetMode2RandomParams() -> void
{
  const auto amplitudeRange =
      m_goomRand.ProbabilityOf(PROB_BIG_AMPLITUDE_RANGE) ? BIG_AMPLITUDE_RANGE : AMPLITUDE_RANGE;

  const auto hypercosMin =
      STD20::lerp(FREQUENCY_FACTOR_RANGE.min, FREQUENCY_FACTOR_RANGE.max, 0.50F);

  SetHypercosEffect(
      HypercosOverlay::MODE2, {hypercosMin, BIG_FREQUENCY_FACTOR_RANGE.max}, amplitudeRange);
}

auto Hypercos::SetMode3RandomParams() -> void
{
  SetHypercosEffect(HypercosOverlay::MODE3, VERY_BIG_FREQUENCY_FACTOR_RANGE, AMPLITUDE_RANGE);
}

auto Hypercos::SetHypercosEffect(const HypercosOverlay overlay,
                                 const IGoomRand::NumberRange<float>& freqRange,
                                 const IGoomRand::NumberRange<float>& amplitudeRange) -> void
{
  const auto xFrequencyFactor = m_goomRand.GetRandInRange(freqRange);
  const auto yFrequencyFactor = m_goomRand.ProbabilityOf(PROB_FREQUENCY_FACTORS_EQUAL)
                                    ? xFrequencyFactor
                                    : m_goomRand.GetRandInRange(freqRange);

  const auto reverse = m_goomRand.ProbabilityOf(PROB_REVERSE);

  const auto xAmplitude = m_goomRand.GetRandInRange(amplitudeRange);
  const auto yAmplitude = m_goomRand.ProbabilityOf(PROB_AMPLITUDES_EQUAL)
                              ? xAmplitude
                              : m_goomRand.GetRandInRange(amplitudeRange);

  SetParams({
      overlay,
      m_hypercosOverlayWeights.GetRandomWeighted(),
      reverse,
      {xFrequencyFactor, yFrequencyFactor},
      {      xAmplitude,       yAmplitude}
  });
}

inline auto Hypercos::GetFrequencyFactorToUse(const float frequencyFactor) const -> float
{
  return m_params.reverse ? -frequencyFactor : +frequencyFactor;
}

auto Hypercos::GetVelocity(const NormalizedCoords& coords, const NormalizedCoords& velocity) const
    -> NormalizedCoords
{
  const auto xFrequencyFactorToUse = GetFrequencyFactorToUse(m_params.frequencyFactor.x);
  const auto yFrequencyFactorToUse = GetFrequencyFactorToUse(m_params.frequencyFactor.y);

  return velocity +
         GetVelocity(coords, m_params.effect, {xFrequencyFactorToUse, yFrequencyFactorToUse});
}

auto Hypercos::GetVelocity(const NormalizedCoords& coords,
                           const HypercosEffect effect,
                           const FrequencyFactor& frequencyFactorToUse) const -> NormalizedCoords
{
  auto xVal = 0.0F;
  auto yVal = 0.0F;

  switch (effect)
  {
    case HypercosEffect::NONE:
      break;
    case HypercosEffect::SIN_RECTANGULAR:
      xVal = std::sin(frequencyFactorToUse.x * coords.GetX());
      yVal = std::sin(frequencyFactorToUse.y * coords.GetY());
      break;
    case HypercosEffect::COS_RECTANGULAR:
      xVal = std::cos(frequencyFactorToUse.x * coords.GetX());
      yVal = std::cos(frequencyFactorToUse.y * coords.GetY());
      break;
    case HypercosEffect::SIN_CURL_SWIRL:
      xVal = std::sin(frequencyFactorToUse.y * coords.GetY());
      yVal = std::sin(frequencyFactorToUse.x * coords.GetX());
      break;
    case HypercosEffect::COS_CURL_SWIRL:
      xVal = std::cos(frequencyFactorToUse.y * coords.GetY());
      yVal = std::cos(frequencyFactorToUse.x * coords.GetX());
      break;
    case HypercosEffect::SIN_COS_CURL_SWIRL:
      xVal = std::sin(frequencyFactorToUse.x * coords.GetY());
      yVal = std::cos(frequencyFactorToUse.y * coords.GetX());
      break;
    case HypercosEffect::COS_SIN_CURL_SWIRL:
      xVal = std::cos(frequencyFactorToUse.y * coords.GetY());
      yVal = std::sin(frequencyFactorToUse.x * coords.GetX());
      break;
    case HypercosEffect::SIN_TAN_CURL_SWIRL:
      xVal = std::sin(std::tan(frequencyFactorToUse.y * coords.GetY()));
      yVal = std::cos(std::tan(frequencyFactorToUse.x * coords.GetX()));
      break;
    case HypercosEffect::COS_TAN_CURL_SWIRL:
      xVal = std::cos(std::tan(frequencyFactorToUse.y * coords.GetY()));
      yVal = std::sin(std::tan(frequencyFactorToUse.x * coords.GetX()));
      break;
    case HypercosEffect::SIN_OF_COS_SWIRL:
      xVal = std::sin(PI * std::cos(frequencyFactorToUse.y * coords.GetY()));
      yVal = std::cos(PI * std::sin(frequencyFactorToUse.x * coords.GetX()));
      break;
    case HypercosEffect::COS_OF_SIN_SWIRL:
      xVal = std::cos(PI * std::sin(frequencyFactorToUse.y * coords.GetY()));
      yVal = std::sin(PI * std::cos(frequencyFactorToUse.x * coords.GetX()));
      break;
    default:
      FailFast();
      return NormalizedCoords{0.0F, 0.0F};
  }

  //  xVal = std::clamp(std::tan(hypercosFreqY * xVal), -1.0, 1.0);
  //  yVal = std::clamp(std::tan(hypercosFreqX * yVal), -1.0, 1.0);

  xVal *= m_params.amplitude.x;
  yVal *= m_params.amplitude.y;

  return {xVal, yVal};
}

auto Hypercos::GetNameValueParams(const std::string& paramGroup) const -> NameValuePairs
{
  const auto fullParamGroup = GetFullParamGroup({paramGroup, "hypercos"});

  if (m_params.overlay == HypercosOverlay::NONE)
  {
    return {GetPair(fullParamGroup, "overlay", std::string{"None"})};
  }

  return {
      GetPair(fullParamGroup, "overlay", static_cast<uint32_t>(m_params.overlay)),
      GetPair(fullParamGroup, "effect", static_cast<uint32_t>(m_params.effect)),
      GetPair(fullParamGroup, "reverse", m_params.reverse),
      GetPair(fullParamGroup,
              "Freq",
              Point2dFlt{m_params.frequencyFactor.x, m_params.frequencyFactor.y}),
      GetPair(fullParamGroup, "Amplitude", Point2dFlt{m_params.amplitude.x, m_params.amplitude.y}),
  };
}

} // namespace GOOM::FILTER_FX::AFTER_EFFECTS
