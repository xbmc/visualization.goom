#include "tubes.h"

#include "goomutils/colormaps.h"
#include "goomutils/colorutils.h"
#include "goomutils/logging_control.h"
#undef NO_LOGGING
#include "goomutils/goomrand.h"
#include "goomutils/graphics/small_image_bitmaps.h"
#include "goomutils/logging.h"
#include "goomutils/mathutils.h"
#include "goomutils/random_colormaps.h"
#include "goomutils/t_values.h"
#include "goomutils/timer.h"
#include "v2d.h"

#include <algorithm>
#include <cstdint>
#include <memory>
#include <random>
#include <vector>

#if __cplusplus <= 201402L
namespace GOOM
{
namespace TUBES
{
#else
namespace GOOM::TUBES
{
#endif

using UTILS::GammaCorrection;
using UTILS::GetLightenedColor;
using UTILS::GetRandInRange;
using UTILS::IColorMap;
using UTILS::m_pi;
using UTILS::m_third_pi;
using UTILS::m_two_pi;
using UTILS::ProbabilityOf;
using UTILS::RandomColorMaps;
using UTILS::SMALL_FLOAT;
using UTILS::SmallImageBitmaps;
using UTILS::Sq;
using UTILS::Timer;
using UTILS::TValue;
using UTILS::Weights;

constexpr uint32_t NUM_SHAPES_PER_TUBE = 45;
// Strangely, 'NUM_SHAPES_PER_TUBE = 100' gives a small gap in
// circle at 90 and 270 degrees.

constexpr bool REVERSIBLE_SHAPE_PATHS = true;
constexpr bool OSCILLATING_SHAPE_PATHS = true;

// TODO: Probability and random should be higher up???????
constexpr float PROB_INTERIOR_SHAPE = 45.0F / 50.0F;
constexpr uint32_t MAX_INTERIOR_SHAPES_TIME = 500;
constexpr float PROB_NO_BOUNDARY_SHAPES = 1.0F / 5.0F;
constexpr uint32_t MAX_NO_BOUNDARY_SHAPES_TIME = 1;

constexpr uint32_t MIN_STRIPE_WIDTH = NUM_SHAPES_PER_TUBE / 6;
constexpr uint32_t MAX_STRIPE_WIDTH = NUM_SHAPES_PER_TUBE / 3;
static_assert(MIN_STRIPE_WIDTH > 0, "MIN_STRIPE_WIDTH must be > 0.");

constexpr uint32_t MIN_NUM_CIRCLES_IN_GROUP = 10;
constexpr uint32_t MAX_NUM_CIRCLES_IN_GROUP = 100;

constexpr float MIN_HEX_SIZE = 3.0F;
constexpr float MAX_HEX_SIZE = 9.0F;

constexpr float MIN_CIRCLE_SPEED = 0.0005F;
constexpr float NML_CIRCLE_SPEED = 0.005F;
constexpr float MAX_CIRCLE_SPEED = 0.008F;

constexpr float MIN_CENTRE_SPEED = 0.0005F;
constexpr float NML_CENTRE_SPEED = 0.005F;
constexpr float MAX_CENTRE_SPEED = 0.05F;
/**
constexpr float MIN_CENTRE_SPEED = 0.00005F;
constexpr float NML_CENTRE_SPEED = 0.0005F;
constexpr float MAX_CENTRE_SPEED = 0.005F;
 **/

static const Weights<ColorMapMixMode> S_COLOR_MAP_MIX_MODES{{
    {ColorMapMixMode::SHAPES_ONLY, 20},
    {ColorMapMixMode::STRIPED_SHAPES_ONLY, 10},
    {ColorMapMixMode::CIRCLES_ONLY, 20},
    {ColorMapMixMode::SHAPES_AND_CIRCLES, 5},
    {ColorMapMixMode::STRIPED_SHAPES_AND_CIRCLES, 15},
}};

enum class LowColorTypes
{
  TRUE_LOW_COLOR,
  MAIN_COLOR,
  LIGHTENED_LOW_COLOR,
};
static const Weights<LowColorTypes> S_LOW_COLOR_TYPES{{
    {LowColorTypes::TRUE_LOW_COLOR, 30},
    {LowColorTypes::MAIN_COLOR, 10},
    {LowColorTypes::LIGHTENED_LOW_COLOR, 10},
}};
constexpr uint32_t MIN_LOW_COLOR_TYPE_TIME = 100;
constexpr uint32_t MAX_LOW_COLOR_TYPE_TIME = 1000;

constexpr float OUTER_CIRCLE_BRIGHTNESS = 0.1F;
constexpr float LIGHTER_COLOR_POWER = 10.0F;

class ShapeColorizer;
class ShapePath;
class ParametricPath;

class Tube::TubeImpl
{
public:
  TubeImpl() noexcept = delete;
  TubeImpl(uint32_t tubeId,
           const DrawFuncs& drawFuncs,
           uint32_t screenWidth,
           uint32_t screenHeight,
           const UTILS::RandomColorMaps* colorMaps,
           const UTILS::RandomColorMaps* lowColorMaps,
           float radiusEdgeOffset,
           float brightnessFactor) noexcept;
  ~TubeImpl() noexcept;
  TubeImpl(const TubeImpl&) noexcept = delete;
  TubeImpl(TubeImpl&&) noexcept = delete;
  auto operator=(const TubeImpl&) -> TubeImpl& = delete;
  auto operator=(TubeImpl&&) -> TubeImpl& = delete;

  [[nodiscard]] auto GetTubeId() const -> uint32_t;
  [[nodiscard]] auto IsActive() const -> bool;

  void ResetPaths();
  void ResetColorMaps();
  void RotateShapeColorMaps();

  [[nodiscard]] auto GetBrightnessFactor() const -> float;
  void SetBrightnessFactor(float val);

  [[nodiscard]] auto GetMaxJitterOffset() const -> int32_t;
  void SetMaxJitterOffset(int32_t val);

  void SetTransformCentreFunc(const TransformCentreFunc& f);
  [[nodiscard]] auto GetCentrePathT() const -> float;
  void SetCentrePathT(float val);
  [[nodiscard]] auto GetCentreSpeed() const -> float;
  void SetCentreSpeed(float val);
  void IncreaseCentreSpeed();
  void DecreaseCentreSpeed();

  void SetOscillatingCirclePaths(bool val);
  void SetCirclePathParams(const PathParams& params);
  [[nodiscard]] auto GetCircleSpeed() const -> float;
  void SetCircleSpeed(float val);
  void IncreaseCircleSpeed();
  void DecreaseCircleSpeed();

  void DrawShapes();
  void UpdateTValues();
  void UpdateTimers();

private:
  struct Shape
  {
    uint32_t shapeNum{};
    std::unique_ptr<ShapePath> path{};
    uint8_t lineThickness{1};
  };

  const uint32_t m_tubeId;
  DrawFuncs m_drawFuncs;
  const uint32_t m_screenWidth;
  const uint32_t m_screenHeight;
  std::unique_ptr<ShapeColorizer> m_colorizer;
  bool m_active = true;
  std::vector<Shape> m_shapes{};
  int32_t m_maxJitterOffset{};
  std::unique_ptr<ParametricPath> m_centrePath{};
  TransformCentreFunc m_getTransformedCentre{};

  UTILS::Timer m_circleGroupTimer;
  UTILS::Timer m_interiorShapeTimer;
  UTILS::Timer m_noBoundaryShapeTimer;
  float m_hexLen;
  auto GetHexLen() const -> float;
  uint32_t m_interiorShapeSize;
  static auto GetInteriorShapeSize(float hexLen) -> uint32_t;

  UTILS::Timer m_lowColorTypeTimer;
  LowColorTypes m_currentLowColorType = LowColorTypes::TRUE_LOW_COLOR;

  void InitShapes(float radiusEdgeOffset);
  void DrawShape(const Shape& shape, const V2dInt& centreOffset);
  void DrawInteriorShape(const V2dInt& shapeCentrePos, const ShapeColors& allColors) const;
  void DrawHexOutline(const V2dInt& hexCentre,
                      const std::vector<Pixel>& lineColors,
                      uint8_t lineThickness) const;
};

const float Tube::NORMAL_CENTRE_SPEED = NML_CENTRE_SPEED;
const float Tube::NORMAL_CIRCLE_SPEED = NML_CIRCLE_SPEED;

Tube::Tube(const uint32_t tubeId,
           const DrawFuncs& drawFuncs,
           const uint32_t screenWidth,
           const uint32_t screenHeight,
           const RandomColorMaps* const colorMaps,
           const RandomColorMaps* const lowColorMaps,
           const float radiusEdgeOffset,
           float brightnessFactor) noexcept
  : m_impl{std::make_unique<Tube::TubeImpl>(tubeId,
                                            drawFuncs,
                                            screenWidth,
                                            screenHeight,
                                            colorMaps,
                                            lowColorMaps,
                                            radiusEdgeOffset,
                                            brightnessFactor)}
{
}

Tube::Tube(Tube&& other) noexcept : m_impl{other.m_impl.release()}
{
}

Tube::~Tube() noexcept = default;

void Tube::ResetPaths()
{
  m_impl->ResetPaths();
}

void Tube::ResetColorMaps()
{
  m_impl->ResetColorMaps();
}

void Tube::RotateShapeColorMaps()
{
  m_impl->RotateShapeColorMaps();
}

auto Tube::GetTubeId() const -> uint32_t
{
  return m_impl->GetTubeId();
}

auto Tube::IsActive() const -> bool
{
  return m_impl->IsActive();
}

void Tube::SetTransformCentreFunc(const TransformCentreFunc& f)
{
  m_impl->SetTransformCentreFunc(f);
}

auto Tube::GetCentrePathT() const -> float
{
  return m_impl->GetCentrePathT();
}

void Tube::SetCentrePathT(const float val)
{
  m_impl->SetCentrePathT(val);
}

auto Tube::GetCentreSpeed() const -> float
{
  return m_impl->GetCentreSpeed();
}

void Tube::SetCentreSpeed(const float val)
{
  m_impl->SetCentreSpeed(val);
}

void Tube::IncreaseCentreSpeed()
{
  m_impl->IncreaseCentreSpeed();
}

void Tube::DecreaseCentreSpeed()
{
  m_impl->DecreaseCentreSpeed();
}

void Tube::SetOscillatingCirclePaths(const bool val)
{
  m_impl->SetOscillatingCirclePaths(val);
}

void Tube::SetCirclePathParams(const PathParams& params)
{
  m_impl->SetCirclePathParams(params);
}

auto Tube::GetCircleSpeed() const -> float
{
  return m_impl->GetCircleSpeed();
}

void Tube::SetCircleSpeed(const float val)
{
  m_impl->SetCircleSpeed(val);
}

void Tube::IncreaseCircleSpeed()
{
  m_impl->IncreaseCircleSpeed();
}

void Tube::DecreaseCircleSpeed()
{
  m_impl->DecreaseCircleSpeed();
}

void Tube::DrawCircleOfShapes()
{
  m_impl->DrawShapes();
}

auto Tube::GetBrightnessFactor() const -> float
{
  return m_impl->GetBrightnessFactor();
}

void Tube::SetBrightnessFactor(const float val)
{
  m_impl->SetBrightnessFactor(val);
}

auto Tube::GetMaxJitterOffset() const -> int32_t
{
  return m_impl->GetMaxJitterOffset();
}

void Tube::SetMaxJitterOffset(const int32_t val)
{
  m_impl->SetMaxJitterOffset(val);
}

class ShapeColorizer
{
public:
  struct ShapeColorMaps
  {
    const IColorMap* colorMap{};
    const IColorMap* lowColorMap{};
    const IColorMap* innerColorMap{};
    const IColorMap* innerLowColorMap{};
  };

  ShapeColorizer() noexcept = delete;
  ~ShapeColorizer() noexcept = default;
  ShapeColorizer(uint32_t screenWidth,
                 uint32_t screenHeight,
                 uint32_t numShapes,
                 uint32_t numCircles,
                 const RandomColorMaps* colorMaps,
                 const RandomColorMaps* innerColorMaps,
                 float brightnessFactor);
  ShapeColorizer(const ShapeColorizer&) noexcept = delete;
  ShapeColorizer(ShapeColorizer&&) = default;
  auto operator=(const ShapeColorizer&) -> ShapeColorizer& = delete;
  auto operator=(ShapeColorizer&&) -> ShapeColorizer& = delete;

  auto GetBrightnessFactor() const -> float;
  void SetBrightnessFactor(float val);

  void ResetColorMaps();
  void RotateShapeColorMaps();
  auto GetColors(LowColorTypes lowColorType,
                 uint32_t shapeNum,
                 uint32_t circleNum,
                 const V2dInt& pos) -> ShapeColors;
  void UpdateAllTValues();

private:
  const RandomColorMaps* const m_randomColorMaps;
  const RandomColorMaps* const m_randomInnerColorMaps;
  float m_brightnessFactor;

  GammaCorrection m_gammaCorrect{5.0F, 0.01F};

  std::vector<ShapeColorMaps> m_shapeColorMaps;
  std::vector<ShapeColors> m_oldShapeColors;
  static constexpr uint32_t NUM_SHAPE_COLOR_STEPS = 1000;
  TValue m_shapeColorsT{TValue::StepType::CONTINUOUS_REPEATABLE, NUM_SHAPE_COLOR_STEPS};

  std::vector<ShapeColorMaps> m_circleColorMaps;
  std::vector<ShapeColors> m_oldCircleColors;
  TValue m_circleColorsT{TValue::StepType::CONTINUOUS_REPEATABLE, MAX_NUM_CIRCLES_IN_GROUP};

  const IColorMap* m_outerCircleColorMap{};
  const IColorMap* m_outerCircleLowColorMap{};
  static constexpr uint32_t NUM_OUTER_CIRCLE_COLOR_STEPS = 100;
  TValue m_outerCircleT{TValue::StepType::CONTINUOUS_REVERSIBLE, NUM_OUTER_CIRCLE_COLOR_STEPS};

  ColorMapMixMode m_colorMapMixMode = ColorMapMixMode::CIRCLES_ONLY;
  static constexpr uint32_t NUM_MIX_COLOR_STEPS = 1000;
  TValue m_mixT{TValue::StepType::CONTINUOUS_REVERSIBLE, NUM_MIX_COLOR_STEPS};

  static constexpr uint32_t NUM_STEPS_FROM_OLD = 50;
  TValue m_oldT{TValue::StepType::SINGLE_CYCLE, NUM_STEPS_FROM_OLD};

  void InitColorMaps();
  void ResetColorMixMode();
  void ResetColorMapsLists();
  void ResetColorMapsList(std::vector<ShapeColorMaps>* colorMaps,
                          std::vector<ShapeColors>* oldColors,
                          TValue* t);
  void ResetColorMaps(ShapeColorMaps* colorMaps);
  void CopyColors(const ShapeColorMaps& colorMaps, const TValue& t, ShapeColors* oldColors);

  uint32_t m_stripeWidth = MIN_STRIPE_WIDTH;
  auto GetShapeNumToUse(uint32_t shapeNum) const -> uint32_t;

  [[nodiscard]] auto GetShapeColors(uint32_t shapeNum, float brightness) -> ShapeColors;
  [[nodiscard]] auto GetCircleColors(uint32_t circleNum, float brightness) -> ShapeColors;
  [[nodiscard]] auto GetColors(const ShapeColorMaps& shapeColorMaps,
                               const TValue& t,
                               const ShapeColors& oldShapeColors,
                               float brightness) const -> ShapeColors;
  static auto GetLowColor(LowColorTypes colorType, const ShapeColors& colors) -> Pixel;
  static auto GetLowMixedColor(LowColorTypes colorType,
                               const ShapeColors& colors1,
                               const ShapeColors& colors2,
                               float mixT) -> Pixel;
  static auto GetInnerLowColor(LowColorTypes colorType, const ShapeColors& colors) -> Pixel;
  static auto GetInnerLowMixedColor(LowColorTypes colorType,
                                    const ShapeColors& colors1,
                                    const ShapeColors& colors2,
                                    float mixT) -> Pixel;
  const uint32_t m_maxRSquared;
  [[nodiscard]] auto GetBrightness(const V2dInt& pos) const -> float;
  [[nodiscard]] auto GetDistFromCentreFactor(const V2dInt& pos) const -> float;
};

class ShapePath
{
public:
  static constexpr float T_AT_CENTRE = 0.5F;

  ShapePath(const V2dInt& startPos,
            const V2dInt& finishPos,
            float step,
            bool reversible,
            bool allowOscillatingPath);

  [[nodiscard]] auto GetT() const -> float;
  void SetPathParams(const PathParams& params);

  [[nodiscard]] auto GetStepSize() const -> float;
  void SetStepSize(float val);

  auto GetAllowOscillatingPath() const -> bool;
  void SetAllowOscillatingPath(bool val);

  void Reset();
  [[nodiscard]] auto GetNextPoint() const -> V2dInt;
  void IncrementT();

private:
  const V2dInt m_startPos;
  const V2dInt m_finishPos;
  TValue m_t;
  V2dInt m_currentStartPos;
  V2dInt m_currentFinishPos;
  PathParams m_pathParams{};
  bool m_allowOscillatingPath;
  [[nodiscard]] auto GetPointAtT(const V2dInt& p0, const V2dInt& p1, float t) const -> V2dInt;
  [[nodiscard]] auto GetTransformedPointAtT(const V2dFlt& point, float t) const -> V2dInt;
};

class ParametricPath
{
public:
  explicit ParametricPath() : m_t{TValue::StepType::CONTINUOUS_REVERSIBLE, NML_CENTRE_SPEED} {}
  [[nodiscard]] auto GetStepSize() const -> float { return m_t.GetStepSize(); }
  void SetStepSize(float val) { m_t.SetStepSize(val); }
  [[nodiscard]] auto GetT() const -> float { return m_t(); }
  void SetT(const float val) { m_t.Reset(val); }
  [[nodiscard]] auto GetNextPoint() const -> V2dInt;
  void Increment() { m_t.Increment(); }

private:
  TValue m_t;
  float m_b = 350.0;
  float m_kX = 3.0;
  float m_kY = 3.0;
};

auto ParametricPath::GetNextPoint() const -> V2dInt
{
  const V2dInt point{
      static_cast<int32_t>(std::round((m_b * std::cos(m_kX * m_t())) * std::cos(m_t()))),
      static_cast<int32_t>(std::round((m_b * std::cos(m_kY * m_t())) * std::sin(m_t()))),
  };

  return point;
}

Tube::TubeImpl::TubeImpl(const uint32_t tubeId,
                         const DrawFuncs& drawFuncs,
                         const uint32_t screenWidth,
                         const uint32_t screenHeight,
                         const RandomColorMaps* const colorMaps,
                         const RandomColorMaps* const lowColorMaps,
                         const float radiusEdgeOffset,
                         float brightnessFactor) noexcept
  : m_tubeId{tubeId},
    m_drawFuncs{drawFuncs},
    m_screenWidth{screenWidth},
    m_screenHeight{screenHeight},
    m_colorizer{std::make_unique<ShapeColorizer>(screenWidth,
                                                 screenHeight,
                                                 NUM_SHAPES_PER_TUBE,
                                                 MAX_NUM_CIRCLES_IN_GROUP,
                                                 colorMaps,
                                                 lowColorMaps,
                                                 brightnessFactor)},
    m_shapes(NUM_SHAPES_PER_TUBE),
    m_circleGroupTimer{GetRandInRange(MIN_NUM_CIRCLES_IN_GROUP, MAX_NUM_CIRCLES_IN_GROUP)},
    m_interiorShapeTimer{MAX_INTERIOR_SHAPES_TIME},
    m_noBoundaryShapeTimer{MAX_NO_BOUNDARY_SHAPES_TIME},
    m_hexLen{MIN_HEX_SIZE},
    m_interiorShapeSize{GetInteriorShapeSize(m_hexLen)},
    m_lowColorTypeTimer{MAX_LOW_COLOR_TYPE_TIME}
{
  InitShapes(radiusEdgeOffset);
}

Tube::TubeImpl::~TubeImpl() noexcept = default;

void Tube::TubeImpl::InitShapes(const float radiusEdgeOffset)
{
  const V2dInt middlePos{static_cast<int32_t>(m_screenWidth / 2),
                         static_cast<int32_t>(m_screenHeight / 2)};
  const auto radius =
      0.5F * static_cast<float>(std::min(m_screenWidth, m_screenHeight)) - radiusEdgeOffset;
  const float angleStep = m_two_pi / static_cast<float>(m_shapes.size());

  m_centrePath = std::make_unique<ParametricPath>();

  constexpr float PATH_STEP = NML_CIRCLE_SPEED;
  float angle = 0.0;
  uint32_t shapeNum = 0;
  for (auto& shape : m_shapes)
  {
    const float cosAngle = std::cos(angle);
    const float sinAngle = std::sin(angle);
    const float xFrom = radius * cosAngle;
    const float yFrom = radius * sinAngle;
    const V2dInt fromPos = middlePos + V2dInt{static_cast<int32_t>(std::round(xFrom)),
                                              static_cast<int32_t>(std::round(yFrom))};
    const float xTo = radius * std::cos(m_pi + angle);
    const float yTo = radius * std::sin(m_pi + angle);
    const V2dInt toPos = middlePos + V2dInt{static_cast<int32_t>(std::round(xTo)),
                                            static_cast<int32_t>(std::round(yTo))};

    shape.shapeNum = shapeNum;
    shape.path = std::make_unique<ShapePath>(fromPos, toPos, PATH_STEP, REVERSIBLE_SHAPE_PATHS,
                                             OSCILLATING_SHAPE_PATHS);
    //shape.lineThickness = ProbabilityOf(0.8) ? 1U : 2U;
    //shape.lineThickness = GetRandInRange(1U, 4U);

    angle += angleStep;
    shapeNum++;
  }
}

void Tube::TubeImpl::ResetPaths()
{
  for (auto& shape : m_shapes)
  {
    shape.path->Reset();
  }
}

void Tube::TubeImpl::ResetColorMaps()
{
  m_colorizer->ResetColorMaps();
  m_circleGroupTimer.SetTimeLimit(
      GetRandInRange(MIN_NUM_CIRCLES_IN_GROUP, MAX_NUM_CIRCLES_IN_GROUP));

  /**
  for (auto& shape : m_shapes)
  {
    shape.lineThickness = GetRandInRange(1U, 4U);
  }
   **/
}

void Tube::TubeImpl::RotateShapeColorMaps()
{
  m_colorizer->RotateShapeColorMaps();
}

inline auto Tube::TubeImpl::GetTubeId() const -> uint32_t
{
  return m_tubeId;
}

inline auto Tube::TubeImpl::IsActive() const -> bool
{
  return m_active;
}

inline auto Tube::TubeImpl::GetBrightnessFactor() const -> float
{
  return m_colorizer->GetBrightnessFactor();
}

inline void Tube::TubeImpl::SetBrightnessFactor(const float val)
{
  m_colorizer->SetBrightnessFactor(val);
}

inline auto Tube::TubeImpl::GetMaxJitterOffset() const -> int32_t
{
  return m_maxJitterOffset;
}

inline void Tube::TubeImpl::SetMaxJitterOffset(const int32_t val)
{
  m_maxJitterOffset = val;
}

inline void Tube::TubeImpl::SetTransformCentreFunc(const TransformCentreFunc& f)
{
  m_getTransformedCentre = f;
}

inline auto Tube::TubeImpl::GetCentrePathT() const -> float
{
  return m_centrePath->GetT();
}

inline void Tube::TubeImpl::SetCentrePathT(const float val)
{
  m_centrePath->SetT(val);
}

inline auto Tube::TubeImpl::GetCentreSpeed() const -> float
{
  return m_centrePath->GetStepSize();
}

inline void Tube::TubeImpl::SetCentreSpeed(const float val)
{
  m_centrePath->SetStepSize(val);
}

void Tube::TubeImpl::IncreaseCentreSpeed()
{
  const float factor = GetRandInRange(1.01F, 10.0F);
  const float newSpeed = std::min(MAX_CENTRE_SPEED, m_centrePath->GetStepSize() * factor);
  m_centrePath->SetStepSize(newSpeed);
}

void Tube::TubeImpl::DecreaseCentreSpeed()
{
  const float factor = GetRandInRange(0.1F, 0.99F);
  const float newSpeed = std::min(MIN_CENTRE_SPEED, m_centrePath->GetStepSize() * factor);
  m_centrePath->SetStepSize(newSpeed);
}

void Tube::TubeImpl::SetOscillatingCirclePaths(const bool val)
{
  for (auto& shape : m_shapes)
  {
    shape.path->SetAllowOscillatingPath(val);
  }
}

void Tube::TubeImpl::SetCirclePathParams(const PathParams& params)
{
  for (auto& shape : m_shapes)
  {
    shape.path->SetPathParams(params);
  }
}

inline auto Tube::TubeImpl::GetCircleSpeed() const -> float
{
  return m_shapes[0].path->GetStepSize();
}

inline void Tube::TubeImpl::SetCircleSpeed(const float val)
{
  for (auto& shape : m_shapes)
  {
    shape.path->SetStepSize(val);
  }
}

void Tube::TubeImpl::IncreaseCircleSpeed()
{
  constexpr float MIN_INCREASE_SPEED_FACTOR = 1.01F;
  constexpr float MAX_INCREASE_SPEED_FACTOR = 10.0F;
  const float factor = GetRandInRange(MIN_INCREASE_SPEED_FACTOR, MAX_INCREASE_SPEED_FACTOR);

  for (auto& shape : m_shapes)
  {
    const float newSpeed = std::min(MAX_CIRCLE_SPEED, shape.path->GetStepSize() * factor);
    shape.path->SetStepSize(newSpeed);
  }
}

void Tube::TubeImpl::DecreaseCircleSpeed()
{
  constexpr float MIN_DECREASE_SPEED_FACTOR = 0.1F;
  constexpr float MAX_DECREASE_SPEED_FACTOR = 0.99F;
  const float factor = GetRandInRange(MIN_DECREASE_SPEED_FACTOR, MAX_DECREASE_SPEED_FACTOR);

  for (auto& shape : m_shapes)
  {
    const float newSpeed = std::max(MIN_CIRCLE_SPEED, shape.path->GetStepSize() * factor);
    shape.path->SetStepSize(newSpeed);
  }
}

void Tube::TubeImpl::DrawShapes()
{
  m_hexLen = GetHexLen();
  m_interiorShapeSize = GetInteriorShapeSize(m_hexLen);

  const V2dInt centrePoint = m_getTransformedCentre(m_tubeId, m_centrePath->GetNextPoint());
  for (auto& shape : m_shapes)
  {
    DrawShape(shape, centrePoint);
  }

  UpdateTValues();
  UpdateTimers();
}

inline auto Tube::TubeImpl::GetHexLen() const -> float
{
  const float hexSizeT =
      std::fabs(m_shapes[0].path->GetT() - ShapePath::T_AT_CENTRE) / ShapePath::T_AT_CENTRE;
  return stdnew::lerp(MIN_HEX_SIZE, MAX_HEX_SIZE, hexSizeT);
}

void Tube::TubeImpl::UpdateTValues()
{
  m_centrePath->Increment();
  m_colorizer->UpdateAllTValues();
}

void Tube::TubeImpl::UpdateTimers()
{
  m_circleGroupTimer.Increment();
  if (m_circleGroupTimer.Finished())
  {
    m_circleGroupTimer.ResetToZero();
  }

  m_interiorShapeTimer.Increment();
  if (m_interiorShapeTimer.Finished() && ProbabilityOf(PROB_INTERIOR_SHAPE))
  {
    m_interiorShapeTimer.ResetToZero();
  }

  m_noBoundaryShapeTimer.Increment();
  if (m_noBoundaryShapeTimer.Finished() && ProbabilityOf(PROB_NO_BOUNDARY_SHAPES))
  {
    m_noBoundaryShapeTimer.ResetToZero();
  }

  m_lowColorTypeTimer.Increment();
  if (m_lowColorTypeTimer.Finished())
  {
    m_currentLowColorType = S_LOW_COLOR_TYPES.GetRandomWeighted();
    m_lowColorTypeTimer.SetTimeLimit(
        GetRandInRange(MIN_LOW_COLOR_TYPE_TIME, MAX_LOW_COLOR_TYPE_TIME + 1));
  }
}

inline auto Tube::TubeImpl::GetInteriorShapeSize(const float hexLen) -> uint32_t
{
  constexpr float MIN_SIZE_FACTOR = 0.5F;
  constexpr float MAX_SIZE_FACTOR = 1.3F;
  return static_cast<uint32_t>(
      std::round(GetRandInRange(MIN_SIZE_FACTOR, MAX_SIZE_FACTOR) * hexLen));
}

void Tube::TubeImpl::DrawShape(const Shape& shape, const V2dInt& centreOffset)
{
  const int32_t jitterXOffset = GetRandInRange(0, m_maxJitterOffset + 1);
  const int32_t jitterYOffset = jitterXOffset;
  const V2dInt jitterOffset{jitterXOffset, jitterYOffset};
  const V2dInt shapeCentrePos = shape.path->GetNextPoint() + jitterOffset + centreOffset;

  const ShapeColors allColors = m_colorizer->GetColors(
      m_currentLowColorType, shape.shapeNum, m_circleGroupTimer.GetCurrentCount(), shapeCentrePos);

  if (m_noBoundaryShapeTimer.Finished())
  {
    const std::vector<Pixel> lineColors{allColors.color, allColors.lowColor};
    DrawHexOutline(shapeCentrePos, lineColors, shape.lineThickness);
  }

  constexpr float MIN_HEX_LEN_FOR_INTERIOR = 2.0;
  if (!m_interiorShapeTimer.Finished() && m_hexLen > MIN_HEX_LEN_FOR_INTERIOR + SMALL_FLOAT)
  {
    DrawInteriorShape(shapeCentrePos, allColors);
  }

  shape.path->IncrementT();
}

void Tube::TubeImpl::DrawHexOutline(const V2dInt& hexCentre,
                                    const std::vector<Pixel>& lineColors,
                                    const uint8_t lineThickness) const
{
  constexpr uint32_t NUM_HEX_SIDES = 6;
  constexpr float ANGLE_STEP = GOOM::UTILS::m_third_pi;
  constexpr float START_ANGLE = 2.0 * ANGLE_STEP;

  // Start hex shape to right of centre position.
  auto x0 = static_cast<int32_t>(std::round(static_cast<float>(hexCentre.x) + m_hexLen));
  int32_t y0 = hexCentre.y;
  float angle = START_ANGLE;

  for (uint32_t i = 0; i < NUM_HEX_SIDES; i++)
  {
    const int32_t x1 = x0 + static_cast<int32_t>(std::round(m_hexLen * std::cos(angle)));
    const int32_t y1 = y0 + static_cast<int32_t>(std::round(m_hexLen * std::sin(angle)));

    m_drawFuncs.drawLine(x0, y0, x1, y1, lineColors, lineThickness);

    angle += ANGLE_STEP;
    x0 = x1;
    y0 = y1;
  }
}

inline void Tube::TubeImpl::DrawInteriorShape(const V2dInt& shapeCentrePos,
                                              const ShapeColors& allColors) const
{
  const std::vector<Pixel> colors{allColors.innerColor, allColors.innerLowColor};
  m_drawFuncs.drawSmallImage(shapeCentrePos.x, shapeCentrePos.y,
                             SmallImageBitmaps::ImageNames::SPHERE, m_interiorShapeSize, colors);

  constexpr float OUTER_CIRCLE_RADIUS_FACTOR = 1.5;
  const auto outerCircleRadius =
      static_cast<int32_t>(std::round(OUTER_CIRCLE_RADIUS_FACTOR * m_hexLen));
  constexpr uint8_t OUTER_CIRCLE_LINE_THICKNESS = 1;
  const std::vector<Pixel> outerCircleColors{allColors.outerCircleColor,
                                             allColors.outerCircleLowColor};
  m_drawFuncs.drawCircle(shapeCentrePos.x, shapeCentrePos.y, outerCircleRadius, outerCircleColors,
                         OUTER_CIRCLE_LINE_THICKNESS);
}

ShapeColorizer::ShapeColorizer(const uint32_t screenWidth,
                               const uint32_t screenHeight,
                               const uint32_t numShapes,
                               const uint32_t numCircles,
                               const RandomColorMaps* const colorMaps,
                               const RandomColorMaps* const innerColorMaps,
                               const float brightnessFactor)
  : m_randomColorMaps{colorMaps},
    m_randomInnerColorMaps{innerColorMaps},
    m_brightnessFactor{brightnessFactor},
    m_shapeColorMaps(numShapes),
    m_oldShapeColors(numShapes),
    m_circleColorMaps(numCircles),
    m_oldCircleColors(numCircles),
    m_maxRSquared{2 * Sq(std::min(screenWidth, screenHeight) / 2)}
{
  InitColorMaps();
  ResetColorMaps();
}

inline auto ShapeColorizer::GetBrightnessFactor() const -> float
{
  return m_brightnessFactor;
}

inline void ShapeColorizer::SetBrightnessFactor(float val)
{
  m_brightnessFactor = val;
}

void ShapeColorizer::InitColorMaps()
{
  for (auto& cm : m_shapeColorMaps)
  {
    ResetColorMaps(&cm);
  }
  for (auto& cm : m_circleColorMaps)
  {
    ResetColorMaps(&cm);
  }
}

void ShapeColorizer::ResetColorMaps()
{
  ResetColorMixMode();
  ResetColorMapsLists();

  m_stripeWidth = GetRandInRange(MIN_STRIPE_WIDTH, MAX_STRIPE_WIDTH + 1);
}

inline void ShapeColorizer::ResetColorMapsLists()
{
  ResetColorMapsList(&m_shapeColorMaps, &m_oldShapeColors, &m_shapeColorsT);
  ResetColorMapsList(&m_circleColorMaps, &m_oldCircleColors, &m_circleColorsT);
}

void ShapeColorizer::RotateShapeColorMaps()
{
  //ShapeColorMaps lastShapeColorMaps = m_shapeColorMaps.back();
  //std::shift_right(begin(m_shapeColorMaps), end(m_shapeColorMaps), 2);
  std::rotate(begin(m_shapeColorMaps), begin(m_shapeColorMaps) + 1, end(m_shapeColorMaps));
  std::rotate(begin(m_oldShapeColors), begin(m_oldShapeColors) + 1, end(m_oldShapeColors));
}

void ShapeColorizer::ResetColorMapsList(std::vector<ShapeColorMaps>* colorMaps,
                                        std::vector<ShapeColors>* oldColors,
                                        TValue* t)
{
  m_outerCircleColorMap = &m_randomInnerColorMaps->GetRandomColorMap();
  m_outerCircleLowColorMap = &m_randomInnerColorMaps->GetRandomColorMap();

  for (size_t i = 0; i < colorMaps->size(); i++)
  {
    CopyColors((*colorMaps)[i], *t, &(*oldColors)[i]);
    ResetColorMaps(&(*colorMaps)[i]);
  }
  t->Reset(0.0);
}

void ShapeColorizer::ResetColorMaps(ShapeColorMaps* colorMaps)
{
  colorMaps->colorMap = &m_randomColorMaps->GetRandomColorMap();
  colorMaps->lowColorMap = &m_randomColorMaps->GetRandomColorMap();
  colorMaps->innerColorMap = &m_randomInnerColorMaps->GetRandomColorMap();
  colorMaps->innerLowColorMap = &m_randomInnerColorMaps->GetRandomColorMap();
}

void ShapeColorizer::CopyColors(const ShapeColorMaps& colorMaps,
                                const TValue& t,
                                ShapeColors* oldColors)
{
  oldColors->color = colorMaps.colorMap->GetColor(t());
  oldColors->lowColor = colorMaps.lowColorMap->GetColor(t());
  oldColors->innerColor = colorMaps.innerColorMap->GetColor(t());
  oldColors->innerLowColor = colorMaps.innerLowColorMap->GetColor(t());
  oldColors->outerCircleColor = m_outerCircleColorMap->GetColor(t());
  oldColors->outerCircleLowColor = m_outerCircleLowColorMap->GetColor(t());
}

inline void ShapeColorizer::ResetColorMixMode()
{
  m_colorMapMixMode = S_COLOR_MAP_MIX_MODES.GetRandomWeighted();
}

void ShapeColorizer::UpdateAllTValues()
{
  m_shapeColorsT.Increment();
  m_circleColorsT.Increment();
  m_outerCircleT.Increment();
  m_oldT.Increment();
  m_mixT.Increment();
}

auto ShapeColorizer::GetColors(const LowColorTypes lowColorType,
                               const uint32_t shapeNum,
                               const uint32_t circleNum,
                               const V2dInt& pos) -> ShapeColors
{
  const float brightness = m_brightnessFactor * GetBrightness(pos);

  switch (m_colorMapMixMode)
  {
    case ColorMapMixMode::STRIPED_SHAPES_ONLY:
    case ColorMapMixMode::SHAPES_ONLY:
    {
      const ShapeColors colors = GetShapeColors(GetShapeNumToUse(shapeNum), brightness);
      return {
          colors.color,
          GetLowColor(lowColorType, colors),
          colors.innerColor,
          GetInnerLowColor(lowColorType, colors),
          colors.outerCircleColor,
          colors.outerCircleLowColor,
      };
    }
    case ColorMapMixMode::CIRCLES_ONLY:
    {
      const ShapeColors colors = GetCircleColors(circleNum, brightness);
      return {
          colors.color,
          GetLowColor(lowColorType, colors),
          colors.innerColor,
          GetInnerLowColor(lowColorType, colors),
          colors.outerCircleColor,
          colors.outerCircleLowColor,
      };
    }
    case ColorMapMixMode::STRIPED_SHAPES_AND_CIRCLES:
    case ColorMapMixMode::SHAPES_AND_CIRCLES:
    {
      const ShapeColors shapeColors = GetShapeColors(GetShapeNumToUse(shapeNum), brightness);
      const ShapeColors circleColors = GetCircleColors(circleNum, brightness);

      return {
          IColorMap::GetColorMix(shapeColors.color, circleColors.color, m_mixT()),
          GetLowMixedColor(lowColorType, shapeColors, circleColors, m_mixT()),
          IColorMap::GetColorMix(shapeColors.innerColor, circleColors.innerColor, m_mixT()),
          GetInnerLowMixedColor(lowColorType, shapeColors, circleColors, m_mixT()),
          IColorMap::GetColorMix(shapeColors.outerCircleColor, circleColors.outerCircleColor,
                                 m_mixT()),
          IColorMap::GetColorMix(shapeColors.outerCircleLowColor, circleColors.outerCircleLowColor,
                                 m_mixT()),
      };
    }
    default:
      throw std::logic_error("Invalid ColorMapMixMode.");
  }
}

inline auto ShapeColorizer::GetLowColor(const LowColorTypes colorType, const ShapeColors& colors)
    -> Pixel
{
  if (colorType == LowColorTypes::LIGHTENED_LOW_COLOR)
  {
    return GetLightenedColor(colors.color, LIGHTER_COLOR_POWER);
  }
  if (colorType == LowColorTypes::MAIN_COLOR)
  {
    return colors.color;
  }
  return colors.lowColor;
}

inline auto ShapeColorizer::GetInnerLowColor(const LowColorTypes colorType,
                                             const ShapeColors& colors) -> Pixel
{
  if (colorType == LowColorTypes::LIGHTENED_LOW_COLOR)
  {
    return GetLightenedColor(colors.innerLowColor, LIGHTER_COLOR_POWER);
  }
  if (colorType == LowColorTypes::MAIN_COLOR)
  {
    return colors.innerColor;
  }
  return colors.innerLowColor;
}

inline auto ShapeColorizer::GetLowMixedColor(const LowColorTypes colorType,
                                             const ShapeColors& colors1,
                                             const ShapeColors& colors2,
                                             const float mixT) -> Pixel
{
  if (colorType == LowColorTypes::LIGHTENED_LOW_COLOR)
  {
    const Pixel mixedColor = IColorMap::GetColorMix(colors1.lowColor, colors2.lowColor, mixT);
    return GetLightenedColor(mixedColor, LIGHTER_COLOR_POWER);
  }
  if (colorType == LowColorTypes::MAIN_COLOR)
  {
    const Pixel mixedColor = IColorMap::GetColorMix(colors1.color, colors2.color, mixT);
    return mixedColor;
  }
  const Pixel mixedColor = IColorMap::GetColorMix(colors1.lowColor, colors2.lowColor, mixT);
  return mixedColor;
}

inline auto ShapeColorizer::GetInnerLowMixedColor(const LowColorTypes colorType,
                                                  const ShapeColors& colors1,
                                                  const ShapeColors& colors2,
                                                  const float mixT) -> Pixel
{
  if (colorType == LowColorTypes::LIGHTENED_LOW_COLOR)
  {
    const Pixel mixedColor =
        IColorMap::GetColorMix(colors1.innerLowColor, colors2.innerLowColor, mixT);
    return GetLightenedColor(mixedColor, LIGHTER_COLOR_POWER);
  }
  if (colorType == LowColorTypes::MAIN_COLOR)
  {
    const Pixel mixedColor = IColorMap::GetColorMix(colors1.innerColor, colors2.innerColor, mixT);
    return mixedColor;
  }
  const Pixel mixedColor =
      IColorMap::GetColorMix(colors1.innerLowColor, colors2.innerLowColor, mixT);
  return mixedColor;
}

inline auto ShapeColorizer::GetShapeNumToUse(const uint32_t shapeNum) const -> uint32_t
{
  return m_colorMapMixMode == ColorMapMixMode::STRIPED_SHAPES_ONLY ||
                 m_colorMapMixMode == ColorMapMixMode::STRIPED_SHAPES_AND_CIRCLES
             ? shapeNum / m_stripeWidth
             : shapeNum;
}

inline auto ShapeColorizer::GetShapeColors(const uint32_t shapeNum, const float brightness)
    -> ShapeColors
{
  return GetColors(m_shapeColorMaps[shapeNum], m_shapeColorsT, m_oldShapeColors[shapeNum],
                   brightness);
}

inline auto ShapeColorizer::GetCircleColors(const uint32_t circleNum, const float brightness)
    -> ShapeColors
{
  return GetColors(m_circleColorMaps[circleNum], m_circleColorsT, m_oldCircleColors[circleNum],
                   brightness);
}

auto ShapeColorizer::GetColors(const ShapeColorMaps& shapeColorMaps,
                               const TValue& t,
                               const ShapeColors& oldShapeColors,
                               const float brightness) const -> ShapeColors
{
  const Pixel color = IColorMap::GetColorMix(oldShapeColors.color,
                                             shapeColorMaps.colorMap->GetColor(t()), m_oldT());
  const Pixel lowColor = IColorMap::GetColorMix(
      oldShapeColors.lowColor, shapeColorMaps.lowColorMap->GetColor(t()), m_oldT());
  const Pixel innerColor = IColorMap::GetColorMix(
      oldShapeColors.innerColor, shapeColorMaps.innerColorMap->GetColor(t()), m_oldT());
  const Pixel innerLowColor = IColorMap::GetColorMix(
      oldShapeColors.innerLowColor, shapeColorMaps.innerLowColorMap->GetColor(t()), m_oldT());
  const Pixel outerCircleColor = IColorMap::GetColorMix(
      oldShapeColors.outerCircleColor, m_outerCircleColorMap->GetColor(m_outerCircleT()), m_oldT());
  const Pixel outerCircleLowColor =
      IColorMap::GetColorMix(oldShapeColors.outerCircleLowColor,
                             m_outerCircleLowColorMap->GetColor(m_outerCircleT()), m_oldT());

  return {
      m_gammaCorrect.GetCorrection(brightness, color),
      m_gammaCorrect.GetCorrection(brightness, lowColor),
      m_gammaCorrect.GetCorrection(brightness, innerColor),
      m_gammaCorrect.GetCorrection(brightness, innerLowColor),
      m_gammaCorrect.GetCorrection(OUTER_CIRCLE_BRIGHTNESS * brightness, outerCircleColor),
      m_gammaCorrect.GetCorrection(OUTER_CIRCLE_BRIGHTNESS * brightness, outerCircleLowColor),
  };
}

inline auto ShapeColorizer::GetBrightness(const V2dInt& pos) const -> float
{
  const float distFromCentre = GetDistFromCentreFactor(pos);
  constexpr float DIST_SQ_CUTOFF = 0.02F;
  constexpr float CUTOFF_BRIGHTNESS = 0.005F;
  constexpr float MIN_BRIGHTNESS = 0.75F;
  return distFromCentre < DIST_SQ_CUTOFF ? CUTOFF_BRIGHTNESS : MIN_BRIGHTNESS + distFromCentre;
}

inline auto ShapeColorizer::GetDistFromCentreFactor(const V2dInt& pos) const -> float
{
  return static_cast<float>(Sq(pos.x) + Sq(pos.y)) / static_cast<float>(m_maxRSquared);
}

inline ShapePath::ShapePath(const V2dInt& startPos,
                            const V2dInt& finishPos,
                            const float step,
                            const bool reversible,
                            const bool allowOscillatingPath)
  : m_startPos{startPos},
    m_finishPos{finishPos},
    m_t{reversible ? TValue::StepType::CONTINUOUS_REVERSIBLE
                   : TValue::StepType::CONTINUOUS_REPEATABLE,
        step},
    m_currentStartPos{m_startPos},
    m_currentFinishPos{m_finishPos},
    m_allowOscillatingPath{allowOscillatingPath}
{
}

inline auto ShapePath::GetT() const -> float
{
  return m_t();
}

inline auto ShapePath::GetStepSize() const -> float
{
  return m_t.GetStepSize();
}

inline void ShapePath::SetStepSize(const float val)
{
  m_t.SetStepSize(val);
}

inline auto ShapePath::GetAllowOscillatingPath() const -> bool
{
  return m_allowOscillatingPath;
}

inline void ShapePath::SetAllowOscillatingPath(const bool val)
{
  m_allowOscillatingPath = val;
}

inline void ShapePath::Reset()
{
  m_currentStartPos = m_startPos;
  m_currentFinishPos = m_finishPos;
  m_t.Reset(0.0);
}

inline void ShapePath::SetPathParams(const PathParams& params)
{
  m_pathParams = params;
}

inline void ShapePath::IncrementT()
{
  m_t.Increment();
}

inline auto ShapePath::GetNextPoint() const -> V2dInt
{
  return GetPointAtT(m_currentStartPos, m_currentFinishPos, m_t());
}

inline auto ShapePath::GetPointAtT(const V2dInt& p0, const V2dInt& p1, const float t) const
    -> V2dInt
{
  const V2dFlt linearPoint = lerp(p0.ToFlt(), p1.ToFlt(), t);
  if (!m_allowOscillatingPath)
  {
    return {static_cast<int32_t>(std::round(linearPoint.x)),
            static_cast<int32_t>(std::round(linearPoint.y))};
  }

  const V2dInt point = GetTransformedPointAtT(linearPoint, t);
  return {static_cast<int32_t>(std::round(point.x)), static_cast<int32_t>(std::round(point.y))};
}

inline auto ShapePath::GetTransformedPointAtT(const V2dFlt& point, const float t) const -> V2dInt
{
  return {
      static_cast<int32_t>(std::round(point.x + m_pathParams.amplitude *
                                                    std::cos(m_pathParams.xFreq * t * m_two_pi))),
      static_cast<int32_t>(std::round(point.y + m_pathParams.amplitude *
                                                    std::sin(m_pathParams.yFreq * t * m_two_pi))),
  };
}

#if __cplusplus <= 201402L
} // namespace TUBES
} // namespace GOOM
#else
} // namespace GOOM::TENTACLES
#endif
