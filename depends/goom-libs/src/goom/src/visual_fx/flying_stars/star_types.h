#pragma once

#include "color/color_data/color_map_enums.h"
#include "color/random_color_maps.h"
#include "color/random_color_maps_groups.h"
#include "goom_config.h"
#include "goom_plugin_info.h"
#include "point2d.h"
#include "utils/math/goom_rand_base.h"
#include "utils/propagate_const.h"

#include <memory>

namespace GOOM::VISUAL_FX::FLYING_STARS
{

class IStarType
{
public:
  IStarType(const PluginInfo& goomInfo, const UTILS::MATH::IGoomRand& goomRand) noexcept;
  IStarType(const IStarType&) noexcept                    = delete;
  IStarType(IStarType&&) noexcept                         = delete;
  virtual ~IStarType() noexcept                           = default;
  auto operator=(const IStarType&) noexcept -> IStarType& = delete;
  auto operator=(IStarType&&) noexcept -> IStarType&      = delete;

  struct SetupParams
  {
    Point2dInt startPos;
    float gravity;
    float sideWind;
    float vage;
    float nominalPathLength;
    float maxStarAge;
  };
  [[nodiscard]] virtual auto GetRandomizedSetupParams(float defaultPathLength) const noexcept
      -> SetupParams = 0;
  [[nodiscard]] virtual auto GetRandomizedStarPathAngle(const Point2dInt& startPos) const noexcept
      -> float = 0;

  [[nodiscard]] auto GetWeightedMainColorMaps() const noexcept -> const COLOR::RandomColorMaps&;
  [[nodiscard]] auto GetWeightedLowColorMaps() const noexcept -> const COLOR::RandomColorMaps&;
  auto SetWeightedMainColorMaps(
      std::shared_ptr<const COLOR::RandomColorMaps> weightedColorMaps) noexcept -> void;
  auto SetWeightedLowColorMaps(
      std::shared_ptr<const COLOR::RandomColorMaps> weightedColorMaps) noexcept -> void;

  [[nodiscard]] auto GetFixedMainColorMapName() const noexcept -> COLOR::COLOR_DATA::ColorMapName;
  [[nodiscard]] auto GetFixedLowColorMapName() const noexcept -> COLOR::COLOR_DATA::ColorMapName;
  auto UpdateFixedColorMapNames() noexcept -> void;

  auto SetZoomMidpoint(const Point2dInt& zoomMidpoint) noexcept -> void;
  auto UpdateWindAndGravity() noexcept -> void;

protected:
  static constexpr float MIN_MAX_STAR_AGE = 15.0F;
  static constexpr float MAX_MAX_STAR_AGE = 50.0F;

  [[nodiscard]] auto GetGoomInfo() const noexcept -> const PluginInfo& { return m_goomInfo; }
  [[nodiscard]] auto GetGoomRand() const noexcept -> const UTILS::MATH::IGoomRand&
  {
    return m_goomRand;
  }
  [[nodiscard]] auto GetZoomMidpoint() const noexcept -> Point2dInt { return m_zoomMidpoint; }
  [[nodiscard]] auto GetHalfWidth() const noexcept -> int32_t { return m_halfWidth; }
  [[nodiscard]] auto GetHalfHeight() const noexcept -> int32_t { return m_halfHeight; }
  [[nodiscard]] auto GetXMax() const noexcept -> float { return m_xMax; }
  [[nodiscard]] auto GetMinSideWind() const noexcept -> float { return m_minSideWind; }
  [[nodiscard]] auto GetMaxSideWind() const noexcept -> float { return m_maxSideWind; }
  [[nodiscard]] auto GetMinGravity() const noexcept -> float { return m_minGravity; }
  [[nodiscard]] auto GetMaxGravity() const noexcept -> float { return m_maxGravity; }

private:
  const PluginInfo& m_goomInfo;
  const UTILS::MATH::IGoomRand& m_goomRand;
  const int32_t m_halfWidth;
  const int32_t m_halfHeight;
  const float m_xMax;
  Point2dInt m_zoomMidpoint;

  std::shared_ptr<const COLOR::RandomColorMaps> m_weightedMainColorMaps{
      COLOR::RandomColorMapsGroups::MakeSharedAllMapsUnweighted(m_goomRand)};
  std::shared_ptr<const COLOR::RandomColorMaps> m_weightedLowColorMaps{
      COLOR::RandomColorMapsGroups::MakeSharedAllMapsUnweighted(m_goomRand)};
  COLOR::COLOR_DATA::ColorMapName m_fixedMainColorMapName = COLOR::COLOR_DATA::ColorMapName::_NULL;
  COLOR::COLOR_DATA::ColorMapName m_fixedLowColorMapName  = COLOR::COLOR_DATA::ColorMapName::_NULL;

  static constexpr float MIN_MIN_SIDE_WIND     = -0.10F;
  static constexpr float MAX_MIN_SIDE_WIND     = -0.01F;
  static constexpr float MIN_MAX_SIDE_WIND     = +0.01F;
  static constexpr float MAX_MAX_SIDE_WIND     = +0.10F;
  static constexpr float DEFAULT_MIN_SIDE_WIND = 0.0F;
  static constexpr float DEFAULT_MAX_SIDE_WIND = 0.00001F;
  float m_minSideWind                          = DEFAULT_MIN_SIDE_WIND;
  float m_maxSideWind                          = DEFAULT_MAX_SIDE_WIND;

  static constexpr float MIN_MIN_GRAVITY = +0.005F;
  static constexpr float MAX_MIN_GRAVITY = +0.010F;
  static constexpr float MIN_MAX_GRAVITY = +0.050F;
  static constexpr float MAX_MAX_GRAVITY = +0.090F;
  float m_minGravity                     = MAX_MIN_GRAVITY;
  float m_maxGravity                     = MAX_MAX_GRAVITY;
};

class FireworksStarType : public IStarType
{
public:
  using IStarType::IStarType;

  [[nodiscard]] auto GetRandomizedSetupParams(float defaultPathLength) const noexcept
      -> SetupParams override;
  [[nodiscard]] auto GetRandomizedStarPathAngle(const Point2dInt& startPos) const noexcept
      -> float override;
};

class RainStarType : public IStarType
{
public:
  using IStarType::IStarType;

  [[nodiscard]] auto GetRandomizedSetupParams(float defaultPathLength) const noexcept
      -> SetupParams override;
  [[nodiscard]] auto GetRandomizedStarPathAngle(const Point2dInt& startPos) const noexcept
      -> float override;
};

class FountainStarType : public IStarType
{
public:
  using IStarType::IStarType;

  [[nodiscard]] auto GetRandomizedSetupParams(float defaultPathLength) const noexcept
      -> SetupParams override;
  [[nodiscard]] auto GetRandomizedStarPathAngle(const Point2dInt& startPos) const noexcept
      -> float override;
};

class StarTypesContainer
{
public:
  static constexpr uint32_t NUM_STAR_TYPES = 3;

  StarTypesContainer(const PluginInfo& goomInfo, const UTILS::MATH::IGoomRand& goomRand) noexcept;

  [[nodiscard]] auto GetRandomStarType() noexcept -> IStarType*;

  auto SetWeightedMainColorMaps(
      uint32_t starTypeId, std::shared_ptr<const COLOR::RandomColorMaps> weightedColorMaps) noexcept
      -> void;
  auto SetWeightedLowColorMaps(
      uint32_t starTypeId, std::shared_ptr<const COLOR::RandomColorMaps> weightedColorMaps) noexcept
      -> void;

  [[nodiscard]] auto GetCurrentColorMapsNames() const noexcept -> std::vector<std::string>;

  auto SetZoomMidpoint(const Point2dInt& zoomMidpoint) noexcept -> void;

private:
  const PluginInfo& m_goomInfo;
  const UTILS::MATH::IGoomRand& m_goomRand;
  std::array<std::experimental::propagate_const<std::unique_ptr<IStarType>>, NUM_STAR_TYPES>
      m_starTypesList{
          std::make_unique<FireworksStarType>(m_goomInfo, m_goomRand),
          std::make_unique<RainStarType>(m_goomInfo, m_goomRand),
          std::make_unique<FountainStarType>(m_goomInfo, m_goomRand),
      };
  enum class AvailableStarTypes
  {
    FIREWORKS,
    RAIN,
    FOUNTAIN,
    _num // unused, and marks the enum end
  };
  static_assert(UTILS::NUM<AvailableStarTypes> == (NUM_STAR_TYPES));
  static constexpr float STAR_TYPES_FIREWORKS_WEIGHT = 10.0F;
  static constexpr float STAR_TYPES_FOUNTAIN_WEIGHT  = 07.0F;
  static constexpr float STAR_TYPES_RAIN_WEIGHT      = 07.0F;
  const UTILS::MATH::Weights<AvailableStarTypes> m_weightedStarTypes{
      m_goomRand,
      {
        {AvailableStarTypes::FIREWORKS, STAR_TYPES_FIREWORKS_WEIGHT},
        {AvailableStarTypes::FOUNTAIN, STAR_TYPES_FOUNTAIN_WEIGHT},
        {AvailableStarTypes::RAIN, STAR_TYPES_RAIN_WEIGHT},
        }
  };
};

inline auto IStarType::GetWeightedMainColorMaps() const noexcept -> const COLOR::RandomColorMaps&
{
  Expects(m_weightedMainColorMaps != nullptr);
  return *m_weightedMainColorMaps;
}

inline auto IStarType::GetWeightedLowColorMaps() const noexcept -> const COLOR::RandomColorMaps&
{
  Expects(m_weightedLowColorMaps != nullptr);
  return *m_weightedLowColorMaps;
}

inline auto IStarType::GetFixedMainColorMapName() const noexcept -> COLOR::COLOR_DATA::ColorMapName
{
  return m_fixedMainColorMapName;
}

inline auto IStarType::GetFixedLowColorMapName() const noexcept -> COLOR::COLOR_DATA::ColorMapName
{
  return m_fixedLowColorMapName;
}

inline auto IStarType::SetZoomMidpoint(const Point2dInt& zoomMidpoint) noexcept -> void
{
  m_zoomMidpoint = zoomMidpoint;
}

} //namespace GOOM::VISUAL_FX::FLYING_STARS
