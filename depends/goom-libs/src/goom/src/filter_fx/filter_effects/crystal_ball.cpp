#include "crystal_ball.h"

#include "filter_fx/common_types.h"
#include "goom_config.h"
#include "utils/name_value_pairs.h"

namespace GOOM::FILTER_FX::FILTER_EFFECTS
{

using UTILS::NameValuePairs;
using UTILS::MATH::IGoomRand;

static constexpr auto DEFAULT_AMPLITUDE     = 0.1F;
static constexpr auto AMPLITUDE_RANGE_MODE0 = AmplitudeRange{
    {0.001F, 0.501F},
    {0.001F, 0.501F},
};
static constexpr auto AMPLITUDE_RANGE_MODE1 = AmplitudeRange{
    {0.500F, 1.001F},
    {0.500F, 1.001F},
};

static constexpr auto DEFAULT_SQ_DIST_MULT     = 0.025F;
static constexpr auto SQ_DIST_MULT_RANGE_MODE0 = SqDistMultRange{
    {0.001F, 0.051F},
    {0.001F, 0.051F},
};
static constexpr auto SQ_DIST_MULT_RANGE_MODE1 = SqDistMultRange{
    {0.050F, 0.101F},
    {0.050F, 0.101F},
};

static constexpr auto DEFAULT_SQ_DIST_OFFSET     = 0.05F;
static constexpr auto SQ_DIST_OFFSET_RANGE_MODE0 = SqDistOffsetRange{
    {0.001F, 0.11F},
    {0.001F, 0.11F},
};
static constexpr auto SQ_DIST_OFFSET_RANGE_MODE1 = SqDistOffsetRange{
    {0.100F, 1.01F},
    {0.100F, 1.01F},
};

static constexpr auto PROB_XY_AMPLITUDES_EQUAL     = 1.00F;
static constexpr auto PROB_XY_SQ_DIST_MULT_EQUAL   = 1.00F;
static constexpr auto PROB_XY_SQ_DIST_OFFSET_EQUAL = 1.00F;

CrystalBall::CrystalBall(const Modes mode, const IGoomRand& goomRand) noexcept
  : m_mode{mode},
    m_goomRand{goomRand},
    m_params{
        {DEFAULT_AMPLITUDE,      DEFAULT_AMPLITUDE},
        {DEFAULT_SQ_DIST_MULT,   DEFAULT_SQ_DIST_MULT},
        {DEFAULT_SQ_DIST_OFFSET, DEFAULT_SQ_DIST_OFFSET}
    }
{
}

auto CrystalBall::SetRandomParams() noexcept -> void
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

auto CrystalBall::SetMode0RandomParams() noexcept -> void
{
  SetRandomParams(AMPLITUDE_RANGE_MODE0, SQ_DIST_MULT_RANGE_MODE0, SQ_DIST_OFFSET_RANGE_MODE0);
}

auto CrystalBall::SetMode1RandomParams() noexcept -> void
{
  SetRandomParams(AMPLITUDE_RANGE_MODE1, SQ_DIST_MULT_RANGE_MODE1, SQ_DIST_OFFSET_RANGE_MODE1);
}

auto CrystalBall::SetRandomParams(const AmplitudeRange& amplitudeRange,
                                  const SqDistMultRange& sqDistMultRange,
                                  const SqDistOffsetRange& sqDistOffsetRange) noexcept -> void
{
  const auto xAmplitude = m_goomRand.GetRandInRange(amplitudeRange.xRange);
  const auto yAmplitude = m_goomRand.ProbabilityOf(PROB_XY_AMPLITUDES_EQUAL)
                              ? xAmplitude
                              : m_goomRand.GetRandInRange(amplitudeRange.yRange);

  const auto xSqDistMult = m_goomRand.GetRandInRange(sqDistMultRange.xRange);
  const auto ySqDistMult = m_goomRand.ProbabilityOf(PROB_XY_SQ_DIST_MULT_EQUAL)
                               ? xSqDistMult
                               : m_goomRand.GetRandInRange(sqDistMultRange.yRange);

  const auto xSqDistOffset = m_goomRand.GetRandInRange(sqDistOffsetRange.xRange);
  const auto ySqDistOffset = m_goomRand.ProbabilityOf(PROB_XY_SQ_DIST_OFFSET_EQUAL)
                                 ? xSqDistOffset
                                 : m_goomRand.GetRandInRange(sqDistOffsetRange.yRange);

  SetParams({
      {   xAmplitude,    yAmplitude},
      {  xSqDistMult,   ySqDistMult},
      {xSqDistOffset, ySqDistOffset}
  });

  Ensures(GetZoomInCoefficientsViewport().GetViewportWidth() == NormalizedCoords::COORD_WIDTH);
}

auto CrystalBall::GetZoomInCoefficientsEffectNameValueParams() const noexcept -> NameValuePairs
{
  return NameValuePairs{};
}

} // namespace GOOM::FILTER_FX::FILTER_EFFECTS
