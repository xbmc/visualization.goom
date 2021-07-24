#ifndef VISUALIZATION_GOOM_FILTER_ZOOM_VECTOR_EFFECTS_H
#define VISUALIZATION_GOOM_FILTER_ZOOM_VECTOR_EFFECTS_H

#include "filter_normalized_coords.h"

#if __cplusplus <= 201402L
namespace GOOM
{

class FilterStats;
struct ZoomFilterData;

namespace FILTERS
{
#else
namespace GOOM::FILTERS
{
#endif

class ZoomVectorEffects
{
public:
  ZoomVectorEffects() noexcept;

  void SetFilterSettings(const ZoomFilterData& filterSettings);
  void SetFilterStats(FilterStats& stats);

  auto GetMaxSpeedCoeff() const -> float;
  void SetMaxSpeedCoeff(float val);

  auto GetStandardVelocity(float sqDistFromZero, const NormalizedCoords& coords) const
      -> NormalizedCoords;
  static auto GetCleanedVelocity(const NormalizedCoords& velocity) -> NormalizedCoords;
  auto GetRotatedVelocity(const NormalizedCoords& velocity) const -> NormalizedCoords;
  auto GetNoiseVelocity() const -> NormalizedCoords;
  auto GetTanEffectVelocity(float sqDistFromZero, const NormalizedCoords& velocity) const
      -> NormalizedCoords;
  auto GetHPlaneEffectVelocity(const NormalizedCoords& coords) const -> float;
  auto GetHypercosVelocity(const NormalizedCoords& coords) const -> NormalizedCoords;
  auto GetVPlaneEffectVelocity(const NormalizedCoords& coords) const -> float;

private:
  const ZoomFilterData* m_filterSettings{};
  mutable FilterStats* m_stats{};
  float m_maxSpeedCoeff;

  auto GetSpeedCoeffVelocity(float sqDistFromZero, const NormalizedCoords& coords) const
      -> NormalizedCoords;
  auto GetImageDisplacementVelocity(const NormalizedCoords& coords) const -> NormalizedCoords;
  auto GetSpeedCoefficient(float sqDistFromZero, const NormalizedCoords& coords) const -> float;
  auto GetWaveEffectSpeedCoeff(float sqDistFromZero) const -> float;
  auto GetYOnlySpeedCoeff(const NormalizedCoords& coords) const -> float;
  auto GetClampedSpeedCoeff(float speedCoeff) const -> float;

  void UpdateDoZoomVectorSpeedCoeffBelowMinStats() const;
  void UpdateDoZoomVectorSpeedCoeffAboveMaxStats() const;
  void UpdateDoZoomVectorNoiseFactorStats() const;
  void UpdateDoZoomVectorTanEffectStats() const;
  void UpdateDoZoomVectorNegativeRotateStats() const;
  void UpdateDoZoomVectorPositiveRotateStats() const;
};

inline auto ZoomVectorEffects::GetMaxSpeedCoeff() const -> float
{
  return m_maxSpeedCoeff;
}

inline void ZoomVectorEffects::SetMaxSpeedCoeff(const float val)
{
  m_maxSpeedCoeff = val;
}

#if __cplusplus <= 201402L
} // namespace FILTERS
} // namespace GOOM
#else
} // namespace GOOM::FILTERS
#endif

#endif //VISUALIZATION_GOOM_FILTER_ZOOM_VECTOR_EFFECTS_H
