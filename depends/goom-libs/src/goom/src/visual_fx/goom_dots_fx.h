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

class GoomDotsFx : public IVisualFx
{
public:
  GoomDotsFx() noexcept = delete;
  GoomDotsFx(const FxHelper& fxHelper,
             const UTILS::GRAPHICS::SmallImageBitmaps& smallBitmaps) noexcept;

  [[nodiscard]] auto GetFxName() const noexcept -> std::string override;

  auto Start() noexcept -> void override;
  auto Finish() noexcept -> void override;

  auto Resume() noexcept -> void override;
  auto Suspend() noexcept -> void override;

  static constexpr uint32_t NUM_DOT_TYPES = 5;
  auto SetWeightedColorMaps(const WeightedColorMaps& weightedColorMaps) noexcept -> void override;
  auto SetSingleBufferDots(bool val) noexcept -> void;

  [[nodiscard]] auto GetCurrentColorMapsNames() const noexcept -> std::vector<std::string> override;

  auto ApplySingle() noexcept -> void override;
  auto ApplyMultiple() noexcept -> void override;

private:
  class GoomDotsFxImpl;
  spimpl::unique_impl_ptr<GoomDotsFxImpl> m_pimpl;
};

} // namespace VISUAL_FX
} // namespace GOOM
