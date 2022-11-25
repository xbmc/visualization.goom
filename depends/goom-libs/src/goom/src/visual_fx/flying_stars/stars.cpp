#include "stars.h"

namespace GOOM::VISUAL_FX::FLYING_STARS
{

Star::Star(const Params& params) noexcept : m_params{params}
{
}

/**
 * Met a jour la position et vitesse d'une particule.
 */
auto Star::Update() noexcept -> void
{
  m_params.currentPosition.Translate(m_params.velocity);
  m_params.velocity += m_params.acceleration;
  m_params.age += m_params.vage;
}

auto Star::GetReversedMixColorSet(const float t) const noexcept -> ColorSet
{
  return GetColorSet(1.0F - t);
}

auto Star::GetSimilarLowColorSet(const float t) const noexcept -> ColorSet
{
  auto starColorSet             = GetColorSet(t);
  starColorSet.dominantLowColor = starColorSet.dominantMainColor;
  return starColorSet;
}

auto Star::GetSineMixColorSet() const noexcept -> ColorSet
{
  static constexpr auto FREQ         = 20.0F;
  static constexpr auto T_MIX_FACTOR = 0.5F;
  static constexpr auto Z_STEP       = 0.1F;
  static auto s_z                    = 0.0F;

  const auto tSin = T_MIX_FACTOR * (1.0F + std::sin(FREQ * s_z));

  ColorSet starColorSet;
  starColorSet.mainColor         = m_colorMapsSet.currentMainColorMap->GetColor(tSin);
  starColorSet.lowColor          = m_colorMapsSet.currentLowColorMap->GetColor(tSin);
  starColorSet.dominantMainColor = m_colorMapsSet.dominantMainColormap->GetColor(tSin);
  starColorSet.dominantLowColor  = m_colorMapsSet.dominantLowColormap->GetColor(tSin);

  s_z += Z_STEP;

  return starColorSet;
}

} // namespace GOOM::VISUAL_FX::FLYING_STARS
