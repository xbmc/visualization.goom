#include "goom_state_dump.h"

#ifdef DO_GOOM_STATE_DUMP

#undef NO_LOGGING

#include "filter_fx/filter_settings_service.h"
#include "logging.h"
#include "goom_all_visual_fx.h"
#include "goom_graphic.h"
#include "goom_music_settings_reactor.h"
#include "utils/date_utils.h"

#include <filesystem>
#include <fstream>
#include <string>

namespace GOOM::CONTROL
{

using FILTER_FX::FilterSettingsService;
using FILTER_FX::HypercosOverlay;
using FILTER_FX::ZoomFilterMode;
using UTILS::GetCurrentDateTimeAsString;
using UTILS::Logging;

class GoomStateDump::CumulativeState
{
public:
  CumulativeState() noexcept;

  void Reset();
  void IncrementUpdateNum();

  [[nodiscard]] auto GetNumUpdates() const -> uint32_t;

  void AddCurrentUpdateTime(uint32_t timeInMs);

  void AddCurrentGoomState(GoomStates goomState);
  void AddCurrentFilterMode(ZoomFilterMode filterMode);
  void AddCurrentHypercosOverlay(HypercosOverlay hypercosOverlay);
  void AddCurrentBlockyWavyEffect(bool value);
  void AddCurrentImageVelocityEffect(bool value);
  void AddCurrentNoiseEffect(bool value);
  void AddCurrentPlaneEffect(bool value);
  void AddCurrentRotationEffect(bool value);
  void AddCurrentTanEffect(bool value);
  void AddCurrentXYLerpEffect(bool value);

  void AddBufferLerp(int32_t value);

  void AddCurrentTimeSinceLastGoom(uint32_t value);
  void AddCurrentTimeSinceLastBigGoom(uint32_t value);
  void AddCurrentTotalGoomsInCurrentCycle(uint32_t value);
  void AddCurrentGoomPower(float value);
  void AddCurrentGoomVolume(float value);

  [[nodiscard]] auto GetUpdateTimesInMs() const -> const std::vector<uint32_t>&;

  [[nodiscard]] auto GetGoomStates() const -> const std::vector<uint8_t>&;
  [[nodiscard]] auto GetFilterModes() const -> const std::vector<uint8_t>&;
  [[nodiscard]] auto GetHypercosOverlays() const -> const std::vector<uint8_t>&;
  [[nodiscard]] auto GetBlockyWavyEffects() const -> const std::vector<uint8_t>&;
  [[nodiscard]] auto GetImageVelocityEffects() const -> const std::vector<uint8_t>&;
  [[nodiscard]] auto GetNoiseEffects() const -> const std::vector<uint8_t>&;
  [[nodiscard]] auto GetPlaneEffects() const -> const std::vector<uint8_t>&;
  [[nodiscard]] auto GetRotationEffects() const -> const std::vector<uint8_t>&;
  [[nodiscard]] auto GetTanEffects() const -> const std::vector<uint8_t>&;
  [[nodiscard]] auto GetXYLerpEffects() const -> const std::vector<uint8_t>&;

  [[nodiscard]] auto GetBufferLerps() const -> const std::vector<int32_t>&;

  [[nodiscard]] auto GetTimesSinceLastGoom() const -> const std::vector<uint32_t>&;
  [[nodiscard]] auto GetTimesSinceLastBigGoom() const -> const std::vector<uint32_t>&;
  [[nodiscard]] auto GetTotalGoomsInCurrentCycle() const -> const std::vector<uint32_t>&;
  [[nodiscard]] auto GetGoomPowers() const -> const std::vector<float>&;
  [[nodiscard]] auto GetGoomVolumes() const -> const std::vector<float>&;

private:
  static constexpr uint32_t INITIAL_NUM_UPDATES_ESTIMATE = 5 * 60 * 60 * 25;
  static constexpr uint32_t EXTRA_NUM_UPDATES_ESTIMATE   = 1 * 60 * 60 * 25;
  uint32_t m_numUpdatesEstimate                          = INITIAL_NUM_UPDATES_ESTIMATE;
  uint32_t m_updateNum                                   = 0;

  std::vector<uint32_t> m_updateTimesInMs{};
  std::vector<uint8_t> m_goomStates{};
  std::vector<uint8_t> m_filterModes{};
  std::vector<uint8_t> m_hypercosOverlays{};
  std::vector<uint8_t> m_blockyWavyEffects{};
  std::vector<uint8_t> m_imageVelocityEffects{};
  std::vector<uint8_t> m_noiseEffects{};
  std::vector<uint8_t> m_planeEffects{};
  std::vector<uint8_t> m_rotationEffects{};
  std::vector<uint8_t> m_tanEffects{};
  std::vector<uint8_t> m_xyLerpEffects{};

  std::vector<int32_t> m_bufferLerps{};

  std::vector<uint32_t> m_timesSinceLastGoom{};
  std::vector<uint32_t> m_timesSinceLastBigGoom{};
  std::vector<uint32_t> m_totalGoomsInCurrentCycle{};
  std::vector<float> m_goomPowers{};
  std::vector<float> m_goomVolumes{};

  void Reserve();
};

GoomStateDump::GoomStateDump(const PluginInfo& goomInfo,
                             const GoomAllVisualFx& visualFx,
                             [[maybe_unused]] const GoomMusicSettingsReactor& musicSettingsReactor,
                             const FilterSettingsService& filterSettingsService) noexcept
  : m_goomInfo{goomInfo},
    m_visualFx{visualFx},
    //    m_musicSettingsReactor{musicSettingsReactor},
    m_filterSettingsService{filterSettingsService},
    m_cumulativeState{std::make_unique<CumulativeState>()}
{
}

GoomStateDump::~GoomStateDump() noexcept = default;

auto GoomStateDump::Start() noexcept -> void
{
  m_cumulativeState->Reset();

  m_prevTimeHiRes = std::chrono::high_resolution_clock::now();
}

auto GoomStateDump::AddCurrentState() noexcept -> void
{
  const auto timeNow          = std::chrono::high_resolution_clock::now();
  const auto diff             = std::chrono::duration_cast<Ms>(timeNow - m_prevTimeHiRes);
  const auto timeOfUpdateInMs = static_cast<uint32_t>(diff.count());
  m_cumulativeState->AddCurrentUpdateTime(timeOfUpdateInMs);
  m_prevTimeHiRes = timeNow;

  m_cumulativeState->AddCurrentGoomState(m_visualFx.GetCurrentState());
  m_cumulativeState->AddCurrentFilterMode(m_filterSettingsService.GetCurrentFilterMode());

  const auto filterSettings = m_filterSettingsService.GetFilterSettings();

  const auto filterColorSettings = filterSettings.filterColorSettings;
  m_cumulativeState->AddCurrentBlockyWavyEffect(filterColorSettings.blockyWavy);

  const auto filterEffectsSettings = filterSettings.filterEffectsSettings;
  m_cumulativeState->AddCurrentHypercosOverlay(filterEffectsSettings.hypercosOverlay);
  m_cumulativeState->AddCurrentImageVelocityEffect(filterEffectsSettings.imageVelocityEffect);
  m_cumulativeState->AddCurrentNoiseEffect(filterEffectsSettings.noiseEffect);
  m_cumulativeState->AddCurrentPlaneEffect(filterEffectsSettings.planeEffect);
  m_cumulativeState->AddCurrentRotationEffect(filterEffectsSettings.rotationEffect);
  m_cumulativeState->AddCurrentTanEffect(filterEffectsSettings.tanEffect);
  m_cumulativeState->AddCurrentXYLerpEffect(filterEffectsSettings.xyLerpEffect);

  m_cumulativeState->AddBufferLerp(m_visualFx.GetZoomFilterFx().GetTranLerpFactor());

  const auto& goomSoundEvents = m_goomInfo.GetSoundEvents();
  m_cumulativeState->AddCurrentTimeSinceLastGoom(goomSoundEvents.GetTimeSinceLastGoom());
  m_cumulativeState->AddCurrentTimeSinceLastBigGoom(goomSoundEvents.GetTimeSinceLastBigGoom());
  m_cumulativeState->AddCurrentTotalGoomsInCurrentCycle(
      goomSoundEvents.GetTotalGoomsInCurrentCycle());
  m_cumulativeState->AddCurrentGoomPower(goomSoundEvents.GetGoomPower());
  m_cumulativeState->AddCurrentGoomVolume(goomSoundEvents.GetSoundInfo().GetVolume());

  m_cumulativeState->IncrementUpdateNum();
}

auto GoomStateDump::DumpData(const std::string& directory) -> void
{
  if (m_cumulativeState->GetNumUpdates() < MIN_TIMELINE_ELEMENTS_TO_DUMP)
  {
    LogWarn("Not dumping. Too few goom updates: {} < {}.",
            m_cumulativeState->GetNumUpdates(),
            MIN_TIMELINE_ELEMENTS_TO_DUMP);
    return;
  }

  m_dateTime = GetCurrentDateTimeAsString();

  SetCurrentDatedDirectory(directory);

  DumpSummary();

  DumpDataArray("update_times", m_cumulativeState->GetUpdateTimesInMs());

  DumpDataArray("goom_states", m_cumulativeState->GetGoomStates());
  DumpDataArray("filter_modes", m_cumulativeState->GetFilterModes());
  DumpDataArray("hypercos_overlays", m_cumulativeState->GetHypercosOverlays());
  DumpDataArray("blocky_wavy_effects", m_cumulativeState->GetBlockyWavyEffects());
  DumpDataArray("image_velocity_effects", m_cumulativeState->GetImageVelocityEffects());
  DumpDataArray("noise_effects", m_cumulativeState->GetNoiseEffects());
  DumpDataArray("plane_effects", m_cumulativeState->GetPlaneEffects());
  DumpDataArray("rotation_effects", m_cumulativeState->GetRotationEffects());
  DumpDataArray("tan_effects", m_cumulativeState->GetTanEffects());
  DumpDataArray("xyLerp_effects", m_cumulativeState->GetXYLerpEffects());

  DumpDataArray("buffer_lerps", m_cumulativeState->GetBufferLerps());

  DumpDataArray("times_since_last_goom", m_cumulativeState->GetTimesSinceLastGoom());
  DumpDataArray("times_since_last_big_goom", m_cumulativeState->GetTimesSinceLastBigGoom());
  DumpDataArray("total_gooms_in_current_cycle", m_cumulativeState->GetTotalGoomsInCurrentCycle());
  DumpDataArray("goom_powers", m_cumulativeState->GetGoomPowers());
  DumpDataArray("goom_volumes", m_cumulativeState->GetGoomVolumes());
}

auto GoomStateDump::DumpSummary() const noexcept -> void
{
  static constexpr auto SUMMARY_FILENAME = "summary.dat";
  auto out = std::ofstream{};
  out.open(m_datedDirectory + "/" + SUMMARY_FILENAME, std::ofstream::out);

  out << "Song:       " << m_songTitle << "\n";
  out << "Date:       " << m_dateTime << "\n";
  out << "Seed:       " << m_goomSeed << "\n";
  out << "Width:      " << m_goomInfo.GetScreenWidth() << "\n";
  out << "Height:     " << m_goomInfo.GetScreenHeight() << "\n";
  out << "Start Time: " << m_stopwatch->GetStartTimeAsStr() << "\n";
  out << "Stop Time:  " << m_stopwatch->GetLastMarkedTimeAsStr() << "\n";
  out << "Act Dur:    " << m_stopwatch->GetActualDurationInMs() << "\n";
  out << "Given Dur:  " << m_stopwatch->GetDurationInMs() << "\n";
  out << "Time Left:  " << m_stopwatch->GetTimeValues().timeRemainingInMs << "\n";

  out.close();
}

auto GoomStateDump::SetCurrentDatedDirectory(const std::string& parentDirectory) -> void
{
  m_datedDirectory = parentDirectory + "/" + m_dateTime;
  LogInfo("Dumping state data to \"{}\"...", m_datedDirectory);
  std::filesystem::create_directories(m_datedDirectory);
}

inline std::ostream& operator<<(std::ostream& out, const uint8_t value)
{
  return out << static_cast<uint32_t>(value);
}

template<typename T>
auto GoomStateDump::DumpDataArray(const std::string& filename,
                                  const std::vector<T>& dataArray) const noexcept -> void
{
  const auto dataLen = m_cumulativeState->GetNumUpdates();
  LogInfo("Dumping Goom state data ({} values) to \"{}\".", dataLen, filename);

  static constexpr auto EXT = ".dat";
  auto out = std::ofstream{};
  out.open(m_datedDirectory + "/" + filename + EXT, std::ofstream::out);

  for (auto i = 0U; i < dataLen; ++i)
  {
    out << dataArray[i] << "\n";
  }

  out.close();
}

GoomStateDump::CumulativeState::CumulativeState() noexcept = default;

inline void GoomStateDump::CumulativeState::Reset()
{
  m_updateNum = 0;

  Reserve();
}

void GoomStateDump::CumulativeState::Reserve()
{
  m_updateTimesInMs.reserve(m_numUpdatesEstimate);
  m_goomStates.reserve(m_numUpdatesEstimate);
  m_filterModes.reserve(m_numUpdatesEstimate);
  m_bufferLerps.reserve(m_numUpdatesEstimate);
  m_hypercosOverlays.reserve(m_numUpdatesEstimate);
  m_blockyWavyEffects.reserve(m_numUpdatesEstimate);
  m_imageVelocityEffects.reserve(m_numUpdatesEstimate);
  m_noiseEffects.reserve(m_numUpdatesEstimate);
  m_planeEffects.reserve(m_numUpdatesEstimate);
  m_rotationEffects.reserve(m_numUpdatesEstimate);
  m_tanEffects.reserve(m_numUpdatesEstimate);
  m_xyLerpEffects.reserve(m_numUpdatesEstimate);
}

inline void GoomStateDump::CumulativeState::IncrementUpdateNum()
{
  ++m_updateNum;

  if (m_updateNum > m_numUpdatesEstimate)
  {
    m_numUpdatesEstimate += EXTRA_NUM_UPDATES_ESTIMATE;
    Reserve();
  }
}

inline void GoomStateDump::CumulativeState::AddCurrentUpdateTime(const uint32_t timeInMs)
{
  m_updateTimesInMs.push_back(timeInMs);
}

inline void GoomStateDump::CumulativeState::AddCurrentGoomState(const GoomStates goomState)
{
  m_goomStates.push_back(static_cast<uint8_t>(goomState));
}

inline void GoomStateDump::CumulativeState::AddCurrentFilterMode(const ZoomFilterMode filterMode)
{
  m_filterModes.push_back(static_cast<uint8_t>(filterMode));
}

inline void GoomStateDump::CumulativeState::AddCurrentHypercosOverlay(
    const HypercosOverlay hypercosOverlay)
{
  m_hypercosOverlays.push_back(static_cast<uint8_t>(hypercosOverlay));
}

inline void GoomStateDump::CumulativeState::AddCurrentBlockyWavyEffect(const bool value)
{
  m_blockyWavyEffects.push_back(static_cast<uint8_t>(value));
}

inline void GoomStateDump::CumulativeState::AddCurrentImageVelocityEffect(const bool value)
{
  m_imageVelocityEffects.push_back(static_cast<uint8_t>(value));
}

inline void GoomStateDump::CumulativeState::AddCurrentNoiseEffect(const bool value)
{
  m_noiseEffects.push_back(static_cast<uint8_t>(value));
}

inline void GoomStateDump::CumulativeState::AddCurrentPlaneEffect(const bool value)
{
  m_planeEffects.push_back(static_cast<uint8_t>(value));
}

inline void GoomStateDump::CumulativeState::AddCurrentRotationEffect(const bool value)
{
  m_rotationEffects.push_back(static_cast<uint8_t>(value));
}

inline void GoomStateDump::CumulativeState::AddBufferLerp(const int32_t value)
{
  m_bufferLerps.push_back(value);
}

inline void GoomStateDump::CumulativeState::AddCurrentTanEffect(const bool value)
{
  m_tanEffects.push_back(static_cast<uint8_t>(value));
}

inline void GoomStateDump::CumulativeState::AddCurrentXYLerpEffect(const bool value)
{
  m_xyLerpEffects.push_back(static_cast<uint8_t>(value));
}

inline void GoomStateDump::CumulativeState::AddCurrentTimeSinceLastGoom(const uint32_t value)
{
  m_timesSinceLastGoom.push_back(value);
}

inline void GoomStateDump::CumulativeState::AddCurrentTimeSinceLastBigGoom(const uint32_t value)
{
  m_timesSinceLastBigGoom.push_back(value);
}

inline void GoomStateDump::CumulativeState::AddCurrentTotalGoomsInCurrentCycle(const uint32_t value)
{
  m_totalGoomsInCurrentCycle.push_back(value);
}

inline void GoomStateDump::CumulativeState::AddCurrentGoomPower(const float value)
{
  m_goomPowers.push_back(value);
}

inline void GoomStateDump::CumulativeState::AddCurrentGoomVolume(const float value)
{
  m_goomVolumes.push_back(value);
}

inline auto GoomStateDump::CumulativeState::GetNumUpdates() const -> uint32_t
{
  return m_updateNum;
}

inline auto GoomStateDump::CumulativeState::GetUpdateTimesInMs() const
    -> const std::vector<uint32_t>&
{
  return m_updateTimesInMs;
}

inline auto GoomStateDump::CumulativeState::GetGoomStates() const -> const std::vector<uint8_t>&
{
  return m_goomStates;
}

inline auto GoomStateDump::CumulativeState::GetFilterModes() const -> const std::vector<uint8_t>&
{
  return m_filterModes;
}

inline auto GoomStateDump::CumulativeState::GetHypercosOverlays() const
    -> const std::vector<uint8_t>&
{
  return m_hypercosOverlays;
}

inline auto GoomStateDump::CumulativeState::GetBlockyWavyEffects() const
    -> const std::vector<uint8_t>&
{
  return m_blockyWavyEffects;
}

inline auto GoomStateDump::CumulativeState::GetImageVelocityEffects() const
    -> const std::vector<uint8_t>&
{
  return m_imageVelocityEffects;
}

inline auto GoomStateDump::CumulativeState::GetNoiseEffects() const -> const std::vector<uint8_t>&
{
  return m_noiseEffects;
}

inline auto GoomStateDump::CumulativeState::GetPlaneEffects() const -> const std::vector<uint8_t>&
{
  return m_planeEffects;
}

inline auto GoomStateDump::CumulativeState::GetRotationEffects() const
    -> const std::vector<uint8_t>&
{
  return m_rotationEffects;
}

inline auto GoomStateDump::CumulativeState::GetBufferLerps() const -> const std::vector<int32_t>&
{
  return m_bufferLerps;
}

inline auto GoomStateDump::CumulativeState::GetTanEffects() const -> const std::vector<uint8_t>&
{
  return m_tanEffects;
}

inline auto GoomStateDump::CumulativeState::GetXYLerpEffects() const -> const std::vector<uint8_t>&
{
  return m_xyLerpEffects;
}

inline auto GoomStateDump::CumulativeState::GetTimesSinceLastGoom() const
    -> const std::vector<uint32_t>&
{
  return m_timesSinceLastGoom;
}

inline auto GoomStateDump::CumulativeState::GetTimesSinceLastBigGoom() const
    -> const std::vector<uint32_t>&
{
  return m_timesSinceLastBigGoom;
}

inline auto GoomStateDump::CumulativeState::GetTotalGoomsInCurrentCycle() const
    -> const std::vector<uint32_t>&
{
  return m_totalGoomsInCurrentCycle;
}

inline auto GoomStateDump::CumulativeState::GetGoomPowers() const -> const std::vector<float>&
{
  return m_goomPowers;
}

inline auto GoomStateDump::CumulativeState::GetGoomVolumes() const -> const std::vector<float>&
{
  return m_goomVolumes;
}

} // namespace GOOM::CONTROL

#endif // DO_GOOM_STATE_DUMP
