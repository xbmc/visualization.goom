#ifndef VISUALIZATION_GOOM_GOOM_TUBES_H
#define VISUALIZATION_GOOM_GOOM_TUBES_H

#include "goom_graphic.h"
#include "goomutils/graphics/small_image_bitmaps.h"
#include "goomutils/timer.h"

#include <functional>
#include <memory>

#if __cplusplus <= 201402L
namespace GOOM
{

namespace UTILS
{
class RandomColorMaps;
} // namespace UTILS

namespace TUBES
{
#else
namespace GOOM::TUBES
{
#endif

enum class ColorMapMixMode
{
  SHAPES_ONLY,
  STRIPED_SHAPES_ONLY,
  CIRCLES_ONLY,
  SHAPES_AND_CIRCLES,
  STRIPED_SHAPES_AND_CIRCLES,
};

struct ShapeColors
{
  Pixel color{};
  Pixel lowColor{};
  Pixel innerColor{};
  Pixel innerLowColor{};
  Pixel outerCircleColor{};
  Pixel outerCircleLowColor{};
};
struct PathParams
{
  float amplitude = 1.0;
  float xFreq = 1.0;
  float yFreq = 1.0;
};

class Tube
{
public:
  using DrawLineFunc = std::function<void(
      int x1, int y1, int x2, int y2, const std::vector<Pixel>& colors, uint8_t thickness)>;
  using DrawCircleFunc = std::function<void(
      int x, int y, int radius, const std::vector<Pixel>& colors, uint8_t thickness)>;
  using DrawSmallImageFunc = std::function<void(int xMid,
                                                int yMid,
                                                UTILS::SmallImageBitmaps::ImageNames imageName,
                                                uint32_t size,
                                                const std::vector<Pixel>& colors)>;
  struct DrawFuncs
  {
    DrawLineFunc drawLine;
    DrawCircleFunc drawCircle;
    DrawSmallImageFunc drawSmallImage;
  };

  Tube() noexcept = delete;
  Tube(uint32_t tubeId,
       const DrawFuncs& drawFuncs,
       uint32_t screenWidth,
       uint32_t screenHeight,
       const UTILS::RandomColorMaps* colorMaps,
       const UTILS::RandomColorMaps* lowColorMaps,
       float radiusEdgeOffset,
       float brightnessFactor) noexcept;
  Tube(const Tube&) noexcept = delete;
  Tube(Tube&&) noexcept;
  ~Tube() noexcept;
  auto operator=(const Tube&) -> Tube& = delete;
  auto operator=(Tube&&) -> Tube& = delete;

  [[nodiscard]] auto GetTubeId() const -> uint32_t;
  [[nodiscard]] auto IsActive() const -> bool;

  void ResetPaths();
  void ResetColorMaps();
  void RotateShapeColorMaps();

  [[nodiscard]] auto GetBrightnessFactor() const -> float;
  void SetBrightnessFactor(float val);

  [[nodiscard]] auto GetMaxJitterOffset() const -> int32_t;
  void SetMaxJitterOffset(int32_t val);

  using TransformCentreFunc = std::function<V2dInt(uint32_t tubeId, const V2dInt& centre)>;
  void SetTransformCentreFunc(const TransformCentreFunc& f);
  [[nodiscard]] auto GetCentrePathT() const -> float;
  void SetCentrePathT(float val);
  [[nodiscard]] auto GetCentreSpeed() const -> float;
  static const float NORMAL_CENTRE_SPEED;
  void SetCentreSpeed(float val);
  void IncreaseCentreSpeed();
  void DecreaseCentreSpeed();

  void SetOscillatingCirclePaths(bool val);
  void SetCirclePathParams(const PathParams& params);
  [[nodiscard]] auto GetCircleSpeed() const -> float;
  static const float NORMAL_CIRCLE_SPEED;
  void SetCircleSpeed(float val);
  void IncreaseCircleSpeed();
  void DecreaseCircleSpeed();

  void DrawCircleOfShapes();

private:
  class TubeImpl;
  std::unique_ptr<TubeImpl> m_impl;
};

#if __cplusplus <= 201402L
} // namespace TUBES
} // namespace GOOM
#else
} // namespace GOOM::TUBES
#endif

#endif //VISUALIZATION_GOOM_TUBES_H
