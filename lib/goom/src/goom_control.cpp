/**
* file: goom_control.c (onetime goom_core.c)
 * author: Jean-Christophe Hoelt (which is not so proud of it)
 *
 * Contains the core of goom's work.
 *
 * (c)2000-2003, by iOS-software.
 *
 *	- converted to C++14 2021-02-01 (glk)
 *
 */

//#include <valgrind/callgrind.h>

#include "goom_control.h"

#include "control/goom_events.h"
#include "control/goom_image_buffers.h"
#include "control/goom_lock.h"
#include "control/goom_states.h"
#include "convolve_fx.h"
#include "draw/goom_draw_buffer.h"
#include "draw/text_draw.h"
#include "filter_data.h"
#include "filters.h"
#include "filters/filter_control.h"
#include "filters/filter_zoom_vector.h"
#include "flying_stars_fx.h"
#include "goom_dots_fx.h"
#include "goom_graphic.h"
#include "goom_plugin_info.h"
#include "goom_stats.h"
#include "goom_visual_fx.h"
#include "goomutils/colormaps.h"
#include "goomutils/colorutils.h"
#include "goomutils/enumutils.h"
#include "goomutils/goomrand.h"
#include "goomutils/logging_control.h"
#undef NO_LOGGING
#include "goomutils/graphics/small_image_bitmaps.h"
#include "goomutils/logging.h"
#include "goomutils/parallel_utils.h"
#include "goomutils/random_colormaps.h"
#include "goomutils/strutils.h"
#include "goomutils/timer.h"
#include "ifs_dancers_fx.h"
#include "image_fx.h"
#include "lines_fx.h"
#include "stats/goom_control_stats.h"
#include "tentacles_fx.h"
#include "tube_fx.h"

#include <array>
#include <cmath>
#include <cstdint>
#if __cplusplus > 201402L
#include <filesystem>
#endif
//#undef NDEBUG
#include <cassert>
#include <memory>
#include <stdexcept>
#include <string>
#include <unordered_set>
#include <utility>
#if __cplusplus > 201402L
#include <variant>
#endif
#include <vector>

//#define SHOW_STATE_TEXT_ON_SCREEN

namespace GOOM
{

using CONTROL::GoomDrawable;
using CONTROL::GoomEvents;
using CONTROL::GoomImageBuffers;
using CONTROL::GoomLock;
using CONTROL::GoomStates;
using DRAW::GoomDrawBuffer;
using DRAW::TextDraw;
using FILTERS::FilterControl;
using FILTERS::FilterZoomVector;
using UTILS::ColorMapGroup;
using UTILS::GammaCorrection;
using UTILS::GetAllSlimMaps;
using UTILS::GetAllStandardMaps;
using UTILS::GetBlueStandardMaps;
using UTILS::GetCitiesStandardMaps;
using UTILS::GetColdStandardMaps;
using UTILS::GetGreenStandardMaps;
using UTILS::GetHeatStandardMaps;
using UTILS::GetMostlySequentialSlimMaps;
using UTILS::GetMostlySequentialStandardMaps;
using UTILS::GetOrangeStandardMaps;
using UTILS::GetPastelStandardMaps;
using UTILS::GetPurpleStandardMaps;
using UTILS::GetRandInRange;
using UTILS::GetRedStandardMaps;
using UTILS::GetSeasonsStandardMaps;
using UTILS::GetSlightlyDivergingSlimMaps;
using UTILS::GetSlightlyDivergingStandardMaps;
using UTILS::GetYellowStandardMaps;
using UTILS::IColorMap;
using UTILS::Logging;
using UTILS::NUM;
using UTILS::Parallel;
using UTILS::ProbabilityOfMInN;
using UTILS::RandomColorMaps;
using UTILS::SmallImageBitmaps;
using UTILS::SplitString;
using UTILS::Timer;

// TODO: put that as variable in PluginInfo
constexpr int32_t MAX_TIME_BETWEEN_ZOOM_EFFECTS_CHANGE = 200;

using GoomEvent = GoomEvents::GoomEvent;

struct GoomMessage
{
  std::string message;
  uint32_t numberOfLinesInMessage = 0;
  uint32_t affiche = 0;
};

struct GoomVisualFx
{
  GoomVisualFx() noexcept = delete;
  explicit GoomVisualFx(Parallel& p,
                        IGoomDraw* draw,
                        const std::shared_ptr<const PluginInfo>& goomInfo) noexcept;

  std::shared_ptr<ConvolveFx> convolve_fx{};
  std::shared_ptr<ZoomFilterFx> zoomFilter_fx{};
  std::shared_ptr<FlyingStarsFx> star_fx{};
  std::shared_ptr<GoomDotsFx> goomDots_fx{};
  std::shared_ptr<IfsDancersFx> ifs_fx{};
  std::shared_ptr<TentaclesFx> tentacles_fx{};
  std::shared_ptr<ImageFx> image_fx{};
  std::shared_ptr<TubeFx> tube_fx{};

  std::vector<std::shared_ptr<IVisualFx>> list{};
  std::map<GoomDrawable, std::shared_ptr<IVisualFx>> map{};
};

GoomVisualFx::GoomVisualFx(Parallel& p,
                           IGoomDraw* const draw,
                           const std::shared_ptr<const PluginInfo>& goomInfo) noexcept
  : convolve_fx{new ConvolveFx{p, goomInfo}},
    zoomFilter_fx{new ZoomFilterFx{p, goomInfo}},
    star_fx{new FlyingStarsFx{draw, goomInfo}},
    goomDots_fx{new GoomDotsFx{draw, goomInfo}},
    ifs_fx{new IfsDancersFx{draw, goomInfo}},
    tentacles_fx{new TentaclesFx{draw, goomInfo}},
    image_fx{new ImageFx{draw, goomInfo}},
    tube_fx{new TubeFx{draw, goomInfo}},
    // clang-format off
    list{
      convolve_fx,
      zoomFilter_fx,
      star_fx,
      ifs_fx,
      goomDots_fx,
      tentacles_fx,
      image_fx,
      tube_fx,
    },
    map{
      {GoomDrawable::STARS, star_fx},
      {GoomDrawable::IFS, ifs_fx},
      {GoomDrawable::DOTS, goomDots_fx},
      {GoomDrawable::TENTACLES, tentacles_fx},
      {GoomDrawable::IMAGE, image_fx},
      {GoomDrawable::TUBE, tube_fx},
    }
// clang-format on
{
}

struct GoomData
{
  GoomLock lock{}; // pour empecher de nouveaux changements
  int32_t stopLines = 0;
  int32_t updatesSinceLastZoomEffectsChange = 0; // nombre de Cycle Depuis Dernier Changement
  // duree de la transition entre afficher les lignes ou pas
  int32_t drawLinesDuration = LinesFx::MIN_LINE_DURATION;
  int32_t lineMode = LinesFx::MIN_LINE_DURATION; // l'effet lineaire a dessiner

  static constexpr float SWITCH_MULT_AMOUNT = 29.0 / 30.0;
  float switchMult = SWITCH_MULT_AMOUNT;
  static constexpr int SWITCH_INCR_AMOUNT = 0x7f;
  int32_t switchIncr = SWITCH_INCR_AMOUNT;
  uint32_t stateSelectionBlocker = 0;
  int32_t previousZoomSpeed = Vitesse::DEFAULT_VITESSE + 1;

  static constexpr int MAX_TITLE_DISPLAY_TIME = 200;
  static constexpr int TIME_TO_SPACE_TITLE_DISPLAY = 100;
  static constexpr int TIME_TO_FADE_TITLE_DISPLAY = 50;
  int32_t timeOfTitleDisplay = 0;
  std::string title{};
};

class GoomControl::GoomControlImpl
{
public:
  GoomControlImpl(uint32_t screenWidth, uint32_t screenHeight, std::string resourcesDirectory);
  ~GoomControlImpl() noexcept;
  GoomControlImpl(const GoomControlImpl&) noexcept = delete;
  GoomControlImpl(GoomControlImpl&&) noexcept = delete;
  auto operator=(const GoomControlImpl&) noexcept -> GoomControlImpl& = delete;
  auto operator=(GoomControlImpl&&) noexcept -> GoomControlImpl& = delete;

  void Swap(GoomControl::GoomControlImpl& other) noexcept = delete;

  [[nodiscard]] auto GetResourcesDirectory() const -> const std::string&;
  void SetResourcesDirectory(const std::string& dirName);

  [[nodiscard]] auto GetScreenBuffer() const -> PixelBuffer&;
  void SetScreenBuffer(PixelBuffer& buff);
  static constexpr uint32_t FONT_SIZE = 35;
  void SetFontFile(const std::string& f);

  [[nodiscard]] auto GetScreenWidth() const -> uint32_t;
  [[nodiscard]] auto GetScreenHeight() const -> uint32_t;

  void Start();
  void Finish();

  void Update(const AudioSamples& soundData,
              float fps,
              const std::string& songTitle,
              const std::string& message);

private:
  Parallel m_parallel;
  GoomDrawBuffer m_multiBufferdraw;
  GoomDrawBuffer m_textDraw;
  TextDraw m_text;
  const std::shared_ptr<WritablePluginInfo> m_goomInfo;
  GoomImageBuffers m_imageBuffers;
  GoomVisualFx m_visualFx;
  GoomControlStats m_stats{};
  FilterZoomVector m_zoomVector;
  GoomStates m_states{};
  GoomEvents m_goomEvent{};
  uint32_t m_timeInState = 0;
  uint32_t m_timeWithFilter = 0;
  uint32_t m_cycle = 0;
  FilterControl m_filterControl;
  std::unordered_set<GoomDrawable> m_curGDrawables{};
  GoomMessage m_messageData{};
  GoomData m_goomData;
  const IColorMap* m_textColorMap{};
  Pixel m_textOutlineColor{};
  std::unique_ptr<TextDraw> m_updateMessageText{};

  std::string m_resourcesDirectory{};
  const SmallImageBitmaps m_smallBitmaps;

  bool m_singleBufferDots = true;
  static constexpr uint32_t MIN_NUM_OVEREXPOSED_UPDATES = 1000;
  static constexpr uint32_t MAX_NUM_OVEREXPOSED_UPDATES = 10000;
  Timer m_convolveAllowOverexposed{MIN_NUM_OVEREXPOSED_UPDATES};
  static constexpr uint32_t MIN_NUM_NOT_OVEREXPOSED_UPDATES = 10000;
  static constexpr uint32_t MAX_NUM_NOT_OVEREXPOSED_UPDATES = 10000;
  Timer m_convolveNotAllowOverexposed{0};

  // Line Fx
  static constexpr float INITIAL_SCREEN_HEIGHT_FRACTION_LINE1 = 0.4;
  static constexpr float INITIAL_SCREEN_HEIGHT_FRACTION_LINE2 = 0.2;
  LinesFx m_gmline1;
  LinesFx m_gmline2;

  void ChangeColorMaps();

  void ProcessAudio(const AudioSamples& soundData) const;

  // Changement d'effet de zoom !
  void ChangeZoomEffect();
  void ApplyZoom();
  void UpdateBuffers();
  void ResetDrawBuffers();
  [[nodiscard]] auto GetCurrentBuffers() const -> std::vector<PixelBuffer*>;
  void ResetDrawBuffSettings(const FXBuffSettings& settings);

  void ApplyCurrentStateToSingleBuffer();
  void ApplyCurrentStateToMultipleBuffers();
  void ApplyDotsIfRequired();
  void ApplyDotsToBothBuffersIfRequired();
  void ApplyIfsToBothBuffersIfRequired();
  void ApplyTentaclesToBothBuffersIfRequired();
  void ApplyStarsToBothBuffersIfRequired();
  void ApplyImageIfRequired();
  void ApplyTubeToBothBuffersIfRequired();

  void DoIfsRenew();

  static constexpr uint32_t NORMAL_UPDATE_LOCK_TIME = 50;
  static constexpr uint32_t REVERSE_SPEED_AND_STOP_SPEED_LOCK_TIME = 75;
  static constexpr uint32_t REVERSE_SPEED_LOCK_TIME = 100;
  static constexpr uint32_t MEGA_LENT_LOCK_TIME_INCREASE = 50;
  static constexpr uint32_t CHANGE_VITESSE_LOCK_TIME_INCREASE = 50;
  static constexpr uint32_t CHANGE_SWITCH_VALUES_LOCK_TIME = 150;
  [[nodiscard]] auto IsLocked() const -> bool;
  [[nodiscard]] auto GetLockTime() const -> uint32_t;
  void UpdateLock();
  void SetLockTime(uint32_t val);
  void IncreaseLockTime(uint32_t byAmount);

  void ChangeState();
  void DoChangeState();
  void SuspendCurrentState();
  void SetNextState();
  void ResumeCurrentState();

  void BigNormalUpdate();
  void MegaLentUpdate();

  void ChangeAllowOverexposed();
  void ChangeBlockyWavy();
  void ChangeNoise();
  void ChangeRotation();
  void ChangeSwitchValues();
  void ChangeSpeedReverse();
  void ChangeVitesse();
  void ChangeStopSpeeds();

  // on verifie qu'il ne se pas un truc interressant avec le son.
  void ChangeFilterModeIfMusicChanges();
  [[nodiscard]] auto ChangeFilterModeEventHappens() -> bool;
  void ChangeFilterMode();
  void SetNextFilterMode();
  void ChangeMilieu();

  // baisser regulierement la vitesse
  void RegularlyLowerTheSpeed();

  // arret demande
  void StopLinesRequest();
  void StopLinesIfRequested();

  // arret aleatore.. changement de mode de ligne..
  void StopRandomLineChangeMode();

  // arreter de decrémenter au bout d'un certain temps
  void StopDecrementingAfterAWhile();
  void StopDecrementing();

  // tout ceci ne sera fait qu'en cas de non-blocage
  void BigUpdateIfNotLocked();
  void BigUpdate();

  // gros frein si la musique est calme
  void BigBreakIfMusicIsCalm();
  void BigBreak();

  void DisplayLinesIfInAGoom(const AudioSamples& soundData);
  void DisplayLines(const AudioSamples& soundData);
  void ChooseGoomLine(float* param1,
                      float* param2,
                      Pixel* couleur,
                      LinesFx::LineType* mode,
                      float* amplitude,
                      int far);

  void UpdateMessage(const std::string& message);
  void DrawText(const std::string& str, int xPos, int yPos, float spacing);
  void DisplayText(const std::string& songTitle, const std::string& message, float fps);
#ifdef SHOW_STATE_TEXT_ON_SCREEN
  void DisplayStateText();
#endif
};

auto GoomControl::GetRandSeed() -> uint64_t
{
  return GOOM::UTILS::GetRandSeed();
}

void GoomControl::SetRandSeed(const uint64_t seed)
{
  LogDebug("Set goom seed = {}.", seed);
  GOOM::UTILS::SetRandSeed(seed);
}

GoomControl::GoomControl(const uint32_t resx, const uint32_t resy, std::string resourcesDirectory)
  : m_controller{new GoomControlImpl{resx, resy, resourcesDirectory}}
{
}

GoomControl::~GoomControl() noexcept = default;

auto GoomControl::GetResourcesDirectory() const -> const std::string&
{
  return m_controller->GetResourcesDirectory();
}

void GoomControl::SetResourcesDirectory(const std::string& dirName)
{
  m_controller->SetResourcesDirectory(dirName);
}

void GoomControl::SetScreenBuffer(PixelBuffer& buffer)
{
  m_controller->SetScreenBuffer(buffer);
}

void GoomControl::Start()
{
  m_controller->Start();
}

void GoomControl::Finish()
{
  m_controller->Finish();
}

void GoomControl::Update(const AudioSamples& soundData,
                         const float fps,
                         const std::string& songTitle,
                         const std::string& message)
{
  m_controller->Update(soundData, fps, songTitle, message);
}

static const Pixel RED_LINE = GetRedLineColor();
static const Pixel GREEN_LINE = GetGreenLineColor();
static const Pixel BLACK_LINE = GetBlackLineColor();

GoomControl::GoomControlImpl::GoomControlImpl(const uint32_t screenWidth,
                                              const uint32_t screenHeight,
                                              std::string resourcesDirectory)
  : m_parallel{-1}, // max cores - 1
    m_multiBufferdraw{screenWidth, screenHeight},
    m_textDraw{screenWidth, screenHeight},
    m_text{&m_textDraw},
    m_goomInfo{new WritablePluginInfo{screenWidth, screenHeight}},
    m_imageBuffers{screenWidth, screenHeight},
    m_visualFx{m_parallel, &m_multiBufferdraw,
               std::const_pointer_cast<const PluginInfo>(
                   std::dynamic_pointer_cast<PluginInfo>(m_goomInfo))},
    m_zoomVector{},
    m_filterControl{m_goomInfo},
    m_goomData{},
    m_resourcesDirectory{std::move(resourcesDirectory)},
    m_smallBitmaps{m_resourcesDirectory},
    m_gmline1{&m_multiBufferdraw,
              std::const_pointer_cast<const PluginInfo>(
                  std::dynamic_pointer_cast<PluginInfo>(m_goomInfo)),
              LinesFx::LineType::hline,
              static_cast<float>(screenHeight),
              BLACK_LINE,
              LinesFx::LineType::circle,
              INITIAL_SCREEN_HEIGHT_FRACTION_LINE1 * static_cast<float>(screenHeight),
              GREEN_LINE},
    m_gmline2{&m_multiBufferdraw,
              std::const_pointer_cast<const PluginInfo>(
                  std::dynamic_pointer_cast<PluginInfo>(m_goomInfo)),
              LinesFx::LineType::hline,
              0,
              BLACK_LINE,
              LinesFx::LineType::circle,
              INITIAL_SCREEN_HEIGHT_FRACTION_LINE2 * static_cast<float>(screenHeight),
              RED_LINE}
{
  LogDebug("Initialize goom: screenWidth = {}, screenHeight = {}.", screenWidth, screenHeight);

  ResetDrawBuffers();
}

GoomControl::GoomControlImpl::~GoomControlImpl() noexcept = default;

auto GoomControl::GoomControlImpl::GetResourcesDirectory() const -> const std::string&
{
  return m_resourcesDirectory;
}

void GoomControl::GoomControlImpl::SetResourcesDirectory(const std::string& dirName)
{
#if __cplusplus > 201402L
  if (!std::filesystem::exists(dirName))
  {
    throw std::runtime_error(std20::format("Could not find directory \"{}\".", dirName));
  }
#endif

  m_resourcesDirectory = dirName;
}

auto GoomControl::GoomControlImpl::GetScreenBuffer() const -> PixelBuffer&
{
  return m_imageBuffers.GetOutputBuff();
}

void GoomControl::GoomControlImpl::SetScreenBuffer(PixelBuffer& buffer)
{
  m_imageBuffers.SetOutputBuff(buffer);
}

void GoomControl::GoomControlImpl::SetFontFile(const std::string& filename)
{
  m_stats.SetFontFileUsed(filename);

  m_text.SetFontFile(filename);
  m_text.SetFontSize(FONT_SIZE);
  m_text.SetOutlineWidth(2);
  m_text.SetAlignment(TextDraw::TextAlignment::LEFT);
}

auto GoomControl::GoomControlImpl::GetScreenWidth() const -> uint32_t
{
  return m_goomInfo->GetScreenInfo().width;
}

auto GoomControl::GoomControlImpl::GetScreenHeight() const -> uint32_t
{
  return m_goomInfo->GetScreenInfo().height;
}

inline auto GoomControl::GoomControlImpl::ChangeFilterModeEventHappens() -> bool
{
  return m_goomEvent.Happens(GoomEvent::CHANGE_FILTER_MODE);
}

void GoomControl::GoomControlImpl::Start()
{
  if (m_resourcesDirectory.empty())
  {
    throw std::logic_error("Cannot start Goom - resource directory not set.");
  }

  ChangeColorMaps();

  SetFontFile(m_resourcesDirectory + PATH_SEP + FONTS_DIR + PATH_SEP + "verdana.ttf");

  m_timeInState = 0;
  m_timeWithFilter = 0;

  m_curGDrawables = m_states.GetCurrentDrawables();

  m_stats.Reset();
  m_stats.SetStateStartValue(m_states.GetCurrentStateIndex());
  m_stats.SetZoomFilterStartValue(m_filterControl.GetFilterSettings().mode);
  m_stats.SetSeedStartValue(GetRandSeed());

  // TODO MAKE line a visual FX
  m_gmline1.SetResourcesDirectory(m_resourcesDirectory);
  m_gmline1.SetSmallImageBitmaps(m_smallBitmaps);
  m_gmline1.Start();
  m_gmline2.SetResourcesDirectory(m_resourcesDirectory);
  m_gmline2.SetSmallImageBitmaps(m_smallBitmaps);
  m_gmline2.Start();

  m_visualFx.goomDots_fx->SetSmallImageBitmaps(m_smallBitmaps);
  m_visualFx.ifs_fx->SetSmallImageBitmaps(m_smallBitmaps);
  m_visualFx.star_fx->SetSmallImageBitmaps(m_smallBitmaps);
  m_visualFx.tube_fx->SetSmallImageBitmaps(m_smallBitmaps);

  m_filterControl.SetResourcesDirectory(m_resourcesDirectory);
  m_filterControl.Start();

  m_visualFx.convolve_fx->SetAllowOverexposed(true);
  m_convolveAllowOverexposed.ResetToZero();

  SetNextFilterMode();
  m_visualFx.zoomFilter_fx->SetInitialFilterSettings(m_filterControl.GetFilterSettings());
  m_visualFx.zoomFilter_fx->SetZoomVector(m_zoomVector);
  m_stats.DoChangeFilterMode(m_filterControl.GetFilterSettings().mode);

  for (auto& v : m_visualFx.list)
  {
    v->SetResourcesDirectory(m_resourcesDirectory);
    v->Start();
  }

  DoChangeState();
}

enum class GoomEffect
{
  DOTS0 = 0,
  DOTS1,
  DOTS2,
  DOTS3,
  DOTS4,
  LINES1,
  LINES2,
  IFS,
  STARS,
  STARS_LOW,
  TENTACLES,
  TUBE,
  TUBE_LOW,
  _NUM // unused and must be last
};

struct GoomStateColorMatch
{
  GoomEffect effect;
  std::function<auto()->std::shared_ptr<RandomColorMaps>> getColorMaps;
};
using GoomStateColorMatchedSet = std::array<GoomStateColorMatch, NUM<GoomEffect>>;
static const std::array<GoomStateColorMatchedSet, 7> GOOM_STATE_COLOR_MATCHED_SETS{{
    {{
        {GoomEffect::DOTS0, GetAllStandardMaps},
        {GoomEffect::DOTS1, GetAllStandardMaps},
        {GoomEffect::DOTS2, GetAllStandardMaps},
        {GoomEffect::DOTS3, GetAllStandardMaps},
        {GoomEffect::DOTS4, GetAllStandardMaps},
        {GoomEffect::LINES1, GetAllStandardMaps},
        {GoomEffect::LINES2, GetAllStandardMaps},
        {GoomEffect::IFS, GetAllStandardMaps},
        {GoomEffect::STARS, GetAllStandardMaps},
        {GoomEffect::STARS_LOW, GetAllStandardMaps},
        {GoomEffect::TENTACLES, GetAllStandardMaps},
        {GoomEffect::TUBE, GetAllStandardMaps},
        {GoomEffect::TUBE_LOW, GetAllStandardMaps},
    }},
    {{
        {GoomEffect::DOTS0, GetRedStandardMaps},
        {GoomEffect::DOTS1, GetBlueStandardMaps},
        {GoomEffect::DOTS2, GetGreenStandardMaps},
        {GoomEffect::DOTS3, GetYellowStandardMaps},
        {GoomEffect::DOTS4, GetSlightlyDivergingSlimMaps},
        {GoomEffect::LINES1, GetMostlySequentialStandardMaps},
        {GoomEffect::LINES2, GetSlightlyDivergingStandardMaps},
        {GoomEffect::IFS, GetSlightlyDivergingStandardMaps},
        {GoomEffect::STARS, GetMostlySequentialSlimMaps},
        {GoomEffect::STARS_LOW, GetSlightlyDivergingStandardMaps},
        {GoomEffect::TENTACLES, GetSlightlyDivergingSlimMaps},
        {GoomEffect::TUBE, GetSlightlyDivergingStandardMaps},
        {GoomEffect::TUBE_LOW, GetSlightlyDivergingSlimMaps},
    }},
    {{
        {GoomEffect::DOTS0, GetOrangeStandardMaps},
        {GoomEffect::DOTS1, GetPurpleStandardMaps},
        {GoomEffect::DOTS2, GetGreenStandardMaps},
        {GoomEffect::DOTS3, GetYellowStandardMaps},
        {GoomEffect::DOTS4, GetSlightlyDivergingSlimMaps},
        {GoomEffect::LINES1, GetSlightlyDivergingSlimMaps},
        {GoomEffect::LINES2, GetSlightlyDivergingStandardMaps},
        {GoomEffect::IFS, GetSlightlyDivergingSlimMaps},
        {GoomEffect::STARS, GetHeatStandardMaps},
        {GoomEffect::STARS_LOW, GetAllSlimMaps},
        {GoomEffect::TENTACLES, GetYellowStandardMaps},
        {GoomEffect::TUBE, GetYellowStandardMaps},
        {GoomEffect::TUBE_LOW, GetBlueStandardMaps},
    }},
    {{
        {GoomEffect::DOTS0, GetRedStandardMaps},
        {GoomEffect::DOTS1, GetBlueStandardMaps},
        {GoomEffect::DOTS2, GetOrangeStandardMaps},
        {GoomEffect::DOTS3, GetYellowStandardMaps},
        {GoomEffect::DOTS4, GetPastelStandardMaps},
        {GoomEffect::LINES1, GetAllSlimMaps},
        {GoomEffect::LINES2, GetBlueStandardMaps},
        {GoomEffect::IFS, GetColdStandardMaps},
        {GoomEffect::STARS, GetSlightlyDivergingSlimMaps},
        {GoomEffect::STARS_LOW, GetBlueStandardMaps},
        {GoomEffect::TENTACLES, GetMostlySequentialStandardMaps},
        {GoomEffect::TUBE, GetMostlySequentialStandardMaps},
        {GoomEffect::TUBE_LOW, GetHeatStandardMaps},
    }},
    {{
        {GoomEffect::DOTS0, GetRedStandardMaps},
        {GoomEffect::DOTS1, GetBlueStandardMaps},
        {GoomEffect::DOTS2, GetGreenStandardMaps},
        {GoomEffect::DOTS3, GetPurpleStandardMaps},
        {GoomEffect::DOTS4, GetSlightlyDivergingSlimMaps},
        {GoomEffect::LINES1, GetSlightlyDivergingStandardMaps},
        {GoomEffect::LINES2, GetRedStandardMaps},
        {GoomEffect::IFS, GetCitiesStandardMaps},
        {GoomEffect::STARS, GetBlueStandardMaps},
        {GoomEffect::STARS_LOW, GetMostlySequentialStandardMaps},
        {GoomEffect::TENTACLES, GetPurpleStandardMaps},
        {GoomEffect::TUBE, GetPurpleStandardMaps},
        {GoomEffect::TUBE_LOW, GetPastelStandardMaps},
    }},
    {{
        {GoomEffect::DOTS0, GetRedStandardMaps},
        {GoomEffect::DOTS1, GetBlueStandardMaps},
        {GoomEffect::DOTS2, GetGreenStandardMaps},
        {GoomEffect::DOTS3, GetYellowStandardMaps},
        {GoomEffect::DOTS4, GetSlightlyDivergingSlimMaps},
        {GoomEffect::LINES1, GetSlightlyDivergingStandardMaps},
        {GoomEffect::LINES2, GetRedStandardMaps},
        {GoomEffect::IFS, GetPastelStandardMaps},
        {GoomEffect::STARS, GetPastelStandardMaps},
        {GoomEffect::STARS_LOW, GetMostlySequentialStandardMaps},
        {GoomEffect::TENTACLES, GetSeasonsStandardMaps},
        {GoomEffect::TUBE, GetSeasonsStandardMaps},
        {GoomEffect::TUBE_LOW, GetColdStandardMaps},
    }},
    {{
        {GoomEffect::DOTS0, GetRedStandardMaps},
        {GoomEffect::DOTS1, GetBlueStandardMaps},
        {GoomEffect::DOTS2, GetGreenStandardMaps},
        {GoomEffect::DOTS3, GetYellowStandardMaps},
        {GoomEffect::DOTS4, GetHeatStandardMaps},
        {GoomEffect::LINES1, GetSlightlyDivergingStandardMaps},
        {GoomEffect::LINES2, GetRedStandardMaps},
        {GoomEffect::IFS, GetPastelStandardMaps},
        {GoomEffect::STARS, GetPastelStandardMaps},
        {GoomEffect::STARS_LOW, GetColdStandardMaps},
        {GoomEffect::TENTACLES, GetSeasonsStandardMaps},
        {GoomEffect::TUBE, GetSeasonsStandardMaps},
        {GoomEffect::TUBE_LOW, GetCitiesStandardMaps},
    }},
}};

auto GetNextColorMatchedSet() -> const GoomStateColorMatchedSet&
{
  return GOOM_STATE_COLOR_MATCHED_SETS[GetRandInRange(0U, GOOM_STATE_COLOR_MATCHED_SETS.size())];
}

void GoomControl::GoomControlImpl::ChangeColorMaps()
{
  const GoomStateColorMatchedSet& colorMatchedSet = GetNextColorMatchedSet();

  for (const auto& colorMatch : colorMatchedSet)
  {
    switch (colorMatch.effect)
    {
      case GoomEffect::DOTS0:
        m_visualFx.goomDots_fx->SetWeightedColorMaps(0, colorMatch.getColorMaps());
        break;
      case GoomEffect::DOTS1:
        m_visualFx.goomDots_fx->SetWeightedColorMaps(1, colorMatch.getColorMaps());
        break;
      case GoomEffect::DOTS2:
        m_visualFx.goomDots_fx->SetWeightedColorMaps(2, colorMatch.getColorMaps());
        break;
      case GoomEffect::DOTS3:
        m_visualFx.goomDots_fx->SetWeightedColorMaps(3, colorMatch.getColorMaps());
        break;
      case GoomEffect::DOTS4:
        m_visualFx.goomDots_fx->SetWeightedColorMaps(4, colorMatch.getColorMaps());
        break;
      case GoomEffect::IFS:
        m_visualFx.ifs_fx->SetWeightedColorMaps(colorMatch.getColorMaps());
        break;
      case GoomEffect::LINES1:
        m_gmline1.SetWeightedColorMaps(colorMatch.getColorMaps());
        break;
      case GoomEffect::LINES2:
        m_gmline2.SetWeightedColorMaps(GetAllStandardMaps());
        break;
      case GoomEffect::STARS:
        m_visualFx.star_fx->SetWeightedColorMaps(colorMatch.getColorMaps());
        break;
      case GoomEffect::STARS_LOW:
        m_visualFx.star_fx->SetWeightedLowColorMaps(colorMatch.getColorMaps());
        break;
      case GoomEffect::TENTACLES:
        m_visualFx.tentacles_fx->SetWeightedColorMaps(colorMatch.getColorMaps());
        break;
      case GoomEffect::TUBE:
        m_visualFx.tube_fx->SetWeightedColorMaps(colorMatch.getColorMaps());
        break;
      case GoomEffect::TUBE_LOW:
        m_visualFx.tube_fx->SetWeightedLowColorMaps(colorMatch.getColorMaps());
        break;
      default:
        break;
    }
  }
}

void GoomControl::GoomControlImpl::Finish()
{
  for (auto& v : m_visualFx.list)
  {
    v->Finish();
  }

  m_stats.SetStateLastValue(m_states.GetCurrentStateIndex());
  m_stats.SetSeedLastValue(GetRandSeed());
  m_stats.SetNumThreadsUsedValue(m_parallel.GetNumThreadsUsed());

  const auto log = [](const std::string& val) { LogInfo(val); };
  const GoomStats statsLogger{log};
  const GoomStats::LogStatsValueFunc logStatsValueFunc = statsLogger.GetLogStatsValueFunc();

  m_stats.Log(logStatsValueFunc);

  m_goomInfo->GetSoundInfo().Log(logStatsValueFunc);

  m_gmline1.Log(logStatsValueFunc);
  m_gmline2.Log(logStatsValueFunc);

  for (auto& v : m_visualFx.list)
  {
    v->Log(logStatsValueFunc);
  }
}

void GoomControl::GoomControlImpl::Update(const AudioSamples& soundData,
                                          const float fps,
                                          const std::string& songTitle,
                                          const std::string& message)
{
  // LogInfo("Begin");

  //  CALLGRIND_START_INSTRUMENTATION;

  m_stats.UpdateChange(m_states.GetCurrentStateIndex(), m_filterControl.GetFilterSettings().mode);

  m_timeInState++;
  m_timeWithFilter++;
  m_convolveAllowOverexposed.Increment();
  m_convolveNotAllowOverexposed.Increment();

  // Elargissement de l'intervalle d'évolution des points!
  // Calcul du deplacement des petits points ...
  // Widening of the interval of evolution of the points!
  // Calculation of the displacement of small points ...

  ProcessAudio(soundData);

  UpdateLock();

  ChangeFilterModeIfMusicChanges();
  BigUpdateIfNotLocked();
  BigBreakIfMusicIsCalm();

  RegularlyLowerTheSpeed();
  StopDecrementingAfterAWhile();
  ChangeZoomEffect();

  ApplyCurrentStateToSingleBuffer();

  ApplyZoom();

  ApplyCurrentStateToMultipleBuffers();

  // Gestion du Scope - Scope management
  StopLinesIfRequested();
  StopRandomLineChangeMode();
  DisplayLinesIfInAGoom(soundData);

  UpdateBuffers();

#ifdef SHOW_STATE_TEXT_ON_SCREEN
  DisplayStateText();
#endif
  DisplayText(songTitle, message, fps);

  m_cycle++;

  //  CALLGRIND_STOP_INSTRUMENTATION;
  //  CALLGRIND_DUMP_STATS;

  // LogInfo("End");
}

void GoomControl::GoomControlImpl::ProcessAudio(const AudioSamples& soundData) const
{
  /* ! etude du signal ... */
  m_goomInfo->ProcessSoundSample(soundData);
}

void GoomControl::GoomControlImpl::ApplyCurrentStateToSingleBuffer()
{
  // applyIfsIfRequired();
  ApplyDotsIfRequired();
}

void GoomControl::GoomControlImpl::ApplyCurrentStateToMultipleBuffers()
{
  //  LogInfo("Begin");

  ApplyDotsToBothBuffersIfRequired();
  ApplyIfsToBothBuffersIfRequired();
  ApplyTentaclesToBothBuffersIfRequired();
  ApplyStarsToBothBuffersIfRequired();
  ApplyTubeToBothBuffersIfRequired();
  //  ApplyImageIfRequired();

  //  LogInfo("End");
}

void GoomControl::GoomControlImpl::ResetDrawBuffSettings(const FXBuffSettings& settings)
{
  m_multiBufferdraw.SetBuffIntensity(settings.buffIntensity);
  m_multiBufferdraw.SetAllowOverexposed(settings.allowOverexposed);
}

void GoomControl::GoomControlImpl::UpdateBuffers()
{
  // affichage et swappage des buffers...
  m_visualFx.convolve_fx->Convolve(m_imageBuffers.GetP1(), m_imageBuffers.GetOutputBuff());

  m_imageBuffers.RotateBuffers();
  ResetDrawBuffers();

  if (m_convolveAllowOverexposed.Finished())
  {
    m_visualFx.convolve_fx->SetAllowOverexposed(false);
    m_convolveNotAllowOverexposed.SetTimeLimit(
        GetRandInRange(MIN_NUM_NOT_OVEREXPOSED_UPDATES, MAX_NUM_NOT_OVEREXPOSED_UPDATES + 1));
  }
  else if (m_convolveNotAllowOverexposed.Finished())
  {
    m_visualFx.convolve_fx->SetAllowOverexposed(true);
    m_convolveAllowOverexposed.SetTimeLimit(
        GetRandInRange(MIN_NUM_OVEREXPOSED_UPDATES, MAX_NUM_OVEREXPOSED_UPDATES + 1));
  }
}

inline void GoomControl::GoomControlImpl::ResetDrawBuffers()
{
  m_multiBufferdraw.SetBuffers(this->GetCurrentBuffers());
}

inline auto GoomControl::GoomControlImpl::GetCurrentBuffers() const -> std::vector<PixelBuffer*>
{
  return {&m_imageBuffers.GetP1(), &m_imageBuffers.GetP2()};
}

inline auto GoomControl::GoomControlImpl::IsLocked() const -> bool
{
  return m_goomData.lock.IsLocked();
}

inline auto GoomControl::GoomControlImpl::GetLockTime() const -> uint32_t
{
  return m_goomData.lock.GetLockTime();
}

inline void GoomControl::GoomControlImpl::UpdateLock()
{
  m_stats.DoLockChange();
  m_goomData.lock.Update();
}

inline void GoomControl::GoomControlImpl::SetLockTime(uint32_t val)
{
  m_stats.DoLockChange();
  m_goomData.lock.SetLockTime(val);
}

inline void GoomControl::GoomControlImpl::IncreaseLockTime(const uint32_t byAmount)
{
  m_stats.DoLockChange();
  m_goomData.lock.IncreaseLockTime(byAmount);
}

void GoomControl::GoomControlImpl::ChangeFilterModeIfMusicChanges()
{
  if ((m_goomInfo->GetSoundInfo().GetTimeSinceLastGoom() == 0) ||
      (m_goomData.updatesSinceLastZoomEffectsChange > MAX_TIME_BETWEEN_ZOOM_EFFECTS_CHANGE))
  {
    LogDebug("Try to change the filter mode.");
    if (ChangeFilterModeEventHappens())
    {
      ChangeFilterMode();
    }
  }
  LogDebug("sound GetTimeSinceLastGoom() = {}", m_goomInfo->GetSoundInfo().GetTimeSinceLastGoom());
}

void GoomControl::GoomControlImpl::ChangeFilterMode()
{
  m_stats.DoChangeFilterMode();

  SetNextFilterMode();

  m_stats.DoChangeFilterMode(m_filterControl.GetFilterSettings().mode);

  DoIfsRenew();
}

void GoomControl::GoomControlImpl::SetNextFilterMode()
{
  m_filterControl.SetRandomFilterSettings();
  m_filterControl.ChangeMilieu();
  m_curGDrawables = m_states.GetCurrentDrawables();
}

void GoomControl::GoomControlImpl::ChangeState()
{
  m_stats.DoStateChangeRequest();

  if (m_goomData.stateSelectionBlocker)
  {
    m_goomData.stateSelectionBlocker--;
  }
  else if (m_goomEvent.Happens(GoomEvent::CHANGE_STATE))
  {
    m_goomData.stateSelectionBlocker = 3;
    DoChangeState();
  }
}

void GoomControl::GoomControlImpl::DoChangeState()
{
  m_stats.DoStateChange(m_timeInState);

  const auto oldGDrawables = m_states.GetCurrentDrawables();

  SuspendCurrentState();
  SetNextState();
  ResumeCurrentState();

  m_stats.DoStateChange(m_states.GetCurrentStateIndex(), m_timeInState);

  m_curGDrawables = m_states.GetCurrentDrawables();
  m_timeInState = 0;

  ChangeColorMaps();

  if (m_states.IsCurrentlyDrawable(GoomDrawable::IFS))
  {
#if __cplusplus <= 201402L
    if (oldGDrawables.find(GoomDrawable::IFS) == oldGDrawables.end())
#else
    if (!oldGDrawables.contains(GoomDrawable::IFS))
#endif
    {
      m_visualFx.ifs_fx->Init();
    }
    else if (m_goomEvent.Happens(GoomEvent::IFS_RENEW))
    {
      DoIfsRenew();
    }
    m_visualFx.ifs_fx->UpdateIncr();
  }

  if (!m_states.IsCurrentlyDrawable(GoomDrawable::SCOPE))
  {
    m_goomData.stopLines = 0xf000 & 5;
  }
  if (!m_states.IsCurrentlyDrawable(GoomDrawable::FAR_SCOPE))
  {
    m_goomData.stopLines = 0;
    m_goomData.lineMode = m_goomData.drawLinesDuration;
  }
}

void GoomControl::GoomControlImpl::ResumeCurrentState()
{
  for (const auto& drawable : m_states.GetCurrentDrawables())
  {
    if (m_visualFx.map.find(drawable) == m_visualFx.map.end())
    {
      continue;
    }
    m_visualFx.map.at(drawable)->Resume();
  }
}

void GoomControl::GoomControlImpl::SuspendCurrentState()
{
  for (const auto& drawable : m_states.GetCurrentDrawables())
  {
    if (m_visualFx.map.find(drawable) == m_visualFx.map.end())
    {
      continue;
    }
    m_visualFx.map.at(drawable)->Suspend();
  }
}

void GoomControl::GoomControlImpl::SetNextState()
{
  constexpr size_t MAX_TRIES = 10;
  const size_t oldStateIndex = m_states.GetCurrentStateIndex();

  for (size_t numTry = 0; numTry < MAX_TRIES; numTry++)
  {
    m_states.DoRandomStateChange();
    // Pick a different state if possible
    if (oldStateIndex != m_states.GetCurrentStateIndex())
    {
      break;
    }
  }
}

void GoomControl::GoomControlImpl::BigBreakIfMusicIsCalm()
{
  constexpr float CALM_SPEED = 0.01;
  constexpr uint32_t CALM_CYCLES = 16;

  if ((m_goomInfo->GetSoundInfo().GetSpeed() < CALM_SPEED) &&
      (m_filterControl.GetVitesseSetting().GetVitesse() < (Vitesse::STOP_SPEED - 4)) &&
      (m_cycle % CALM_CYCLES == 0))
  {
    BigBreak();
  }
}

void GoomControl::GoomControlImpl::BigBreak()
{
  m_stats.DoBigBreak();

  m_filterControl.GetVitesseSetting().GoSlowerBy(3);

  ChangeColorMaps();
}

void GoomControl::GoomControlImpl::BigUpdateIfNotLocked()
{
  if (!IsLocked())
  {
    BigUpdate();
  }
}

void GoomControl::GoomControlImpl::BigUpdate()
{
  m_stats.DoBigUpdate();

  // Reperage de goom (acceleration forte de l'acceleration du volume).
  // Coup de boost de la vitesse si besoin.
  // Goom tracking (strong acceleration of volume acceleration).
  // Speed boost if needed.
  if (m_goomInfo->GetSoundInfo().GetTimeSinceLastGoom() == 0)
  {
    BigNormalUpdate();
  }

  // mode mega-lent
  if (m_goomEvent.Happens(GoomEvent::CHANGE_TO_MEGA_LENT_MODE))
  {
    MegaLentUpdate();
  }
}

void GoomControl::GoomControlImpl::BigNormalUpdate()
{
  m_stats.DoBigNormalUpdate();

  SetLockTime(NORMAL_UPDATE_LOCK_TIME);

  ChangeState();
  ChangeSpeedReverse();
  ChangeStopSpeeds();
  ChangeRotation();
  ChangeMilieu();
  ChangeNoise();
  ChangeBlockyWavy();
  ChangeAllowOverexposed();
  ChangeVitesse();
  ChangeSwitchValues();

  m_singleBufferDots = ProbabilityOfMInN(1, 20);
}

void GoomControl::GoomControlImpl::MegaLentUpdate()
{
  m_stats.DoMegaLentChange();

  IncreaseLockTime(MEGA_LENT_LOCK_TIME_INCREASE);

  m_filterControl.GetVitesseSetting().SetVitesse(Vitesse::STOP_SPEED - 1);
  m_goomData.switchIncr = GoomData::SWITCH_INCR_AMOUNT;
  m_goomData.switchMult = 1.0F;
}

void GoomControl::GoomControlImpl::ChangeMilieu()
{
  m_stats.DoChangeMilieu();
  m_filterControl.ChangeMilieu();
}

void GoomControl::GoomControlImpl::ChangeVitesse()
{
  const auto goFasterVal = static_cast<int32_t>(
      std::lround(3.5F * std::log10(1.0F + 500.0F * m_goomInfo->GetSoundInfo().GetSpeed())));
  const int32_t newVitesse = Vitesse::STOP_SPEED - goFasterVal;
  const int32_t oldVitesse = m_filterControl.GetVitesseSetting().GetVitesse();

  if (newVitesse >= oldVitesse)
  {
    return;
  }

  m_stats.DoChangeVitesse();

  constexpr uint32_t VITESSE_CYCLES = 3;
  constexpr int32_t FAST_SPEED = Vitesse::STOP_SPEED - 6;
  constexpr int32_t FASTER_SPEED = Vitesse::STOP_SPEED - 7;
  constexpr int32_t SLOW_SPEED = Vitesse::STOP_SPEED - 1;
  constexpr float OLD_TO_NEW_MIX = 0.4;

  // on accelere
  if (((newVitesse < FASTER_SPEED) && (oldVitesse < FAST_SPEED) &&
       (m_cycle % VITESSE_CYCLES == 0)) ||
      m_goomEvent.Happens(GoomEvent::FILTER_CHANGE_VITESSE_AND_TOGGLE_REVERSE))
  {
    m_filterControl.GetVitesseSetting().SetVitesse(SLOW_SPEED);
    m_filterControl.GetVitesseSetting().ToggleReverseVitesse();
  }
  else
  {
    m_filterControl.GetVitesseSetting().SetVitesse(static_cast<int32_t>(std::lround(stdnew::lerp(
        static_cast<float>(oldVitesse), static_cast<float>(newVitesse), OLD_TO_NEW_MIX))));
  }

  IncreaseLockTime(CHANGE_VITESSE_LOCK_TIME_INCREASE);
}

void GoomControl::GoomControlImpl::ChangeSpeedReverse()
{
  // Retablir le zoom avant.
  // Restore zoom in.

  constexpr uint32_t REVERSE_VITESSE_CYCLES = 13;
  constexpr int32_t SLOW_SPEED = Vitesse::STOP_SPEED - 2;

  if ((m_filterControl.GetVitesseSetting().GetReverseVitesse()) &&
      (m_cycle % REVERSE_VITESSE_CYCLES != 0) &&
      m_goomEvent.Happens(GoomEvent::FILTER_REVERSE_OFF_AND_STOP_SPEED))
  {
    m_stats.DoChangeReverseSpeedOff();
    m_filterControl.GetVitesseSetting().SetReverseVitesse(false);
    m_filterControl.GetVitesseSetting().SetVitesse(SLOW_SPEED);
    SetLockTime(REVERSE_SPEED_AND_STOP_SPEED_LOCK_TIME);
  }
  if (m_goomEvent.Happens(GoomEvent::FILTER_REVERSE_ON))
  {
    m_stats.DoChangeReverseSpeedOn();
    m_filterControl.GetVitesseSetting().SetReverseVitesse(true);
    SetLockTime(REVERSE_SPEED_LOCK_TIME);
  }
}

void GoomControl::GoomControlImpl::ChangeStopSpeeds()
{
  if (m_goomEvent.Happens(GoomEvent::FILTER_VITESSE_STOP_SPEED_MINUS1))
  {
    m_stats.DoReduceStopSpeed();
    constexpr int32_t SLOW_SPEED = Vitesse::STOP_SPEED - 1;
    m_filterControl.GetVitesseSetting().SetVitesse(SLOW_SPEED);
  }
  if (m_goomEvent.Happens(GoomEvent::FILTER_VITESSE_STOP_SPEED))
  {
    m_stats.DoIncreaseStopSpeed();
    m_filterControl.GetVitesseSetting().SetVitesse(Vitesse::STOP_SPEED);
  }
}

void GoomControl::GoomControlImpl::ChangeSwitchValues()
{
  if (GetLockTime() > CHANGE_SWITCH_VALUES_LOCK_TIME)
  {
    m_stats.DoChangeSwitchValues();
    m_goomData.switchIncr = GoomData::SWITCH_INCR_AMOUNT;
    m_goomData.switchMult = 1.0F;
  }
}

void GoomControl::GoomControlImpl::ChangeNoise()
{
  if (m_goomEvent.Happens(GoomEvent::TURN_OFF_NOISE))
  {
    m_stats.DoTurnOffNoise();
    m_filterControl.SetNoisifySetting(false);
  }
  else
  {
    m_stats.DoNoise();
    m_filterControl.SetNoisifySetting(true);
    m_filterControl.SetNoiseFactorSetting(1.0);
  }
}

void GoomControl::GoomControlImpl::ChangeRotation()
{
  if (m_goomEvent.Happens(GoomEvent::FILTER_STOP_ROTATION))
  {
    m_stats.DoStopRotation();
    m_filterControl.SetRotateSetting(0.0F);
  }
  else if (m_goomEvent.Happens(GoomEvent::FILTER_DECREASE_ROTATION))
  {
    m_stats.DoDecreaseRotation();
    constexpr float ROTATE_SLOWER_FACTOR = 0.9;
    m_filterControl.MultiplyRotateSetting(ROTATE_SLOWER_FACTOR);
  }
  else if (m_goomEvent.Happens(GoomEvent::FILTER_INCREASE_ROTATION))
  {
    m_stats.DoIncreaseRotation();
    constexpr float ROTATE_FASTER_FACTOR = 1.1;
    m_filterControl.MultiplyRotateSetting(ROTATE_FASTER_FACTOR);
  }
  else if (m_goomEvent.Happens(GoomEvent::FILTER_TOGGLE_ROTATION))
  {
    m_stats.DoToggleRotation();
    m_filterControl.ToggleRotateSetting();
  }
}

void GoomControl::GoomControlImpl::ChangeBlockyWavy()
{
  if (!m_goomEvent.Happens(GoomEvent::CHANGE_BLOCKY_WAVY_TO_ON))
  {
    m_stats.DoBlockyWavyOff();
    m_filterControl.SetBlockyWavySetting(false);
  }
  else
  {
    m_stats.DoBlockyWavyOn();
    m_filterControl.SetBlockyWavySetting(true);
  }
}

void GoomControl::GoomControlImpl::ChangeAllowOverexposed()
{
  constexpr float HALF_INTENSITY = 0.5;

  if (!m_goomEvent.Happens(GoomEvent::CHANGE_ZOOM_FILTER_ALLOW_OVEREXPOSED_TO_ON))
  {
    m_stats.DoZoomFilterAllowOverexposedOff();
    m_visualFx.zoomFilter_fx->SetBuffSettings(
        {/*.buffIntensity = */ HALF_INTENSITY, /*.allowOverexposed = */ false});
  }
  else
  {
    m_stats.DoZoomFilterAllowOverexposedOn();
    m_visualFx.zoomFilter_fx->SetBuffSettings(
        {/*.buffIntensity = */ HALF_INTENSITY, /*.allowOverexposed = */ true});
  }
}

/* Changement d'effet de zoom !
 */
void GoomControl::GoomControlImpl::ChangeZoomEffect()
{
  ChangeBlockyWavy();
  ChangeAllowOverexposed();

  if (!m_filterControl.HaveSettingsChangedSinceMark())
  {
    if (m_goomData.updatesSinceLastZoomEffectsChange > MAX_TIME_BETWEEN_ZOOM_EFFECTS_CHANGE)
    {
      m_goomData.updatesSinceLastZoomEffectsChange = 0;

      ChangeRotation();
      DoIfsRenew();
    }
    else
    {
      m_goomData.updatesSinceLastZoomEffectsChange++;
    }
  }
  else
  {
    m_goomData.updatesSinceLastZoomEffectsChange = 0;
    m_goomData.switchIncr = GoomData::SWITCH_INCR_AMOUNT;

    int diff = m_filterControl.GetVitesseSetting().GetVitesse() - m_goomData.previousZoomSpeed;
    if (diff < 0)
    {
      diff = -diff;
    }

    if (diff > 2)
    {
      m_goomData.switchIncr *= (diff + 2) / 2;
    }
    m_goomData.previousZoomSpeed = m_filterControl.GetVitesseSetting().GetVitesse();
    m_goomData.switchMult = 1.0F;

    if (m_goomInfo->GetSoundInfo().GetTimeSinceLastGoom() == 0 &&
        m_goomInfo->GetSoundInfo().GetTotalGoomsInCurrentCycle() < 2)
    {
      m_goomData.switchIncr = 0;
      m_goomData.switchMult = GoomData::SWITCH_MULT_AMOUNT;

      ChangeRotation();
      DoIfsRenew();
    }
  }
}

void GoomControl::GoomControlImpl::StopDecrementingAfterAWhile()
{
  if (m_cycle % 101 == 0)
  {
    StopDecrementing();
  }
}

void GoomControl::GoomControlImpl::StopDecrementing()
{
  // TODO What used to be here???
}

void GoomControl::GoomControlImpl::RegularlyLowerTheSpeed()
{
  constexpr uint32_t LOWER_SPEED_CYCLES = 73;
  constexpr int32_t FAST_SPEED = Vitesse::STOP_SPEED - 5;

  if ((m_cycle % LOWER_SPEED_CYCLES == 0) &&
      (m_filterControl.GetVitesseSetting().GetVitesse() < FAST_SPEED))
  {
    m_stats.DoLowerVitesse();
    m_filterControl.GetVitesseSetting().GoSlowerBy(1);
  }
}

void GoomControl::GoomControlImpl::ApplyZoom()
{
  if (m_filterControl.HaveSettingsChangedSinceMark())
  {
    if (m_filterControl.GetFilterSettings().mode !=
        m_visualFx.zoomFilter_fx->GetFilterSettings().mode)
    {
      m_stats.DoApplyChangeFilterSettings(m_timeWithFilter);
      m_timeWithFilter = 0;
    }
    m_visualFx.zoomFilter_fx->ChangeFilterSettings(m_filterControl.GetFilterSettings());
    m_filterControl.ClearUnchangedMark();
  }

  uint32_t numClipped = 0;
  m_visualFx.zoomFilter_fx->ZoomFilterFastRgb(m_imageBuffers.GetP1(), m_imageBuffers.GetP2(),
                                              m_goomData.switchIncr, m_goomData.switchMult,
                                              numClipped);

  m_stats.SetLastNumClipped(numClipped);
  constexpr uint32_t TOO_MANY_CLIPPED_DIVISOR = 100;
  if (numClipped > m_goomInfo->GetScreenInfo().size / TOO_MANY_CLIPPED_DIVISOR)
  {
    m_stats.TooManyClipped();
    m_goomData.switchIncr = -m_goomData.switchIncr;
    m_goomData.switchMult = 1.0F;
  }

  if (m_filterControl.GetFilterSettings().noisify)
  {
    constexpr float REDUCING_FACTOR = 0.94;
    const float reducedNoiseFactor =
        m_filterControl.GetFilterSettings().noiseFactor * REDUCING_FACTOR;
    m_filterControl.SetNoiseFactorSetting(reducedNoiseFactor);
  }
}

void GoomControl::GoomControlImpl::ApplyDotsIfRequired()
{
  // LogInfo("Begin");

#if __cplusplus <= 201402L
  if (m_curGDrawables.find(GoomDrawable::DOTS) == m_curGDrawables.end())
#else
  if (!m_curGDrawables.contains(GoomDrawable::DOTS))
#endif
  {
    return;
  }

  if (!m_singleBufferDots)
  {
    return;
  }

  m_stats.DoDots();
  ResetDrawBuffSettings(m_states.GetCurrentBuffSettings(GoomDrawable::DOTS));
  m_visualFx.goomDots_fx->ApplySingle();

  // LogInfo("End");
}

void GoomControl::GoomControlImpl::ApplyDotsToBothBuffersIfRequired()
{
  // LogInfo("Begin");

#if __cplusplus <= 201402L
  if (m_curGDrawables.find(GoomDrawable::DOTS) == m_curGDrawables.end())
#else
  if (!m_curGDrawables.contains(GoomDrawable::DOTS))
#endif
  {
    return;
  }

  if (m_singleBufferDots)
  {
    return;
  }

  m_stats.DoDots();
  ResetDrawBuffSettings(m_states.GetCurrentBuffSettings(GoomDrawable::DOTS));
  m_visualFx.goomDots_fx->ApplyMultiple();

  // LogInfo("End");
}

void GoomControl::GoomControlImpl::ApplyIfsToBothBuffersIfRequired()
{
  // LogInfo("Begin");

#if __cplusplus <= 201402L
  if (m_curGDrawables.find(GoomDrawable::IFS) == m_curGDrawables.end())
#else
  if (!m_curGDrawables.contains(GoomDrawable::IFS))
#endif
  {
    m_visualFx.ifs_fx->ApplyNoDraw();
    return;
  }

  m_stats.DoIfs();
  ResetDrawBuffSettings(m_states.GetCurrentBuffSettings(GoomDrawable::IFS));
  m_visualFx.ifs_fx->ApplyMultiple();

  // LogInfo("End");
}

void GoomControl::GoomControlImpl::DoIfsRenew()
{
  m_visualFx.ifs_fx->Renew();
  m_stats.DoIfsRenew();
}

void GoomControl::GoomControlImpl::ApplyTentaclesToBothBuffersIfRequired()
{
  //  LogInfo("Begin");

#if __cplusplus <= 201402L
  if (m_curGDrawables.find(GoomDrawable::TENTACLES) == m_curGDrawables.end())
#else
  if (!m_curGDrawables.contains(GoomDrawable::TENTACLES))
#endif
  {
    m_visualFx.tentacles_fx->ApplyNoDraw();
    return;
  }

  m_stats.DoTentacles();
  ResetDrawBuffSettings(m_states.GetCurrentBuffSettings(GoomDrawable::TENTACLES));
  m_visualFx.tentacles_fx->ApplyMultiple();

  //  LogInfo("End");
}

void GoomControl::GoomControlImpl::ApplyTubeToBothBuffersIfRequired()
{
  //  LogInfo("Begin");

#if __cplusplus <= 201402L
  if (m_curGDrawables.find(GoomDrawable::TUBE) == m_curGDrawables.end())
#else
  if (!m_curGDrawables.contains(GoomDrawable::TUBE))
#endif
  {
    m_visualFx.tube_fx->ApplyNoDraw();
    return;
  }

  //  m_stats.DoTube();
  ResetDrawBuffSettings(m_states.GetCurrentBuffSettings(GoomDrawable::TUBE));
  m_visualFx.tube_fx->ApplyMultiple();

  //  LogInfo("End");
}

void GoomControl::GoomControlImpl::ApplyStarsToBothBuffersIfRequired()
{
  //  LogInfo("Begin");

#if __cplusplus <= 201402L
  if (m_curGDrawables.find(GoomDrawable::STARS) == m_curGDrawables.end())
#else
  if (!m_curGDrawables.contains(GoomDrawable::STARS))
#endif
  {
    return;
  }

  LogDebug("curGDrawables stars is set.");
  m_stats.DoStars();
  ResetDrawBuffSettings(m_states.GetCurrentBuffSettings(GoomDrawable::STARS));
  m_visualFx.star_fx->ApplyMultiple();

  //  LogInfo("End");
}

void GoomControl::GoomControlImpl::ApplyImageIfRequired()
{
#if __cplusplus <= 201402L
  if (m_curGDrawables.find(GoomDrawable::IMAGE) == m_curGDrawables.end())
#else
  if (!m_curGDrawables.contains(GoomDrawable::IMAGE))
#endif
  {
    return;
  }

  //m_stats.DoImage();
  ResetDrawBuffSettings(m_states.GetCurrentBuffSettings(GoomDrawable::IMAGE));
  m_visualFx.image_fx->ApplyMultiple();
}

void GoomControl::GoomControlImpl::StopLinesIfRequested()
{
  if ((m_goomData.stopLines & 0xf000) || !m_states.IsCurrentlyDrawable(GoomDrawable::SCOPE))
  {
    StopLinesRequest();
  }
}

void GoomControl::GoomControlImpl::StopLinesRequest()
{
  if (!m_gmline1.CanResetDestLine() || !m_gmline2.CanResetDestLine())
  {
    return;
  }

  m_stats.DoStopLinesRequest();

  float param1 = 0.0;
  float param2 = 0.0;
  float amplitude = 0.0;
  Pixel couleur{};
  LinesFx::LineType mode;
  ChooseGoomLine(&param1, &param2, &couleur, &mode, &amplitude, 1);
  couleur = GetBlackLineColor();

  m_gmline1.ResetDestLine(mode, param1, amplitude, couleur);
  m_gmline2.ResetDestLine(mode, param2, amplitude, couleur);
  m_stats.DoSwitchLines();
  m_goomData.stopLines &= 0x0fff;
}

void GoomControl::GoomControlImpl::ChooseGoomLine(float* param1,
                                                  float* param2,
                                                  Pixel* couleur,
                                                  LinesFx::LineType* mode,
                                                  float* amplitude,
                                                  const int far)
{
  *amplitude = 1.0F;
  *mode = m_goomEvent.GetRandomLineTypeEvent();

  switch (*mode)
  {
    case LinesFx::LineType::circle:
      if (far)
      {
        *param1 = *param2 = 0.47F;
        *amplitude = 0.8F;
        break;
      }
      if (m_goomEvent.Happens(GoomEvent::CHANGE_LINE_CIRCLE_AMPLITUDE))
      {
        *param1 = *param2 = 0.0F;
        *amplitude = 3.0F;
      }
      else if (m_goomEvent.Happens(GoomEvent::CHANGE_LINE_CIRCLE_PARAMS))
      {
        *param1 = 0.40F * static_cast<float>(GetScreenHeight());
        *param2 = 0.22F * static_cast<float>(GetScreenHeight());
      }
      else
      {
        *param1 = *param2 = static_cast<float>(GetScreenHeight()) * 0.35F;
      }
      break;
    case LinesFx::LineType::hline:
      if (m_goomEvent.Happens(GoomEvent::CHANGE_H_LINE_PARAMS) || far)
      {
        *param1 = static_cast<float>(GetScreenHeight()) / 7.0F;
        *param2 = 6.0F * static_cast<float>(GetScreenHeight()) / 7.0F;
      }
      else
      {
        *param1 = *param2 = static_cast<float>(GetScreenHeight()) / 2.0F;
        *amplitude = 2.0F;
      }
      break;
    case LinesFx::LineType::vline:
      if (m_goomEvent.Happens(GoomEvent::CHANGE_V_LINE_PARAMS) || far)
      {
        *param1 = static_cast<float>(GetScreenWidth()) / 7.0F;
        *param2 = 6.0F * static_cast<float>(GetScreenWidth()) / 7.0F;
      }
      else
      {
        *param1 = *param2 = static_cast<float>(GetScreenWidth()) / 2.0F;
        *amplitude = 1.5F;
      }
      break;
    default:
      throw std::logic_error("Unknown LineTypes enum.");
  }

  m_stats.DoChangeLineColor();
  *couleur = m_gmline1.GetRandomLineColor();
}

/* arret aleatore.. changement de mode de ligne..
  */
void GoomControl::GoomControlImpl::StopRandomLineChangeMode()
{
  constexpr uint32_t DEC_LINE_MODE_CYCLES = 80;
  constexpr uint32_t UPDATE_LINE_MODE_CYCLES = 120;

  if (m_goomData.lineMode != m_goomData.drawLinesDuration)
  {
    m_goomData.lineMode--;
    if (m_goomData.lineMode == -1)
    {
      m_goomData.lineMode = 0;
    }
  }
  else if ((m_cycle % DEC_LINE_MODE_CYCLES == 0) &&
           m_goomEvent.Happens(GoomEvent::REDUCE_LINE_MODE) && m_goomData.lineMode)
  {
    m_goomData.lineMode--;
  }

  if ((m_cycle % UPDATE_LINE_MODE_CYCLES == 0) &&
      m_goomEvent.Happens(GoomEvent::UPDATE_LINE_MODE) &&
#if __cplusplus <= 201402L
      m_curGDrawables.find(GoomDrawable::SCOPE) != m_curGDrawables.end())
#else
      m_curGDrawables.contains(GoomDrawable::SCOPE))
#endif
  {
    if (m_goomData.lineMode == 0)
    {
      m_goomData.lineMode = m_goomData.drawLinesDuration;
    }
    else if (m_goomData.lineMode == m_goomData.drawLinesDuration && m_gmline1.CanResetDestLine() &&
             m_gmline2.CanResetDestLine())
    {
      m_goomData.lineMode--;

      float param1 = 0.0;
      float param2 = 0.0;
      float amplitude = 0.0;
      Pixel color1{};
      LinesFx::LineType mode;
      ChooseGoomLine(&param1, &param2, &color1, &mode, &amplitude, m_goomData.stopLines);

      Pixel color2 = m_gmline2.GetRandomLineColor();
      if (m_goomData.stopLines)
      {
        m_goomData.stopLines--;
        if (m_goomEvent.Happens(GoomEvent::CHANGE_LINE_TO_BLACK))
        {
          color2 = color1 = GetBlackLineColor();
        }
      }

      LogDebug("goomData.lineMode = {} == {} = goomData.drawLinesDuration", m_goomData.lineMode,
               m_goomData.drawLinesDuration);
      m_gmline1.ResetDestLine(mode, param1, amplitude, color1);
      m_gmline2.ResetDestLine(mode, param2, amplitude, color2);
      m_stats.DoSwitchLines();
    }
  }
}

void GoomControl::GoomControlImpl::DisplayLines(const AudioSamples& soundData)
{
#if __cplusplus <= 201402L
  if (m_curGDrawables.find(GoomDrawable::LINES) == m_curGDrawables.end())
#else
  if (!m_curGDrawables.contains(GoomDrawable::LINES))
#endif
  {
    return;
  }

  LogDebug("curGDrawables lines is set.");

  m_stats.DoLines();

  m_gmline2.SetPower(m_gmline1.GetPower());

  const std::vector<int16_t>& audioSample = soundData.GetSample(0);
  const AudioSamples::MaxMinValues& soundMinMax = soundData.GetSampleMinMax(0);
  m_gmline1.DrawLines(audioSample, soundMinMax);
  m_gmline2.DrawLines(audioSample, soundMinMax);
  //  gmline2.drawLines(soundData.GetSample(1));

  constexpr uint32_t CHANGE_GOOM_LINE_CYCLES = 121;

  if (((m_cycle % CHANGE_GOOM_LINE_CYCLES) == 9) &&
      m_goomEvent.Happens(GoomEvent::CHANGE_GOOM_LINE) &&
      ((m_goomData.lineMode == 0) || (m_goomData.lineMode == m_goomData.drawLinesDuration)) &&
      m_gmline1.CanResetDestLine() && m_gmline2.CanResetDestLine())
  {
    LogDebug("cycle % 121 etc.: goomInfo->cycle = {}, rand1_3 = ?", m_cycle);
    float param1 = 0.0;
    float param2 = 0.0;
    float amplitude = 0.0;
    Pixel color1{};
    LinesFx::LineType mode;
    ChooseGoomLine(&param1, &param2, &color1, &mode, &amplitude, m_goomData.stopLines);

    Pixel color2 = m_gmline2.GetRandomLineColor();
    if (m_goomData.stopLines)
    {
      m_goomData.stopLines--;
      if (m_goomEvent.Happens(GoomEvent::CHANGE_LINE_TO_BLACK))
      {
        color2 = color1 = GetBlackLineColor();
      }
    }
    m_gmline1.ResetDestLine(mode, param1, amplitude, color1);
    m_gmline2.ResetDestLine(mode, param2, amplitude, color2);
  }
}

void GoomControl::GoomControlImpl::DisplayLinesIfInAGoom(const AudioSamples& soundData)
{
  constexpr uint32_t DISPLAY_LINES_GOOM_NUM = 5;

  if ((m_goomData.lineMode != 0) ||
      (m_goomInfo->GetSoundInfo().GetTimeSinceLastGoom() < DISPLAY_LINES_GOOM_NUM))
  {
    DisplayLines(soundData);
  }
}

#ifdef SHOW_STATE_TEXT_ON_SCREEN

void GoomControl::GoomControlImpl::DisplayStateText()
{
  std::string message = "";

  message += std20::format("State: {}\n", m_states.GetCurrentStateIndex());
  message += std20::format("Filter: {}\n",
                           EnumToString(m_visualFx.zoomFilter_fx->GetFilterSettings().mode));
  message += std20::format("Filter Settings Pending: {}\n",
                           m_visualFx.zoomFilter_fx->GetFilterSettingsArePending());

  message += std20::format("middleX: {}\n", m_visualFx.zoomFilter_fx->GetFilterSettings().middleX);
  message += std20::format("middleY: {}\n", m_visualFx.zoomFilter_fx->GetFilterSettings().middleY);

  message += std20::format("switchIncr: {}\n", m_goomData.switchIncr);
  message += std20::format("switchMult: {}\n", m_goomData.switchMult);

  message += std20::format("vitesse: {}\n",
                           m_visualFx.zoomFilter_fx->GetFilterSettings().vitesse.GetVitesse());
  message += std20::format("previousZoomSpeed: {}\n", m_goomData.previousZoomSpeed);
  message += std20::format(
      "reverse: {}\n", m_visualFx.zoomFilter_fx->GetFilterSettings().vitesse.GetReverseVitesse());
  message +=
      std20::format("relative speed: {}\n",
                    m_visualFx.zoomFilter_fx->GetFilterSettings().vitesse.GetRelativeSpeed());

  message += std20::format("hPlaneEffect: {}\n",
                           m_visualFx.zoomFilter_fx->GetFilterSettings().hPlaneEffect);
  message += std20::format("hPlaneEffectAmplitude: {}\n",
                           m_visualFx.zoomFilter_fx->GetFilterSettings().hPlaneEffectAmplitude);
  message += std20::format("vPlaneEffect: {}\n",
                           m_visualFx.zoomFilter_fx->GetFilterSettings().vPlaneEffect);
  message += std20::format("vPlaneEffectAmplitude: {}\n",
                           m_visualFx.zoomFilter_fx->GetFilterSettings().vPlaneEffectAmplitude);
  message +=
      std20::format("rotateSpeed: {}\n", m_visualFx.zoomFilter_fx->GetFilterSettings().rotateSpeed);
  message +=
      std20::format("tanEffect: {}\n", m_visualFx.zoomFilter_fx->GetFilterSettings().tanEffect);

  message += std20::format("noisify: {}\n", m_visualFx.zoomFilter_fx->GetFilterSettings().noisify);
  message +=
      std20::format("noiseFactor: {}\n", m_visualFx.zoomFilter_fx->GetFilterSettings().noiseFactor);

  message +=
      std20::format("blockyWavy: {}\n", m_visualFx.zoomFilter_fx->GetFilterSettings().blockyWavy);

  message +=
      std20::format("waveEffectType: {}\n",
                    EnumToString(m_visualFx.zoomFilter_fx->GetFilterSettings().waveEffectType));
  message += std20::format("waveFreqFactor: {}\n",
                           m_visualFx.zoomFilter_fx->GetFilterSettings().waveFreqFactor);
  message += std20::format("waveAmplitude: {}\n",
                           m_visualFx.zoomFilter_fx->GetFilterSettings().waveAmplitude);

  message += std20::format("amuletAmplitude: {}\n",
                           m_visualFx.zoomFilter_fx->GetFilterSettings().amuletAmplitude);
  message += std20::format("crystalBallAmplitude: {}\n",
                           m_visualFx.zoomFilter_fx->GetFilterSettings().crystalBallAmplitude);
  message += std20::format("scrunchAmplitude: {}\n",
                           m_visualFx.zoomFilter_fx->GetFilterSettings().scrunchAmplitude);
  message += std20::format("speedwayAmplitude: {}\n",
                           m_visualFx.zoomFilter_fx->GetFilterSettings().speedwayAmplitude);

  message +=
      std20::format("hypercosEffect: {}\n",
                    EnumToString(m_visualFx.zoomFilter_fx->GetFilterSettings().hypercosEffect));
  message += std20::format("hypercosFreqX: {}\n",
                           m_visualFx.zoomFilter_fx->GetFilterSettings().hypercosFreqX);
  message += std20::format("hypercosFreqY: {}\n",
                           m_visualFx.zoomFilter_fx->GetFilterSettings().hypercosFreqY);
  message += std20::format("hypercosAmplitudeX: {}\n",
                           m_visualFx.zoomFilter_fx->GetFilterSettings().hypercosAmplitudeX);
  message += std20::format("hypercosAmplitudeY: {}\n",
                           m_visualFx.zoomFilter_fx->GetFilterSettings().hypercosAmplitudeY);

  message +=
      std20::format("updatesSinceLastChange: {}\n", m_goomData.updatesSinceLastZoomEffectsChange);
  //  message += std20::format("GetGeneralSpeed: {}\n", m_visualFx.zoomFilter_fx->GetGeneralSpeed());
  //  message += std20::format("pertedec: {}\n", m_visualFx.zoomFilter_fx->GetFilterSettings().pertedec);
  //  message +=
  //    std20::format("waveEffect: {}\n", m_visualFx.zoomFilter_fx->GetFilterSettings().waveEffect);
  //  message += std20::format("lineMode: {}\n", m_goomData.lineMode);
  //  message += std20::format("lockTime: {}\n", GetLockTime());
  //  message += std20::format("stopLines: {}\n", m_goomData.stopLines);

  UpdateMessage(message);
}

#endif

void GoomControl::GoomControlImpl::DisplayText(const std::string& songTitle,
                                               const std::string& message,
                                               const float fps)
{
  UpdateMessage(message);

  if (fps > 0.0)
  {
    const std::string text = std20::format("{.0f} fps", fps);
    m_textDraw.SetBuffers({&m_imageBuffers.GetOutputBuff()});
    DrawText(text, 10, 24, 0.0);
  }

  if (!songTitle.empty())
  {
    m_stats.SetSongTitle(songTitle);
    m_goomData.title = songTitle;
    m_goomData.timeOfTitleDisplay = GoomData::MAX_TITLE_DISPLAY_TIME;
  }

  if (m_goomData.timeOfTitleDisplay > 0)
  {
    if (m_goomData.timeOfTitleDisplay == GoomData::MAX_TITLE_DISPLAY_TIME)
    {
      m_textColorMap = &(RandomColorMaps{}.GetRandomColorMap(ColorMapGroup::DIVERGING_BLACK));
      m_textOutlineColor = Pixel::WHITE;
    }
    const auto xPos = static_cast<int>(0.085F * static_cast<float>(GetScreenWidth()));
    const auto yPos = static_cast<int>(0.300F * static_cast<float>(GetScreenHeight()));
    const auto timeGone =
        static_cast<float>(GoomData::TIME_TO_SPACE_TITLE_DISPLAY - m_goomData.timeOfTitleDisplay);
    const float spacing = std::max(0.0F, 0.056F * timeGone);
    const int xExtra = static_cast<int>(
        std::max(0.0F, 3.0F * timeGone / static_cast<float>(m_goomData.timeOfTitleDisplay)));

    m_textDraw.SetBuffers({&m_imageBuffers.GetOutputBuff()});
    DrawText(m_goomData.title, xPos + xExtra, yPos, spacing);

    m_goomData.timeOfTitleDisplay--;

    if (m_goomData.timeOfTitleDisplay < GoomData::TIME_TO_FADE_TITLE_DISPLAY)
    {
      m_textDraw.SetBuffers({&m_imageBuffers.GetP1()});
      DrawText(m_goomData.title, xPos, yPos, spacing);
    }
  }
}

void GoomControl::GoomControlImpl::DrawText(const std::string& str,
                                            const int xPos,
                                            const int yPos,
                                            const float spacing)
{
  const float t = static_cast<float>(m_goomData.timeOfTitleDisplay) /
                  static_cast<float>(GoomData::MAX_TITLE_DISPLAY_TIME);
  const float brightness = t;

  const IColorMap& charColorMap =
      m_goomData.timeOfTitleDisplay > GoomData::TIME_TO_SPACE_TITLE_DISPLAY
          ? RandomColorMaps{}.GetRandomColorMap(ColorMapGroup::DIVERGING)
          : RandomColorMaps{}.GetRandomColorMap(/*ColorMapGroup::diverging*/);
  const auto lastTextIndex = static_cast<float>(str.size() - 1);
  //  const ColorMap& colorMap2 = colorMaps.getColorMap(colordata::ColorMapName::Blues);
  //  const Pixel fontColor = m_textColorMap->GetColor(t);
  const Pixel outlineColor = m_textOutlineColor;
  constexpr float TEXT_GAMMA = 4.2;
  constexpr float TEXT_GAMMA_THRESHOLD = 0.01;
  static GammaCorrection s_gammaCorrect{TEXT_GAMMA, TEXT_GAMMA_THRESHOLD};
  const auto getFontColor = [&](const size_t textIndexOfChar, float x, float y, float width,
                                float height) {
    const float tChar = 1.0F - static_cast<float>(textIndexOfChar) / lastTextIndex;
    const Pixel fontColor = m_textColorMap->GetColor(y / static_cast<float>(height));
    const Pixel charColor = charColorMap.GetColor(tChar);
    return s_gammaCorrect.GetCorrection(
        brightness, IColorMap::GetColorMix(fontColor, charColor, x / static_cast<float>(width)));
  };
  const auto getOutlineFontColor =
      [&]([[maybe_unused]] size_t textIndexOfChar, [[maybe_unused]] float x,
          [[maybe_unused]] float y, [[maybe_unused]] float width, [[maybe_unused]] float height) {
        return s_gammaCorrect.GetCorrection(brightness, outlineColor);
      };

  //  CALL UP TO PREPARE ONCE ONLY
  m_text.SetText(str);
  m_text.SetFontColorFunc(getFontColor);
  m_text.SetOutlineFontColorFunc(getOutlineFontColor);
  m_text.SetCharSpacing(spacing);
  m_text.Prepare();
  m_text.Draw(xPos, yPos);
}

/*
 * Met a jour l'affichage du message defilant
 */
void GoomControl::GoomControlImpl::UpdateMessage(const std::string& message)
{
  constexpr int MSG_FONT_SIZE = 10;
  constexpr int VERTICAL_SPACING = 10;
  constexpr int LINE_HEIGHT = MSG_FONT_SIZE + VERTICAL_SPACING;
  constexpr int Y_START = 50;

  if (!message.empty())
  {
    m_messageData.message = message;
    const std::vector<std::string> msgLines = SplitString(m_messageData.message, "\n");
    m_messageData.numberOfLinesInMessage = msgLines.size();
    m_messageData.affiche = 20 + LINE_HEIGHT * m_messageData.numberOfLinesInMessage;
  }
  if (m_messageData.affiche)
  {
    if (m_updateMessageText == nullptr)
    {
      const auto getFontColor = []([[maybe_unused]] const size_t textIndexOfChar,
                                   [[maybe_unused]] float x, [[maybe_unused]] float y,
                                   [[maybe_unused]] float width,
                                   [[maybe_unused]] float height) { return Pixel::WHITE; };
      const auto getOutlineFontColor =
          []([[maybe_unused]] const size_t textIndexOfChar, [[maybe_unused]] float x,
             [[maybe_unused]] float y, [[maybe_unused]] float width,
             [[maybe_unused]] float height) { return Pixel{0xfafafafaU}; };
      m_updateMessageText = std::make_unique<TextDraw>(&m_textDraw);
      m_updateMessageText->SetFontFile(m_text.GetFontFile());
      m_updateMessageText->SetFontSize(MSG_FONT_SIZE);
      m_updateMessageText->SetOutlineWidth(1);
      m_updateMessageText->SetAlignment(TextDraw::TextAlignment::LEFT);
      m_updateMessageText->SetFontColorFunc(getFontColor);
      m_updateMessageText->SetOutlineFontColorFunc(getOutlineFontColor);
    }
    const std::vector<std::string> msgLines = SplitString(m_messageData.message, "\n");
    for (size_t i = 0; i < msgLines.size(); i++)
    {
      const auto yPos = static_cast<int>(Y_START + m_messageData.affiche -
                                         (m_messageData.numberOfLinesInMessage - i) * LINE_HEIGHT);
      m_updateMessageText->SetText(msgLines[i]);
      m_updateMessageText->Prepare();
      m_textDraw.SetBuffers({&m_imageBuffers.GetOutputBuff()});
      m_updateMessageText->Draw(50, yPos);
    }
    m_messageData.affiche--;
  }
}

} // namespace GOOM
