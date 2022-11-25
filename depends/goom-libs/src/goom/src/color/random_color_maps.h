#pragma once

#include "color/color_data/color_map_enums.h"
#include "color/color_maps.h"
#include "goom_graphic.h"
#include "utils/math/goom_rand_base.h"

#include <memory>
#include <set>
#include <string>

namespace GOOM::COLOR
{

class RandomColorMaps : public ColorMaps
{
public:
  explicit RandomColorMaps(const UTILS::MATH::IGoomRand& goomRand,
                           const std::string& colorMapsName = "") noexcept;

  [[nodiscard]] auto GetColorMapsName() const noexcept -> const std::string&;

  [[nodiscard]] virtual auto GetRandomColorMapName() const noexcept -> COLOR_DATA::ColorMapName;
  [[nodiscard]] auto GetRandomColorMap() const noexcept -> const IColorMap&;
  [[nodiscard]] static auto GetRandomColorMap(const UTILS::MATH::IGoomRand& goomRand) noexcept
      -> const IColorMap&;
  [[nodiscard]] auto GetRandomColorMap(ColorMapGroup colorMapGroup) const noexcept
      -> const IColorMap&;
  [[nodiscard]] static auto GetRandomColorMap(const UTILS::MATH::IGoomRand& goomRand,
                                              ColorMapGroup colorMapGroup) noexcept
      -> const IColorMap&;

  enum class ColorMapTypes
  {
    ROTATED_T,
    SHADES,
  };
  static inline const std::set<ColorMapTypes> NO_COLOR_MAP_TYPES{};
  static inline const std::set<ColorMapTypes> ALL_COLOR_MAP_TYPES{
      ColorMapTypes::ROTATED_T,
      ColorMapTypes::SHADES,
  };
  [[nodiscard]] auto GetRandomColorMapPtr(const std::set<ColorMapTypes>& types) const noexcept
      -> std::shared_ptr<const IColorMap>;
  [[nodiscard]] auto GetRandomColorMapPtr(COLOR_DATA::ColorMapName colorMapName,
                                          const std::set<ColorMapTypes>& types) const noexcept
      -> std::shared_ptr<const IColorMap>;
  [[nodiscard]] auto GetRandomColorMapPtr(ColorMapGroup colorMapGroup,
                                          const std::set<ColorMapTypes>& types) const noexcept
      -> std::shared_ptr<const IColorMap>;
  [[nodiscard]] auto GetRandomColorMapPtr(const std::shared_ptr<const IColorMap>& colorMap,
                                          const std::set<ColorMapTypes>& types) const noexcept
      -> std::shared_ptr<const IColorMap>;

  [[nodiscard]] auto GetMinRotationPoint() const noexcept -> float;
  [[nodiscard]] auto GetMaxRotationPoint() const noexcept -> float;
  auto SetRotationPointLimits(float minRotationPoint, float maxRotationPoint) noexcept -> void;

  [[nodiscard]] auto GetRandomRotatedColorMapPtr() const noexcept
      -> std::shared_ptr<const IColorMap>;
  [[nodiscard]] auto GetRandomRotatedColorMapPtr(
      COLOR_DATA::ColorMapName colorMapName) const noexcept -> std::shared_ptr<const IColorMap>;
  [[nodiscard]] auto GetRandomRotatedColorMapPtr(ColorMapGroup colorMapGroup) const noexcept
      -> std::shared_ptr<const IColorMap>;
  [[nodiscard]] auto GetRandomRotatedColorMapPtr(const std::shared_ptr<const IColorMap>& colorMap)
      const noexcept -> std::shared_ptr<const IColorMap>;

  [[nodiscard]] auto GetMinSaturation() const noexcept -> float;
  [[nodiscard]] auto GetMaxSaturation() const noexcept -> float;
  auto SetSaturationLimits(float minSaturation, float maxSaturation) noexcept -> void;
  [[nodiscard]] auto GetMaxLightness() const noexcept -> float;
  [[nodiscard]] auto GetMinLightness() const noexcept -> float;
  auto SetLightnessLimits(float minLightness, float maxLightness) noexcept -> void;

  [[nodiscard]] auto GetRandomTintedColorMapPtr() const noexcept
      -> std::shared_ptr<const IColorMap>;
  [[nodiscard]] auto GetRandomTintedColorMapPtr(
      COLOR_DATA::ColorMapName colorMapName) const noexcept -> std::shared_ptr<const IColorMap>;
  [[nodiscard]] auto GetRandomTintedColorMapPtr(ColorMapGroup colorMapGroup) const noexcept
      -> std::shared_ptr<const IColorMap>;
  [[nodiscard]] auto GetRandomTintedColorMapPtr(const std::shared_ptr<const IColorMap>& colorMap)
      const noexcept -> std::shared_ptr<const IColorMap>;

  [[nodiscard]] virtual auto GetRandomGroup() const noexcept -> ColorMapGroup;

  [[nodiscard]] auto GetRandomColor(const IColorMap& colorMap, float t0, float t1) const noexcept
      -> Pixel;
  [[nodiscard]] static auto GetRandomColor(const UTILS::MATH::IGoomRand& goomRand,
                                           const IColorMap& colorMap,
                                           float t0,
                                           float t1) noexcept -> Pixel;

protected:
  [[nodiscard]] auto GetRandomColorMapName(ColorMapGroup colorMapGroup) const noexcept
      -> COLOR_DATA::ColorMapName;

private:
  const UTILS::MATH::IGoomRand& m_goomRand;
  const std::string m_colorMapsName;
  static constexpr float MIN_ROTATION_POINT = 0.5F;
  static constexpr float MAX_ROTATION_POINT = 0.9F;
  float m_minRotationPoint                  = MIN_ROTATION_POINT;
  float m_maxRotationPoint                  = MAX_ROTATION_POINT;

  static constexpr float MIN_SATURATION = 0.5F;
  static constexpr float MAX_SATURATION = 1.0F;
  static constexpr float MIN_LIGHTNESS  = 0.5F;
  static constexpr float MAX_LIGHTNESS  = 1.0F;
  float m_minSaturation                 = MIN_SATURATION;
  float m_maxSaturation                 = MAX_SATURATION;
  float m_minLightness                  = MIN_LIGHTNESS;
  float m_maxLightness                  = MAX_LIGHTNESS;
};

class WeightedColorMaps : public RandomColorMaps
{
public:
  WeightedColorMaps(const UTILS::MATH::IGoomRand& goomRand,
                    const UTILS::MATH::Weights<ColorMapGroup>& weights,
                    const std::string& colorMapsName = "") noexcept;

  [[nodiscard]] auto GetRandomGroup() const noexcept -> ColorMapGroup override;
  [[nodiscard]] auto GetRandomColorMapName() const noexcept -> COLOR_DATA::ColorMapName override;

private:
  UTILS::MATH::Weights<ColorMapGroup> m_weights;
  bool m_weightsActive = true;
};

inline RandomColorMaps::RandomColorMaps(const UTILS::MATH::IGoomRand& goomRand,
                                        const std::string& colorMapsName) noexcept
  : m_goomRand{goomRand}, m_colorMapsName{colorMapsName}
{
}

inline auto RandomColorMaps::GetColorMapsName() const noexcept -> const std::string&
{
  return m_colorMapsName;
}

inline auto RandomColorMaps::GetRandomColorMap(const UTILS::MATH::IGoomRand& goomRand) noexcept
    -> const IColorMap&
{
  return RandomColorMaps{goomRand}.GetRandomColorMap();
}

inline auto RandomColorMaps::GetRandomColorMap(const UTILS::MATH::IGoomRand& goomRand,
                                               ColorMapGroup colorMapGroup) noexcept
    -> const IColorMap&
{
  return RandomColorMaps{goomRand}.GetRandomColorMap(colorMapGroup);
}

inline auto RandomColorMaps::GetRandomColor(const UTILS::MATH::IGoomRand& goomRand,
                                            const IColorMap& colorMap,
                                            float t0,
                                            float t1) noexcept -> Pixel
{
  return RandomColorMaps{goomRand}.GetRandomColor(colorMap, t0, t1);
}

} // namespace GOOM::COLOR
