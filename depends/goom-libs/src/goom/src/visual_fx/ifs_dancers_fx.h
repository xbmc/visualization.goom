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

namespace UTILS::GRAPHICS
{
class SmallImageBitmaps;
}

namespace VISUAL_FX
{
class FxHelper;

class IfsDancersFx : public IVisualFx
{
public:
  enum class ColorMode
  {
    _NULL = -1, // NOLINT: Need special name here
    MAP_COLORS,
    MIX_COLORS,
    REVERSE_MIX_COLORS,
    MEGA_MAP_COLOR_CHANGE,
    MEGA_MIX_COLOR_CHANGE,
    SINGLE_COLORS,
    SINE_MIX_COLORS,
    SINE_MAP_COLORS,
    _num // unused, and marks the enum end
  };

  IfsDancersFx() noexcept = delete;
  IfsDancersFx(const FxHelper& fxHelper,
               const UTILS::GRAPHICS::SmallImageBitmaps& smallBitmaps) noexcept;

  [[nodiscard]] auto GetFxName() const noexcept -> std::string override;

  auto Start() noexcept -> void override;
  auto Finish() noexcept -> void override;

  auto Resume() noexcept -> void override;
  auto Suspend() noexcept -> void override;

  auto SetWeightedColorMaps(const WeightedColorMaps& weightedColorMaps) noexcept -> void override;
  auto Refresh() noexcept -> void override;
  auto PostStateUpdate(bool wasActiveInPreviousState) noexcept -> void override;

  [[nodiscard]] auto GetCurrentColorMapsNames() const noexcept -> std::vector<std::string> override;

  auto ApplyNoDraw() noexcept -> void override;
  auto ApplyMultiple() noexcept -> void override;

private:
  class IfsDancersFxImpl;
  spimpl::unique_impl_ptr<IfsDancersFxImpl> m_pimpl;
};

} // namespace VISUAL_FX
} // namespace GOOM
