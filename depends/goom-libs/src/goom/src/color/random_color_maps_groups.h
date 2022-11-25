#pragma once

#include "random_color_maps.h"
#include "utils/math/goom_rand_base.h"

#include <memory>

namespace GOOM::COLOR
{

class RandomColorMapsGroups
{
public:
  explicit RandomColorMapsGroups(const UTILS::MATH::IGoomRand& goomRand) noexcept;

  enum class Groups
  {
    ALL_MAPS_UNWEIGHTED,
    ALL_STANDARD_MAPS,
    ALL_SLIM_MAPS,
    MOSTLY_SEQUENTIAL_STANDARD_MAPS,
    MOSTLY_SEQUENTIAL_SLIM_MAPS,
    SLIGHTLY_DIVERGING_STANDARD_MAPS,
    SLIGHTLY_DIVERGING_SLIM_MAPS,
    DIVERGING_BLACK_STANDARD_MAPS,
    RED_STANDARD_MAPS,
    GREEN_STANDARD_MAPS,
    BLUE_STANDARD_MAPS,
    YELLOW_STANDARD_MAPS,
    ORANGE_STANDARD_MAPS,
    PURPLE_STANDARD_MAPS,
    CITIES_STANDARD_MAPS,
    SEASONS_STANDARD_MAPS,
    HEAT_STANDARD_MAPS,
    COLD_STANDARD_MAPS,
    PASTEL_STANDARD_MAPS,
    WES_ANDERSON_MAPS,
    _num // unused, and marks the enum end
  };

  [[nodiscard]] auto MakeRandomColorMapsGroup(Groups randomColorMapsGroup) const noexcept
      -> std::shared_ptr<RandomColorMaps>;

  [[nodiscard]] static auto MakeSharedAllMapsUnweighted(
      const UTILS::MATH::IGoomRand& goomRand) noexcept -> std::shared_ptr<RandomColorMaps>;

private:
  const UTILS::MATH::IGoomRand& m_goomRand;
};

inline auto RandomColorMapsGroups::MakeSharedAllMapsUnweighted(
    const UTILS::MATH::IGoomRand& goomRand) noexcept -> std::shared_ptr<RandomColorMaps>
{
  return RandomColorMapsGroups{goomRand}.MakeRandomColorMapsGroup(Groups::ALL_MAPS_UNWEIGHTED);
}

} // namespace GOOM::COLOR
