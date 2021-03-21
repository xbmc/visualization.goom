#ifndef VISUALIZATION_GOOM_TENTACLES_FX_H
#define VISUALIZATION_GOOM_TENTACLES_FX_H

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
} // namespace UTILS

class TentaclesFx : public IVisualFx
{
public:
  TentaclesFx() noexcept = delete;
  explicit TentaclesFx(const IGoomDraw* draw, const std::shared_ptr<const PluginInfo>&) noexcept;
  TentaclesFx(const TentaclesFx&) noexcept = delete;
  TentaclesFx(TentaclesFx&&) noexcept = delete;
  ~TentaclesFx() noexcept override;
  auto operator=(const TentaclesFx&) -> TentaclesFx& = delete;
  auto operator=(TentaclesFx&&) -> TentaclesFx& = delete;

  [[nodiscard]] auto GetFxName() const -> std::string override;

  [[nodiscard]] auto GetResourcesDirectory() const -> const std::string& override;
  void SetResourcesDirectory(const std::string& dirName) override;

  void Start() override;

  void FreshStart();
  void Resume() override;
  void Suspend() override;

  void SetWeightedColorMaps(std::shared_ptr<UTILS::RandomColorMaps> weightedMaps);

  void ApplyNoDraw();
  void ApplyMultiple();

  void Log(const GoomStats::LogStatsValueFunc& l) const override;
  void Finish() override;

private:
  bool m_enabled = true;
  class TentaclesImpl;
  const std::unique_ptr<TentaclesImpl> m_fxImpl;
};

} // namespace GOOM
#endif
