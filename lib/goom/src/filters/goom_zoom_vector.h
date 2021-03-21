#ifndef VISUALIZATION_GOOM_GOOM_ZOOM_VECTOR_H
#define VISUALIZATION_GOOM_GOOM_ZOOM_VECTOR_H

#include "v2d.h"

#if __cplusplus <= 201402L
namespace GOOM
{

class FilterStats;
struct ZoomFilterData;

namespace FILTERS
{

class NormalizedCoords;
#else
namespace GOOM
{
class FilterStats;
struct ZoomFilterData;
}; // namespace GOOM
namespace GOOM::FILTERS
{
#endif

class IZoomVector
{
public:
  IZoomVector() noexcept = default;
  IZoomVector(const IZoomVector&) noexcept = delete;
  IZoomVector(IZoomVector&&) noexcept = delete;
  virtual ~IZoomVector() noexcept = default;
  auto operator=(const IZoomVector&) -> IZoomVector& = delete;
  auto operator=(IZoomVector&&) -> IZoomVector& = delete;

  virtual auto GetFilterStats() const -> FilterStats* = 0;
  virtual void SetFilterStats(FilterStats& stats) = 0;

  virtual auto GetFilterSettings() const -> const ZoomFilterData* = 0;
  virtual void SetFilterSettings(const ZoomFilterData& filterSettings) = 0;

  virtual auto GetMaxSpeedCoeff() const -> float = 0;
  virtual void SetMaxSpeedCoeff(float val) = 0;

  virtual auto GetZoomPoint(const NormalizedCoords& coords) const -> NormalizedCoords = 0;
};

#if __cplusplus <= 201402L
} // namespace FILTERS
} // namespace GOOM
#else
} // namespace GOOM::FILTERS
#endif

#endif //VISUALIZATION_GOOM_GOOM_ZOOM_VECTOR_H
