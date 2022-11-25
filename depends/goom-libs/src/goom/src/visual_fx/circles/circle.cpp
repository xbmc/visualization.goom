#include "circle.h"

//#undef NO_LOGGING

#include "color/color_maps.h"
#include "color/color_utils.h"
#include "color/random_color_maps.h"
#include "color/random_color_maps_groups.h"
#include "draw/goom_draw.h"
#include "goom_config.h"
#include "goom_graphic.h"
#include "logging.h"
#include "point2d.h"
#include "utils/enum_utils.h"
#include "utils/math/goom_rand_base.h"
#include "utils/math/misc.h"
#include "utils/math/paths.h"
#include "utils/t_values.h"

#include <cmath>
#include <cstdint>
#include <memory>
#include <vector>

namespace GOOM::VISUAL_FX::CIRCLES
{

using COLOR::GetBrighterColor;
using COLOR::IColorMap;
using COLOR::RandomColorMaps;
using COLOR::RandomColorMapsGroups;
using DRAW::GetLowColor;
using DRAW::GetMainColor;
using DRAW::IGoomDraw;
using DRAW::MultiplePixels;
using DRAW::ReversePixels;
using UTILS::EnumMap;
using UTILS::Logging; // NOLINT(misc-unused-using-decls)
using UTILS::NUM;
using UTILS::TValue;
using UTILS::MATH::AngleParams;
using UTILS::MATH::CirclePath;
using UTILS::MATH::IGoomRand;
using UTILS::MATH::ModIncrement;
using UTILS::MATH::OscillatingFunction;
using UTILS::MATH::U_HALF;

static constexpr auto DOT_MAIN_COLOR_BRIGHTNESS_FACTOR      = 0.1F;
static constexpr auto DOT_LOW_COLOR_BRIGHTNESS_FACTOR       = 2.0F;
static constexpr auto DOT_ROTATING_COLOR_BRIGHTNESS_FACTOR  = 5.0F;
static constexpr auto DOT_INSIDE_MIN_BRIGHTNESS_FACTOR      = 0.5F;
static constexpr auto DOT_INSIDE_MAX_BRIGHTNESS_FACTOR      = 1.0F;
static constexpr auto LINE_MAIN_COLOR_BRIGHTNESS_FACTOR     = 0.1F;
static constexpr auto LINE_LOW_COLOR_BRIGHTNESS_FACTOR      = 1.0F;
static constexpr auto NEAR_START_BRIGHTNESS_FACTOR          = 0.25F;
static constexpr auto NEAR_END_BRIGHTNESS_VALUE             = 0.001F;
static constexpr auto SPECIAL_NUM_BRIGHTNESS_INCREASE       = 1.5F;
static constexpr auto SPECIAL_NUM_LINE_BRIGHTNESS_INCREASE  = 2.0F;
static constexpr auto DECORATION_DIFFERENT_COLOR_BRIGHTNESS = 1.0F;
static constexpr auto DECORATION_SPECIAL_BRIGHTNESS         = 2.0F;
static constexpr auto MIN_COLOR_GRID_MIX_T                  = 0.1F;
static constexpr auto MAX_COLOR_GRID_MIX_T                  = 0.9F;
static constexpr auto PROB_NO_ROTATING_COLORS               = 0.9F;
static constexpr auto MIN_NUM_ROTATING_COLORS               = 1U;
static constexpr auto MAX_NUM_ROTATING_COLORS               = 2U;
static constexpr auto CLOSE_TO_START_T                      = 0.1F;
static constexpr auto CLOSE_TO_END_T                        = 0.2F;

class Circle::DotDrawer
{
public:
  DotDrawer(IGoomDraw& draw, const IGoomRand& goomRand, const Helper& helper) noexcept;

  auto SetWeightedColorMaps(const RandomColorMaps& weightedMaps) noexcept -> void;
  auto SetGlobalBrightnessFactor(float val) noexcept -> void;

  auto DrawDot(const Point2dInt& pos, uint32_t diameter, const MultiplePixels& colors) noexcept
      -> void;

private:
  DRAW::IGoomDraw& m_draw;
  const IGoomRand& m_goomRand;
  const Helper& m_helper;
  float m_globalBrightnessFactor = 1.0F;

  static constexpr float MIN_BGND_MIX_T = 0.2F;
  static constexpr float MAX_BGND_MIX_T = 0.8F;
  float m_bgndMainColorMixT;
  float m_bgndLowColorMixT;
  enum class DecorationType
  {
    NO_DECORATION,
    BLACK_LINES,
    BRIGHT_LINES,
    DIFFERENT_COLORS,
    _num // unused, and marks the enum end
  };
  DecorationType m_decorationType;
  Pixel m_differentColor = BLACK_PIXEL;

  bool m_doCircleDotShapes = true;
  const IColorMap* m_outerCircleDotColorMap{};
  static constexpr float MIN_OUTER_CIRCLE_DOT_COLOR_MIX_T = 0.1F;
  static constexpr float MAX_OUTER_CIRCLE_DOT_COLOR_MIX_T = 0.9F;
  float m_outerCircleDotColorMix                          = MIN_OUTER_CIRCLE_DOT_COLOR_MIX_T;

  auto DrawBitmapDot(const Point2dInt& position,
                     uint32_t diameter,
                     const MultiplePixels& colors) noexcept -> void;
  [[nodiscard]] auto GetRandomDifferentColor(const RandomColorMaps& weightedMaps) const noexcept
      -> Pixel;
  [[nodiscard]] auto GetRandomDecorationType() const noexcept -> DecorationType;
  [[nodiscard]] static auto IsSpecialPoint(size_t x, size_t y, uint32_t diameter) noexcept -> bool;
  [[nodiscard]] auto GetDotMixedColor(size_t x,
                                      size_t y,
                                      uint32_t diameter,
                                      const Pixel& bgnd,
                                      const Pixel& color,
                                      float mixT) const noexcept -> Pixel;
  auto DrawCircleDot(const Point2dInt& centre,
                     uint32_t diameter,
                     const MultiplePixels& colors,
                     const IColorMap& innerColorMap) noexcept -> void;
  [[nodiscard]] static auto GetCircleColors(float brightness, const MultiplePixels& colors) noexcept
      -> MultiplePixels;
  [[nodiscard]] static auto GetCircleColorsWithInner(float brightness,
                                                     const MultiplePixels& colors,
                                                     const Pixel& innerColor,
                                                     float innerColorMix) noexcept
      -> MultiplePixels;
};

static constexpr auto GRID_COLOR_RANGE_ONE_WEIGHT    = 20.0F;
static constexpr auto GRID_COLOR_RANGE_LOW_WEIGHT    = 03.0F;
static constexpr auto GRID_COLOR_RANGE_MEDIUM_WEIGHT = 02.0F;
static constexpr auto GRID_COLOR_RANGE_HIGH_WEIGHT   = 01.0F;

Circle::Circle(const FxHelper& fxHelper,
               const Helper& helper,
               const Params& circleParams,
               const OscillatingFunction::Params& pathParams) noexcept
  : m_draw{fxHelper.GetDraw()},
    m_goomInfo{fxHelper.GetGoomInfo()},
    m_goomRand{fxHelper.GetGoomRand()},
    m_helper{helper},
    m_dotPaths{m_goomRand,
               NUM_DOTS,
               {GetDotStartingPositions(circleParams.toTargetParams.circleCentreStart,
                                        circleParams.toTargetParams.circleRadius),
                GetDotStartingPositions(circleParams.fromTargetParams.circleCentreStart,
                                        circleParams.fromTargetParams.circleRadius)},
               {circleParams.toTargetParams.circleCentreTarget,
                circleParams.fromTargetParams.circleCentreTarget},
               {pathParams, pathParams},
    },
    m_dotDrawer{std::make_unique<DotDrawer>(m_draw, m_goomRand, m_helper)},
    m_mainColorMaps{RandomColorMapsGroups::MakeSharedAllMapsUnweighted(m_goomRand)},
    m_lowColorMaps{RandomColorMapsGroups::MakeSharedAllMapsUnweighted(m_goomRand)},
    m_weightedGridColorRanges{
        m_goomRand,
        {
            {GridColorRange::ONE, GRID_COLOR_RANGE_ONE_WEIGHT},
            {GridColorRange::LOW, GRID_COLOR_RANGE_LOW_WEIGHT},
            {GridColorRange::MEDIUM, GRID_COLOR_RANGE_MEDIUM_WEIGHT},
            {GridColorRange::HIGH, GRID_COLOR_RANGE_HIGH_WEIGHT},
        }
    }
{
  UpdateRotatingColorMaps();
}

Circle::Circle(Circle&&) noexcept = default;

Circle::~Circle() noexcept = default;

auto Circle::GetDotStartingPositions(const Point2dInt& centre, const float radius) noexcept
    -> std::vector<Point2dInt>
{
  auto positionT       = std::make_unique<TValue>(TValue::StepType::SINGLE_CYCLE, NUM_DOTS);
  const auto centrePos = Vec2dFlt{centre.ToFlt()};
  static constexpr auto DEFAULT_ANGLE_PARAMS = AngleParams{};
  const auto path =
      std::make_unique<CirclePath>(std::move(positionT), centrePos, radius, DEFAULT_ANGLE_PARAMS);

  auto dotStartingPositions = std::vector<Point2dInt>(NUM_DOTS);

  for (auto i = 0U; i < NUM_DOTS; ++i)
  {
    dotStartingPositions.at(i) = path->GetNextPoint();

    path->IncrementT();
  }

  return dotStartingPositions;
}

inline auto Circle::GetColorMixT([[maybe_unused]] const float tX,
                                 [[maybe_unused]] const float tY) const noexcept -> float
{
  return m_currentColorGridMixT;
}

inline auto Circle::UpdateNumDifferentGridMaps() noexcept -> void
{
  if (static constexpr auto NUM_UPDATE_SKIPS = 5U; (m_updateNum % NUM_UPDATE_SKIPS) != 0)
  {
    return;
  }

  static constexpr auto NUM_MAPS = EnumMap<GridColorRange, uint32_t>{{{
      {GridColorRange::ONE, 1U},
      {GridColorRange::LOW, NUM_DOTS / 6},
      {GridColorRange::MEDIUM, NUM_DOTS / 2},
      {GridColorRange::HIGH, NUM_DOTS},
  }}};

  m_currentGridColorRange = m_weightedGridColorRanges.GetRandomWeighted();
  m_numDifferentGridMaps  = NUM_MAPS[m_currentGridColorRange];
}

inline auto Circle::GetMainColorMapsGrid() const noexcept -> COLOR::ColorMapsGrid
{
  return {GetHorizontalMainColorMaps(),
          m_dotPaths.GetPositionTRef(),
          GetVerticalMainColorMaps(),
          [this](const float tX, const float tY) { return GetColorMixT(tX, tY); }};
}

inline auto Circle::GetLowColorMapsGrid() const noexcept -> COLOR::ColorMapsGrid
{
  return {GetHorizontalLowColorMaps(),
          m_dotPaths.GetPositionTRef(),
          GetVerticalLowColorMaps(),
          [this](const float tX, const float tY) { return GetColorMixT(tX, tY); }};
}

inline auto Circle::GetHorizontalMainColorMaps() const noexcept
    -> std::vector<const COLOR::IColorMap*>
{
  return {&m_mainColorMaps->GetRandomColorMap()};
}

inline auto Circle::GetVerticalMainColorMaps() const noexcept
    -> std::vector<const COLOR::IColorMap*>
{
  return GetAllDotColorMaps(*m_mainColorMaps);
}

inline auto Circle::GetHorizontalLowColorMaps() const noexcept
    -> std::vector<const COLOR::IColorMap*>
{
  return {&m_lowColorMaps->GetRandomColorMap()};
}

inline auto Circle::GetVerticalLowColorMaps() const noexcept -> std::vector<const COLOR::IColorMap*>
{
  return GetAllDotColorMaps(*m_lowColorMaps);
}

auto Circle::UpdateRotatingColorMaps() noexcept -> void
{
  const auto newNumRotatingColors =
      m_goomRand.ProbabilityOf(PROB_NO_ROTATING_COLORS)
          ? 0U
          : m_goomRand.GetRandInRange(MIN_NUM_ROTATING_COLORS, MAX_NUM_ROTATING_COLORS + 1);

  if (m_numRotatingColors == newNumRotatingColors)
  {
    return;
  }
  m_numRotatingColors = newNumRotatingColors;

  m_rotatingDotNums.resize(m_numRotatingColors);
  for (auto& dotNum : m_rotatingDotNums)
  {
    dotNum = m_goomRand.GetRandInRange(0U, NUM_DOTS);
  }

  m_rotatingMainColorMaps.resize(m_numRotatingColors);
  for (auto& colorMap : m_rotatingMainColorMaps)
  {
    colorMap = &m_mainColorMaps->GetRandomColorMap();
  }

  m_rotatingLowColorMaps.resize(m_numRotatingColors);
  for (auto& colorMap : m_rotatingLowColorMaps)
  {
    colorMap = &m_lowColorMaps->GetRandomColorMap();
  }
}

auto Circle::GetAllDotColorMaps(const COLOR::RandomColorMaps& baseRandomColorMaps) const noexcept
    -> std::vector<const COLOR::IColorMap*>
{
  auto differentMaps = std::vector<const COLOR::IColorMap*>(m_numDifferentGridMaps);
  for (auto& map : differentMaps)
  {
    map = &baseRandomColorMaps.GetRandomColorMap();
  }

  auto dotColorMaps = std::vector<const COLOR::IColorMap*>(NUM_DOTS);

  auto start = 0U;
  for (auto k = 0U; k < m_numDifferentGridMaps; ++k)
  {
    for (auto i = start; i < NUM_DOTS; i += m_numDifferentGridMaps)
    {
      dotColorMaps.at(i) = differentMaps.at(k);
    }
    ++start;
  }

  return dotColorMaps;
}

auto Circle::SetWeightedColorMaps(
    const std::shared_ptr<const RandomColorMaps> weightedMainMaps,
    const std::shared_ptr<const RandomColorMaps> weightedLowMaps) noexcept -> void
{
  m_mainColorMaps = weightedMainMaps;
  m_lowColorMaps  = weightedLowMaps;

  UpdateRotatingColorMaps();

  UpdateNumDifferentGridMaps();
  m_currentColorGridMixT = m_goomRand.GetRandInRange(MIN_COLOR_GRID_MIX_T, MAX_COLOR_GRID_MIX_T);
  m_mainColorMapsGrid.SetColorMaps(GetHorizontalMainColorMaps(), GetVerticalMainColorMaps());
  m_lowColorMapsGrid.SetColorMaps(GetHorizontalLowColorMaps(), GetVerticalLowColorMaps());

  m_linesMainColorMap = GetHorizontalMainColorMaps().at(0);
  m_linesLowColorMap  = GetHorizontalLowColorMaps().at(0);

  static constexpr auto PROB_SHOW_LINE = 0.5F;
  m_showLine                           = m_goomRand.ProbabilityOf(PROB_SHOW_LINE);

  m_dotDiameters.ChangeDotDiameters();
  static constexpr auto PROB_ALTERNATE_MAIN_LOW_DOT_COLORS = 0.1F;
  m_alternateMainLowDotColors = m_goomRand.ProbabilityOf(PROB_ALTERNATE_MAIN_LOW_DOT_COLORS);
  m_dotDrawer->SetWeightedColorMaps(*weightedMainMaps);
}

auto Circle::SetPathParams(const OscillatingFunction::Params& pathParams) noexcept -> void
{
  m_dotPaths.SetPathParams({pathParams, pathParams});
}

auto Circle::SetGlobalBrightnessFactor(const float val) noexcept -> void
{
  m_globalBrightnessFactor = val;
  m_dotDrawer->SetGlobalBrightnessFactor(m_globalBrightnessFactor);
}

auto Circle::Start() noexcept -> void
{
  m_updateNum = 0;
  m_dotPaths.ChangeDirection(DotPaths::Direction::TO_TARGET);
}

auto Circle::UpdateAndDraw() noexcept -> void
{
  UpdateTime();
  DrawNextCircle();
}

inline auto Circle::UpdateTime() noexcept -> void
{
  ++m_updateNum;
}

inline auto Circle::DrawNextCircle() noexcept -> void
{
  DrawNextCircleDots();
  ResetNumSteps();
}

auto Circle::ResetNumSteps() noexcept -> void
{
  if (0 == m_newNumSteps)
  {
    return;
  }
  if (not HasPositionTJustHitEndBoundary())
  {
    return;
  }
  m_dotPaths.SetPositionTNumSteps(m_newNumSteps);
  m_newNumSteps = 0;
}

auto Circle::DrawNextCircleDots() noexcept -> void
{
  LogInfo("m_globalBrightnessFactor = {}", m_globalBrightnessFactor);

  const auto nextDotPositions = m_dotPaths.GetNextDotPositions();

  const auto brightness     = GetCurrentBrightness();
  const auto dotBrightness  = GetDotBrightness(brightness);
  const auto lineBrightness = GetLineBrightness(brightness);
  const auto allDotColors   = GetAllDotColors();
  LogInfo("brightness = {}", brightness);
  LogInfo("dotBrightness = {}", dotBrightness);
  LogInfo("lineBrightness = {}", lineBrightness);

  auto iRotate         = m_dotRotateOffset;
  auto tLineColor      = 0.0F;
  auto prevDotPosition = nextDotPositions[NUM_DOTS - 1];
  for (auto i = 0U; i < NUM_DOTS; ++i)
  {
    const auto dotPosition = nextDotPositions.at(i);
    const auto dotDiameter = m_dotDiameters.GetDotDiameters().at(iRotate);
    const auto dotColors   = GetSingleDotColors(iRotate, allDotColors, dotBrightness);
    LogInfo(
        "corrected dotColors low = {},{},{}", dotColors[1].R(), dotColors[1].G(), dotColors[1].B());

    m_dotDrawer->DrawDot(dotPosition, dotDiameter, dotColors);

    DrawLine(prevDotPosition, dotPosition, lineBrightness, tLineColor);

    m_lastDrawnDots.at(i) = dotPosition;
    prevDotPosition       = dotPosition;
    tLineColor += T_LINE_COLOR_STEP;
    iRotate = ModIncrement(iRotate, NUM_DOTS);
  }

  m_dotRotateOffset = ModIncrement(m_dotRotateOffset, NUM_DOTS);
  m_rotatingColorsT.Increment();
}

inline auto Circle::GetAllDotColors() const noexcept -> AllDotColors
{
  return {m_mainColorMapsGrid.GetCurrentHorizontalLineColors(),
          m_lowColorMapsGrid.GetCurrentHorizontalLineColors()};
}

inline auto Circle::GetSingleDotColors(const uint32_t dotNum,
                                       const AllDotColors& allDotColors,
                                       const float dotBrightness) const noexcept -> MultiplePixels
{
  for (auto i = 0U; i < m_numRotatingColors; ++i)
  {
    if (dotNum == m_rotatingDotNums.at(i))
    {
      return {m_rotatingMainColorMaps.at(i)->GetColor(m_rotatingColorsT()),
              GetBrighterColor(DOT_ROTATING_COLOR_BRIGHTNESS_FACTOR * dotBrightness,
                               m_rotatingLowColorMaps.at(i)->GetColor(m_rotatingColorsT()))};
    }
  }

  const auto dotMainColor = allDotColors.mainColors.at(dotNum);
  const auto dotLowColor  = allDotColors.lowColors.at(dotNum);
  return {GetCorrectedColor(DOT_MAIN_COLOR_BRIGHTNESS_FACTOR * dotBrightness, dotMainColor),
          GetCorrectedColor(DOT_LOW_COLOR_BRIGHTNESS_FACTOR * dotBrightness, dotLowColor)};
}

inline auto Circle::GetCurrentBrightness() const noexcept -> float
{
  return m_dotPaths.IsCloseToEndBoundary(CLOSE_TO_END_T) ? NEAR_END_BRIGHTNESS_VALUE
                                                         : m_globalBrightnessFactor;
}

inline auto Circle::GetDotBrightness(const float brightness) const noexcept -> float
{
  if (not m_dotPaths.IsCloseToStartBoundary(CLOSE_TO_START_T))
  {
    if (IsSpecialUpdateNum())
    {
      return SPECIAL_NUM_BRIGHTNESS_INCREASE * brightness;
    }
    return brightness;
  }

  return NEAR_START_BRIGHTNESS_FACTOR * brightness;
}

inline auto Circle::IsSpecialUpdateNum() const noexcept -> bool
{
  static constexpr auto SPECIAL_UPDATE_MULTIPLE = 5U;
  return 0 == (m_updateNum % SPECIAL_UPDATE_MULTIPLE);
}

inline auto Circle::IsSpecialLineUpdateNum() const noexcept -> bool
{
  if (m_dotPaths.IsCloseToStartBoundary(CLOSE_TO_START_T))
  {
    return true;
  }
  static constexpr auto LINE_UPDATE_MULTIPLE = 8U;
  return 0 == (m_updateNum % LINE_UPDATE_MULTIPLE);
}

inline auto Circle::GetLineBrightness(const float brightness) const noexcept -> float
{
  return IsSpecialLineUpdateNum() ? (SPECIAL_NUM_LINE_BRIGHTNESS_INCREASE * brightness)
                                  : brightness;
}

inline auto Circle::GetCorrectedColor(const float brightness, const Pixel& color) const noexcept
    -> Pixel
{
  LogInfo("corrected color brightness = {}", brightness);
  return m_colorAdjustment.GetAdjustment(brightness, color);
}

inline auto Circle::DrawLine(const Point2dInt& position1,
                             const Point2dInt& position2,
                             const float lineBrightness,
                             const float tLineColor) noexcept -> void
{
  const auto lastTDotColor = DrawLineDots(lineBrightness, position1, position2, tLineColor);
  DrawConnectingLine(position1, position2, lineBrightness, lastTDotColor);
}

inline auto Circle::DrawLineDots(const float lineBrightness,
                                 const Point2dInt& position1,
                                 const Point2dInt& position2,
                                 const float tLineColor) noexcept -> float
{
  static constexpr auto NUM_LINE_DOTS = 5U;

  static constexpr auto T_DOT_POS_STEP = 1.0F / static_cast<float>(NUM_LINE_DOTS);
  auto tDotPos                         = T_DOT_POS_STEP;

  static constexpr auto T_DOT_COLOR_STEP = T_LINE_COLOR_STEP / static_cast<float>(NUM_LINE_DOTS);

  auto tDotColor = tLineColor + T_DOT_COLOR_STEP;
  for (auto i = 0U; i < (NUM_LINE_DOTS - 1); ++i)
  {
    const auto dotPos    = lerp(position1, position2, tDotPos);
    const auto mainColor = GetCorrectedColor(LINE_MAIN_COLOR_BRIGHTNESS_FACTOR * lineBrightness,
                                             m_linesMainColorMap->GetColor(tDotColor));
    const auto lowColor  = GetCorrectedColor(LINE_LOW_COLOR_BRIGHTNESS_FACTOR * lineBrightness,
                                            m_linesLowColorMap->GetColor(tDotColor));

    DrawDot(i, dotPos, {mainColor, lowColor});

    tDotPos += T_DOT_POS_STEP;
    tDotColor += T_DOT_COLOR_STEP;
  }

  return tDotColor;
}

inline auto Circle::DrawDot(const uint32_t dotNum,
                            const Point2dInt& pos,
                            const MultiplePixels& colors) noexcept -> void
{
  if (m_alternateMainLowDotColors and UTILS::MATH::IsEven(dotNum))
  {
    m_dotDrawer->DrawDot(pos, m_helper.lineDotDiameter, ReversePixels(colors));
  }
  else
  {
    m_dotDrawer->DrawDot(pos, m_helper.lineDotDiameter, colors);
  }
}

auto Circle::DrawConnectingLine(const Point2dInt& position1,
                                const Point2dInt& position2,
                                const float lineBrightness,
                                const float tDotColor) noexcept -> void
{
  if (not m_dotPaths.IsCloseToStartBoundary(CLOSE_TO_START_T) and
      ((not m_showLine) or (not IsSpecialLineUpdateNum())))
  {
    return;
  }

  static constexpr auto LINE_THICKNESS = 1U;
  const auto mainColor = GetCorrectedColor(LINE_MAIN_COLOR_BRIGHTNESS_FACTOR * lineBrightness,
                                           m_linesMainColorMap->GetColor(tDotColor));
  const auto lowColor  = GetCorrectedColor(LINE_LOW_COLOR_BRIGHTNESS_FACTOR * lineBrightness,
                                          m_linesLowColorMap->GetColor(tDotColor));
  LogInfo("corrected lowColor = {},{},{}", lowColor.R(), lowColor.G(), lowColor.B());


  m_draw.Line(position1, position2, {mainColor, lowColor}, LINE_THICKNESS);
}

Circle::DotDrawer::DotDrawer(DRAW::IGoomDraw& draw,
                             const IGoomRand& goomRand,
                             const Circle::Helper& helper) noexcept
  : m_draw{draw},
    m_goomRand{goomRand},
    m_helper{helper},
    m_bgndMainColorMixT{m_goomRand.GetRandInRange(MIN_BGND_MIX_T, MAX_BGND_MIX_T)},
    m_bgndLowColorMixT{m_goomRand.GetRandInRange(MIN_BGND_MIX_T, MAX_BGND_MIX_T)},
    m_decorationType{GetRandomDecorationType()},
    m_differentColor{GetRandomDifferentColor(RandomColorMaps{m_goomRand})}
{
}

inline auto Circle::DotDrawer::SetWeightedColorMaps(const RandomColorMaps& weightedMaps) noexcept
    -> void
{
  m_bgndMainColorMixT      = m_goomRand.GetRandInRange(MIN_BGND_MIX_T, MAX_BGND_MIX_T);
  m_bgndLowColorMixT       = m_goomRand.GetRandInRange(MIN_BGND_MIX_T, MAX_BGND_MIX_T);
  m_decorationType         = GetRandomDecorationType();
  m_differentColor         = GetRandomDifferentColor(weightedMaps);
  m_outerCircleDotColorMap = &weightedMaps.GetRandomColorMap();

  static constexpr auto PROB_CIRCLES = 0.5F;
  m_doCircleDotShapes                = m_goomRand.ProbabilityOf(PROB_CIRCLES);
  m_outerCircleDotColorMix =
      m_goomRand.GetRandInRange(MIN_OUTER_CIRCLE_DOT_COLOR_MIX_T, MAX_OUTER_CIRCLE_DOT_COLOR_MIX_T);
}

inline auto Circle::DotDrawer::SetGlobalBrightnessFactor(const float val) noexcept -> void
{
  m_globalBrightnessFactor = val;
}

inline auto Circle::DotDrawer::DrawDot(const Point2dInt& pos,
                                       const uint32_t diameter,
                                       const MultiplePixels& colors) noexcept -> void
{
  if (m_doCircleDotShapes)
  {
    DrawCircleDot(pos, diameter, colors, *m_outerCircleDotColorMap);
  }
  else
  {
    DrawBitmapDot(pos, diameter, colors);
  }
}

auto Circle::DotDrawer::DrawCircleDot(const Point2dInt& centre,
                                      const uint32_t diameter,
                                      const MultiplePixels& colors,
                                      const IColorMap& innerColorMap) noexcept -> void
{
  const auto maxRadius = static_cast<int32_t>(diameter + 3) / 2;
  auto innerColorT =
      TValue{UTILS::TValue::StepType::SINGLE_CYCLE, static_cast<uint32_t>(maxRadius - 1)};
  static constexpr auto INNER_COLOR_CUTOFF_RADIUS = 4;

  auto brightnessT = TValue{TValue::StepType::SINGLE_CYCLE, static_cast<uint32_t>(maxRadius)};
  const auto minBrightness = m_globalBrightnessFactor * DOT_INSIDE_MIN_BRIGHTNESS_FACTOR;
  const auto maxBrightness = m_globalBrightnessFactor * DOT_INSIDE_MAX_BRIGHTNESS_FACTOR;

  // '> 1' means leave a little hole in the middle of the circles.
  for (auto radius = maxRadius; radius > 1; --radius)
  {
    const auto brightness = STD20::lerp(minBrightness, maxBrightness, brightnessT());
    const auto innerColor = innerColorMap.GetColor(innerColorT());
    const auto circleColors =
        radius <= INNER_COLOR_CUTOFF_RADIUS
            ? GetCircleColors(brightness, colors)
            : GetCircleColorsWithInner(brightness, colors, innerColor, m_outerCircleDotColorMix);

    m_draw.Circle(centre, radius, circleColors);

    brightnessT.Increment();
    innerColorT.Increment();
  }
}

inline auto Circle::DotDrawer::GetCircleColors(const float brightness,
                                               const MultiplePixels& colors) noexcept
    -> MultiplePixels
{
  return {
      GetBrighterColor(brightness, GetMainColor(colors)),
      GetBrighterColor(brightness, GetLowColor(colors)),
  };
}

inline auto Circle::DotDrawer::GetCircleColorsWithInner(const float brightness,
                                                        const MultiplePixels& colors,
                                                        const Pixel& innerColor,
                                                        const float innerColorMix) noexcept
    -> MultiplePixels
{
  return {
      GetBrighterColor(brightness,
                       IColorMap::GetColorMix(GetMainColor(colors), innerColor, innerColorMix)),
      GetBrighterColor(brightness,
                       IColorMap::GetColorMix(GetLowColor(colors), innerColor, innerColorMix)),
  };
}

auto Circle::DotDrawer::DrawBitmapDot(const Point2dInt& position,
                                      const uint32_t diameter,
                                      const MultiplePixels& colors) noexcept -> void
{
  const auto getMainColor =
      [this, &colors, &diameter](const size_t x, const size_t y, const Pixel& bgnd)
  { return GetDotMixedColor(x, y, diameter, bgnd, GetMainColor(colors), m_bgndMainColorMixT); };

  const auto getLowColor =
      [this, &colors, &diameter](const size_t x, const size_t y, const Pixel& bgnd)
  { return GetDotMixedColor(x, y, diameter, bgnd, GetLowColor(colors), m_bgndLowColorMixT); };

  m_draw.Bitmap(position, m_helper.bitmapGetter.GetBitmap(diameter), {getMainColor, getLowColor});
}

inline auto Circle::DotDrawer::GetRandomDecorationType() const noexcept -> DecorationType
{
  return static_cast<DecorationType>(m_goomRand.GetRandInRange(0U, NUM<DecorationType>));
}

inline auto Circle::DotDrawer::GetRandomDifferentColor(
    const RandomColorMaps& weightedMaps) const noexcept -> Pixel
{
  return weightedMaps.GetRandomColorMap().GetColor(m_goomRand.GetRandInRange(0.0F, 1.0F));
}

inline auto Circle::DotDrawer::GetDotMixedColor(const size_t x,
                                                const size_t y,
                                                const uint32_t diameter,
                                                const Pixel& bgnd,
                                                const Pixel& color,
                                                const float mixT) const noexcept -> Pixel
{
  if (0 == bgnd.A())
  {
    return BLACK_PIXEL;
  }

  const auto mixedColor = IColorMap::GetColorMix(bgnd, color, mixT);

  if (not IsSpecialPoint(x, y, diameter))
  {
    return GetBrighterColor(m_globalBrightnessFactor, mixedColor);
  }

  switch (m_decorationType)
  {
    case DecorationType::NO_DECORATION:
      return GetBrighterColor(m_globalBrightnessFactor, mixedColor);
    case DecorationType::BLACK_LINES:
      return BLACK_PIXEL;
    case DecorationType::DIFFERENT_COLORS:
      return GetBrighterColor(m_globalBrightnessFactor * DECORATION_DIFFERENT_COLOR_BRIGHTNESS,
                              m_differentColor);
    case DecorationType::BRIGHT_LINES:
      return GetBrighterColor(m_globalBrightnessFactor * DECORATION_SPECIAL_BRIGHTNESS, mixedColor);
    default:
      FailFast();
      return BLACK_PIXEL;
  }
}

inline auto Circle::DotDrawer::IsSpecialPoint(const size_t x,
                                              const size_t y,
                                              const uint32_t diameter) noexcept -> bool
{
  if (static constexpr auto EDGE_CUTOFF = 3U; (x <= EDGE_CUTOFF) ||
                                              (x >= (diameter - EDGE_CUTOFF)) ||
                                              (y <= EDGE_CUTOFF) || (y >= (diameter - EDGE_CUTOFF)))
  {
    return false;
  }
  if (((U_HALF * diameter) == x) || ((U_HALF * diameter) == y))
  {
    return true;
  }
  if ((x == y) || ((diameter - x) == y))
  {
    return true;
  }

  return false;
}

} // namespace GOOM::VISUAL_FX::CIRCLES
