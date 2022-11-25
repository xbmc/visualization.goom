#include "zoom_transform_buffers.h"

#include "goom_types.h"
#include "point2d.h"
#include "zoom_coord_transforms.h"

#include <algorithm>

namespace GOOM::FILTER_FX::FILTER_UTILS
{

ZoomTransformBuffers::ZoomTransformBuffers(const Dimensions& dimensions,
                                           const Point2dInt& maxTranPoint) noexcept
  : m_dimensions{dimensions},
    m_maxTranPointMinus1{maxTranPoint - Vec2dInt{1, 1}},
    m_tranSrce(m_bufferSize),
    m_tranDest(m_bufferSize),
    m_tranTemp(m_bufferSize)
{
}

auto ZoomTransformBuffers::SetSrceTranToIdentity() noexcept -> void
{
  auto buffPos = 0U;
  for (auto y = 0; y < m_dimensions.GetIntHeight(); ++y)
  {
    for (auto x = 0; x < m_dimensions.GetIntWidth(); ++x)
    {
      m_tranSrce[buffPos] = ZoomCoordTransforms::ScreenToTranPoint({x, y});
      ++buffPos;
    }
  }
}

auto ZoomTransformBuffers::CopyDestTranToSrceTran() noexcept -> void
{
  // sauvegarde de l'etat actuel dans la nouvelle source
  // Save the current state in the source buff.
  if (0 == GetTranLerpFactor())
  {
    // Nothing to do: tran srce == tran dest.
  }
  else if (GetTranLerpFactor() == MAX_TRAN_LERP_VALUE)
  {
    std::copy(cbegin(m_tranDest), cend(m_tranDest), begin(m_tranSrce));
  }
  else
  {
    // Lerp and copy the dest buff to the source buff.
    for (auto buffPos = 0U; buffPos < m_bufferSize; ++buffPos)
    {
      m_tranSrce[buffPos] = GetSrceDestLerpBufferPoint(buffPos);
    }
  }
}

} // namespace GOOM::FILTER_FX::FILTER_UTILS
