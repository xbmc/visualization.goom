#include "dot_diameters.h"

#include "goom_config.h"

namespace GOOM::VISUAL_FX::CIRCLES
{

DotDiameters::DotDiameters(const UTILS::MATH::IGoomRand& goomRand,
                           const uint32_t numDots,
                           const uint32_t minDotDiameter,
                           const uint32_t maxDotDiameter) noexcept
  : m_goomRand{goomRand},
    m_numDots{numDots},
    m_minDotDiameter{minDotDiameter + MIN_DIAMETER_EXTRA},
    m_maxDotDiameter{maxDotDiameter}
{
  Expects(m_minDotDiameter <= m_maxDotDiameter);
  ChangeDotDiameters();
}

auto DotDiameters::GetInitialDotDiameters(const uint32_t numDots,
                                          const uint32_t maxDotDiameter) noexcept
    -> std::vector<uint32_t>
{
  auto diameters = std::vector<uint32_t>(numDots);
  std::fill(begin(diameters), end(diameters), maxDotDiameter);
  return diameters;
}

auto DotDiameters::ChangeDotDiameters() noexcept -> void
{
  if (m_goomRand.ProbabilityOf(PROB_FIXED_DIAMETER))
  {
    ChangeToFixedDotDiameters();
  }
  else
  {
    ChangeToVariableDotDiameters();
  }
}

auto DotDiameters::ChangeToFixedDotDiameters() noexcept -> void
{
  const auto fixedDotDiameter = m_goomRand.GetRandInRange(m_minDotDiameter, m_maxDotDiameter + 1);

  std::fill(begin(m_dotDiameters), end(m_dotDiameters), fixedDotDiameter);
}

auto DotDiameters::ChangeToVariableDotDiameters() noexcept -> void
{
  const auto smallDotDiameter = m_goomRand.GetRandInRange(m_minDotDiameter, m_maxDotDiameter - 1);

  static constexpr auto INCREASED_DIAMETER = 3U;
  const auto minLargerDotDiameter =
      std::min(m_maxDotDiameter, smallDotDiameter + INCREASED_DIAMETER);
  const auto largerDotDiameter =
      m_goomRand.GetRandInRange(minLargerDotDiameter, m_maxDotDiameter + 1);

  static constexpr auto MIN_LARGER_DIAMETER_FREQ = 2U;
  static constexpr auto MAX_LARGER_DIAMETER_FREQ = 5U;
  const auto largerDiameterEvery =
      m_goomRand.GetRandInRange(MIN_LARGER_DIAMETER_FREQ, MAX_LARGER_DIAMETER_FREQ + 1);

  for (auto i = 1U; i < m_numDots; ++i)
  {
    m_dotDiameters.at(i) = 0 == (i % largerDiameterEvery) ? largerDotDiameter : smallDotDiameter;
  }
}

} // namespace GOOM::VISUAL_FX::CIRCLES
