#include "filter_zoom_vector.h"

#include "../stats/filter_stats.h"
#include "filter_data.h"
#include "filter_normalized_coords.h"
#include "filter_zoom_vector_effects.h"

#include <memory>

#if __cplusplus <= 201402L
namespace GOOM
{
namespace FILTERS
{
#else
namespace GOOM::FILTERS
{
#endif

using UTILS::GetRandInRange;
using UTILS::SMALL_FLOAT;
using UTILS::SqDistance;

FilterZoomVector::FilterZoomVector() noexcept
  : m_zoomVectorEffects{std::make_unique<ZoomVectorEffects>()}
{
}

FilterZoomVector::~FilterZoomVector() noexcept = default;

auto FilterZoomVector::GetFilterStats() const -> FilterStats*
{
  return m_stats;
}

void FilterZoomVector::SetFilterStats(FilterStats& stats)
{
  m_stats = &stats;
  m_zoomVectorEffects->SetFilterStats(stats);
}

auto FilterZoomVector::GetFilterSettings() const -> const ZoomFilterData*
{
  return m_filterSettings;
}

void FilterZoomVector::SetFilterSettings(const ZoomFilterData& filterSettings)
{
  m_filterSettings = &filterSettings;
  m_zoomVectorEffects->SetFilterSettings(filterSettings);
}

auto FilterZoomVector::GetMaxSpeedCoeff() const -> float
{
  return m_zoomVectorEffects->GetMaxSpeedCoeff();
}

void FilterZoomVector::SetMaxSpeedCoeff(const float val)
{
  m_zoomVectorEffects->SetMaxSpeedCoeff(val);
}

auto FilterZoomVector::GetZoomPoint(const NormalizedCoords& coords) const -> NormalizedCoords
{
  const float sqDistFromZero = SqDistance(coords.GetX(), coords.GetY());

  NormalizedCoords velocity = m_zoomVectorEffects->GetStandardVelocity(sqDistFromZero, coords);

  // The Effects add-ons...
  if (std::fabs(m_filterSettings->rotateSpeed) > SMALL_FLOAT)
  {
    velocity = m_zoomVectorEffects->GetRotatedVelocity(velocity);
  }
  if (m_filterSettings->tanEffect)
  {
    velocity = m_zoomVectorEffects->GetTanEffectVelocity(sqDistFromZero, velocity);
  }
  if (m_filterSettings->noisify)
  {
    UpdateDoZoomVectorNoisifyStats();
    velocity += m_zoomVectorEffects->GetNoiseVelocity();
  }
  if (m_filterSettings->hypercosEffect != ZoomFilterData::HypercosEffect::NONE)
  {
    UpdateDoZoomVectorHypercosEffectStats();
    velocity += m_zoomVectorEffects->GetHypercosVelocity(coords);
  }
  if (m_filterSettings->hPlaneEffect != 0)
  {
    UpdateDoZoomVectorHPlaneEffectStats();
    velocity.SetX(velocity.GetX() + m_zoomVectorEffects->GetHPlaneEffectVelocity(coords));
  }
  if (m_filterSettings->vPlaneEffect != 0)
  {
    UpdateDoZoomVectorVPlaneEffectStats();
    velocity.SetY(velocity.GetY() + m_zoomVectorEffects->GetVPlaneEffectVelocity(coords));
  }
  /* TODO : Water Mode */
  //    if (data->waveEffect)

  /**
  if (m_filterSettings->mode == ZoomFilterMode::NORMAL_MODE)
    if (ProbabilityOfMInN(1, 2))
      velocity = {-2.0F * xNormalized + velocity.x, -2.0F * yNormalized + velocity.y};
  **/

  return coords - m_zoomVectorEffects->GetCleanedVelocity(velocity);
}

inline void FilterZoomVector::UpdateDoZoomVectorNoisifyStats() const
{
  if (m_stats == nullptr)
  {
    return;
  }
  m_stats->DoZoomVectorNoisify();
}

inline void FilterZoomVector::UpdateDoZoomVectorHypercosEffectStats() const
{
  if (m_stats == nullptr)
  {
    return;
  }
  m_stats->DoZoomVectorHypercosEffect();
}

inline void FilterZoomVector::UpdateDoZoomVectorHPlaneEffectStats() const
{
  if (m_stats == nullptr)
  {
    return;
  }
  m_stats->DoZoomVectorHPlaneEffect();
}

inline void FilterZoomVector::UpdateDoZoomVectorVPlaneEffectStats() const
{
  if (m_stats == nullptr)
  {
    return;
  }
  m_stats->DoZoomVectorVPlaneEffect();
}

#if __cplusplus <= 201402L
} // namespace FILTERS
} // namespace GOOM
#else
} // namespace GOOM::FILTERS
#endif
