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

class CirclesFx : public IVisualFx
{
public:
  CirclesFx(const FxHelper& fxHelper,
            const UTILS::GRAPHICS::SmallImageBitmaps& smallBitmaps) noexcept;

  [[nodiscard]] auto GetFxName() const noexcept -> std::string override;

  auto SetWeightedColorMaps(const WeightedColorMaps& weightedColorMaps) noexcept -> void override;
  auto SetZoomMidpoint(const Point2dInt& zoomMidpoint) noexcept -> void override;

  [[nodiscard]] auto GetCurrentColorMapsNames() const noexcept -> std::vector<std::string> override;

  auto Start() noexcept -> void override;
  auto Finish() noexcept -> void override;

  auto ApplyMultiple() noexcept -> void override;

private:
  class CirclesFxImpl;
  spimpl::unique_impl_ptr<CirclesFxImpl> m_pimpl;
};

} // namespace VISUAL_FX
} // namespace GOOM
