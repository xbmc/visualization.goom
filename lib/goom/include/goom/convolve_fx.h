#ifndef VISUALIZATION_GOOM_CONVOLVE_FX_H
#define VISUALIZATION_GOOM_CONVOLVE_FX_H

#include "goom_stats.h"
#include "goom_visual_fx.h"

#include <memory>
#include <string>

namespace GOOM
{

namespace UTILS
{
class Parallel;
} // namespace UTILS

struct FXBuffSettings;
class PixelBuffer;
class PluginInfo;

class ConvolveFx : public IVisualFx
{
public:
  ConvolveFx() noexcept = delete;
  ConvolveFx(UTILS::Parallel&, const std::shared_ptr<const PluginInfo>&) noexcept;
  ConvolveFx(const ConvolveFx&) noexcept = delete;
  ConvolveFx(ConvolveFx&&) noexcept = delete;
  ~ConvolveFx() noexcept override;
  auto operator=(const ConvolveFx&) -> ConvolveFx& = delete;
  auto operator=(ConvolveFx&&) -> ConvolveFx& = delete;

  void Convolve(const PixelBuffer& currentBuff, PixelBuffer& outputBuff);

  [[nodiscard]] auto GetResourcesDirectory() const -> const std::string& override;
  void SetResourcesDirectory(const std::string& dirName) override;

  [[nodiscard]] auto GetFxName() const -> std::string override;
  void SetBuffSettings(const FXBuffSettings& settings);
  void SetAllowOverexposed(bool val);

  void Start() override;

  void Log(const GoomStats::LogStatsValueFunc& l) const override;
  void Finish() override;

private:
  bool m_enabled = true;
  class ConvolveImpl;
  const std::unique_ptr<ConvolveImpl> m_fxImpl;
};

} // namespace GOOM
#endif
