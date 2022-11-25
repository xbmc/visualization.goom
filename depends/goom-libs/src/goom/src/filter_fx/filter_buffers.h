#pragma once

#include "filter_utils/zoom_coord_transforms.h"
#include "filter_utils/zoom_filter_coefficients.h"
#include "filter_utils/zoom_transform_buffers.h"
#include "goom_graphic.h"
#include "goom_types.h"
#include "normalized_coords.h"
#include "point2d.h"

#include <cmath>
#include <cstdint>
#include <functional>
#include <vector>

namespace GOOM
{

class PluginInfo;

namespace UTILS
{
class Parallel;
}

} // namespace GOOM

namespace GOOM::FILTER_FX
{

class ZoomFilterBuffers
{
public:
  static constexpr float MIN_SCREEN_COORD_ABS_VAL =
      1.0F / static_cast<float>(FILTER_UTILS::ZOOM_FILTER_COEFFS::DIM_FILTER_COEFFS);

  enum class TranBuffersState
  {
    START_FRESH_TRAN_BUFFERS,
    RESET_TRAN_BUFFERS,
    TRAN_BUFFERS_READY,
  };

  using ZoomPointFunc =
      std::function<NormalizedCoords(const NormalizedCoords& normalizedCoords,
                                     const NormalizedCoords& normalizedFilterViewportCoords)>;

  ZoomFilterBuffers(UTILS::Parallel& parallel,
                    const PluginInfo& goomInfo,
                    const NormalizedCoordsConverter& normalizedCoordsConverter,
                    const ZoomPointFunc& zoomPointFunc) noexcept;
  ZoomFilterBuffers(const ZoomFilterBuffers&) noexcept = delete;
  ZoomFilterBuffers(ZoomFilterBuffers&&) noexcept      = delete;
  ~ZoomFilterBuffers() noexcept;
  auto operator=(const ZoomFilterBuffers&) noexcept -> ZoomFilterBuffers& = delete;
  auto operator=(ZoomFilterBuffers&&) noexcept -> ZoomFilterBuffers&      = delete;

  [[nodiscard]] auto GetBuffMidpoint() const noexcept -> Point2dInt;
  auto SetBuffMidpoint(const Point2dInt& val) noexcept -> void;

  [[nodiscard]] auto GetFilterViewport() const noexcept -> Viewport;
  auto SetFilterViewport(const Viewport& val) noexcept -> void;

  [[nodiscard]] auto GetTranLerpFactor() const noexcept -> uint32_t;
  auto SetTranLerpFactor(uint32_t val) noexcept -> void;
  [[nodiscard]] static auto GetMaxTranLerpFactor() noexcept -> uint32_t;

  [[nodiscard]] auto GetTranBuffYLineStart() const noexcept -> uint32_t;

  auto Start() noexcept -> void;

  auto NotifyFilterSettingsHaveChanged() noexcept -> void;
  [[nodiscard]] auto HaveFilterSettingsChanged() const noexcept -> bool;

  auto UpdateTranBuffers() noexcept -> void;
  [[nodiscard]] auto GetTranBuffersState() const noexcept -> TranBuffersState;

  struct SourcePointInfo
  {
    Point2dInt screenPoint;
    const FILTER_UTILS::ZOOM_FILTER_COEFFS::NeighborhoodCoeffArray* coeffs;
    bool isClipped;
  };
  [[nodiscard]] auto GetSourcePointInfo(size_t buffPos) const noexcept -> SourcePointInfo;

  [[nodiscard]] auto GetZoomBufferTranPoint(size_t buffPos, bool& isClipped) const noexcept
      -> Point2dInt;

  [[nodiscard]] auto GetTransformBuffers() const noexcept
      -> const FILTER_UTILS::ZoomTransformBuffers&
  {
    return m_transformBuffers;
  }

private:
  const Dimensions m_dimensions;
  const NormalizedCoordsConverter& m_normalizedCoordsConverter;
  const FILTER_UTILS::ZoomCoordTransforms m_coordTransforms{m_dimensions};

  [[nodiscard]] auto GetMaxTranX() const noexcept -> uint32_t;
  [[nodiscard]] auto GetMaxTranY() const noexcept -> uint32_t;

  UTILS::Parallel& m_parallel;
  const ZoomPointFunc m_getZoomPoint;
  const Point2dInt m_maxTranPoint = FILTER_UTILS::ZoomCoordTransforms::ScreenToTranPoint(
      {m_dimensions.GetIntWidth() - 1, m_dimensions.GetIntHeight() - 1});
  // 'NUM_STRIPE_GROUPS' controls how many updates before all stripes, and therefore,
  // all the tran buffer is filled. We use stripes to spread the buffer update load
  // over a number of updates. Too few and performance suffers periodically for a
  // number of updates; too many, and performance suffers overall.
  static constexpr uint32_t NUM_STRIPE_GROUPS = 16U;
  const uint32_t m_tranBuffStripeHeight       = m_dimensions.GetHeight() / NUM_STRIPE_GROUPS;
  FILTER_UTILS::ZoomTransformBuffers m_transformBuffers{m_dimensions, m_maxTranPoint};

  Point2dInt m_buffMidpoint             = {0, 0};
  NormalizedCoords m_normalizedMidpoint = {0.0F, 0.0F};
  Viewport m_filterViewport             = Viewport{};
  bool m_filterSettingsHaveChanged      = false;

  uint32_t m_tranBuffYLineStart       = 0;
  TranBuffersState m_tranBuffersState = TranBuffersState::TRAN_BUFFERS_READY;

  std::vector<int32_t> m_firedec;

  auto InitAllTranBuffers() noexcept -> void;
  auto StartFreshTranBuffers() noexcept -> void;
  auto ResetTranBuffers() noexcept -> void;
  auto FillTempTranBuffers() noexcept -> void;
  auto DoNextTempTranBuffersStripe(uint32_t tranBuffStripeHeight) noexcept -> void;
  auto GenerateWaterFxHorizontalBuffer() noexcept -> void;
  [[nodiscard]] auto GetTranPoint(const NormalizedCoords& normalized) const noexcept -> Point2dInt;
};

inline auto ZoomFilterBuffers::GetBuffMidpoint() const noexcept -> Point2dInt
{
  return m_buffMidpoint;
}

inline auto ZoomFilterBuffers::SetBuffMidpoint(const Point2dInt& val) noexcept -> void
{
  m_buffMidpoint       = val;
  m_normalizedMidpoint = m_normalizedCoordsConverter.OtherToNormalizedCoords(m_buffMidpoint);
}

inline auto ZoomFilterBuffers::GetFilterViewport() const noexcept -> Viewport
{
  return m_filterViewport;
}

inline auto ZoomFilterBuffers::SetFilterViewport(const Viewport& val) noexcept -> void
{
  m_filterViewport = val;
}

inline auto ZoomFilterBuffers::GetTranBuffersState() const noexcept -> TranBuffersState
{
  return m_tranBuffersState;
}

inline auto ZoomFilterBuffers::GetTranLerpFactor() const noexcept -> uint32_t
{
  return m_transformBuffers.GetTranLerpFactor();
}

inline auto ZoomFilterBuffers::GetMaxTranLerpFactor() noexcept -> uint32_t
{
  return FILTER_UTILS::ZoomTransformBuffers::MAX_TRAN_LERP_VALUE;
}

inline auto ZoomFilterBuffers::SetTranLerpFactor(const uint32_t val) noexcept -> void
{
  m_transformBuffers.SetTranLerpFactor(val);
}

inline auto ZoomFilterBuffers::GetMaxTranX() const noexcept -> uint32_t
{
  return static_cast<uint32_t>(m_maxTranPoint.x);
}

inline auto ZoomFilterBuffers::GetMaxTranY() const noexcept -> uint32_t
{
  return static_cast<uint32_t>(m_maxTranPoint.y);
}

inline auto ZoomFilterBuffers::GetTranBuffYLineStart() const noexcept -> uint32_t
{
  return m_tranBuffYLineStart;
}

} // namespace GOOM::FILTER_FX
