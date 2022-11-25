#pragma once

#include "filter_fx/normalized_coords.h"
#include "utils/math/goom_rand_base.h"
#include "utils/math/misc.h"
#include "utils/name_value_pairs.h"

#include <algorithm>
#include <cmath>
#include <stdexcept>

namespace GOOM::FILTER_FX::AFTER_EFFECTS
{

class XYLerpEffect
{
public:
  explicit XYLerpEffect(const UTILS::MATH::IGoomRand& goomRand);
  XYLerpEffect(const XYLerpEffect&) noexcept           = delete;
  XYLerpEffect(XYLerpEffect&&) noexcept                = delete;
  virtual ~XYLerpEffect() noexcept                     = default;
  auto operator=(const XYLerpEffect&) -> XYLerpEffect& = delete;
  auto operator=(XYLerpEffect&&) -> XYLerpEffect&      = delete;

  virtual auto SetRandomParams() -> void;

  [[nodiscard]] auto GetVelocity(float sqDistFromZero, const NormalizedCoords& velocity) const
      -> NormalizedCoords;

  [[nodiscard]] auto GetNameValueParams(const std::string& paramGroup) const
      -> UTILS::NameValuePairs;

  enum class Modes
  {
    MODE0,
    MODE1,
    MODE2,
    MODE3,
    _num // unused, and marks the enum end
  };
  struct Params
  {
    Modes mode;
    float tFreq;
    float ySign;
    bool flipXY;
  };
  [[nodiscard]] auto GetParams() const -> const Params&;

protected:
  auto SetParams(const Params& params) -> void;

private:
  const UTILS::MATH::IGoomRand& m_goomRand;
  const UTILS::MATH::Weights<Modes> m_modeWeights;
  Params m_params;
  [[nodiscard]] auto GetT(float sqDistFromZero, const NormalizedCoords& velocity) const -> float;
  [[nodiscard]] static auto GetFlipYProbability(Modes mode) -> float;
};

inline auto XYLerpEffect::GetVelocity([[maybe_unused]] const float sqDistFromZero,
                                      const NormalizedCoords& velocity) const -> NormalizedCoords
{
  const auto t = GetT(sqDistFromZero, velocity);

  const auto xVelocity = STD20::lerp(velocity.GetX(), velocity.GetY(), t);
  const auto yVelocity = STD20::lerp(velocity.GetY(), velocity.GetX(), t);

  if (m_params.flipXY)
  {
    return {yVelocity, m_params.ySign * xVelocity};
  }

  return {xVelocity, m_params.ySign * yVelocity};
}

inline auto XYLerpEffect::GetT(const float sqDistFromZero, const NormalizedCoords& velocity) const
    -> float
{
  static constexpr auto MODE0_OFFSET     = 5.5F;
  static constexpr auto MODE0_FREQ       = 2.0F;
  static constexpr auto MODE1_MIN_FACTOR = 0.99F;
  static constexpr auto MODE1_MAX_FACTOR = 1.01F;

  switch (m_params.mode)
  {
    case Modes::MODE0:
      return std::cos((m_params.tFreq * sqDistFromZero) +
                      (MODE0_OFFSET + std::sin(MODE0_FREQ * sqDistFromZero)));
    case Modes::MODE1:
      return std::cos((m_params.tFreq * sqDistFromZero) *
                      m_goomRand.GetRandInRange(MODE1_MIN_FACTOR, MODE1_MAX_FACTOR));
    case Modes::MODE2:
      return -(1.0F / UTILS::MATH::HALF_PI) *
             std::atan(std::tan(UTILS::MATH::HALF_PI - (m_params.tFreq * sqDistFromZero)));
    case Modes::MODE3:
      return (1.0F / UTILS::MATH::HALF_PI) * std::abs(std::atan2(velocity.GetY(), velocity.GetX()));
    default:
      FailFast();
      return 0.0F;
  }
}

inline auto XYLerpEffect::GetParams() const -> const Params&
{
  return m_params;
}

inline auto XYLerpEffect::SetParams(const Params& params) -> void
{
  m_params = params;
}

} // namespace GOOM::FILTER_FX::AFTER_EFFECTS
