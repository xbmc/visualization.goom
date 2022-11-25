#include "tentacles_fx.h"

//#undef NO_LOGGING

#include "color/color_maps.h"
#include "color/random_color_maps.h"
#include "draw/goom_draw.h"
#include "fx_helper.h"
#include "goom_config.h"
#include "goom_plugin_info.h"
#include "logging.h"
#include "spimpl.h"
#include "tentacles/circles_tentacle_layout.h"
#include "tentacles/tentacle_driver.h"
#include "utils/enum_utils.h"
#include "utils/math/goom_rand_base.h"
#include "utils/math/misc.h"
#include "utils/timer.h"

#include <array>
#include <memory>
#include <vector>

namespace GOOM::VISUAL_FX
{

using COLOR::IColorMap;
using COLOR::RandomColorMaps;
using DRAW::IGoomDraw;
using DRAW::MultiplePixels;
using TENTACLES::CirclesTentacleLayout;
using TENTACLES::TentacleDriver;
using UTILS::Logging; // NOLINT(misc-unused-using-decls)
using UTILS::NUM;
using UTILS::Timer;
using UTILS::MATH::IGoomRand;
using UTILS::MATH::Weights;

class TentaclesFx::TentaclesImpl
{
public:
  explicit TentaclesImpl(const FxHelper& fxHelper);

  [[nodiscard]] auto GetCurrentColorMapsNames() const noexcept -> std::vector<std::string>;
  auto SetWeightedColorMaps(const WeightedColorMaps& weightedColorMaps) noexcept -> void;

  auto SetZoomMidpoint(const Point2dInt& zoomMidpoint) noexcept -> void;

  auto Start() -> void;
  auto Resume() -> void;

  auto Update() -> void;

private:
  IGoomDraw& m_draw;
  const PluginInfo& m_goomInfo;
  const IGoomRand& m_goomRand;

  enum class Drivers
  {
    NUM0 = 0,
    NUM1,
    NUM2,
    NUM3,
    _num // unused, and marks the enum end
  };
  static constexpr size_t NUM_TENTACLE_DRIVERS = NUM<Drivers>;
  const Weights<Drivers> m_driverWeights;
  const std::array<CirclesTentacleLayout, NUM_TENTACLE_DRIVERS> m_tentacleLayouts;
  std::vector<TentacleDriver> m_tentacleDrivers{GetTentacleDrivers()};
  [[nodiscard]] auto GetTentacleDrivers() const -> std::vector<TentacleDriver>;
  TentacleDriver* m_currentTentacleDriver{GetNextDriver()};
  [[nodiscard]] auto GetNextDriver() -> TentacleDriver*;

  std::shared_ptr<const RandomColorMaps> m_weightedDominantMainColorMaps{};
  std::shared_ptr<const RandomColorMaps> m_weightedDominantLowColorMaps{};
  std::shared_ptr<const IColorMap> m_dominantMainColorMap{};
  std::shared_ptr<const IColorMap> m_dominantLowColorMap{};
  auto ChangeDominantColor() -> void;

  static constexpr uint32_t MAX_TIME_FOR_DOMINANT_COLOR = 100;
  Timer m_timeWithThisDominantColor{MAX_TIME_FOR_DOMINANT_COLOR};
  auto UpdateTimers() -> void;

  auto RefreshTentacles() -> void;
  auto DoTentaclesUpdate() -> void;
  auto UpdateTentacleWaveFrequency() -> void;
};

TentaclesFx::TentaclesFx(const FxHelper& fxHelper) noexcept
  : m_pimpl{spimpl::make_unique_impl<TentaclesImpl>(fxHelper)}
{
}

auto TentaclesFx::GetFxName() const noexcept -> std::string
{
  return "Tentacles FX";
}

auto TentaclesFx::GetCurrentColorMapsNames() const noexcept -> std::vector<std::string>
{
  return m_pimpl->GetCurrentColorMapsNames();
}

auto TentaclesFx::SetWeightedColorMaps(const WeightedColorMaps& weightedColorMaps) noexcept -> void
{
  m_pimpl->SetWeightedColorMaps(weightedColorMaps);
}

auto TentaclesFx::SetZoomMidpoint(const Point2dInt& zoomMidpoint) noexcept -> void
{
  m_pimpl->SetZoomMidpoint(zoomMidpoint);
}

auto TentaclesFx::Start() noexcept -> void
{
  m_pimpl->Start();
}

auto TentaclesFx::Finish() noexcept -> void
{
  // nothing to do
}

auto TentaclesFx::Resume() noexcept -> void
{
  m_pimpl->Resume();
}

auto TentaclesFx::Suspend() noexcept -> void
{
  // nothing to do
}

auto TentaclesFx::ApplyMultiple() noexcept -> void
{
  m_pimpl->Update();
}

static constexpr auto LAYOUT0_START_RADIUS = 80.0F;
static constexpr auto LAYOUT1_START_RADIUS = 80.0F;
static constexpr auto LAYOUT2_START_RADIUS = 100.0F;
static constexpr auto LAYOUT3_START_RADIUS = 110.0F;

static constexpr auto LAYOUT0_END_RADIUS = 20.0F;
static constexpr auto LAYOUT1_END_RADIUS = 20.0F;
static constexpr auto LAYOUT2_END_RADIUS = 20.0F;
static constexpr auto LAYOUT3_END_RADIUS = 20.0F;

static constexpr auto LAYOUT0_NUM_TENTACLES = 40U;
static constexpr auto LAYOUT1_NUM_TENTACLES = 50U;
static constexpr auto LAYOUT2_NUM_TENTACLES = 70U;
static constexpr auto LAYOUT3_NUM_TENTACLES = 150U;

static constexpr auto DRIVERS_NUM0_WEIGHT = 50.0F;
static constexpr auto DRIVERS_NUM1_WEIGHT = 30.0F;
static constexpr auto DRIVERS_NUM2_WEIGHT = 10.0F;
static constexpr auto DRIVERS_NUM3_WEIGHT = 05.0F;

TentaclesFx::TentaclesImpl::TentaclesImpl(const FxHelper& fxHelper)
  : m_draw{fxHelper.GetDraw()},
    m_goomInfo{fxHelper.GetGoomInfo()},
    m_goomRand{fxHelper.GetGoomRand()},
    m_driverWeights{
      m_goomRand,
      {
          {Drivers::NUM0, DRIVERS_NUM0_WEIGHT},
          {Drivers::NUM1, DRIVERS_NUM1_WEIGHT},
          {Drivers::NUM2, DRIVERS_NUM2_WEIGHT},
          {Drivers::NUM3, DRIVERS_NUM3_WEIGHT},
      }},
    m_tentacleLayouts{{
        {LAYOUT0_START_RADIUS, LAYOUT0_END_RADIUS, LAYOUT0_NUM_TENTACLES},
        {LAYOUT1_START_RADIUS, LAYOUT1_END_RADIUS, LAYOUT1_NUM_TENTACLES},
        {LAYOUT2_START_RADIUS, LAYOUT2_END_RADIUS, LAYOUT2_NUM_TENTACLES},
        {LAYOUT3_START_RADIUS, LAYOUT3_END_RADIUS, LAYOUT3_NUM_TENTACLES},
    }}
{
  Expects(NUM_TENTACLE_DRIVERS == m_driverWeights.GetNumElements());
  Ensures(m_currentTentacleDriver != nullptr);
}

inline auto TentaclesFx::TentaclesImpl::Start() -> void
{
  m_timeWithThisDominantColor.SetToFinished();

  RefreshTentacles();
}

inline auto TentaclesFx::TentaclesImpl::Resume() -> void
{
  if (static constexpr auto PROB_NEW_DRIVER = 0.5F; m_goomRand.ProbabilityOf(PROB_NEW_DRIVER))
  {
    m_currentTentacleDriver = GetNextDriver();
  }

  m_timeWithThisDominantColor.SetToFinished();

  RefreshTentacles();
}

auto TentaclesFx::TentaclesImpl::GetTentacleDrivers() const -> std::vector<TentacleDriver>
{
  auto tentacleDrivers = std::vector<TentacleDriver>{};
  for (auto i = 0U; i < NUM_TENTACLE_DRIVERS; ++i)
  {
    tentacleDrivers.emplace_back(m_draw, m_goomRand, m_tentacleLayouts.at(i));
  }

  for (auto i = 0U; i < NUM_TENTACLE_DRIVERS; ++i)
  {
    tentacleDrivers[i].StartIterating();
  }

  return tentacleDrivers;
}

inline auto TentaclesFx::TentaclesImpl::GetNextDriver() -> TentacleDriver*
{
  const auto driverIndex = static_cast<size_t>(m_driverWeights.GetRandomWeighted());
  return &m_tentacleDrivers[driverIndex];
}

inline auto TentaclesFx::TentaclesImpl::RefreshTentacles() -> void
{
  Expects(m_currentTentacleDriver != nullptr);

  ChangeDominantColor();

  m_currentTentacleDriver->ChangeTentacleColorMaps();
}

auto TentaclesFx::TentaclesImpl::GetCurrentColorMapsNames() const noexcept
    -> std::vector<std::string>
{
  return {m_weightedDominantMainColorMaps->GetColorMapsName(),
          m_weightedDominantLowColorMaps->GetColorMapsName()};
}

auto TentaclesFx::TentaclesImpl::SetWeightedColorMaps(
    const WeightedColorMaps& weightedColorMaps) noexcept -> void
{
  Expects(weightedColorMaps.mainColorMaps != nullptr);
  Expects(weightedColorMaps.lowColorMaps != nullptr);

  if (weightedColorMaps.id == NORMAL_COLOR_TYPE)
  {
    std::for_each(begin(m_tentacleDrivers),
                  end(m_tentacleDrivers),
                  [&weightedColorMaps](auto& driver)
                  { driver.SetWeightedColorMaps(weightedColorMaps); });
  }
  else if (weightedColorMaps.id == DOMINANT_COLOR_TYPE)
  {
    m_weightedDominantMainColorMaps = weightedColorMaps.mainColorMaps;
    m_dominantMainColorMap =
        m_weightedDominantMainColorMaps->GetRandomColorMapPtr(RandomColorMaps::ALL_COLOR_MAP_TYPES);

    m_weightedDominantLowColorMaps = weightedColorMaps.lowColorMaps;
    m_dominantLowColorMap =
        m_weightedDominantLowColorMaps->GetRandomColorMapPtr(RandomColorMaps::ALL_COLOR_MAP_TYPES);
  }
  else
  {
    FailFast();
  }
}

inline auto TentaclesFx::TentaclesImpl::SetZoomMidpoint(const Point2dInt& zoomMidpoint) noexcept
    -> void
{
  std::for_each(begin(m_tentacleDrivers),
                end(m_tentacleDrivers),
                [&zoomMidpoint](auto& driver)
                { driver.SetAllTentaclesEndCentrePos(zoomMidpoint); });
}

inline auto TentaclesFx::TentaclesImpl::ChangeDominantColor() -> void
{
  if (!m_timeWithThisDominantColor.Finished())
  {
    return;
  }

  m_timeWithThisDominantColor.ResetToZero();

  m_currentTentacleDriver->SetDominantColorMaps(m_dominantMainColorMap, m_dominantLowColorMap);
}

inline auto TentaclesFx::TentaclesImpl::Update() -> void
{
  UpdateTimers();

  DoTentaclesUpdate();
}

inline auto TentaclesFx::TentaclesImpl::UpdateTimers() -> void
{
  m_timeWithThisDominantColor.Increment();
}

inline auto TentaclesFx::TentaclesImpl::DoTentaclesUpdate() -> void
{
  if (0 == m_goomInfo.GetSoundEvents().GetTimeSinceLastGoom())
  {
    ChangeDominantColor();
  }

  UpdateTentacleWaveFrequency();

  m_currentTentacleDriver->Update();
}

inline auto TentaclesFx::TentaclesImpl::UpdateTentacleWaveFrequency() -> void
{
  // Higher sound acceleration increases tentacle wave frequency.
  Expects(m_currentTentacleDriver);
  const auto tentacleWaveFreqMultiplier =
      m_goomInfo.GetSoundEvents().GetSoundInfo().GetAcceleration() <
              SoundInfo::ACCELERATION_MIDPOINT
          ? 0.95F
          : (1.0F / (1.1F - m_goomInfo.GetSoundEvents().GetSoundInfo().GetAcceleration()));
  m_currentTentacleDriver->MultiplyIterZeroYValWaveFreq(tentacleWaveFreqMultiplier);
}

} // namespace GOOM::VISUAL_FX
