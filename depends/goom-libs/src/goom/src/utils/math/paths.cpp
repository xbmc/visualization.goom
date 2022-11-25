#include "paths.h"

#include "goom_config.h"
#include "utils/math/misc.h"
#include "utils/t_values.h"

#include <algorithm>
#include <memory>

namespace GOOM::UTILS::MATH
{

using MATH::Transform2d;

TransformedPath::TransformedPath(std::unique_ptr<IPath> path, const Transform2d& transform) noexcept
  : m_path{std::move(path)}, m_transform{transform}
{
}

LerpedPath::LerpedPath(const std::shared_ptr<IPath> path1,
                       const std::shared_ptr<IPath> path2,
                       TValue& lerpT) noexcept
  : m_path1{path1}, m_path2{path2}, m_lerpT{lerpT}
{
}

auto LerpedPath::GetClone() const noexcept -> std::unique_ptr<IPath>
{
  FailFast();
  return std::unique_ptr<LerpedPath>{};
}

JoinedPaths::JoinedPaths(std::unique_ptr<TValue> positionT,
                         const std::vector<float>& pathTStarts,
                         std::vector<std::unique_ptr<IPath>>&& subPaths) noexcept
  : m_positionT{std::move(positionT)}, m_pathTStarts{pathTStarts}, m_subPaths{std::move(subPaths)}
{
  Expects(not pathTStarts.empty());
  Expects(pathTStarts.size() == m_subPaths.size());

  assert(SegmentPathTsAreAscending());
  assert(SegmentPathTsAreValid());

  AdjustSegmentStepSizes();
}

auto JoinedPaths::SegmentPathTsAreAscending() const noexcept -> bool
{
  auto prevTStart = -SMALL_FLOAT;

  for (const auto& tStart : m_pathTStarts)
  {
    if (tStart <= prevTStart)
    {
      return false;
    }
    prevTStart = tStart;
  }

  return true;
}

auto JoinedPaths::SegmentPathTsAreValid() const noexcept -> bool
{
  return std::all_of(cbegin(m_pathTStarts),
                     cend(m_pathTStarts),
                     [](const float tStart) { return (tStart >= 0.0F) and (tStart <= 1.0F); });
}

auto JoinedPaths::AdjustSegmentStepSizes() noexcept -> void
{
  auto tStartsWithSentinel = std::vector<float>{m_pathTStarts};
  tStartsWithSentinel.push_back(1.0F);

  auto prevTStart = 0.0F;

  for (auto i = 1U; i < m_pathTStarts.size(); ++i)
  {
    const auto stepSizeFactor = 1.0F / (tStartsWithSentinel[i] - prevTStart);
    const auto oldStepSize    = m_subPaths[i]->GetStepSize();
    m_subPaths[i]->SetStepSize(stepSizeFactor * oldStepSize);

    prevTStart = tStartsWithSentinel[i];
  }
}

auto JoinedPaths::GetClone() const noexcept -> std::unique_ptr<IPath>
{
  FailFast();
  return std::unique_ptr<JoinedPaths>{};
}

} // namespace GOOM::UTILS::MATH
