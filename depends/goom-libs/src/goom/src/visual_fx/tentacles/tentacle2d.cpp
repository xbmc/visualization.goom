#include "tentacle2d.h"

#include "goom_config.h"
#include "utils/math/misc.h"

#include <memory>
#include <tuple>
#include <vector>

namespace GOOM::VISUAL_FX::TENTACLES
{

using UTILS::MATH::ExpDampingFunction;
using UTILS::MATH::FlatDampingFunction;
using UTILS::MATH::LinearDampingFunction;
using UTILS::MATH::PiecewiseDampingFunction;

static constexpr auto SMALL_WEIGHT = 0.001;

static constexpr auto DEFAULT_Y_DAMPING_FACTOR = 0.1;
static constexpr auto NUM_SMOOTH_NODES         = std::min(10U, Tentacle2D::MIN_NUM_NODES);

static constexpr auto DAMPING_AMPLITUDE          = 0.1;
static constexpr auto DAMPING_Y_AT_START_TO_RISE = 5.0;
static constexpr auto DAMPING_Y_AT_X_MAX         = 30.0;
static constexpr auto LINEAR_DAMPING_FLAT_VALUE  = 0.1;
static constexpr auto LINEAR_DAMPING_Y_SCALE     = 30.0;

Tentacle2D::Tentacle2D(const uint32_t numNodes,
                       const Dimensions& dimensions,
                       const BaseYWeights& baseYWeights) noexcept
  : m_numNodes{numNodes},
    m_dimensions{dimensions},
    m_basePreviousYWeight{static_cast<double>(baseYWeights.previous)},
    m_baseCurrentYWeight{static_cast<double>(baseYWeights.current)},
    m_dampingFunc{CreateDampingFunc(m_basePreviousYWeight, m_dimensions.xDimensions)}
{
}

inline auto Tentacle2D::ValidateSettings() const -> void
{
  Expects(m_dimensions.xDimensions.min < m_dimensions.xDimensions.max);
  Expects(m_dimensions.yDimensions.min < m_dimensions.yDimensions.max);
  Expects(m_numNodes >= MIN_NUM_NODES);
  Expects(m_basePreviousYWeight > SMALL_WEIGHT);
  Expects(m_baseCurrentYWeight > SMALL_WEIGHT);
  UNUSED_FOR_NDEBUG(SMALL_WEIGHT);
}

auto Tentacle2D::SetXDimensions(const LinearDimensions& xDimensions) -> void
{
  Expects(not m_startedIterating);
  Expects(xDimensions.min < xDimensions.max);

  m_dimensions.xDimensions = xDimensions;

  m_dampingFunc = CreateDampingFunc(m_basePreviousYWeight, m_dimensions.xDimensions);
}

inline auto Tentacle2D::GetFirstY() -> float
{
  return static_cast<float>(STD20::lerp(m_yVec[0], m_iterZeroYVal, m_iterZeroLerpFactor));
}

inline auto Tentacle2D::GetNextY(const size_t nodeNum) -> float
{
  const auto prevY    = m_yVec[nodeNum - 1];
  const auto currentY = m_yVec[nodeNum];

  return static_cast<float>((m_basePreviousYWeight * prevY) + (m_baseCurrentYWeight * currentY));
}

inline auto Tentacle2D::GetDampedVal(const size_t nodeNum, const double val) const -> double
{
  return m_dampingCache[nodeNum] * val;
}

auto Tentacle2D::StartIterating() -> void
{
  ValidateSettings();

  InitVectors();

  m_startedIterating = true;
  m_iterNum          = 0;

  DoSomeInitialIterations();
}

auto Tentacle2D::InitVectors() noexcept -> void
{
  m_xVec.resize(m_numNodes);
  m_yVec.resize(m_numNodes);
  m_dampedYVec.resize(m_numNodes);
  m_dampingCache.resize(m_numNodes);

  const auto xStep = (m_dimensions.xDimensions.max - m_dimensions.xDimensions.min) /
                     static_cast<double>(m_numNodes - 1);
  auto x = m_dimensions.xDimensions.min;

  for (auto i = 0U; i < m_numNodes; ++i)
  {
    m_dampingCache[i] = (*m_dampingFunc)(x);
    m_xVec[i]         = x;
    m_yVec[i]         = DEFAULT_Y_DAMPING_FACTOR * m_dampingCache[i];

    x += xStep;
  }
}

inline auto Tentacle2D::DoSomeInitialIterations() noexcept -> void
{
  static constexpr auto NUM_START_ITERATIONS = 50U;
  for (auto i = 0U; i < NUM_START_ITERATIONS; ++i)
  {
    Iterate();
  }
}

auto Tentacle2D::Iterate() -> void
{
  ++m_iterNum;

  m_yVec[0] = static_cast<double>(GetFirstY());
  for (auto i = 1U; i < m_numNodes; ++i)
  {
    m_yVec[i] = static_cast<double>(GetNextY(i));
  }

  UpdateDampedValues();
}

auto Tentacle2D::UpdateDampedValues() -> void
{
  const auto tSmooth = [](const double t)
  {
    static constexpr auto PARABOLA_COEFF = 2.0;
    return t * (PARABOLA_COEFF - t);
  };

  const auto tStep = 1.0 / (NUM_SMOOTH_NODES - 1);
  auto tNext       = tStep;
  m_dampedYVec[0]  = 0.0;
  for (auto i = 1U; i < NUM_SMOOTH_NODES; ++i)
  {
    const auto t    = tSmooth(tNext);
    m_dampedYVec[i] = STD20::lerp(m_dampedYVec[i - 1], GetDampedVal(i, m_yVec[i]), t);
    tNext += tStep;
  }

  for (auto i = NUM_SMOOTH_NODES; i < m_numNodes; ++i)
  {
    m_dampedYVec[i] = GetDampedVal(i, m_yVec[i]);
  }
}

auto Tentacle2D::CreateDampingFunc(const double prevYWeight, const LinearDimensions& xDimensions)
    -> Tentacle2D::DampingFuncPtr
{
  if (static constexpr auto LINEAR_CUTOFF_WEIGHT = 0.6; prevYWeight < LINEAR_CUTOFF_WEIGHT)
  {
    return CreateLinearDampingFunc(xDimensions);
  }
  return CreateExpDampingFunc(xDimensions);
}

auto Tentacle2D::CreateExpDampingFunc(const LinearDimensions& xDimensions)
    -> Tentacle2D::DampingFuncPtr
{
  const auto xToStartRise = xDimensions.min + (0.25 * xDimensions.max);

  return DampingFuncPtr{std::make_unique<ExpDampingFunction>(DAMPING_AMPLITUDE,
                                                             xToStartRise,
                                                             DAMPING_Y_AT_START_TO_RISE,
                                                             xDimensions.max,
                                                             DAMPING_Y_AT_X_MAX)};
}

auto Tentacle2D::CreateLinearDampingFunc(const LinearDimensions& xDimensions)
    -> Tentacle2D::DampingFuncPtr
{
  auto pieces = std::vector<std::tuple<double, double, DampingFuncPtr>>{};

  const auto flatXMin = xDimensions.min;
  const auto flatXMax = 0.1 * xDimensions.max;
  pieces.emplace_back(
      flatXMin,
      flatXMax,
      DampingFuncPtr{std::make_unique<FlatDampingFunction>(LINEAR_DAMPING_FLAT_VALUE)});

  const auto linearXMin = flatXMax;
  const auto linearXMax = 10.0 * xDimensions.max;
  pieces.emplace_back(
      linearXMin,
      linearXMax,
      DampingFuncPtr{std::make_unique<LinearDampingFunction>(
          flatXMax, LINEAR_DAMPING_FLAT_VALUE, xDimensions.max, LINEAR_DAMPING_Y_SCALE)});

  return DampingFuncPtr{std::make_unique<PiecewiseDampingFunction>(pieces)};
}

} // namespace GOOM::VISUAL_FX::TENTACLES
