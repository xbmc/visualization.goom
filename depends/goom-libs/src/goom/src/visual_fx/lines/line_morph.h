#pragma once

#include "../fx_utils/dot_drawer.h"
#include "../fx_utils/lines.h"
#include "color/color_adjustment.h"
#include "color/color_maps.h"
#include "color/random_color_maps.h"
#include "color/random_color_maps_groups.h"
#include "color/random_color_maps_manager.h"
#include "draw/goom_draw.h"
#include "goom_config.h"
#include "goom_graphic.h"
#include "goom_plugin_info.h"
#include "line_types.h"
#include "point2d.h"
#include "sound_info.h"
#include "utils/graphics/small_image_bitmaps.h"
#include "utils/math/goom_rand_base.h"

#include <cstdint>
#include <memory>
#include <vector>

namespace GOOM::VISUAL_FX::LINES
{

class LineMorph
{
public:
  static constexpr uint32_t MIN_LINE_DURATION = 80;

  // construit un effet de line (une ligne horitontale pour commencer)
  // builds a line effect (a horizontal line to start with)
  LineMorph() noexcept = delete;

  LineMorph(DRAW::IGoomDraw& draw,
            const PluginInfo& goomInfo,
            const UTILS::MATH::IGoomRand& goomRand,
            const UTILS::GRAPHICS::SmallImageBitmaps& smallBitmaps,
            const LineParams& srceLineParams,
            const LineParams& destLineParams) noexcept;

  [[nodiscard]] auto GetCurrentColorMapsNames() const noexcept -> std::vector<std::string>;
  auto SetWeightedColorMaps(std::shared_ptr<const COLOR::RandomColorMaps> weightedMaps) noexcept
      -> void;

  auto Start() noexcept -> void;

  [[nodiscard]] auto GetLineColorPower() const noexcept -> float;
  auto SetLineColorPower(float val) noexcept -> void;

  [[nodiscard]] auto CanResetDestLine() const noexcept -> bool;
  auto ResetDestLine(const LineParams& newParams) noexcept -> void;

  auto DrawLines(const AudioSamples::SampleArray& soundData,
                 const AudioSamples::MinMaxValues& soundMinMax) noexcept -> void;

  [[nodiscard]] auto GetRandomLineColor() const noexcept -> Pixel;

private:
  DRAW::IGoomDraw& m_draw;
  const PluginInfo& m_goomInfo;
  const UTILS::MATH::IGoomRand& m_goomRand;

  std::shared_ptr<const COLOR::RandomColorMaps> m_colorMaps{
      COLOR::RandomColorMapsGroups::MakeSharedAllMapsUnweighted(m_goomRand)};
  COLOR::RandomColorMapsManager m_colorMapsManager{};
  COLOR::RandomColorMapsManager::ColorMapId m_currentColorMapID{
      m_colorMapsManager.AddDefaultColorMapInfo(m_goomRand)};
  float m_currentBrightness = 1.0F;

  static constexpr float GAMMA = 1.0F / 2.0F;
  const COLOR::ColorAdjustment m_colorAdjust{GAMMA,
                                             COLOR::ColorAdjustment::INCREASED_CHROMA_FACTOR};

  std::vector<FX_UTILS::LinePoint> m_srcePoints;
  std::vector<FX_UTILS::LinePoint> m_srcePointsCopy;
  LineParams m_srceLineParams;

  std::vector<FX_UTILS::LinePoint> m_destPoints;
  LineParams m_destLineParams;

  static constexpr float LINE_LERP_FINISHED_VAL = 1.1F;
  static constexpr float LINE_LERP_INC          = 1.0F / static_cast<float>(MIN_LINE_DURATION - 1);
  float m_lineLerpParam                         = 0.0F;
  auto MoveSrceLineCloserToDest() noexcept -> void;
  [[nodiscard]] auto GetFreshLine(LineType lineType, float lineParam) const noexcept
      -> std::vector<FX_UTILS::LinePoint>;

  // pour l'instant je stocke la couleur a terme, on stockera le mode couleur et l'on animera
  bool m_useLineColor             = true;
  float m_lineColorPower          = 0.0F;
  float m_lineColorPowerIncrement = 0.0F;
  [[nodiscard]] auto GetRandomColorMap() const noexcept -> const COLOR::IColorMap&;
  [[nodiscard]] auto GetFinalLineColor(const Pixel& color) const noexcept -> Pixel;
  auto UpdateColorInfo() noexcept -> void;

  // This factor gives the maximum height to the peaks of the audio samples lines.
  // This value seems pleasing.
  static constexpr float MIN_MAX_NORMALIZED_PEAK = 100.0F;
  static constexpr float MAX_MAX_NORMALIZED_PEAK = 400.0F;
  float m_maxNormalizedPeak                      = MIN_MAX_NORMALIZED_PEAK;

  FX_UTILS::DotDrawer m_dotDrawer;
  float m_audioRange    = 0.0F;
  float m_minAudioValue = 0.0F;
  struct PointAndColor
  {
    Point2dInt point;
    Pixel color;
  };
  [[nodiscard]] auto GetAudioPoints(const Pixel& lineColor,
                                    const AudioSamples::SampleArray& audioData) const noexcept
      -> std::vector<PointAndColor>;
  [[nodiscard]] auto GetNextPointData(const FX_UTILS::LinePoint& linePoint,
                                      const Pixel& mainColor,
                                      const Pixel& randColor,
                                      float dataVal) const noexcept -> PointAndColor;

  [[nodiscard]] auto GetMainColor(const Pixel& lineColor, float t) const noexcept -> Pixel;
  auto DrawFlatLine(const Pixel& lineColor) noexcept -> void;
};

inline auto LineMorph::GetLineColorPower() const noexcept -> float
{
  return m_lineColorPower;
}

inline auto LineMorph::SetLineColorPower(const float val) noexcept -> void
{
  m_lineColorPower = val;
}

inline auto LineMorph::CanResetDestLine() const noexcept -> bool
{
  return m_lineLerpParam > LINE_LERP_FINISHED_VAL;
}

} // namespace GOOM::VISUAL_FX::LINES
