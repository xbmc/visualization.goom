#ifndef VISUALIZATION_GOOM_FILTER_DATA_H
#define VISUALIZATION_GOOM_FILTER_DATA_H

#include "goomutils/mathutils.h"

#include <cstdint>

namespace GOOM
{

namespace FILTERS
{
class ImageDisplacement;
}

enum class ZoomFilterMode
{
  _NULL = -1,
  AMULET_MODE = 0,
  CRYSTAL_BALL_MODE0,
  CRYSTAL_BALL_MODE1,
  HYPERCOS_MODE0,
  HYPERCOS_MODE1,
  HYPERCOS_MODE2,
  IMAGE_DISPLACEMENT_MODE,
  NORMAL_MODE,
  SCRUNCH_MODE,
  SPEEDWAY_MODE,
  WATER_MODE,
  WAVE_MODE0,
  WAVE_MODE1,
  Y_ONLY_MODE,
  _NUM // unused and must be last
};

// 128 = vitesse nule...
// 256 = en arriere
//   hyper vite.. * * 0 = en avant hype vite.
// 128 = zero speed
// 256 = reverse
//   super fast ... 0 = forward quickly.
class Vitesse
{
  static constexpr int32_t MAX_VITESSE = 128;

public:
  static constexpr int32_t STOP_SPEED = MAX_VITESSE;
  static constexpr int32_t FASTEST_SPEED = 0;
  static constexpr int32_t DEFAULT_VITESSE = 127;

  auto GetVitesse() const -> int32_t { return m_vitesse; };
  void SetVitesse(int32_t val);
  void SetDefault();
  void GoSlowerBy(int32_t val);
  void GoFasterBy(int32_t val);

  auto GetReverseVitesse() const -> bool { return m_reverseVitesse; }
  void SetReverseVitesse(const bool val) { m_reverseVitesse = val; }
  void ToggleReverseVitesse() { m_reverseVitesse = !m_reverseVitesse; }

  auto GetRelativeSpeed() const -> float;

private:
  int32_t m_vitesse = DEFAULT_VITESSE;
  bool m_reverseVitesse = true;
};

inline void Vitesse::SetVitesse(const int32_t val)
{
  m_vitesse = stdnew::clamp(val, FASTEST_SPEED, STOP_SPEED);
}

inline void Vitesse::SetDefault()
{
  m_vitesse = DEFAULT_VITESSE;
  m_reverseVitesse = true;
}

inline void Vitesse::GoSlowerBy(const int32_t val)
{
  SetVitesse(m_vitesse + val);
}

inline void Vitesse::GoFasterBy(const int32_t val)
{
  SetVitesse(m_vitesse - 30 * val);
}

inline auto Vitesse::GetRelativeSpeed() const -> float
{
  const float speed = static_cast<float>(m_vitesse - MAX_VITESSE) / static_cast<float>(MAX_VITESSE);
  return m_reverseVitesse ? -speed : +speed;
}

struct ZoomFilterData
{
  ZoomFilterMode mode = ZoomFilterMode::NORMAL_MODE;
  Vitesse vitesse{};
#if __cplusplus <= 201402L
  static const uint8_t pertedec; // NEVER SEEMS TO CHANGE
#else
  static constexpr uint8_t pertedec = 8; // NEVER SEEMS TO CHANGE
#endif
  static constexpr uint32_t DEFAULT_MIDDLE_X = 16;
  static constexpr uint32_t DEFAULT_MIDDLE_Y = 1;
  uint32_t middleX = DEFAULT_MIDDLE_X;
  uint32_t middleY = DEFAULT_MIDDLE_Y; // milieu de l'effet
  bool tanEffect = false;
  bool blockyWavy = false;
  static constexpr float MIN_ROTATE_SPEED = -0.5F;
  static constexpr float MAX_ROTATE_SPEED = +0.5F;
  static constexpr float DEFAULT_ROTATE_SPEED = 0.0F;
  float rotateSpeed = DEFAULT_ROTATE_SPEED;

  static constexpr float SPEED_COEFF_DENOMINATOR = 50.0F;
  static constexpr float MIN_SPEED_COEFF = -4.01F;
  static constexpr float MAX_MAX_SPEED_COEFF = +4.01F;
  static constexpr float DEFAULT_MAX_SPEED_COEFF = +2.01F;

  //* @since April 2002
  // TODO - Not used yet
  bool waveEffect = false; // applique une "surcouche" de wave effect

  // Noise:
  bool noisify = false; // ajoute un bruit a la transformation
  float noiseFactor = 1.0; // in range [0, 1]
  // For noise amplitude, take the reciprocal of these.
  static constexpr float NOISE_MIN = 40.0F;
  static constexpr float NOISE_MAX = 120.0F;

  // H Plane:
  // @since June 2001
  int hPlaneEffect = 0; // deviation horitontale
  static constexpr float DEFAULT_H_PLANE_EFFECT_AMPLITUDE = 0.0025F;
  static constexpr float MIN_H_PLANE_EFFECT_AMPLITUDE = 0.0015F;
  static constexpr float MAX_H_PLANE_EFFECT_AMPLITUDE = 0.0035F;
  float hPlaneEffectAmplitude = DEFAULT_H_PLANE_EFFECT_AMPLITUDE;

  // V Plane:
  int vPlaneEffect = 0; // deviation verticale
  static constexpr float DEFAULT_V_PLANE_EFFECT_AMPLITUDE = 0.0025F;
  static constexpr float MIN_V_PLANE_EFFECT_AMPLITUDE = 0.0015F;
  static constexpr float MAX_V_PLANE_EFFECT_AMPLITUDE = 0.0035F;
  float vPlaneEffectAmplitude = DEFAULT_V_PLANE_EFFECT_AMPLITUDE;

  // Amulet:
  static constexpr float DEFAULT_AMULET_AMPLITUDE = 3.5F;
  static constexpr float MIN_AMULET_AMPLITUDE = 2.0F;
  static constexpr float MAX_AMULET_AMPLITUDE = 5.0F;
  float amuletAmplitude = DEFAULT_AMULET_AMPLITUDE;

  // Crystal ball:
  static constexpr float DEFAULT_CRYSTAL_BALL_AMPLITUDE = 0.1F;
  static constexpr float MIN_CRYSTAL_BALL0_AMPLITUDE = 0.05F;
  static constexpr float MIN_CRYSTAL_BALL1_AMPLITUDE = 0.01F;
  static constexpr float MAX_CRYSTAL_BALL0_AMPLITUDE = 2.0F;
  static constexpr float MAX_CRYSTAL_BALL1_AMPLITUDE = 15.0F;
  float crystalBallAmplitude = DEFAULT_CRYSTAL_BALL_AMPLITUDE;
  static constexpr float DEFAULT_CRYSTAL_BALL_SQ_DIST_OFFSET = 0.3F;
  static constexpr float MIN_CRYSTAL_BALL0_SQ_DIST_OFFSET = 0.1F;
  static constexpr float MIN_CRYSTAL_BALL1_SQ_DIST_OFFSET = 0.01F;
  static constexpr float MAX_CRYSTAL_BALL0_SQ_DIST_OFFSET = 1.0F;
  static constexpr float MAX_CRYSTAL_BALL1_SQ_DIST_OFFSET = 1.5F;
  float crystalBallSqDistOffset = DEFAULT_CRYSTAL_BALL_SQ_DIST_OFFSET;

  // Hypercos:
  enum class HypercosEffect
  {
    NONE,
    SIN_CURL_SWIRL,
    COS_CURL_SWIRL,
    SIN_COS_CURL_SWIRL,
    COS_SIN_CURL_SWIRL,
    SIN_TAN_CURL_SWIRL,
    COS_TAN_CURL_SWIRL,
    SIN_RECTANGULAR,
    COS_RECTANGULAR,
    _NUM // unused and must be last
  };

  // applique une surcouche de hypercos effect
  // applies an overlay of hypercos effect
  HypercosEffect hypercosEffect = HypercosEffect::NONE;
  bool hypercosReverse = false;

  static constexpr float DEFAULT_HYPERCOS_FREQ = 10.0F;
  static constexpr float MIN_HYPERCOS_FREQ = 5.0F;
  static constexpr float MAX_HYPERCOS_FREQ = 100.0F;
  // Tried 1000 for hypercos_freq but effect was too fine and annoying.
  static constexpr float BIG_MAX_HYPERCOS_FREQ = 500.0F;
  float hypercosFreqX = DEFAULT_HYPERCOS_FREQ;
  float hypercosFreqY = DEFAULT_HYPERCOS_FREQ;

  static constexpr float DEFAULT_HYPERCOS_AMPLITUDE = 1.0F / 120.0F;
  static constexpr float MIN_HYPERCOS_AMPLITUDE = 0.1F * DEFAULT_HYPERCOS_AMPLITUDE;
  static constexpr float MAX_HYPERCOS_AMPLITUDE = 1.1F * DEFAULT_HYPERCOS_AMPLITUDE;
  float hypercosAmplitudeX = DEFAULT_HYPERCOS_AMPLITUDE;
  float hypercosAmplitudeY = DEFAULT_HYPERCOS_AMPLITUDE;

  // Image Displacement:
  static constexpr float DEFAULT_IMAGE_DISPL_AMPLITUDE = 0.0250F;
  static constexpr float MIN_IMAGE_DISPL_AMPLITUDE = 0.0025F;
  static constexpr float MAX_IMAGE_DISPL_AMPLITUDE = 0.1000F;
  float imageDisplacementAmplitude = DEFAULT_IMAGE_DISPL_AMPLITUDE;
  std::shared_ptr<FILTERS::ImageDisplacement> imageDisplacement{};
  static constexpr float MIN_IMAGE_DISPL_COLOR_CUTOFF = 0.1F;
  static constexpr float MAX_IMAGE_DISPL_COLOR_CUTOFF = 0.9F;
  static constexpr float DEFAULT_IMAGE_DISPL_COLOR_CUTOFF = 0.5F;
  float imageDisplacementXColorCutoff = DEFAULT_IMAGE_DISPL_COLOR_CUTOFF;
  float imageDisplacementYColorCutoff = DEFAULT_IMAGE_DISPL_COLOR_CUTOFF;
  static constexpr float MIN_IMAGE_DISPL_ZOOM_FACTOR = 1.00F;
  static constexpr float MAX_IMAGE_DISPL_ZOOM_FACTOR = 10.0F;
  static constexpr float DEFAULT_IMAGE_DISPL_ZOOM_FACTOR = 5.0F;
  float imageDisplacementZoomFactor = DEFAULT_IMAGE_DISPL_ZOOM_FACTOR;

  // Wave:
  enum class WaveEffect
  {
    WAVE_SIN_EFFECT,
    WAVE_COS_EFFECT,
    WAVE_SIN_COS_EFFECT,
    _NUM // unused and must be last
  };
  static constexpr WaveEffect DEFAULT_WAVE_EFFECT_TYPE = WaveEffect::WAVE_SIN_EFFECT;
  WaveEffect waveEffectType = DEFAULT_WAVE_EFFECT_TYPE;

  static constexpr float DEFAULT_WAVE_FREQ_FACTOR = 20.0F;
  static constexpr float MIN_WAVE_FREQ_FACTOR = 1.0F;
  static constexpr float MAX_WAVE_FREQ_FACTOR = 50.0F;
  float waveFreqFactor = DEFAULT_WAVE_FREQ_FACTOR;

  static constexpr float DEFAULT_WAVE_AMPLITUDE = 0.01F;
  static constexpr float MIN_WAVE_AMPLITUDE = 0.001F;
  static constexpr float MAX_WAVE_AMPLITUDE = 0.25F;
  float waveAmplitude = DEFAULT_WAVE_AMPLITUDE;

  // These give weird but interesting wave results
  static constexpr float SMALL_MIN_WAVE_FREQ_FACTOR = 0.001F;
  static constexpr float SMALL_MAX_WAVE_FREQ_FACTOR = 0.1F;
  static constexpr float BIG_MIN_WAVE_AMPLITUDE = 1.0F;
  static constexpr float BIG_MAX_WAVE_AMPLITUDE = 50.0F;

  // Scrunch:
  static constexpr float DEFAULT_SCRUNCH_AMPLITUDE = 0.1F;
  static constexpr float MIN_SCRUNCH_AMPLITUDE = 0.05F;
  static constexpr float MAX_SCRUNCH_AMPLITUDE = 0.2F;
  float scrunchAmplitude = DEFAULT_SCRUNCH_AMPLITUDE;

  // Speedway:
  static constexpr float DEFAULT_SPEEDWAY_AMPLITUDE = 4.0F;
  static constexpr float MIN_SPEEDWAY_AMPLITUDE = 1.0F;
  static constexpr float MAX_SPEEDWAY_AMPLITUDE = 8.0F;
  float speedwayAmplitude = DEFAULT_SPEEDWAY_AMPLITUDE;

  // Y Only
  enum class YOnlyEffect
  {
    NONE,
    XSIN_YSIN,
    XSIN_YCOS,
    XCOS_YSIN,
    XCOS_YCOS,
    _NUM // unused and must be last
  };

  YOnlyEffect yOnlyEffect = YOnlyEffect::XSIN_YSIN;

  static constexpr float DEFAULT_Y_ONLY_X_FREQ_FACTOR = 1.0F;
  static constexpr float MIN_Y_ONLY_X_FREQ_FACTOR = -10.0F;
  static constexpr float MAX_Y_ONLY_X_FREQ_FACTOR = +10.0F;
  float yOnlyXFreqFactor = DEFAULT_Y_ONLY_X_FREQ_FACTOR;

  static constexpr float DEFAULT_Y_ONLY_FREQ_FACTOR = 10.0F;
  static constexpr float MIN_Y_ONLY_FREQ_FACTOR = -10.0F;
  static constexpr float MAX_Y_ONLY_FREQ_FACTOR = +10.0F;
  float yOnlyFreqFactor = DEFAULT_Y_ONLY_FREQ_FACTOR;

  static constexpr float DEFAULT_Y_ONLY_AMPLITUDE = 10.0F;
  static constexpr float MIN_Y_ONLY_AMPLITUDE = 0.1F;
  static constexpr float MAX_Y_ONLY_AMPLITUDE = 20.0F;
  float yOnlyAmplitude = DEFAULT_Y_ONLY_AMPLITUDE;
};

} // namespace GOOM
#endif
