#include "random_color_maps_groups.h"

#include "goom_config.h"
#include "random_color_maps.h"

namespace GOOM::COLOR
{

using COLOR::ColorMapGroup;
using COLOR::RandomColorMaps;
using COLOR::WeightedColorMaps;
using UTILS::MATH::IGoomRand;
using UTILS::MATH::Weights;

namespace
{
namespace IMPL
{

auto MakeSharedAllMapsUnweighted(const IGoomRand& goomRand) noexcept
    -> std::shared_ptr<RandomColorMaps>
{
  static constexpr auto* MAPS_NAME = "AllMapsUnweighted";

  // clang-format off
  return std::make_shared<WeightedColorMaps>(
      goomRand,
      Weights<ColorMapGroup>{
          goomRand,
          {
              {ColorMapGroup::ALL, 1.0F},
          }
      },
      MAPS_NAME
  );
  // clang-format on
}

auto MakeSharedAllStandardMaps(const IGoomRand& goomRand) noexcept
    -> std::shared_ptr<RandomColorMaps>
{
  static constexpr auto* MAPS_NAME = "AllStandardMaps";

  static constexpr auto PERCEPTUALLY_UNIFORM_SEQUENTIAL_WEIGHT = 1.0F;
  static constexpr auto SEQUENTIAL_WEIGHT                      = 1.0F;
  static constexpr auto SEQUENTIAL2_WEIGHT                     = 1.0F;
  static constexpr auto CYCLIC_WEIGHT                          = 1.0F;
  static constexpr auto DIVERGING_WEIGHT                       = 1.0F;
  static constexpr auto DIVERGING_BLACK_WEIGHT                 = 1.0F;
  static constexpr auto QUALITATIVE_WEIGHT                     = 1.0F;
  static constexpr auto MISC_WEIGHT                            = 1.0F;

  // TODO(glk) - Investigate clang-format issue with this.
  // clang-format off
  return std::make_shared<WeightedColorMaps>(
      goomRand,
      Weights<ColorMapGroup>{
        goomRand,
        {
          {ColorMapGroup::PERCEPTUALLY_UNIFORM_SEQUENTIAL, PERCEPTUALLY_UNIFORM_SEQUENTIAL_WEIGHT},
          {ColorMapGroup::SEQUENTIAL,                      SEQUENTIAL_WEIGHT},
          {ColorMapGroup::SEQUENTIAL2,                     SEQUENTIAL2_WEIGHT},
          {ColorMapGroup::CYCLIC,                          CYCLIC_WEIGHT},
          {ColorMapGroup::DIVERGING,                       DIVERGING_WEIGHT},
          {ColorMapGroup::DIVERGING_BLACK,                 DIVERGING_BLACK_WEIGHT},
          {ColorMapGroup::QUALITATIVE,                     QUALITATIVE_WEIGHT},
          {ColorMapGroup::MISC,                            MISC_WEIGHT},
        }
      },
      MAPS_NAME
  );
  // clang-format on
}

auto MakeSharedAllSlimMaps(const IGoomRand& goomRand) noexcept -> std::shared_ptr<RandomColorMaps>
{
  static constexpr auto* MAPS_NAME = "AllSlimMaps";

  static constexpr auto PERCEPTUALLY_UNIFORM_SEQUENTIAL_SLIM_WEIGHT = 1.0F;
  static constexpr auto SEQUENTIAL_SLIM_WEIGHT                      = 1.0F;
  static constexpr auto SEQUENTIAL2_SLIM_WEIGHT                     = 1.0F;
  static constexpr auto CYCLIC_SLIM_WEIGHT                          = 1.0F;
  static constexpr auto DIVERGING_SLIM_WEIGHT                       = 1.0F;
  static constexpr auto DIVERGING_BLACK_SLIM_WEIGHT                 = 1.0F;
  static constexpr auto QUALITATIVE_SLIM_WEIGHT                     = 1.0F;
  static constexpr auto MISC_SLIM_WEIGHT                            = 1.0F;

  // clang-format off
  return std::make_shared<WeightedColorMaps>(
      goomRand,
      Weights<ColorMapGroup>{
          goomRand,
          {
              {ColorMapGroup::PERCEPTUALLY_UNIFORM_SEQUENTIAL_SLIM,
                                                       PERCEPTUALLY_UNIFORM_SEQUENTIAL_SLIM_WEIGHT},
              {ColorMapGroup::SEQUENTIAL_SLIM,         SEQUENTIAL_SLIM_WEIGHT},
              {ColorMapGroup::SEQUENTIAL2_SLIM,        SEQUENTIAL2_SLIM_WEIGHT},
              {ColorMapGroup::CYCLIC_SLIM,             CYCLIC_SLIM_WEIGHT},
              {ColorMapGroup::DIVERGING_SLIM,          DIVERGING_SLIM_WEIGHT},
              {ColorMapGroup::DIVERGING_BLACK_SLIM,    DIVERGING_BLACK_SLIM_WEIGHT},
              {ColorMapGroup::QUALITATIVE_SLIM,        QUALITATIVE_SLIM_WEIGHT},
              {ColorMapGroup::MISC_SLIM,               MISC_SLIM_WEIGHT},
          }
      },
      MAPS_NAME
  );
  // clang-format on
}

auto MakeSharedMostlySequentialStandardMaps(const IGoomRand& goomRand) noexcept
    -> std::shared_ptr<RandomColorMaps>
{
  static constexpr auto* MAPS_NAME = "MostlySequentialStandardMaps";

  static constexpr auto PERCEPTUALLY_UNIFORM_SEQUENTIAL_WEIGHT = 1.0F;
  static constexpr auto SEQUENTIAL_WEIGHT                      = 1.0F;
  static constexpr auto SEQUENTIAL2_WEIGHT                     = 1.0F;
  static constexpr auto CYCLIC_WEIGHT                          = 0.0F;
  static constexpr auto DIVERGING_WEIGHT                       = 0.0F;
  static constexpr auto DIVERGING_BLACK_WEIGHT                 = 0.0F;
  static constexpr auto QUALITATIVE_WEIGHT                     = 1.0F;
  static constexpr auto MISC_WEIGHT                            = 1.0F;

  // clang-format off
  return std::make_shared<WeightedColorMaps>(
      goomRand,
      Weights<ColorMapGroup>{
        goomRand,
        {
          {ColorMapGroup::PERCEPTUALLY_UNIFORM_SEQUENTIAL, PERCEPTUALLY_UNIFORM_SEQUENTIAL_WEIGHT},
          {ColorMapGroup::SEQUENTIAL,                      SEQUENTIAL_WEIGHT},
          {ColorMapGroup::SEQUENTIAL2,                     SEQUENTIAL2_WEIGHT},
          {ColorMapGroup::CYCLIC,                          CYCLIC_WEIGHT},
          {ColorMapGroup::DIVERGING,                       DIVERGING_WEIGHT},
          {ColorMapGroup::DIVERGING_BLACK,                 DIVERGING_BLACK_WEIGHT},
          {ColorMapGroup::QUALITATIVE,                     QUALITATIVE_WEIGHT},
          {ColorMapGroup::MISC,                            MISC_WEIGHT},
        }
      },
      MAPS_NAME
  );
  // clang-format on
}

auto MakeSharedMostlySequentialSlimMaps(const IGoomRand& goomRand) noexcept
    -> std::shared_ptr<RandomColorMaps>
{
  static constexpr auto* MAPS_NAME = "MostlySequentialSlimMaps";

  static constexpr auto PERCEPTUALLY_UNIFORM_SEQUENTIAL_SLIM_WEIGHT = 1.0F;
  static constexpr auto SEQUENTIAL_SLIM_WEIGHT                      = 1.0F;
  static constexpr auto SEQUENTIAL2_SLIM_WEIGHT                     = 1.0F;
  static constexpr auto CYCLIC_SLIM_WEIGHT                          = 0.0F;
  static constexpr auto DIVERGING_SLIM_WEIGHT                       = 0.0F;
  static constexpr auto DIVERGING_BLACK_SLIM_WEIGHT                 = 0.0F;
  static constexpr auto QUALITATIVE_SLIM_WEIGHT                     = 1.0F;
  static constexpr auto MISC_SLIM_WEIGHT                            = 1.0F;

  // clang-format off
  return std::make_shared<WeightedColorMaps>(
      goomRand,
      Weights<ColorMapGroup>{
          goomRand,
          {
              {ColorMapGroup::PERCEPTUALLY_UNIFORM_SEQUENTIAL_SLIM,
                                                       PERCEPTUALLY_UNIFORM_SEQUENTIAL_SLIM_WEIGHT},
              {ColorMapGroup::SEQUENTIAL_SLIM,         SEQUENTIAL_SLIM_WEIGHT},
              {ColorMapGroup::SEQUENTIAL2_SLIM,        SEQUENTIAL2_SLIM_WEIGHT},
              {ColorMapGroup::CYCLIC_SLIM,             CYCLIC_SLIM_WEIGHT},
              {ColorMapGroup::DIVERGING_SLIM,          DIVERGING_SLIM_WEIGHT},
              {ColorMapGroup::DIVERGING_BLACK_SLIM,    DIVERGING_BLACK_SLIM_WEIGHT},
              {ColorMapGroup::QUALITATIVE_SLIM,        QUALITATIVE_SLIM_WEIGHT},
              {ColorMapGroup::MISC_SLIM,               MISC_SLIM_WEIGHT},
          }
      },
      MAPS_NAME
  );
  // clang-format on
}

auto MakeSharedSlightlyDivergingStandardMaps(const IGoomRand& goomRand) noexcept
    -> std::shared_ptr<RandomColorMaps>
{
  static constexpr auto* MAPS_NAME = "SlightlyDivergingStandardMaps";

  static constexpr auto PERCEPTUALLY_UNIFORM_SEQUENTIAL_WEIGHT = 10.0F;
  static constexpr auto SEQUENTIAL_WEIGHT                      = 10.0F;
  static constexpr auto SEQUENTIAL2_WEIGHT                     = 10.0F;
  static constexpr auto CYCLIC_WEIGHT                          = 10.0F;
  static constexpr auto DIVERGING_WEIGHT                       = 20.0F;
  static constexpr auto DIVERGING_BLACK_WEIGHT                 = 01.0F;
  static constexpr auto QUALITATIVE_WEIGHT                     = 10.0F;
  static constexpr auto MISC_WEIGHT                            = 20.0F;

  // clang-format off
  return std::make_shared<WeightedColorMaps>(
      goomRand,
      Weights<ColorMapGroup>{
        goomRand,
        {
          {ColorMapGroup::PERCEPTUALLY_UNIFORM_SEQUENTIAL, PERCEPTUALLY_UNIFORM_SEQUENTIAL_WEIGHT},
          {ColorMapGroup::SEQUENTIAL,                      SEQUENTIAL_WEIGHT},
          {ColorMapGroup::SEQUENTIAL2,                     SEQUENTIAL2_WEIGHT},
          {ColorMapGroup::CYCLIC,                          CYCLIC_WEIGHT},
          {ColorMapGroup::DIVERGING,                       DIVERGING_WEIGHT},
          {ColorMapGroup::DIVERGING_BLACK,                 DIVERGING_BLACK_WEIGHT},
          {ColorMapGroup::QUALITATIVE,                     QUALITATIVE_WEIGHT},
          {ColorMapGroup::MISC,                            MISC_WEIGHT},
        }
      },
      MAPS_NAME
  );
  // clang-format on
}

auto MakeSharedSlightlyDivergingSlimMaps(const IGoomRand& goomRand) noexcept
    -> std::shared_ptr<RandomColorMaps>
{
  static constexpr auto* MAPS_NAME = "SlightlyDivergingSlimMaps";

  static constexpr auto PERCEPTUALLY_UNIFORM_SEQUENTIAL_SLIM_WEIGHT = 10.0F;
  static constexpr auto SEQUENTIAL_SLIM_WEIGHT                      = 10.0F;
  static constexpr auto SEQUENTIAL2_SLIM_WEIGHT                     = 10.0F;
  static constexpr auto CYCLIC_SLIM_WEIGHT                          = 10.0F;
  static constexpr auto DIVERGING_SLIM_WEIGHT                       = 20.0F;
  static constexpr auto DIVERGING_BLACK_SLIM_WEIGHT                 = 01.0F;
  static constexpr auto QUALITATIVE_SLIM_WEIGHT                     = 10.0F;
  static constexpr auto MISC_SLIM_WEIGHT                            = 20.0F;

  // clang-format off
  return std::make_shared<WeightedColorMaps>(
      goomRand,
      Weights<ColorMapGroup>{
          goomRand,
          {
              {ColorMapGroup::PERCEPTUALLY_UNIFORM_SEQUENTIAL_SLIM,
                                                       PERCEPTUALLY_UNIFORM_SEQUENTIAL_SLIM_WEIGHT},
              {ColorMapGroup::SEQUENTIAL_SLIM,         SEQUENTIAL_SLIM_WEIGHT},
              {ColorMapGroup::SEQUENTIAL2_SLIM,        SEQUENTIAL2_SLIM_WEIGHT},
              {ColorMapGroup::CYCLIC_SLIM,             CYCLIC_SLIM_WEIGHT},
              {ColorMapGroup::DIVERGING_SLIM,          DIVERGING_SLIM_WEIGHT},
              {ColorMapGroup::DIVERGING_BLACK_SLIM,    DIVERGING_BLACK_SLIM_WEIGHT},
              {ColorMapGroup::QUALITATIVE_SLIM,        QUALITATIVE_SLIM_WEIGHT},
              {ColorMapGroup::MISC_SLIM,               MISC_SLIM_WEIGHT},
          }
      },
      MAPS_NAME
  );
  // clang-format on
}

auto MakeSharedBlueStandardMaps(const IGoomRand& goomRand) noexcept
    -> std::shared_ptr<RandomColorMaps>
{
  static constexpr auto* MAPS_NAME = "BlueStandardMaps";

  // clang-format off
  return std::make_shared<WeightedColorMaps>(
      goomRand,
      Weights<ColorMapGroup>{
          goomRand,
          {
              {ColorMapGroup::BLUES, 1.0F},
          }
      },
      MAPS_NAME
  );
  // clang-format on
}

auto MakeSharedRedStandardMaps(const IGoomRand& goomRand) noexcept
    -> std::shared_ptr<RandomColorMaps>
{
  static constexpr auto* MAPS_NAME = "RedStandardMaps";

  // clang-format off
  return std::make_shared<WeightedColorMaps>(
      goomRand,
      Weights<ColorMapGroup>{
          goomRand,
          {
              {ColorMapGroup::REDS, 1.0F},
          }
      },
      MAPS_NAME
  );
  // clang-format on
}

auto MakeSharedGreenStandardMaps(const IGoomRand& goomRand) noexcept
    -> std::shared_ptr<RandomColorMaps>
{
  static constexpr auto* MAPS_NAME = "GreenStandardMaps";

  // clang-format off
  return std::make_shared<WeightedColorMaps>(
      goomRand,
      Weights<ColorMapGroup>{
          goomRand,
          {
              {ColorMapGroup::GREENS, 1.0F},
          }
      },
      MAPS_NAME
  );
  // clang-format on
}

auto MakeSharedYellowStandardMaps(const IGoomRand& goomRand) noexcept
    -> std::shared_ptr<RandomColorMaps>
{
  static constexpr auto* MAPS_NAME = "YellowStandardMaps";

  // clang-format off
  return std::make_shared<WeightedColorMaps>(
      goomRand,
      Weights<ColorMapGroup>{
          goomRand,
          {
              {ColorMapGroup::YELLOWS, 1.0F},
          }
      },
      MAPS_NAME
  );
  // clang-format on
}

auto MakeSharedOrangeStandardMaps(const IGoomRand& goomRand) noexcept
    -> std::shared_ptr<RandomColorMaps>
{
  static constexpr auto* MAPS_NAME = "OrangeStandardMaps";

  // clang-format off
  return std::make_shared<WeightedColorMaps>(
      goomRand,
      Weights<ColorMapGroup>{
          goomRand,
          {
              {ColorMapGroup::ORANGES, 1.0F},
          }
      },
      MAPS_NAME
  );
  // clang-format on
}

auto MakeSharedPurpleStandardMaps(const IGoomRand& goomRand) noexcept
    -> std::shared_ptr<RandomColorMaps>
{
  static constexpr auto* MAPS_NAME = "PurpleStandardMaps";

  // clang-format off
  return std::make_shared<WeightedColorMaps>(
      goomRand,
      Weights<ColorMapGroup>{
          goomRand,
          {
              {ColorMapGroup::PURPLES, 1.0F},
          }
      },
      MAPS_NAME
  );
  // clang-format on
}

auto MakeSharedCitiesStandardMaps(const IGoomRand& goomRand) noexcept
    -> std::shared_ptr<RandomColorMaps>
{
  static constexpr auto* MAPS_NAME = "CitiesStandardMaps";

  // clang-format off
  return std::make_shared<WeightedColorMaps>(
      goomRand,
      Weights<ColorMapGroup>{
          goomRand,
          {
              {ColorMapGroup::CITIES, 1.0F},
          }
      },
      MAPS_NAME
  );
  // clang-format on
}

auto MakeSharedSeasonsStandardMaps(const IGoomRand& goomRand) noexcept
    -> std::shared_ptr<RandomColorMaps>
{
  static constexpr auto* MAPS_NAME = "SeasonsStandardMaps";

  // clang-format off
  return std::make_shared<WeightedColorMaps>(
      goomRand,
      Weights<ColorMapGroup>{
          goomRand,
          {
              {ColorMapGroup::SEASONS, 1.0F},
          }
      },
      MAPS_NAME
  );
  // clang-format on
}

auto MakeSharedHeatStandardMaps(const IGoomRand& goomRand) noexcept
    -> std::shared_ptr<RandomColorMaps>
{
  static constexpr auto* MAPS_NAME = "HeatStandardMaps";

  // clang-format off
  return std::make_shared<WeightedColorMaps>(
      goomRand,
      Weights<ColorMapGroup>{
          goomRand,
          {
              {ColorMapGroup::HEAT, 1.0F},
          }
      },
      MAPS_NAME
  );
  // clang-format on
}

auto MakeSharedColdStandardMaps(const IGoomRand& goomRand) noexcept
    -> std::shared_ptr<RandomColorMaps>
{
  static constexpr auto* MAPS_NAME = "ColdStandardMaps";

  // clang-format off
  return std::make_shared<WeightedColorMaps>(
      goomRand,
      Weights<ColorMapGroup>{
          goomRand,
          {
              {ColorMapGroup::COLD, 1.0F},
          }
      },
      MAPS_NAME
  );
  // clang-format on
}

auto MakeSharedPastelStandardMaps(const IGoomRand& goomRand) noexcept
    -> std::shared_ptr<RandomColorMaps>
{
  static constexpr auto* MAPS_NAME = "PastelStandardMaps";

  // clang-format off
  return std::make_shared<WeightedColorMaps>(
      goomRand,
      Weights<ColorMapGroup>{
          goomRand,
          {
              {ColorMapGroup::PASTEL, 1.0F},
          }
      },
      MAPS_NAME
  );
  // clang-format on
}

auto MakeSharedDivergingBlackStandardMaps(const IGoomRand& goomRand) noexcept
    -> std::shared_ptr<RandomColorMaps>
{
  static constexpr auto* MAPS_NAME = "DivergingBlackStandardMaps";

  // clang-format off
  return std::make_shared<WeightedColorMaps>(
      goomRand,
      Weights<ColorMapGroup>{
          goomRand,
          {
              {ColorMapGroup::DIVERGING_BLACK, 1.0F},
          }
      },
      MAPS_NAME
  );
  // clang-format on
}

auto MakeSharedWesAndersonMaps(const UTILS::MATH::IGoomRand& goomRand) noexcept
    -> std::shared_ptr<RandomColorMaps>
{
  static constexpr auto* MAPS_NAME = "WesAndersonMaps";

  // clang-format off
  return std::make_shared<WeightedColorMaps>(
      goomRand,
      Weights<ColorMapGroup>{
          goomRand,
          {
              {ColorMapGroup::WES_ANDERSON, 1.0F},
          }
      },
      MAPS_NAME
  );
  // clang-format on
}

} // namespace IMPL
} // namespace

RandomColorMapsGroups::RandomColorMapsGroups(const IGoomRand& goomRand) noexcept
  : m_goomRand{goomRand}
{
}

auto RandomColorMapsGroups::MakeRandomColorMapsGroup(
    const Groups randomColorMapsGroup) const noexcept -> std::shared_ptr<RandomColorMaps>
{
  switch (randomColorMapsGroup)
  {
    case Groups::ALL_MAPS_UNWEIGHTED:
      return IMPL::MakeSharedAllMapsUnweighted(m_goomRand);
    case Groups::ALL_STANDARD_MAPS:
      return IMPL::MakeSharedAllStandardMaps(m_goomRand);
    case Groups::ALL_SLIM_MAPS:
      return IMPL::MakeSharedAllSlimMaps(m_goomRand);
    case Groups::MOSTLY_SEQUENTIAL_STANDARD_MAPS:
      return IMPL::MakeSharedMostlySequentialStandardMaps(m_goomRand);
    case Groups::MOSTLY_SEQUENTIAL_SLIM_MAPS:
      return IMPL::MakeSharedMostlySequentialSlimMaps(m_goomRand);
    case Groups::SLIGHTLY_DIVERGING_STANDARD_MAPS:
      return IMPL::MakeSharedSlightlyDivergingStandardMaps(m_goomRand);
    case Groups::SLIGHTLY_DIVERGING_SLIM_MAPS:
      return IMPL::MakeSharedSlightlyDivergingSlimMaps(m_goomRand);
    case Groups::DIVERGING_BLACK_STANDARD_MAPS:
      return IMPL::MakeSharedDivergingBlackStandardMaps(m_goomRand);
    case Groups::RED_STANDARD_MAPS:
      return IMPL::MakeSharedRedStandardMaps(m_goomRand);
    case Groups::GREEN_STANDARD_MAPS:
      return IMPL::MakeSharedGreenStandardMaps(m_goomRand);
    case Groups::BLUE_STANDARD_MAPS:
      return IMPL::MakeSharedBlueStandardMaps(m_goomRand);
    case Groups::YELLOW_STANDARD_MAPS:
      return IMPL::MakeSharedYellowStandardMaps(m_goomRand);
    case Groups::ORANGE_STANDARD_MAPS:
      return IMPL::MakeSharedOrangeStandardMaps(m_goomRand);
    case Groups::PURPLE_STANDARD_MAPS:
      return IMPL::MakeSharedPurpleStandardMaps(m_goomRand);
    case Groups::CITIES_STANDARD_MAPS:
      return IMPL::MakeSharedCitiesStandardMaps(m_goomRand);
    case Groups::SEASONS_STANDARD_MAPS:
      return IMPL::MakeSharedSeasonsStandardMaps(m_goomRand);
    case Groups::HEAT_STANDARD_MAPS:
      return IMPL::MakeSharedHeatStandardMaps(m_goomRand);
    case Groups::COLD_STANDARD_MAPS:
      return IMPL::MakeSharedColdStandardMaps(m_goomRand);
    case Groups::PASTEL_STANDARD_MAPS:
      return IMPL::MakeSharedPastelStandardMaps(m_goomRand);
    case Groups::WES_ANDERSON_MAPS:
      return IMPL::MakeSharedWesAndersonMaps(m_goomRand);
    default:
      FailFast();
      return nullptr;
  }
}

} // namespace GOOM::COLOR
