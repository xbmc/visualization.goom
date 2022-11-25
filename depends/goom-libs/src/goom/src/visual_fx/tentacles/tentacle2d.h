#pragma once

#include "utils/math/damping_functions.h"

#include <memory>
#include <utility>
#include <vector>

namespace GOOM::VISUAL_FX::TENTACLES
{

class Tentacle2D
{
  using XAndYVectors = std::pair<std::vector<double>&, std::vector<double>&>;

public:
  static constexpr uint32_t MIN_NUM_NODES = 5U;

  struct LinearDimensions
  {
    double min;
    double max;
  };
  struct Dimensions
  {
    LinearDimensions xDimensions;
    LinearDimensions yDimensions;
  };
  struct BaseYWeights
  {
    float previous;
    float current;
  };

  Tentacle2D(uint32_t numNodes,
             const Dimensions& dimensions,
             const BaseYWeights& baseYWeights) noexcept;

  auto StartIterating() -> void;
  auto Iterate() -> void;

  auto SetXDimensions(const LinearDimensions& xDimensions) -> void;
  auto SetIterZeroYVal(double val) -> void;
  auto SetIterZeroLerpFactor(double val) -> void;
  auto SetBaseYWeights(const BaseYWeights& val) -> void;

  [[nodiscard]] auto GetDampedXAndYVectors() const -> const XAndYVectors&;

  [[nodiscard]] auto GetNumNodes() const -> uint32_t;
  [[nodiscard]] auto GetTentacleLength() const -> double;
  [[nodiscard]] auto GetXMin() const -> double;
  [[nodiscard]] auto GetXMax() const -> double;

private:
  const uint32_t m_numNodes;
  Dimensions m_dimensions;

  double m_basePreviousYWeight;
  double m_baseCurrentYWeight;

  uint32_t m_iterNum      = 0U;
  bool m_startedIterating = false;

  static constexpr double DEFAULT_ITER_ZERO_Y_VAL       = 0.9;
  double m_iterZeroYVal                                 = DEFAULT_ITER_ZERO_Y_VAL;
  static constexpr double DEFAULT_ITER_ZERO_LERP_FACTOR = 0.8;
  double m_iterZeroLerpFactor                           = DEFAULT_ITER_ZERO_LERP_FACTOR;

  std::vector<double> m_xVec{};
  std::vector<double> m_yVec{};
  std::vector<double> m_dampedYVec{};
  std::vector<double> m_dampingCache{};
  XAndYVectors m_dampedVectors{std::ref(m_xVec), std::ref(m_dampedYVec)};
  std::unique_ptr<UTILS::MATH::IDampingFunction> m_dampingFunc;
  auto InitVectors() noexcept -> void;
  auto DoSomeInitialIterations() noexcept -> void;

  [[nodiscard]] auto GetFirstY() -> float;
  [[nodiscard]] auto GetNextY(size_t nodeNum) -> float;

  auto ValidateSettings() const -> void;

  auto UpdateDampedValues() -> void;
  [[nodiscard]] auto GetDampedVal(size_t nodeNum, double val) const -> double;

  using DampingFuncPtr = std::unique_ptr<UTILS::MATH::IDampingFunction>;
  [[nodiscard]] static auto CreateDampingFunc(double prevYWeight,
                                              const LinearDimensions& xDimensions)
      -> DampingFuncPtr;
  [[nodiscard]] static auto CreateExpDampingFunc(const LinearDimensions& xDimensions)
      -> DampingFuncPtr;
  [[nodiscard]] static auto CreateLinearDampingFunc(const LinearDimensions& xDimensions)
      -> DampingFuncPtr;
};

inline auto Tentacle2D::SetIterZeroYVal(const double val) -> void
{
  m_iterZeroYVal = val;
}

inline auto Tentacle2D::SetIterZeroLerpFactor(const double val) -> void
{
  m_iterZeroLerpFactor = val;
}

inline auto Tentacle2D::SetBaseYWeights(const BaseYWeights& val) -> void
{
  m_basePreviousYWeight = static_cast<double>(val.previous);
  m_baseCurrentYWeight = static_cast<double>(val.current);
}

inline auto Tentacle2D::GetNumNodes() const -> uint32_t
{
  return m_numNodes;
}

inline auto Tentacle2D::GetTentacleLength() const -> double
{
  return m_dimensions.xDimensions.max - m_dimensions.xDimensions.min;
}

inline auto Tentacle2D::GetXMin() const -> double
{
  return m_dimensions.xDimensions.min;
}

inline auto Tentacle2D::GetXMax() const -> double
{
  return m_dimensions.xDimensions.max;
}

inline auto Tentacle2D::GetDampedXAndYVectors() const -> const Tentacle2D::XAndYVectors&
{
  return m_dampedVectors;
}

} // namespace GOOM::VISUAL_FX::TENTACLES
