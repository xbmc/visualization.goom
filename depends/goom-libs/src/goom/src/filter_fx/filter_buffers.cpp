#include "filter_buffers.h"

//#undef NO_LOGGING

#include "filter_utils/zoom_coord_transforms.h"
#include "filter_utils/zoom_filter_coefficients.h"
#include "goom_config.h"
#include "goom_plugin_info.h"
#include "logging.h"
#include "normalized_coords.h"
#include "point2d.h"
#include "utils/parallel_utils.h"

#include <cmath>
#include <cstdint>

namespace GOOM::FILTER_FX
{

using FILTER_UTILS::ZoomCoordTransforms;
using FILTER_UTILS::ZOOM_FILTER_COEFFS::PRECALCULATED_COEFF_PTRS;
using UTILS::Logging; // NOLINT(misc-unused-using-decls)
using UTILS::Parallel;

ZoomFilterBuffers::ZoomFilterBuffers(Parallel& parallel,
                                     const PluginInfo& goomInfo,
                                     const NormalizedCoordsConverter& normalizedCoordsConverter,
                                     const ZoomPointFunc& zoomPointFunc) noexcept
  : m_dimensions{goomInfo.GetScreenDimensions()},
    m_normalizedCoordsConverter{normalizedCoordsConverter},
    m_parallel{parallel},
    m_getZoomPoint{zoomPointFunc},
    m_firedec(m_dimensions.GetHeight())
{
}

ZoomFilterBuffers::~ZoomFilterBuffers() noexcept = default;

auto ZoomFilterBuffers::Start() noexcept -> void
{
  InitAllTranBuffers();
}

auto ZoomFilterBuffers::GetSourcePointInfo(const size_t buffPos) const noexcept -> SourcePointInfo
{
  auto isClipped       = false;
  const auto tranPoint = GetZoomBufferTranPoint(buffPos, isClipped);

  const auto srceScreenPoint  = ZoomCoordTransforms::TranToScreenPoint(tranPoint);
  const auto [xIndex, yIndex] = ZoomCoordTransforms::TranCoordToZoomCoeffIndexes(tranPoint);

  return SourcePointInfo{srceScreenPoint, PRECALCULATED_COEFF_PTRS[xIndex][yIndex], isClipped};
}

auto ZoomFilterBuffers::GetZoomBufferTranPoint(const size_t buffPos, bool& isClipped) const noexcept
    -> Point2dInt
{
  return m_transformBuffers.GetSrceDestLerpBufferPoint(buffPos, isClipped);
}

auto ZoomFilterBuffers::HaveFilterSettingsChanged() const noexcept -> bool
{
  return m_filterSettingsHaveChanged;
}

auto ZoomFilterBuffers::NotifyFilterSettingsHaveChanged() noexcept -> void
{
  m_filterSettingsHaveChanged = true;
}

auto ZoomFilterBuffers::InitAllTranBuffers() noexcept -> void
{
  m_tranBuffersState = TranBuffersState::TRAN_BUFFERS_READY;

  GenerateWaterFxHorizontalBuffer();

  FillTempTranBuffers();

  m_transformBuffers.SetSrceTranToIdentity();
  m_transformBuffers.CopyTempTranToDestTran();

  m_tranBuffYLineStart = 0;
  m_tranBuffersState   = TranBuffersState::START_FRESH_TRAN_BUFFERS;
}

auto ZoomFilterBuffers::UpdateTranBuffers() noexcept -> void
{
  if (m_tranBuffersState == TranBuffersState::RESET_TRAN_BUFFERS)
  {
    ResetTranBuffers();
  }
  else if (m_tranBuffersState == TranBuffersState::START_FRESH_TRAN_BUFFERS)
  {
    StartFreshTranBuffers();
  }
  else
  {
    // Create a new destination stripe of 'm_tranBuffStripeHeight' height starting
    // at 'm_tranBuffYLineStart'.
    DoNextTempTranBuffersStripe(m_tranBuffStripeHeight);
  }
}

// generation du buffer de transform
auto ZoomFilterBuffers::ResetTranBuffers() noexcept -> void
{
  m_transformBuffers.CopyDestTranToSrceTran();
  m_transformBuffers.SetUpNextDestTran();

  m_transformBuffers.SetTranLerpFactor(0);
  m_tranBuffYLineStart = 0;
  m_tranBuffersState   = TranBuffersState::START_FRESH_TRAN_BUFFERS;
}

auto ZoomFilterBuffers::StartFreshTranBuffers() noexcept -> void
{
  if (not m_filterSettingsHaveChanged)
  {
    return;
  }

  m_filterSettingsHaveChanged = false;
  m_tranBuffYLineStart        = 0;
  m_tranBuffersState          = TranBuffersState::TRAN_BUFFERS_READY;
}

inline auto ZoomFilterBuffers::FillTempTranBuffers() noexcept -> void
{
  DoNextTempTranBuffersStripe(m_dimensions.GetHeight());
}

/*
 * Makes a stripe of a transform buffer
 *
 * The transform is (in order) :
 * Translation (-data->middleX, -data->middleY)
 * Homothetie (Center : 0,0   Coeff : 2/data->screenWidth)
 */
auto ZoomFilterBuffers::DoNextTempTranBuffersStripe(const uint32_t tranBuffStripeHeight) noexcept
    -> void
{
  Expects(m_tranBuffersState == TranBuffersState::TRAN_BUFFERS_READY);

  const auto screenWidth                  = m_dimensions.GetWidth();
  const auto screenSpan                   = static_cast<float>(screenWidth - 1);
  const auto sourceCoordsStepSize         = NormalizedCoords::COORD_WIDTH / screenSpan;
  const auto sourceViewportCoordsStepSize = m_filterViewport.GetViewportWidth() / screenSpan;

  const auto doStripeLine =
      [this, &screenWidth, &sourceCoordsStepSize, &sourceViewportCoordsStepSize](const size_t y)
  {
    // Y-position of the first stripe pixel to compute in screen coordinates.
    const auto yScreenCoord = static_cast<uint32_t>(y) + m_tranBuffYLineStart;
    auto tranBufferPos      = yScreenCoord * screenWidth;

    auto centredSourceCoords =
        m_normalizedCoordsConverter.OtherToNormalizedCoords(Point2dInt{0U, yScreenCoord}) -
        m_normalizedMidpoint;
    auto centredSourceViewportCoords = m_filterViewport.GetViewportCoords(centredSourceCoords);

    for (auto x = 0U; x < screenWidth; ++x)
    {
      const auto zoomCoords = m_getZoomPoint(centredSourceCoords, centredSourceViewportCoords);
      const auto uncenteredZoomCoords = m_normalizedMidpoint + zoomCoords;

      m_transformBuffers.SetTempBuffersTransformPoint(tranBufferPos,
                                                      GetTranPoint(uncenteredZoomCoords));

      centredSourceCoords.IncX(sourceCoordsStepSize);
      centredSourceViewportCoords.IncX(sourceViewportCoordsStepSize);
      ++tranBufferPos;
    }
  };

  // Where (vertically) to stop generating the buffer stripe
  const auto tranBuffYLineEnd =
      std::min(m_dimensions.GetHeight(), m_tranBuffYLineStart + tranBuffStripeHeight);
  const auto numStripes = static_cast<size_t>(tranBuffYLineEnd - m_tranBuffYLineStart);

  m_parallel.ForLoop(numStripes, doStripeLine);

  m_tranBuffYLineStart += tranBuffStripeHeight;
  if (tranBuffYLineEnd >= m_dimensions.GetHeight())
  {
    m_tranBuffersState   = TranBuffersState::RESET_TRAN_BUFFERS;
    m_tranBuffYLineStart = 0;
  }
}

inline auto ZoomFilterBuffers::GetTranPoint(const NormalizedCoords& normalized) const noexcept
    -> Point2dInt
{
  return m_coordTransforms.NormalizedToTranPoint(normalized);

  /**
  int32_t tranX = NormalizedToTranPoint(xNormalised);
  if (tranX < 0)
  {
    tranX = -1;
  }
  else if (tranX >= static_cast<int32_t>(m_maxTranX))
  {
    //    tranX = static_cast<int32_t>(m_maxTranX - 1);
    tranX = static_cast<int32_t>(m_maxTranX);
  }

  int32_t tranY = NormalizedToTranPoint(yNormalised);
  if (tranY < 0)
  {
    tranY = -1;
  }
  else if (tranY >= static_cast<int32_t>(m_maxTranY))
  {
    //    tranY = static_cast<int32_t>(m_maxTranY - 1);
    tranY = static_cast<int32_t>(m_maxTranY);
  }

  return std::make_tuple(tranX, tranY);
   **/
}

auto ZoomFilterBuffers::GenerateWaterFxHorizontalBuffer() noexcept -> void
{
  /*****************
  int32_t decc = m_goomRand.GetRandInRange(-4, +4);
  int32_t spdc = m_goomRand.GetRandInRange(-4, +4);
  int32_t accel = m_goomRand.GetRandInRange(-4, +4);

  for (size_t loopv = m_screenHeight; loopv != 0;)
  {
    --loopv;
    m_firedec[loopv] = decc;
    decc += spdc / 10;
    spdc += m_goomRand.GetRandInRange(-2, +3);

    if (decc > 4)
    {
      spdc -= 1;
    }
    if (decc < -4)
    {
      spdc += 1;
    }

    if (spdc > 30)
    {
      spdc = (spdc - static_cast<int32_t>(m_goomRand.GetNRand(3))) + (accel / 10);
    }
    if (spdc < -30)
    {
      spdc = spdc + static_cast<int32_t>(m_goomRand.GetNRand(3)) + (accel / 10);
    }

    if ((decc > 8) && (spdc > 1))
    {
      spdc -= m_goomRand.GetRandInRange(-2, +1);
    }
    if ((decc < -8) && (spdc < -1))
    {
      spdc += static_cast<int32_t>(m_goomRand.GetNRand(3)) + 2;
    }
    if ((decc > 8) || (decc < -8))
    {
      decc = (decc * 8) / 9;
    }

    accel += m_goomRand.GetRandInRange(-1, +2);
    if (accel > 20)
    {
      accel -= 2;
    }
    if (accel < -20)
    {
      accel += 2;
    }
  }
  *************************/
}

} // namespace GOOM::FILTER_FX
