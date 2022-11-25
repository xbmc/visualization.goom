#pragma once

#include "color/random_color_maps.h"
#include "goom_config.h"
#include "goom_effects.h"
#include "utils/enum_utils.h"
#include "utils/math/goom_rand_base.h"
#include "visual_fx_color_matched_sets.h"
#include "visual_fx_weighted_color_maps.h"

#include <memory>

namespace GOOM::CONTROL
{

class VisualFxColorMaps
{
public:
  explicit VisualFxColorMaps(const UTILS::MATH::IGoomRand& goomRand);

  auto ChangeRandomColorMaps() -> void;

  [[nodiscard]] auto GetCurrentRandomColorMaps(GoomEffect goomEffect) const
      -> std::shared_ptr<const COLOR::RandomColorMaps>;

private:
  const UTILS::MATH::IGoomRand& m_goomRand;
  COLOR::RandomColorMapsGroups m_randomColorMapsGroups{m_goomRand};
  VisualFxColorMatchedSets m_visualFxColorMatchedSets{m_goomRand};
  VisualFxWeightedColorMaps m_visualFxWeightedColorMaps{m_goomRand};
  [[nodiscard]] auto GetNextRandomColorMapsGroup(GoomEffect goomEffect) const
      -> COLOR::RandomColorMapsGroups::Groups;
  [[nodiscard]] auto GetNextCompletelyRandomColorMapsGroup() const
      -> COLOR::RandomColorMapsGroups::Groups;
};

inline VisualFxColorMaps::VisualFxColorMaps(const UTILS::MATH::IGoomRand& goomRand)
  : m_goomRand{goomRand}
{
}

inline auto VisualFxColorMaps::ChangeRandomColorMaps() -> void
{
  m_visualFxColorMatchedSets.SetNextRandomColorMatchedSet();
}

inline auto VisualFxColorMaps::GetCurrentRandomColorMaps(const GoomEffect goomEffect) const
    -> std::shared_ptr<const COLOR::RandomColorMaps>
{
  return m_randomColorMapsGroups.MakeRandomColorMapsGroup(GetNextRandomColorMapsGroup(goomEffect));
}

inline auto VisualFxColorMaps::GetNextRandomColorMapsGroup(const GoomEffect goomEffect) const
    -> COLOR::RandomColorMapsGroups::Groups
{
  //  COLOR::RandomColorMapsGroups randomColorMapsGroups{m_goomRand};
  //  const auto group = COLOR::RandomColorMapsGroups::Groups::PURPLE_STANDARD_MAPS;
  //  return randomColorMapsGroups.MakeRandomColorMapsGroup(group);

  if (static constexpr auto PROB_COMPLETELY_RANDOM = 0.05F;
      m_goomRand.ProbabilityOf(PROB_COMPLETELY_RANDOM))
  {
    return GetNextCompletelyRandomColorMapsGroup();
  }
  if (static constexpr auto PROB_WEIGHTED_COLOR_MAPS = 0.25F;
      m_goomRand.ProbabilityOf(PROB_WEIGHTED_COLOR_MAPS))
  {
    return m_visualFxWeightedColorMaps.GetCurrentRandomColorMapsGroup(goomEffect);
  }

  return m_visualFxColorMatchedSets.GetCurrentRandomColorMapsGroup(goomEffect);
}

inline auto VisualFxColorMaps::GetNextCompletelyRandomColorMapsGroup() const
    -> COLOR::RandomColorMapsGroups::Groups
{
  return static_cast<COLOR::RandomColorMapsGroups::Groups>(
      m_goomRand.GetRandInRange(0U, UTILS::NUM<COLOR::RandomColorMapsGroups::Groups>));
}

} // namespace GOOM::CONTROL
