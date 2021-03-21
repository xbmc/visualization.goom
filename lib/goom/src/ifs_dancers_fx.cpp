/*
 * ifs.c --- modified iterated functions system for goom.
 */

/*-
 * Copyright (c) 1997 by Massimino Pascal <Pascal.Massimon@ens.fr>
 *
 * Permission to use, copy, modify, and distribute this software and its
 * documentation for any purpose and without fee is hereby granted,
 * provided that the above copyright notice appear in all copies and that
 * both that copyright notice and this permission notice appear in
 * supporting documentation.
 *
 * This file is provided AS IS with no warranties of any kind.  The author
 * shall have no liability with respect to the infringement of copyrights,
 * trade secrets or any patents by this file or any part thereof.  In no
 * event will the author be liable for any lost revenue or profits or
 * other special, indirect and consequential damages.
 *
 * If this mode is weird and you have an old MetroX server, it is buggy.
 * There is a free SuSE-enhanced MetroX X server that is fine.
 *
 * When shown ifs, Diana Rose (4 years old) said, "It looks like dancing."
 *
 * Revision History:
 * 01-Feb-2021: converted to C++14, lots of color changes (glk)
 * 13-Dec-2003: Added some goom specific stuffs (to make ifs a VisualFX).
 * 11-Apr-2002: jeko@ios-software.com: Make ifs.c system-indendant. (ifs.h added)
 * 01-Nov-2000: Allocation checks
 * 10-May-1997: jwz@jwz.org: turned into a standalone program.
 *              Made it render into an offscreen bitmap and then copy
 *              that onto the screen, to reduce flicker.
 */

#include "ifs_dancers_fx.h"

#include "goom_draw.h"
#include "goom_graphic.h"
#include "goom_plugin_info.h"
#include "goom_stats.h"
#include "goomutils/colorutils.h"
#include "goomutils/goomrand.h"
// #undef NO_LOGGING
#include "goomutils/graphics/small_image_bitmaps.h"
#include "goomutils/logging.h"
#include "goomutils/random_colormaps.h"
#include "ifs/colorizer.h"
#include "ifs/fractal.h"
#include "ifs/low_density_blurrer.h"
#include "stats/ifs_stats.h"

#include <array>

//#undef NDEBUG
#include <cassert>
#include <cmath>
#include <cstdint>
#include <memory>
#include <string>
#include <utility>
#include <vector>

namespace GOOM
{

using IFS::BlurrerColorMode;
using IFS::Colorizer;
using IFS::Fractal;
using IFS::IfsPoint;
using IFS::LowDensityBlurrer;
using UTILS::GammaCorrection;
using UTILS::GetRandInRange;
using UTILS::ProbabilityOfMInN;
using UTILS::RandomColorMaps;
using UTILS::SmallImageBitmaps;
using UTILS::Weights;

inline auto MegaChangeColorMapEvent() -> bool
{
  return ProbabilityOfMInN(3, 10);
}

// clang-format off
static const Weights<BlurrerColorMode> BLURRER_COLOR_MODE_WEIGHTS{{
  {BlurrerColorMode::SMOOTH_WITH_NEIGHBOURS,1000},
  {BlurrerColorMode::SMOOTH_NO_NEIGHBOURS,     1},
  {BlurrerColorMode::SIMI_WITH_NEIGHBOURS,     1},
  {BlurrerColorMode::SIMI_NO_NEIGHBOURS,       5},
  {BlurrerColorMode::SINGLE_WITH_NEIGHBOURS,   1},
  {BlurrerColorMode::SINGLE_NO_NEIGHBOURS,     5},
}};
// clang-format on

class IfsDancersFx::IfsDancersFxImpl
{
public:
  explicit IfsDancersFxImpl(const IGoomDraw* draw, std::shared_ptr<const PluginInfo> info) noexcept;
  ~IfsDancersFxImpl() noexcept;
  IfsDancersFxImpl(const IfsDancersFxImpl&) = delete;
  IfsDancersFxImpl(const IfsDancersFxImpl&&) = delete;
  auto operator=(const IfsDancersFxImpl&) -> IfsDancersFxImpl& = delete;
  auto operator=(const IfsDancersFxImpl&&) -> IfsDancersFxImpl& = delete;

  [[nodiscard]] auto GetResourcesDirectory() const -> const std::string&;
  void SetResourcesDirectory(const std::string& dirName);
  void SetSmallImageBitmaps(const SmallImageBitmaps& smallBitmaps);

  void Init();

  void ApplyNoDraw();
  void UpdateIfs();
  void UpdateLowDensityThreshold();
  auto GetColorMode() const -> IfsDancersFx::ColorMode;
  void SetColorMode(IfsDancersFx::ColorMode c);
  void Renew();
  void UpdateIncr();

  void SetWeightedColorMaps(std::shared_ptr<RandomColorMaps> weightedMaps);

  void Start();
  void Finish();
  void Log(const GoomStats::LogStatsValueFunc& l) const;

private:
  static constexpr int32_t MAX_COUNT_BEFORE_NEXT_UPDATE = 1000;
  static constexpr int32_t MIN_CYCLE_LENGTH = 1000;
  static constexpr int32_t MAX_CYCLE_LENGTH = 2000;
  int32_t m_cycleLength = MIN_CYCLE_LENGTH;

  const IGoomDraw* const m_draw;
  const std::shared_ptr<const PluginInfo> m_goomInfo;

  Colorizer m_colorizer{};
  std::string m_resourcesDirectory{};

  std::unique_ptr<Fractal> m_fractal{};

  int m_cycle = 0;
  int m_ifsIncr = 1; // dessiner l'ifs (0 = non: > = increment)
  int m_decayIfs = 0; // disparition de l'ifs
  int m_recayIfs = 0; // dedisparition de l'ifs
  void UpdateCycle();
  void UpdateDecay();
  void UpdateDecayAndRecay();

  IfsStats m_stats{};

  static constexpr float LOW_DENSITY_GAMMA = 10.0;
  static constexpr float LOW_DENSITY_GAMMA_THRESHOLD = 0.01;
  const GammaCorrection m_lowDensityGammaCorrect{LOW_DENSITY_GAMMA, LOW_DENSITY_GAMMA_THRESHOLD};

  void ChangeColormaps();
  static constexpr uint32_t MAX_DENSITY_COUNT = 20;
  static constexpr uint32_t MIN_DENSITY_COUNT = 5;
  uint32_t m_lowDensityCount = MIN_DENSITY_COUNT;
  LowDensityBlurrer m_blurrer;
  float m_lowDensityBlurThreshold = 0.99;
  bool m_useRandomLowDensityColors = false;
  auto BlurLowDensityColors(size_t numPoints, const std::vector<IfsPoint>& lowDensityPoints) const
      -> bool;
  void DrawNextIfsPoints();
  void DrawPoint(const IfsPoint& point, const float tMix);
  void SetLowDensityColors(std::vector<IfsPoint>& points, uint32_t maxLowDensityCount) const;
  [[nodiscard]] auto GetIfsIncr() const -> int;
};

IfsDancersFx::IfsDancersFx(const IGoomDraw* const draw,
                           const std::shared_ptr<const PluginInfo>& info) noexcept
  : m_fxImpl{std::make_unique<IfsDancersFxImpl>(draw, info)}
{
}

IfsDancersFx::~IfsDancersFx() noexcept = default;

void IfsDancersFx::Init()
{
  m_fxImpl->Init();
}

auto IfsDancersFx::GetResourcesDirectory() const -> const std::string&
{
  return m_fxImpl->GetResourcesDirectory();
}

void IfsDancersFx::SetResourcesDirectory(const std::string& dirName)
{
  m_fxImpl->SetResourcesDirectory(dirName);
}

void IfsDancersFx::SetSmallImageBitmaps(const SmallImageBitmaps& smallBitmaps)
{
  m_fxImpl->SetSmallImageBitmaps(smallBitmaps);
}

void IfsDancersFx::SetWeightedColorMaps(const std::shared_ptr<RandomColorMaps> weightedMaps)
{
  m_fxImpl->SetWeightedColorMaps(weightedMaps);
}

void IfsDancersFx::Start()
{
  m_fxImpl->Start();
}

void IfsDancersFx::Resume()
{
}

void IfsDancersFx::Suspend()
{
}

void IfsDancersFx::Finish()
{
  m_fxImpl->Finish();
}

void IfsDancersFx::Log(const GoomStats::LogStatsValueFunc& logVal) const
{
  m_fxImpl->Log(logVal);
}

auto IfsDancersFx::GetFxName() const -> std::string
{
  return "IFS FX";
}

void IfsDancersFx::ApplyNoDraw()
{
  if (!m_enabled)
  {
    return;
  }

  m_fxImpl->ApplyNoDraw();
}

void IfsDancersFx::ApplyMultiple()
{
  if (!m_enabled)
  {
    return;
  }

  m_fxImpl->UpdateIfs();
}

auto IfsDancersFx::GetColorMode() const -> IfsDancersFx::ColorMode
{
  return m_fxImpl->GetColorMode();
}

void IfsDancersFx::SetColorMode(ColorMode c)
{
  m_fxImpl->SetColorMode(c);
}

void IfsDancersFx::UpdateIncr()
{
  m_fxImpl->UpdateIncr();
}

void IfsDancersFx::Renew()
{
  m_fxImpl->Renew();
}

IfsDancersFx::IfsDancersFxImpl::IfsDancersFxImpl(const IGoomDraw* const draw,
                                                 std::shared_ptr<const PluginInfo> info) noexcept
  : m_draw{draw},
    m_goomInfo{std::move(info)},
    m_fractal{std::make_unique<Fractal>(
        m_draw->GetScreenWidth(), m_draw->GetScreenHeight(), m_colorizer.GetColorMaps(), &m_stats)},
    m_blurrer{m_draw, 3}
{
}

IfsDancersFx::IfsDancersFxImpl::~IfsDancersFxImpl() noexcept = default;

void IfsDancersFx::IfsDancersFxImpl::Init()
{
  m_fractal->Init();
  UpdateLowDensityThreshold();
}

inline auto IfsDancersFx::IfsDancersFxImpl::GetResourcesDirectory() const -> const std::string&
{
  return m_resourcesDirectory;
}

inline void IfsDancersFx::IfsDancersFxImpl::SetResourcesDirectory(const std::string& dirName)
{
  m_resourcesDirectory = dirName;
}

inline void IfsDancersFx::IfsDancersFxImpl::SetSmallImageBitmaps(
    const SmallImageBitmaps& smallBitmaps)
{
  m_fractal->SetSmallImageBitmaps(smallBitmaps);
}

inline auto IfsDancersFx::IfsDancersFxImpl::GetColorMode() const -> IfsDancersFx::ColorMode
{
  return m_colorizer.GetColorMode();
}

inline void IfsDancersFx::IfsDancersFxImpl::SetColorMode(const IfsDancersFx::ColorMode c)
{
  return m_colorizer.SetForcedColorMode(c);
}

inline void IfsDancersFx::IfsDancersFxImpl::SetWeightedColorMaps(
    const std::shared_ptr<RandomColorMaps> weightedMaps)
{
  m_colorizer.SetWeightedColorMaps(weightedMaps);
}

inline void IfsDancersFx::IfsDancersFxImpl::Start()
{
  Init();
}

inline void IfsDancersFx::IfsDancersFxImpl::Finish()
{
  m_stats.SetlastIfsIncr(m_ifsIncr);
}

inline void IfsDancersFx::IfsDancersFxImpl::Log(const GoomStats::LogStatsValueFunc& l) const
{
  m_stats.Log(l);
}

void IfsDancersFx::IfsDancersFxImpl::Renew()
{
  ChangeColormaps();
  m_colorizer.ChangeColorMode();

  constexpr float MIN_SPEED_AMP = 1.1;
  constexpr float MAX_SPEED_AMP = 5.1;
  constexpr float MAX_SPEED_WEIGHT = 10.0;
  const float speedAmp = std::min(GetRandInRange(MIN_SPEED_AMP, MAX_SPEED_WEIGHT), MAX_SPEED_AMP);
  const float accelFactor = 1.0F / (1.2F - m_goomInfo->GetSoundInfo().GetAcceleration());

  m_fractal->SetSpeed(std::max(1U, static_cast<uint32_t>(speedAmp * accelFactor)));
}

void IfsDancersFx::IfsDancersFxImpl::ChangeColormaps()
{
  m_colorizer.ChangeColorMaps();
  m_blurrer.SetColorMode(BLURRER_COLOR_MODE_WEIGHTS.GetRandomWeighted());
  m_blurrer.SetSingleColor(m_colorizer.GetColorMaps().GetRandomColorMap().GetColor(0.5F));
}

void IfsDancersFx::IfsDancersFxImpl::ApplyNoDraw()
{
  UpdateDecayAndRecay();
  UpdateDecay();
}

void IfsDancersFx::IfsDancersFxImpl::UpdateIfs()
{
  m_stats.UpdateStart();

  UpdateDecayAndRecay();
  if (GetIfsIncr() <= 0)
  {
    return;
  }

  UpdateCycle();

  DrawNextIfsPoints();

  m_stats.UpdateEnd();
}

void IfsDancersFx::IfsDancersFxImpl::UpdateDecayAndRecay()
{
  m_decayIfs--;
  if (m_decayIfs > 0)
  {
    m_ifsIncr += 2;
  }
  if (m_decayIfs == 0)
  {
    m_ifsIncr = 0;
  }

  if (m_recayIfs)
  {
    m_ifsIncr -= 2;
    m_recayIfs--;
    if ((m_recayIfs == 0) && (m_ifsIncr <= 0))
    {
      m_ifsIncr = 1;
    }
  }

  m_stats.UpdateIfsIncr(m_ifsIncr);
}

void IfsDancersFx::IfsDancersFxImpl::UpdateIncr()
{
  if (m_ifsIncr <= 0)
  {
    m_recayIfs = 5;
    m_ifsIncr = 11;
    m_stats.UpdateIfsIncr(m_ifsIncr);
    Renew();
  }
}

void IfsDancersFx::IfsDancersFxImpl::UpdateDecay()
{
  if ((m_ifsIncr > 0) && (m_decayIfs <= 0))
  {
    m_decayIfs = 100;
  }
}

inline auto IfsDancersFx::IfsDancersFxImpl::GetIfsIncr() const -> int
{
  return m_ifsIncr;
}

void IfsDancersFx::IfsDancersFxImpl::UpdateCycle()
{
  // TODO: trouver meilleur soluce pour increment (mettre le code de gestion de l'ifs
  //       dans ce fichier)
  //       find the best solution for increment (put the management code of the ifs in this file)
  m_cycle++;
  if (m_cycle < m_cycleLength)
  {
    return;
  }

  m_cycle = 0;
  m_cycleLength = GetRandInRange(MIN_CYCLE_LENGTH, MAX_CYCLE_LENGTH + 1);
  m_stats.UpdateCycleChanges();

  if (ProbabilityOfMInN(15, 20))
  {
    m_lowDensityBlurThreshold = 0.99;
    m_stats.UpdateHighLowDensityBlurThreshold();
  }
  else
  {
    m_lowDensityBlurThreshold = 0.40;
    m_stats.UpdateLowLowDensityBlurThreshold();
  }

  m_fractal->Reset();

  Renew();
}

void IfsDancersFx::IfsDancersFxImpl::DrawNextIfsPoints()
{
  const std::vector<IfsPoint>& points = m_fractal->GetNextIfsPoints();
  const uint32_t maxHitCount = m_fractal->GetMaxHitCount();

  m_colorizer.SetMaxHitCount(maxHitCount);

  const size_t numPoints = points.size();
  const float tStep = numPoints == 1 ? 0.0F : (1.0F - 0.0F) / static_cast<float>(numPoints - 1);
  float t = -tStep;

  bool doneColorChange =
      m_colorizer.GetColorMode() != IfsDancersFx::ColorMode::MEGA_MAP_COLOR_CHANGE &&
      m_colorizer.GetColorMode() != IfsDancersFx::ColorMode::MEGA_MIX_COLOR_CHANGE;
  uint32_t maxLowDensityCount = 0;
  uint32_t numSelectedPoints = 0;
  std::vector<IfsPoint> lowDensityPoints{};

  for (size_t i = 0; i < numPoints; i += static_cast<size_t>(GetIfsIncr()))
  {
    t += tStep;

    const uint32_t x = points[i].x;
    const uint32_t y = points[i].y;
    if ((x >= m_goomInfo->GetScreenInfo().width) || (y >= m_goomInfo->GetScreenInfo().height))
    {
      continue;
    }

    if (!doneColorChange && MegaChangeColorMapEvent())
    {
      ChangeColormaps();
      doneColorChange = true;
    }

    numSelectedPoints++;
    DrawPoint(points[i], t);

    if (points[i].count <= m_lowDensityCount)
    {
      (void)lowDensityPoints.emplace_back(points[i]);
      if (maxLowDensityCount < points[i].count)
      {
        maxLowDensityCount = points[i].count;
      }
    }
  }

  if (!BlurLowDensityColors(numSelectedPoints, lowDensityPoints))
  {
    SetLowDensityColors(lowDensityPoints, maxLowDensityCount);
  }
  else
  {
    // Enough dense points to make blurring worthwhile.
    if (ProbabilityOfMInN(4, 5))
    {
      m_blurrer.SetNeighbourMixFactor(0.98F);
    }
    else
    {
      m_blurrer.SetNeighbourMixFactor(GetRandInRange(0.90F, 1.0F));
    }
    m_blurrer.DoBlur(lowDensityPoints, maxLowDensityCount);
  }
}

inline void IfsDancersFx::IfsDancersFxImpl::DrawPoint(const IfsPoint& point, const float tMix)
{
  const float fx =
      static_cast<float>(point.x) / static_cast<float>(m_goomInfo->GetScreenInfo().width);
  const float fy =
      static_cast<float>(point.y) / static_cast<float>(m_goomInfo->GetScreenInfo().height);

  //  const float t = static_cast<float>(m_cycle) / static_cast<float>(m_cycleLength);
  const float t = tMix;
  if (point.simi->currentPointBitmap == nullptr)
  {
    constexpr float BRIGHTNESS = 2.0;
    const Pixel mixedColor = m_colorizer.GetMixedColor(
        point.simi->colorMap->GetColor(t), point.count, BRIGHTNESS, false, tMix, fx, fy);
    const std::vector<Pixel> colors{mixedColor, mixedColor};
    m_draw->DrawPixels(static_cast<int32_t>(point.x), static_cast<int32_t>(point.y), colors);
  }
  else
  {
    constexpr float BRIGHTNESS = 0.07;
    const Pixel mixedColor = m_colorizer.GetMixedColor(point.simi->colorMap->GetColor(t),
                                                       point.count, BRIGHTNESS, true, tMix, fx, fy);
    const std::vector<Pixel> colors{mixedColor, mixedColor};
    const auto getColor1 = [&]([[maybe_unused]] const size_t x, [[maybe_unused]] const size_t y,
                               [[maybe_unused]] const Pixel& b) -> Pixel { return mixedColor; };
    const auto getColor2 = [&]([[maybe_unused]] const size_t x, [[maybe_unused]] const size_t y,
                               [[maybe_unused]] const Pixel& b) -> Pixel { return mixedColor; };
    const std::vector<IGoomDraw::GetBitmapColorFunc> getColors{getColor1, getColor2};
    const PixelBuffer& bitmap{*point.simi->currentPointBitmap};
    m_draw->Bitmap(static_cast<int32_t>(point.x), static_cast<int32_t>(point.y), bitmap, getColors);
  }
}

inline auto IfsDancersFx::IfsDancersFxImpl::BlurLowDensityColors(
    const size_t numPoints, const std::vector<IfsPoint>& lowDensityPoints) const -> bool
{
  if (numPoints == 0)
  {
    return false;
  }
  return static_cast<float>(lowDensityPoints.size()) / static_cast<float>(numPoints) >
         m_lowDensityBlurThreshold;
}

void IfsDancersFx::IfsDancersFxImpl::SetLowDensityColors(std::vector<IfsPoint>& points,
                                                         const uint32_t maxLowDensityCount) const
{
  const float logMaxLowDensityCount = std::log(static_cast<float>(maxLowDensityCount));

  float t = 0.0;
  const float tStep = 1.0F / static_cast<float>(points.size());
  for (const auto& point : points)
  {
    const float logAlpha =
        point.count <= 1 ? 1.0F : std::log(static_cast<float>(point.count)) / logMaxLowDensityCount;
    constexpr float BRIGHTNESS = 1.0;
    const Pixel color = m_lowDensityGammaCorrect.GetCorrection(BRIGHTNESS * logAlpha,
                                                               point.simi->colorMap->GetColor(t));
    m_draw->DrawPixelsUnblended(static_cast<int32_t>(point.x), static_cast<int32_t>(point.y),
                                {color, color});
    t += tStep;
  }
}

void IfsDancersFx::IfsDancersFxImpl::UpdateLowDensityThreshold()
{
  m_lowDensityCount = GetRandInRange(MIN_DENSITY_COUNT, MAX_DENSITY_COUNT);

  uint32_t blurWidth;
  constexpr uint32_t NUM_WIDTHS = 3;
  constexpr uint32_t WIDTH_RANGE = (MAX_DENSITY_COUNT - MIN_DENSITY_COUNT) / NUM_WIDTHS;
  if (m_lowDensityCount <= MIN_DENSITY_COUNT + WIDTH_RANGE)
  {
    blurWidth = 7;
  }
  else if (m_lowDensityCount <= MIN_DENSITY_COUNT + 2 * WIDTH_RANGE)
  {
    blurWidth = 5;
  }
  else
  {
    blurWidth = 3;
  }
  m_blurrer.SetWidth(blurWidth);
}

} // namespace GOOM
