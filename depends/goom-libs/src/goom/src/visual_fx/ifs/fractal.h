#pragma once

#include "fractal_hits.h"
#include "goom_types.h"
#include "ifs_types.h"
#include "similitudes.h"
#include "utils/math/goom_rand_base.h"
#include "utils/t_values.h"

#include <cstdint>
#include <memory>
#include <vector>

namespace GOOM
{

namespace COLOR
{
class RandomColorMaps;
}

namespace UTILS::GRAPHICS
{
class SmallImageBitmaps;
}

namespace VISUAL_FX::IFS
{

class Fractal
{
public:
  Fractal(const Dimensions& dimensions,
          const UTILS::MATH::IGoomRand& goomRand,
          const UTILS::GRAPHICS::SmallImageBitmaps& smallBitmaps);

  auto Init() -> void;
  auto Reset() -> void;

  auto SetWeightedColorMaps(const std::shared_ptr<const COLOR::RandomColorMaps>& weightedColorMaps)
      -> void;

  [[nodiscard]] auto GetSpeed() const -> uint32_t;
  auto SetSpeed(uint32_t val) -> void;

  [[nodiscard]] auto GetNextIfsPoints() -> const std::vector<IfsPoint>&;
  [[nodiscard]] auto GetMaxHitCount() const -> uint32_t;

private:
  Similitudes m_similitudes;
  const UTILS::MATH::IGoomRand& m_goomRand;

  const Flt m_halfWidth;
  const Flt m_halfHeight;

  static constexpr uint32_t MIN_MAX_COUNT_TIMES_SPEED = 950;
  static constexpr uint32_t MAX_MAX_COUNT_TIMES_SPEED = 1500;
  uint32_t m_iterationCount                           = 0;
  auto UpdateIterationCount() -> void;

  static constexpr uint32_t INITIAL_SPEED              = 6;
  uint32_t m_prevSpeed                                 = INITIAL_SPEED;
  uint32_t m_speed                                     = INITIAL_SPEED;
  static constexpr uint32_t NUM_SPEED_TRANSITION_STEPS = 500;
  UTILS::TValue m_speedTransitionT{UTILS::TValue::StepType::SINGLE_CYCLE,
                                   NUM_SPEED_TRANSITION_STEPS};
  uint32_t m_maxCountTimesSpeed = MAX_MAX_COUNT_TIMES_SPEED;

  FractalHits m_hits1;
  FractalHits m_hits2;
  FractalHits* m_prevHits{&m_hits1};
  FractalHits* m_curHits{&m_hits2};
  auto InitHits() -> void;

  auto UpdateMainSimis() -> void;
  [[nodiscard]] auto GetCurrentIfsPoints() -> const std::vector<IfsPoint>&;
  auto DrawFractal() -> void;
  auto Trace(uint32_t curDepth, const FltPoint& point0) -> void;
  [[nodiscard]] static auto AreSimilarPoints(const FltPoint& point1, const FltPoint& point2)
      -> bool;
  auto UpdateHits(const Similitude& simi, const FltPoint& point) -> void;
};

inline auto Fractal::GetMaxHitCount() const -> uint32_t
{
  return m_curHits->GetMaxHitCount();
}

} // namespace VISUAL_FX::IFS
} // namespace GOOM
