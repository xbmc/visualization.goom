#pragma once

#include "bitmap_getter_base.h"
#include "color/color_adjustment.h"
#include "color/color_maps.h"
#include "color/color_maps_grids.h"
#include "color/random_color_maps.h"
#include "dot_diameters.h"
#include "dot_paths.h"
#include "draw/goom_draw.h"
#include "goom_graphic.h"
#include "goom_plugin_info.h"
#include "point2d.h"
#include "utils/math/goom_rand_base.h"
#include "utils/math/misc.h"
#include "utils/math/paths.h"
#include "utils/propagate_const.h"
#include "utils/t_values.h"
#include "utils/timer.h"
#include "visual_fx/fx_helper.h"

#include <cmath>
#include <cstdint>
#include <memory>
#include <vector>

namespace GOOM::VISUAL_FX::CIRCLES
{

class Circle
{
public:
  struct Helper
  {
    uint32_t lineDotDiameter;
    uint32_t minDotDiameter;
    uint32_t maxDotDiameter;
    const IBitmapGetter& bitmapGetter;
  };
  struct OneWayParams
  {
    float circleRadius;
    Point2dInt circleCentreStart;
    Point2dInt circleCentreTarget;
  };
  struct Params
  {
    OneWayParams toTargetParams;
    OneWayParams fromTargetParams;
  };

  Circle() = delete;
  Circle(const FxHelper& fxHelper,
         const Helper& helper,
         const Params& circleParams,
         const UTILS::MATH::OscillatingFunction::Params& pathParams) noexcept;
  Circle(const Circle&) = delete;
  Circle(Circle&& other) noexcept;
  ~Circle() noexcept;
  auto operator=(const Circle&) -> Circle& = delete;
  auto operator=(Circle&&) -> Circle&      = delete;

  auto SetWeightedColorMaps(std::shared_ptr<const COLOR::RandomColorMaps> weightedMainMaps,
                            std::shared_ptr<const COLOR::RandomColorMaps> weightedLowMaps) noexcept
      -> void;
  auto SetPathParams(const UTILS::MATH::OscillatingFunction::Params& pathParams) noexcept -> void;
  [[nodiscard]] auto GetCurrentDirection() const noexcept -> DotPaths::Direction;
  auto ChangeDirection(DotPaths::Direction newDirection) noexcept -> void;
  auto SetGlobalBrightnessFactor(float val) noexcept -> void;

  auto Start() noexcept -> void;
  auto UpdatePositionSpeed(uint32_t newNumSteps) noexcept -> void;
  auto UpdateAndDraw() noexcept -> void;
  auto IncrementTs() noexcept -> void;

  [[nodiscard]] auto HasPositionTJustHitABoundary() const noexcept -> bool;
  [[nodiscard]] auto HasPositionTJustHitStartBoundary() const noexcept -> bool;
  [[nodiscard]] auto HasPositionTJustHitEndBoundary() const noexcept -> bool;
  [[nodiscard]] auto GetLastDrawnCircleDots() const noexcept -> const std::vector<Point2dInt>&;

private:
  DRAW::IGoomDraw& m_draw;
  const PluginInfo& m_goomInfo;
  const UTILS::MATH::IGoomRand& m_goomRand;
  const Helper m_helper;

  DotPaths m_dotPaths;
  DotDiameters m_dotDiameters{
      m_goomRand, NUM_DOTS, m_helper.minDotDiameter, m_helper.maxDotDiameter};
  [[nodiscard]] static auto GetDotStartingPositions(const Point2dInt& centre, float radius) noexcept
      -> std::vector<Point2dInt>;

  uint64_t m_updateNum       = 0;
  uint32_t m_dotRotateOffset = 0;
  [[nodiscard]] auto IsSpecialUpdateNum() const noexcept -> bool;
  [[nodiscard]] auto IsSpecialLineUpdateNum() const noexcept -> bool;

  auto UpdateTime() noexcept -> void;
  auto ResetNumSteps() noexcept -> void;

  static constexpr uint32_t NUM_DOTS = 30;
  static_assert(UTILS::MATH::IsEven(NUM_DOTS));
  std::vector<Point2dInt> m_lastDrawnDots{NUM_DOTS};
  uint32_t m_newNumSteps = 0;

  auto DrawNextCircle() noexcept -> void;
  auto DrawNextCircleDots() noexcept -> void;

  static constexpr float GAMMA = 1.0F;
  const COLOR::ColorAdjustment m_colorAdjustment{GAMMA,
                                                 COLOR::ColorAdjustment::INCREASED_CHROMA_FACTOR};

  float m_globalBrightnessFactor = 1.0F;
  [[nodiscard]] auto GetCurrentBrightness() const noexcept -> float;
  [[nodiscard]] auto GetDotBrightness(float brightness) const noexcept -> float;
  [[nodiscard]] auto GetLineBrightness(float brightness) const noexcept -> float;

  class DotDrawer;
  std::experimental::propagate_const<std::unique_ptr<DotDrawer>> m_dotDrawer;
  bool m_alternateMainLowDotColors         = false;
  bool m_showLine                          = false;
  static constexpr float T_LINE_COLOR_STEP = 1.0F / static_cast<float>(NUM_DOTS);
  auto DrawLine(const Point2dInt& position1,
                const Point2dInt& position2,
                float lineBrightness,
                float tLineColor) noexcept -> void;
  [[nodiscard]] auto DrawLineDots(float lineBrightness,
                                  const Point2dInt& position1,
                                  const Point2dInt& position2,
                                  float tLineColor) noexcept -> float;
  auto DrawDot(uint32_t dotNum, const Point2dInt& pos, const DRAW::MultiplePixels& colors) noexcept
      -> void;
  auto DrawConnectingLine(const Point2dInt& position1,
                          const Point2dInt& position2,
                          float lineBrightness,
                          float tDotColor) noexcept -> void;

  std::shared_ptr<const COLOR::RandomColorMaps> m_mainColorMaps;
  std::shared_ptr<const COLOR::RandomColorMaps> m_lowColorMaps;
  const COLOR::IColorMap* m_linesMainColorMap{};
  const COLOR::IColorMap* m_linesLowColorMap{};
  uint32_t m_numRotatingColors = 0;
  std::vector<const COLOR::IColorMap*> m_rotatingMainColorMaps{};
  std::vector<const COLOR::IColorMap*> m_rotatingLowColorMaps{};
  std::vector<uint32_t> m_rotatingDotNums{};
  static constexpr uint32_t NUM_ROTATING_COLOR_STEPS = 100U;
  UTILS::TValue m_rotatingColorsT{UTILS::TValue::StepType::CONTINUOUS_REVERSIBLE,
                                  NUM_ROTATING_COLOR_STEPS};
  auto UpdateRotatingColorMaps() noexcept -> void;

  enum class GridColorRange
  {
    ONE,
    LOW,
    MEDIUM,
    HIGH,
    _num // unused, and marks the enum end
  };
  GridColorRange m_currentGridColorRange = GridColorRange::ONE;
  const GOOM::UTILS::MATH::Weights<GridColorRange> m_weightedGridColorRanges;
  uint32_t m_numDifferentGridMaps                 = 1U;
  COLOR::ColorMapsGrid m_mainColorMapsGrid        = GetMainColorMapsGrid();
  COLOR::ColorMapsGrid m_lowColorMapsGrid         = GetLowColorMapsGrid();
  static constexpr float DEFAULT_COLOR_GRID_MIX_T = 0.5F;
  float m_currentColorGridMixT                    = DEFAULT_COLOR_GRID_MIX_T;
  auto UpdateNumDifferentGridMaps() noexcept -> void;
  [[nodiscard]] auto GetMainColorMapsGrid() const noexcept -> COLOR::ColorMapsGrid;
  [[nodiscard]] auto GetLowColorMapsGrid() const noexcept -> COLOR::ColorMapsGrid;
  [[nodiscard]] auto GetHorizontalMainColorMaps() const noexcept
      -> std::vector<const COLOR::IColorMap*>;
  [[nodiscard]] auto GetVerticalMainColorMaps() const noexcept
      -> std::vector<const COLOR::IColorMap*>;
  [[nodiscard]] auto GetHorizontalLowColorMaps() const noexcept
      -> std::vector<const COLOR::IColorMap*>;
  [[nodiscard]] auto GetVerticalLowColorMaps() const noexcept
      -> std::vector<const COLOR::IColorMap*>;
  [[nodiscard]] auto GetAllDotColorMaps(const COLOR::RandomColorMaps& baseRandomColorMaps)
      const noexcept -> std::vector<const COLOR::IColorMap*>;

  [[nodiscard]] auto GetColorMixT(float tX, float tY) const noexcept -> float;
  struct AllDotColors
  {
    std::vector<Pixel> mainColors;
    std::vector<Pixel> lowColors;
  };
  [[nodiscard]] auto GetAllDotColors() const noexcept -> AllDotColors;
  [[nodiscard]] auto GetSingleDotColors(uint32_t dotNum,
                                        const AllDotColors& allDotColors,
                                        float dotBrightness) const noexcept -> DRAW::MultiplePixels;
  [[nodiscard]] auto GetCorrectedColor(float brightness, const Pixel& color) const noexcept
      -> Pixel;
};

inline auto Circle::IncrementTs() noexcept -> void
{
  m_dotPaths.IncrementPositionT();

  if (m_dotPaths.HasUpdatedDotPathsToAndFrom())
  {
    m_mainColorMapsGrid.SetVerticalT(m_dotPaths.GetPositionTRef());
    m_lowColorMapsGrid.SetVerticalT(m_dotPaths.GetPositionTRef());
    m_dotPaths.ResetUpdatedDotPathsToAndFromFlag();
  }
}

inline auto Circle::UpdatePositionSpeed(const uint32_t newNumSteps) noexcept -> void
{
  m_newNumSteps = newNumSteps;
}

inline auto Circle::GetCurrentDirection() const noexcept -> DotPaths::Direction
{
  return m_dotPaths.GetCurrentDirection();
}

inline auto Circle::ChangeDirection(const DotPaths::Direction newDirection) noexcept -> void
{
  m_dotPaths.ChangeDirection(newDirection);
}

inline auto Circle::HasPositionTJustHitABoundary() const noexcept -> bool
{
  return m_dotPaths.HasPositionTJustHitStartBoundary() or
         m_dotPaths.HasPositionTJustHitEndBoundary();
}

inline auto Circle::HasPositionTJustHitStartBoundary() const noexcept -> bool
{
  return m_dotPaths.HasPositionTJustHitStartBoundary();
}

inline auto Circle::HasPositionTJustHitEndBoundary() const noexcept -> bool
{
  return m_dotPaths.HasPositionTJustHitEndBoundary();
}

inline auto Circle::GetLastDrawnCircleDots() const noexcept -> const std::vector<Point2dInt>&
{
  return m_lastDrawnDots;
}

} // namespace GOOM::VISUAL_FX::CIRCLES
