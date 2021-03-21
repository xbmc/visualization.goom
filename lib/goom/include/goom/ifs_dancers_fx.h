#ifndef VISUALIZATION_GOOM_IFS_DANCERS_FX_H
#define VISUALIZATION_GOOM_IFS_DANCERS_FX_H

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

class IfsDancersFx : public IVisualFx
{
public:
  enum class ColorMode
  {
    _NULL = -1,
    MAP_COLORS,
    MIX_COLORS,
    REVERSE_MIX_COLORS,
    MEGA_MAP_COLOR_CHANGE,
    MEGA_MIX_COLOR_CHANGE,
    SINGLE_COLORS,
    SINE_MIX_COLORS,
    SINE_MAP_COLORS,
    _NUM // unused and must be last
  };

  IfsDancersFx() noexcept = delete;
  explicit IfsDancersFx(const IGoomDraw* draw, const std::shared_ptr<const PluginInfo>&) noexcept;
  IfsDancersFx(const IfsDancersFx&) noexcept = delete;
  IfsDancersFx(IfsDancersFx&&) noexcept = delete;
  ~IfsDancersFx() noexcept override;
  auto operator=(const IfsDancersFx&) -> IfsDancersFx& = delete;
  auto operator=(IfsDancersFx&&) -> IfsDancersFx& = delete;

  [[nodiscard]] auto GetFxName() const -> std::string override;

  [[nodiscard]] auto GetResourcesDirectory() const -> const std::string& override;
  void SetResourcesDirectory(const std::string& dirName) override;

  void SetSmallImageBitmaps(const UTILS::SmallImageBitmaps& smallBitmaps);

  void Init();

  // If colorMode is not set or set to '_null', then returns
  // random weighted color mode.
  [[nodiscard]] auto GetColorMode() const -> ColorMode;
  void SetColorMode(ColorMode c);

  void Renew();
  void UpdateIncr();

  void Start() override;

  void Resume() override;
  void Suspend() override;

  void SetWeightedColorMaps(std::shared_ptr<UTILS::RandomColorMaps> weightedMaps);

  void ApplyNoDraw();
  void ApplyMultiple();

  void Log(const GoomStats::LogStatsValueFunc& l) const override;
  void Finish() override;

private:
  bool m_enabled = true;
  class IfsDancersFxImpl;
  const std::unique_ptr<IfsDancersFxImpl> m_fxImpl;
};

} // namespace GOOM
#endif
