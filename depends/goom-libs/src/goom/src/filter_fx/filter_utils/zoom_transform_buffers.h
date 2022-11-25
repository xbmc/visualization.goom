#pragma once

#include "goom_types.h"
#include "point2d.h"
#include "utils/math/misc.h"
#include "zoom_coord_transforms.h"

#include <algorithm>
#include <cstdint>
#include <vector>

namespace GOOM::FILTER_FX::FILTER_UTILS
{

class ZoomTransformBuffers
{
  static constexpr auto MAX_TRAN_LERP_EXP = 16U;

public:
  static constexpr auto MAX_TRAN_LERP_VALUE = UTILS::MATH::PowerOf2(MAX_TRAN_LERP_EXP);

  ZoomTransformBuffers(const Dimensions& dimensions, const Point2dInt& maxTranPoint) noexcept;

  auto SetSrceTranToIdentity() noexcept -> void;
  auto CopyTempTranToDestTran() noexcept -> void;
  auto CopyDestTranToSrceTran() noexcept -> void;
  auto SetUpNextDestTran() noexcept -> void;

  auto SetTempBuffersTransformPoint(uint32_t buffPos, const Point2dInt& transformPoint) noexcept
      -> void;

  [[nodiscard]] auto GetTranLerpFactor() const noexcept -> uint32_t;
  auto SetTranLerpFactor(uint32_t val) noexcept -> void;

  [[nodiscard]] auto GetSrceDestLerpBufferPoint(size_t buffPos, bool& isClipped) const noexcept
      -> Point2dInt;

  [[nodiscard]] static auto GetTranBuffLerpPoint(Point2dInt srcePoint,
                                                 Point2dInt destPoint,
                                                 uint32_t t) noexcept -> Point2dInt;

  [[nodiscard]] auto GetTranSrce(const size_t buffPos) const noexcept -> Point2dInt
  {
    return m_tranSrce[buffPos];
  }
  [[nodiscard]] auto GetTranDest(const size_t buffPos) const noexcept -> Point2dInt
  {
    return m_tranDest[buffPos];
  }

private:
  const Dimensions m_dimensions;
  const uint32_t m_bufferSize = m_dimensions.GetSize();
  const Point2dInt m_maxTranPointMinus1;
  std::vector<Point2dInt> m_tranSrce;
  std::vector<Point2dInt> m_tranDest;
  std::vector<Point2dInt> m_tranTemp;
  uint32_t m_tranLerpFactor = 0U;

  [[nodiscard]] auto GetSrceDestLerpBufferPoint(size_t buffPos) const noexcept -> Point2dInt;
  [[nodiscard]] static auto GetTranBuffLerpVal(int32_t srceBuffVal,
                                               int32_t destBuffVal,
                                               uint32_t t) noexcept -> int32_t;
  [[nodiscard]] auto GetClampedXVal(int32_t x) const noexcept -> int32_t;
  [[nodiscard]] auto GetClampedYVal(int32_t y) const noexcept -> int32_t;
};

inline auto ZoomTransformBuffers::CopyTempTranToDestTran() noexcept -> void
{
  std::copy(cbegin(m_tranTemp), cend(m_tranTemp), begin(m_tranDest));
}

inline auto ZoomTransformBuffers::SetUpNextDestTran() noexcept -> void
{
  std::swap(m_tranDest, m_tranTemp);
}

inline auto ZoomTransformBuffers::SetTempBuffersTransformPoint(
    const uint32_t buffPos, const Point2dInt& transformPoint) noexcept -> void
{
  m_tranTemp[buffPos] = transformPoint;
}

inline auto ZoomTransformBuffers::GetTranLerpFactor() const noexcept -> uint32_t
{
  return m_tranLerpFactor;
}

inline auto ZoomTransformBuffers::SetTranLerpFactor(const uint32_t val) noexcept -> void
{
  m_tranLerpFactor = val;
}

inline auto ZoomTransformBuffers::GetSrceDestLerpBufferPoint(const size_t buffPos) const noexcept
    -> Point2dInt
{
  auto isClipped = false;
  return GetSrceDestLerpBufferPoint(buffPos, isClipped);
}

inline auto ZoomTransformBuffers::GetSrceDestLerpBufferPoint(const size_t buffPos,
                                                             bool& isClipped) const noexcept
    -> Point2dInt
{
  const auto lerpPoint =
      GetTranBuffLerpPoint(m_tranSrce[buffPos], m_tranDest[buffPos], m_tranLerpFactor);

  if (lerpPoint.x < 0)
  {
    isClipped = true;
    return {0, GetClampedYVal(lerpPoint.y)};
  }
  if (lerpPoint.x > m_maxTranPointMinus1.x)
  {
    isClipped = true;
    return {m_maxTranPointMinus1.x, GetClampedYVal(lerpPoint.y)};
  }

  if (lerpPoint.y < 0)
  {
    isClipped = true;
    return {GetClampedXVal(lerpPoint.x), 0};
  }
  if (lerpPoint.y > m_maxTranPointMinus1.y)
  {
    isClipped = true;
    return {GetClampedXVal(lerpPoint.x), m_maxTranPointMinus1.y};
  }

  return lerpPoint;
}

inline auto ZoomTransformBuffers::GetClampedXVal(const int32_t x) const noexcept -> int32_t
{
  return std::clamp(x, 0, m_maxTranPointMinus1.x);
}

inline auto ZoomTransformBuffers::GetClampedYVal(const int32_t y) const noexcept -> int32_t
{
  return std::clamp(y, 0, m_maxTranPointMinus1.y);
}

inline auto ZoomTransformBuffers::GetTranBuffLerpPoint(const Point2dInt srcePoint,
                                                       const Point2dInt destPoint,
                                                       const uint32_t t) noexcept -> Point2dInt
{
  return {GetTranBuffLerpVal(srcePoint.x, destPoint.x, t),
          GetTranBuffLerpVal(srcePoint.y, destPoint.y, t)};
}

inline auto ZoomTransformBuffers::GetTranBuffLerpVal(const int32_t srceBuffVal,
                                                     const int32_t destBuffVal,
                                                     const uint32_t t) noexcept -> int32_t
{
  const auto diff      = static_cast<int64_t>(destBuffVal - srceBuffVal);
  const auto numerator = static_cast<int64_t>(t) * diff;
  const auto result =
      static_cast<int32_t>(static_cast<int64_t>(srceBuffVal) + (numerator >> MAX_TRAN_LERP_EXP));

  if (const auto mod = numerator & static_cast<int64_t>(MAX_TRAN_LERP_VALUE - 1U);
      mod >= static_cast<int64_t>(MAX_TRAN_LERP_VALUE / 2))
  {
    return result + 1;
  }
  return result;
}

} // namespace GOOM::FILTER_FX::FILTER_UTILS
