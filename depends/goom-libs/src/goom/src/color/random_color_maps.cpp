#include "random_color_maps.h"

//#undef NO_LOGGING

#include "color_data/color_map_enums.h"
#include "color_maps.h"
#include "goom_graphic.h"
#include "logging.h"
#include "utils/enum_utils.h"
#include "utils/math/goom_rand_base.h"

#include <memory>
#include <set>

namespace GOOM::COLOR
{

using COLOR_DATA::ColorMapName;
using UTILS::Logging; // NOLINT(misc-unused-using-decls)
using UTILS::NUM;
using UTILS::MATH::IGoomRand;
using UTILS::MATH::Weights;

auto RandomColorMaps::GetRandomColorMapName() const noexcept -> COLOR_DATA::ColorMapName
{
  return static_cast<ColorMapName>(m_goomRand.GetRandInRange(0U, GetNumColorMapNames()));
}

auto RandomColorMaps::GetRandomColorMapName(const ColorMapGroup colorMapGroup) const noexcept
    -> COLOR_DATA::ColorMapName
{
  const auto& colorMapNames = GetColorMapNames(colorMapGroup);
  return colorMapNames[m_goomRand.GetRandInRange(0U, static_cast<uint32_t>(colorMapNames.size()))];
}

auto RandomColorMaps::GetRandomColorMap() const noexcept -> const IColorMap&
{
  return GetColorMap(GetRandomColorMapName());
}

auto RandomColorMaps::GetRandomColorMap(const ColorMapGroup colorMapGroup) const noexcept
    -> const IColorMap&
{
  return GetColorMap(GetRandomColorMapName(colorMapGroup));
}

auto RandomColorMaps::GetRandomColorMapPtr(const std::set<ColorMapTypes>& types) const noexcept
    -> std::shared_ptr<const IColorMap>
{
  return GetRandomColorMapPtr(GetColorMapPtr(GetRandomColorMapName()), types);
}

auto RandomColorMaps::GetRandomColorMapPtr(const COLOR_DATA::ColorMapName colorMapName,
                                           const std::set<ColorMapTypes>& types) const noexcept
    -> std::shared_ptr<const IColorMap>
{
  if (colorMapName == COLOR_DATA::ColorMapName::_NULL)
  {
    return GetRandomColorMapPtr(types);
  }
  return GetRandomColorMapPtr(GetColorMapPtr(colorMapName), types);
}

auto RandomColorMaps::GetRandomColorMapPtr(const ColorMapGroup colorMapGroup,
                                           const std::set<ColorMapTypes>& types) const noexcept
    -> std::shared_ptr<const IColorMap>
{
  return GetRandomColorMapPtr(GetColorMapPtr(GetRandomColorMapName(colorMapGroup)), types);
}

auto RandomColorMaps::GetRandomColorMapPtr(const std::shared_ptr<const IColorMap>& colorMap,
                                           const std::set<ColorMapTypes>& types) const noexcept
    -> std::shared_ptr<const IColorMap>
{
  if (types.empty())
  {
    return colorMap;
  }

  auto newColorMap = colorMap;

#if __cplusplus <= 201703L
  if (types.find(ColorMapTypes::ROTATED_T) != cend(types))
#else
  if (types.contains(ColorMapTypes::ROTATED_T))
#endif
  {
    newColorMap = GetRandomRotatedColorMapPtr(newColorMap);
  }
#if __cplusplus <= 201703L
  if (types.find(ColorMapTypes::SHADES) != cend(types))
#else
  if (types.contains(ColorMapTypes::SHADES))
#endif
  {
    newColorMap = GetRandomTintedColorMapPtr(newColorMap);
  }

  return newColorMap;
}

auto RandomColorMaps::GetRandomRotatedColorMapPtr() const noexcept
    -> std::shared_ptr<const IColorMap>
{
  return GetRotatedColorMapPtr(GetRandomColorMapName(),
                               m_goomRand.GetRandInRange(m_minRotationPoint, m_maxRotationPoint));
}

auto RandomColorMaps::GetRandomRotatedColorMapPtr(
    const COLOR_DATA::ColorMapName colorMapName) const noexcept -> std::shared_ptr<const IColorMap>
{
  return GetRotatedColorMapPtr(colorMapName,
                               m_goomRand.GetRandInRange(m_minRotationPoint, m_maxRotationPoint));
}

auto RandomColorMaps::GetRandomRotatedColorMapPtr(const ColorMapGroup colorMapGroup) const noexcept
    -> std::shared_ptr<const IColorMap>
{
  return GetRotatedColorMapPtr(GetRandomColorMapName(colorMapGroup),
                               m_goomRand.GetRandInRange(m_minRotationPoint, m_maxRotationPoint));
}

auto RandomColorMaps::GetRandomRotatedColorMapPtr(const std::shared_ptr<const IColorMap>& colorMap)
    const noexcept -> std::shared_ptr<const IColorMap>
{
  return GetRotatedColorMapPtr(colorMap,
                               m_goomRand.GetRandInRange(m_minRotationPoint, m_maxRotationPoint));
}

auto RandomColorMaps::GetRandomTintedColorMapPtr() const noexcept
    -> std::shared_ptr<const IColorMap>
{
  return GetTintedColorMapPtr(GetRandomColorMapName(),
                              m_goomRand.GetRandInRange(m_minSaturation, m_maxSaturation),
                              m_goomRand.GetRandInRange(m_minLightness, m_maxLightness));
}

auto RandomColorMaps::GetRandomTintedColorMapPtr(const ColorMapName colorMapName) const noexcept
    -> std::shared_ptr<const IColorMap>
{
  return GetTintedColorMapPtr(colorMapName,
                              m_goomRand.GetRandInRange(m_minSaturation, m_maxSaturation),
                              m_goomRand.GetRandInRange(m_minLightness, m_maxLightness));
}

auto RandomColorMaps::GetRandomTintedColorMapPtr(const ColorMapGroup colorMapGroup) const noexcept
    -> std::shared_ptr<const IColorMap>
{
  return GetTintedColorMapPtr(GetRandomColorMapName(colorMapGroup),
                              m_goomRand.GetRandInRange(m_minSaturation, m_maxSaturation),
                              m_goomRand.GetRandInRange(m_minLightness, m_maxLightness));
}

auto RandomColorMaps::GetRandomTintedColorMapPtr(const std::shared_ptr<const IColorMap>& colorMap)
    const noexcept -> std::shared_ptr<const IColorMap>
{
  return GetTintedColorMapPtr(colorMap,
                              m_goomRand.GetRandInRange(m_minSaturation, m_maxSaturation),
                              m_goomRand.GetRandInRange(m_minLightness, m_maxLightness));
}

auto RandomColorMaps::GetRandomGroup() const noexcept -> ColorMapGroup
{
  return static_cast<ColorMapGroup>(m_goomRand.GetRandInRange(0U, NUM<ColorMapGroup>));
}

auto RandomColorMaps::GetRandomColor(const IColorMap& colorMap,
                                     const float t0,
                                     const float t1) const noexcept -> Pixel
{
  return colorMap.GetColor(m_goomRand.GetRandInRange(t0, t1));
}

auto RandomColorMaps::GetMinRotationPoint() const noexcept -> float
{
  return m_minRotationPoint;
}

auto RandomColorMaps::GetMaxRotationPoint() const noexcept -> float
{
  return m_maxRotationPoint;
}

auto RandomColorMaps::SetRotationPointLimits(const float minRotationPoint,
                                             const float maxRotationPoint) noexcept -> void
{
  Expects(minRotationPoint >= MIN_ROTATION_POINT);
  Expects(maxRotationPoint <= MAX_ROTATION_POINT);
  Expects(minRotationPoint <= maxRotationPoint);

  m_minRotationPoint = minRotationPoint;
  m_maxRotationPoint = maxRotationPoint;
}

auto RandomColorMaps::GetMinSaturation() const noexcept -> float
{
  return m_minSaturation;
}

auto RandomColorMaps::GetMaxSaturation() const noexcept -> float
{
  return m_maxSaturation;
}

auto RandomColorMaps::SetSaturationLimits(const float minSaturation,
                                          const float maxSaturation) noexcept -> void
{
  Expects(minSaturation >= MIN_SATURATION);
  Expects(maxSaturation <= MAX_SATURATION);
  Expects(minSaturation <= maxSaturation);

  m_minSaturation = minSaturation;
  m_maxSaturation = maxSaturation;
}

auto RandomColorMaps::GetMinLightness() const noexcept -> float
{
  return m_minLightness;
}

auto RandomColorMaps::GetMaxLightness() const noexcept -> float
{
  return m_maxLightness;
}

auto RandomColorMaps::SetLightnessLimits(const float minLightness,
                                         const float maxLightness) noexcept -> void
{
  Expects(minLightness >= MIN_LIGHTNESS);
  Expects(maxLightness <= MAX_LIGHTNESS);
  Expects(minLightness <= maxLightness);

  m_minLightness = minLightness;
  m_maxLightness = maxLightness;
}

WeightedColorMaps::WeightedColorMaps(const IGoomRand& goomRand,
                                     const Weights<ColorMapGroup>& weights,
                                     const std::string& colorMapsName) noexcept
  : RandomColorMaps{goomRand, colorMapsName}, m_weights{weights}
{
}

auto WeightedColorMaps::GetRandomGroup() const noexcept -> ColorMapGroup
{
  if (not m_weightsActive)
  {
    return RandomColorMaps::GetRandomGroup();
  }

  return m_weights.GetRandomWeighted();
}

auto WeightedColorMaps::GetRandomColorMapName() const noexcept -> COLOR_DATA::ColorMapName
{
  return RandomColorMaps::GetRandomColorMapName(GetRandomGroup());
}

} // namespace GOOM::COLOR
