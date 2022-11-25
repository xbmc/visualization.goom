#include "goom_all_visual_fx.h"

//#undef NO_LOGGING

#include "all_standard_visual_fx.h"
#include "color/color_maps.h"
#include "color/color_utils.h"
#include "draw/goom_draw.h"
#include "filter_fx/filter_buffers_service.h"
#include "filter_fx/filter_colors_service.h"
#include "goom_config.h"
#include "goom_plugin_info.h"
#include "logging.h"
#include "sound_info.h"
#include "utils/graphics/pixel_utils.h"
#include "utils/name_value_pairs.h"
#include "utils/stopwatch.h"
#include "visual_fx/fx_helper.h"
#include "visual_fx/lines_fx.h"

#include <array>
#include <memory>

namespace GOOM::CONTROL
{

using COLOR::GetLuma;
using COLOR::IColorMap;
using CONTROL::GoomDrawables;
using DRAW::IGoomDraw;
using FILTER_FX::FilterBuffersService;
using FILTER_FX::FilterColorsService;
using FILTER_FX::ZoomFilterFx;
using FILTER_FX::ZoomFilterSettings;
using FILTER_FX::AFTER_EFFECTS::AfterEffectsTypes;
using UTILS::Logging; // NOLINT(misc-unused-using-decls)
using UTILS::NameValuePairs;
using UTILS::Parallel;
using UTILS::Stopwatch;
using UTILS::GRAPHICS::MakePixel;
using UTILS::GRAPHICS::SmallImageBitmaps;
using VISUAL_FX::FxHelper;

static constexpr auto SMALL_LUMA = 0.1F;

GoomAllVisualFx::GoomAllVisualFx(Parallel& parallel,
                                 const FxHelper& fxHelper,
                                 const SmallImageBitmaps& smallBitmaps,
                                 const std::string& resourcesDirectory,
                                 IGoomStateHandler& goomStateHandler,
                                 std::unique_ptr<FilterBuffersService> filterBuffersService,
                                 std::unique_ptr<FilterColorsService> filterColorsService) noexcept
  : m_goomDraw{fxHelper.GetDraw()},
    m_goomRand{fxHelper.GetGoomRand()},
    m_allStandardVisualFx{spimpl::make_unique_impl<AllStandardVisualFx>(
        parallel, fxHelper, smallBitmaps, resourcesDirectory)},
    m_zoomFilterFx{std::make_unique<ZoomFilterFx>(parallel,
                                                  fxHelper.GetGoomInfo(),
                                                  std::move(filterBuffersService),
                                                  std::move(filterColorsService))},
    m_goomStateHandler{goomStateHandler}
{
  m_allStandardVisualFx->SetResetDrawBuffSettingsFunc([this](const GoomDrawables fx)
                                                      { ResetCurrentDrawBuffSettings(fx); });
}

GoomAllVisualFx::~GoomAllVisualFx() noexcept = default;

void GoomAllVisualFx::Start()
{
  m_allStandardVisualFx->Start();
  m_adaptiveExposure.Start();
  m_zoomFilterFx->Start();
}

void GoomAllVisualFx::Finish()
{
  m_allStandardVisualFx->Finish();

  m_zoomFilterFx->Finish();
}

void GoomAllVisualFx::ChangeState()
{
  m_allStandardVisualFx->SuspendFx();

  static constexpr auto MAX_TRIES = 10U;
  const auto oldState             = m_goomStateHandler.GetCurrentState();

  for (auto numTry = 0U; numTry < MAX_TRIES; ++numTry)
  {
    m_goomStateHandler.ChangeToNextState();

    if ((not m_allowMultiThreadedStates) and
        GoomStateInfo::IsMultiThreaded(m_goomStateHandler.GetCurrentState()))
    {
      continue;
    }

    // Pick a different state if possible
    if (oldState != m_goomStateHandler.GetCurrentState())
    {
      break;
    }
  }

  m_currentGoomDrawables = m_goomStateHandler.GetCurrentDrawables();
  m_allStandardVisualFx->SetCurrentGoomDrawables(m_currentGoomDrawables);
  m_allStandardVisualFx->ChangeShaderEffects();

  m_allStandardVisualFx->GetLinesFx().ResetLineModes();

  m_allStandardVisualFx->ResumeFx();
}

void GoomAllVisualFx::StartExposureControl()
{
  m_doExposureControl = true;
}

auto GoomAllVisualFx::GetLastShaderEffects() const -> const GoomShaderEffects&
{
  return m_allStandardVisualFx->GetLastShaderEffects();
}

void GoomAllVisualFx::SetSingleBufferDots(const bool value)
{
  m_allStandardVisualFx->SetSingleBufferDots(value);
}

void GoomAllVisualFx::PostStateUpdate(const std::unordered_set<GoomDrawables>& oldGoomDrawables)
{
  m_allStandardVisualFx->PostStateUpdate(oldGoomDrawables);
}

void GoomAllVisualFx::RefreshAllFx()
{
  m_allStandardVisualFx->RefreshAllFx();
}

inline void GoomAllVisualFx::ResetCurrentDrawBuffSettings(const GoomDrawables fx)
{
  m_resetDrawBuffSettings(GetCurrentBuffSettings(fx));
}

inline auto GoomAllVisualFx::GetCurrentBuffSettings(const GoomDrawables fx) const -> FXBuffSettings
{
  const auto buffIntensity = m_goomRand.GetRandInRange(
      GoomStateInfo::GetBuffIntensityRange(m_goomStateHandler.GetCurrentState(), fx));
  // Careful here. > 1 reduces smearing.
  static constexpr auto INTENSITY_FACTOR = 1.0F;
  return {INTENSITY_FACTOR * buffIntensity};
}

void GoomAllVisualFx::ChangeAllFxColorMaps()
{
  m_allStandardVisualFx->ChangeColorMaps();
}

void GoomAllVisualFx::ChangeDrawPixelBlend()
{
  if (m_goomRand.ProbabilityOf(1.0F))
  {
    m_goomDraw.SetDefaultBlendPixelFunc();
  }
  else if (m_goomRand.ProbabilityOf(0.0F))
  {
    m_goomDraw.SetBlendPixelFunc(GetSameLumaBlendPixelFunc());
  }
  else if (m_goomRand.ProbabilityOf(0.0F))
  {
    m_goomDraw.SetBlendPixelFunc(GetSameLumaMixBlendPixelFunc());
  }
  else
  {
    m_goomDraw.SetBlendPixelFunc(GetReverseColorAddBlendPixelPixelFunc());
  }
}

auto GoomAllVisualFx::GetReverseColorAddBlendPixelPixelFunc() -> IGoomDraw::BlendPixelFunc
{
  return [](const Pixel& oldColor, const Pixel& newColor, const uint32_t intBuffIntensity)
  { return COLOR::GetColorAdd(COLOR::GetBrighterColorInt(intBuffIntensity, oldColor), newColor); };
}

auto GoomAllVisualFx::GetSameLumaBlendPixelFunc() -> IGoomDraw::BlendPixelFunc
{
  return [](const Pixel& oldColor, const Pixel& newColor, const uint32_t intBuffIntensity)
  {
    const auto newColorLuma =
        GetLuma(newColor) * (static_cast<float>(intBuffIntensity) / channel_limits<float>::max());
    if (newColorLuma < SMALL_LUMA)
    {
      return COLOR::GetColorAdd(oldColor, newColor);
    }
    const auto oldColorLuma = GetLuma(oldColor);
    const auto brightness   = 1.0F + (oldColorLuma / newColorLuma);

    const auto red   = static_cast<uint32_t>(brightness * static_cast<float>(newColor.R()));
    const auto green = static_cast<uint32_t>(brightness * static_cast<float>(newColor.G()));
    const auto blue  = static_cast<uint32_t>(brightness * static_cast<float>(newColor.B()));

    return MakePixel(red, green, blue, MAX_ALPHA);
  };
}

auto GoomAllVisualFx::GetSameLumaMixBlendPixelFunc() -> IGoomDraw::BlendPixelFunc
{
  return [](const Pixel& oldColor, const Pixel& newColor, const uint32_t intBuffIntensity)
  {
    const auto newColorLuma =
        GetLuma(newColor) * (static_cast<float>(intBuffIntensity) / channel_limits<float>::max());
    if (newColorLuma < SMALL_LUMA)
    {
      return COLOR::GetColorAdd(oldColor, newColor);
    }
    const auto oldColorLuma = GetLuma(oldColor);
    const auto brightness   = 0.5F * (1.0F + (oldColorLuma / newColorLuma));

    const auto finalNewColor = IColorMap::GetColorMix(oldColor, newColor, 0.7F);
    const auto red   = static_cast<uint32_t>(brightness * static_cast<float>(finalNewColor.R()));
    const auto green = static_cast<uint32_t>(brightness * static_cast<float>(finalNewColor.G()));
    const auto blue  = static_cast<uint32_t>(brightness * static_cast<float>(finalNewColor.B()));

    return MakePixel(red, green, blue, MAX_ALPHA);
  };
}

void GoomAllVisualFx::UpdateFilterSettings(const ZoomFilterSettings& filterSettings)
{
  if (filterSettings.filterEffectsSettingsHaveChanged)
  {
    m_zoomFilterFx->UpdateFilterEffectsSettings(filterSettings.filterEffectsSettings);
  }

  m_zoomFilterFx->UpdateFilterBufferSettings(filterSettings.filterBufferSettings);
  m_zoomFilterFx->UpdateFilterColorSettings(
      filterSettings.filterEffectsSettings.afterEffectsSettings
          .active[AfterEffectsTypes::BLOCK_WAVY]);

  m_allStandardVisualFx->SetZoomMidpoint(filterSettings.filterEffectsSettings.zoomMidpoint);
}

void GoomAllVisualFx::ApplyCurrentStateToSingleBuffer()
{
  m_allStandardVisualFx->ApplyCurrentStateToSingleBuffer();
}

void GoomAllVisualFx::ApplyCurrentStateToMultipleBuffers(const AudioSamples& soundData)
{
  m_allStandardVisualFx->ApplyCurrentStateToMultipleBuffers(soundData);
}

auto GoomAllVisualFx::ApplyEndEffectIfNearEnd(const Stopwatch::TimeValues& timeValues) -> void
{
  m_allStandardVisualFx->ApplyEndEffectIfNearEnd(timeValues);
}

auto GoomAllVisualFx::GetCurrentColorMapsNames() const -> std::unordered_set<std::string>
{
  return m_allStandardVisualFx->GetActiveColorMapsNames();
}

auto GoomAllVisualFx::GetZoomFilterFxNameValueParams() const -> NameValuePairs
{
  return m_zoomFilterFx->GetNameValueParams();
}

} // namespace GOOM::CONTROL
