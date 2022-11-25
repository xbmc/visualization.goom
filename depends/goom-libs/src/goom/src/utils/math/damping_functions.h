#pragma once

#include "misc.h"

#include <memory>
#include <tuple>
#include <vector>

namespace GOOM::UTILS::MATH
{

class IDampingFunction
{
public:
  IDampingFunction() noexcept                                  = default;
  IDampingFunction(const IDampingFunction&) noexcept           = delete;
  IDampingFunction(IDampingFunction&&) noexcept                = delete;
  virtual ~IDampingFunction() noexcept                         = default;
  auto operator=(const IDampingFunction&) -> IDampingFunction& = delete;
  auto operator=(IDampingFunction&&) -> IDampingFunction&      = delete;

  virtual auto operator()(double x) -> double = 0;
};

// Asymptotes to 'amplitude' in negative x direction,
//   and the rate depends on the input parameters.
class ExpDampingFunction : public IDampingFunction
{
public:
  ExpDampingFunction() noexcept = default;
  ExpDampingFunction(
      double amplitude, double xToStartRise, double yAtStartToRise, double xMax, double yAtXMax);
  auto operator()(double x) -> double override;
  [[nodiscard]] auto KVal() const -> double { return m_k; }
  [[nodiscard]] auto BVal() const -> double { return m_b; }

private:
  const double m_amplitude = 1;
  double m_k               = 1;
  double m_b               = 1;
};

class FlatDampingFunction : public IDampingFunction
{
public:
  FlatDampingFunction() noexcept = default;
  explicit FlatDampingFunction(double y) noexcept;
  auto operator()(double x) -> double override;

private:
  const double m_y = 0.0;
};

class LinearDampingFunction : public IDampingFunction
{
public:
  LinearDampingFunction() noexcept = default;
  explicit LinearDampingFunction(double x0, double y0, double x1, double y1) noexcept;
  auto operator()(double x) -> double override;

private:
  const double m_m  = 1;
  const double m_x1 = 0;
  const double m_y1 = 1;
};

class PiecewiseDampingFunction : public IDampingFunction
{
public:
  PiecewiseDampingFunction() noexcept = default;
  explicit PiecewiseDampingFunction(
      std::vector<std::tuple<double, double, std::unique_ptr<IDampingFunction>>>& func) noexcept;
  auto operator()(double x) -> double override;

private:
  const std::vector<std::tuple<double, double, std::unique_ptr<IDampingFunction>>> m_pieces{};
};

class ISequenceFunction
{
public:
  ISequenceFunction() noexcept                                            = default;
  ISequenceFunction(const ISequenceFunction&) noexcept                    = default;
  ISequenceFunction(ISequenceFunction&&) noexcept                         = delete;
  virtual ~ISequenceFunction() noexcept                                   = default;
  auto operator=(const ISequenceFunction&) noexcept -> ISequenceFunction& = default;
  auto operator=(ISequenceFunction&&) noexcept -> ISequenceFunction&      = delete;

  virtual auto Increment() noexcept -> void = 0;
  [[nodiscard]] virtual auto GetNext() const noexcept -> float = 0;
};

class SineWaveMultiplier : public ISequenceFunction
{
public:
  SineWaveMultiplier(float frequency, float lower, float upper, float x0) noexcept;

  auto Increment() noexcept -> void override;
  [[nodiscard]] auto GetNext() const noexcept -> float override;

  auto SetX0(float x0) noexcept -> void;
  [[nodiscard]] auto GetFrequency() const noexcept -> float;
  auto SetFrequency(float val) noexcept -> void;

  [[nodiscard]] auto GetLower() const noexcept -> float;
  [[nodiscard]] auto GetUpper() const noexcept -> float;
  auto SetRange(float lwr, float upr) noexcept -> void;

  auto SetPiStepFrac(float val) noexcept -> void;

private:
  RangeMapper m_rangeMapper;
  float m_frequency;
  float m_lower;
  float m_upper;
  float m_piStepFrac;
  float m_x;
};

inline auto SineWaveMultiplier::SetX0(const float x0) noexcept -> void
{
  m_x = x0;
}

inline auto SineWaveMultiplier::GetFrequency() const noexcept -> float
{
  return m_frequency;
}

inline auto SineWaveMultiplier::SetFrequency(const float val) noexcept -> void
{
  m_frequency = val;
}

inline auto SineWaveMultiplier::GetLower() const noexcept -> float
{
  return m_lower;
}

inline auto SineWaveMultiplier::GetUpper() const noexcept -> float
{
  return m_upper;
}

inline auto SineWaveMultiplier::SetRange(const float lwr, const float upr) noexcept -> void
{
  m_lower = lwr;
  m_upper = upr;
}

inline auto SineWaveMultiplier::SetPiStepFrac(const float val) noexcept -> void
{
  m_piStepFrac = val;
}

} // namespace GOOM::UTILS::MATH
