#include "visual_fx_weighted_color_maps.h"

namespace GOOM::CONTROL
{

using COLOR::RandomColorMapsGroups;
using UTILS::MATH::IGoomRand;
using Groups = RandomColorMapsGroups::Groups;

VisualFxWeightedColorMaps::VisualFxWeightedColorMaps(const IGoomRand& goomRand) noexcept
  : m_goomRand{goomRand},
    m_goomEffectsWeightedColorMaps{{{
        {GoomEffect::CIRCLES_MAIN, GetCirclesMainGroups()},
        {GoomEffect::CIRCLES_LOW, GetCirclesLowGroups()},
        {GoomEffect::DOTS0, GetDots0Groups()},
        {GoomEffect::DOTS1, GetDots1Groups()},
        {GoomEffect::DOTS2, GetDots2Groups()},
        {GoomEffect::DOTS3, GetDots3Groups()},
        {GoomEffect::DOTS4, GetDots4Groups()},
        {GoomEffect::IFS, GetIfsGroups()},
        {GoomEffect::IMAGE, GetImageGroups()},
        {GoomEffect::LINES1, GetLines1Groups()},
        {GoomEffect::LINES2, GetLines2Groups()},
        {GoomEffect::SHAPES_MAIN, GetShapesMainGroups()},
        {GoomEffect::SHAPES_LOW, GetShapesLowGroups()},
        {GoomEffect::SHAPES_INNER, GetShapesInnerGroups()},
        {GoomEffect::STARS_MAIN_FIREWORKS, GetStarsMainFireworksGroups()},
        {GoomEffect::STARS_LOW_FIREWORKS, GetStarsLowFireworksGroups()},
        {GoomEffect::STARS_MAIN_RAIN, GetStarsMainRainGroups()},
        {GoomEffect::STARS_LOW_RAIN, GetStarsLowRainGroups()},
        {GoomEffect::STARS_MAIN_FOUNTAIN, GetStarsMainFountainGroups()},
        {GoomEffect::STARS_LOW_FOUNTAIN, GetStarsLowFountainGroups()},
        {GoomEffect::TENTACLES_DOMINANT_MAIN, GetTentaclesDominantMainGroups()},
        {GoomEffect::TENTACLES_DOMINANT_LOW, GetTentaclesDominantLowGroups()},
        {GoomEffect::TENTACLES_MAIN, GetTentaclesMainGroups()},
        {GoomEffect::TENTACLES_LOW, GetTentaclesLowGroups()},
        {GoomEffect::TUBE_MAIN, GetTubesMainGroups()},
        {GoomEffect::TUBE_LOW, GetTubesLowGroups()},
    }}}
{
}

auto VisualFxWeightedColorMaps::GetCirclesMainGroups() const noexcept -> WeightedGroups
{
  static constexpr auto ALL_MAPS_UNWEIGHTED_WEIGHT              = 05.0F;
  static constexpr auto ALL_STANDARD_MAPS_WEIGHT                = 05.0F;
  static constexpr auto ALL_SLIM_MAPS_WEIGHT                    = 05.0F;
  static constexpr auto MOSTLY_SEQUENTIAL_STANDARD_MAPS_WEIGHT  = 05.0F;
  static constexpr auto MOSTLY_SEQUENTIAL_SLIM_MAPS_WEIGHT      = 05.0F;
  static constexpr auto SLIGHTLY_DIVERGING_STANDARD_MAPS_WEIGHT = 05.0F;
  static constexpr auto SLIGHTLY_DIVERGING_SLIM_MAPS_WEIGHT     = 20.0F;
  static constexpr auto DIVERGING_BLACK_STANDARD_MAPS_WEIGHT    = 35.0F;
  static constexpr auto RED_STANDARD_MAPS_WEIGHT                = 35.0F;
  static constexpr auto GREEN_STANDARD_MAPS_WEIGHT              = 40.0F;
  static constexpr auto BLUE_STANDARD_MAPS_WEIGHT               = 40.0F;
  static constexpr auto YELLOW_STANDARD_MAPS_WEIGHT             = 40.0F;
  static constexpr auto ORANGE_STANDARD_MAPS_WEIGHT             = 40.0F;
  static constexpr auto PURPLE_STANDARD_MAPS_WEIGHT             = 90.0F;
  static constexpr auto CITIES_STANDARD_MAPS_WEIGHT             = 90.0F;
  static constexpr auto SEASONS_STANDARD_MAPS_WEIGHT            = 90.0F;
  static constexpr auto HEAT_STANDARD_MAPS_WEIGHT               = 90.0F;
  static constexpr auto COLD_STANDARD_MAPS_WEIGHT               = 90.0F;
  static constexpr auto PASTEL_STANDARD_MAPS_WEIGHT             = 90.0F;
  static constexpr auto WES_ANDERSON_MAPS_WEIGHT                = 90.0F;

  return {
      m_goomRand,
      {
        {Groups::ALL_MAPS_UNWEIGHTED, ALL_MAPS_UNWEIGHTED_WEIGHT},
        {Groups::ALL_STANDARD_MAPS, ALL_STANDARD_MAPS_WEIGHT},
        {Groups::ALL_SLIM_MAPS, ALL_SLIM_MAPS_WEIGHT},
        {Groups::MOSTLY_SEQUENTIAL_STANDARD_MAPS, MOSTLY_SEQUENTIAL_STANDARD_MAPS_WEIGHT},
        {Groups::MOSTLY_SEQUENTIAL_SLIM_MAPS, MOSTLY_SEQUENTIAL_SLIM_MAPS_WEIGHT},
        {Groups::SLIGHTLY_DIVERGING_STANDARD_MAPS, SLIGHTLY_DIVERGING_STANDARD_MAPS_WEIGHT},
        {Groups::SLIGHTLY_DIVERGING_SLIM_MAPS, SLIGHTLY_DIVERGING_SLIM_MAPS_WEIGHT},
        {Groups::DIVERGING_BLACK_STANDARD_MAPS, DIVERGING_BLACK_STANDARD_MAPS_WEIGHT},
        {Groups::RED_STANDARD_MAPS, RED_STANDARD_MAPS_WEIGHT},
        {Groups::GREEN_STANDARD_MAPS, GREEN_STANDARD_MAPS_WEIGHT},
        {Groups::BLUE_STANDARD_MAPS, BLUE_STANDARD_MAPS_WEIGHT},
        {Groups::YELLOW_STANDARD_MAPS, YELLOW_STANDARD_MAPS_WEIGHT},
        {Groups::ORANGE_STANDARD_MAPS, ORANGE_STANDARD_MAPS_WEIGHT},
        {Groups::PURPLE_STANDARD_MAPS, PURPLE_STANDARD_MAPS_WEIGHT},
        {Groups::CITIES_STANDARD_MAPS, CITIES_STANDARD_MAPS_WEIGHT},
        {Groups::SEASONS_STANDARD_MAPS, SEASONS_STANDARD_MAPS_WEIGHT},
        {Groups::HEAT_STANDARD_MAPS, HEAT_STANDARD_MAPS_WEIGHT},
        {Groups::COLD_STANDARD_MAPS, COLD_STANDARD_MAPS_WEIGHT},
        {Groups::PASTEL_STANDARD_MAPS, PASTEL_STANDARD_MAPS_WEIGHT},
        {Groups::WES_ANDERSON_MAPS, WES_ANDERSON_MAPS_WEIGHT},
        }
  };
}

auto VisualFxWeightedColorMaps::GetCirclesLowGroups() const noexcept -> WeightedGroups
{
  static constexpr auto ALL_MAPS_UNWEIGHTED_WEIGHT              = 05.0F;
  static constexpr auto ALL_STANDARD_MAPS_WEIGHT                = 05.0F;
  static constexpr auto ALL_SLIM_MAPS_WEIGHT                    = 05.0F;
  static constexpr auto MOSTLY_SEQUENTIAL_STANDARD_MAPS_WEIGHT  = 05.0F;
  static constexpr auto MOSTLY_SEQUENTIAL_SLIM_MAPS_WEIGHT      = 05.0F;
  static constexpr auto SLIGHTLY_DIVERGING_STANDARD_MAPS_WEIGHT = 05.0F;
  static constexpr auto SLIGHTLY_DIVERGING_SLIM_MAPS_WEIGHT     = 20.0F;
  static constexpr auto DIVERGING_BLACK_STANDARD_MAPS_WEIGHT    = 35.0F;
  static constexpr auto RED_STANDARD_MAPS_WEIGHT                = 35.0F;
  static constexpr auto GREEN_STANDARD_MAPS_WEIGHT              = 40.0F;
  static constexpr auto BLUE_STANDARD_MAPS_WEIGHT               = 40.0F;
  static constexpr auto YELLOW_STANDARD_MAPS_WEIGHT             = 40.0F;
  static constexpr auto ORANGE_STANDARD_MAPS_WEIGHT             = 40.0F;
  static constexpr auto PURPLE_STANDARD_MAPS_WEIGHT             = 90.0F;
  static constexpr auto CITIES_STANDARD_MAPS_WEIGHT             = 90.0F;
  static constexpr auto SEASONS_STANDARD_MAPS_WEIGHT            = 90.0F;
  static constexpr auto HEAT_STANDARD_MAPS_WEIGHT               = 90.0F;
  static constexpr auto COLD_STANDARD_MAPS_WEIGHT               = 90.0F;
  static constexpr auto PASTEL_STANDARD_MAPS_WEIGHT             = 90.0F;
  static constexpr auto WES_ANDERSON_MAPS_WEIGHT                = 90.0F;

  return {
      m_goomRand,
      {
        {Groups::ALL_MAPS_UNWEIGHTED, ALL_MAPS_UNWEIGHTED_WEIGHT},
        {Groups::ALL_STANDARD_MAPS, ALL_STANDARD_MAPS_WEIGHT},
        {Groups::ALL_SLIM_MAPS, ALL_SLIM_MAPS_WEIGHT},
        {Groups::MOSTLY_SEQUENTIAL_STANDARD_MAPS, MOSTLY_SEQUENTIAL_STANDARD_MAPS_WEIGHT},
        {Groups::MOSTLY_SEQUENTIAL_SLIM_MAPS, MOSTLY_SEQUENTIAL_SLIM_MAPS_WEIGHT},
        {Groups::SLIGHTLY_DIVERGING_STANDARD_MAPS, SLIGHTLY_DIVERGING_STANDARD_MAPS_WEIGHT},
        {Groups::SLIGHTLY_DIVERGING_SLIM_MAPS, SLIGHTLY_DIVERGING_SLIM_MAPS_WEIGHT},
        {Groups::DIVERGING_BLACK_STANDARD_MAPS, DIVERGING_BLACK_STANDARD_MAPS_WEIGHT},
        {Groups::RED_STANDARD_MAPS, RED_STANDARD_MAPS_WEIGHT},
        {Groups::GREEN_STANDARD_MAPS, GREEN_STANDARD_MAPS_WEIGHT},
        {Groups::BLUE_STANDARD_MAPS, BLUE_STANDARD_MAPS_WEIGHT},
        {Groups::YELLOW_STANDARD_MAPS, YELLOW_STANDARD_MAPS_WEIGHT},
        {Groups::ORANGE_STANDARD_MAPS, ORANGE_STANDARD_MAPS_WEIGHT},
        {Groups::PURPLE_STANDARD_MAPS, PURPLE_STANDARD_MAPS_WEIGHT},
        {Groups::CITIES_STANDARD_MAPS, CITIES_STANDARD_MAPS_WEIGHT},
        {Groups::SEASONS_STANDARD_MAPS, SEASONS_STANDARD_MAPS_WEIGHT},
        {Groups::HEAT_STANDARD_MAPS, HEAT_STANDARD_MAPS_WEIGHT},
        {Groups::COLD_STANDARD_MAPS, COLD_STANDARD_MAPS_WEIGHT},
        {Groups::PASTEL_STANDARD_MAPS, PASTEL_STANDARD_MAPS_WEIGHT},
        {Groups::WES_ANDERSON_MAPS, WES_ANDERSON_MAPS_WEIGHT},
        }
  };
}

auto VisualFxWeightedColorMaps::GetDots0Groups() const noexcept -> WeightedGroups
{
  static constexpr auto ALL_MAPS_UNWEIGHTED_WEIGHT              = 05.0F;
  static constexpr auto ALL_STANDARD_MAPS_WEIGHT                = 05.0F;
  static constexpr auto ALL_SLIM_MAPS_WEIGHT                    = 05.0F;
  static constexpr auto MOSTLY_SEQUENTIAL_STANDARD_MAPS_WEIGHT  = 05.0F;
  static constexpr auto MOSTLY_SEQUENTIAL_SLIM_MAPS_WEIGHT      = 05.0F;
  static constexpr auto SLIGHTLY_DIVERGING_STANDARD_MAPS_WEIGHT = 05.0F;
  static constexpr auto SLIGHTLY_DIVERGING_SLIM_MAPS_WEIGHT     = 20.0F;
  static constexpr auto DIVERGING_BLACK_STANDARD_MAPS_WEIGHT    = 35.0F;
  static constexpr auto RED_STANDARD_MAPS_WEIGHT                = 35.0F;
  static constexpr auto GREEN_STANDARD_MAPS_WEIGHT              = 40.0F;
  static constexpr auto BLUE_STANDARD_MAPS_WEIGHT               = 40.0F;
  static constexpr auto YELLOW_STANDARD_MAPS_WEIGHT             = 40.0F;
  static constexpr auto ORANGE_STANDARD_MAPS_WEIGHT             = 40.0F;
  static constexpr auto PURPLE_STANDARD_MAPS_WEIGHT             = 90.0F;
  static constexpr auto CITIES_STANDARD_MAPS_WEIGHT             = 90.0F;
  static constexpr auto SEASONS_STANDARD_MAPS_WEIGHT            = 90.0F;
  static constexpr auto HEAT_STANDARD_MAPS_WEIGHT               = 90.0F;
  static constexpr auto COLD_STANDARD_MAPS_WEIGHT               = 90.0F;
  static constexpr auto PASTEL_STANDARD_MAPS_WEIGHT             = 90.0F;
  static constexpr auto WES_ANDERSON_MAPS_WEIGHT                = 90.0F;

  return {
      m_goomRand,
      {
        {Groups::ALL_MAPS_UNWEIGHTED, ALL_MAPS_UNWEIGHTED_WEIGHT},
        {Groups::ALL_STANDARD_MAPS, ALL_STANDARD_MAPS_WEIGHT},
        {Groups::ALL_SLIM_MAPS, ALL_SLIM_MAPS_WEIGHT},
        {Groups::MOSTLY_SEQUENTIAL_STANDARD_MAPS, MOSTLY_SEQUENTIAL_STANDARD_MAPS_WEIGHT},
        {Groups::MOSTLY_SEQUENTIAL_SLIM_MAPS, MOSTLY_SEQUENTIAL_SLIM_MAPS_WEIGHT},
        {Groups::SLIGHTLY_DIVERGING_STANDARD_MAPS, SLIGHTLY_DIVERGING_STANDARD_MAPS_WEIGHT},
        {Groups::SLIGHTLY_DIVERGING_SLIM_MAPS, SLIGHTLY_DIVERGING_SLIM_MAPS_WEIGHT},
        {Groups::DIVERGING_BLACK_STANDARD_MAPS, DIVERGING_BLACK_STANDARD_MAPS_WEIGHT},
        {Groups::RED_STANDARD_MAPS, RED_STANDARD_MAPS_WEIGHT},
        {Groups::GREEN_STANDARD_MAPS, GREEN_STANDARD_MAPS_WEIGHT},
        {Groups::BLUE_STANDARD_MAPS, BLUE_STANDARD_MAPS_WEIGHT},
        {Groups::YELLOW_STANDARD_MAPS, YELLOW_STANDARD_MAPS_WEIGHT},
        {Groups::ORANGE_STANDARD_MAPS, ORANGE_STANDARD_MAPS_WEIGHT},
        {Groups::PURPLE_STANDARD_MAPS, PURPLE_STANDARD_MAPS_WEIGHT},
        {Groups::CITIES_STANDARD_MAPS, CITIES_STANDARD_MAPS_WEIGHT},
        {Groups::SEASONS_STANDARD_MAPS, SEASONS_STANDARD_MAPS_WEIGHT},
        {Groups::HEAT_STANDARD_MAPS, HEAT_STANDARD_MAPS_WEIGHT},
        {Groups::COLD_STANDARD_MAPS, COLD_STANDARD_MAPS_WEIGHT},
        {Groups::PASTEL_STANDARD_MAPS, PASTEL_STANDARD_MAPS_WEIGHT},
        {Groups::WES_ANDERSON_MAPS, WES_ANDERSON_MAPS_WEIGHT},
        }
  };
}

auto VisualFxWeightedColorMaps::GetDots1Groups() const noexcept -> WeightedGroups
{
  static constexpr auto ALL_MAPS_UNWEIGHTED_WEIGHT              = 05.0F;
  static constexpr auto ALL_STANDARD_MAPS_WEIGHT                = 05.0F;
  static constexpr auto ALL_SLIM_MAPS_WEIGHT                    = 05.0F;
  static constexpr auto MOSTLY_SEQUENTIAL_STANDARD_MAPS_WEIGHT  = 05.0F;
  static constexpr auto MOSTLY_SEQUENTIAL_SLIM_MAPS_WEIGHT      = 05.0F;
  static constexpr auto SLIGHTLY_DIVERGING_STANDARD_MAPS_WEIGHT = 05.0F;
  static constexpr auto SLIGHTLY_DIVERGING_SLIM_MAPS_WEIGHT     = 20.0F;
  static constexpr auto DIVERGING_BLACK_STANDARD_MAPS_WEIGHT    = 35.0F;
  static constexpr auto RED_STANDARD_MAPS_WEIGHT                = 35.0F;
  static constexpr auto GREEN_STANDARD_MAPS_WEIGHT              = 40.0F;
  static constexpr auto BLUE_STANDARD_MAPS_WEIGHT               = 40.0F;
  static constexpr auto YELLOW_STANDARD_MAPS_WEIGHT             = 40.0F;
  static constexpr auto ORANGE_STANDARD_MAPS_WEIGHT             = 40.0F;
  static constexpr auto PURPLE_STANDARD_MAPS_WEIGHT             = 90.0F;
  static constexpr auto CITIES_STANDARD_MAPS_WEIGHT             = 90.0F;
  static constexpr auto SEASONS_STANDARD_MAPS_WEIGHT            = 90.0F;
  static constexpr auto HEAT_STANDARD_MAPS_WEIGHT               = 90.0F;
  static constexpr auto COLD_STANDARD_MAPS_WEIGHT               = 90.0F;
  static constexpr auto PASTEL_STANDARD_MAPS_WEIGHT             = 90.0F;
  static constexpr auto WES_ANDERSON_MAPS_WEIGHT                = 90.0F;

  return {
      m_goomRand,
      {
        {Groups::ALL_MAPS_UNWEIGHTED, ALL_MAPS_UNWEIGHTED_WEIGHT},
        {Groups::ALL_STANDARD_MAPS, ALL_STANDARD_MAPS_WEIGHT},
        {Groups::ALL_SLIM_MAPS, ALL_SLIM_MAPS_WEIGHT},
        {Groups::MOSTLY_SEQUENTIAL_STANDARD_MAPS, MOSTLY_SEQUENTIAL_STANDARD_MAPS_WEIGHT},
        {Groups::MOSTLY_SEQUENTIAL_SLIM_MAPS, MOSTLY_SEQUENTIAL_SLIM_MAPS_WEIGHT},
        {Groups::SLIGHTLY_DIVERGING_STANDARD_MAPS, SLIGHTLY_DIVERGING_STANDARD_MAPS_WEIGHT},
        {Groups::SLIGHTLY_DIVERGING_SLIM_MAPS, SLIGHTLY_DIVERGING_SLIM_MAPS_WEIGHT},
        {Groups::DIVERGING_BLACK_STANDARD_MAPS, DIVERGING_BLACK_STANDARD_MAPS_WEIGHT},
        {Groups::RED_STANDARD_MAPS, RED_STANDARD_MAPS_WEIGHT},
        {Groups::GREEN_STANDARD_MAPS, GREEN_STANDARD_MAPS_WEIGHT},
        {Groups::BLUE_STANDARD_MAPS, BLUE_STANDARD_MAPS_WEIGHT},
        {Groups::YELLOW_STANDARD_MAPS, YELLOW_STANDARD_MAPS_WEIGHT},
        {Groups::ORANGE_STANDARD_MAPS, ORANGE_STANDARD_MAPS_WEIGHT},
        {Groups::PURPLE_STANDARD_MAPS, PURPLE_STANDARD_MAPS_WEIGHT},
        {Groups::CITIES_STANDARD_MAPS, CITIES_STANDARD_MAPS_WEIGHT},
        {Groups::SEASONS_STANDARD_MAPS, SEASONS_STANDARD_MAPS_WEIGHT},
        {Groups::HEAT_STANDARD_MAPS, HEAT_STANDARD_MAPS_WEIGHT},
        {Groups::COLD_STANDARD_MAPS, COLD_STANDARD_MAPS_WEIGHT},
        {Groups::PASTEL_STANDARD_MAPS, PASTEL_STANDARD_MAPS_WEIGHT},
        {Groups::WES_ANDERSON_MAPS, WES_ANDERSON_MAPS_WEIGHT},
        }
  };
}

auto VisualFxWeightedColorMaps::GetDots2Groups() const noexcept -> WeightedGroups
{
  static constexpr auto ALL_MAPS_UNWEIGHTED_WEIGHT              = 05.0F;
  static constexpr auto ALL_STANDARD_MAPS_WEIGHT                = 05.0F;
  static constexpr auto ALL_SLIM_MAPS_WEIGHT                    = 05.0F;
  static constexpr auto MOSTLY_SEQUENTIAL_STANDARD_MAPS_WEIGHT  = 05.0F;
  static constexpr auto MOSTLY_SEQUENTIAL_SLIM_MAPS_WEIGHT      = 05.0F;
  static constexpr auto SLIGHTLY_DIVERGING_STANDARD_MAPS_WEIGHT = 05.0F;
  static constexpr auto SLIGHTLY_DIVERGING_SLIM_MAPS_WEIGHT     = 20.0F;
  static constexpr auto DIVERGING_BLACK_STANDARD_MAPS_WEIGHT    = 35.0F;
  static constexpr auto RED_STANDARD_MAPS_WEIGHT                = 35.0F;
  static constexpr auto GREEN_STANDARD_MAPS_WEIGHT              = 40.0F;
  static constexpr auto BLUE_STANDARD_MAPS_WEIGHT               = 40.0F;
  static constexpr auto YELLOW_STANDARD_MAPS_WEIGHT             = 40.0F;
  static constexpr auto ORANGE_STANDARD_MAPS_WEIGHT             = 40.0F;
  static constexpr auto PURPLE_STANDARD_MAPS_WEIGHT             = 90.0F;
  static constexpr auto CITIES_STANDARD_MAPS_WEIGHT             = 90.0F;
  static constexpr auto SEASONS_STANDARD_MAPS_WEIGHT            = 90.0F;
  static constexpr auto HEAT_STANDARD_MAPS_WEIGHT               = 90.0F;
  static constexpr auto COLD_STANDARD_MAPS_WEIGHT               = 90.0F;
  static constexpr auto PASTEL_STANDARD_MAPS_WEIGHT             = 90.0F;
  static constexpr auto WES_ANDERSON_MAPS_WEIGHT                = 90.0F;

  return {
      m_goomRand,
      {
        {Groups::ALL_MAPS_UNWEIGHTED, ALL_MAPS_UNWEIGHTED_WEIGHT},
        {Groups::ALL_STANDARD_MAPS, ALL_STANDARD_MAPS_WEIGHT},
        {Groups::ALL_SLIM_MAPS, ALL_SLIM_MAPS_WEIGHT},
        {Groups::MOSTLY_SEQUENTIAL_STANDARD_MAPS, MOSTLY_SEQUENTIAL_STANDARD_MAPS_WEIGHT},
        {Groups::MOSTLY_SEQUENTIAL_SLIM_MAPS, MOSTLY_SEQUENTIAL_SLIM_MAPS_WEIGHT},
        {Groups::SLIGHTLY_DIVERGING_STANDARD_MAPS, SLIGHTLY_DIVERGING_STANDARD_MAPS_WEIGHT},
        {Groups::SLIGHTLY_DIVERGING_SLIM_MAPS, SLIGHTLY_DIVERGING_SLIM_MAPS_WEIGHT},
        {Groups::DIVERGING_BLACK_STANDARD_MAPS, DIVERGING_BLACK_STANDARD_MAPS_WEIGHT},
        {Groups::RED_STANDARD_MAPS, RED_STANDARD_MAPS_WEIGHT},
        {Groups::GREEN_STANDARD_MAPS, GREEN_STANDARD_MAPS_WEIGHT},
        {Groups::BLUE_STANDARD_MAPS, BLUE_STANDARD_MAPS_WEIGHT},
        {Groups::YELLOW_STANDARD_MAPS, YELLOW_STANDARD_MAPS_WEIGHT},
        {Groups::ORANGE_STANDARD_MAPS, ORANGE_STANDARD_MAPS_WEIGHT},
        {Groups::PURPLE_STANDARD_MAPS, PURPLE_STANDARD_MAPS_WEIGHT},
        {Groups::CITIES_STANDARD_MAPS, CITIES_STANDARD_MAPS_WEIGHT},
        {Groups::SEASONS_STANDARD_MAPS, SEASONS_STANDARD_MAPS_WEIGHT},
        {Groups::HEAT_STANDARD_MAPS, HEAT_STANDARD_MAPS_WEIGHT},
        {Groups::COLD_STANDARD_MAPS, COLD_STANDARD_MAPS_WEIGHT},
        {Groups::PASTEL_STANDARD_MAPS, PASTEL_STANDARD_MAPS_WEIGHT},
        {Groups::WES_ANDERSON_MAPS, WES_ANDERSON_MAPS_WEIGHT},
        }
  };
}

auto VisualFxWeightedColorMaps::GetDots3Groups() const noexcept -> WeightedGroups
{
  static constexpr auto ALL_MAPS_UNWEIGHTED_WEIGHT              = 05.0F;
  static constexpr auto ALL_STANDARD_MAPS_WEIGHT                = 05.0F;
  static constexpr auto ALL_SLIM_MAPS_WEIGHT                    = 05.0F;
  static constexpr auto MOSTLY_SEQUENTIAL_STANDARD_MAPS_WEIGHT  = 05.0F;
  static constexpr auto MOSTLY_SEQUENTIAL_SLIM_MAPS_WEIGHT      = 05.0F;
  static constexpr auto SLIGHTLY_DIVERGING_STANDARD_MAPS_WEIGHT = 05.0F;
  static constexpr auto SLIGHTLY_DIVERGING_SLIM_MAPS_WEIGHT     = 20.0F;
  static constexpr auto DIVERGING_BLACK_STANDARD_MAPS_WEIGHT    = 35.0F;
  static constexpr auto RED_STANDARD_MAPS_WEIGHT                = 35.0F;
  static constexpr auto GREEN_STANDARD_MAPS_WEIGHT              = 40.0F;
  static constexpr auto BLUE_STANDARD_MAPS_WEIGHT               = 40.0F;
  static constexpr auto YELLOW_STANDARD_MAPS_WEIGHT             = 40.0F;
  static constexpr auto ORANGE_STANDARD_MAPS_WEIGHT             = 40.0F;
  static constexpr auto PURPLE_STANDARD_MAPS_WEIGHT             = 90.0F;
  static constexpr auto CITIES_STANDARD_MAPS_WEIGHT             = 90.0F;
  static constexpr auto SEASONS_STANDARD_MAPS_WEIGHT            = 90.0F;
  static constexpr auto HEAT_STANDARD_MAPS_WEIGHT               = 90.0F;
  static constexpr auto COLD_STANDARD_MAPS_WEIGHT               = 90.0F;
  static constexpr auto PASTEL_STANDARD_MAPS_WEIGHT             = 90.0F;
  static constexpr auto WES_ANDERSON_MAPS_WEIGHT                = 90.0F;

  return {
      m_goomRand,
      {
        {Groups::ALL_MAPS_UNWEIGHTED, ALL_MAPS_UNWEIGHTED_WEIGHT},
        {Groups::ALL_STANDARD_MAPS, ALL_STANDARD_MAPS_WEIGHT},
        {Groups::ALL_SLIM_MAPS, ALL_SLIM_MAPS_WEIGHT},
        {Groups::MOSTLY_SEQUENTIAL_STANDARD_MAPS, MOSTLY_SEQUENTIAL_STANDARD_MAPS_WEIGHT},
        {Groups::MOSTLY_SEQUENTIAL_SLIM_MAPS, MOSTLY_SEQUENTIAL_SLIM_MAPS_WEIGHT},
        {Groups::SLIGHTLY_DIVERGING_STANDARD_MAPS, SLIGHTLY_DIVERGING_STANDARD_MAPS_WEIGHT},
        {Groups::SLIGHTLY_DIVERGING_SLIM_MAPS, SLIGHTLY_DIVERGING_SLIM_MAPS_WEIGHT},
        {Groups::DIVERGING_BLACK_STANDARD_MAPS, DIVERGING_BLACK_STANDARD_MAPS_WEIGHT},
        {Groups::RED_STANDARD_MAPS, RED_STANDARD_MAPS_WEIGHT},
        {Groups::GREEN_STANDARD_MAPS, GREEN_STANDARD_MAPS_WEIGHT},
        {Groups::BLUE_STANDARD_MAPS, BLUE_STANDARD_MAPS_WEIGHT},
        {Groups::YELLOW_STANDARD_MAPS, YELLOW_STANDARD_MAPS_WEIGHT},
        {Groups::ORANGE_STANDARD_MAPS, ORANGE_STANDARD_MAPS_WEIGHT},
        {Groups::PURPLE_STANDARD_MAPS, PURPLE_STANDARD_MAPS_WEIGHT},
        {Groups::CITIES_STANDARD_MAPS, CITIES_STANDARD_MAPS_WEIGHT},
        {Groups::SEASONS_STANDARD_MAPS, SEASONS_STANDARD_MAPS_WEIGHT},
        {Groups::HEAT_STANDARD_MAPS, HEAT_STANDARD_MAPS_WEIGHT},
        {Groups::COLD_STANDARD_MAPS, COLD_STANDARD_MAPS_WEIGHT},
        {Groups::PASTEL_STANDARD_MAPS, PASTEL_STANDARD_MAPS_WEIGHT},
        {Groups::WES_ANDERSON_MAPS, WES_ANDERSON_MAPS_WEIGHT},
        }
  };
}

auto VisualFxWeightedColorMaps::GetDots4Groups() const noexcept -> WeightedGroups
{
  static constexpr auto ALL_MAPS_UNWEIGHTED_WEIGHT              = 05.0F;
  static constexpr auto ALL_STANDARD_MAPS_WEIGHT                = 05.0F;
  static constexpr auto ALL_SLIM_MAPS_WEIGHT                    = 05.0F;
  static constexpr auto MOSTLY_SEQUENTIAL_STANDARD_MAPS_WEIGHT  = 05.0F;
  static constexpr auto MOSTLY_SEQUENTIAL_SLIM_MAPS_WEIGHT      = 05.0F;
  static constexpr auto SLIGHTLY_DIVERGING_STANDARD_MAPS_WEIGHT = 05.0F;
  static constexpr auto SLIGHTLY_DIVERGING_SLIM_MAPS_WEIGHT     = 20.0F;
  static constexpr auto DIVERGING_BLACK_STANDARD_MAPS_WEIGHT    = 35.0F;
  static constexpr auto RED_STANDARD_MAPS_WEIGHT                = 35.0F;
  static constexpr auto GREEN_STANDARD_MAPS_WEIGHT              = 40.0F;
  static constexpr auto BLUE_STANDARD_MAPS_WEIGHT               = 40.0F;
  static constexpr auto YELLOW_STANDARD_MAPS_WEIGHT             = 40.0F;
  static constexpr auto ORANGE_STANDARD_MAPS_WEIGHT             = 40.0F;
  static constexpr auto PURPLE_STANDARD_MAPS_WEIGHT             = 90.0F;
  static constexpr auto CITIES_STANDARD_MAPS_WEIGHT             = 90.0F;
  static constexpr auto SEASONS_STANDARD_MAPS_WEIGHT            = 90.0F;
  static constexpr auto HEAT_STANDARD_MAPS_WEIGHT               = 90.0F;
  static constexpr auto COLD_STANDARD_MAPS_WEIGHT               = 90.0F;
  static constexpr auto PASTEL_STANDARD_MAPS_WEIGHT             = 90.0F;
  static constexpr auto WES_ANDERSON_MAPS_WEIGHT                = 90.0F;

  return {
      m_goomRand,
      {
        {Groups::ALL_MAPS_UNWEIGHTED, ALL_MAPS_UNWEIGHTED_WEIGHT},
        {Groups::ALL_STANDARD_MAPS, ALL_STANDARD_MAPS_WEIGHT},
        {Groups::ALL_SLIM_MAPS, ALL_SLIM_MAPS_WEIGHT},
        {Groups::MOSTLY_SEQUENTIAL_STANDARD_MAPS, MOSTLY_SEQUENTIAL_STANDARD_MAPS_WEIGHT},
        {Groups::MOSTLY_SEQUENTIAL_SLIM_MAPS, MOSTLY_SEQUENTIAL_SLIM_MAPS_WEIGHT},
        {Groups::SLIGHTLY_DIVERGING_STANDARD_MAPS, SLIGHTLY_DIVERGING_STANDARD_MAPS_WEIGHT},
        {Groups::SLIGHTLY_DIVERGING_SLIM_MAPS, SLIGHTLY_DIVERGING_SLIM_MAPS_WEIGHT},
        {Groups::DIVERGING_BLACK_STANDARD_MAPS, DIVERGING_BLACK_STANDARD_MAPS_WEIGHT},
        {Groups::RED_STANDARD_MAPS, RED_STANDARD_MAPS_WEIGHT},
        {Groups::GREEN_STANDARD_MAPS, GREEN_STANDARD_MAPS_WEIGHT},
        {Groups::BLUE_STANDARD_MAPS, BLUE_STANDARD_MAPS_WEIGHT},
        {Groups::YELLOW_STANDARD_MAPS, YELLOW_STANDARD_MAPS_WEIGHT},
        {Groups::ORANGE_STANDARD_MAPS, ORANGE_STANDARD_MAPS_WEIGHT},
        {Groups::PURPLE_STANDARD_MAPS, PURPLE_STANDARD_MAPS_WEIGHT},
        {Groups::CITIES_STANDARD_MAPS, CITIES_STANDARD_MAPS_WEIGHT},
        {Groups::SEASONS_STANDARD_MAPS, SEASONS_STANDARD_MAPS_WEIGHT},
        {Groups::HEAT_STANDARD_MAPS, HEAT_STANDARD_MAPS_WEIGHT},
        {Groups::COLD_STANDARD_MAPS, COLD_STANDARD_MAPS_WEIGHT},
        {Groups::PASTEL_STANDARD_MAPS, PASTEL_STANDARD_MAPS_WEIGHT},
        {Groups::WES_ANDERSON_MAPS, WES_ANDERSON_MAPS_WEIGHT},
        }
  };
}

auto VisualFxWeightedColorMaps::GetIfsGroups() const noexcept -> WeightedGroups
{
  static constexpr auto ALL_MAPS_UNWEIGHTED_WEIGHT              = 05.0F;
  static constexpr auto ALL_STANDARD_MAPS_WEIGHT                = 05.0F;
  static constexpr auto ALL_SLIM_MAPS_WEIGHT                    = 05.0F;
  static constexpr auto MOSTLY_SEQUENTIAL_STANDARD_MAPS_WEIGHT  = 05.0F;
  static constexpr auto MOSTLY_SEQUENTIAL_SLIM_MAPS_WEIGHT      = 05.0F;
  static constexpr auto SLIGHTLY_DIVERGING_STANDARD_MAPS_WEIGHT = 05.0F;
  static constexpr auto SLIGHTLY_DIVERGING_SLIM_MAPS_WEIGHT     = 20.0F;
  static constexpr auto DIVERGING_BLACK_STANDARD_MAPS_WEIGHT    = 35.0F;
  static constexpr auto RED_STANDARD_MAPS_WEIGHT                = 35.0F;
  static constexpr auto GREEN_STANDARD_MAPS_WEIGHT              = 40.0F;
  static constexpr auto BLUE_STANDARD_MAPS_WEIGHT               = 40.0F;
  static constexpr auto YELLOW_STANDARD_MAPS_WEIGHT             = 40.0F;
  static constexpr auto ORANGE_STANDARD_MAPS_WEIGHT             = 40.0F;
  static constexpr auto PURPLE_STANDARD_MAPS_WEIGHT             = 90.0F;
  static constexpr auto CITIES_STANDARD_MAPS_WEIGHT             = 90.0F;
  static constexpr auto SEASONS_STANDARD_MAPS_WEIGHT            = 90.0F;
  static constexpr auto HEAT_STANDARD_MAPS_WEIGHT               = 90.0F;
  static constexpr auto COLD_STANDARD_MAPS_WEIGHT               = 90.0F;
  static constexpr auto PASTEL_STANDARD_MAPS_WEIGHT             = 90.0F;
  static constexpr auto WES_ANDERSON_MAPS_WEIGHT                = 90.0F;

  return {
      m_goomRand,
      {
        {Groups::ALL_MAPS_UNWEIGHTED, ALL_MAPS_UNWEIGHTED_WEIGHT},
        {Groups::ALL_STANDARD_MAPS, ALL_STANDARD_MAPS_WEIGHT},
        {Groups::ALL_SLIM_MAPS, ALL_SLIM_MAPS_WEIGHT},
        {Groups::MOSTLY_SEQUENTIAL_STANDARD_MAPS, MOSTLY_SEQUENTIAL_STANDARD_MAPS_WEIGHT},
        {Groups::MOSTLY_SEQUENTIAL_SLIM_MAPS, MOSTLY_SEQUENTIAL_SLIM_MAPS_WEIGHT},
        {Groups::SLIGHTLY_DIVERGING_STANDARD_MAPS, SLIGHTLY_DIVERGING_STANDARD_MAPS_WEIGHT},
        {Groups::SLIGHTLY_DIVERGING_SLIM_MAPS, SLIGHTLY_DIVERGING_SLIM_MAPS_WEIGHT},
        {Groups::DIVERGING_BLACK_STANDARD_MAPS, DIVERGING_BLACK_STANDARD_MAPS_WEIGHT},
        {Groups::RED_STANDARD_MAPS, RED_STANDARD_MAPS_WEIGHT},
        {Groups::GREEN_STANDARD_MAPS, GREEN_STANDARD_MAPS_WEIGHT},
        {Groups::BLUE_STANDARD_MAPS, BLUE_STANDARD_MAPS_WEIGHT},
        {Groups::YELLOW_STANDARD_MAPS, YELLOW_STANDARD_MAPS_WEIGHT},
        {Groups::ORANGE_STANDARD_MAPS, ORANGE_STANDARD_MAPS_WEIGHT},
        {Groups::PURPLE_STANDARD_MAPS, PURPLE_STANDARD_MAPS_WEIGHT},
        {Groups::CITIES_STANDARD_MAPS, CITIES_STANDARD_MAPS_WEIGHT},
        {Groups::SEASONS_STANDARD_MAPS, SEASONS_STANDARD_MAPS_WEIGHT},
        {Groups::HEAT_STANDARD_MAPS, HEAT_STANDARD_MAPS_WEIGHT},
        {Groups::COLD_STANDARD_MAPS, COLD_STANDARD_MAPS_WEIGHT},
        {Groups::PASTEL_STANDARD_MAPS, PASTEL_STANDARD_MAPS_WEIGHT},
        {Groups::WES_ANDERSON_MAPS, WES_ANDERSON_MAPS_WEIGHT},
        }
  };
}

auto VisualFxWeightedColorMaps::GetImageGroups() const noexcept -> WeightedGroups
{
  static constexpr auto ALL_MAPS_UNWEIGHTED_WEIGHT              = 05.0F;
  static constexpr auto ALL_STANDARD_MAPS_WEIGHT                = 05.0F;
  static constexpr auto ALL_SLIM_MAPS_WEIGHT                    = 05.0F;
  static constexpr auto MOSTLY_SEQUENTIAL_STANDARD_MAPS_WEIGHT  = 05.0F;
  static constexpr auto MOSTLY_SEQUENTIAL_SLIM_MAPS_WEIGHT      = 05.0F;
  static constexpr auto SLIGHTLY_DIVERGING_STANDARD_MAPS_WEIGHT = 05.0F;
  static constexpr auto SLIGHTLY_DIVERGING_SLIM_MAPS_WEIGHT     = 20.0F;
  static constexpr auto DIVERGING_BLACK_STANDARD_MAPS_WEIGHT    = 35.0F;
  static constexpr auto RED_STANDARD_MAPS_WEIGHT                = 00.0F;
  static constexpr auto GREEN_STANDARD_MAPS_WEIGHT              = 00.0F;
  static constexpr auto BLUE_STANDARD_MAPS_WEIGHT               = 00.0F;
  static constexpr auto YELLOW_STANDARD_MAPS_WEIGHT             = 00.0F;
  static constexpr auto ORANGE_STANDARD_MAPS_WEIGHT             = 00.0F;
  static constexpr auto PURPLE_STANDARD_MAPS_WEIGHT             = 00.0F;
  static constexpr auto CITIES_STANDARD_MAPS_WEIGHT             = 90.0F;
  static constexpr auto SEASONS_STANDARD_MAPS_WEIGHT            = 90.0F;
  static constexpr auto HEAT_STANDARD_MAPS_WEIGHT               = 90.0F;
  static constexpr auto COLD_STANDARD_MAPS_WEIGHT               = 90.0F;
  static constexpr auto PASTEL_STANDARD_MAPS_WEIGHT             = 90.0F;
  static constexpr auto WES_ANDERSON_MAPS_WEIGHT                = 90.0F;

  return {
      m_goomRand,
      {
        {Groups::ALL_MAPS_UNWEIGHTED, ALL_MAPS_UNWEIGHTED_WEIGHT},
        {Groups::ALL_STANDARD_MAPS, ALL_STANDARD_MAPS_WEIGHT},
        {Groups::ALL_SLIM_MAPS, ALL_SLIM_MAPS_WEIGHT},
        {Groups::MOSTLY_SEQUENTIAL_STANDARD_MAPS, MOSTLY_SEQUENTIAL_STANDARD_MAPS_WEIGHT},
        {Groups::MOSTLY_SEQUENTIAL_SLIM_MAPS, MOSTLY_SEQUENTIAL_SLIM_MAPS_WEIGHT},
        {Groups::SLIGHTLY_DIVERGING_STANDARD_MAPS, SLIGHTLY_DIVERGING_STANDARD_MAPS_WEIGHT},
        {Groups::SLIGHTLY_DIVERGING_SLIM_MAPS, SLIGHTLY_DIVERGING_SLIM_MAPS_WEIGHT},
        {Groups::DIVERGING_BLACK_STANDARD_MAPS, DIVERGING_BLACK_STANDARD_MAPS_WEIGHT},
        {Groups::RED_STANDARD_MAPS, RED_STANDARD_MAPS_WEIGHT},
        {Groups::GREEN_STANDARD_MAPS, GREEN_STANDARD_MAPS_WEIGHT},
        {Groups::BLUE_STANDARD_MAPS, BLUE_STANDARD_MAPS_WEIGHT},
        {Groups::YELLOW_STANDARD_MAPS, YELLOW_STANDARD_MAPS_WEIGHT},
        {Groups::ORANGE_STANDARD_MAPS, ORANGE_STANDARD_MAPS_WEIGHT},
        {Groups::PURPLE_STANDARD_MAPS, PURPLE_STANDARD_MAPS_WEIGHT},
        {Groups::CITIES_STANDARD_MAPS, CITIES_STANDARD_MAPS_WEIGHT},
        {Groups::SEASONS_STANDARD_MAPS, SEASONS_STANDARD_MAPS_WEIGHT},
        {Groups::HEAT_STANDARD_MAPS, HEAT_STANDARD_MAPS_WEIGHT},
        {Groups::COLD_STANDARD_MAPS, COLD_STANDARD_MAPS_WEIGHT},
        {Groups::PASTEL_STANDARD_MAPS, PASTEL_STANDARD_MAPS_WEIGHT},
        {Groups::WES_ANDERSON_MAPS, WES_ANDERSON_MAPS_WEIGHT},
        }
  };
}

auto VisualFxWeightedColorMaps::GetLines1Groups() const noexcept -> WeightedGroups
{
  static constexpr auto ALL_MAPS_UNWEIGHTED_WEIGHT              = 05.0F;
  static constexpr auto ALL_STANDARD_MAPS_WEIGHT                = 05.0F;
  static constexpr auto ALL_SLIM_MAPS_WEIGHT                    = 05.0F;
  static constexpr auto MOSTLY_SEQUENTIAL_STANDARD_MAPS_WEIGHT  = 05.0F;
  static constexpr auto MOSTLY_SEQUENTIAL_SLIM_MAPS_WEIGHT      = 05.0F;
  static constexpr auto SLIGHTLY_DIVERGING_STANDARD_MAPS_WEIGHT = 05.0F;
  static constexpr auto SLIGHTLY_DIVERGING_SLIM_MAPS_WEIGHT     = 20.0F;
  static constexpr auto DIVERGING_BLACK_STANDARD_MAPS_WEIGHT    = 35.0F;
  static constexpr auto RED_STANDARD_MAPS_WEIGHT                = 35.0F;
  static constexpr auto GREEN_STANDARD_MAPS_WEIGHT              = 40.0F;
  static constexpr auto BLUE_STANDARD_MAPS_WEIGHT               = 40.0F;
  static constexpr auto YELLOW_STANDARD_MAPS_WEIGHT             = 40.0F;
  static constexpr auto ORANGE_STANDARD_MAPS_WEIGHT             = 40.0F;
  static constexpr auto PURPLE_STANDARD_MAPS_WEIGHT             = 90.0F;
  static constexpr auto CITIES_STANDARD_MAPS_WEIGHT             = 90.0F;
  static constexpr auto SEASONS_STANDARD_MAPS_WEIGHT            = 90.0F;
  static constexpr auto HEAT_STANDARD_MAPS_WEIGHT               = 90.0F;
  static constexpr auto COLD_STANDARD_MAPS_WEIGHT               = 90.0F;
  static constexpr auto PASTEL_STANDARD_MAPS_WEIGHT             = 90.0F;
  static constexpr auto WES_ANDERSON_MAPS_WEIGHT                = 90.0F;

  return {
      m_goomRand,
      {
        {Groups::ALL_MAPS_UNWEIGHTED, ALL_MAPS_UNWEIGHTED_WEIGHT},
        {Groups::ALL_STANDARD_MAPS, ALL_STANDARD_MAPS_WEIGHT},
        {Groups::ALL_SLIM_MAPS, ALL_SLIM_MAPS_WEIGHT},
        {Groups::MOSTLY_SEQUENTIAL_STANDARD_MAPS, MOSTLY_SEQUENTIAL_STANDARD_MAPS_WEIGHT},
        {Groups::MOSTLY_SEQUENTIAL_SLIM_MAPS, MOSTLY_SEQUENTIAL_SLIM_MAPS_WEIGHT},
        {Groups::SLIGHTLY_DIVERGING_STANDARD_MAPS, SLIGHTLY_DIVERGING_STANDARD_MAPS_WEIGHT},
        {Groups::SLIGHTLY_DIVERGING_SLIM_MAPS, SLIGHTLY_DIVERGING_SLIM_MAPS_WEIGHT},
        {Groups::DIVERGING_BLACK_STANDARD_MAPS, DIVERGING_BLACK_STANDARD_MAPS_WEIGHT},
        {Groups::RED_STANDARD_MAPS, RED_STANDARD_MAPS_WEIGHT},
        {Groups::GREEN_STANDARD_MAPS, GREEN_STANDARD_MAPS_WEIGHT},
        {Groups::BLUE_STANDARD_MAPS, BLUE_STANDARD_MAPS_WEIGHT},
        {Groups::YELLOW_STANDARD_MAPS, YELLOW_STANDARD_MAPS_WEIGHT},
        {Groups::ORANGE_STANDARD_MAPS, ORANGE_STANDARD_MAPS_WEIGHT},
        {Groups::PURPLE_STANDARD_MAPS, PURPLE_STANDARD_MAPS_WEIGHT},
        {Groups::CITIES_STANDARD_MAPS, CITIES_STANDARD_MAPS_WEIGHT},
        {Groups::SEASONS_STANDARD_MAPS, SEASONS_STANDARD_MAPS_WEIGHT},
        {Groups::HEAT_STANDARD_MAPS, HEAT_STANDARD_MAPS_WEIGHT},
        {Groups::COLD_STANDARD_MAPS, COLD_STANDARD_MAPS_WEIGHT},
        {Groups::PASTEL_STANDARD_MAPS, PASTEL_STANDARD_MAPS_WEIGHT},
        {Groups::WES_ANDERSON_MAPS, WES_ANDERSON_MAPS_WEIGHT},
        }
  };
}

auto VisualFxWeightedColorMaps::GetLines2Groups() const noexcept -> WeightedGroups
{
  static constexpr auto ALL_MAPS_UNWEIGHTED_WEIGHT              = 05.0F;
  static constexpr auto ALL_STANDARD_MAPS_WEIGHT                = 05.0F;
  static constexpr auto ALL_SLIM_MAPS_WEIGHT                    = 05.0F;
  static constexpr auto MOSTLY_SEQUENTIAL_STANDARD_MAPS_WEIGHT  = 05.0F;
  static constexpr auto MOSTLY_SEQUENTIAL_SLIM_MAPS_WEIGHT      = 05.0F;
  static constexpr auto SLIGHTLY_DIVERGING_STANDARD_MAPS_WEIGHT = 05.0F;
  static constexpr auto SLIGHTLY_DIVERGING_SLIM_MAPS_WEIGHT     = 20.0F;
  static constexpr auto DIVERGING_BLACK_STANDARD_MAPS_WEIGHT    = 35.0F;
  static constexpr auto RED_STANDARD_MAPS_WEIGHT                = 35.0F;
  static constexpr auto GREEN_STANDARD_MAPS_WEIGHT              = 40.0F;
  static constexpr auto BLUE_STANDARD_MAPS_WEIGHT               = 40.0F;
  static constexpr auto YELLOW_STANDARD_MAPS_WEIGHT             = 40.0F;
  static constexpr auto ORANGE_STANDARD_MAPS_WEIGHT             = 40.0F;
  static constexpr auto PURPLE_STANDARD_MAPS_WEIGHT             = 90.0F;
  static constexpr auto CITIES_STANDARD_MAPS_WEIGHT             = 90.0F;
  static constexpr auto SEASONS_STANDARD_MAPS_WEIGHT            = 90.0F;
  static constexpr auto HEAT_STANDARD_MAPS_WEIGHT               = 90.0F;
  static constexpr auto COLD_STANDARD_MAPS_WEIGHT               = 90.0F;
  static constexpr auto PASTEL_STANDARD_MAPS_WEIGHT             = 90.0F;
  static constexpr auto WES_ANDERSON_MAPS_WEIGHT                = 90.0F;

  return {
      m_goomRand,
      {
        {Groups::ALL_MAPS_UNWEIGHTED, ALL_MAPS_UNWEIGHTED_WEIGHT},
        {Groups::ALL_STANDARD_MAPS, ALL_STANDARD_MAPS_WEIGHT},
        {Groups::ALL_SLIM_MAPS, ALL_SLIM_MAPS_WEIGHT},
        {Groups::MOSTLY_SEQUENTIAL_STANDARD_MAPS, MOSTLY_SEQUENTIAL_STANDARD_MAPS_WEIGHT},
        {Groups::MOSTLY_SEQUENTIAL_SLIM_MAPS, MOSTLY_SEQUENTIAL_SLIM_MAPS_WEIGHT},
        {Groups::SLIGHTLY_DIVERGING_STANDARD_MAPS, SLIGHTLY_DIVERGING_STANDARD_MAPS_WEIGHT},
        {Groups::SLIGHTLY_DIVERGING_SLIM_MAPS, SLIGHTLY_DIVERGING_SLIM_MAPS_WEIGHT},
        {Groups::DIVERGING_BLACK_STANDARD_MAPS, DIVERGING_BLACK_STANDARD_MAPS_WEIGHT},
        {Groups::RED_STANDARD_MAPS, RED_STANDARD_MAPS_WEIGHT},
        {Groups::GREEN_STANDARD_MAPS, GREEN_STANDARD_MAPS_WEIGHT},
        {Groups::BLUE_STANDARD_MAPS, BLUE_STANDARD_MAPS_WEIGHT},
        {Groups::YELLOW_STANDARD_MAPS, YELLOW_STANDARD_MAPS_WEIGHT},
        {Groups::ORANGE_STANDARD_MAPS, ORANGE_STANDARD_MAPS_WEIGHT},
        {Groups::PURPLE_STANDARD_MAPS, PURPLE_STANDARD_MAPS_WEIGHT},
        {Groups::CITIES_STANDARD_MAPS, CITIES_STANDARD_MAPS_WEIGHT},
        {Groups::SEASONS_STANDARD_MAPS, SEASONS_STANDARD_MAPS_WEIGHT},
        {Groups::HEAT_STANDARD_MAPS, HEAT_STANDARD_MAPS_WEIGHT},
        {Groups::COLD_STANDARD_MAPS, COLD_STANDARD_MAPS_WEIGHT},
        {Groups::PASTEL_STANDARD_MAPS, PASTEL_STANDARD_MAPS_WEIGHT},
        {Groups::WES_ANDERSON_MAPS, WES_ANDERSON_MAPS_WEIGHT},
        }
  };
}

auto VisualFxWeightedColorMaps::GetShapesMainGroups() const noexcept -> WeightedGroups
{
  static constexpr auto ALL_MAPS_UNWEIGHTED_WEIGHT              = 05.0F;
  static constexpr auto ALL_STANDARD_MAPS_WEIGHT                = 05.0F;
  static constexpr auto ALL_SLIM_MAPS_WEIGHT                    = 05.0F;
  static constexpr auto MOSTLY_SEQUENTIAL_STANDARD_MAPS_WEIGHT  = 05.0F;
  static constexpr auto MOSTLY_SEQUENTIAL_SLIM_MAPS_WEIGHT      = 05.0F;
  static constexpr auto SLIGHTLY_DIVERGING_STANDARD_MAPS_WEIGHT = 05.0F;
  static constexpr auto SLIGHTLY_DIVERGING_SLIM_MAPS_WEIGHT     = 20.0F;
  static constexpr auto DIVERGING_BLACK_STANDARD_MAPS_WEIGHT    = 35.0F;
  static constexpr auto RED_STANDARD_MAPS_WEIGHT                = 35.0F;
  static constexpr auto GREEN_STANDARD_MAPS_WEIGHT              = 40.0F;
  static constexpr auto BLUE_STANDARD_MAPS_WEIGHT               = 40.0F;
  static constexpr auto YELLOW_STANDARD_MAPS_WEIGHT             = 40.0F;
  static constexpr auto ORANGE_STANDARD_MAPS_WEIGHT             = 40.0F;
  static constexpr auto PURPLE_STANDARD_MAPS_WEIGHT             = 90.0F;
  static constexpr auto CITIES_STANDARD_MAPS_WEIGHT             = 90.0F;
  static constexpr auto SEASONS_STANDARD_MAPS_WEIGHT            = 90.0F;
  static constexpr auto HEAT_STANDARD_MAPS_WEIGHT               = 90.0F;
  static constexpr auto COLD_STANDARD_MAPS_WEIGHT               = 90.0F;
  static constexpr auto PASTEL_STANDARD_MAPS_WEIGHT             = 90.0F;
  static constexpr auto WES_ANDERSON_MAPS_WEIGHT                = 90.0F;

  return {
      m_goomRand,
      {
        {Groups::ALL_MAPS_UNWEIGHTED, ALL_MAPS_UNWEIGHTED_WEIGHT},
        {Groups::ALL_STANDARD_MAPS, ALL_STANDARD_MAPS_WEIGHT},
        {Groups::ALL_SLIM_MAPS, ALL_SLIM_MAPS_WEIGHT},
        {Groups::MOSTLY_SEQUENTIAL_STANDARD_MAPS, MOSTLY_SEQUENTIAL_STANDARD_MAPS_WEIGHT},
        {Groups::MOSTLY_SEQUENTIAL_SLIM_MAPS, MOSTLY_SEQUENTIAL_SLIM_MAPS_WEIGHT},
        {Groups::SLIGHTLY_DIVERGING_STANDARD_MAPS, SLIGHTLY_DIVERGING_STANDARD_MAPS_WEIGHT},
        {Groups::SLIGHTLY_DIVERGING_SLIM_MAPS, SLIGHTLY_DIVERGING_SLIM_MAPS_WEIGHT},
        {Groups::DIVERGING_BLACK_STANDARD_MAPS, DIVERGING_BLACK_STANDARD_MAPS_WEIGHT},
        {Groups::RED_STANDARD_MAPS, RED_STANDARD_MAPS_WEIGHT},
        {Groups::GREEN_STANDARD_MAPS, GREEN_STANDARD_MAPS_WEIGHT},
        {Groups::BLUE_STANDARD_MAPS, BLUE_STANDARD_MAPS_WEIGHT},
        {Groups::YELLOW_STANDARD_MAPS, YELLOW_STANDARD_MAPS_WEIGHT},
        {Groups::ORANGE_STANDARD_MAPS, ORANGE_STANDARD_MAPS_WEIGHT},
        {Groups::PURPLE_STANDARD_MAPS, PURPLE_STANDARD_MAPS_WEIGHT},
        {Groups::CITIES_STANDARD_MAPS, CITIES_STANDARD_MAPS_WEIGHT},
        {Groups::SEASONS_STANDARD_MAPS, SEASONS_STANDARD_MAPS_WEIGHT},
        {Groups::HEAT_STANDARD_MAPS, HEAT_STANDARD_MAPS_WEIGHT},
        {Groups::COLD_STANDARD_MAPS, COLD_STANDARD_MAPS_WEIGHT},
        {Groups::PASTEL_STANDARD_MAPS, PASTEL_STANDARD_MAPS_WEIGHT},
        {Groups::WES_ANDERSON_MAPS, WES_ANDERSON_MAPS_WEIGHT},
        }
  };
}

auto VisualFxWeightedColorMaps::GetShapesLowGroups() const noexcept -> WeightedGroups
{
  static constexpr auto ALL_MAPS_UNWEIGHTED_WEIGHT              = 05.0F;
  static constexpr auto ALL_STANDARD_MAPS_WEIGHT                = 05.0F;
  static constexpr auto ALL_SLIM_MAPS_WEIGHT                    = 05.0F;
  static constexpr auto MOSTLY_SEQUENTIAL_STANDARD_MAPS_WEIGHT  = 05.0F;
  static constexpr auto MOSTLY_SEQUENTIAL_SLIM_MAPS_WEIGHT      = 05.0F;
  static constexpr auto SLIGHTLY_DIVERGING_STANDARD_MAPS_WEIGHT = 05.0F;
  static constexpr auto SLIGHTLY_DIVERGING_SLIM_MAPS_WEIGHT     = 20.0F;
  static constexpr auto DIVERGING_BLACK_STANDARD_MAPS_WEIGHT    = 35.0F;
  static constexpr auto RED_STANDARD_MAPS_WEIGHT                = 35.0F;
  static constexpr auto GREEN_STANDARD_MAPS_WEIGHT              = 40.0F;
  static constexpr auto BLUE_STANDARD_MAPS_WEIGHT               = 40.0F;
  static constexpr auto YELLOW_STANDARD_MAPS_WEIGHT             = 40.0F;
  static constexpr auto ORANGE_STANDARD_MAPS_WEIGHT             = 40.0F;
  static constexpr auto PURPLE_STANDARD_MAPS_WEIGHT             = 90.0F;
  static constexpr auto CITIES_STANDARD_MAPS_WEIGHT             = 90.0F;
  static constexpr auto SEASONS_STANDARD_MAPS_WEIGHT            = 90.0F;
  static constexpr auto HEAT_STANDARD_MAPS_WEIGHT               = 90.0F;
  static constexpr auto COLD_STANDARD_MAPS_WEIGHT               = 90.0F;
  static constexpr auto PASTEL_STANDARD_MAPS_WEIGHT             = 90.0F;
  static constexpr auto WES_ANDERSON_MAPS_WEIGHT                = 90.0F;

  return {
      m_goomRand,
      {
        {Groups::ALL_MAPS_UNWEIGHTED, ALL_MAPS_UNWEIGHTED_WEIGHT},
        {Groups::ALL_STANDARD_MAPS, ALL_STANDARD_MAPS_WEIGHT},
        {Groups::ALL_SLIM_MAPS, ALL_SLIM_MAPS_WEIGHT},
        {Groups::MOSTLY_SEQUENTIAL_STANDARD_MAPS, MOSTLY_SEQUENTIAL_STANDARD_MAPS_WEIGHT},
        {Groups::MOSTLY_SEQUENTIAL_SLIM_MAPS, MOSTLY_SEQUENTIAL_SLIM_MAPS_WEIGHT},
        {Groups::SLIGHTLY_DIVERGING_STANDARD_MAPS, SLIGHTLY_DIVERGING_STANDARD_MAPS_WEIGHT},
        {Groups::SLIGHTLY_DIVERGING_SLIM_MAPS, SLIGHTLY_DIVERGING_SLIM_MAPS_WEIGHT},
        {Groups::DIVERGING_BLACK_STANDARD_MAPS, DIVERGING_BLACK_STANDARD_MAPS_WEIGHT},
        {Groups::RED_STANDARD_MAPS, RED_STANDARD_MAPS_WEIGHT},
        {Groups::GREEN_STANDARD_MAPS, GREEN_STANDARD_MAPS_WEIGHT},
        {Groups::BLUE_STANDARD_MAPS, BLUE_STANDARD_MAPS_WEIGHT},
        {Groups::YELLOW_STANDARD_MAPS, YELLOW_STANDARD_MAPS_WEIGHT},
        {Groups::ORANGE_STANDARD_MAPS, ORANGE_STANDARD_MAPS_WEIGHT},
        {Groups::PURPLE_STANDARD_MAPS, PURPLE_STANDARD_MAPS_WEIGHT},
        {Groups::CITIES_STANDARD_MAPS, CITIES_STANDARD_MAPS_WEIGHT},
        {Groups::SEASONS_STANDARD_MAPS, SEASONS_STANDARD_MAPS_WEIGHT},
        {Groups::HEAT_STANDARD_MAPS, HEAT_STANDARD_MAPS_WEIGHT},
        {Groups::COLD_STANDARD_MAPS, COLD_STANDARD_MAPS_WEIGHT},
        {Groups::PASTEL_STANDARD_MAPS, PASTEL_STANDARD_MAPS_WEIGHT},
        {Groups::WES_ANDERSON_MAPS, WES_ANDERSON_MAPS_WEIGHT},
        }
  };
}

auto VisualFxWeightedColorMaps::GetShapesInnerGroups() const noexcept -> WeightedGroups
{
  static constexpr auto ALL_MAPS_UNWEIGHTED_WEIGHT              = 05.0F;
  static constexpr auto ALL_STANDARD_MAPS_WEIGHT                = 05.0F;
  static constexpr auto ALL_SLIM_MAPS_WEIGHT                    = 05.0F;
  static constexpr auto MOSTLY_SEQUENTIAL_STANDARD_MAPS_WEIGHT  = 05.0F;
  static constexpr auto MOSTLY_SEQUENTIAL_SLIM_MAPS_WEIGHT      = 05.0F;
  static constexpr auto SLIGHTLY_DIVERGING_STANDARD_MAPS_WEIGHT = 05.0F;
  static constexpr auto SLIGHTLY_DIVERGING_SLIM_MAPS_WEIGHT     = 20.0F;
  static constexpr auto DIVERGING_BLACK_STANDARD_MAPS_WEIGHT    = 35.0F;
  static constexpr auto RED_STANDARD_MAPS_WEIGHT                = 35.0F;
  static constexpr auto GREEN_STANDARD_MAPS_WEIGHT              = 40.0F;
  static constexpr auto BLUE_STANDARD_MAPS_WEIGHT               = 40.0F;
  static constexpr auto YELLOW_STANDARD_MAPS_WEIGHT             = 40.0F;
  static constexpr auto ORANGE_STANDARD_MAPS_WEIGHT             = 40.0F;
  static constexpr auto PURPLE_STANDARD_MAPS_WEIGHT             = 90.0F;
  static constexpr auto CITIES_STANDARD_MAPS_WEIGHT             = 90.0F;
  static constexpr auto SEASONS_STANDARD_MAPS_WEIGHT            = 90.0F;
  static constexpr auto HEAT_STANDARD_MAPS_WEIGHT               = 90.0F;
  static constexpr auto COLD_STANDARD_MAPS_WEIGHT               = 90.0F;
  static constexpr auto PASTEL_STANDARD_MAPS_WEIGHT             = 90.0F;
  static constexpr auto WES_ANDERSON_MAPS_WEIGHT                = 90.0F;

  return {
      m_goomRand,
      {
        {Groups::ALL_MAPS_UNWEIGHTED, ALL_MAPS_UNWEIGHTED_WEIGHT},
        {Groups::ALL_STANDARD_MAPS, ALL_STANDARD_MAPS_WEIGHT},
        {Groups::ALL_SLIM_MAPS, ALL_SLIM_MAPS_WEIGHT},
        {Groups::MOSTLY_SEQUENTIAL_STANDARD_MAPS, MOSTLY_SEQUENTIAL_STANDARD_MAPS_WEIGHT},
        {Groups::MOSTLY_SEQUENTIAL_SLIM_MAPS, MOSTLY_SEQUENTIAL_SLIM_MAPS_WEIGHT},
        {Groups::SLIGHTLY_DIVERGING_STANDARD_MAPS, SLIGHTLY_DIVERGING_STANDARD_MAPS_WEIGHT},
        {Groups::SLIGHTLY_DIVERGING_SLIM_MAPS, SLIGHTLY_DIVERGING_SLIM_MAPS_WEIGHT},
        {Groups::DIVERGING_BLACK_STANDARD_MAPS, DIVERGING_BLACK_STANDARD_MAPS_WEIGHT},
        {Groups::RED_STANDARD_MAPS, RED_STANDARD_MAPS_WEIGHT},
        {Groups::GREEN_STANDARD_MAPS, GREEN_STANDARD_MAPS_WEIGHT},
        {Groups::BLUE_STANDARD_MAPS, BLUE_STANDARD_MAPS_WEIGHT},
        {Groups::YELLOW_STANDARD_MAPS, YELLOW_STANDARD_MAPS_WEIGHT},
        {Groups::ORANGE_STANDARD_MAPS, ORANGE_STANDARD_MAPS_WEIGHT},
        {Groups::PURPLE_STANDARD_MAPS, PURPLE_STANDARD_MAPS_WEIGHT},
        {Groups::CITIES_STANDARD_MAPS, CITIES_STANDARD_MAPS_WEIGHT},
        {Groups::SEASONS_STANDARD_MAPS, SEASONS_STANDARD_MAPS_WEIGHT},
        {Groups::HEAT_STANDARD_MAPS, HEAT_STANDARD_MAPS_WEIGHT},
        {Groups::COLD_STANDARD_MAPS, COLD_STANDARD_MAPS_WEIGHT},
        {Groups::PASTEL_STANDARD_MAPS, PASTEL_STANDARD_MAPS_WEIGHT},
        {Groups::WES_ANDERSON_MAPS, WES_ANDERSON_MAPS_WEIGHT},
        }
  };
}

auto VisualFxWeightedColorMaps::GetStarsMainFireworksGroups() const noexcept -> WeightedGroups
{
  static constexpr auto ALL_MAPS_UNWEIGHTED_WEIGHT              = 05.0F;
  static constexpr auto ALL_STANDARD_MAPS_WEIGHT                = 05.0F;
  static constexpr auto ALL_SLIM_MAPS_WEIGHT                    = 05.0F;
  static constexpr auto MOSTLY_SEQUENTIAL_STANDARD_MAPS_WEIGHT  = 05.0F;
  static constexpr auto MOSTLY_SEQUENTIAL_SLIM_MAPS_WEIGHT      = 05.0F;
  static constexpr auto SLIGHTLY_DIVERGING_STANDARD_MAPS_WEIGHT = 05.0F;
  static constexpr auto SLIGHTLY_DIVERGING_SLIM_MAPS_WEIGHT     = 20.0F;
  static constexpr auto DIVERGING_BLACK_STANDARD_MAPS_WEIGHT    = 35.0F;
  static constexpr auto RED_STANDARD_MAPS_WEIGHT                = 00.0F;
  static constexpr auto GREEN_STANDARD_MAPS_WEIGHT              = 00.0F;
  static constexpr auto BLUE_STANDARD_MAPS_WEIGHT               = 00.0F;
  static constexpr auto YELLOW_STANDARD_MAPS_WEIGHT             = 00.0F;
  static constexpr auto ORANGE_STANDARD_MAPS_WEIGHT             = 00.0F;
  static constexpr auto PURPLE_STANDARD_MAPS_WEIGHT             = 00.0F;
  static constexpr auto CITIES_STANDARD_MAPS_WEIGHT             = 90.0F;
  static constexpr auto SEASONS_STANDARD_MAPS_WEIGHT            = 90.0F;
  static constexpr auto HEAT_STANDARD_MAPS_WEIGHT               = 90.0F;
  static constexpr auto COLD_STANDARD_MAPS_WEIGHT               = 90.0F;
  static constexpr auto PASTEL_STANDARD_MAPS_WEIGHT             = 90.0F;
  static constexpr auto WES_ANDERSON_MAPS_WEIGHT                = 90.0F;

  return {
      m_goomRand,
      {
        {Groups::ALL_MAPS_UNWEIGHTED, ALL_MAPS_UNWEIGHTED_WEIGHT},
        {Groups::ALL_STANDARD_MAPS, ALL_STANDARD_MAPS_WEIGHT},
        {Groups::ALL_SLIM_MAPS, ALL_SLIM_MAPS_WEIGHT},
        {Groups::MOSTLY_SEQUENTIAL_STANDARD_MAPS, MOSTLY_SEQUENTIAL_STANDARD_MAPS_WEIGHT},
        {Groups::MOSTLY_SEQUENTIAL_SLIM_MAPS, MOSTLY_SEQUENTIAL_SLIM_MAPS_WEIGHT},
        {Groups::SLIGHTLY_DIVERGING_STANDARD_MAPS, SLIGHTLY_DIVERGING_STANDARD_MAPS_WEIGHT},
        {Groups::SLIGHTLY_DIVERGING_SLIM_MAPS, SLIGHTLY_DIVERGING_SLIM_MAPS_WEIGHT},
        {Groups::DIVERGING_BLACK_STANDARD_MAPS, DIVERGING_BLACK_STANDARD_MAPS_WEIGHT},
        {Groups::RED_STANDARD_MAPS, RED_STANDARD_MAPS_WEIGHT},
        {Groups::GREEN_STANDARD_MAPS, GREEN_STANDARD_MAPS_WEIGHT},
        {Groups::BLUE_STANDARD_MAPS, BLUE_STANDARD_MAPS_WEIGHT},
        {Groups::YELLOW_STANDARD_MAPS, YELLOW_STANDARD_MAPS_WEIGHT},
        {Groups::ORANGE_STANDARD_MAPS, ORANGE_STANDARD_MAPS_WEIGHT},
        {Groups::PURPLE_STANDARD_MAPS, PURPLE_STANDARD_MAPS_WEIGHT},
        {Groups::CITIES_STANDARD_MAPS, CITIES_STANDARD_MAPS_WEIGHT},
        {Groups::SEASONS_STANDARD_MAPS, SEASONS_STANDARD_MAPS_WEIGHT},
        {Groups::HEAT_STANDARD_MAPS, HEAT_STANDARD_MAPS_WEIGHT},
        {Groups::COLD_STANDARD_MAPS, COLD_STANDARD_MAPS_WEIGHT},
        {Groups::PASTEL_STANDARD_MAPS, PASTEL_STANDARD_MAPS_WEIGHT},
        {Groups::WES_ANDERSON_MAPS, WES_ANDERSON_MAPS_WEIGHT},
        }
  };
}

auto VisualFxWeightedColorMaps::GetStarsLowFireworksGroups() const noexcept -> WeightedGroups
{
  static constexpr auto ALL_MAPS_UNWEIGHTED_WEIGHT              = 05.0F;
  static constexpr auto ALL_STANDARD_MAPS_WEIGHT                = 05.0F;
  static constexpr auto ALL_SLIM_MAPS_WEIGHT                    = 05.0F;
  static constexpr auto MOSTLY_SEQUENTIAL_STANDARD_MAPS_WEIGHT  = 05.0F;
  static constexpr auto MOSTLY_SEQUENTIAL_SLIM_MAPS_WEIGHT      = 05.0F;
  static constexpr auto SLIGHTLY_DIVERGING_STANDARD_MAPS_WEIGHT = 05.0F;
  static constexpr auto SLIGHTLY_DIVERGING_SLIM_MAPS_WEIGHT     = 20.0F;
  static constexpr auto DIVERGING_BLACK_STANDARD_MAPS_WEIGHT    = 35.0F;
  static constexpr auto RED_STANDARD_MAPS_WEIGHT                = 00.0F;
  static constexpr auto GREEN_STANDARD_MAPS_WEIGHT              = 00.0F;
  static constexpr auto BLUE_STANDARD_MAPS_WEIGHT               = 00.0F;
  static constexpr auto YELLOW_STANDARD_MAPS_WEIGHT             = 00.0F;
  static constexpr auto ORANGE_STANDARD_MAPS_WEIGHT             = 00.0F;
  static constexpr auto PURPLE_STANDARD_MAPS_WEIGHT             = 00.0F;
  static constexpr auto CITIES_STANDARD_MAPS_WEIGHT             = 90.0F;
  static constexpr auto SEASONS_STANDARD_MAPS_WEIGHT            = 90.0F;
  static constexpr auto HEAT_STANDARD_MAPS_WEIGHT               = 90.0F;
  static constexpr auto COLD_STANDARD_MAPS_WEIGHT               = 90.0F;
  static constexpr auto PASTEL_STANDARD_MAPS_WEIGHT             = 90.0F;
  static constexpr auto WES_ANDERSON_MAPS_WEIGHT                = 90.0F;

  return {
      m_goomRand,
      {
        {Groups::ALL_MAPS_UNWEIGHTED, ALL_MAPS_UNWEIGHTED_WEIGHT},
        {Groups::ALL_STANDARD_MAPS, ALL_STANDARD_MAPS_WEIGHT},
        {Groups::ALL_SLIM_MAPS, ALL_SLIM_MAPS_WEIGHT},
        {Groups::MOSTLY_SEQUENTIAL_STANDARD_MAPS, MOSTLY_SEQUENTIAL_STANDARD_MAPS_WEIGHT},
        {Groups::MOSTLY_SEQUENTIAL_SLIM_MAPS, MOSTLY_SEQUENTIAL_SLIM_MAPS_WEIGHT},
        {Groups::SLIGHTLY_DIVERGING_STANDARD_MAPS, SLIGHTLY_DIVERGING_STANDARD_MAPS_WEIGHT},
        {Groups::SLIGHTLY_DIVERGING_SLIM_MAPS, SLIGHTLY_DIVERGING_SLIM_MAPS_WEIGHT},
        {Groups::DIVERGING_BLACK_STANDARD_MAPS, DIVERGING_BLACK_STANDARD_MAPS_WEIGHT},
        {Groups::RED_STANDARD_MAPS, RED_STANDARD_MAPS_WEIGHT},
        {Groups::GREEN_STANDARD_MAPS, GREEN_STANDARD_MAPS_WEIGHT},
        {Groups::BLUE_STANDARD_MAPS, BLUE_STANDARD_MAPS_WEIGHT},
        {Groups::YELLOW_STANDARD_MAPS, YELLOW_STANDARD_MAPS_WEIGHT},
        {Groups::ORANGE_STANDARD_MAPS, ORANGE_STANDARD_MAPS_WEIGHT},
        {Groups::PURPLE_STANDARD_MAPS, PURPLE_STANDARD_MAPS_WEIGHT},
        {Groups::CITIES_STANDARD_MAPS, CITIES_STANDARD_MAPS_WEIGHT},
        {Groups::SEASONS_STANDARD_MAPS, SEASONS_STANDARD_MAPS_WEIGHT},
        {Groups::HEAT_STANDARD_MAPS, HEAT_STANDARD_MAPS_WEIGHT},
        {Groups::COLD_STANDARD_MAPS, COLD_STANDARD_MAPS_WEIGHT},
        {Groups::PASTEL_STANDARD_MAPS, PASTEL_STANDARD_MAPS_WEIGHT},
        {Groups::WES_ANDERSON_MAPS, WES_ANDERSON_MAPS_WEIGHT},
        }
  };
}

auto VisualFxWeightedColorMaps::GetStarsMainRainGroups() const noexcept -> WeightedGroups
{
  static constexpr auto ALL_MAPS_UNWEIGHTED_WEIGHT              = 05.0F;
  static constexpr auto ALL_STANDARD_MAPS_WEIGHT                = 05.0F;
  static constexpr auto ALL_SLIM_MAPS_WEIGHT                    = 05.0F;
  static constexpr auto MOSTLY_SEQUENTIAL_STANDARD_MAPS_WEIGHT  = 05.0F;
  static constexpr auto MOSTLY_SEQUENTIAL_SLIM_MAPS_WEIGHT      = 05.0F;
  static constexpr auto SLIGHTLY_DIVERGING_STANDARD_MAPS_WEIGHT = 05.0F;
  static constexpr auto SLIGHTLY_DIVERGING_SLIM_MAPS_WEIGHT     = 20.0F;
  static constexpr auto DIVERGING_BLACK_STANDARD_MAPS_WEIGHT    = 35.0F;
  static constexpr auto RED_STANDARD_MAPS_WEIGHT                = 00.0F;
  static constexpr auto GREEN_STANDARD_MAPS_WEIGHT              = 00.0F;
  static constexpr auto BLUE_STANDARD_MAPS_WEIGHT               = 00.0F;
  static constexpr auto YELLOW_STANDARD_MAPS_WEIGHT             = 00.0F;
  static constexpr auto ORANGE_STANDARD_MAPS_WEIGHT             = 00.0F;
  static constexpr auto PURPLE_STANDARD_MAPS_WEIGHT             = 00.0F;
  static constexpr auto CITIES_STANDARD_MAPS_WEIGHT             = 90.0F;
  static constexpr auto SEASONS_STANDARD_MAPS_WEIGHT            = 90.0F;
  static constexpr auto HEAT_STANDARD_MAPS_WEIGHT               = 90.0F;
  static constexpr auto COLD_STANDARD_MAPS_WEIGHT               = 90.0F;
  static constexpr auto PASTEL_STANDARD_MAPS_WEIGHT             = 90.0F;
  static constexpr auto WES_ANDERSON_MAPS_WEIGHT                = 90.0F;

  return {
      m_goomRand,
      {
        {Groups::ALL_MAPS_UNWEIGHTED, ALL_MAPS_UNWEIGHTED_WEIGHT},
        {Groups::ALL_STANDARD_MAPS, ALL_STANDARD_MAPS_WEIGHT},
        {Groups::ALL_SLIM_MAPS, ALL_SLIM_MAPS_WEIGHT},
        {Groups::MOSTLY_SEQUENTIAL_STANDARD_MAPS, MOSTLY_SEQUENTIAL_STANDARD_MAPS_WEIGHT},
        {Groups::MOSTLY_SEQUENTIAL_SLIM_MAPS, MOSTLY_SEQUENTIAL_SLIM_MAPS_WEIGHT},
        {Groups::SLIGHTLY_DIVERGING_STANDARD_MAPS, SLIGHTLY_DIVERGING_STANDARD_MAPS_WEIGHT},
        {Groups::SLIGHTLY_DIVERGING_SLIM_MAPS, SLIGHTLY_DIVERGING_SLIM_MAPS_WEIGHT},
        {Groups::DIVERGING_BLACK_STANDARD_MAPS, DIVERGING_BLACK_STANDARD_MAPS_WEIGHT},
        {Groups::RED_STANDARD_MAPS, RED_STANDARD_MAPS_WEIGHT},
        {Groups::GREEN_STANDARD_MAPS, GREEN_STANDARD_MAPS_WEIGHT},
        {Groups::BLUE_STANDARD_MAPS, BLUE_STANDARD_MAPS_WEIGHT},
        {Groups::YELLOW_STANDARD_MAPS, YELLOW_STANDARD_MAPS_WEIGHT},
        {Groups::ORANGE_STANDARD_MAPS, ORANGE_STANDARD_MAPS_WEIGHT},
        {Groups::PURPLE_STANDARD_MAPS, PURPLE_STANDARD_MAPS_WEIGHT},
        {Groups::CITIES_STANDARD_MAPS, CITIES_STANDARD_MAPS_WEIGHT},
        {Groups::SEASONS_STANDARD_MAPS, SEASONS_STANDARD_MAPS_WEIGHT},
        {Groups::HEAT_STANDARD_MAPS, HEAT_STANDARD_MAPS_WEIGHT},
        {Groups::COLD_STANDARD_MAPS, COLD_STANDARD_MAPS_WEIGHT},
        {Groups::PASTEL_STANDARD_MAPS, PASTEL_STANDARD_MAPS_WEIGHT},
        {Groups::WES_ANDERSON_MAPS, WES_ANDERSON_MAPS_WEIGHT},
        }
  };
}

auto VisualFxWeightedColorMaps::GetStarsLowRainGroups() const noexcept -> WeightedGroups
{
  static constexpr auto ALL_MAPS_UNWEIGHTED_WEIGHT              = 05.0F;
  static constexpr auto ALL_STANDARD_MAPS_WEIGHT                = 05.0F;
  static constexpr auto ALL_SLIM_MAPS_WEIGHT                    = 05.0F;
  static constexpr auto MOSTLY_SEQUENTIAL_STANDARD_MAPS_WEIGHT  = 05.0F;
  static constexpr auto MOSTLY_SEQUENTIAL_SLIM_MAPS_WEIGHT      = 05.0F;
  static constexpr auto SLIGHTLY_DIVERGING_STANDARD_MAPS_WEIGHT = 05.0F;
  static constexpr auto SLIGHTLY_DIVERGING_SLIM_MAPS_WEIGHT     = 20.0F;
  static constexpr auto DIVERGING_BLACK_STANDARD_MAPS_WEIGHT    = 35.0F;
  static constexpr auto RED_STANDARD_MAPS_WEIGHT                = 00.0F;
  static constexpr auto GREEN_STANDARD_MAPS_WEIGHT              = 00.0F;
  static constexpr auto BLUE_STANDARD_MAPS_WEIGHT               = 00.0F;
  static constexpr auto YELLOW_STANDARD_MAPS_WEIGHT             = 00.0F;
  static constexpr auto ORANGE_STANDARD_MAPS_WEIGHT             = 00.0F;
  static constexpr auto PURPLE_STANDARD_MAPS_WEIGHT             = 00.0F;
  static constexpr auto CITIES_STANDARD_MAPS_WEIGHT             = 90.0F;
  static constexpr auto SEASONS_STANDARD_MAPS_WEIGHT            = 90.0F;
  static constexpr auto HEAT_STANDARD_MAPS_WEIGHT               = 90.0F;
  static constexpr auto COLD_STANDARD_MAPS_WEIGHT               = 90.0F;
  static constexpr auto PASTEL_STANDARD_MAPS_WEIGHT             = 90.0F;
  static constexpr auto WES_ANDERSON_MAPS_WEIGHT                = 90.0F;

  return {
      m_goomRand,
      {
        {Groups::ALL_MAPS_UNWEIGHTED, ALL_MAPS_UNWEIGHTED_WEIGHT},
        {Groups::ALL_STANDARD_MAPS, ALL_STANDARD_MAPS_WEIGHT},
        {Groups::ALL_SLIM_MAPS, ALL_SLIM_MAPS_WEIGHT},
        {Groups::MOSTLY_SEQUENTIAL_STANDARD_MAPS, MOSTLY_SEQUENTIAL_STANDARD_MAPS_WEIGHT},
        {Groups::MOSTLY_SEQUENTIAL_SLIM_MAPS, MOSTLY_SEQUENTIAL_SLIM_MAPS_WEIGHT},
        {Groups::SLIGHTLY_DIVERGING_STANDARD_MAPS, SLIGHTLY_DIVERGING_STANDARD_MAPS_WEIGHT},
        {Groups::SLIGHTLY_DIVERGING_SLIM_MAPS, SLIGHTLY_DIVERGING_SLIM_MAPS_WEIGHT},
        {Groups::DIVERGING_BLACK_STANDARD_MAPS, DIVERGING_BLACK_STANDARD_MAPS_WEIGHT},
        {Groups::RED_STANDARD_MAPS, RED_STANDARD_MAPS_WEIGHT},
        {Groups::GREEN_STANDARD_MAPS, GREEN_STANDARD_MAPS_WEIGHT},
        {Groups::BLUE_STANDARD_MAPS, BLUE_STANDARD_MAPS_WEIGHT},
        {Groups::YELLOW_STANDARD_MAPS, YELLOW_STANDARD_MAPS_WEIGHT},
        {Groups::ORANGE_STANDARD_MAPS, ORANGE_STANDARD_MAPS_WEIGHT},
        {Groups::PURPLE_STANDARD_MAPS, PURPLE_STANDARD_MAPS_WEIGHT},
        {Groups::CITIES_STANDARD_MAPS, CITIES_STANDARD_MAPS_WEIGHT},
        {Groups::SEASONS_STANDARD_MAPS, SEASONS_STANDARD_MAPS_WEIGHT},
        {Groups::HEAT_STANDARD_MAPS, HEAT_STANDARD_MAPS_WEIGHT},
        {Groups::COLD_STANDARD_MAPS, COLD_STANDARD_MAPS_WEIGHT},
        {Groups::PASTEL_STANDARD_MAPS, PASTEL_STANDARD_MAPS_WEIGHT},
        {Groups::WES_ANDERSON_MAPS, WES_ANDERSON_MAPS_WEIGHT},
        }
  };
}

auto VisualFxWeightedColorMaps::GetStarsMainFountainGroups() const noexcept -> WeightedGroups
{
  static constexpr auto ALL_MAPS_UNWEIGHTED_WEIGHT              = 05.0F;
  static constexpr auto ALL_STANDARD_MAPS_WEIGHT                = 05.0F;
  static constexpr auto ALL_SLIM_MAPS_WEIGHT                    = 05.0F;
  static constexpr auto MOSTLY_SEQUENTIAL_STANDARD_MAPS_WEIGHT  = 05.0F;
  static constexpr auto MOSTLY_SEQUENTIAL_SLIM_MAPS_WEIGHT      = 05.0F;
  static constexpr auto SLIGHTLY_DIVERGING_STANDARD_MAPS_WEIGHT = 05.0F;
  static constexpr auto SLIGHTLY_DIVERGING_SLIM_MAPS_WEIGHT     = 20.0F;
  static constexpr auto DIVERGING_BLACK_STANDARD_MAPS_WEIGHT    = 35.0F;
  static constexpr auto RED_STANDARD_MAPS_WEIGHT                = 00.0F;
  static constexpr auto GREEN_STANDARD_MAPS_WEIGHT              = 00.0F;
  static constexpr auto BLUE_STANDARD_MAPS_WEIGHT               = 00.0F;
  static constexpr auto YELLOW_STANDARD_MAPS_WEIGHT             = 00.0F;
  static constexpr auto ORANGE_STANDARD_MAPS_WEIGHT             = 00.0F;
  static constexpr auto PURPLE_STANDARD_MAPS_WEIGHT             = 00.0F;
  static constexpr auto CITIES_STANDARD_MAPS_WEIGHT             = 90.0F;
  static constexpr auto SEASONS_STANDARD_MAPS_WEIGHT            = 90.0F;
  static constexpr auto HEAT_STANDARD_MAPS_WEIGHT               = 90.0F;
  static constexpr auto COLD_STANDARD_MAPS_WEIGHT               = 90.0F;
  static constexpr auto PASTEL_STANDARD_MAPS_WEIGHT             = 90.0F;
  static constexpr auto WES_ANDERSON_MAPS_WEIGHT                = 90.0F;

  return {
      m_goomRand,
      {
        {Groups::ALL_MAPS_UNWEIGHTED, ALL_MAPS_UNWEIGHTED_WEIGHT},
        {Groups::ALL_STANDARD_MAPS, ALL_STANDARD_MAPS_WEIGHT},
        {Groups::ALL_SLIM_MAPS, ALL_SLIM_MAPS_WEIGHT},
        {Groups::MOSTLY_SEQUENTIAL_STANDARD_MAPS, MOSTLY_SEQUENTIAL_STANDARD_MAPS_WEIGHT},
        {Groups::MOSTLY_SEQUENTIAL_SLIM_MAPS, MOSTLY_SEQUENTIAL_SLIM_MAPS_WEIGHT},
        {Groups::SLIGHTLY_DIVERGING_STANDARD_MAPS, SLIGHTLY_DIVERGING_STANDARD_MAPS_WEIGHT},
        {Groups::SLIGHTLY_DIVERGING_SLIM_MAPS, SLIGHTLY_DIVERGING_SLIM_MAPS_WEIGHT},
        {Groups::DIVERGING_BLACK_STANDARD_MAPS, DIVERGING_BLACK_STANDARD_MAPS_WEIGHT},
        {Groups::RED_STANDARD_MAPS, RED_STANDARD_MAPS_WEIGHT},
        {Groups::GREEN_STANDARD_MAPS, GREEN_STANDARD_MAPS_WEIGHT},
        {Groups::BLUE_STANDARD_MAPS, BLUE_STANDARD_MAPS_WEIGHT},
        {Groups::YELLOW_STANDARD_MAPS, YELLOW_STANDARD_MAPS_WEIGHT},
        {Groups::ORANGE_STANDARD_MAPS, ORANGE_STANDARD_MAPS_WEIGHT},
        {Groups::PURPLE_STANDARD_MAPS, PURPLE_STANDARD_MAPS_WEIGHT},
        {Groups::CITIES_STANDARD_MAPS, CITIES_STANDARD_MAPS_WEIGHT},
        {Groups::SEASONS_STANDARD_MAPS, SEASONS_STANDARD_MAPS_WEIGHT},
        {Groups::HEAT_STANDARD_MAPS, HEAT_STANDARD_MAPS_WEIGHT},
        {Groups::COLD_STANDARD_MAPS, COLD_STANDARD_MAPS_WEIGHT},
        {Groups::PASTEL_STANDARD_MAPS, PASTEL_STANDARD_MAPS_WEIGHT},
        {Groups::WES_ANDERSON_MAPS, WES_ANDERSON_MAPS_WEIGHT},
        }
  };
}

auto VisualFxWeightedColorMaps::GetStarsLowFountainGroups() const noexcept -> WeightedGroups
{
  static constexpr auto ALL_MAPS_UNWEIGHTED_WEIGHT              = 05.0F;
  static constexpr auto ALL_STANDARD_MAPS_WEIGHT                = 05.0F;
  static constexpr auto ALL_SLIM_MAPS_WEIGHT                    = 05.0F;
  static constexpr auto MOSTLY_SEQUENTIAL_STANDARD_MAPS_WEIGHT  = 05.0F;
  static constexpr auto MOSTLY_SEQUENTIAL_SLIM_MAPS_WEIGHT      = 05.0F;
  static constexpr auto SLIGHTLY_DIVERGING_STANDARD_MAPS_WEIGHT = 05.0F;
  static constexpr auto SLIGHTLY_DIVERGING_SLIM_MAPS_WEIGHT     = 20.0F;
  static constexpr auto DIVERGING_BLACK_STANDARD_MAPS_WEIGHT    = 35.0F;
  static constexpr auto RED_STANDARD_MAPS_WEIGHT                = 00.0F;
  static constexpr auto GREEN_STANDARD_MAPS_WEIGHT              = 00.0F;
  static constexpr auto BLUE_STANDARD_MAPS_WEIGHT               = 00.0F;
  static constexpr auto YELLOW_STANDARD_MAPS_WEIGHT             = 00.0F;
  static constexpr auto ORANGE_STANDARD_MAPS_WEIGHT             = 00.0F;
  static constexpr auto PURPLE_STANDARD_MAPS_WEIGHT             = 00.0F;
  static constexpr auto CITIES_STANDARD_MAPS_WEIGHT             = 90.0F;
  static constexpr auto SEASONS_STANDARD_MAPS_WEIGHT            = 90.0F;
  static constexpr auto HEAT_STANDARD_MAPS_WEIGHT               = 90.0F;
  static constexpr auto COLD_STANDARD_MAPS_WEIGHT               = 90.0F;
  static constexpr auto PASTEL_STANDARD_MAPS_WEIGHT             = 90.0F;
  static constexpr auto WES_ANDERSON_MAPS_WEIGHT                = 90.0F;

  return {
      m_goomRand,
      {
        {Groups::ALL_MAPS_UNWEIGHTED, ALL_MAPS_UNWEIGHTED_WEIGHT},
        {Groups::ALL_STANDARD_MAPS, ALL_STANDARD_MAPS_WEIGHT},
        {Groups::ALL_SLIM_MAPS, ALL_SLIM_MAPS_WEIGHT},
        {Groups::MOSTLY_SEQUENTIAL_STANDARD_MAPS, MOSTLY_SEQUENTIAL_STANDARD_MAPS_WEIGHT},
        {Groups::MOSTLY_SEQUENTIAL_SLIM_MAPS, MOSTLY_SEQUENTIAL_SLIM_MAPS_WEIGHT},
        {Groups::SLIGHTLY_DIVERGING_STANDARD_MAPS, SLIGHTLY_DIVERGING_STANDARD_MAPS_WEIGHT},
        {Groups::SLIGHTLY_DIVERGING_SLIM_MAPS, SLIGHTLY_DIVERGING_SLIM_MAPS_WEIGHT},
        {Groups::DIVERGING_BLACK_STANDARD_MAPS, DIVERGING_BLACK_STANDARD_MAPS_WEIGHT},
        {Groups::RED_STANDARD_MAPS, RED_STANDARD_MAPS_WEIGHT},
        {Groups::GREEN_STANDARD_MAPS, GREEN_STANDARD_MAPS_WEIGHT},
        {Groups::BLUE_STANDARD_MAPS, BLUE_STANDARD_MAPS_WEIGHT},
        {Groups::YELLOW_STANDARD_MAPS, YELLOW_STANDARD_MAPS_WEIGHT},
        {Groups::ORANGE_STANDARD_MAPS, ORANGE_STANDARD_MAPS_WEIGHT},
        {Groups::PURPLE_STANDARD_MAPS, PURPLE_STANDARD_MAPS_WEIGHT},
        {Groups::CITIES_STANDARD_MAPS, CITIES_STANDARD_MAPS_WEIGHT},
        {Groups::SEASONS_STANDARD_MAPS, SEASONS_STANDARD_MAPS_WEIGHT},
        {Groups::HEAT_STANDARD_MAPS, HEAT_STANDARD_MAPS_WEIGHT},
        {Groups::COLD_STANDARD_MAPS, COLD_STANDARD_MAPS_WEIGHT},
        {Groups::PASTEL_STANDARD_MAPS, PASTEL_STANDARD_MAPS_WEIGHT},
        {Groups::WES_ANDERSON_MAPS, WES_ANDERSON_MAPS_WEIGHT},
        }
  };
}

auto VisualFxWeightedColorMaps::GetTentaclesDominantMainGroups() const noexcept -> WeightedGroups
{
  static constexpr auto ALL_MAPS_UNWEIGHTED_WEIGHT              = 05.0F;
  static constexpr auto ALL_STANDARD_MAPS_WEIGHT                = 05.0F;
  static constexpr auto ALL_SLIM_MAPS_WEIGHT                    = 05.0F;
  static constexpr auto MOSTLY_SEQUENTIAL_STANDARD_MAPS_WEIGHT  = 05.0F;
  static constexpr auto MOSTLY_SEQUENTIAL_SLIM_MAPS_WEIGHT      = 05.0F;
  static constexpr auto SLIGHTLY_DIVERGING_STANDARD_MAPS_WEIGHT = 05.0F;
  static constexpr auto SLIGHTLY_DIVERGING_SLIM_MAPS_WEIGHT     = 20.0F;
  static constexpr auto DIVERGING_BLACK_STANDARD_MAPS_WEIGHT    = 35.0F;
  static constexpr auto RED_STANDARD_MAPS_WEIGHT                = 35.0F;
  static constexpr auto GREEN_STANDARD_MAPS_WEIGHT              = 40.0F;
  static constexpr auto BLUE_STANDARD_MAPS_WEIGHT               = 40.0F;
  static constexpr auto YELLOW_STANDARD_MAPS_WEIGHT             = 40.0F;
  static constexpr auto ORANGE_STANDARD_MAPS_WEIGHT             = 40.0F;
  static constexpr auto PURPLE_STANDARD_MAPS_WEIGHT             = 90.0F;
  static constexpr auto CITIES_STANDARD_MAPS_WEIGHT             = 90.0F;
  static constexpr auto SEASONS_STANDARD_MAPS_WEIGHT            = 90.0F;
  static constexpr auto HEAT_STANDARD_MAPS_WEIGHT               = 90.0F;
  static constexpr auto COLD_STANDARD_MAPS_WEIGHT               = 90.0F;
  static constexpr auto PASTEL_STANDARD_MAPS_WEIGHT             = 90.0F;
  static constexpr auto WES_ANDERSON_MAPS_WEIGHT                = 90.0F;

  return {
      m_goomRand,
      {
        {Groups::ALL_MAPS_UNWEIGHTED, ALL_MAPS_UNWEIGHTED_WEIGHT},
        {Groups::ALL_STANDARD_MAPS, ALL_STANDARD_MAPS_WEIGHT},
        {Groups::ALL_SLIM_MAPS, ALL_SLIM_MAPS_WEIGHT},
        {Groups::MOSTLY_SEQUENTIAL_STANDARD_MAPS, MOSTLY_SEQUENTIAL_STANDARD_MAPS_WEIGHT},
        {Groups::MOSTLY_SEQUENTIAL_SLIM_MAPS, MOSTLY_SEQUENTIAL_SLIM_MAPS_WEIGHT},
        {Groups::SLIGHTLY_DIVERGING_STANDARD_MAPS, SLIGHTLY_DIVERGING_STANDARD_MAPS_WEIGHT},
        {Groups::SLIGHTLY_DIVERGING_SLIM_MAPS, SLIGHTLY_DIVERGING_SLIM_MAPS_WEIGHT},
        {Groups::DIVERGING_BLACK_STANDARD_MAPS, DIVERGING_BLACK_STANDARD_MAPS_WEIGHT},
        {Groups::RED_STANDARD_MAPS, RED_STANDARD_MAPS_WEIGHT},
        {Groups::GREEN_STANDARD_MAPS, GREEN_STANDARD_MAPS_WEIGHT},
        {Groups::BLUE_STANDARD_MAPS, BLUE_STANDARD_MAPS_WEIGHT},
        {Groups::YELLOW_STANDARD_MAPS, YELLOW_STANDARD_MAPS_WEIGHT},
        {Groups::ORANGE_STANDARD_MAPS, ORANGE_STANDARD_MAPS_WEIGHT},
        {Groups::PURPLE_STANDARD_MAPS, PURPLE_STANDARD_MAPS_WEIGHT},
        {Groups::CITIES_STANDARD_MAPS, CITIES_STANDARD_MAPS_WEIGHT},
        {Groups::SEASONS_STANDARD_MAPS, SEASONS_STANDARD_MAPS_WEIGHT},
        {Groups::HEAT_STANDARD_MAPS, HEAT_STANDARD_MAPS_WEIGHT},
        {Groups::COLD_STANDARD_MAPS, COLD_STANDARD_MAPS_WEIGHT},
        {Groups::PASTEL_STANDARD_MAPS, PASTEL_STANDARD_MAPS_WEIGHT},
        {Groups::WES_ANDERSON_MAPS, WES_ANDERSON_MAPS_WEIGHT},
        }
  };
}

auto VisualFxWeightedColorMaps::GetTentaclesDominantLowGroups() const noexcept -> WeightedGroups
{
  static constexpr auto ALL_MAPS_UNWEIGHTED_WEIGHT              = 05.0F;
  static constexpr auto ALL_STANDARD_MAPS_WEIGHT                = 05.0F;
  static constexpr auto ALL_SLIM_MAPS_WEIGHT                    = 05.0F;
  static constexpr auto MOSTLY_SEQUENTIAL_STANDARD_MAPS_WEIGHT  = 05.0F;
  static constexpr auto MOSTLY_SEQUENTIAL_SLIM_MAPS_WEIGHT      = 05.0F;
  static constexpr auto SLIGHTLY_DIVERGING_STANDARD_MAPS_WEIGHT = 05.0F;
  static constexpr auto SLIGHTLY_DIVERGING_SLIM_MAPS_WEIGHT     = 20.0F;
  static constexpr auto DIVERGING_BLACK_STANDARD_MAPS_WEIGHT    = 35.0F;
  static constexpr auto RED_STANDARD_MAPS_WEIGHT                = 35.0F;
  static constexpr auto GREEN_STANDARD_MAPS_WEIGHT              = 40.0F;
  static constexpr auto BLUE_STANDARD_MAPS_WEIGHT               = 40.0F;
  static constexpr auto YELLOW_STANDARD_MAPS_WEIGHT             = 40.0F;
  static constexpr auto ORANGE_STANDARD_MAPS_WEIGHT             = 40.0F;
  static constexpr auto PURPLE_STANDARD_MAPS_WEIGHT             = 90.0F;
  static constexpr auto CITIES_STANDARD_MAPS_WEIGHT             = 90.0F;
  static constexpr auto SEASONS_STANDARD_MAPS_WEIGHT            = 90.0F;
  static constexpr auto HEAT_STANDARD_MAPS_WEIGHT               = 90.0F;
  static constexpr auto COLD_STANDARD_MAPS_WEIGHT               = 90.0F;
  static constexpr auto PASTEL_STANDARD_MAPS_WEIGHT             = 90.0F;
  static constexpr auto WES_ANDERSON_MAPS_WEIGHT                = 90.0F;

  return {
      m_goomRand,
      {
        {Groups::ALL_MAPS_UNWEIGHTED, ALL_MAPS_UNWEIGHTED_WEIGHT},
        {Groups::ALL_STANDARD_MAPS, ALL_STANDARD_MAPS_WEIGHT},
        {Groups::ALL_SLIM_MAPS, ALL_SLIM_MAPS_WEIGHT},
        {Groups::MOSTLY_SEQUENTIAL_STANDARD_MAPS, MOSTLY_SEQUENTIAL_STANDARD_MAPS_WEIGHT},
        {Groups::MOSTLY_SEQUENTIAL_SLIM_MAPS, MOSTLY_SEQUENTIAL_SLIM_MAPS_WEIGHT},
        {Groups::SLIGHTLY_DIVERGING_STANDARD_MAPS, SLIGHTLY_DIVERGING_STANDARD_MAPS_WEIGHT},
        {Groups::SLIGHTLY_DIVERGING_SLIM_MAPS, SLIGHTLY_DIVERGING_SLIM_MAPS_WEIGHT},
        {Groups::DIVERGING_BLACK_STANDARD_MAPS, DIVERGING_BLACK_STANDARD_MAPS_WEIGHT},
        {Groups::RED_STANDARD_MAPS, RED_STANDARD_MAPS_WEIGHT},
        {Groups::GREEN_STANDARD_MAPS, GREEN_STANDARD_MAPS_WEIGHT},
        {Groups::BLUE_STANDARD_MAPS, BLUE_STANDARD_MAPS_WEIGHT},
        {Groups::YELLOW_STANDARD_MAPS, YELLOW_STANDARD_MAPS_WEIGHT},
        {Groups::ORANGE_STANDARD_MAPS, ORANGE_STANDARD_MAPS_WEIGHT},
        {Groups::PURPLE_STANDARD_MAPS, PURPLE_STANDARD_MAPS_WEIGHT},
        {Groups::CITIES_STANDARD_MAPS, CITIES_STANDARD_MAPS_WEIGHT},
        {Groups::SEASONS_STANDARD_MAPS, SEASONS_STANDARD_MAPS_WEIGHT},
        {Groups::HEAT_STANDARD_MAPS, HEAT_STANDARD_MAPS_WEIGHT},
        {Groups::COLD_STANDARD_MAPS, COLD_STANDARD_MAPS_WEIGHT},
        {Groups::PASTEL_STANDARD_MAPS, PASTEL_STANDARD_MAPS_WEIGHT},
        {Groups::WES_ANDERSON_MAPS, WES_ANDERSON_MAPS_WEIGHT},
        }
  };
}

auto VisualFxWeightedColorMaps::GetTentaclesMainGroups() const noexcept -> WeightedGroups
{
  static constexpr auto ALL_MAPS_UNWEIGHTED_WEIGHT              = 05.0F;
  static constexpr auto ALL_STANDARD_MAPS_WEIGHT                = 05.0F;
  static constexpr auto ALL_SLIM_MAPS_WEIGHT                    = 05.0F;
  static constexpr auto MOSTLY_SEQUENTIAL_STANDARD_MAPS_WEIGHT  = 05.0F;
  static constexpr auto MOSTLY_SEQUENTIAL_SLIM_MAPS_WEIGHT      = 05.0F;
  static constexpr auto SLIGHTLY_DIVERGING_STANDARD_MAPS_WEIGHT = 05.0F;
  static constexpr auto SLIGHTLY_DIVERGING_SLIM_MAPS_WEIGHT     = 20.0F;
  static constexpr auto DIVERGING_BLACK_STANDARD_MAPS_WEIGHT    = 35.0F;
  static constexpr auto RED_STANDARD_MAPS_WEIGHT                = 35.0F;
  static constexpr auto GREEN_STANDARD_MAPS_WEIGHT              = 40.0F;
  static constexpr auto BLUE_STANDARD_MAPS_WEIGHT               = 40.0F;
  static constexpr auto YELLOW_STANDARD_MAPS_WEIGHT             = 40.0F;
  static constexpr auto ORANGE_STANDARD_MAPS_WEIGHT             = 40.0F;
  static constexpr auto PURPLE_STANDARD_MAPS_WEIGHT             = 90.0F;
  static constexpr auto CITIES_STANDARD_MAPS_WEIGHT             = 90.0F;
  static constexpr auto SEASONS_STANDARD_MAPS_WEIGHT            = 90.0F;
  static constexpr auto HEAT_STANDARD_MAPS_WEIGHT               = 90.0F;
  static constexpr auto COLD_STANDARD_MAPS_WEIGHT               = 90.0F;
  static constexpr auto PASTEL_STANDARD_MAPS_WEIGHT             = 90.0F;
  static constexpr auto WES_ANDERSON_MAPS_WEIGHT                = 90.0F;

  return {
      m_goomRand,
      {
        {Groups::ALL_MAPS_UNWEIGHTED, ALL_MAPS_UNWEIGHTED_WEIGHT},
        {Groups::ALL_STANDARD_MAPS, ALL_STANDARD_MAPS_WEIGHT},
        {Groups::ALL_SLIM_MAPS, ALL_SLIM_MAPS_WEIGHT},
        {Groups::MOSTLY_SEQUENTIAL_STANDARD_MAPS, MOSTLY_SEQUENTIAL_STANDARD_MAPS_WEIGHT},
        {Groups::MOSTLY_SEQUENTIAL_SLIM_MAPS, MOSTLY_SEQUENTIAL_SLIM_MAPS_WEIGHT},
        {Groups::SLIGHTLY_DIVERGING_STANDARD_MAPS, SLIGHTLY_DIVERGING_STANDARD_MAPS_WEIGHT},
        {Groups::SLIGHTLY_DIVERGING_SLIM_MAPS, SLIGHTLY_DIVERGING_SLIM_MAPS_WEIGHT},
        {Groups::DIVERGING_BLACK_STANDARD_MAPS, DIVERGING_BLACK_STANDARD_MAPS_WEIGHT},
        {Groups::RED_STANDARD_MAPS, RED_STANDARD_MAPS_WEIGHT},
        {Groups::GREEN_STANDARD_MAPS, GREEN_STANDARD_MAPS_WEIGHT},
        {Groups::BLUE_STANDARD_MAPS, BLUE_STANDARD_MAPS_WEIGHT},
        {Groups::YELLOW_STANDARD_MAPS, YELLOW_STANDARD_MAPS_WEIGHT},
        {Groups::ORANGE_STANDARD_MAPS, ORANGE_STANDARD_MAPS_WEIGHT},
        {Groups::PURPLE_STANDARD_MAPS, PURPLE_STANDARD_MAPS_WEIGHT},
        {Groups::CITIES_STANDARD_MAPS, CITIES_STANDARD_MAPS_WEIGHT},
        {Groups::SEASONS_STANDARD_MAPS, SEASONS_STANDARD_MAPS_WEIGHT},
        {Groups::HEAT_STANDARD_MAPS, HEAT_STANDARD_MAPS_WEIGHT},
        {Groups::COLD_STANDARD_MAPS, COLD_STANDARD_MAPS_WEIGHT},
        {Groups::PASTEL_STANDARD_MAPS, PASTEL_STANDARD_MAPS_WEIGHT},
        {Groups::WES_ANDERSON_MAPS, WES_ANDERSON_MAPS_WEIGHT},
        }
  };
}

auto VisualFxWeightedColorMaps::GetTentaclesLowGroups() const noexcept -> WeightedGroups
{
  static constexpr auto ALL_MAPS_UNWEIGHTED_WEIGHT              = 05.0F;
  static constexpr auto ALL_STANDARD_MAPS_WEIGHT                = 05.0F;
  static constexpr auto ALL_SLIM_MAPS_WEIGHT                    = 05.0F;
  static constexpr auto MOSTLY_SEQUENTIAL_STANDARD_MAPS_WEIGHT  = 05.0F;
  static constexpr auto MOSTLY_SEQUENTIAL_SLIM_MAPS_WEIGHT      = 05.0F;
  static constexpr auto SLIGHTLY_DIVERGING_STANDARD_MAPS_WEIGHT = 05.0F;
  static constexpr auto SLIGHTLY_DIVERGING_SLIM_MAPS_WEIGHT     = 20.0F;
  static constexpr auto DIVERGING_BLACK_STANDARD_MAPS_WEIGHT    = 35.0F;
  static constexpr auto RED_STANDARD_MAPS_WEIGHT                = 35.0F;
  static constexpr auto GREEN_STANDARD_MAPS_WEIGHT              = 40.0F;
  static constexpr auto BLUE_STANDARD_MAPS_WEIGHT               = 40.0F;
  static constexpr auto YELLOW_STANDARD_MAPS_WEIGHT             = 40.0F;
  static constexpr auto ORANGE_STANDARD_MAPS_WEIGHT             = 40.0F;
  static constexpr auto PURPLE_STANDARD_MAPS_WEIGHT             = 90.0F;
  static constexpr auto CITIES_STANDARD_MAPS_WEIGHT             = 90.0F;
  static constexpr auto SEASONS_STANDARD_MAPS_WEIGHT            = 90.0F;
  static constexpr auto HEAT_STANDARD_MAPS_WEIGHT               = 90.0F;
  static constexpr auto COLD_STANDARD_MAPS_WEIGHT               = 90.0F;
  static constexpr auto PASTEL_STANDARD_MAPS_WEIGHT             = 90.0F;
  static constexpr auto WES_ANDERSON_MAPS_WEIGHT                = 90.0F;

  return {
      m_goomRand,
      {
        {Groups::ALL_MAPS_UNWEIGHTED, ALL_MAPS_UNWEIGHTED_WEIGHT},
        {Groups::ALL_STANDARD_MAPS, ALL_STANDARD_MAPS_WEIGHT},
        {Groups::ALL_SLIM_MAPS, ALL_SLIM_MAPS_WEIGHT},
        {Groups::MOSTLY_SEQUENTIAL_STANDARD_MAPS, MOSTLY_SEQUENTIAL_STANDARD_MAPS_WEIGHT},
        {Groups::MOSTLY_SEQUENTIAL_SLIM_MAPS, MOSTLY_SEQUENTIAL_SLIM_MAPS_WEIGHT},
        {Groups::SLIGHTLY_DIVERGING_STANDARD_MAPS, SLIGHTLY_DIVERGING_STANDARD_MAPS_WEIGHT},
        {Groups::SLIGHTLY_DIVERGING_SLIM_MAPS, SLIGHTLY_DIVERGING_SLIM_MAPS_WEIGHT},
        {Groups::DIVERGING_BLACK_STANDARD_MAPS, DIVERGING_BLACK_STANDARD_MAPS_WEIGHT},
        {Groups::RED_STANDARD_MAPS, RED_STANDARD_MAPS_WEIGHT},
        {Groups::GREEN_STANDARD_MAPS, GREEN_STANDARD_MAPS_WEIGHT},
        {Groups::BLUE_STANDARD_MAPS, BLUE_STANDARD_MAPS_WEIGHT},
        {Groups::YELLOW_STANDARD_MAPS, YELLOW_STANDARD_MAPS_WEIGHT},
        {Groups::ORANGE_STANDARD_MAPS, ORANGE_STANDARD_MAPS_WEIGHT},
        {Groups::PURPLE_STANDARD_MAPS, PURPLE_STANDARD_MAPS_WEIGHT},
        {Groups::CITIES_STANDARD_MAPS, CITIES_STANDARD_MAPS_WEIGHT},
        {Groups::SEASONS_STANDARD_MAPS, SEASONS_STANDARD_MAPS_WEIGHT},
        {Groups::HEAT_STANDARD_MAPS, HEAT_STANDARD_MAPS_WEIGHT},
        {Groups::COLD_STANDARD_MAPS, COLD_STANDARD_MAPS_WEIGHT},
        {Groups::PASTEL_STANDARD_MAPS, PASTEL_STANDARD_MAPS_WEIGHT},
        {Groups::WES_ANDERSON_MAPS, WES_ANDERSON_MAPS_WEIGHT},
        }
  };
}

auto VisualFxWeightedColorMaps::GetTubesMainGroups() const noexcept -> WeightedGroups
{
  static constexpr auto ALL_MAPS_UNWEIGHTED_WEIGHT              = 05.0F;
  static constexpr auto ALL_STANDARD_MAPS_WEIGHT                = 05.0F;
  static constexpr auto ALL_SLIM_MAPS_WEIGHT                    = 05.0F;
  static constexpr auto MOSTLY_SEQUENTIAL_STANDARD_MAPS_WEIGHT  = 05.0F;
  static constexpr auto MOSTLY_SEQUENTIAL_SLIM_MAPS_WEIGHT      = 05.0F;
  static constexpr auto SLIGHTLY_DIVERGING_STANDARD_MAPS_WEIGHT = 05.0F;
  static constexpr auto SLIGHTLY_DIVERGING_SLIM_MAPS_WEIGHT     = 20.0F;
  static constexpr auto DIVERGING_BLACK_STANDARD_MAPS_WEIGHT    = 35.0F;
  static constexpr auto RED_STANDARD_MAPS_WEIGHT                = 35.0F;
  static constexpr auto GREEN_STANDARD_MAPS_WEIGHT              = 40.0F;
  static constexpr auto BLUE_STANDARD_MAPS_WEIGHT               = 40.0F;
  static constexpr auto YELLOW_STANDARD_MAPS_WEIGHT             = 40.0F;
  static constexpr auto ORANGE_STANDARD_MAPS_WEIGHT             = 40.0F;
  static constexpr auto PURPLE_STANDARD_MAPS_WEIGHT             = 90.0F;
  static constexpr auto CITIES_STANDARD_MAPS_WEIGHT             = 90.0F;
  static constexpr auto SEASONS_STANDARD_MAPS_WEIGHT            = 90.0F;
  static constexpr auto HEAT_STANDARD_MAPS_WEIGHT               = 90.0F;
  static constexpr auto COLD_STANDARD_MAPS_WEIGHT               = 90.0F;
  static constexpr auto PASTEL_STANDARD_MAPS_WEIGHT             = 90.0F;
  static constexpr auto WES_ANDERSON_MAPS_WEIGHT                = 90.0F;

  return {
      m_goomRand,
      {
        {Groups::ALL_MAPS_UNWEIGHTED, ALL_MAPS_UNWEIGHTED_WEIGHT},
        {Groups::ALL_STANDARD_MAPS, ALL_STANDARD_MAPS_WEIGHT},
        {Groups::ALL_SLIM_MAPS, ALL_SLIM_MAPS_WEIGHT},
        {Groups::MOSTLY_SEQUENTIAL_STANDARD_MAPS, MOSTLY_SEQUENTIAL_STANDARD_MAPS_WEIGHT},
        {Groups::MOSTLY_SEQUENTIAL_SLIM_MAPS, MOSTLY_SEQUENTIAL_SLIM_MAPS_WEIGHT},
        {Groups::SLIGHTLY_DIVERGING_STANDARD_MAPS, SLIGHTLY_DIVERGING_STANDARD_MAPS_WEIGHT},
        {Groups::SLIGHTLY_DIVERGING_SLIM_MAPS, SLIGHTLY_DIVERGING_SLIM_MAPS_WEIGHT},
        {Groups::DIVERGING_BLACK_STANDARD_MAPS, DIVERGING_BLACK_STANDARD_MAPS_WEIGHT},
        {Groups::RED_STANDARD_MAPS, RED_STANDARD_MAPS_WEIGHT},
        {Groups::GREEN_STANDARD_MAPS, GREEN_STANDARD_MAPS_WEIGHT},
        {Groups::BLUE_STANDARD_MAPS, BLUE_STANDARD_MAPS_WEIGHT},
        {Groups::YELLOW_STANDARD_MAPS, YELLOW_STANDARD_MAPS_WEIGHT},
        {Groups::ORANGE_STANDARD_MAPS, ORANGE_STANDARD_MAPS_WEIGHT},
        {Groups::PURPLE_STANDARD_MAPS, PURPLE_STANDARD_MAPS_WEIGHT},
        {Groups::CITIES_STANDARD_MAPS, CITIES_STANDARD_MAPS_WEIGHT},
        {Groups::SEASONS_STANDARD_MAPS, SEASONS_STANDARD_MAPS_WEIGHT},
        {Groups::HEAT_STANDARD_MAPS, HEAT_STANDARD_MAPS_WEIGHT},
        {Groups::COLD_STANDARD_MAPS, COLD_STANDARD_MAPS_WEIGHT},
        {Groups::PASTEL_STANDARD_MAPS, PASTEL_STANDARD_MAPS_WEIGHT},
        {Groups::WES_ANDERSON_MAPS, WES_ANDERSON_MAPS_WEIGHT},
        }
  };
}

auto VisualFxWeightedColorMaps::GetTubesLowGroups() const noexcept -> WeightedGroups
{
  static constexpr auto ALL_MAPS_UNWEIGHTED_WEIGHT              = 05.0F;
  static constexpr auto ALL_STANDARD_MAPS_WEIGHT                = 05.0F;
  static constexpr auto ALL_SLIM_MAPS_WEIGHT                    = 05.0F;
  static constexpr auto MOSTLY_SEQUENTIAL_STANDARD_MAPS_WEIGHT  = 05.0F;
  static constexpr auto MOSTLY_SEQUENTIAL_SLIM_MAPS_WEIGHT      = 05.0F;
  static constexpr auto SLIGHTLY_DIVERGING_STANDARD_MAPS_WEIGHT = 05.0F;
  static constexpr auto SLIGHTLY_DIVERGING_SLIM_MAPS_WEIGHT     = 20.0F;
  static constexpr auto DIVERGING_BLACK_STANDARD_MAPS_WEIGHT    = 35.0F;
  static constexpr auto RED_STANDARD_MAPS_WEIGHT                = 35.0F;
  static constexpr auto GREEN_STANDARD_MAPS_WEIGHT              = 40.0F;
  static constexpr auto BLUE_STANDARD_MAPS_WEIGHT               = 40.0F;
  static constexpr auto YELLOW_STANDARD_MAPS_WEIGHT             = 40.0F;
  static constexpr auto ORANGE_STANDARD_MAPS_WEIGHT             = 40.0F;
  static constexpr auto PURPLE_STANDARD_MAPS_WEIGHT             = 90.0F;
  static constexpr auto CITIES_STANDARD_MAPS_WEIGHT             = 90.0F;
  static constexpr auto SEASONS_STANDARD_MAPS_WEIGHT            = 90.0F;
  static constexpr auto HEAT_STANDARD_MAPS_WEIGHT               = 90.0F;
  static constexpr auto COLD_STANDARD_MAPS_WEIGHT               = 90.0F;
  static constexpr auto PASTEL_STANDARD_MAPS_WEIGHT             = 90.0F;
  static constexpr auto WES_ANDERSON_MAPS_WEIGHT                = 90.0F;

  return {
      m_goomRand,
      {
        {Groups::ALL_MAPS_UNWEIGHTED, ALL_MAPS_UNWEIGHTED_WEIGHT},
        {Groups::ALL_STANDARD_MAPS, ALL_STANDARD_MAPS_WEIGHT},
        {Groups::ALL_SLIM_MAPS, ALL_SLIM_MAPS_WEIGHT},
        {Groups::MOSTLY_SEQUENTIAL_STANDARD_MAPS, MOSTLY_SEQUENTIAL_STANDARD_MAPS_WEIGHT},
        {Groups::MOSTLY_SEQUENTIAL_SLIM_MAPS, MOSTLY_SEQUENTIAL_SLIM_MAPS_WEIGHT},
        {Groups::SLIGHTLY_DIVERGING_STANDARD_MAPS, SLIGHTLY_DIVERGING_STANDARD_MAPS_WEIGHT},
        {Groups::SLIGHTLY_DIVERGING_SLIM_MAPS, SLIGHTLY_DIVERGING_SLIM_MAPS_WEIGHT},
        {Groups::DIVERGING_BLACK_STANDARD_MAPS, DIVERGING_BLACK_STANDARD_MAPS_WEIGHT},
        {Groups::RED_STANDARD_MAPS, RED_STANDARD_MAPS_WEIGHT},
        {Groups::GREEN_STANDARD_MAPS, GREEN_STANDARD_MAPS_WEIGHT},
        {Groups::BLUE_STANDARD_MAPS, BLUE_STANDARD_MAPS_WEIGHT},
        {Groups::YELLOW_STANDARD_MAPS, YELLOW_STANDARD_MAPS_WEIGHT},
        {Groups::ORANGE_STANDARD_MAPS, ORANGE_STANDARD_MAPS_WEIGHT},
        {Groups::PURPLE_STANDARD_MAPS, PURPLE_STANDARD_MAPS_WEIGHT},
        {Groups::CITIES_STANDARD_MAPS, CITIES_STANDARD_MAPS_WEIGHT},
        {Groups::SEASONS_STANDARD_MAPS, SEASONS_STANDARD_MAPS_WEIGHT},
        {Groups::HEAT_STANDARD_MAPS, HEAT_STANDARD_MAPS_WEIGHT},
        {Groups::COLD_STANDARD_MAPS, COLD_STANDARD_MAPS_WEIGHT},
        {Groups::PASTEL_STANDARD_MAPS, PASTEL_STANDARD_MAPS_WEIGHT},
        {Groups::WES_ANDERSON_MAPS, WES_ANDERSON_MAPS_WEIGHT},
        }
  };
}

} // namespace GOOM::CONTROL
