#include "tubes.h"

//#undef NO_LOGGING

#include "color/color_adjustment.h"
#include "color/color_maps.h"
#include "color/color_utils.h"
#include "color/random_color_maps.h"
#include "draw/goom_draw.h"
#include "goom_config.h"
#include "logging.h"
#include "point2d.h"
#include "spimpl.h"
#include "utils/graphics/small_image_bitmaps.h"
#include "utils/math/goom_rand_base.h"
#include "utils/math/misc.h"
#include "utils/math/paths.h"
#include "utils/propagate_const.h"
#include "utils/t_values.h"
#include "utils/timer.h"

#include <array>
#include <cstdint>
#include <memory>
#include <vector>

namespace GOOM::VISUAL_FX::TUBES
{

using COLOR::ColorAdjustment;
using COLOR::GetLightenedColor;
using COLOR::IColorMap;
using COLOR::RandomColorMaps;
using DRAW::MultiplePixels;
using std::experimental::propagate_const;
using STD20::pi;
using UTILS::Logging; // NOLINT(misc-unused-using-decls)
using UTILS::Timer;
using UTILS::TValue;
using UTILS::GRAPHICS::SmallImageBitmaps;
using UTILS::MATH::ISimplePath;
using UTILS::MATH::OscillatingFunction;
using UTILS::MATH::OscillatingPath;
using UTILS::MATH::PI;
using UTILS::MATH::SMALL_FLOAT;
using UTILS::MATH::Sq;
using UTILS::MATH::THIRD_PI;
using UTILS::MATH::TWO_PI;
using UTILS::MATH::U_HALF;
using UTILS::MATH::Weights;

static constexpr auto NUM_SHAPES_PER_TUBE = 45U;
// Strangely, 'NUM_SHAPES_PER_TUBE = 100' gives a small gap in
// circle at 90 and 270 degrees.

static constexpr auto PROB_INTERIOR_SHAPE         = 45.0F / 50.0F;
static constexpr auto MAX_INTERIOR_SHAPES_TIME    = 500U;
static constexpr auto PROB_NO_BOUNDARY_SHAPES     = 10.0F / 50.0F;
static constexpr auto MAX_NO_BOUNDARY_SHAPES_TIME = 1U;
static constexpr auto PROB_HEX_DOT_SHAPE          = 1.0F / 50.0F;
static constexpr auto MAX_HEX_DOT_SHAPES_TIME     = 100U;

static constexpr auto MIN_STRIPE_WIDTH = NUM_SHAPES_PER_TUBE / 6;
static constexpr auto MAX_STRIPE_WIDTH = NUM_SHAPES_PER_TUBE / 3;
static_assert(MIN_STRIPE_WIDTH > 0);

static constexpr auto MIN_NUM_CIRCLES_IN_GROUP = 10U;
static constexpr auto MAX_NUM_CIRCLES_IN_GROUP = 100U;

static constexpr auto MIN_HEX_SIZE = 3.0F;
static constexpr auto MAX_HEX_SIZE = 9.0F;

static constexpr auto MIN_CIRCLE_SPEED = 0.0005F;
static constexpr auto NML_CIRCLE_SPEED = 0.005F;
static constexpr auto MAX_CIRCLE_SPEED = 0.008F;

static constexpr auto MIN_CENTRE_SPEED = 0.0005F;
static constexpr auto NML_CENTRE_SPEED = 0.005F;
static constexpr auto MAX_CENTRE_SPEED = 0.05F;

enum class LowColorTypes
{
  TRUE_LOW_COLOR,
  MAIN_COLOR,
  LIGHTENED_LOW_COLOR,
  _num // unused, and marks the enum end
};
static constexpr auto MIN_LOW_COLOR_TYPE_TIME = 100U;
static constexpr auto MAX_LOW_COLOR_TYPE_TIME = 1000U;

static constexpr auto OUTER_CIRCLE_BRIGHTNESS = 0.4F;
static constexpr auto LIGHTER_COLOR_POWER     = 10.0F;

class ShapeColorizer;

class TubeParametricPath : public ISimplePath
{
public:
  explicit TubeParametricPath(std::unique_ptr<TValue> positionT) noexcept;

  [[nodiscard]] auto GetClone() const noexcept -> std::unique_ptr<IPath> override;
  [[nodiscard]] auto GetNextPoint() const noexcept -> Point2dInt override;

private:
  static constexpr float DEFAULT_B   = 350.0F;
  float m_b                          = DEFAULT_B;
  static constexpr float DEFAULT_K_X = 3.0F;
  float m_kX                         = DEFAULT_K_X;
  static constexpr float DEFAULT_K_Y = 3.0F;
  float m_kY                         = DEFAULT_K_Y;
};

TubeParametricPath::TubeParametricPath(std::unique_ptr<TValue> positionT) noexcept
  : ISimplePath{std::move(positionT)}
{
}

auto TubeParametricPath::GetClone() const noexcept -> std::unique_ptr<IPath>
{
  return std::make_unique<TubeParametricPath>(std::make_unique<TValue>(GetPositionT()));
}

auto TubeParametricPath::GetNextPoint() const noexcept -> Point2dInt
{
  const auto point = Point2dInt{
      static_cast<int32_t>(
          std::round((m_b * std::cos(m_kX * GetCurrentT())) * std::cos(GetCurrentT()))),
      static_cast<int32_t>(
          std::round((m_b * std::cos(m_kY * GetCurrentT())) * std::sin(GetCurrentT()))),
  };

  return point;
}

struct Shape
{
  uint32_t shapeNum{};
  propagate_const<std::unique_ptr<OscillatingPath>> path{};
  uint8_t lineThickness{1};
};

class Tube::TubeImpl
{
public:
  TubeImpl() noexcept = delete;
  TubeImpl(const TubeData& data, const OscillatingFunction::Params& pathParams);

  [[nodiscard]] auto GetTubeId() const -> uint32_t;
  [[nodiscard]] auto IsActive() const -> bool;

  void SetWeightedMainColorMaps(std::shared_ptr<const RandomColorMaps> weightedMaps);
  void SetWeightedLowColorMaps(std::shared_ptr<const RandomColorMaps> weightedMaps);

  void ResetColorMaps();
  void RotateShapeColorMaps();

  [[nodiscard]] auto GetBrightnessFactor() const -> float;
  void SetBrightnessFactor(float val);

  [[nodiscard]] auto GetMaxJitterOffset() const -> int32_t;
  void SetMaxJitterOffset(int32_t val);

  void SetTransformCentreFunc(const TransformCentreFunc& func);
  [[nodiscard]] auto GetCentrePathT() const -> float;
  void SetCentrePathT(float val);
  [[nodiscard]] auto GetCentreSpeed() const -> float;
  void SetCentreSpeed(float val);
  void IncreaseCentreSpeed();
  void DecreaseCentreSpeed();

  void SetAllowOscillatingCirclePaths(bool val);
  void SetCirclePathParams(const OscillatingFunction::Params& params);
  [[nodiscard]] auto GetCircleSpeed() const -> float;
  void SetCircleSpeed(float val);
  void IncreaseCircleSpeed();
  void DecreaseCircleSpeed();

  void DrawShapes();
  void UpdateTValues();
  void UpdateTimers();

private:
  const TubeData m_data;
  propagate_const<std::unique_ptr<ShapeColorizer>> m_colorizer{
      std::make_unique<ShapeColorizer>(m_data, NUM_SHAPES_PER_TUBE, MAX_NUM_CIRCLES_IN_GROUP)};
  bool m_active                                = true;
  static constexpr float PATH_STEP             = NML_CIRCLE_SPEED;
  static constexpr uint32_t SHAPE_T_DELAY_TIME = 10;
  static constexpr float T_AT_CENTRE           = 0.5F;
  int32_t m_maxJitterOffset                    = 0;
  propagate_const<std::unique_ptr<TubeParametricPath>> m_centrePath{
      std::make_unique<TubeParametricPath>(
          std::make_unique<TValue>(TValue::StepType::CONTINUOUS_REVERSIBLE, PATH_STEP))};
  TransformCentreFunc m_getTransformedCentre{};
  std::vector<Shape> m_shapes;
  [[nodiscard]] static auto GetInitialShapes(const TubeData& data,
                                             const OscillatingFunction::Params& pathParams)
      -> std::vector<Shape>;

  Timer m_circleGroupTimer{
      m_data.goomRand.GetRandInRange(MIN_NUM_CIRCLES_IN_GROUP, MAX_NUM_CIRCLES_IN_GROUP)};
  Timer m_interiorShapeTimer{MAX_INTERIOR_SHAPES_TIME};
  Timer m_noBoundaryShapeTimer{MAX_NO_BOUNDARY_SHAPES_TIME};
  Timer m_hexDotShapeTimer{MAX_HEX_DOT_SHAPES_TIME, true};
  float m_hexLen = MIN_HEX_SIZE;
  [[nodiscard]] auto GetHexLen() const -> float;
  uint32_t m_interiorShapeSize{GetInteriorShapeSize(m_hexLen)};
  [[nodiscard]] auto GetInteriorShapeSize(float hexLen) const -> uint32_t;

  Timer m_lowColorTypeTimer{MAX_LOW_COLOR_TYPE_TIME};
  LowColorTypes m_currentLowColorType = LowColorTypes::TRUE_LOW_COLOR;
  const Weights<LowColorTypes> m_lowColorTypes;

  void DrawShape(const Shape& shape, const Vec2dInt& centreOffset) const;
  void DrawInteriorShape(const Point2dInt& shapeCentrePos, const ShapeColors& allColors) const;
  void DrawHexOutline(const Point2dInt& hexCentre,
                      const ShapeColors& allColors,
                      uint8_t lineThickness) const;
  void DrawOuterCircle(const Point2dInt& shapeCentrePos, const ShapeColors& allColors) const;
};

const float Tube::NORMAL_CENTRE_SPEED = NML_CENTRE_SPEED;
const float Tube::NORMAL_CIRCLE_SPEED = NML_CIRCLE_SPEED;

Tube::Tube(const TubeData& data, const OscillatingFunction::Params& pathParams) noexcept
  : m_pimpl{spimpl::make_unique_impl<Tube::TubeImpl>(data, pathParams)}
{
}

void Tube::SetWeightedMainColorMaps(const std::shared_ptr<const RandomColorMaps> weightedMaps)
{
  m_pimpl->SetWeightedMainColorMaps(weightedMaps);
}

void Tube::SetWeightedLowColorMaps(const std::shared_ptr<const RandomColorMaps> weightedMaps)
{
  m_pimpl->SetWeightedLowColorMaps(weightedMaps);
}

void Tube::ResetColorMaps()
{
  m_pimpl->ResetColorMaps();
}

auto Tube::IsActive() const -> bool
{
  return m_pimpl->IsActive();
}

void Tube::SetTransformCentreFunc(const TransformCentreFunc& func)
{
  m_pimpl->SetTransformCentreFunc(func);
}

void Tube::SetCentrePathT(const float val)
{
  m_pimpl->SetCentrePathT(val);
}

void Tube::SetCentreSpeed(const float val)
{
  m_pimpl->SetCentreSpeed(val);
}

void Tube::IncreaseCentreSpeed()
{
  m_pimpl->IncreaseCentreSpeed();
}

void Tube::DecreaseCentreSpeed()
{
  m_pimpl->DecreaseCentreSpeed();
}

void Tube::SetAllowOscillatingCirclePaths(const bool val)
{
  m_pimpl->SetAllowOscillatingCirclePaths(val);
}

void Tube::SetCirclePathParams(const OscillatingFunction::Params& params)
{
  m_pimpl->SetCirclePathParams(params);
}

void Tube::SetCircleSpeed(const float val)
{
  m_pimpl->SetCircleSpeed(val);
}

void Tube::IncreaseCircleSpeed()
{
  m_pimpl->IncreaseCircleSpeed();
}

void Tube::DecreaseCircleSpeed()
{
  m_pimpl->DecreaseCircleSpeed();
}

void Tube::DrawCircleOfShapes()
{
  m_pimpl->DrawShapes();
}

void Tube::SetBrightnessFactor(const float val)
{
  m_pimpl->SetBrightnessFactor(val);
}

void Tube::SetMaxJitterOffset(const int32_t val)
{
  m_pimpl->SetMaxJitterOffset(val);
}

class ShapeColorizer
{
public:
  struct ShapeColorMaps
  {
    const IColorMap* mainColorMap{};
    const IColorMap* lowColorMap{};
    const IColorMap* innerMainColorMap{};
    const IColorMap* innerLowColorMap{};
  };

  ShapeColorizer() noexcept = delete;
  ShapeColorizer(const TubeData& data, uint32_t numShapes, uint32_t numCircles);

  [[nodiscard]] auto GetBrightnessFactor() const -> float;
  void SetBrightnessFactor(float val);

  void SetWeightedMainColorMaps(std::shared_ptr<const RandomColorMaps> weightedMaps);
  void SetWeightedLowColorMaps(std::shared_ptr<const RandomColorMaps> weightedMaps);

  void ResetColorMaps();
  void RotateShapeColorMaps();
  [[nodiscard]] auto GetColors(LowColorTypes lowColorType,
                               uint32_t circleNum,
                               const Shape& shape,
                               const Point2dInt& shapeCentrePos) const -> ShapeColors;
  void UpdateAllTValues();

private:
  TubeData m_data;

  static constexpr auto GAMMA = 1.0F;
  const ColorAdjustment m_colorAdjust{GAMMA, ColorAdjustment::INCREASED_CHROMA_FACTOR};

  std::vector<ShapeColorMaps> m_shapeColorMaps;
  std::vector<ShapeColors> m_oldShapeColors;
  static constexpr uint32_t NUM_SHAPE_COLOR_STEPS = 1000;
  TValue m_shapeColorsT{TValue::StepType::CONTINUOUS_REPEATABLE, NUM_SHAPE_COLOR_STEPS};

  std::vector<ShapeColorMaps> m_circleColorMaps;
  std::vector<ShapeColors> m_oldCircleColors;
  TValue m_circleColorsT{TValue::StepType::CONTINUOUS_REPEATABLE, MAX_NUM_CIRCLES_IN_GROUP};

  const IColorMap* m_outerCircleMainColorMap;
  const IColorMap* m_outerCircleLowColorMap;
  static constexpr uint32_t NUM_OUTER_CIRCLE_COLOR_STEPS = 100;
  TValue m_outerCircleT{TValue::StepType::CONTINUOUS_REVERSIBLE, NUM_OUTER_CIRCLE_COLOR_STEPS};

  ColorMapMixMode m_colorMapMixMode             = ColorMapMixMode::CIRCLES_ONLY;
  static constexpr uint32_t NUM_MIX_COLOR_STEPS = 1000;
  TValue m_mixT{TValue::StepType::CONTINUOUS_REVERSIBLE, NUM_MIX_COLOR_STEPS};
  const Weights<ColorMapMixMode> m_colorMapMixModes;

  static constexpr uint32_t NUM_STEPS_FROM_OLD = 50;
  TValue m_oldT{TValue::StepType::SINGLE_CYCLE, NUM_STEPS_FROM_OLD};

  void InitColorMaps();
  void ResetColorMixMode();
  void ResetColorMapsLists();
  void ResetColorMapsList(std::vector<ShapeColorMaps>* colorMaps,
                          std::vector<ShapeColors>* oldColors,
                          TValue* t);
  void ResetColorMaps(ShapeColorMaps* colorMaps) const;
  void CopyColors(const ShapeColorMaps& colorMaps, const TValue& t, ShapeColors* oldColors) const;

  uint32_t m_stripeWidth = MIN_STRIPE_WIDTH;
  [[nodiscard]] auto GetShapeNumToUse(uint32_t shapeNum) const -> uint32_t;
  [[nodiscard]] auto GetBrightness(const Shape& shape, const Point2dInt& shapeCentrePos) const
      -> float;

  [[nodiscard]] auto GetShapeColors(uint32_t shapeNum, float brightness) const -> ShapeColors;
  [[nodiscard]] auto GetCircleColors(uint32_t circleNum, float brightness) const -> ShapeColors;
  [[nodiscard]] auto GetColors(const ShapeColorMaps& shapeColorMaps,
                               const TValue& t,
                               const ShapeColors& oldShapeColors,
                               float brightness) const -> ShapeColors;
  [[nodiscard]] static auto GetLowColor(LowColorTypes colorType, const ShapeColors& colors)
      -> Pixel;
  [[nodiscard]] static auto GetLowMixedColor(LowColorTypes colorType,
                                             const ShapeColors& colors1,
                                             const ShapeColors& colors2,
                                             float mixT) -> Pixel;
  [[nodiscard]] static auto GetInnerLowColor(LowColorTypes colorType, const ShapeColors& colors)
      -> Pixel;
  [[nodiscard]] static auto GetInnerLowMixedColor(LowColorTypes colorType,
                                                  const ShapeColors& colors1,
                                                  const ShapeColors& colors2,
                                                  float mixT) -> Pixel;
  static constexpr float CUTOFF_BRIGHTNESS = 0.005F;
  const BrightnessAttenuation m_brightnessAttenuation;
  [[nodiscard]] auto GetFinalColor(const Pixel& oldColor, const Pixel& color) const -> Pixel;
  [[nodiscard]] auto GetShapesOnlyColors(const LowColorTypes& lowColorType,
                                         const Shape& shape,
                                         float brightness) const -> ShapeColors;
  [[nodiscard]] auto GetCirclesOnlyColors(const LowColorTypes& lowColorType,
                                          uint32_t circleNum,
                                          float brightness) const -> ShapeColors;
  [[nodiscard]] auto GetShapesAndCirclesColors(const LowColorTypes& lowColorType,
                                               uint32_t circleNum,
                                               const Shape& shape,
                                               float brightness) const -> ShapeColors;
};

static constexpr auto TRUE_LOW_COLOR_WEIGHT      = 30.0F;
static constexpr auto MAIN_COLOR_WEIGHT          = 10.0F;
static constexpr auto LIGHTENED_LOW_COLOR_WEIGHT = 10.0F;

Tube::TubeImpl::TubeImpl(const TubeData& data, const OscillatingFunction::Params& pathParams)
  : m_data{data},
    m_shapes{GetInitialShapes(m_data, pathParams)},
    m_lowColorTypes{
        m_data.goomRand,
        {
            {LowColorTypes::TRUE_LOW_COLOR,      TRUE_LOW_COLOR_WEIGHT},
            {LowColorTypes::MAIN_COLOR,          MAIN_COLOR_WEIGHT},
            {LowColorTypes::LIGHTENED_LOW_COLOR, LIGHTENED_LOW_COLOR_WEIGHT},
        }
    }
{
}

auto Tube::TubeImpl::GetInitialShapes(const TubeData& data,
                                      const OscillatingFunction::Params& pathParams)
    -> std::vector<Shape>
{
  const auto middlePos = Point2dInt{static_cast<int32_t>(U_HALF * data.screenWidth),
                                    static_cast<int32_t>(U_HALF * data.screenHeight)};
  const auto radius = (0.5F * static_cast<float>(std::min(data.screenWidth, data.screenHeight))) -
                      data.radiusEdgeOffset;
  static constexpr auto ANGLE_STEP = TWO_PI / static_cast<float>(NUM_SHAPES_PER_TUBE);

  auto shapes = std::vector<Shape>(NUM_SHAPES_PER_TUBE);

  auto angle    = 0.0F;
  auto shapeNum = 0U;
  for (auto& shape : shapes)
  {
    const auto cosAngle = std::cos(angle);
    const auto sinAngle = std::sin(angle);
    const auto xFrom    = radius * cosAngle;
    const auto yFrom    = radius * sinAngle;
    const auto fromPos  = middlePos + Vec2dInt{static_cast<int32_t>(std::round(xFrom)),
                                              static_cast<int32_t>(std::round(yFrom))};
    const auto xTo      = radius * std::cos(PI + angle);
    const auto yTo      = radius * std::sin(PI + angle);
    const auto toPos    = middlePos + Vec2dInt{static_cast<int32_t>(std::round(xTo)),
                                            static_cast<int32_t>(std::round(yTo))};

    shape.shapeNum                   = shapeNum;
    static const auto s_DELAY_POINTS = std::vector<TValue::DelayPoint>{
        {       0.0F, SHAPE_T_DELAY_TIME},
        {T_AT_CENTRE, SHAPE_T_DELAY_TIME},
        {       1.0F, SHAPE_T_DELAY_TIME}
    };
    auto shapeT = std::make_unique<TValue>(
        TValue::StepType::CONTINUOUS_REVERSIBLE, PATH_STEP, s_DELAY_POINTS);
    shape.path = std::make_unique<OscillatingPath>(
        std::move(shapeT), fromPos.ToFlt(), toPos.ToFlt(), pathParams);

    angle += ANGLE_STEP;
    ++shapeNum;
  }

  return shapes;
}

void Tube::TubeImpl::SetWeightedMainColorMaps(
    const std::shared_ptr<const RandomColorMaps> weightedMaps)
{
  m_colorizer->SetWeightedMainColorMaps(weightedMaps);
}

void Tube::TubeImpl::SetWeightedLowColorMaps(
    const std::shared_ptr<const RandomColorMaps> weightedMaps)
{
  m_colorizer->SetWeightedLowColorMaps(weightedMaps);
}

void Tube::TubeImpl::ResetColorMaps()
{
  m_colorizer->ResetColorMaps();
  m_circleGroupTimer.SetTimeLimit(
      m_data.goomRand.GetRandInRange(MIN_NUM_CIRCLES_IN_GROUP, MAX_NUM_CIRCLES_IN_GROUP));
}

inline void Tube::TubeImpl::RotateShapeColorMaps()
{
  m_colorizer->RotateShapeColorMaps();
}

inline auto Tube::TubeImpl::GetTubeId() const -> uint32_t
{
  return m_data.tubeId;
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

inline void Tube::TubeImpl::SetTransformCentreFunc(const TransformCentreFunc& func)
{
  m_getTransformedCentre = func;
}

inline auto Tube::TubeImpl::GetCentrePathT() const -> float
{
  return m_centrePath->GetCurrentT();
}

inline void Tube::TubeImpl::SetCentrePathT(const float val)
{
  m_centrePath->Reset(val);
}

inline auto Tube::TubeImpl::GetCentreSpeed() const -> float
{
  return m_centrePath->GetStepSize();
}

inline void Tube::TubeImpl::SetCentreSpeed(const float val)
{
  m_centrePath->SetStepSize(val);
}

inline void Tube::TubeImpl::IncreaseCentreSpeed()
{
  const auto factor   = m_data.goomRand.GetRandInRange(1.01F, 10.0F);
  const auto newSpeed = std::min(MAX_CENTRE_SPEED, m_centrePath->GetStepSize() * factor);
  m_centrePath->SetStepSize(newSpeed);
}

inline void Tube::TubeImpl::DecreaseCentreSpeed()
{
  const auto factor   = m_data.goomRand.GetRandInRange(0.1F, 0.99F);
  const auto newSpeed = std::min(MIN_CENTRE_SPEED, m_centrePath->GetStepSize() * factor);
  m_centrePath->SetStepSize(newSpeed);
}

inline void Tube::TubeImpl::SetAllowOscillatingCirclePaths(const bool val)
{
  for (auto& shape : m_shapes)
  {
    shape.path->GetParametricFunction().SetAllowOscillatingPath(val);
  }
}

inline void Tube::TubeImpl::SetCirclePathParams(const OscillatingFunction::Params& params)
{
  for (auto& shape : m_shapes)
  {
    shape.path->GetParametricFunction().SetParams(params);
  }
}

inline auto Tube::TubeImpl::GetCircleSpeed() const -> float
{
  return m_shapes.at(0).path->GetStepSize();
}

inline void Tube::TubeImpl::SetCircleSpeed(const float val)
{
  std::for_each(
      begin(m_shapes), end(m_shapes), [&val](Shape& shape) { shape.path->SetStepSize(val); });
}

inline void Tube::TubeImpl::IncreaseCircleSpeed()
{
  static constexpr auto MIN_INCREASE_SPEED_FACTOR = 1.01F;
  static constexpr auto MAX_INCREASE_SPEED_FACTOR = 10.0F;
  const auto factor =
      m_data.goomRand.GetRandInRange(MIN_INCREASE_SPEED_FACTOR, MAX_INCREASE_SPEED_FACTOR);

  const auto newSpeed = std::min(MAX_CIRCLE_SPEED, GetCircleSpeed() * factor);
  SetCircleSpeed(newSpeed);
}

inline void Tube::TubeImpl::DecreaseCircleSpeed()
{
  static constexpr auto MIN_DECREASE_SPEED_FACTOR = 0.1F;
  static constexpr auto MAX_DECREASE_SPEED_FACTOR = 0.99F;
  const auto factor =
      m_data.goomRand.GetRandInRange(MIN_DECREASE_SPEED_FACTOR, MAX_DECREASE_SPEED_FACTOR);

  const auto newSpeed = std::max(MIN_CIRCLE_SPEED, GetCircleSpeed() * factor);
  SetCircleSpeed(newSpeed);
}

void Tube::TubeImpl::DrawShapes()
{
  m_hexLen            = GetHexLen();
  m_interiorShapeSize = GetInteriorShapeSize(m_hexLen);

  const auto centreOffset = m_getTransformedCentre(m_data.tubeId, m_centrePath->GetNextPoint());
  for (const auto& shape : m_shapes)
  {
    DrawShape(shape, centreOffset);
  }

  UpdateTValues();
  UpdateTimers();
}

inline auto Tube::TubeImpl::GetHexLen() const -> float
{
  const auto hexSizeT = std::fabs(m_shapes[0].path->GetCurrentT() - T_AT_CENTRE) / T_AT_CENTRE;
  return STD20::lerp(MIN_HEX_SIZE, MAX_HEX_SIZE, hexSizeT);
}

inline void Tube::TubeImpl::UpdateTValues()
{
  std::for_each(begin(m_shapes), end(m_shapes), [](Shape& shape) { shape.path->IncrementT(); });
  m_centrePath->IncrementT();
  m_colorizer->UpdateAllTValues();
}

inline void Tube::TubeImpl::UpdateTimers()
{
  m_circleGroupTimer.Increment();
  if (m_circleGroupTimer.Finished())
  {
    m_circleGroupTimer.ResetToZero();
  }

  m_interiorShapeTimer.Increment();
  if (m_interiorShapeTimer.Finished() && m_data.goomRand.ProbabilityOf(PROB_INTERIOR_SHAPE))
  {
    m_interiorShapeTimer.ResetToZero();
  }

  m_noBoundaryShapeTimer.Increment();
  if (m_noBoundaryShapeTimer.Finished() && m_data.goomRand.ProbabilityOf(PROB_NO_BOUNDARY_SHAPES))
  {
    m_noBoundaryShapeTimer.ResetToZero();
  }

  m_hexDotShapeTimer.Increment();
  if (m_hexDotShapeTimer.Finished() && m_data.goomRand.ProbabilityOf(PROB_HEX_DOT_SHAPE))
  {
    m_hexDotShapeTimer.ResetToZero();
  }

  m_lowColorTypeTimer.Increment();
  if (m_lowColorTypeTimer.Finished())
  {
    m_currentLowColorType = m_lowColorTypes.GetRandomWeighted();
    m_lowColorTypeTimer.SetTimeLimit(
        m_data.goomRand.GetRandInRange(MIN_LOW_COLOR_TYPE_TIME, MAX_LOW_COLOR_TYPE_TIME + 1));
  }
}

inline auto Tube::TubeImpl::GetInteriorShapeSize(const float hexLen) const -> uint32_t
{
  static constexpr auto MIN_SIZE_FACTOR = 0.5F;
  static constexpr auto MAX_SIZE_FACTOR = 1.3F;
  return static_cast<uint32_t>(
      std::round(m_data.goomRand.GetRandInRange(MIN_SIZE_FACTOR, MAX_SIZE_FACTOR) * hexLen));
}

void Tube::TubeImpl::DrawShape(const Shape& shape, const Vec2dInt& centreOffset) const
{
  const auto jitterXOffset  = m_data.goomRand.GetRandInRange(0, m_maxJitterOffset + 1);
  const auto jitterYOffset  = jitterXOffset;
  const auto jitterOffset   = Vec2dInt{jitterXOffset, jitterYOffset};
  const auto shapeCentrePos = shape.path->GetNextPoint() + jitterOffset + centreOffset;

  const auto allColors =
      m_colorizer->GetColors(m_currentLowColorType,
                             static_cast<uint32_t>(m_circleGroupTimer.GetCurrentCount()),
                             shape,
                             shapeCentrePos);

  if (m_noBoundaryShapeTimer.Finished())
  {
    DrawHexOutline(shapeCentrePos, allColors, shape.lineThickness);
  }

  static constexpr auto MIN_HEX_LEN_FOR_INTERIOR = 2.0F;
  if ((!m_interiorShapeTimer.Finished()) && (m_hexLen > (MIN_HEX_LEN_FOR_INTERIOR + SMALL_FLOAT)))
  {
    DrawInteriorShape(shapeCentrePos, allColors);
    DrawOuterCircle(shapeCentrePos, allColors);
  }
}

void Tube::TubeImpl::DrawHexOutline(const Point2dInt& hexCentre,
                                    const ShapeColors& allColors,
                                    const uint8_t lineThickness) const
{
  static constexpr auto NUM_HEX_SIDES = 6U;
  static constexpr auto ANGLE_STEP    = THIRD_PI;
  static constexpr auto START_ANGLE   = 2.0F * ANGLE_STEP;
  const auto lineColors               = MultiplePixels{allColors.mainColor, allColors.lowColor};
  const auto outerCircleColors =
      MultiplePixels{allColors.outerCircleMainColor, allColors.outerCircleLowColor};
  const auto drawHexDot = !m_hexDotShapeTimer.Finished();

  // Start hex shape to right of centre position.
  auto point1 = Point2dInt{
      static_cast<int32_t>(std::round(static_cast<float>(hexCentre.x) + m_hexLen)), hexCentre.y};
  auto angle = START_ANGLE;

  for (auto i = 0U; i < NUM_HEX_SIDES; ++i)
  {
    const auto point2 =
        Point2dInt{point1.x + static_cast<int32_t>(std::round(m_hexLen * std::cos(angle))),
                   point1.y + static_cast<int32_t>(std::round(m_hexLen * std::sin(angle)))};

    m_data.drawFuncs.drawLine(point1, point2, lineColors, lineThickness);
    if (drawHexDot)
    {
      static constexpr uint32_t HEX_DOT_SIZE = 3;
      m_data.drawFuncs.drawSmallImage(
          point2, SmallImageBitmaps::ImageNames::SPHERE, HEX_DOT_SIZE, outerCircleColors);
    }

    angle += ANGLE_STEP;
    point1 = point2;
  }
}

inline void Tube::TubeImpl::DrawInteriorShape(const Point2dInt& shapeCentrePos,
                                              const ShapeColors& allColors) const
{
  const auto colors = MultiplePixels{allColors.innerMainColor, allColors.innerLowColor};
  m_data.drawFuncs.drawSmallImage(
      shapeCentrePos, SmallImageBitmaps::ImageNames::SPHERE, m_interiorShapeSize, colors);
}

inline void Tube::TubeImpl::DrawOuterCircle(const Point2dInt& shapeCentrePos,
                                            const ShapeColors& allColors) const
{
  static constexpr auto OUTER_CIRCLE_RADIUS_FACTOR = 1.5F;
  const auto outerCircleRadius =
      static_cast<int32_t>(std::round(OUTER_CIRCLE_RADIUS_FACTOR * m_hexLen));
  static constexpr auto OUTER_CIRCLE_LINE_THICKNESS = 1U;
  const auto outerCircleColors =
      MultiplePixels{allColors.outerCircleMainColor, allColors.outerCircleLowColor};
  m_data.drawFuncs.drawCircle(
      shapeCentrePos, outerCircleRadius, outerCircleColors, OUTER_CIRCLE_LINE_THICKNESS);
}

static constexpr auto SHAPES_ONLY_WEIGHT                = 20.0F;
static constexpr auto STRIPED_SHAPES_ONLY_WEIGHT        = 10.0F;
static constexpr auto CIRCLES_ONLY_WEIGHT               = 20.0F;
static constexpr auto SHAPES_AND_CIRCLES_WEIGHT         = 05.0F;
static constexpr auto STRIPED_SHAPES_AND_CIRCLES_WEIGHT = 15.0F;

ShapeColorizer::ShapeColorizer(const TubeData& data,
                               const uint32_t numShapes,
                               const uint32_t numCircles)
  : m_data{data},
    m_shapeColorMaps(numShapes),
    m_oldShapeColors(numShapes),
    m_circleColorMaps(numCircles),
    m_oldCircleColors(numCircles),
    m_outerCircleMainColorMap{&m_data.mainColorMaps->GetRandomColorMap()},
    m_outerCircleLowColorMap{&m_data.lowColorMaps->GetRandomColorMap()},
    m_colorMapMixModes{
        m_data.goomRand,
        {
            {ColorMapMixMode::SHAPES_ONLY,                SHAPES_ONLY_WEIGHT},
            {ColorMapMixMode::STRIPED_SHAPES_ONLY,        STRIPED_SHAPES_ONLY_WEIGHT},
            {ColorMapMixMode::CIRCLES_ONLY,               CIRCLES_ONLY_WEIGHT},
            {ColorMapMixMode::SHAPES_AND_CIRCLES,         SHAPES_AND_CIRCLES_WEIGHT},
            {ColorMapMixMode::STRIPED_SHAPES_AND_CIRCLES, STRIPED_SHAPES_AND_CIRCLES_WEIGHT},
        }
    },
    m_brightnessAttenuation{m_data.screenWidth, m_data.screenHeight, CUTOFF_BRIGHTNESS}
{
  InitColorMaps();
  ResetColorMaps();
}

inline auto ShapeColorizer::GetBrightnessFactor() const -> float
{
  return m_data.brightnessFactor;
}

inline void ShapeColorizer::SetBrightnessFactor(const float val)
{
  m_data.brightnessFactor = val;
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

void ShapeColorizer::SetWeightedMainColorMaps(
    const std::shared_ptr<const RandomColorMaps> weightedMaps)
{
  m_data.mainColorMaps = weightedMaps;
}

void ShapeColorizer::SetWeightedLowColorMaps(
    const std::shared_ptr<const RandomColorMaps> weightedMaps)
{
  m_data.lowColorMaps = weightedMaps;
}

void ShapeColorizer::ResetColorMaps()
{
  ResetColorMixMode();
  ResetColorMapsLists();

  m_stripeWidth = m_data.goomRand.GetRandInRange(MIN_STRIPE_WIDTH, MAX_STRIPE_WIDTH + 1);
}

inline void ShapeColorizer::ResetColorMapsLists()
{
  ResetColorMapsList(&m_shapeColorMaps, &m_oldShapeColors, &m_shapeColorsT);
  ResetColorMapsList(&m_circleColorMaps, &m_oldCircleColors, &m_circleColorsT);
}

void ShapeColorizer::RotateShapeColorMaps()
{
  std::rotate(begin(m_shapeColorMaps), begin(m_shapeColorMaps) + 1, end(m_shapeColorMaps));
  std::rotate(begin(m_oldShapeColors), begin(m_oldShapeColors) + 1, end(m_oldShapeColors));
}

void ShapeColorizer::ResetColorMapsList(std::vector<ShapeColorMaps>* const colorMaps,
                                        std::vector<ShapeColors>* const oldColors,
                                        TValue* const t)
{
  const auto numColorMaps = colorMaps->size();
  Expects(numColorMaps == oldColors->size());

  m_outerCircleMainColorMap = &m_data.mainColorMaps->GetRandomColorMap();
  m_outerCircleLowColorMap  = &m_data.lowColorMaps->GetRandomColorMap();

  for (auto i = 0U; i < numColorMaps; ++i)
  {
    CopyColors((*colorMaps)[i], *t, &(*oldColors)[i]);
    ResetColorMaps(&(*colorMaps)[i]);
  }
  t->Reset(0.0);
}

void ShapeColorizer::ResetColorMaps(ShapeColorMaps* const colorMaps) const
{
  colorMaps->mainColorMap      = &m_data.mainColorMaps->GetRandomColorMap();
  colorMaps->lowColorMap       = &m_data.mainColorMaps->GetRandomColorMap();
  colorMaps->innerMainColorMap = &m_data.lowColorMaps->GetRandomColorMap();
  colorMaps->innerLowColorMap  = &m_data.lowColorMaps->GetRandomColorMap();
}

void ShapeColorizer::CopyColors(const ShapeColorMaps& colorMaps,
                                const TValue& t,
                                ShapeColors* const oldColors) const
{
  oldColors->mainColor            = colorMaps.mainColorMap->GetColor(t());
  oldColors->lowColor             = colorMaps.lowColorMap->GetColor(t());
  oldColors->innerMainColor       = colorMaps.innerMainColorMap->GetColor(t());
  oldColors->innerLowColor        = colorMaps.innerLowColorMap->GetColor(t());
  oldColors->outerCircleMainColor = m_outerCircleMainColorMap->GetColor(t());
  oldColors->outerCircleLowColor  = m_outerCircleLowColorMap->GetColor(t());
}

inline void ShapeColorizer::ResetColorMixMode()
{
  m_colorMapMixMode = m_colorMapMixModes.GetRandomWeighted();
}

void ShapeColorizer::UpdateAllTValues()
{
  m_shapeColorsT.Increment();
  m_circleColorsT.Increment();
  m_outerCircleT.Increment();
  m_oldT.Increment();
  m_mixT.Increment();
}

auto ShapeColorizer::GetBrightness(const Shape& shape, const Point2dInt& shapeCentrePos) const
    -> float
{
  static constexpr auto MIN_BRIGHTNESS = 0.5F;
  const auto brightness =
      std::min(3.0F,
               m_data.brightnessFactor *
                   m_brightnessAttenuation.GetPositionBrightness(shapeCentrePos, MIN_BRIGHTNESS));

  static constexpr auto SMALL_T = 0.15F;
  if (static constexpr float HALFWAY_T = 0.5F;
      std::fabs(shape.path->GetCurrentT() - HALFWAY_T) < SMALL_T)
  {
    static constexpr auto SMALL_T_BRIGHTNESS = 0.250F;
    return SMALL_T_BRIGHTNESS * brightness;
  }
  return brightness;
}

auto ShapeColorizer::GetColors(const LowColorTypes lowColorType,
                               const uint32_t circleNum,
                               const Shape& shape,
                               const Point2dInt& shapeCentrePos) const -> ShapeColors
{
  const auto brightness = GetBrightness(shape, shapeCentrePos);

  switch (m_colorMapMixMode)
  {
    case ColorMapMixMode::STRIPED_SHAPES_ONLY:
    case ColorMapMixMode::SHAPES_ONLY:
      return GetShapesOnlyColors(lowColorType, shape, brightness);
    case ColorMapMixMode::CIRCLES_ONLY:
      return GetCirclesOnlyColors(lowColorType, circleNum, brightness);
    case ColorMapMixMode::STRIPED_SHAPES_AND_CIRCLES:
    case ColorMapMixMode::SHAPES_AND_CIRCLES:
      return GetShapesAndCirclesColors(lowColorType, circleNum, shape, brightness);
    default:
      throw std::logic_error("Invalid ColorMapMixMode.");
  }
}

inline auto ShapeColorizer::GetShapesOnlyColors(const LowColorTypes& lowColorType,
                                                const Shape& shape,
                                                const float brightness) const -> ShapeColors
{
  const auto colors = GetShapeColors(GetShapeNumToUse(shape.shapeNum), brightness);
  return {
      colors.mainColor,
      GetLowColor(lowColorType, colors),
      colors.innerMainColor,
      GetInnerLowColor(lowColorType, colors),
      colors.outerCircleMainColor,
      colors.outerCircleLowColor,
  };
}

inline auto ShapeColorizer::GetCirclesOnlyColors(const LowColorTypes& lowColorType,
                                                 const uint32_t circleNum,
                                                 const float brightness) const -> ShapeColors
{
  const auto colors = GetCircleColors(circleNum, brightness);
  return {
      colors.mainColor,
      GetLowColor(lowColorType, colors),
      colors.innerMainColor,
      GetInnerLowColor(lowColorType, colors),
      colors.outerCircleMainColor,
      colors.outerCircleLowColor,
  };
}

inline auto ShapeColorizer::GetShapesAndCirclesColors(const LowColorTypes& lowColorType,
                                                      const uint32_t circleNum,
                                                      const Shape& shape,
                                                      const float brightness) const -> ShapeColors
{
  const auto shapeColors  = GetShapeColors(GetShapeNumToUse(shape.shapeNum), brightness);
  const auto circleColors = GetCircleColors(circleNum, brightness);

  return {
      IColorMap::GetColorMix(shapeColors.mainColor, circleColors.mainColor, m_mixT()),
      GetLowMixedColor(lowColorType, shapeColors, circleColors, m_mixT()),
      IColorMap::GetColorMix(shapeColors.innerMainColor, circleColors.innerMainColor, m_mixT()),
      GetInnerLowMixedColor(lowColorType, shapeColors, circleColors, m_mixT()),
      IColorMap::GetColorMix(
          shapeColors.outerCircleMainColor, circleColors.outerCircleMainColor, m_mixT()),
      IColorMap::GetColorMix(
          shapeColors.outerCircleLowColor, circleColors.outerCircleLowColor, m_mixT()),
  };
}

inline auto ShapeColorizer::GetLowColor(const LowColorTypes colorType, const ShapeColors& colors)
    -> Pixel
{
  if (colorType == LowColorTypes::LIGHTENED_LOW_COLOR)
  {
    return GetLightenedColor(colors.mainColor, LIGHTER_COLOR_POWER);
  }
  if (colorType == LowColorTypes::MAIN_COLOR)
  {
    return colors.mainColor;
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
    return colors.innerMainColor;
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
    const auto mixedColor = IColorMap::GetColorMix(colors1.lowColor, colors2.lowColor, mixT);
    return GetLightenedColor(mixedColor, LIGHTER_COLOR_POWER);
  }
  if (colorType == LowColorTypes::MAIN_COLOR)
  {
    const auto mixedColor = IColorMap::GetColorMix(colors1.mainColor, colors2.mainColor, mixT);
    return mixedColor;
  }
  const auto mixedColor = IColorMap::GetColorMix(colors1.lowColor, colors2.lowColor, mixT);
  return mixedColor;
}

inline auto ShapeColorizer::GetInnerLowMixedColor(const LowColorTypes colorType,
                                                  const ShapeColors& colors1,
                                                  const ShapeColors& colors2,
                                                  const float mixT) -> Pixel
{
  if (colorType == LowColorTypes::LIGHTENED_LOW_COLOR)
  {
    const auto mixedColor =
        IColorMap::GetColorMix(colors1.innerLowColor, colors2.innerLowColor, mixT);
    return GetLightenedColor(mixedColor, LIGHTER_COLOR_POWER);
  }
  if (colorType == LowColorTypes::MAIN_COLOR)
  {
    const auto mixedColor =
        IColorMap::GetColorMix(colors1.innerMainColor, colors2.innerMainColor, mixT);
    return mixedColor;
  }
  const auto mixedColor =
      IColorMap::GetColorMix(colors1.innerLowColor, colors2.innerLowColor, mixT);
  return mixedColor;
}

inline auto ShapeColorizer::GetShapeNumToUse(const uint32_t shapeNum) const -> uint32_t
{
  return (m_colorMapMixMode == ColorMapMixMode::STRIPED_SHAPES_ONLY) ||
                 (m_colorMapMixMode == ColorMapMixMode::STRIPED_SHAPES_AND_CIRCLES)
             ? (shapeNum / m_stripeWidth)
             : shapeNum;
}

inline auto ShapeColorizer::GetShapeColors(const uint32_t shapeNum, const float brightness) const
    -> ShapeColors
{
  return GetColors(
      m_shapeColorMaps[shapeNum], m_shapeColorsT, m_oldShapeColors[shapeNum], brightness);
}

inline auto ShapeColorizer::GetCircleColors(const uint32_t circleNum, const float brightness) const
    -> ShapeColors
{
  return GetColors(
      m_circleColorMaps[circleNum], m_circleColorsT, m_oldCircleColors[circleNum], brightness);
}

auto ShapeColorizer::GetColors(const ShapeColorMaps& shapeColorMaps,
                               const TValue& t,
                               const ShapeColors& oldShapeColors,
                               const float brightness) const -> ShapeColors
{
  const auto mainColor =
      GetFinalColor(oldShapeColors.mainColor, shapeColorMaps.mainColorMap->GetColor(t()));
  const auto lowColor =
      GetFinalColor(oldShapeColors.lowColor, shapeColorMaps.lowColorMap->GetColor(t()));
  const auto innerMainColor =
      GetFinalColor(oldShapeColors.innerMainColor, shapeColorMaps.innerMainColorMap->GetColor(t()));
  const auto innerLowColor =
      GetFinalColor(oldShapeColors.innerLowColor, shapeColorMaps.innerLowColorMap->GetColor(t()));
  const auto outerCircleMainColor = GetFinalColor(
      oldShapeColors.outerCircleMainColor, m_outerCircleMainColorMap->GetColor(m_outerCircleT()));
  const auto outerCircleLowColor = GetFinalColor(
      oldShapeColors.outerCircleLowColor, m_outerCircleLowColorMap->GetColor(m_outerCircleT()));

  return {
      m_colorAdjust.GetAdjustment(brightness, mainColor),
      m_colorAdjust.GetAdjustment(brightness, lowColor),
      m_colorAdjust.GetAdjustment(brightness, innerMainColor),
      m_colorAdjust.GetAdjustment(brightness, innerLowColor),
      m_colorAdjust.GetAdjustment(OUTER_CIRCLE_BRIGHTNESS * brightness, outerCircleMainColor),
      m_colorAdjust.GetAdjustment(OUTER_CIRCLE_BRIGHTNESS * brightness, outerCircleLowColor),
  };
}

inline auto ShapeColorizer::GetFinalColor(const Pixel& oldColor, const Pixel& color) const -> Pixel
{
  return IColorMap::GetColorMix(oldColor, color, m_oldT());
}

BrightnessAttenuation::BrightnessAttenuation(const uint32_t screenWidth,
                                             const uint32_t screenHeight,
                                             const float cutoffBrightness)
  : m_cutoffBrightness{cutoffBrightness},
    m_maxRSquared{2 * Sq(U_HALF * std::min(screenWidth, screenHeight))}
{
}

auto BrightnessAttenuation::GetPositionBrightness(const Point2dInt& pos,
                                                  const float minBrightnessPastCutoff) const
    -> float
{
  const auto distFromCentre = GetDistFromCentreFactor(pos);
  return distFromCentre < DIST_SQ_CUTOFF ? m_cutoffBrightness
                                         : (minBrightnessPastCutoff + distFromCentre);
}

inline auto BrightnessAttenuation::GetDistFromCentreFactor(const Point2dInt& pos) const -> float
{
  return static_cast<float>(Sq(pos.x) + Sq(pos.y)) / static_cast<float>(m_maxRSquared);
}

} // namespace GOOM::VISUAL_FX::TUBES
