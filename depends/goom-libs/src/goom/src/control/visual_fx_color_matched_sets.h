#pragma once

#include "color/random_color_maps_groups.h"
#include "goom_config.h"
#include "goom_effects.h"
#include "utils/enum_utils.h"
#include "utils/math/goom_rand_base.h"

#include <memory>

namespace GOOM::CONTROL
{

class VisualFxColorMatchedSets
{
public:
  explicit VisualFxColorMatchedSets(const UTILS::MATH::IGoomRand& goomRand) noexcept;

  auto SetNextRandomColorMatchedSet() noexcept -> void;
  [[nodiscard]] auto GetCurrentRandomColorMapsGroup(GoomEffect goomEffect) const noexcept
      -> COLOR::RandomColorMapsGroups::Groups;

private:
  const UTILS::MATH::IGoomRand& m_goomRand;

  using ColorMatchedSet = UTILS::EnumMap<GoomEffect, COLOR::RandomColorMapsGroups::Groups>;
  enum class ColorMatchedSets
  {
    RED_GREEN_STD_MAPS,
    RED_BLUE_STD_MAPS,
    YELLOW_BLUE_STD_MAPS,
    YELLOW_PURPLE_STD_MAPS,
    ORANGE_GREEN_STD_MAPS,
    ORANGE_PURPLE_STD_MAPS,
    ALL_ONLY_STD_MAPS,
    HEAT_ONLY_STD_MAPS,
    COLD_ONLY_STD_MAPS,
    DIVERGING_ONLY_STD_MAPS,
    DIVERGING_BLACK_ONLY_STD_MAPS,
    WES_ANDERSON_ONLY_MAPS,
    PASTEL_ONLY_MAPS,
    COLOR_MATCHED_SET1,
    COLOR_MATCHED_SET2,
    COLOR_MATCHED_SET3,
    COLOR_MATCHED_SET4,
    COLOR_MATCHED_SET5,
    COLOR_MATCHED_SET6,
    COLOR_MATCHED_SET7,
    COLOR_MATCHED_SET8,
    _num // unused, and marks the enum end
  };
  using ColorMatchedSetsMap = UTILS::EnumMap<ColorMatchedSets, ColorMatchedSet>;
  [[nodiscard]] auto MakeColorMatchedSetsMap() const noexcept -> ColorMatchedSetsMap;
  const ColorMatchedSetsMap m_colorMatchedSetsMap{MakeColorMatchedSetsMap()};

  const UTILS::MATH::Weights<ColorMatchedSets> m_colorMatchedSetsWeights;
  [[nodiscard]] auto GetNextRandomColorMatchedSet() const noexcept -> const ColorMatchedSet&;
  const ColorMatchedSet* m_currentColorMatchedSet{&GetNextRandomColorMatchedSet()};

  [[nodiscard]] static auto GetOneGroupColorMatchedSet(
      COLOR::RandomColorMapsGroups::Groups group) noexcept -> ColorMatchedSet;
  [[nodiscard]] static auto GetOneGroupArray(COLOR::RandomColorMapsGroups::Groups group)
      -> std::array<ColorMatchedSet::KeyValue, UTILS::NUM<GoomEffect>>;
  [[nodiscard]] auto GetTwoGroupsColorMatchedSet(
      COLOR::RandomColorMapsGroups::Groups group1,
      COLOR::RandomColorMapsGroups::Groups group2) const noexcept -> ColorMatchedSet;

  static auto GetPrimaryColorDots(ColorMatchedSet& matchedSet) noexcept -> void;

  [[nodiscard]] static auto GetColorMatchedSet1() noexcept -> ColorMatchedSet;
  [[nodiscard]] static auto GetColorMatchedSet2() noexcept -> ColorMatchedSet;
  [[nodiscard]] static auto GetColorMatchedSet3() noexcept -> ColorMatchedSet;
  [[nodiscard]] static auto GetColorMatchedSet4() noexcept -> ColorMatchedSet;
  [[nodiscard]] static auto GetColorMatchedSet5() noexcept -> ColorMatchedSet;
  [[nodiscard]] static auto GetColorMatchedSet6() noexcept -> ColorMatchedSet;
  [[nodiscard]] static auto GetColorMatchedSet7() noexcept -> ColorMatchedSet;
  [[nodiscard]] static auto GetColorMatchedSet8() noexcept -> ColorMatchedSet;
};

inline auto VisualFxColorMatchedSets::SetNextRandomColorMatchedSet() noexcept -> void
{
  m_currentColorMatchedSet = &GetNextRandomColorMatchedSet();
  Ensures(m_currentColorMatchedSet->size() == UTILS::NUM<GoomEffect>);
}

inline auto VisualFxColorMatchedSets::GetCurrentRandomColorMapsGroup(
    const GoomEffect goomEffect) const noexcept -> COLOR::RandomColorMapsGroups::Groups
{
  return (*m_currentColorMatchedSet)[goomEffect];
}

} // namespace GOOM::CONTROL
