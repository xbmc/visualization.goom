#pragma once

#include "goom_visual_fx.h"
#include "spimpl.h"

#include <string>
#include <vector>

namespace GOOM
{

namespace COLOR
{
class RandomColorMaps;
}

namespace VISUAL_FX
{
class FxHelper;

class TentaclesFx : public IVisualFx
{
  static constexpr auto DOMINANT_COLOR_TYPE = 0U;
  static constexpr auto NORMAL_COLOR_TYPE   = 1U;

public:
  static constexpr uint32_t NUM_TENTACLE_COLOR_TYPES = NORMAL_COLOR_TYPE + 1;

  TentaclesFx() noexcept = delete;
  explicit TentaclesFx(const FxHelper& fxHelper) noexcept;

  [[nodiscard]] auto GetFxName() const noexcept -> std::string override;

  auto SetWeightedColorMaps(const WeightedColorMaps& weightedColorMaps) noexcept -> void override;
  [[nodiscard]] auto GetCurrentColorMapsNames() const noexcept -> std::vector<std::string> override;

  auto SetZoomMidpoint(const Point2dInt& zoomMidpoint) noexcept -> void override;

  auto Start() noexcept -> void override;
  auto Finish() noexcept -> void override;

  auto Resume() noexcept -> void override;
  auto Suspend() noexcept -> void override;

  auto ApplyMultiple() noexcept -> void override;

private:
  class TentaclesImpl;
  spimpl::unique_impl_ptr<TentaclesImpl> m_pimpl;
};

} // namespace VISUAL_FX
} // namespace GOOM
