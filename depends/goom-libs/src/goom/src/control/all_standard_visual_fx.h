#pragma once

#include "goom_graphic.h"
#include "goom_states.h"
#include "point2d.h"
#include "utils/enum_utils.h"
#include "utils/propagate_const.h"
#include "utils/stopwatch.h"
#include "visual_fx/shader_fx.h"
#include "visual_fx_color_maps.h"

#include <functional>
#include <memory>
#include <unordered_set>

namespace GOOM
{
class AudioSamples;

namespace UTILS
{
class Parallel;

namespace GRAPHICS
{
class SmallImageBitmaps;
}
}

namespace VISUAL_FX
{
class IVisualFx;
class LinesFx;
class ShaderFx;
}

namespace CONTROL
{

class AllStandardVisualFx
{
public:
  using GoomDrawablesSet = std::unordered_set<GoomDrawables>;

  AllStandardVisualFx(UTILS::Parallel& parallel,
                      const VISUAL_FX::FxHelper& fxHelper,
                      const UTILS::GRAPHICS::SmallImageBitmaps& smallBitmaps,
                      const std::string& resourcesDirectory) noexcept;

  [[nodiscard]] auto GetCurrentGoomDrawables() const -> const GoomDrawablesSet&;
  auto SetCurrentGoomDrawables(const GoomDrawablesSet& goomDrawablesSet) -> void;

  auto ChangeColorMaps() -> void;
  [[nodiscard]] auto GetActiveColorMapsNames() const -> std::unordered_set<std::string>;

  using ResetCurrentDrawBuffSettingsFunc = std::function<void(GoomDrawables fx)>;
  auto SetResetDrawBuffSettingsFunc(const ResetCurrentDrawBuffSettingsFunc& func) -> void;

  auto SetSingleBufferDots(bool val) -> void;

  auto Start() -> void;
  auto Finish() -> void;

  auto RefreshAllFx() -> void;
  auto SuspendFx() -> void;
  auto ResumeFx() -> void;
  auto SetZoomMidpoint(const Point2dInt& zoomMidpoint) -> void;
  auto PostStateUpdate(const GoomDrawablesSet& oldGoomDrawables) -> void;

  auto ApplyCurrentStateToSingleBuffer() -> void;
  auto ApplyCurrentStateToMultipleBuffers(const AudioSamples& soundData) -> void;
  auto ApplyEndEffectIfNearEnd(const UTILS::Stopwatch::TimeValues& timeValues) -> void;

  [[nodiscard]] auto GetLinesFx() noexcept -> VISUAL_FX::LinesFx&;

  auto ChangeShaderEffects() -> void;
  [[nodiscard]] auto GetLastShaderEffects() const -> const GoomShaderEffects&;

private:
  std::experimental::propagate_const<std::unique_ptr<VISUAL_FX::ShaderFx>> m_shaderFx;
  using PropagateConstUniquePtr =
      std::experimental::propagate_const<std::unique_ptr<VISUAL_FX::IVisualFx>>;
  UTILS::EnumMap<GoomDrawables, PropagateConstUniquePtr> m_drawablesMap;
  [[nodiscard]] static auto GetDrawablesMap(UTILS::Parallel& parallel,
                                            const VISUAL_FX::FxHelper& fxHelper,
                                            const UTILS::GRAPHICS::SmallImageBitmaps& smallBitmaps,
                                            const std::string& resourcesDirectory)
      -> UTILS::EnumMap<GoomDrawables, PropagateConstUniquePtr>;
  VisualFxColorMaps m_visualFxColorMaps;
  auto ChangeDotsColorMaps() noexcept -> void;
  auto ChangeLinesColorMaps() noexcept -> void;
  auto ChangeShapesColorMaps() noexcept -> void;
  auto ChangeStarsColorMaps() noexcept -> void;
  auto ChangeTentaclesColorMaps() noexcept -> void;

  GoomDrawablesSet m_currentGoomDrawables{};
  [[nodiscard]] auto IsCurrentlyDrawable(GoomDrawables goomDrawable) const -> bool;
  ResetCurrentDrawBuffSettingsFunc m_resetCurrentDrawBuffSettingsFunc{};
  auto ResetDrawBuffSettings(GoomDrawables fx) -> void;

  auto ApplyStandardFxToMultipleBuffers(const AudioSamples& soundData) -> void;
  auto ApplyShaderToBothBuffersIfRequired() -> void;
};

inline auto AllStandardVisualFx::GetCurrentGoomDrawables() const -> const GoomDrawablesSet&
{
  return m_currentGoomDrawables;
}

inline void AllStandardVisualFx::SetCurrentGoomDrawables(const GoomDrawablesSet& goomDrawablesSet)
{
  m_currentGoomDrawables = goomDrawablesSet;
}

inline void AllStandardVisualFx::SetResetDrawBuffSettingsFunc(
    const ResetCurrentDrawBuffSettingsFunc& func)
{
  m_resetCurrentDrawBuffSettingsFunc = func;
}

inline void AllStandardVisualFx::ResetDrawBuffSettings(const GoomDrawables fx)
{
  m_resetCurrentDrawBuffSettingsFunc(fx);
}

inline auto AllStandardVisualFx::ApplyCurrentStateToMultipleBuffers(const AudioSamples& soundData)
    -> void
{
  ApplyStandardFxToMultipleBuffers(soundData);
  ApplyShaderToBothBuffersIfRequired();
}

} // namespace CONTROL
} // namespace GOOM
