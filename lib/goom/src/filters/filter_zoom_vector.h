#ifndef VISUALIZATION_GOOM_FILTER_ZOOM_VECTOR_H
#define VISUALIZATION_GOOM_FILTER_ZOOM_VECTOR_H

#include "filter_normalized_coords.h"
#include "goom_zoom_vector.h"
#include "v2d.h"

#include <memory>

#if __cplusplus <= 201402L
namespace GOOM
{

class FilterStats;
struct ZoomFilterData;

namespace FILTERS
{
#else
namespace GOOM
{
class FilterStats;
struct ZoomFilterData;
}; // namespace GOOM
namespace GOOM::FILTERS
{
#endif

class ZoomVectorEffects;

class FilterZoomVector : public IZoomVector
{
public:
  FilterZoomVector() noexcept;
  FilterZoomVector(const FilterZoomVector&) noexcept = delete;
  FilterZoomVector(FilterZoomVector&&) noexcept = delete;
  ~FilterZoomVector() noexcept override;
  auto operator=(const FilterZoomVector&) -> FilterZoomVector& = delete;
  auto operator=(FilterZoomVector&&) -> FilterZoomVector& = delete;

  auto GetFilterStats() const -> FilterStats* override;
  void SetFilterStats(FilterStats& stats) override;

  auto GetFilterSettings() const -> const ZoomFilterData* override;
  void SetFilterSettings(const ZoomFilterData& filterSettings) override;

  auto GetMaxSpeedCoeff() const -> float override;
  void SetMaxSpeedCoeff(float val) override;

  auto GetZoomPoint(const NormalizedCoords& coords) const -> NormalizedCoords override;

private:
  const ZoomFilterData* m_filterSettings{};
  std::unique_ptr<ZoomVectorEffects> m_zoomVectorEffects;
  mutable FilterStats* m_stats{};

  void UpdateDoZoomVectorNoisifyStats() const;
  void UpdateDoZoomVectorHypercosEffectStats() const;
  void UpdateDoZoomVectorHPlaneEffectStats() const;
  void UpdateDoZoomVectorVPlaneEffectStats() const;
};

#if __cplusplus <= 201402L
} // namespace FILTERS
} // namespace GOOM
#else
} // namespace GOOM::FILTERS
#endif

#endif //VISUALIZATION_GOOM_FILTER_ZOOM_VECTOR_H
