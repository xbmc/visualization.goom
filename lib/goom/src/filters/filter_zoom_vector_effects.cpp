#include "filter_zoom_vector_effects.h"

#include "../stats/filter_stats.h"
#include "filter_data.h"
#include "filter_normalized_coords.h"
#include "image_displacement.h"

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
using UTILS::m_half_pi;
using UTILS::SMALL_FLOAT;

ZoomVectorEffects::ZoomVectorEffects() noexcept
  : m_maxSpeedCoeff{ZoomFilterData::DEFAULT_MAX_SPEED_COEFF}
{
}

void ZoomVectorEffects::SetFilterSettings(const ZoomFilterData& filterSettings)
{
  m_filterSettings = &filterSettings;
}

void ZoomVectorEffects::SetFilterStats(FilterStats& stats)
{
  m_stats = &stats;
}

auto ZoomVectorEffects::GetCleanedVelocity(const NormalizedCoords& velocity) const
    -> NormalizedCoords
{
  NormalizedCoords newVelocity = velocity;
  if (std::fabs(velocity.GetX()) < NormalizedCoords::GetMinNormalizedCoordVal())
  {
    newVelocity.SetX(newVelocity.GetX() < 0.0F ? -NormalizedCoords::GetMinNormalizedCoordVal()
                                               : NormalizedCoords::GetMinNormalizedCoordVal());
  }
  if (std::fabs(newVelocity.GetY()) < NormalizedCoords::GetMinNormalizedCoordVal())
  {
    newVelocity.SetY(newVelocity.GetY() < 0.0F ? -NormalizedCoords::GetMinNormalizedCoordVal()
                                               : NormalizedCoords::GetMinNormalizedCoordVal());
  }
  return newVelocity;
}

auto ZoomVectorEffects::GetStandardVelocity(const float sqDistFromZero,
                                            const NormalizedCoords& coords) const
    -> NormalizedCoords
{
  NormalizedCoords velocity = m_filterSettings->mode == ZoomFilterMode::IMAGE_DISPLACEMENT_MODE
                                  ? GetImageDisplacementVelocity(coords)
                                  : GetSpeedCoeffVelocity(sqDistFromZero, coords);

  return velocity;
}

auto ZoomVectorEffects::GetImageDisplacementVelocity(const NormalizedCoords& coords) const
    -> NormalizedCoords
{
  if (m_filterSettings->imageDisplacement == nullptr)
  {
    throw std::logic_error("No image displacement map setup.");
  }

  const V2dFlt displacement =
      m_filterSettings->imageDisplacement->GetDisplacementVector({coords.GetX(), coords.GetY()});
  return m_filterSettings->imageDisplacementAmplitude *
         NormalizedCoords{displacement.x, displacement.y};
}

auto ZoomVectorEffects::GetSpeedCoeffVelocity(const float sqDistFromZero,
                                              const NormalizedCoords& coords) const
    -> NormalizedCoords
{
  return GetSpeedCoefficient(sqDistFromZero, coords) * coords;
}

auto ZoomVectorEffects::GetSpeedCoefficient(const float sqDistFromZero,
                                            const NormalizedCoords& coords) const -> float
{
  float speedCoeff = (1.0F + m_filterSettings->vitesse.GetRelativeSpeed()) /
                     ZoomFilterData::SPEED_COEFF_DENOMINATOR;

  switch (m_filterSettings->mode)
  {
    case ZoomFilterMode::AMULET_MODE:
    {
      speedCoeff += m_filterSettings->amuletAmplitude * sqDistFromZero;
      break;
    }
    case ZoomFilterMode::CRYSTAL_BALL_MODE0:
    case ZoomFilterMode::CRYSTAL_BALL_MODE1:
    {
      speedCoeff -= m_filterSettings->crystalBallAmplitude *
                    (sqDistFromZero - m_filterSettings->crystalBallSqDistOffset);
      break;
    }
    case ZoomFilterMode::HYPERCOS_MODE0:
    case ZoomFilterMode::HYPERCOS_MODE1:
    case ZoomFilterMode::HYPERCOS_MODE2:
    case ZoomFilterMode::IMAGE_DISPLACEMENT_MODE:
    case ZoomFilterMode::NORMAL_MODE:
    {
      break;
    }
    case ZoomFilterMode::SCRUNCH_MODE:
    {
      speedCoeff += m_filterSettings->scrunchAmplitude * sqDistFromZero;
      break;
    }
    case ZoomFilterMode::SPEEDWAY_MODE:
    {
      constexpr float SQ_DIST_FACTOR = 0.01;
      speedCoeff *=
          m_filterSettings->speedwayAmplitude * (coords.GetY() + SQ_DIST_FACTOR * sqDistFromZero);
      break;
    }
    case ZoomFilterMode::WAVE_MODE0:
    case ZoomFilterMode::WAVE_MODE1:
    {
      speedCoeff += GetWaveEffectSpeedCoeff(sqDistFromZero);
      break;
    }
    case ZoomFilterMode::Y_ONLY_MODE:
    {
      speedCoeff *= GetYOnlySpeedCoeff(coords);
      break;
    }
      /* Amulette 2 */
      // vx = X * tan(dist);
      // vy = Y * tan(dist);
    default:
      throw std::logic_error(std20::format("Switch: unhandled case '{}'.", m_filterSettings->mode));
  }

  return GetClampedSpeedCoeff(speedCoeff);
}

auto ZoomVectorEffects::GetClampedSpeedCoeff(const float speedCoeff) const -> float
{
  if (speedCoeff < ZoomFilterData::MIN_SPEED_COEFF)
  {
    UpdateDoZoomVectorSpeedCoeffBelowMinStats();
    return ZoomFilterData::MIN_SPEED_COEFF;
  }
  if (speedCoeff > m_maxSpeedCoeff)
  {
    UpdateDoZoomVectorSpeedCoeffAboveMaxStats();
    return m_maxSpeedCoeff;
  }
  return speedCoeff;
}

auto ZoomVectorEffects::GetWaveEffectSpeedCoeff(const float sqDistFromZero) const -> float
{
  const float angle = m_filterSettings->waveFreqFactor * sqDistFromZero;
  float periodicPart;
  switch (m_filterSettings->waveEffectType)
  {
    case ZoomFilterData::WaveEffect::WAVE_SIN_EFFECT:
      periodicPart = std::sin(angle);
      break;
    case ZoomFilterData::WaveEffect::WAVE_COS_EFFECT:
      periodicPart = std::cos(angle);
      break;
    case ZoomFilterData::WaveEffect::WAVE_SIN_COS_EFFECT:
      periodicPart = std::sin(angle) + std::cos(angle);
      break;
    default:
      throw std::logic_error("Unknown WaveEffect enum");
  }
  return m_filterSettings->waveAmplitude * periodicPart;
}

auto ZoomVectorEffects::GetYOnlySpeedCoeff(const NormalizedCoords& coords) const -> float
{
  switch (m_filterSettings->yOnlyEffect)
  {
    case ZoomFilterData::YOnlyEffect::XSIN_YSIN:
      return m_filterSettings->yOnlyAmplitude *
             std::sin(m_filterSettings->yOnlyXFreqFactor * coords.GetX()) *
             std::sin(m_filterSettings->yOnlyFreqFactor * coords.GetY());
    case ZoomFilterData::YOnlyEffect::XSIN_YCOS:
      return m_filterSettings->yOnlyAmplitude *
             std::sin(m_filterSettings->yOnlyXFreqFactor * coords.GetX()) *
             std::cos(m_filterSettings->yOnlyFreqFactor * coords.GetY());
    case ZoomFilterData::YOnlyEffect::XCOS_YSIN:
      return m_filterSettings->yOnlyAmplitude *
             std::cos(m_filterSettings->yOnlyXFreqFactor * coords.GetX()) *
             std::sin(m_filterSettings->yOnlyFreqFactor * coords.GetY());
    case ZoomFilterData::YOnlyEffect::XCOS_YCOS:
      return m_filterSettings->yOnlyAmplitude *
             std::cos(m_filterSettings->yOnlyXFreqFactor * coords.GetX()) *
             std::cos(m_filterSettings->yOnlyFreqFactor * coords.GetY());
    default:
      throw std::logic_error(
          std20::format("Switch: unhandled case '{}'.", m_filterSettings->yOnlyEffect));
  }
}

auto ZoomVectorEffects::GetHypercosVelocity(const NormalizedCoords& coords) const
    -> NormalizedCoords
{
  const float hypercosFreqX = m_filterSettings->hypercosReverse ? -m_filterSettings->hypercosFreqX
                                                                : +m_filterSettings->hypercosFreqX;
  const float hypercosFreqY = m_filterSettings->hypercosReverse ? -m_filterSettings->hypercosFreqY
                                                                : +m_filterSettings->hypercosFreqY;
  float xVal = 0.0;
  float yVal = 0.0;

  switch (m_filterSettings->hypercosEffect)
  {
    case ZoomFilterData::HypercosEffect::NONE:
      break;
    case ZoomFilterData::HypercosEffect::SIN_RECTANGULAR:
      xVal = std::sin(hypercosFreqX * coords.GetX());
      yVal = std::sin(hypercosFreqY * coords.GetY());
      break;
    case ZoomFilterData::HypercosEffect::COS_RECTANGULAR:
      xVal = std::cos(hypercosFreqX * coords.GetX());
      yVal = std::cos(hypercosFreqY * coords.GetY());
      break;
    case ZoomFilterData::HypercosEffect::SIN_CURL_SWIRL:
      xVal = std::sin(hypercosFreqY * coords.GetY());
      yVal = std::sin(hypercosFreqX * coords.GetX());
      break;
    case ZoomFilterData::HypercosEffect::COS_CURL_SWIRL:
      xVal = std::cos(hypercosFreqY * coords.GetY());
      yVal = std::cos(hypercosFreqX * coords.GetX());
      break;
    case ZoomFilterData::HypercosEffect::SIN_COS_CURL_SWIRL:
      xVal = std::sin(hypercosFreqX * coords.GetY());
      yVal = std::cos(hypercosFreqY * coords.GetX());
      break;
    case ZoomFilterData::HypercosEffect::COS_SIN_CURL_SWIRL:
      xVal = std::cos(hypercosFreqY * coords.GetY());
      yVal = std::sin(hypercosFreqX * coords.GetX());
      break;
    case ZoomFilterData::HypercosEffect::SIN_TAN_CURL_SWIRL:
      xVal = std::sin(std::tan(hypercosFreqY * coords.GetY()));
      yVal = std::cos(std::tan(hypercosFreqX * coords.GetX()));
      break;
    case ZoomFilterData::HypercosEffect::COS_TAN_CURL_SWIRL:
      xVal = std::cos(std::tan(hypercosFreqY * coords.GetY()));
      yVal = std::sin(std::tan(hypercosFreqX * coords.GetX()));
      break;
    default:
      throw std::logic_error("Unknown filterData.hypercosEffect value");
  }

  //  xVal = stdnew::clamp(std::tan(hypercosFreqY * xVal), -1.0, 1.0);
  //  yVal = stdnew::clamp(std::tan(hypercosFreqX * yVal), -1.0, 1.0);

  return {m_filterSettings->hypercosAmplitudeX * xVal, m_filterSettings->hypercosAmplitudeY * yVal};
}

auto ZoomVectorEffects::GetHPlaneEffectVelocity(const NormalizedCoords& coords) const -> float
{
  // TODO - try xNormalized
  return coords.GetY() * m_filterSettings->hPlaneEffectAmplitude *
         static_cast<float>(m_filterSettings->hPlaneEffect);
}

auto ZoomVectorEffects::GetVPlaneEffectVelocity(const NormalizedCoords& coords) const -> float
{
  // TODO - try yNormalized
  return coords.GetX() * m_filterSettings->vPlaneEffectAmplitude *
         static_cast<float>(m_filterSettings->vPlaneEffect);
}

auto ZoomVectorEffects::GetNoiseVelocity() const -> NormalizedCoords
{
  if (m_filterSettings->noiseFactor < SMALL_FLOAT)
  {
    return {0.0, 0.0};
  }

  UpdateDoZoomVectorNoiseFactorStats();
  //    const float xAmp = 1.0/getRandInRange(50.0f, 200.0f);
  //    const float yAmp = 1.0/getRandInRange(50.0f, 200.0f);
  const float amp = 0.5F * m_filterSettings->noiseFactor /
                    GetRandInRange(ZoomFilterData::NOISE_MIN, ZoomFilterData::NOISE_MAX);
  return {GetRandInRange(-amp, +amp), GetRandInRange(-amp, +amp)};
}

auto ZoomVectorEffects::GetTanEffectVelocity(const float sqDistFromZero,
                                             const NormalizedCoords& velocity) const
    -> NormalizedCoords
{
  UpdateDoZoomVectorTanEffectStats();
  const float tanArg =
      stdnew::clamp(std::fmod(sqDistFromZero, m_half_pi), -0.85 * m_half_pi, 0.85 * m_half_pi);
  const float tanSqDist = std::tan(tanArg);
  return {tanSqDist * velocity.GetX(), tanSqDist * velocity.GetY()};
}

auto ZoomVectorEffects::GetRotatedVelocity(const NormalizedCoords& velocity) const
    -> NormalizedCoords
{
  if (m_filterSettings->rotateSpeed < 0.0F)
  {
    UpdateDoZoomVectorNegativeRotateStats();
    return {-m_filterSettings->rotateSpeed * (velocity.GetX() - velocity.GetY()),
            -m_filterSettings->rotateSpeed * (velocity.GetX() + velocity.GetY())};
  }

  UpdateDoZoomVectorPositiveRotateStats();
  return {m_filterSettings->rotateSpeed * (velocity.GetY() + velocity.GetX()),
          m_filterSettings->rotateSpeed * (velocity.GetY() - velocity.GetX())};
}

inline void ZoomVectorEffects::UpdateDoZoomVectorSpeedCoeffBelowMinStats() const
{
  if (m_stats == nullptr)
  {
    return;
  }
  m_stats->DoZoomVectorSpeedCoeffBelowMin();
}

inline void ZoomVectorEffects::UpdateDoZoomVectorSpeedCoeffAboveMaxStats() const
{
  if (m_stats == nullptr)
  {
    return;
  }
  m_stats->DoZoomVectorSpeedCoeffAboveMax();
}

inline void ZoomVectorEffects::UpdateDoZoomVectorNoiseFactorStats() const
{
  if (m_stats == nullptr)
  {
    return;
  }
  m_stats->DoZoomVectorNoiseFactor();
}

inline void ZoomVectorEffects::UpdateDoZoomVectorTanEffectStats() const
{
  if (m_stats == nullptr)
  {
    return;
  }
  m_stats->DoZoomVectorTanEffect();
}

inline void ZoomVectorEffects::UpdateDoZoomVectorNegativeRotateStats() const
{
  if (m_stats == nullptr)
  {
    return;
  }
  m_stats->DoZoomVectorNegativeRotate();
}

inline void ZoomVectorEffects::UpdateDoZoomVectorPositiveRotateStats() const
{
  if (m_stats == nullptr)
  {
    return;
  }
  m_stats->DoZoomVectorPositiveRotate();
}

#if __cplusplus <= 201402L
} // namespace FILTERS
} // namespace GOOM
#else
} // namespace GOOM::FILTERS
#endif
