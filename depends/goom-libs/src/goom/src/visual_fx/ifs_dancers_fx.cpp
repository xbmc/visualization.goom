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
 * If this mode is weird, and you have an old MetroX server, it is buggy.
 * There is a free SuSE-enhanced MetroX X server that is fine.
 *
 * When shown ifs, Diana Rose (4 years old) said, "It looks like dancing."
 *
 * Revision History:
 * 01-Feb-2021: converted to C++17, lots of color changes (glk)
 * 13-Dec-2003: Added some goom specific stuffs (to make ifs a VisualFX).
 * 11-Apr-2002: jeko@ios-software.com: Make ifs.c system-independent. (ifs.h added)
 * 01-Nov-2000: Allocation checks
 * 10-May-1997: jwz@jwz.org: turned into a standalone program.
 *              Made it render into an off-screen bitmap and then copy
 *              that onto the screen, to reduce flicker.
 */

#include "ifs_dancers_fx.h"

//#undef NO_LOGGING

#include "color/random_color_maps.h"
#include "draw/goom_draw.h"
#include "fx_helper.h"
#include "goom_graphic.h"
#include "goom_plugin_info.h"
#include "ifs/colorizer.h"
#include "ifs/fractal.h"
#include "ifs/low_density_blurrer.h"
#include "logging.h"
#include "spimpl.h"
#include "utils/graphics/small_image_bitmaps.h"
#include "utils/math/goom_rand_base.h"
#include "utils/propagate_const.h"
#include "utils/t_values.h"

#include <array>
#include <cmath>
#include <cstdint>
#include <memory>
#include <vector>

namespace GOOM::VISUAL_FX
{

using COLOR::RandomColorMaps;
using DRAW::IGoomDraw;
using IFS::BlurrerColorMode;
using IFS::Colorizer;
using IFS::Fractal;
using IFS::IfsPoint;
using IFS::LowDensityBlurrer;
using std::experimental::propagate_const;
using UTILS::Logging; // NOLINT(misc-unused-using-decls)
using UTILS::TValue;
using UTILS::GRAPHICS::SmallImageBitmaps;
using UTILS::MATH::IGoomRand;
using UTILS::MATH::Weights;

class IfsDancersFx::IfsDancersFxImpl
{
public:
  IfsDancersFxImpl(const FxHelper& fxHelper, const SmallImageBitmaps& smallBitmaps) noexcept;

  auto ApplyNoDraw() -> void;
  auto UpdateIfs() -> void;
  auto UpdateLowDensityThreshold() -> void;
  auto Refresh() -> void;

  [[nodiscard]] auto GetCurrentColorMapsNames() const noexcept -> std::vector<std::string>;
  auto SetWeightedColorMaps(const WeightedColorMaps& weightedColorMaps) noexcept -> void;
  auto PostStateUpdate(bool wasActiveInPreviousState) -> void;

  auto Start() -> void;

private:
  static constexpr int32_t MIN_CYCLE_LENGTH = 1000;
  static constexpr int32_t MAX_CYCLE_LENGTH = 2000;
  int32_t m_cycleLength                     = MIN_CYCLE_LENGTH;

  IGoomDraw& m_draw;
  const PluginInfo& m_goomInfo;
  const IGoomRand& m_goomRand;

  Colorizer m_colorizer{m_goomRand};

  propagate_const<std::unique_ptr<Fractal>> m_fractal{};

  auto InitFractal() -> void;

  int32_t m_cycle    = 0;
  int32_t m_ifsIncr  = 1; // dessiner l'ifs (0 = non: > = increment)
  int32_t m_decayIfs = 0; // disparition de l'ifs
  int32_t m_recayIfs = 0; // dedisparition de l'ifs
  auto UpdateIncr() -> void;
  auto UpdateCycle() -> void;
  auto UpdateDecay() -> void;
  auto UpdateDecayAndRecay() -> void;
  auto Renew() -> void;

  // TODO(glk) Move to simi
  static constexpr auto T_MIX_STARTING_VALUE = 0.01F;
  TValue m_tMix{TValue::StepType::CONTINUOUS_REVERSIBLE, T_MIX_STARTING_VALUE};
  static constexpr auto POINT_BRIGHTNESS  = 3.0F;
  static constexpr auto BITMAP_BRIGHTNESS = 2.0F;
  auto ChangeColorMaps() -> void;
  auto ChangeSpeed() -> void;
  auto DrawNextIfsPoints() -> void;
  auto DrawPoint(float t, const IfsPoint& ifsPoint, float tMix) const -> void;

  static constexpr float PROB_DRAW_LOW_DENSITY_POINTS = 0.1F;
  bool m_drawLowDensityPoints                         = false;
  static constexpr uint32_t MAX_DENSITY_COUNT         = 20;
  static constexpr uint32_t MIN_DENSITY_COUNT         = 5;
  uint32_t m_lowDensityCount                          = MIN_DENSITY_COUNT;
  LowDensityBlurrer m_blurrer;
  static constexpr uint32_t BLUR_WIDTH                     = 3;
  static constexpr auto DEFAULT_LOW_DENSITY_BLUR_THRESHOLD = 0.99F;
  float m_lowDensityBlurThreshold                          = DEFAULT_LOW_DENSITY_BLUR_THRESHOLD;
  auto DrawLowDensityPoints(size_t numPointsAlreadyDrawn, const std::vector<IfsPoint>& points)
      -> void;
  [[nodiscard]] auto BlurTheLowDensityPoints(size_t numPointsAlreadyDrawn,
                                             const std::vector<IfsPoint>& lowDensityPoints) const
      -> bool;
  auto DrawLowDensityPointsWithoutBlur(const std::vector<IfsPoint>& lowDensityPoints,
                                       uint32_t maxLowDensityCount) const -> void;
  auto DrawLowDensityPointsWithBlur(std::vector<IfsPoint>& lowDensityPoints,
                                    uint32_t maxLowDensityCount) -> void;
  auto UpdateLowDensityBlurThreshold() -> void;
  [[nodiscard]] auto GetNewBlurWidth() const -> uint32_t;

  [[nodiscard]] auto MegaChangeColorMapEvent() const -> bool;
  [[nodiscard]] auto IfsRenewEvent() const -> bool;
  const Weights<BlurrerColorMode> m_blurrerColorModeWeights;
};

IfsDancersFx::IfsDancersFx(const FxHelper& fxHelper, const SmallImageBitmaps& smallBitmaps) noexcept
  : m_pimpl{spimpl::make_unique_impl<IfsDancersFxImpl>(fxHelper, smallBitmaps)}
{
}

auto IfsDancersFx::GetFxName() const noexcept -> std::string
{
  return "IFS FX";
}

auto IfsDancersFx::GetCurrentColorMapsNames() const noexcept -> std::vector<std::string>
{
  return m_pimpl->GetCurrentColorMapsNames();
}

auto IfsDancersFx::SetWeightedColorMaps(const WeightedColorMaps& weightedColorMaps) noexcept -> void
{
  m_pimpl->SetWeightedColorMaps(weightedColorMaps);
}

auto IfsDancersFx::Start() noexcept -> void
{
  m_pimpl->Start();
}

auto IfsDancersFx::Finish() noexcept -> void
{
  // nothing to do
}

auto IfsDancersFx::Resume() noexcept -> void
{
  // nothing to do
}

auto IfsDancersFx::Suspend() noexcept -> void
{
  // nothing to do
}

auto IfsDancersFx::ApplyNoDraw() noexcept -> void
{
  m_pimpl->ApplyNoDraw();
}

auto IfsDancersFx::ApplyMultiple() noexcept -> void
{
  m_pimpl->UpdateIfs();
}

auto IfsDancersFx::Refresh() noexcept -> void
{
  m_pimpl->Refresh();
}

auto IfsDancersFx::PostStateUpdate(const bool wasActiveInPreviousState) noexcept -> void
{
  m_pimpl->PostStateUpdate(wasActiveInPreviousState);
}

static constexpr auto BLURRER_COLOR_MODE_SMOOTH_WITH_NEIGHBOURS_WEIGHT = 999.0F;
static constexpr auto BLURRER_COLOR_MODE_SMOOTH_NO_NEIGHBOURS_WEIGHT   = 001.0F;
static constexpr auto BLURRER_COLOR_MODE_SIMI_WITH_NEIGHBOURS_WEIGHT   = 001.0F;
static constexpr auto BLURRER_COLOR_MODE_SIMI_NO_NEIGHBOURS_WEIGHT     = 005.0F;
static constexpr auto BLURRER_COLOR_MODE_SINGLE_WITH_NEIGHBOURS_WEIGHT = 001.0F;
static constexpr auto BLURRER_COLOR_MODE_SINGLE_NO_NEIGHBOURS_WEIGHT   = 005.0F;

IfsDancersFx::IfsDancersFxImpl::IfsDancersFxImpl(const FxHelper& fxHelper,
                                                 const SmallImageBitmaps& smallBitmaps) noexcept
  : m_draw{fxHelper.GetDraw()},
    m_goomInfo{fxHelper.GetGoomInfo()},
    m_goomRand{fxHelper.GetGoomRand()},
    m_fractal{std::make_unique<Fractal>(m_draw.GetScreenDimensions(),
                                        m_goomRand,
                                        smallBitmaps)},
    m_blurrer{m_draw, m_goomRand, BLUR_WIDTH, &m_colorizer, smallBitmaps},
    m_blurrerColorModeWeights{
      m_goomRand,
      {
        {BlurrerColorMode::SMOOTH_WITH_NEIGHBOURS, BLURRER_COLOR_MODE_SMOOTH_WITH_NEIGHBOURS_WEIGHT},
        {BlurrerColorMode::SMOOTH_NO_NEIGHBOURS,   BLURRER_COLOR_MODE_SMOOTH_NO_NEIGHBOURS_WEIGHT},
        {BlurrerColorMode::SIMI_WITH_NEIGHBOURS,   BLURRER_COLOR_MODE_SIMI_WITH_NEIGHBOURS_WEIGHT},
        {BlurrerColorMode::SIMI_NO_NEIGHBOURS,     BLURRER_COLOR_MODE_SIMI_NO_NEIGHBOURS_WEIGHT},
        {BlurrerColorMode::SINGLE_WITH_NEIGHBOURS, BLURRER_COLOR_MODE_SINGLE_WITH_NEIGHBOURS_WEIGHT},
        {BlurrerColorMode::SINGLE_NO_NEIGHBOURS,   BLURRER_COLOR_MODE_SINGLE_NO_NEIGHBOURS_WEIGHT},
    }}
{
}

inline auto IfsDancersFx::IfsDancersFxImpl::MegaChangeColorMapEvent() const -> bool
{
  static constexpr auto PROB_MEGA_CHANGE_COLOR_MAP_EVENT = 0.5F;
  return m_goomRand.ProbabilityOf(PROB_MEGA_CHANGE_COLOR_MAP_EVENT);
}

inline auto IfsDancersFx::IfsDancersFxImpl::IfsRenewEvent() const -> bool
{
  static constexpr auto PROB_IFS_RENEW_EVENT = 2.0F / 3.0F;
  return m_goomRand.ProbabilityOf(PROB_IFS_RENEW_EVENT);
}

inline auto IfsDancersFx::IfsDancersFxImpl::InitFractal() -> void
{
  m_fractal->Init();
  UpdateLowDensityThreshold();
}

inline auto IfsDancersFx::IfsDancersFxImpl::GetCurrentColorMapsNames() const noexcept
    -> std::vector<std::string>
{
  return {m_colorizer.GetWeightedColorMaps()->GetColorMapsName()};
}

inline auto IfsDancersFx::IfsDancersFxImpl::SetWeightedColorMaps(
    const WeightedColorMaps& weightedColorMaps) noexcept -> void
{
  Expects(weightedColorMaps.mainColorMaps != nullptr);

  m_fractal->SetWeightedColorMaps(weightedColorMaps.mainColorMaps);
  m_colorizer.SetWeightedColorMaps(weightedColorMaps.mainColorMaps);
}

inline auto IfsDancersFx::IfsDancersFxImpl::Start() -> void
{
  InitFractal();
}

inline auto IfsDancersFx::IfsDancersFxImpl::PostStateUpdate(const bool wasActiveInPreviousState)
    -> void
{
  if (!wasActiveInPreviousState)
  {
    InitFractal();
  }

  UpdateIncr();

  if (IfsRenewEvent())
  {
    Renew();
  }
}

inline auto IfsDancersFx::IfsDancersFxImpl::Refresh() -> void
{
  Renew();
}

inline auto IfsDancersFx::IfsDancersFxImpl::Renew() -> void
{
  ChangeColorMaps();
  m_colorizer.ChangeColorMode();

  ChangeSpeed();
}

inline auto IfsDancersFx::IfsDancersFxImpl::ChangeSpeed() -> void
{
  static constexpr auto MIN_SPEED_AMP    = 1.1F;
  static constexpr auto MAX_SPEED_AMP    = 5.1F;
  static constexpr auto MAX_SPEED_WEIGHT = 10.0F;
  const auto speedAmp =
      std::min(m_goomRand.GetRandInRange(MIN_SPEED_AMP, MAX_SPEED_WEIGHT), MAX_SPEED_AMP);
  const auto accelFactor =
      1.0F / (1.1F - m_goomInfo.GetSoundEvents().GetSoundInfo().GetAcceleration());

  m_fractal->SetSpeed(std::max(1U, static_cast<uint32_t>(speedAmp * accelFactor)));
}

auto IfsDancersFx::IfsDancersFxImpl::ChangeColorMaps() -> void
{
  m_colorizer.ChangeColorMaps();

  m_drawLowDensityPoints = m_goomRand.ProbabilityOf(PROB_DRAW_LOW_DENSITY_POINTS);

  if (m_drawLowDensityPoints)
  {
    m_blurrer.SetColorMode(m_blurrerColorModeWeights.GetRandomWeighted());
    static constexpr auto SINGLE_COLOR_T = 0.5F;
    m_blurrer.SetSingleColor(
        m_colorizer.GetColorMaps().GetRandomColorMap().GetColor(SINGLE_COLOR_T));
  }
}

inline auto IfsDancersFx::IfsDancersFxImpl::ApplyNoDraw() -> void
{
  UpdateDecayAndRecay();
  UpdateDecay();
}

auto IfsDancersFx::IfsDancersFxImpl::UpdateIfs() -> void
{
  UpdateDecayAndRecay();
  if (m_ifsIncr <= 0)
  {
    return;
  }

  UpdateCycle();

  DrawNextIfsPoints();
}

auto IfsDancersFx::IfsDancersFxImpl::UpdateDecayAndRecay() -> void
{
  static constexpr auto BY_TWO = 2;

  --m_decayIfs;
  if (m_decayIfs > 0)
  {
    m_ifsIncr += BY_TWO;
  }
  if (0 == m_decayIfs)
  {
    m_ifsIncr = 0;
  }

  if (m_recayIfs)
  {
    m_ifsIncr -= BY_TWO;
    --m_recayIfs;
    if ((0 == m_recayIfs) && (m_ifsIncr <= 0))
    {
      m_ifsIncr = 1;
    }
  }
}

inline auto IfsDancersFx::IfsDancersFxImpl::UpdateIncr() -> void
{
  if (m_ifsIncr <= 0)
  {
    static constexpr auto NEW_RECAY_IFS = 5;
    m_recayIfs                          = NEW_RECAY_IFS;
    static constexpr auto NEW_IFS_INCR  = 11;
    m_ifsIncr                           = NEW_IFS_INCR;
    Renew();
  }
}

inline auto IfsDancersFx::IfsDancersFxImpl::UpdateDecay() -> void
{
  if ((m_ifsIncr > 0) && (m_decayIfs <= 0))
  {
    static constexpr auto NEW_DECAY_IFS = 100;
    m_decayIfs                          = NEW_DECAY_IFS;
  }
}

inline auto IfsDancersFx::IfsDancersFxImpl::UpdateCycle() -> void
{
  // TODO(glk): trouver meilleur soluce pour increment (mettre le code de gestion de l'ifs
  //            dans ce fichier)
  //            find the best solution for increment (put the management code of the ifs
  //            in this file)
  m_tMix.Increment();

  ++m_cycle;
  if (m_cycle < m_cycleLength)
  {
    return;
  }

  m_cycle       = 0;
  m_cycleLength = m_goomRand.GetRandInRange(MIN_CYCLE_LENGTH, MAX_CYCLE_LENGTH + 1);

  UpdateLowDensityBlurThreshold();

  m_fractal->Reset();

  Renew();
}

inline auto IfsDancersFx::IfsDancersFxImpl::UpdateLowDensityBlurThreshold() -> void
{
  static constexpr auto PROB_HIGH_BLUR_THRESHOLD = 0.75F;
  static constexpr auto HIGH_BLUR_THRESHOLD      = 0.99F;
  static constexpr auto LOW_BLUR_THRESHOLD       = 0.40F;
  m_lowDensityBlurThreshold =
      m_goomRand.ProbabilityOf(PROB_HIGH_BLUR_THRESHOLD) ? HIGH_BLUR_THRESHOLD : LOW_BLUR_THRESHOLD;
}

auto IfsDancersFx::IfsDancersFxImpl::DrawNextIfsPoints() -> void
{
  m_colorizer.SetMaxHitCount(m_fractal->GetMaxHitCount());

  const auto& points   = m_fractal->GetNextIfsPoints();
  const auto numPoints = points.size();
  const auto tStep = (1 == numPoints) ? 0.0F : ((1.0F - 0.0F) / static_cast<float>(numPoints - 1));
  auto t           = -tStep;

  auto doneColorChange =
      (m_colorizer.GetColorMode() != IfsDancersFx::ColorMode::MEGA_MAP_COLOR_CHANGE) &&
      (m_colorizer.GetColorMode() != IfsDancersFx::ColorMode::MEGA_MIX_COLOR_CHANGE);
  auto numPointsDrawn = 0U;

  for (auto i = 0U; i < numPoints; i += static_cast<uint32_t>(m_ifsIncr))
  {
    const auto& point = points[i];

    t += tStep;

    if ((not doneColorChange) and MegaChangeColorMapEvent())
    {
      ChangeColorMaps();
      doneColorChange = true;
    }

    DrawPoint(t, point, m_tMix());

    ++numPointsDrawn;
  }

  DrawLowDensityPoints(numPointsDrawn, points);
}

auto IfsDancersFx::IfsDancersFxImpl::DrawPoint(const float t,
                                               const IfsPoint& ifsPoint,
                                               const float tMix) const -> void
{
  const auto point =
      Point2dInt{static_cast<int32_t>(ifsPoint.GetX()), static_cast<int32_t>(ifsPoint.GetY())};

  const auto tX = static_cast<float>(point.x) / static_cast<float>(m_draw.GetScreenWidth());
  const auto tY = static_cast<float>(point.y) / static_cast<float>(m_draw.GetScreenHeight());

  if (const auto baseColor = ifsPoint.GetSimi()->GetColorMap()->GetColor(t);
      nullptr == ifsPoint.GetSimi()->GetCurrentPointBitmap())
  {
    const auto mixedColor =
        m_colorizer.GetMixedColor(baseColor, ifsPoint.GetCount(), POINT_BRIGHTNESS, tMix, tX, tY);
    m_draw.DrawPixels(point, {mixedColor, mixedColor});
  }
  else
  {
    const auto mixedColor =
        m_colorizer.GetMixedColor(baseColor, ifsPoint.GetCount(), BITMAP_BRIGHTNESS, tMix, tX, tY);
    const auto getColor = [&mixedColor]([[maybe_unused]] const size_t x,
                                        [[maybe_unused]] const size_t y,
                                        [[maybe_unused]] const Pixel& bgnd) { return mixedColor; };
    const auto& bitmap{*ifsPoint.GetSimi()->GetCurrentPointBitmap()};
    m_draw.Bitmap(point, bitmap, {getColor, getColor});
  }
}

inline auto IfsDancersFx::IfsDancersFxImpl::DrawLowDensityPoints(
    const size_t numPointsAlreadyDrawn, const std::vector<IfsPoint>& points) -> void
{
  if (not m_drawLowDensityPoints)
  {
    return;
  }

  const auto numPoints = points.size();
  auto maxLowDensityCount = 0U;
  auto lowDensityPoints   = std::vector<IfsPoint>{};

  for (auto i = 0U; i < numPoints; i += static_cast<uint32_t>(m_ifsIncr))
  {
    const auto& point = points[i];

    if (point.GetCount() > m_lowDensityCount)
    {
      continue;
    }

    lowDensityPoints.emplace_back(point);

    if (maxLowDensityCount < point.GetCount())
    {
      maxLowDensityCount = point.GetCount();
    }
  }

  if (BlurTheLowDensityPoints(numPointsAlreadyDrawn, lowDensityPoints))
  {
    DrawLowDensityPointsWithBlur(lowDensityPoints, maxLowDensityCount);
  }
  else
  {
    DrawLowDensityPointsWithoutBlur(lowDensityPoints, maxLowDensityCount);
  }
}

inline auto IfsDancersFx::IfsDancersFxImpl::BlurTheLowDensityPoints(
    const size_t numPointsAlreadyDrawn, const std::vector<IfsPoint>& lowDensityPoints) const -> bool
{
  if (0 == numPointsAlreadyDrawn)
  {
    return false;
  }
  return (static_cast<float>(lowDensityPoints.size()) / static_cast<float>(numPointsAlreadyDrawn)) >
         m_lowDensityBlurThreshold;
}

inline auto IfsDancersFx::IfsDancersFxImpl::DrawLowDensityPointsWithoutBlur(
    const std::vector<IfsPoint>& lowDensityPoints, const uint32_t maxLowDensityCount) const -> void
{
  const auto logMaxLowDensityCount = std::log(static_cast<float>(maxLowDensityCount));

  auto t           = 0.0F;
  const auto tStep = 1.0F / static_cast<float>(lowDensityPoints.size());
  for (const auto& point : lowDensityPoints)
  {
    const auto logAlpha =
        point.GetCount() <= 1
            ? 1.0F
            : (std::log(static_cast<float>(point.GetCount())) / logMaxLowDensityCount);

    DrawPoint(t, point, logAlpha);

    t += tStep;
  }
}

inline auto IfsDancersFx::IfsDancersFxImpl::DrawLowDensityPointsWithBlur(
    std::vector<IfsPoint>& lowDensityPoints, const uint32_t maxLowDensityCount) -> void
{
  if (static constexpr auto PROB_FIXED_MIX_FACTOR = 0.8F;
      m_goomRand.ProbabilityOf(PROB_FIXED_MIX_FACTOR))
  {
    static constexpr auto FIXED_MIX_FACTOR = 0.98F;
    m_blurrer.SetNeighbourMixFactor(FIXED_MIX_FACTOR);
  }
  else
  {
    static constexpr auto MIN_MIX_FACTOR = 0.9F;
    static constexpr auto MAX_MIX_FACTOR = 1.0F;
    m_blurrer.SetNeighbourMixFactor(m_goomRand.GetRandInRange(MIN_MIX_FACTOR, MAX_MIX_FACTOR));
  }

  m_blurrer.DoBlur(lowDensityPoints, maxLowDensityCount);
}

inline auto IfsDancersFx::IfsDancersFxImpl::UpdateLowDensityThreshold() -> void
{
  m_lowDensityCount = m_goomRand.GetRandInRange(MIN_DENSITY_COUNT, MAX_DENSITY_COUNT);

  m_blurrer.SetWidth(GetNewBlurWidth());
}

inline auto IfsDancersFx::IfsDancersFxImpl::GetNewBlurWidth() const -> uint32_t
{
  static constexpr auto NUM_WIDTHS         = 3U;
  static constexpr auto WIDTH_RANGE        = (MAX_DENSITY_COUNT - MIN_DENSITY_COUNT) / NUM_WIDTHS;
  static constexpr auto DOUBLE_WIDTH_RANGE = 2 * WIDTH_RANGE;

  static constexpr auto LARGE_BLUR_WIDTH  = 7U;
  static constexpr auto MEDIUM_BLUR_WIDTH = 5U;
  static constexpr auto SMALL_BLUR_WIDTH  = 3U;

  auto blurWidth = SMALL_BLUR_WIDTH;

  if (m_lowDensityCount <= (MIN_DENSITY_COUNT + WIDTH_RANGE))
  {
    blurWidth = LARGE_BLUR_WIDTH;
  }
  else if (m_lowDensityCount <= (MIN_DENSITY_COUNT + DOUBLE_WIDTH_RANGE))
  {
    blurWidth = MEDIUM_BLUR_WIDTH;
  }

  return blurWidth;
}

} // namespace GOOM::VISUAL_FX
