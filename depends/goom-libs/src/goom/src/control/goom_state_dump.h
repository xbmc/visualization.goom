#pragma once

#include "goom_config.h"

#ifdef DO_GOOM_STATE_DUMP

#include "filter_fx/filter_settings_service.h"
#include "goom_all_visual_fx.h"
#include "goom_music_settings_reactor.h"
#include "utils/stopwatch.h"

#include <chrono>
#include <cstdint>
#include <memory>
#include <string_view>

namespace GOOM::CONTROL
{

class GoomStateDump
{
public:
  GoomStateDump(const PluginInfo& goomInfo,
                const GoomAllVisualFx& visualFx,
                const GoomMusicSettingsReactor& musicSettingsReactor,
                const FILTER_FX::FilterSettingsService& filterSettingsService) noexcept;
  GoomStateDump(const GoomStateDump&) noexcept = delete;
  GoomStateDump(GoomStateDump&&) noexcept      = delete;
  ~GoomStateDump() noexcept;
  auto operator=(const GoomStateDump&) -> GoomStateDump& = delete;
  auto operator=(GoomStateDump&&) -> GoomStateDump&      = delete;

  auto SetSongTitle(const std::string& songTitle) noexcept -> void;
  auto SetGoomSeed(uint64_t goomSeed) noexcept -> void;
  auto SetStopWatch(const UTILS::Stopwatch& stopwatch) noexcept -> void;

  auto Start() noexcept -> void;

  auto AddCurrentState() noexcept -> void;
  auto DumpData(const std::string& directory) -> void;

private:
  static constexpr uint32_t MIN_TIMELINE_ELEMENTS_TO_DUMP = 10;

  const PluginInfo& m_goomInfo;
  const GoomAllVisualFx& m_visualFx;
  const FILTER_FX::FilterSettingsService& m_filterSettingsService;

  using Ms = std::chrono::milliseconds;
  std::chrono::high_resolution_clock::time_point m_prevTimeHiRes{};

  class CumulativeState;
  std::unique_ptr<CumulativeState> m_cumulativeState;

  std::string m_songTitle{};
  std::string m_dateTime{};
  uint64_t m_goomSeed{};
  const UTILS::Stopwatch* m_stopwatch{};

  std::string m_datedDirectory{};
  auto SetCurrentDatedDirectory(const std::string& parentDirectory) -> void;
  auto DumpSummary() const noexcept -> void;
  template<typename T>
  auto DumpDataArray(const std::string& filename, const std::vector<T>& dataArray) const noexcept
      -> void;
};

inline auto GoomStateDump::SetSongTitle(const std::string& songTitle) noexcept -> void
{
  m_songTitle = songTitle;
}

inline auto GoomStateDump::SetGoomSeed(const uint64_t goomSeed) noexcept -> void
{
  m_goomSeed = goomSeed;
}

inline auto GoomStateDump::SetStopWatch(const UTILS::Stopwatch& stopwatch) noexcept -> void
{
  m_stopwatch = &stopwatch;
}

} // namespace GOOM::CONTROL

#endif // DO_GOOM_STATE_DUMP
