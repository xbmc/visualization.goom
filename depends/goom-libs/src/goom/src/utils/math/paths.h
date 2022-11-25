#pragma once

#include "point2d.h"
#include "utils/math/parametric_functions2d.h"
#include "utils/math/transform2d.h"
#include "utils/t_values.h"

#include <cstdint>
#include <memory>
#include <vector>

namespace GOOM::UTILS::MATH
{

class IPath
{
public:
  IPath() noexcept                       = default;
  IPath(const IPath&) noexcept           = delete;
  IPath(IPath&&) noexcept                = default;
  virtual ~IPath() noexcept              = default;
  auto operator=(const IPath&) -> IPath& = delete;
  auto operator=(IPath&&) -> IPath&      = delete;

  [[nodiscard]] virtual auto GetClone() const noexcept -> std::unique_ptr<IPath> = 0;

  [[nodiscard]] virtual auto GetStartPos() const noexcept -> Point2dInt = 0;
  [[nodiscard]] virtual auto GetEndPos() const noexcept -> Point2dInt   = 0;

  [[nodiscard]] virtual auto GetPositionT() const noexcept -> const TValue& = 0;

  [[nodiscard]] auto GetNumSteps() const noexcept -> uint32_t;
  virtual auto SetNumSteps(uint32_t val) noexcept -> void = 0;

  [[nodiscard]] auto GetStepSize() const noexcept -> float;
  virtual auto SetStepSize(float val) noexcept -> void = 0;

  [[nodiscard]] auto GetCurrentT() const noexcept -> float;
  [[nodiscard]] auto IsStopped() const noexcept -> bool;

  virtual auto IncrementT() noexcept -> void   = 0;
  virtual auto Reset(float t) noexcept -> void = 0;

  [[nodiscard]] virtual auto GetNextPoint() const noexcept -> Point2dInt = 0;

private:
  friend class TransformedPath;
  friend class LerpedPath;
};

class ISimplePath : public IPath
{
public:
  explicit ISimplePath(std::unique_ptr<TValue> positionT) noexcept;
  ISimplePath(const ISimplePath&) noexcept           = delete;
  ISimplePath(ISimplePath&&) noexcept                = default;
  ~ISimplePath() noexcept override                   = default;
  auto operator=(const ISimplePath&) -> ISimplePath& = delete;
  auto operator=(ISimplePath&&) -> ISimplePath&      = delete;

  [[nodiscard]] auto GetStartPos() const noexcept -> Point2dInt override;
  [[nodiscard]] auto GetEndPos() const noexcept -> Point2dInt override;

  auto SetNumSteps(uint32_t val) noexcept -> void override;
  auto SetStepSize(float val) noexcept -> void override;

  auto IncrementT() noexcept -> void override;
  auto Reset(float t) noexcept -> void override;

  [[nodiscard]] auto GetPositionT() const noexcept -> const TValue& override;

private:
  mutable std::unique_ptr<TValue> m_positionT;
};

class TransformedPath : public IPath
{
public:
  TransformedPath(std::unique_ptr<IPath> path, const Transform2d& transform) noexcept;

  [[nodiscard]] auto GetClone() const noexcept -> std::unique_ptr<IPath> override;

  [[nodiscard]] auto GetStartPos() const noexcept -> Point2dInt override;
  [[nodiscard]] auto GetEndPos() const noexcept -> Point2dInt override;

  [[nodiscard]] auto GetPositionT() const noexcept -> const TValue& override;

  auto SetNumSteps(uint32_t val) noexcept -> void override;
  auto SetStepSize(float val) noexcept -> void override;

  auto IncrementT() noexcept -> void override;
  auto Reset(float t) noexcept -> void override;

  [[nodiscard]] auto GetNextPoint() const noexcept -> Point2dInt override;

  [[nodiscard]] auto GetTransform() const noexcept -> Transform2d;
  auto SetTransform(const Transform2d& val) noexcept -> void;

private:
  std::unique_ptr<IPath> m_path;
  Transform2d m_transform;
};

class LerpedPath : public IPath
{
public:
  LerpedPath(std::shared_ptr<IPath> path1, std::shared_ptr<IPath> path2, TValue& lerpT) noexcept;

  [[nodiscard]] auto GetClone() const noexcept -> std::unique_ptr<IPath> override;

  [[nodiscard]] auto GetStartPos() const noexcept -> Point2dInt override;
  [[nodiscard]] auto GetEndPos() const noexcept -> Point2dInt override;

  [[nodiscard]] auto GetPositionT() const noexcept -> const TValue& override;

  auto SetNumSteps(uint32_t val) noexcept -> void override;
  auto SetStepSize(float val) noexcept -> void override;

  auto IncrementT() noexcept -> void override;
  auto Reset(float t) noexcept -> void override;

  [[nodiscard]] auto GetNextPoint() const noexcept -> Point2dInt override;

  [[nodiscard]] auto GetPath1() noexcept -> IPath&;
  [[nodiscard]] auto GetPath2() noexcept -> IPath&;

private:
  std::shared_ptr<IPath> m_path1;
  std::shared_ptr<IPath> m_path2;
  TValue& m_lerpT;
};

class JoinedPaths : public IPath
{
public:
  JoinedPaths(std::unique_ptr<TValue> positionT,
              const std::vector<float>& pathTStarts,
              std::vector<std::unique_ptr<IPath>>&& subPaths) noexcept;

  [[nodiscard]] auto GetClone() const noexcept -> std::unique_ptr<IPath> override;

  [[nodiscard]] auto GetStartPos() const noexcept -> Point2dInt override;
  [[nodiscard]] auto GetEndPos() const noexcept -> Point2dInt override;

  [[nodiscard]] auto GetPositionT() const noexcept -> const TValue& override;

  auto SetNumSteps(uint32_t val) noexcept -> void override;
  auto SetStepSize(float val) noexcept -> void override;

  auto IncrementT() noexcept -> void override;
  auto Reset(float t) noexcept -> void override;

  [[nodiscard]] auto GetNextPoint() const noexcept -> Point2dInt override;

private:
  std::unique_ptr<TValue> m_positionT;
  std::vector<float> m_pathTStarts;
  std::vector<std::unique_ptr<IPath>> m_subPaths;
  size_t m_currentSegment = 0;
  [[nodiscard]] auto SegmentPathTsAreAscending() const noexcept -> bool;
  [[nodiscard]] auto SegmentPathTsAreValid() const noexcept -> bool;
  auto AdjustSegmentStepSizes() noexcept -> void;
};

template<typename T>
class ParametricPath : public ISimplePath
{
public:
  template<typename... TArgs>
  explicit ParametricPath(std::unique_ptr<TValue> positionT, TArgs&&... args) noexcept;

  [[nodiscard]] auto GetClone() const noexcept -> std::unique_ptr<IPath> override;

  [[nodiscard]] auto GetParametricFunction() noexcept -> T&;

  [[nodiscard]] auto GetNextPoint() const noexcept -> Point2dInt override;

private:
  T m_parametricFunction;
};

using CirclePath       = ParametricPath<CircleFunction>;
using SpiralPath       = ParametricPath<SpiralFunction>;
using LissajousPath    = ParametricPath<LissajousFunction>;
using HypotrochoidPath = ParametricPath<HypotrochoidFunction>;
using EpicycloidPath   = ParametricPath<EpicycloidFunction>;
using SinePath         = ParametricPath<SineFunction>;
using OscillatingPath  = ParametricPath<OscillatingFunction>;

inline auto IPath::GetNumSteps() const noexcept -> uint32_t
{
  return GetPositionT().GetNumSteps();
}

inline auto IPath::GetStepSize() const noexcept -> float
{
  return GetPositionT().GetStepSize();
}

inline auto IPath::GetCurrentT() const noexcept -> float
{
  return GetPositionT()();
}

inline auto IPath::IsStopped() const noexcept -> bool
{
  return GetPositionT().IsStopped();
}

inline ISimplePath::ISimplePath(std::unique_ptr<TValue> positionT) noexcept
  : m_positionT{std::move(positionT)}
{
}

inline auto ISimplePath::GetStartPos() const noexcept -> Point2dInt
{
  const auto currentT = GetCurrentT();
  m_positionT->Reset(0.0F);
  const auto startPos = GetNextPoint();
  m_positionT->Reset(currentT);
  return startPos;
}

inline auto ISimplePath::GetEndPos() const noexcept -> Point2dInt
{
  const auto currentT = GetCurrentT();
  m_positionT->Reset(1.0F);
  const auto startPos = GetNextPoint();
  m_positionT->Reset(currentT);
  return startPos;
}

inline auto ISimplePath::GetPositionT() const noexcept -> const TValue&
{
  return *m_positionT;
}

inline auto ISimplePath::SetStepSize(const float val) noexcept -> void
{
  m_positionT->SetStepSize(val);
}

inline auto ISimplePath::SetNumSteps(const uint32_t val) noexcept -> void
{
  m_positionT->SetNumSteps(val);
}

inline auto ISimplePath::IncrementT() noexcept -> void
{
  m_positionT->Increment();
}

inline auto ISimplePath::Reset(const float t) noexcept -> void
{
  m_positionT->Reset(t);
}

inline auto TransformedPath::GetClone() const noexcept -> std::unique_ptr<IPath>
{
  return std::make_unique<TransformedPath>(m_path->GetClone(), m_transform);
}

inline auto TransformedPath::GetStartPos() const noexcept -> Point2dInt
{
  return m_transform.GetTransformedPoint(m_path->GetStartPos());
}

inline auto TransformedPath::GetEndPos() const noexcept -> Point2dInt
{
  return m_transform.GetTransformedPoint(m_path->GetEndPos());
}

inline auto TransformedPath::GetNextPoint() const noexcept -> Point2dInt
{
  return m_transform.GetTransformedPoint(m_path->GetNextPoint());
}

inline auto TransformedPath::GetTransform() const noexcept -> Transform2d
{
  return m_transform;
}

inline auto TransformedPath::SetTransform(const Transform2d& val) noexcept -> void
{
  m_transform = val;
}

inline auto TransformedPath::GetPositionT() const noexcept -> const TValue&
{
  return m_path->GetPositionT();
}

inline auto TransformedPath::SetStepSize(const float val) noexcept -> void
{
  m_path->SetStepSize(val);
}

inline auto TransformedPath::SetNumSteps(const uint32_t val) noexcept -> void
{
  m_path->SetNumSteps(val);
}

inline auto TransformedPath::IncrementT() noexcept -> void
{
  m_path->IncrementT();
}

inline auto TransformedPath::Reset(const float t) noexcept -> void
{
  m_path->Reset(t);
}

inline auto LerpedPath::GetPositionT() const noexcept -> const TValue&
{
  return m_path1->GetPositionT();
}

inline auto LerpedPath::SetStepSize(const float val) noexcept -> void
{
  m_path1->SetStepSize(val);
  m_path2->SetStepSize(val);
}

inline auto LerpedPath::SetNumSteps(const uint32_t val) noexcept -> void
{
  m_path1->SetNumSteps(val);
  m_path2->SetNumSteps(val);
}

inline auto LerpedPath::GetStartPos() const noexcept -> Point2dInt
{
  return lerp(m_path1->GetStartPos(), m_path2->GetStartPos(), m_lerpT());
}

inline auto LerpedPath::GetEndPos() const noexcept -> Point2dInt
{
  return lerp(m_path1->GetEndPos(), m_path2->GetEndPos(), m_lerpT());
}

inline auto LerpedPath::GetNextPoint() const noexcept -> Point2dInt
{
  return lerp(m_path1->GetNextPoint(), m_path2->GetNextPoint(), m_lerpT());
}

inline auto LerpedPath::IncrementT() noexcept -> void
{
  m_path1->IncrementT();
  m_path2->IncrementT();
}

inline auto LerpedPath::Reset(const float t) noexcept -> void
{
  m_path1->Reset(t);
  m_path2->Reset(t);
}

inline auto LerpedPath::GetPath1() noexcept -> IPath&
{
  return *m_path1;
}

inline auto LerpedPath::GetPath2() noexcept -> IPath&
{
  return *m_path2;
}

inline auto JoinedPaths::GetStartPos() const noexcept -> Point2dInt
{
  return m_subPaths.front()->GetStartPos();
}

inline auto JoinedPaths::GetEndPos() const noexcept -> Point2dInt
{
  return m_subPaths.back()->GetStartPos();
}

inline auto JoinedPaths::GetPositionT() const noexcept -> const TValue&
{
  return *m_positionT;
}

inline auto JoinedPaths::SetNumSteps(const uint32_t val) noexcept -> void
{
  m_positionT->SetNumSteps(val);
}

inline auto JoinedPaths::SetStepSize(const float val) noexcept -> void
{
  m_positionT->SetStepSize(val);
}

inline auto JoinedPaths::GetNextPoint() const noexcept -> Point2dInt
{
  return m_subPaths.at(m_currentSegment)->GetNextPoint();
}

inline auto JoinedPaths::IncrementT() noexcept -> void
{
  m_positionT->Increment();
  m_subPaths.at(m_currentSegment)->IncrementT();

  if ((m_currentSegment < (m_subPaths.size() - 1)) and
      (m_pathTStarts.at(m_currentSegment + 1) <= (*m_positionT)()))
  {
    ++m_currentSegment;
  }
}

inline auto JoinedPaths::Reset(const float t) noexcept -> void
{
  m_positionT->Reset(t);
  m_currentSegment = 0;
}

template<typename T>
template<typename... TArgs>
ParametricPath<T>::ParametricPath(std::unique_ptr<TValue> positionT, TArgs&&... args) noexcept
  : ISimplePath{std::move(positionT)}, m_parametricFunction{std::forward<TArgs>(args)...}
{
}

template<typename T>
auto ParametricPath<T>::GetClone() const noexcept -> std::unique_ptr<IPath>
{
  return std::make_unique<ParametricPath<T>>(std::make_unique<TValue>(GetPositionT()),
                                             m_parametricFunction);
}

template<typename T>
inline auto ParametricPath<T>::GetParametricFunction() noexcept -> T&
{
  return m_parametricFunction;
}

template<typename T>
inline auto ParametricPath<T>::GetNextPoint() const noexcept -> Point2dInt
{
  return m_parametricFunction.GetPoint(GetCurrentT()).ToInt();
}

} // namespace GOOM::UTILS::MATH
