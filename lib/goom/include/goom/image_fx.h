#ifndef VISUALIZATION_GOOM_IMAGE_FX_H
#define VISUALIZATION_GOOM_IMAGE_FX_H

#include "goom_stats.h"
#include "goom_visual_fx.h"

#include <memory>
#include <string>

namespace GOOM
{

class IGoomDraw;
class PluginInfo;

class ImageFx : public IVisualFx
{
public:
  ImageFx() noexcept;
  explicit ImageFx(const IGoomDraw* draw, const std::shared_ptr<const PluginInfo>&) noexcept;
  ImageFx(const ImageFx&) noexcept = delete;
  ImageFx(ImageFx&&) noexcept = delete;
  ~ImageFx() noexcept override;
  auto operator=(const ImageFx&) -> ImageFx& = delete;
  auto operator=(ImageFx&&) -> ImageFx& = delete;

  [[nodiscard]] auto GetFxName() const -> std::string override;

  [[nodiscard]] auto GetResourcesDirectory() const -> const std::string& override;
  void SetResourcesDirectory(const std::string& dirName) override;

  void Start() override;

  void ApplyMultiple();

  void Log(const GoomStats::LogStatsValueFunc& l) const override;
  void Finish() override;

private:
  bool m_enabled = true;
  class ImageFxImpl;
  const std::unique_ptr<ImageFxImpl> m_fxImpl;
};

} // namespace GOOM

#endif /* VISUALIZATION_GOOM_IMAGE_FX_H */
