#ifndef VISUALIZATION_GOOM_VISUAL_FX_H
#define VISUALIZATION_GOOM_VISUAL_FX_H

#include "goom_stats.h"

#include <string>

namespace GOOM
{

class IVisualFx
{
public:
  IVisualFx() = default;
  IVisualFx(const IVisualFx&) noexcept = delete;
  IVisualFx(IVisualFx&&) noexcept = delete;
  virtual ~IVisualFx() = default;
  auto operator=(const IVisualFx&) -> IVisualFx& = delete;
  auto operator=(IVisualFx&&) -> IVisualFx& = delete;

  [[nodiscard]] virtual auto GetFxName() const -> std::string = 0;

  [[nodiscard]] virtual auto GetResourcesDirectory() const -> const std::string& = 0;
  virtual void SetResourcesDirectory(const std::string& dirName) = 0;

  virtual void Start() = 0;

  virtual void Resume(){};
  virtual void Suspend(){};

  virtual void Log(const GoomStats::LogStatsValueFunc& l) const = 0;
  virtual void Finish() = 0;
};

} // namespace GOOM
#endif
