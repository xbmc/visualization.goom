#pragma once

#include "draw/goom_draw.h"
#include "goom_graphic.h"
#include "point2d.h"
#include "spimpl.h"
#include "tube_data.h"
#include "utils/math/paths.h"
#include "utils/timer.h"

#include <functional>
#include <memory>

namespace GOOM
{

namespace COLOR
{
class RandomColorMaps;
}

namespace VISUAL_FX::TUBES
{

enum class ColorMapMixMode
{
  SHAPES_ONLY,
  STRIPED_SHAPES_ONLY,
  CIRCLES_ONLY,
  SHAPES_AND_CIRCLES,
  STRIPED_SHAPES_AND_CIRCLES,
  _num // unused, and marks the enum end
};

struct ShapeColors
{
  Pixel mainColor{};
  Pixel lowColor{};
  Pixel innerMainColor{};
  Pixel innerLowColor{};
  Pixel outerCircleMainColor{};
  Pixel outerCircleLowColor{};
};

class BrightnessAttenuation
{
public:
  static constexpr float DIST_SQ_CUTOFF = 0.10F;
  BrightnessAttenuation(uint32_t screenWidth, uint32_t screenHeight, float cutoffBrightness);
  [[nodiscard]] auto GetPositionBrightness(const Point2dInt& pos,
                                           float minBrightnessPastCutoff) const -> float;

private:
  const float m_cutoffBrightness;
  const uint32_t m_maxRSquared;
  [[nodiscard]] auto GetDistFromCentreFactor(const Point2dInt& pos) const -> float;
};

class Tube
{
public:
  Tube() noexcept = delete;
  Tube(const TubeData& data, const UTILS::MATH::OscillatingFunction::Params& pathParams) noexcept;

  [[nodiscard]] auto IsActive() const -> bool;

  void SetWeightedMainColorMaps(std::shared_ptr<const COLOR::RandomColorMaps> weightedMaps);
  void SetWeightedLowColorMaps(std::shared_ptr<const COLOR::RandomColorMaps> weightedMaps);

  void ResetColorMaps();

  void SetBrightnessFactor(float val);

  void SetMaxJitterOffset(int32_t val);

  using TransformCentreFunc = std::function<Vec2dInt(uint32_t tubeId, const Point2dInt& centre)>;
  void SetTransformCentreFunc(const TransformCentreFunc& func);
  void SetCentrePathT(float val);
  static const float NORMAL_CENTRE_SPEED;
  void SetCentreSpeed(float val);
  void IncreaseCentreSpeed();
  void DecreaseCentreSpeed();

  void SetAllowOscillatingCirclePaths(bool val);
  void SetCirclePathParams(const UTILS::MATH::OscillatingFunction::Params& params);
  static const float NORMAL_CIRCLE_SPEED;
  void SetCircleSpeed(float val);
  void IncreaseCircleSpeed();
  void DecreaseCircleSpeed();

  void DrawCircleOfShapes();

private:
  class TubeImpl;
  spimpl::unique_impl_ptr<TubeImpl> m_pimpl;
};

} // namespace VISUAL_FX::TUBES
} // namespace GOOM
