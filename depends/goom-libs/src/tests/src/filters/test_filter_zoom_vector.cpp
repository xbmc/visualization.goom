#ifndef GOOM_DEBUG
#define GOOM_DEBUG
#endif

#include "catch2/catch.hpp"
#include "filter_fx/after_effects/after_effects_types.h"
#include "filter_fx/filter_buffers.h"
#include "filter_fx/filter_effects/uniform_zoom_in_coefficients_effect.h"
#include "filter_fx/filter_effects/zoom_vector_effects.h"
#include "filter_fx/filter_settings.h"
#include "filter_fx/filter_zoom_vector.h"
#include "filter_fx/normalized_coords.h"
#include "goom_config.h"
#include "goom_plugin_info.h"
#include "utils/enum_utils.h"
#include "utils/math/goom_rand.h"
#include "utils/math/misc.h"

#include <cmath>
#include <memory>

namespace GOOM::UNIT_TESTS
{

using FILTER_FX::FilterZoomVector;
using FILTER_FX::NormalizedCoords;
using FILTER_FX::NormalizedCoordsConverter;
using FILTER_FX::Vitesse;
using FILTER_FX::ZoomFilterBuffers;
using FILTER_FX::ZoomFilterEffectsSettings;
using FILTER_FX::AFTER_EFFECTS::AfterEffectsTypes;
using FILTER_FX::AFTER_EFFECTS::HypercosOverlay;
using FILTER_FX::AFTER_EFFECTS::RotationAdjustments;
using FILTER_FX::FILTER_EFFECTS::UniformZoomInCoefficientsEffect;
using FILTER_FX::FILTER_EFFECTS::ZoomVectorEffects;
using UTILS::EnumMap;
using UTILS::MATH::GoomRand;

static constexpr size_t WIDTH                    = 120;
static constexpr size_t HEIGHT                   = 70;
static constexpr const char* RESOURCES_DIRECTORY = "";
static const GoomRand GOOM_RAND{};
static const NormalizedCoordsConverter NORMALIZED_COORDS_CONVERTER{
    {WIDTH, HEIGHT},
    ZoomFilterBuffers::MIN_SCREEN_COORD_ABS_VAL
};

namespace
{
[[nodiscard]] auto GetRelativeSpeed(const uint32_t intSpeed, const bool reverseSpeed) -> float
{
  static constexpr auto MAX_INT_SPEED = static_cast<float>(Vitesse::MAXIMUM_SPEED);
  const auto absRelativeSpeed         = static_cast<float>(intSpeed) / MAX_INT_SPEED;
  return reverseSpeed ? -absRelativeSpeed : absRelativeSpeed;
}

[[nodiscard]] auto GetZoomInCoeff(const float baseZoomInCoeffFactor, const float relativeSpeed)
    -> float
{
  return baseZoomInCoeffFactor * (1.0F + relativeSpeed);
}

} // namespace

TEST_CASE("FilterZoomVector")
{
  static constexpr auto TEST_X = 10;
  static constexpr auto TEST_Y = 50;
  static_assert((0 <= TEST_X) && (TEST_X < WIDTH), "Invalid X");
  static_assert((0 <= TEST_Y) && (TEST_Y < WIDTH), "Invalid Y");

  auto filterZoomVector =
      FilterZoomVector{WIDTH, RESOURCES_DIRECTORY, GOOM_RAND, NORMALIZED_COORDS_CONVERTER};

  static constexpr auto DEFAULT_ZOOM_MID_X                        = 16;
  static constexpr auto DEFAULT_ZOOM_MID_Y                        = 1;
  static constexpr auto DEFAULT_MAX_ZOOM_IN_COEFF                 = 2.01F;
  static constexpr auto UNIT_BASE_ZOOM_IN_COEFF_FACTOR_MULTIPLIER = 1.0F;
  static constexpr auto ALL_OFF_AFTER_EFFECTS_STATES = EnumMap<AfterEffectsTypes, bool>{{{
      {AfterEffectsTypes::BLOCK_WAVY, false},
      {AfterEffectsTypes::HYPERCOS, false},
      {AfterEffectsTypes::IMAGE_VELOCITY, false},
      {AfterEffectsTypes::NOISE, false},
      {AfterEffectsTypes::PLANES, false},
      {AfterEffectsTypes::ROTATION, false},
      {AfterEffectsTypes::TAN_EFFECT, false},
      {AfterEffectsTypes::XY_LERP_EFFECT, false},
  }}};

  auto filterSettings = ZoomFilterEffectsSettings{
      Vitesse{},
      DEFAULT_MAX_ZOOM_IN_COEFF,
      UNIT_BASE_ZOOM_IN_COEFF_FACTOR_MULTIPLIER,
      std::make_shared<UniformZoomInCoefficientsEffect>(),
      {DEFAULT_ZOOM_MID_X, DEFAULT_ZOOM_MID_Y},
      {
              HypercosOverlay::NONE,
              ALL_OFF_AFTER_EFFECTS_STATES, RotationAdjustments{},
              },
  };

  static constexpr auto BASE_ZOOM_IN_COEFF_FACTOR =
      ZoomVectorEffects::RAW_BASE_ZOOM_IN_COEFF_FACTOR;

  SECTION("Zero Speed")
  {
    const auto coords = NormalizedCoords{1.0F, 1.0F};

    filterSettings.vitesse.SetVitesse(Vitesse::STOP_SPEED);
    REQUIRE(filterSettings.vitesse.GetRelativeSpeed() == Approx(0.0F));
    const auto baseZoomInCoeff     = GetZoomInCoeff(BASE_ZOOM_IN_COEFF_FACTOR, 0.0F);
    const auto zoomInFactor        = 1.0F - baseZoomInCoeff;
    const auto expectedZoomInPoint = zoomInFactor * coords;

    filterZoomVector.SetFilterSettings(filterSettings);
    REQUIRE(filterZoomVector.GetZoomInPoint(coords, coords).GetX() ==
            Approx(expectedZoomInPoint.GetX()));
    REQUIRE(filterZoomVector.GetZoomInPoint(coords, coords).GetY() ==
            Approx(expectedZoomInPoint.GetY()));
  }

  SECTION("Non-zero Speed")
  {
    const auto coords = NormalizedCoords{1.0F, 1.0F};

    for (auto i = 0; i < 2; ++i)
    {
      const auto reverseSpeed = 1 == i;
      filterSettings.vitesse.SetReverseVitesse(reverseSpeed);

      for (auto speedInc = 0U; speedInc <= Vitesse::MAXIMUM_SPEED; ++speedInc)
      {
        UNSCOPED_INFO("speedInc = " << speedInc);

        const auto intSpeed      = Vitesse::STOP_SPEED + speedInc;
        const auto relativeSpeed = GetRelativeSpeed(intSpeed, reverseSpeed);
        UNSCOPED_INFO("relativeSpeed = " << relativeSpeed);
        REQUIRE(-1.0F <= relativeSpeed);
        REQUIRE(relativeSpeed <= 1.0F);
        filterSettings.vitesse.SetVitesse(intSpeed);
        REQUIRE(filterSettings.vitesse.GetRelativeSpeed() == Approx(relativeSpeed));

        const auto baseZoomInCoeff     = GetZoomInCoeff(BASE_ZOOM_IN_COEFF_FACTOR, relativeSpeed);
        const auto zoomInFactor        = 1.0F - baseZoomInCoeff;
        const auto expectedZoomInPoint = NormalizedCoords{zoomInFactor, zoomInFactor};
        UNSCOPED_INFO("baseZoomInCoeff = " << baseZoomInCoeff);
        UNSCOPED_INFO("zoomInFactor = " << zoomInFactor);

        filterZoomVector.SetFilterSettings(filterSettings);
        const auto zoomInPoint = filterZoomVector.GetZoomInPoint(coords, coords);
        REQUIRE(zoomInPoint.GetX() == Approx(expectedZoomInPoint.GetX()));
        REQUIRE(zoomInPoint.GetY() == Approx(expectedZoomInPoint.GetY()));
      }
    }
  }
}

} // namespace GOOM::UNIT_TESTS
