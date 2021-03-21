#ifndef VISUALIZATION_GOOM_FLYING_STARS_FX_H
#define VISUALIZATION_GOOM_FLYING_STARS_FX_H

#include "goom_stats.h"
#include "goom_visual_fx.h"

#include <memory>
#include <string>

namespace GOOM
{

class IGoomDraw;
class PluginInfo;

namespace UTILS
{
class RandomColorMaps;
class SmallImageBitmaps;
} // namespace UTILS

class FlyingStarsFx : public IVisualFx
{
public:
  enum class ColorMode
  {
    _NULL = -1,
    MIX_COLORS,
    REVERSE_MIX_COLORS,
    SIMILAR_LOW_COLORS,
    SINE_MIX_COLORS,
  };

  FlyingStarsFx() noexcept = delete;
  explicit FlyingStarsFx(const IGoomDraw* draw, const std::shared_ptr<const PluginInfo>&) noexcept;
  FlyingStarsFx(const FlyingStarsFx&) noexcept = delete;
  FlyingStarsFx(FlyingStarsFx&&) noexcept = delete;
  ~FlyingStarsFx() noexcept override;
  auto operator=(const FlyingStarsFx&) -> FlyingStarsFx& = delete;
  auto operator=(FlyingStarsFx&&) -> FlyingStarsFx& = delete;

  [[nodiscard]] auto GetFxName() const -> std::string override;

  [[nodiscard]] auto GetResourcesDirectory() const -> const std::string& override;
  void SetResourcesDirectory(const std::string& dirName) override;

  void SetSmallImageBitmaps(const UTILS::SmallImageBitmaps& smallBitmaps);

  void Start() override;

  void Resume() override;
  void Suspend() override;

  void SetWeightedColorMaps(std::shared_ptr<UTILS::RandomColorMaps> weightedMaps);
  void SetWeightedLowColorMaps(std::shared_ptr<UTILS::RandomColorMaps> weightedMaps);

  void ApplyMultiple();

  void Log(const GoomStats::LogStatsValueFunc& l) const override;
  void Finish() override;

private:
  bool m_enabled = true;
  class FlyingStarsImpl;
  const std::unique_ptr<FlyingStarsImpl> m_fxImpl;
};

} // namespace GOOM
#endif
