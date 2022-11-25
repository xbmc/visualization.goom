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

class ShapesFx : public IVisualFx
{
public:
  static constexpr uint32_t NUM_SHAPES = 1;

  explicit ShapesFx(const FxHelper& fxHelper) noexcept;

  [[nodiscard]] auto GetFxName() const noexcept -> std::string override;

  auto Start() noexcept -> void override;
  auto Finish() noexcept -> void override;

  auto SetWeightedColorMaps(const WeightedColorMaps& weightedColorMaps) noexcept -> void override;
  auto SetZoomMidpoint(const Point2dInt& zoomMidpoint) noexcept -> void override;

  [[nodiscard]] auto GetCurrentColorMapsNames() const noexcept -> std::vector<std::string> override;

  auto ApplyMultiple() noexcept -> void override;

private:
  class ShapesFxImpl;
  spimpl::unique_impl_ptr<ShapesFxImpl> m_pimpl;
};

} // namespace VISUAL_FX
} // namespace GOOM
