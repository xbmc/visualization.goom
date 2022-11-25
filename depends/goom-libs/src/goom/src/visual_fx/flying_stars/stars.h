#pragma once

#include "color/color_maps.h"
#include "goom_config.h"
#include "goom_graphic.h"
#include "point2d.h"

#include <memory>

namespace GOOM::VISUAL_FX::FLYING_STARS
{

class Star
{
public:
  struct Params
  {
    Point2dFlt currentPosition;
    Vec2dFlt velocity;
    Vec2dFlt acceleration;
    float age;
    float vage;
    float maxAge;
  };

  explicit Star(const Params& params) noexcept;

  [[nodiscard]] auto GetStartPos() const noexcept -> Point2dFlt;
  [[nodiscard]] auto GetAge() const noexcept -> float;
  [[nodiscard]] auto GetMaxAge() const noexcept -> float;
  [[nodiscard]] auto GetVelocity() const noexcept -> Vec2dFlt;

  [[nodiscard]] auto IsTooOld() const noexcept -> bool;

  auto Update() noexcept -> void;

  struct ColorMapsSet
  {
    std::shared_ptr<const COLOR::IColorMap> currentMainColorMap{};
    std::shared_ptr<const COLOR::IColorMap> currentLowColorMap{};
    std::shared_ptr<const COLOR::IColorMap> dominantMainColormap{};
    std::shared_ptr<const COLOR::IColorMap> dominantLowColormap{};
  };
  auto SetColorMapsSet(const ColorMapsSet& val) noexcept -> void;

  struct ColorSet
  {
    Pixel mainColor;
    Pixel lowColor;
    Pixel dominantMainColor;
    Pixel dominantLowColor;
  };
  [[nodiscard]] auto GetColorSet(float t) const noexcept -> ColorSet;
  [[nodiscard]] auto GetReversedMixColorSet(float t) const noexcept -> ColorSet;
  [[nodiscard]] auto GetSineMixColorSet() const noexcept -> ColorSet;
  [[nodiscard]] auto GetSimilarLowColorSet(float t) const noexcept -> ColorSet;

  static constexpr float MIN_INITIAL_AGE      = 1.0F - (99.0F / 100.0F);
  static constexpr float MAX_INITIAL_AGE      = 1.0F - (80.0F / 100.0F);
  static constexpr float HALF_MAX_INITIAL_AGE = 0.5F * MAX_INITIAL_AGE;

private:
  Params m_params;
  ColorMapsSet m_colorMapsSet{};
};

inline auto Star::GetColorSet(const float t) const noexcept -> ColorSet
{
  return {m_colorMapsSet.currentMainColorMap->GetColor(t),
          m_colorMapsSet.currentLowColorMap->GetColor(t),
          m_colorMapsSet.dominantMainColormap->GetColor(t),
          m_colorMapsSet.dominantLowColormap->GetColor(t)};
}

inline auto Star::SetColorMapsSet(const ColorMapsSet& val) noexcept -> void
{
  m_colorMapsSet = val;

  Ensures(m_colorMapsSet.currentMainColorMap != nullptr);
  Ensures(m_colorMapsSet.currentLowColorMap != nullptr);
  Ensures(m_colorMapsSet.dominantMainColormap != nullptr);
  Ensures(m_colorMapsSet.dominantLowColormap != nullptr);
}

inline auto Star::GetStartPos() const noexcept -> Point2dFlt
{
  return m_params.currentPosition;
}

inline auto Star::GetAge() const noexcept -> float
{
  return m_params.age;
}

inline auto Star::GetMaxAge() const noexcept -> float
{
  return m_params.maxAge;
}

inline auto Star::IsTooOld() const noexcept -> bool
{
  return m_params.age >= m_params.maxAge;
}

inline auto Star::GetVelocity() const noexcept -> Vec2dFlt
{
  return m_params.velocity;
}

} //namespace GOOM::VISUAL_FX::FLYING_STARS
