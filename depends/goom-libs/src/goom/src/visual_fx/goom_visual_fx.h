#pragma once

#include <cstdint>
#include <memory>
#include <string>
#include <vector>

namespace GOOM
{
struct Point2dInt;
class AudioSamples;

namespace COLOR
{
class RandomColorMaps;
}

namespace VISUAL_FX
{

class IVisualFx
{
public:
  IVisualFx() noexcept                           = default;
  IVisualFx(const IVisualFx&) noexcept           = delete;
  IVisualFx(IVisualFx&&) noexcept                = delete;
  virtual ~IVisualFx() noexcept                  = default;
  auto operator=(const IVisualFx&) -> IVisualFx& = delete;
  auto operator=(IVisualFx&&) -> IVisualFx&      = delete;

  [[nodiscard]] virtual auto GetFxName() const noexcept -> std::string = 0;

  virtual auto Start() noexcept -> void  = 0;
  virtual auto Finish() noexcept -> void = 0;

  virtual auto Resume() noexcept -> void
  { /* default does nothing */
  }
  virtual auto Suspend() noexcept -> void
  { /* default does nothing */
  }

  virtual auto Refresh() noexcept -> void
  { /* default does nothing */
  }

  virtual auto PostStateUpdate([[maybe_unused]] const bool wasActiveInPreviousState) noexcept
      -> void
  { /* default does nothing */
  }

  virtual auto SetZoomMidpoint([[maybe_unused]] const Point2dInt& zoomMidpoint) noexcept -> void
  { /* default does nothing */
  }

  [[nodiscard]] virtual auto GetCurrentColorMapsNames() const noexcept
      -> std::vector<std::string> = 0;
  struct WeightedColorMaps
  {
    uint32_t id                                                  = 0;
    std::shared_ptr<const COLOR::RandomColorMaps> mainColorMaps  = nullptr;
    std::shared_ptr<const COLOR::RandomColorMaps> lowColorMaps   = nullptr;
    std::shared_ptr<const COLOR::RandomColorMaps> extraColorMaps = nullptr;
  };
  virtual auto SetWeightedColorMaps(
      [[maybe_unused]] const WeightedColorMaps& weightedColorMaps) noexcept -> void
  { /* default does nothing */
  }

  virtual auto SetSoundData([[maybe_unused]] const AudioSamples& soundData) noexcept -> void
  { /* default does nothing */
  }

  virtual auto ApplyNoDraw() noexcept -> void
  { /* default does nothing */
  }
  virtual auto ApplySingle() noexcept -> void
  { /* default does nothing */
  }
  virtual auto ApplyMultiple() noexcept -> void
  { /* default does nothing */
  }
};

} // namespace VISUAL_FX
} // namespace GOOM
