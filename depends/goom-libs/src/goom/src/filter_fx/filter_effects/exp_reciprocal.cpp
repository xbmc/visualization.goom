#include "exp_reciprocal.h"

//#undef NO_LOGGING

#include "filter_fx/normalized_coords.h"
#include "logging.h"
#include "utils/math/misc.h"
#include "utils/name_value_pairs.h"

#include <cmath>
#include <complex>
#include <limits>

namespace GOOM::FILTER_FX::FILTER_EFFECTS
{

using UTILS::GetFullParamGroup;
using UTILS::GetPair;
using UTILS::Logging; // NOLINT(misc-unused-using-decls)
using UTILS::NameValuePairs;
using UTILS::MATH::GetTriangle;
using UTILS::MATH::IGoomRand;
using UTILS::MATH::TWO_PI;

static constexpr auto DEFAULT_VIEWPORT = Viewport{};

static constexpr auto DEFAULT_AMPLITUDE = 0.1F;
static constexpr auto AMPLITUDE_RANGE   = IGoomRand::NumberRange<float>{0.01F, 0.11F};

static constexpr auto DEFAULT_MAGNIFY_AND_ROTATE = std::complex{0.0F, 0.0F};
static constexpr auto ROTATE_RANGE               = IGoomRand::NumberRange<float>{0.0F, TWO_PI};
static constexpr auto MAGNIFY_RANGE              = IGoomRand::NumberRange<float>{0.95F, 1.05F};

static constexpr auto DEFAULT_RECIPROCAL_EXPONENT = 3.0F;
static constexpr auto RECIPROCAL_EXPONENT_RANGE   = IGoomRand::NumberRange<uint32_t>{3, 6};

static constexpr auto DEFAULT_MODULATOR_PERIOD = 2.0F;
static constexpr auto MODULATOR_PERIOD_RANGE   = IGoomRand::NumberRange<float>{1.0F, 100.0F};

static constexpr auto PROB_AMPLITUDES_EQUAL       = 0.95F;
static constexpr auto PROB_NO_INVERSE_SQUARE      = 0.90F;
static constexpr auto PROB_USE_MODULATOR_CONTOURS = 0.01F;

static constexpr auto VIEWPORT_RECTANGLES = std::array{
    Viewport::Rectangle{{-1.99F, -1.99F}, {1.99F, 1.99F}},
    Viewport::Rectangle{{-1.00F, -1.00F}, {1.00F, 1.00F}},
    Viewport::Rectangle{    {0.5F, 0.5F},   {2.0F, 2.0F}},
    Viewport::Rectangle{ {0.30F, -0.10F}, {0.70F, 0.10F}},
};

ExpReciprocal::ExpReciprocal(const IGoomRand& goomRand) noexcept
  : m_goomRand{goomRand},
    m_params{
        DEFAULT_VIEWPORT,
        {DEFAULT_AMPLITUDE, DEFAULT_AMPLITUDE},
        true,
        DEFAULT_MAGNIFY_AND_ROTATE,
        DEFAULT_RECIPROCAL_EXPONENT,
        false,
        DEFAULT_MODULATOR_PERIOD,
    }
{
}

auto ExpReciprocal::SetRandomParams() noexcept -> void
{
  const auto viewport = Viewport{VIEWPORT_RECTANGLES.at(
      m_goomRand.GetRandInRange(0U, static_cast<uint32_t>(VIEWPORT_RECTANGLES.size())))};

  const auto xAmplitude = m_goomRand.GetRandInRange(AMPLITUDE_RANGE);
  const auto yAmplitude = m_goomRand.ProbabilityOf(PROB_AMPLITUDES_EQUAL)
                              ? xAmplitude
                              : m_goomRand.GetRandInRange(AMPLITUDE_RANGE);

  const auto noInverseSquare = m_goomRand.ProbabilityOf(PROB_NO_INVERSE_SQUARE);

  const auto rotate  = std::polar(1.0F, m_goomRand.GetRandInRange(ROTATE_RANGE));
  const auto magnify = m_goomRand.GetRandInRange(MAGNIFY_RANGE);

  const auto reciprocalExponent =
      static_cast<float>(m_goomRand.GetRandInRange(RECIPROCAL_EXPONENT_RANGE));

  const auto useModulatorContours = m_goomRand.ProbabilityOf(PROB_USE_MODULATOR_CONTOURS);
  const auto modulatorPeriod =
      not useModulatorContours ? 0.0F : m_goomRand.GetRandInRange(MODULATOR_PERIOD_RANGE);

  SetParams({
      viewport,
      {xAmplitude, yAmplitude},
      noInverseSquare,
      magnify * rotate,
      reciprocalExponent,
      useModulatorContours,
      modulatorPeriod,
  });
}

auto ExpReciprocal::GetZoomInCoefficients(const NormalizedCoords& coords,
                                          const float sqDistFromZero) const noexcept -> Point2dFlt
{
  Expects(GetZoomInCoefficientsViewport().GetViewportWidth() != NormalizedCoords::COORD_WIDTH);

  if (sqDistFromZero < UTILS::MATH::SMALL_FLOAT)
  {
    return GetBaseZoomInCoeffs();
  }

  const auto zOffset = std::complex<FltCalcType>{};
  const auto z       = static_cast<std::complex<FltCalcType>>(m_params.magnifyAndRotate) *
                 (std::complex{static_cast<FltCalcType>(coords.GetX()),
                               static_cast<FltCalcType>(coords.GetY())} +
                  zOffset);

  const auto fz      = std::exp(ONE / std::pow(z, m_params.reciprocalExponent));
  const auto absSqFz = std::norm(fz);

  if (absSqFz < static_cast<FltCalcType>(UTILS::MATH::SMALL_FLOAT))
  {
    return GetBaseZoomInCoeffs();
  }

  const auto phase = GetAdjustedPhase(fz, sqDistFromZero);

  if (not m_params.useModulatorContours)
  {
    return {GetBaseZoomInCoeffs().x + static_cast<float>(phase.real()),
            GetBaseZoomInCoeffs().y + static_cast<float>(phase.imag())};
  }

  const auto modulatedPhase = GetModulatedPhase(phase, absSqFz);

  return {GetBaseZoomInCoeffs().x + static_cast<float>(modulatedPhase.real()),
          GetBaseZoomInCoeffs().y + static_cast<float>(modulatedPhase.imag())};
}

inline auto ExpReciprocal::GetAdjustedPhase(const std::complex<FltCalcType>& fz,
                                            const float sqDistFromZero) const noexcept
    -> std::complex<FltCalcType>
{
  const auto phase = std::polar(ONE, std::arg(fz));

  const auto realPhasePart = static_cast<FltCalcType>(m_params.amplitude.x) * phase.real();
  const auto imagPhasePart = static_cast<FltCalcType>(m_params.amplitude.y) * phase.imag();

  if (m_params.noInverseSquare)
  {
    return {realPhasePart, imagPhasePart};
  }

  static constexpr auto MIN_LOG_ARG = static_cast<FltCalcType>(1.5F);
  const auto inverseLogSqDistFromZero =
      ONE / std::log(MIN_LOG_ARG + static_cast<FltCalcType>(sqDistFromZero));

  return {inverseLogSqDistFromZero * realPhasePart, inverseLogSqDistFromZero * imagPhasePart};
}

inline auto ExpReciprocal::GetModulatedPhase(const std::complex<FltCalcType>& phase,
                                             const FltCalcType absSqFz) const noexcept
    -> std::complex<FltCalcType>
{
  static constexpr auto MAX_ABS_SQ_FZ = static_cast<FltCalcType>(std::numeric_limits<float>::max());
  static constexpr auto MAX_LOG_VAL   = static_cast<FltCalcType>(1000.0F);
  const auto logAbsSqFz               = absSqFz > MAX_ABS_SQ_FZ ? MAX_LOG_VAL : std::log(absSqFz);

  const auto logAbsFzModulator = static_cast<FltCalcType>(
      GetTriangle(static_cast<float>(logAbsSqFz), m_params.modulatorPeriod));

  return logAbsFzModulator * phase;
}

auto ExpReciprocal::GetZoomInCoefficientsEffectNameValueParams() const noexcept -> NameValuePairs
{
  const auto fullParamGroup = GetFullParamGroup({PARAM_GROUP, "exp reciprocal"});
  return {
      GetPair(fullParamGroup, "recipr exp", m_params.reciprocalExponent),
      GetPair(fullParamGroup, "amplitude", Point2dFlt{m_params.amplitude.x, m_params.amplitude.y}),
      GetPair(fullParamGroup,
              "magnify/rotate",
              Point2dFlt{m_params.magnifyAndRotate.real(), m_params.magnifyAndRotate.imag()}),
      GetPair(fullParamGroup, "modulatorPeriod", m_params.modulatorPeriod),
  };
}

} // namespace GOOM::FILTER_FX::FILTER_EFFECTS
