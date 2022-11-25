#pragma once

#include "goom_graphic.h"
#include "goom_visual_fx.h"
#include "spimpl.h"

#include <string>
#include <vector>

namespace GOOM
{

class AudioSamples;

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

class LinesFx : public IVisualFx
{
public:
  static constexpr uint32_t NUM_LINES = 2;

  // construit un effet de line (une ligne horitontale pour commencer)
  LinesFx() noexcept = delete;
  LinesFx(const FxHelper& fxHelper,
          const UTILS::GRAPHICS::SmallImageBitmaps& smallBitmaps) noexcept;

  [[nodiscard]] auto GetFxName() const noexcept -> std::string override;

  auto SetWeightedColorMaps(const WeightedColorMaps& weightedColorMaps) noexcept -> void override;
  [[nodiscard]] auto GetCurrentColorMapsNames() const noexcept -> std::vector<std::string> override;

  auto Start() noexcept -> void override;
  auto Finish() noexcept -> void override;

  auto ResetLineModes() noexcept -> void;

  auto SetSoundData(const AudioSamples& soundData) noexcept -> void override;
  auto ApplyMultiple() noexcept -> void override;

private:
  class LinesImpl;
  spimpl::unique_impl_ptr<LinesImpl> m_pimpl;
};

} // namespace VISUAL_FX
} // namespace GOOM
