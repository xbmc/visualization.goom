#include "dot_paths.h"

//#undef NO_LOGGING

#include "logging.h"
#include "point2d.h"
#include "utils/math/paths.h"
#include "utils/t_values.h"

#include <cstdint>
#include <memory>
#include <vector>

namespace GOOM::VISUAL_FX::CIRCLES
{

using UTILS::Logging; // NOLINT(misc-unused-using-decls)
using UTILS::TValue;
using UTILS::MATH::IGoomRand;
using UTILS::MATH::OscillatingPath;

DotPaths::DotPaths(const IGoomRand& goomRand,
                   const uint32_t numDots,
                   DotStartsToAndFrom&& dotStartsToAndFrom,
                   const DotTargetsToAndFrom& dotTargetsToAndFrom,
                   const DotPathParamsToAndFrom& dotPathParamsToAndFrom) noexcept
  : m_goomRand{goomRand},
    m_numDots{numDots},
    m_dotStartsToAndFrom{std::move(dotStartsToAndFrom)},
    m_dotTargetsToAndFrom{dotTargetsToAndFrom},
    m_dotPathParamsToAndFrom{dotPathParamsToAndFrom}
{
}

DotPaths::~DotPaths() noexcept = default;

auto DotPaths::GetNewDotPaths(const DotStartsToAndFrom& dotStartsToAndFrom) noexcept
    -> DotPathsToAndFrom
{
  auto dotPathsToAndFrom = DotPathsToAndFrom{};

  for (auto i = 0U; i < m_numDots; ++i)
  {
    dotPathsToAndFrom.dotPathToTarget.emplace_back(
        std::make_unique<TValue>(TValue::StepType::SINGLE_CYCLE, DEFAULT_POSITION_STEPS),
        dotStartsToAndFrom.dotStartingPositionsToTarget.at(i).ToFlt(),
        m_dotTargetsToAndFrom.dotTargetPositionToTarget.ToFlt(),
        m_dotPathParamsToAndFrom.dotPathParamsToTarget);
    dotPathsToAndFrom.dotPathFromTarget.emplace_back(
        std::make_unique<TValue>(TValue::StepType::SINGLE_CYCLE, DEFAULT_POSITION_STEPS),
        m_dotTargetsToAndFrom.dotTargetPositionFromTarget.ToFlt(),
        dotStartsToAndFrom.dotStartingPositionsFromTarget.at(i).ToFlt(),
        m_dotPathParamsToAndFrom.dotPathParamsFromTarget);
  }

  return dotPathsToAndFrom;
}

auto DotPaths::MakeToDotPathsSameAsFromDotPaths() noexcept -> void
{
  m_dotPathsToAndFrom.dotPathToTarget.clear();
  for (auto i = 0U; i < m_numDots; ++i)
  {
    m_dotPathsToAndFrom.dotPathToTarget.emplace_back(
        std::make_unique<TValue>(TValue::StepType::SINGLE_CYCLE,
                                 m_dotPathsToAndFrom.dotPathFromTarget.at(i).GetNumSteps()),
        m_dotPathsToAndFrom.dotPathFromTarget.at(i).GetNextPoint().ToFlt(),
        m_dotTargetsToAndFrom.dotTargetPositionFromTarget.ToFlt(),
        m_dotPathParamsToAndFrom.dotPathParamsToTarget);
  }

  m_updatedDotPathsToAndFrom = true;
}

auto DotPaths::GetNextDotPositions() const noexcept -> std::vector<Point2dInt>
{
  if (m_direction == Direction::TO_TARGET)
  {
    return GetNextDotPositions(m_dotPathsToAndFrom.dotPathToTarget);
  }

  return GetNextDotPositions(m_dotPathsToAndFrom.dotPathFromTarget);
}

auto DotPaths::GetNextDotPositions(const std::vector<UTILS::MATH::OscillatingPath>& dotPath)
    const noexcept -> std::vector<Point2dInt>
{
  auto nextDotPositions = std::vector<Point2dInt>(m_numDots);
  for (auto i = 0U; i < m_numDots; ++i)
  {
    nextDotPositions.at(i) = dotPath.at(i).GetNextPoint();
    if (m_randomizePoints)
    {
      nextDotPositions.at(i).Translate(GetSmallRandomOffset());
    }
  }
  return nextDotPositions;
}

inline auto DotPaths::GetSmallRandomOffset() const noexcept -> Vec2dInt
{
  static constexpr auto MIN_VARIATION = -5;
  static constexpr auto MAX_VARIATION = +5;
  return {m_goomRand.GetRandInRange(MIN_VARIATION, MAX_VARIATION + 1),
          m_goomRand.GetRandInRange(MIN_VARIATION, MAX_VARIATION + 1)};
}

} // namespace GOOM::VISUAL_FX::CIRCLES
