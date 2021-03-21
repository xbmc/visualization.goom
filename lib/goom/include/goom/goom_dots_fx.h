#ifndef VISUALIZATION_GOOM_GOOM_DOTS_FX_H
#define VISUALIZATION_GOOM_GOOM_DOTS_FX_H

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

class GoomDotsFx : public IVisualFx
{
public:
  GoomDotsFx() noexcept = delete;
  explicit GoomDotsFx(const IGoomDraw* draw, const std::shared_ptr<const PluginInfo>&) noexcept;
  GoomDotsFx(const GoomDotsFx&) noexcept = delete;
  GoomDotsFx(GoomDotsFx&&) noexcept = delete;
  ~GoomDotsFx() noexcept override;
  auto operator=(const GoomDotsFx&) -> GoomDotsFx& = delete;
  auto operator=(GoomDotsFx&&) -> GoomDotsFx& = delete;

  [[nodiscard]] auto GetFxName() const -> std::string override;

  [[nodiscard]] auto GetResourcesDirectory() const -> const std::string& override;
  void SetResourcesDirectory(const std::string& dirName) override;

  void SetSmallImageBitmaps(const UTILS::SmallImageBitmaps& smallBitmaps);

  void Start() override;

  void Resume() override;
  void Suspend() override;

  static constexpr uint32_t NUM_DOT_TYPES = 5;
  void SetWeightedColorMaps(uint32_t dotNum, std::shared_ptr<UTILS::RandomColorMaps> weightedMaps);

  void ApplySingle();
  void ApplyMultiple();

  void Log(const GoomStats::LogStatsValueFunc& l) const override;
  void Finish() override;

private:
  bool m_enabled = true;
  class GoomDotsFxImpl;
  const std::unique_ptr<GoomDotsFxImpl> m_fxImpl;
};

} // namespace GOOM

#endif /* VISUALIZATION_GOOM_GOOM_DOTS_FX_H */
