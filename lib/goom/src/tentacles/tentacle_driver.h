#ifndef VISUALIZATION_GOOM_TENTACLE_DRIVER_H
#define VISUALIZATION_GOOM_TENTACLE_DRIVER_H

#include "goom_graphic.h"
#include "goom_visual_fx.h"
#include "goomutils/colormaps.h"
#include "goomutils/mathutils.h"
#include "goomutils/random_colormaps.h"
#include "tentacles.h"
#include "v2d.h"

#include <cstdint>
#include <memory>
#include <vector>

#if __cplusplus <= 201402L
namespace GOOM
{

class IGoomDraw;

namespace TENTACLES
{
#else
namespace GOOM::TENTACLES
{
#endif

class IterTimer
{
public:
  explicit IterTimer(const size_t startCnt) : m_startCount{startCnt} {}

  void Start() { m_count = m_startCount; }
  void Next()
  {
    if (m_count > 0)
    {
      m_count--;
    }
  }

private:
  const size_t m_startCount;
  size_t m_count = 0;
};

class ITentacleLayout
{
public:
  ITentacleLayout() noexcept = default;
  ITentacleLayout(const ITentacleLayout&) noexcept = default;
  ITentacleLayout(ITentacleLayout&&) noexcept = delete;
  virtual ~ITentacleLayout() noexcept = default;
  auto operator=(const ITentacleLayout&) -> ITentacleLayout& = delete;
  auto operator=(ITentacleLayout&&) -> ITentacleLayout& = delete;

  [[nodiscard]] virtual auto GetNumPoints() const -> size_t = 0;
  [[nodiscard]] virtual auto GetPoints() const -> const std::vector<V3dFlt>& = 0;
};

class TentacleDriver
{
public:
  enum class ColorModes
  {
    minimal,
    oneGroupForAll,
    multiGroups,
  };

  TentacleDriver() noexcept = delete;
  explicit TentacleDriver(const IGoomDraw* draw) noexcept;
  TentacleDriver(const TentacleDriver&) noexcept = delete;
  TentacleDriver(TentacleDriver&&) noexcept = delete;
  ~TentacleDriver() noexcept = default;
  auto operator=(const TentacleDriver&) -> TentacleDriver& = delete;
  auto operator=(TentacleDriver&&) -> TentacleDriver& = delete;

  void Init(UTILS::ColorMapGroup initialColorMapGroup, const ITentacleLayout& l);
  [[nodiscard]] auto GetNumTentacles() const -> size_t;

  [[nodiscard]] auto GetColorMode() const -> ColorModes;
  void SetColorMode(ColorModes m);

  void SetWeightedColorMaps(const UTILS::RandomColorMaps& weightedMaps);

  void StartIterating();

  void FreshStart();
  void Update(
      float angle, float distance, float distance2, const Pixel& color, const Pixel& lowColor);

  void SetReverseColorMix(bool val);
  void MultiplyIterZeroYValWaveFreq(float val);

private:
  const IGoomDraw* const m_draw;
  ColorModes m_colorMode = ColorModes::oneGroupForAll;
  struct IterationParams
  {
    size_t numNodes = 200;
    float prevYWeight = 0.770F;
    float iterZeroYValWaveFreq = 1.0F;
    UTILS::SineWaveMultiplier iterZeroYValWave{};
    float length = 50.0F;
  };
  struct IterParamsGroup
  {
    IterationParams first{};
    IterationParams last{};
    [[nodiscard]] auto GetNext(float t) const -> IterationParams;
  };
  std::vector<IterParamsGroup> m_iterParamsGroups{};

  void UpdateTentaclesLayout(const ITentacleLayout& l);

  const UTILS::RandomColorMaps* m_colorMaps{};
  std::vector<std::shared_ptr<ITentacleColorizer>> m_colorizers{};

  size_t m_updateNum = 0;
  Tentacles3D m_tentacles{};
  size_t m_numTentacles = 0;
  std::vector<IterationParams> m_tentacleParams{};
  static const size_t CHANGE_CURRENT_COLOR_MAP_GROUP_EVERY_N_UPDATES;
  [[nodiscard]] auto GetNextColorMapGroups() const -> std::vector<UTILS::ColorMapGroup>;

  static auto CreateNewTentacle2D(size_t id, const IterationParams& p)
      -> std::unique_ptr<Tentacle2D>;
  const std::vector<IterTimer*> m_iterTimers{};
  void UpdateIterTimers();
  void CheckForTimerEvents();
  void Plot3D(const Tentacle3D& tentacle,
              const Pixel& dominantColor,
              const Pixel& dominantLowColor,
              float angle,
              float distance,
              float distance2) const;
  [[nodiscard]] auto ProjectV3DOntoV2D(const std::vector<V3dFlt>& v3, float distance) const
      -> std::vector<V2dInt>;
  static void RotateV3DAboutYAxis(float sinAngle, float cosAngle, const V3dFlt& src, V3dFlt& dest);
  static void TranslateV3D(const V3dFlt& add, V3dFlt& inOut);
};

class TentacleColorMapColorizer : public ITentacleColorizer
{
public:
  TentacleColorMapColorizer() noexcept = delete;
  explicit TentacleColorMapColorizer(UTILS::ColorMapGroup, size_t numNodes) noexcept;
  TentacleColorMapColorizer(const TentacleColorMapColorizer&) noexcept = delete;
  TentacleColorMapColorizer(TentacleColorMapColorizer&&) noexcept = delete;
  ~TentacleColorMapColorizer() noexcept override = default;
  auto operator=(const TentacleColorMapColorizer&) -> TentacleColorMapColorizer& = delete;
  auto operator=(TentacleColorMapColorizer&&) -> TentacleColorMapColorizer& = delete;

  auto GetColorMapGroup() const -> UTILS::ColorMapGroup override;
  void SetColorMapGroup(UTILS::ColorMapGroup c) override;
  void ChangeColorMap() override;
  auto GetColor(size_t nodeNum) const -> Pixel override;

private:
  size_t m_numNodes = 0;
  UTILS::ColorMapGroup m_currentColorMapGroup{};
  const UTILS::RandomColorMaps m_colorMaps{};
  std::shared_ptr<const UTILS::IColorMap> m_colorMap{};
  std::shared_ptr<const UTILS::IColorMap> m_prevColorMap{};
  static constexpr uint32_t MAX_COUNT_SINCE_COLORMAP_CHANGE = 100;
  static constexpr float TRANSITION_STEP =
      1.0F / static_cast<float>(MAX_COUNT_SINCE_COLORMAP_CHANGE);
  mutable float m_tTransition = 0.0F;
};

class CirclesTentacleLayout : public ITentacleLayout
{
public:
  CirclesTentacleLayout(float radiusMin,
                        float radiusMax,
                        const std::vector<size_t>& numCircleSamples,
                        float zConst);
  // Order of points is outer circle to inner.
  [[nodiscard]] auto GetNumPoints() const -> size_t override;
  [[nodiscard]] auto GetPoints() const -> const std::vector<V3dFlt>& override;

private:
  std::vector<V3dFlt> m_points{};
};

#if __cplusplus <= 201402L
} // namespace TENTACLES
} // namespace GOOM
#else
} // namespace GOOM::TENTACLES
#endif

#endif
