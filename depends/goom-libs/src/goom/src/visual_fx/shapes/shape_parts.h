#pragma once

#include "color/color_maps.h"
#include "color/random_color_maps.h"
#include "color/random_color_maps_manager.h"
#include "draw/goom_draw.h"
#include "goom_plugin_info.h"
#include "point2d.h"
#include "shape_paths.h"
#include "utils/math/goom_rand_base.h"
#include "utils/step_speed.h"
#include "utils/t_values.h"
#include "utils/timer.h"

#include <cstdint>
#include <memory>
#include <vector>

namespace GOOM::VISUAL_FX::SHAPES
{

class ShapePart
{
public:
  struct Params
  {
    uint32_t shapePartNum;
    uint32_t totalNumShapeParts;
    float minRadiusFraction;
    float maxRadiusFraction;
    int32_t minShapeDotRadius;
    int32_t maxShapeDotRadius;
    uint32_t maxNumShapePaths;
    float tMinMaxLerp;
    Point2dInt shapePathsTargetPoint;
    uint32_t shapePathsMinNumSteps;
    uint32_t shapePathsMaxNumSteps;
  };

  ShapePart(DRAW::IGoomDraw& draw,
            const UTILS::MATH::IGoomRand& goomRand,
            const PluginInfo& goomInfo,
            COLOR::RandomColorMapsManager& colorMapsManager,
            const Params& params) noexcept;
  ShapePart(const ShapePart&) noexcept           = delete;
  ShapePart(ShapePart&&) noexcept                = default;
  ~ShapePart() noexcept                          = default;
  auto operator=(const ShapePart&) -> ShapePart& = delete;
  auto operator=(ShapePart&&) -> ShapePart&      = delete;

  auto SetWeightedMainColorMaps(std::shared_ptr<const COLOR::RandomColorMaps> weightedMaps) noexcept
      -> void;
  auto SetWeightedLowColorMaps(std::shared_ptr<const COLOR::RandomColorMaps> weightedMaps) noexcept
      -> void;
  auto SetWeightedInnerColorMaps(
      std::shared_ptr<const COLOR::RandomColorMaps> weightedMaps) noexcept -> void;
  auto SetChromaFactor(float val) noexcept -> void;

  auto SetShapePathsTargetPoint(const Point2dInt& targetPoint) -> void;

  auto SetShapePathsMinMaxNumSteps(uint32_t shapePathsMinNumSteps,
                                   uint32_t shapePathsMaxNumSteps) noexcept -> void;

  auto Start() noexcept -> void;

  struct DrawParams
  {
    float brightnessAttenuation;
    bool firstShapePathAtMeetingPoint;
    bool varyDotRadius;
    ShapePath::ShapePathColors meetingPointColors;
  };
  auto Draw(const DrawParams& drawParams) noexcept -> void;

  auto Update() noexcept -> void;
  auto ResetTs(float val) noexcept -> void;

  auto DoRandomChanges() noexcept -> void;
  auto UseRandomShapePathsNumSteps() noexcept -> void;
  auto UseFixedShapePathsNumSteps(float tMinMaxLerp) noexcept -> void;
  auto UseEvenShapePartNumsForDirection(bool val) -> void;
  [[nodiscard]] static auto GetNewRandomMinMaxLerpT(const UTILS::MATH::IGoomRand& goomRand,
                                                    float oldTMinMaxLerp) noexcept -> float;

  [[nodiscard]] auto GetNumShapePaths() const noexcept -> uint32_t;
  [[nodiscard]] auto GetShapePath(size_t shapePathNum) const noexcept -> const ShapePath&;
  [[nodiscard]] auto GetCurrentShapeDotRadius(bool varyRadius) const noexcept -> int32_t;
  [[nodiscard]] auto GetFirstShapePathPositionT() const noexcept -> float;
  [[nodiscard]] auto GetFirstShapePathTDistanceFromClosestBoundary() const noexcept -> float;
  [[nodiscard]] auto AreShapePathsCloseToMeeting() const noexcept -> bool;

private:
  DRAW::IGoomDraw& m_draw;
  const UTILS::MATH::IGoomRand& m_goomRand;
  const PluginInfo& m_goomInfo;
  COLOR::RandomColorMapsManager& m_colorMapsManager;

  float m_currentTMinMaxLerp;
  UTILS::StepSpeed m_shapePathsStepSpeed;
  auto SetShapePathsNumSteps() noexcept -> void;

  const int32_t m_minShapeDotRadius;
  const int32_t m_maxShapeDotRadius;
  static constexpr int32_t EXTREME_MAX_DOT_RADIUS_MULTIPLIER = 5;
  const int32_t m_extremeMaxShapeDotRadius =
      EXTREME_MAX_DOT_RADIUS_MULTIPLIER * m_maxShapeDotRadius;
  bool m_useExtremeMaxShapeDotRadius              = false;
  static constexpr uint32_t MIN_DOT_RADIUS_STEPS  = 100;
  static constexpr uint32_t MAX_DOT_RADIUS_STEPS  = 200;
  static constexpr float INITIAL_DOT_RADIUS_SPEED = 0.5F;
  UTILS::StepSpeed m_dotRadiusStepSpeed{
      MIN_DOT_RADIUS_STEPS, MAX_DOT_RADIUS_STEPS, INITIAL_DOT_RADIUS_SPEED};
  UTILS::TValue m_dotRadiusT{UTILS::TValue::StepType::CONTINUOUS_REVERSIBLE,
                             m_dotRadiusStepSpeed.GetCurrentNumSteps()};
  [[nodiscard]] auto GetMaxDotRadius(bool varyRadius) const noexcept -> int32_t;

  static constexpr float MIN_INNER_COLOR_MIX_T = 0.1F;
  static constexpr float MAX_INNER_COLOR_MIX_T = 0.9F;
  struct ColorInfo
  {
    std::shared_ptr<const COLOR::RandomColorMaps> mainColorMaps;
    std::shared_ptr<const COLOR::RandomColorMaps> lowColorMaps;
    std::shared_ptr<const COLOR::RandomColorMaps> innerColorMaps;
    float innerColorMix;
  };
  [[nodiscard]] auto GetInitialColorInfo() const noexcept -> ColorInfo;
  ColorInfo m_colorInfo{GetInitialColorInfo()};
  auto ChangeAllColorMapsNow() noexcept -> void;
  float m_chromaFactor = 1.0F;

  bool m_megaColorChangeMode = false;
  auto DoMegaColorChange() noexcept -> void;
  static constexpr uint32_t MEGA_COLOR_CHANGE_ON_TIME         = 100;
  static constexpr uint32_t MEGA_COLOR_CHANGE_ON_FAILED_TIME  = 10;
  static constexpr uint32_t MEGA_COLOR_CHANGE_OFF_TIME        = 1000;
  static constexpr uint32_t MEGA_COLOR_CHANGE_OFF_FAILED_TIME = 20;
  UTILS::OnOffTimer m_megaColorChangeOnOffTimer{
      {
       MEGA_COLOR_CHANGE_ON_TIME, MEGA_COLOR_CHANGE_ON_FAILED_TIME,
       MEGA_COLOR_CHANGE_OFF_TIME, MEGA_COLOR_CHANGE_OFF_FAILED_TIME,
       }
  };
  auto StartMegaColorChangeOnOffTimer() noexcept -> void;
  [[nodiscard]] auto SetMegaColorChangeOn() noexcept -> bool;
  [[nodiscard]] auto SetMegaColorChangeOff() noexcept -> bool;

  const uint32_t m_shapePartNum;
  static constexpr uint32_t MIN_NUM_SHAPE_PATHS = 4;
  const uint32_t m_maxNumShapePaths;
  const uint32_t m_totalNumShapeParts;
  std::vector<ShapePath> m_shapePaths{};
  bool m_useEvenShapePartNumsForDirection = true;

  Point2dInt m_shapePathsTargetPoint;
  Point2dInt m_newShapePathsTargetPoint;
  bool m_needToUpdateTargetPoint = false;
  auto UpdateShapePathTargets() noexcept -> void;
  auto UpdateShapePathTransform(ShapePath& shapePath) const noexcept -> void;

  auto IncrementTs() noexcept -> void;
  auto SetRandomizedShapePaths() noexcept -> void;
  [[nodiscard]] auto GetRandomizedShapePaths() noexcept -> std::vector<ShapePath>;
  [[nodiscard]] auto GetShapePaths(uint32_t numShapePaths, float minScale, float maxScale) noexcept
      -> std::vector<ShapePath>;
  [[nodiscard]] static auto GetTransform2d(const Vec2dFlt& targetPoint,
                                           float radius,
                                           float scale,
                                           float rotate) noexcept -> UTILS::MATH::Transform2d;
  struct ShapeFunctionParams
  {
    float radius;
    UTILS::MATH::AngleParams angleParams;
    UTILS::MATH::CircleFunction::Direction direction;
  };
  const float m_minRadiusFraction;
  const float m_maxRadiusFraction;
  [[nodiscard]] auto GetCircleRadius() const noexcept -> float;
  [[nodiscard]] auto GetCircleDirection() const noexcept -> UTILS::MATH::CircleFunction::Direction;
  [[nodiscard]] auto MakeShapePathColorInfo() noexcept -> ShapePath::ColorInfo;
  [[nodiscard]] static auto GetCirclePath(float radius,
                                          UTILS::MATH::CircleFunction::Direction direction,
                                          uint32_t numSteps) noexcept -> UTILS::MATH::CirclePath;
  [[nodiscard]] static auto GetCircleFunction(const ShapeFunctionParams& params)
      -> UTILS::MATH::CircleFunction;
};

static_assert(std::is_nothrow_move_constructible_v<ShapePart>);

inline auto ShapePart::GetNumShapePaths() const noexcept -> uint32_t
{
  return static_cast<uint32_t>(m_shapePaths.size());
}

inline auto ShapePart::GetShapePath(const size_t shapePathNum) const noexcept -> const ShapePath&
{
  return m_shapePaths.at(shapePathNum);
}

inline auto ShapePart::ResetTs(const float val) noexcept -> void
{
  std::for_each(
      begin(m_shapePaths), end(m_shapePaths), [&val](ShapePath& path) { path.ResetT(val); });
}

inline auto ShapePart::GetNewRandomMinMaxLerpT(const UTILS::MATH::IGoomRand& goomRand,
                                               const float oldTMinMaxLerp) noexcept -> float
{
  static constexpr auto SMALL_OFFSET = 0.2F;
  return goomRand.GetRandInRange(std::max(0.0F, -SMALL_OFFSET + oldTMinMaxLerp),
                                 std::min(1.0F, oldTMinMaxLerp + SMALL_OFFSET));
}

inline auto ShapePart::UseEvenShapePartNumsForDirection(const bool val) -> void
{
  m_useEvenShapePartNumsForDirection = val;
}

inline auto ShapePart::SetRandomizedShapePaths() noexcept -> void
{
  m_shapePaths = GetRandomizedShapePaths();
  SetChromaFactor(m_chromaFactor);
}

} // namespace GOOM::VISUAL_FX::SHAPES
