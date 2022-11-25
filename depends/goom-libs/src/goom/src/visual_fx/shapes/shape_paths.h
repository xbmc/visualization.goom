#pragma once

#include "color/color_adjustment.h"
#include "color/random_color_maps_manager.h"
#include "draw/goom_draw.h"
#include "goom_graphic.h"
#include "point2d.h"
#include "utils/math/paths.h"
#include "utils/propagate_const.h"

#include <memory>

namespace GOOM::VISUAL_FX::SHAPES
{

class ShapePath
{
public:
  struct ColorInfo
  {
    COLOR::RandomColorMapsManager::ColorMapId mainColorMapId{};
    COLOR::RandomColorMapsManager::ColorMapId lowColorMapId{};
    COLOR::RandomColorMapsManager::ColorMapId innerColorMapId{};
    float chromaFactor = 1.0F;
  };
  ShapePath(DRAW::IGoomDraw& draw,
            std::shared_ptr<UTILS::MATH::IPath> path,
            COLOR::RandomColorMapsManager& colorMapsManager,
            ColorInfo colorInfo) noexcept;

  auto UpdateMainColorInfo(
      const std::shared_ptr<const COLOR::RandomColorMaps>& mainColorMaps) noexcept -> void;
  auto UpdateLowColorInfo(
      const std::shared_ptr<const COLOR::RandomColorMaps>& lowColorMaps) noexcept -> void;
  auto UpdateInnerColorInfo(
      const std::shared_ptr<const COLOR::RandomColorMaps>& innerColorMaps) noexcept -> void;
  auto SetChromaFactor(float val) noexcept -> void;

  auto SetNumSteps(uint32_t val) noexcept -> void;
  auto IncrementT() noexcept -> void;
  auto ResetT(float val) noexcept -> void;
  [[nodiscard]] auto HasJustHitStartBoundary() const noexcept -> bool;
  [[nodiscard]] auto HasJustHitEndBoundary() const noexcept -> bool;
  [[nodiscard]] auto HasJustHitAnyBoundary() const noexcept -> bool;
  [[nodiscard]] auto GetNextPoint() const noexcept -> Point2dInt;
  [[nodiscard]] auto GetColorInfo() const noexcept -> const ColorInfo&;
  [[nodiscard]] auto GetCurrentT() const noexcept -> float;

  [[nodiscard]] auto GetIPath() const noexcept -> const UTILS::MATH::IPath&;
  [[nodiscard]] auto GetIPath() noexcept -> UTILS::MATH::IPath&;

  struct ShapePathColors
  {
    Pixel mainColor;
    Pixel lowColor;
  };
  struct DrawParams
  {
    float brightnessAttenuation;
    bool firstShapePathAtMeetingPoint;
    int32_t maxRadius;
    float innerColorMix;
    ShapePathColors meetingPointColors;
  };
  auto Draw(const DrawParams& drawParams) noexcept -> void;

private:
  DRAW::IGoomDraw& m_draw;
  std::experimental::propagate_const<std::shared_ptr<UTILS::MATH::IPath>> m_path;
  COLOR::RandomColorMapsManager& m_colorMapsManager;

  ColorInfo m_colorInfo;
  static inline const std::set<COLOR::RandomColorMaps::ColorMapTypes> COLOR_MAP_TYPES =
      COLOR::RandomColorMaps::ALL_COLOR_MAP_TYPES;

  [[nodiscard]] static auto GetInnerColorCutoffRadius(int32_t maxRadius) noexcept -> int32_t;
  [[nodiscard]] auto GetCurrentShapeColors() const noexcept -> ShapePathColors;
  [[nodiscard]] auto GetColors(const DrawParams& drawParams,
                               int32_t radius,
                               float brightness,
                               const ShapePathColors& shapeColors,
                               int32_t innerColorCutoffRadius,
                               const Pixel& innerColor) const noexcept -> DRAW::MultiplePixels;
  [[nodiscard]] auto GetColorsWithoutInner(float brightness,
                                           const ShapePathColors& shapeColors) const noexcept
      -> DRAW::MultiplePixels;
  [[nodiscard]] auto GetColorsWithInner(float brightness,
                                        const ShapePathColors& shapeColors,
                                        const Pixel& innerColor,
                                        float innerColorMix) const noexcept -> DRAW::MultiplePixels;
  [[nodiscard]] auto GetFinalMeetingPointColors(const ShapePathColors& meetingPointColors,
                                                float brightness) const noexcept
      -> DRAW::MultiplePixels;

  static constexpr float GAMMA = 1.3F;
  COLOR::ColorAdjustment m_colorAdjust{GAMMA, COLOR::ColorAdjustment::INCREASED_CHROMA_FACTOR};
};

inline auto ShapePath::SetNumSteps(const uint32_t val) noexcept -> void
{
  m_path->SetNumSteps(val);
}

inline auto ShapePath::IncrementT() noexcept -> void
{
  m_path->IncrementT();
}

inline auto ShapePath::ResetT(const float val) noexcept -> void
{
  m_path->Reset(val);
}

inline auto ShapePath::HasJustHitStartBoundary() const noexcept -> bool
{
  return m_path->GetPositionT().HasJustHitStartBoundary();
}

inline auto ShapePath::HasJustHitEndBoundary() const noexcept -> bool
{
  return m_path->GetPositionT().HasJustHitEndBoundary();
}

inline auto ShapePath::HasJustHitAnyBoundary() const noexcept -> bool
{
  return HasJustHitStartBoundary() || HasJustHitEndBoundary();
}

inline auto ShapePath::GetNextPoint() const noexcept -> Point2dInt
{
  return m_path->GetNextPoint();
}

inline auto ShapePath::GetCurrentT() const noexcept -> float
{
  return m_path->GetPositionT()();
}

inline auto ShapePath::GetIPath() const noexcept -> const UTILS::MATH::IPath&
{
  return *m_path;
}

inline auto ShapePath::GetIPath() noexcept -> UTILS::MATH::IPath&
{
  return *m_path;
}

inline auto ShapePath::GetColorInfo() const noexcept -> const ColorInfo&
{
  return m_colorInfo;
}

inline auto ShapePath::UpdateMainColorInfo(
    const std::shared_ptr<const COLOR::RandomColorMaps>& mainColorMaps) noexcept -> void
{
  m_colorMapsManager.UpdateColorMapInfo(m_colorInfo.mainColorMapId,
                                        {mainColorMaps, COLOR_MAP_TYPES});
}

inline auto ShapePath::UpdateLowColorInfo(
    const std::shared_ptr<const COLOR::RandomColorMaps>& lowColorMaps) noexcept -> void
{
  m_colorMapsManager.UpdateColorMapInfo(m_colorInfo.lowColorMapId, {lowColorMaps, COLOR_MAP_TYPES});
}

inline auto ShapePath::UpdateInnerColorInfo(
    const std::shared_ptr<const COLOR::RandomColorMaps>& innerColorMaps) noexcept -> void
{
  m_colorMapsManager.UpdateColorMapInfo(m_colorInfo.innerColorMapId,
                                        {innerColorMaps, COLOR_MAP_TYPES});
}

inline auto ShapePath::SetChromaFactor(const float val) noexcept -> void
{
  m_colorInfo.chromaFactor = val;
}

} // namespace GOOM::VISUAL_FX::SHAPES
