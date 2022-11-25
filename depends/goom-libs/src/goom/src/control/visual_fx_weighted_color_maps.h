#pragma once

#include "color/random_color_maps_groups.h"
#include "goom_config.h"
#include "goom_effects.h"
#include "utils/enum_utils.h"
#include "utils/math/goom_rand_base.h"

#include <memory>

namespace GOOM::CONTROL
{

class VisualFxWeightedColorMaps
{
public:
  explicit VisualFxWeightedColorMaps(const UTILS::MATH::IGoomRand& goomRand) noexcept;

  [[nodiscard]] auto GetCurrentRandomColorMapsGroup(GoomEffect goomEffect) const noexcept
      -> COLOR::RandomColorMapsGroups::Groups;

private:
  const UTILS::MATH::IGoomRand& m_goomRand;

  using WeightedGroups = UTILS::MATH::Weights<COLOR::RandomColorMapsGroups::Groups>;
  const UTILS::RuntimeEnumMap<GoomEffect, WeightedGroups> m_goomEffectsWeightedColorMaps;

  [[nodiscard]] auto GetCirclesMainGroups() const noexcept -> WeightedGroups;
  [[nodiscard]] auto GetCirclesLowGroups() const noexcept -> WeightedGroups;
  [[nodiscard]] auto GetDots0Groups() const noexcept -> WeightedGroups;
  [[nodiscard]] auto GetDots1Groups() const noexcept -> WeightedGroups;
  [[nodiscard]] auto GetDots2Groups() const noexcept -> WeightedGroups;
  [[nodiscard]] auto GetDots3Groups() const noexcept -> WeightedGroups;
  [[nodiscard]] auto GetDots4Groups() const noexcept -> WeightedGroups;
  [[nodiscard]] auto GetIfsGroups() const noexcept -> WeightedGroups;
  [[nodiscard]] auto GetImageGroups() const noexcept -> WeightedGroups;
  [[nodiscard]] auto GetLines1Groups() const noexcept -> WeightedGroups;
  [[nodiscard]] auto GetLines2Groups() const noexcept -> WeightedGroups;
  [[nodiscard]] auto GetShapesMainGroups() const noexcept -> WeightedGroups;
  [[nodiscard]] auto GetShapesLowGroups() const noexcept -> WeightedGroups;
  [[nodiscard]] auto GetShapesInnerGroups() const noexcept -> WeightedGroups;
  [[nodiscard]] auto GetStarsMainFireworksGroups() const noexcept -> WeightedGroups;
  [[nodiscard]] auto GetStarsLowFireworksGroups() const noexcept -> WeightedGroups;
  [[nodiscard]] auto GetStarsMainRainGroups() const noexcept -> WeightedGroups;
  [[nodiscard]] auto GetStarsLowRainGroups() const noexcept -> WeightedGroups;
  [[nodiscard]] auto GetStarsMainFountainGroups() const noexcept -> WeightedGroups;
  [[nodiscard]] auto GetStarsLowFountainGroups() const noexcept -> WeightedGroups;
  [[nodiscard]] auto GetTentaclesDominantMainGroups() const noexcept -> WeightedGroups;
  [[nodiscard]] auto GetTentaclesDominantLowGroups() const noexcept -> WeightedGroups;
  [[nodiscard]] auto GetTentaclesMainGroups() const noexcept -> WeightedGroups;
  [[nodiscard]] auto GetTentaclesLowGroups() const noexcept -> WeightedGroups;
  [[nodiscard]] auto GetTubesMainGroups() const noexcept -> WeightedGroups;
  [[nodiscard]] auto GetTubesLowGroups() const noexcept -> WeightedGroups;
};

inline auto VisualFxWeightedColorMaps::GetCurrentRandomColorMapsGroup(
    GoomEffect goomEffect) const noexcept -> COLOR::RandomColorMapsGroups::Groups
{
  return m_goomEffectsWeightedColorMaps[goomEffect].GetRandomWeighted();
}

} // namespace GOOM::CONTROL
