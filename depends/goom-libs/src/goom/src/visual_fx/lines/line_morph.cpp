/*
 *  Goom
 *  Copyright (c) 2000-2003 iOS-software. All rights reserved.
 *
 *  - converted to C++17 2021-02-01 (glk)
 */

#include "line_morph.h"

//#undef NO_LOGGING

#include "color/color_maps.h"
#include "color/color_utils.h"
#include "color/random_color_maps.h"
#include "draw/goom_draw.h"
#include "logging.h"
#include "goom_config.h"
#include "goom_graphic.h"
#include "goom_plugin_info.h"
#include "point2d.h"
#include "sound_info.h"
#include "utils/enum_utils.h"
#include "utils/graphics/small_image_bitmaps.h"
#include "utils/math/goom_rand_base.h"
#include "utils/math/misc.h"

#include <cmath>
#include <cstdint>
#include <memory>
#include <vector>

namespace GOOM::VISUAL_FX::LINES
{

using COLOR::GetLightenedColor;
using COLOR::GetSimpleColor;
using COLOR::IColorMap;
using COLOR::RandomColorMaps;
using COLOR::SimpleColors;
using DRAW::IGoomDraw;
using DRAW::MultiplePixels;
using FX_UTILS::DotSizes;
using FX_UTILS::GetCircularLinePoints;
using FX_UTILS::GetHorizontalLinePoints;
using FX_UTILS::GetVerticalLinePoints;
using FX_UTILS::LinePoint;
using FX_UTILS::SmoothTheCircleJoinAtEnds;
using UTILS::Logging; // NOLINT(misc-unused-using-decls)
using UTILS::NUM;
using UTILS::GRAPHICS::SmallImageBitmaps;
using UTILS::MATH::FloatsEqual;
using UTILS::MATH::IGoomRand;
using UTILS::MATH::SMALL_FLOAT;

static constexpr auto MIN_DOT_SIZE01_WEIGHT = 100.0F;
static constexpr auto MIN_DOT_SIZE02_WEIGHT = 050.0F;
static constexpr auto MIN_DOT_SIZE03_WEIGHT = 020.0F;
static constexpr auto MIN_DOT_SIZE04_WEIGHT = 010.0F;

static constexpr auto NORMAL_DOT_SIZE01_WEIGHT = 50.0F;
static constexpr auto NORMAL_DOT_SIZE02_WEIGHT = 20.0F;
static constexpr auto NORMAL_DOT_SIZE03_WEIGHT = 20.0F;
static constexpr auto NORMAL_DOT_SIZE04_WEIGHT = 10.0F;
static constexpr auto NORMAL_DOT_SIZE05_WEIGHT = 10.0F;
static constexpr auto NORMAL_DOT_SIZE06_WEIGHT = 10.0F;
static constexpr auto NORMAL_DOT_SIZE07_WEIGHT = 10.0F;
static constexpr auto NORMAL_DOT_SIZE08_WEIGHT = 10.0F;

LineMorph::LineMorph(IGoomDraw& draw,
                     const PluginInfo& goomInfo,
                     const IGoomRand& goomRand,
                     const SmallImageBitmaps& smallBitmaps,
                     const LineParams& srceLineParams,
                     const LineParams& destLineParams) noexcept
  : m_draw{draw},
    m_goomInfo{goomInfo},
    m_goomRand{goomRand},
    m_srcePoints(AudioSamples::AUDIO_SAMPLE_LEN),
    m_srcePointsCopy(AudioSamples::AUDIO_SAMPLE_LEN),
    m_srceLineParams{srceLineParams},
    m_destPoints(AudioSamples::AUDIO_SAMPLE_LEN),
    m_destLineParams{destLineParams},
    m_dotDrawer{
        m_draw,
        m_goomRand,
        smallBitmaps,
        // min dot sizes
        {
            m_goomRand,
            {
                {DotSizes::DOT_SIZE01, MIN_DOT_SIZE01_WEIGHT},
                {DotSizes::DOT_SIZE02, MIN_DOT_SIZE02_WEIGHT},
                {DotSizes::DOT_SIZE03, MIN_DOT_SIZE03_WEIGHT},
                {DotSizes::DOT_SIZE04, MIN_DOT_SIZE04_WEIGHT},
            }
        },
        // normal dot sizes
        {
            m_goomRand,
            {
                {DotSizes::DOT_SIZE01, NORMAL_DOT_SIZE01_WEIGHT},
                {DotSizes::DOT_SIZE02, NORMAL_DOT_SIZE02_WEIGHT},
                {DotSizes::DOT_SIZE03, NORMAL_DOT_SIZE03_WEIGHT},
                {DotSizes::DOT_SIZE04, NORMAL_DOT_SIZE04_WEIGHT},
                {DotSizes::DOT_SIZE05, NORMAL_DOT_SIZE05_WEIGHT},
                {DotSizes::DOT_SIZE06, NORMAL_DOT_SIZE06_WEIGHT},
                {DotSizes::DOT_SIZE07, NORMAL_DOT_SIZE07_WEIGHT},
                {DotSizes::DOT_SIZE08, NORMAL_DOT_SIZE08_WEIGHT},
            }
        }
    }
{
}

auto LineMorph::GetRandomColorMap() const noexcept -> const IColorMap&
{
  Expects(m_colorMaps != nullptr);
  return m_colorMaps->GetRandomColorMap(m_colorMaps->GetRandomGroup());
}

auto LineMorph::Start() noexcept -> void
{
  UpdateColorInfo();

  m_srcePoints     = GetFreshLine(m_srceLineParams.lineType, m_srceLineParams.param);
  m_srcePointsCopy = m_srcePoints;

  ResetDestLine(m_destLineParams);
}

auto LineMorph::GetCurrentColorMapsNames() const noexcept -> std::vector<std::string>
{
  return {m_colorMaps->GetColorMapsName()};
}

auto LineMorph::SetWeightedColorMaps(
    const std::shared_ptr<const RandomColorMaps> weightedMaps) noexcept -> void
{
  m_colorMaps = weightedMaps;
  m_colorMapsManager.UpdateColorMapInfo(m_currentColorMapID,
                                        {m_colorMaps, RandomColorMaps::ALL_COLOR_MAP_TYPES});
}

inline auto LineMorph::UpdateColorInfo() noexcept -> void
{
  m_colorMapsManager.ChangeAllColorMapsNow();

  static constexpr auto PROB_USE_LINE_COLOR = 0.5F;
  m_useLineColor                            = m_goomRand.ProbabilityOf(PROB_USE_LINE_COLOR);
}

inline auto LineMorph::GetFreshLine(const LineType lineType, const float lineParam) const noexcept
    -> std::vector<LinePoint>
{
  switch (lineType)
  {
    case LineType::H_LINE:
      return GetHorizontalLinePoints(
          AudioSamples::AUDIO_SAMPLE_LEN, m_goomInfo.GetScreenWidth(), lineParam);
    case LineType::V_LINE:
      return GetVerticalLinePoints(
          AudioSamples::AUDIO_SAMPLE_LEN, m_goomInfo.GetScreenHeight(), lineParam);
    case LineType::CIRCLE:
      return GetCircularLinePoints(AudioSamples::AUDIO_SAMPLE_LEN,
                                   m_goomInfo.GetScreenWidth(),
                                   m_goomInfo.GetScreenHeight(),
                                   lineParam);
    default:
      FailFast();
      return {};
  }
}

auto LineMorph::MoveSrceLineCloserToDest() noexcept -> void
{
  m_lineLerpParam += LINE_LERP_INC;
  const auto t = std::min(1.0F, m_lineLerpParam);
  for (auto i = 0U; i < AudioSamples::AUDIO_SAMPLE_LEN; ++i)
  {
    m_srcePoints[i].point = lerp(m_srcePointsCopy[i].point, m_destPoints[i].point, t);
    m_srcePoints[i].angle = STD20::lerp(m_srcePointsCopy[i].angle, m_destPoints[i].angle, t);
  }
  if (m_lineLerpParam >= 1.0F)
  {
    m_srceLineParams.lineType            = m_destLineParams.lineType;
    static constexpr auto MIN_BRIGHTNESS = 2.5F;
    static constexpr auto MAX_BRIGHTNESS = 4.0F;
    m_currentBrightness = m_goomRand.GetRandInRange(MIN_BRIGHTNESS, MAX_BRIGHTNESS);
  }

  Ensures((m_srceLineParams.lineType != LineType::CIRCLE) or (m_lineLerpParam < 1.0F) or
          (FloatsEqual(m_srcePoints[0].point.x,
                       m_srcePoints[AudioSamples::AUDIO_SAMPLE_LEN - 1].point.x) and
           FloatsEqual(m_srcePoints[0].point.y,
                       m_srcePoints[AudioSamples::AUDIO_SAMPLE_LEN - 1].point.y)));

  static constexpr auto COLOR_MIX_AMOUNT = 1.0F / 64.0F;
  m_srceLineParams.color =
      IColorMap::GetColorMix(m_srceLineParams.color, m_destLineParams.color, COLOR_MIX_AMOUNT);

  static constexpr auto MIN_POW_INC = 0.03F;
  static constexpr auto MAX_POW_INC = 0.10F;
  static constexpr auto MIN_POWER   = 1.1F;
  static constexpr auto MAX_POWER   = 17.5F;
  m_lineColorPower += m_lineColorPowerIncrement;
  if (m_lineColorPower < MIN_POWER)
  {
    m_lineColorPower          = MIN_POWER;
    m_lineColorPowerIncrement = m_goomRand.GetRandInRange(MIN_POW_INC, MAX_POW_INC);
  }
  if (m_lineColorPower > MAX_POWER)
  {
    m_lineColorPower          = MAX_POWER;
    m_lineColorPowerIncrement = -m_goomRand.GetRandInRange(MIN_POW_INC, MAX_POW_INC);
  }

  static constexpr auto AMP_MIX_AMOUNT = 0.01F;
  m_srceLineParams.amplitude =
      STD20::lerp(m_srceLineParams.amplitude, m_destLineParams.amplitude, AMP_MIX_AMOUNT);
}

auto LineMorph::ResetDestLine(const LineParams& newParams) noexcept -> void
{
  UpdateColorInfo();

  m_destPoints     = GetFreshLine(newParams.lineType, m_destLineParams.param);
  m_destLineParams = newParams;

  m_lineLerpParam = 0.0;

  static constexpr auto MIN_BRIGHTNESS = 1.5F;
  static constexpr auto MAX_BRIGHTNESS = 3.0F;
  m_currentBrightness                  = m_goomRand.GetRandInRange(MIN_BRIGHTNESS, MAX_BRIGHTNESS);

  m_dotDrawer.ChangeDotSizes();

  m_maxNormalizedPeak = m_goomRand.GetRandInRange(MIN_MAX_NORMALIZED_PEAK, MAX_MAX_NORMALIZED_PEAK);

  m_srcePointsCopy = m_srcePoints;
}

auto LineMorph::GetRandomLineColor() const noexcept -> Pixel
{
  if (static constexpr auto PROB_LINE_COLOR = 0.02F; m_goomRand.ProbabilityOf(PROB_LINE_COLOR))
  {
    return GetSimpleColor(static_cast<SimpleColors>(m_goomRand.GetNRand(NUM<SimpleColors>)));
  }
  return RandomColorMaps::GetRandomColor(m_goomRand, GetRandomColorMap(), 0.0F, 1.0F);
}

inline auto LineMorph::GetFinalLineColor(const Pixel& color) const noexcept -> Pixel
{
  return GetLightenedColor(color, m_lineColorPower);
}

auto LineMorph::DrawLines(const AudioSamples::SampleArray& soundData,
                          const AudioSamples::MinMaxValues& soundMinMax) noexcept -> void
{
  static constexpr auto LAST_POINT_INDEX = AudioSamples::AUDIO_SAMPLE_LEN - 1;
  UNUSED_FOR_NDEBUG(LAST_POINT_INDEX);

  Expects((m_srceLineParams.lineType != LineType::CIRCLE) or (m_lineLerpParam < 1.0F) or
          (FloatsEqual(m_srcePoints[0].point.x, m_srcePoints[LAST_POINT_INDEX].point.x) and
           FloatsEqual(m_srcePoints[0].point.y, m_srcePoints[LAST_POINT_INDEX].point.y)));

  const auto lineColor = GetFinalLineColor(m_srceLineParams.color);

  m_audioRange = soundMinMax.maxVal - soundMinMax.minVal;
  assert(m_audioRange >= 0.0F);
  m_minAudioValue = soundMinMax.minVal;

  if (m_audioRange < SMALL_FLOAT)
  {
    // No range - flatline audio
    DrawFlatLine(lineColor);
    MoveSrceLineCloserToDest();
    return;
  }

  static constexpr auto LINE_THICKNESS = 1U;
  const auto audioPoints               = GetAudioPoints(lineColor, soundData);

  auto point1 = audioPoints[0].point;

  for (auto i = 1U; i < audioPoints.size(); ++i)
  {
    const auto& nextPointData = audioPoints[i];

    const auto point2 = nextPointData.point;
    const auto colors = MultiplePixels{lineColor, nextPointData.color};

    m_draw.Line(point1, point2, colors, LINE_THICKNESS);

    static constexpr auto DOT_BRIGHTNESS = 1.5F;
    m_dotDrawer.DrawDot(point2, colors, DOT_BRIGHTNESS);

    point1 = point2;
  }

  MoveSrceLineCloserToDest();

  m_dotDrawer.ChangeDotSizes();
}

auto LineMorph::DrawFlatLine(const Pixel& lineColor) noexcept -> void
{
  const auto& pt0   = m_srcePoints[0];
  const auto& ptN   = m_srcePoints[AudioSamples::AUDIO_SAMPLE_LEN - 1];
  const auto colors = MultiplePixels{lineColor, lineColor};

  m_draw.Line(pt0.point.ToInt(), ptN.point.ToInt(), colors, 1);
}

auto LineMorph::GetAudioPoints(const Pixel& lineColor,
                               const AudioSamples::SampleArray& audioData) const noexcept
    -> std::vector<PointAndColor>
{
  const auto randColor = GetRandomLineColor();

  static constexpr auto T_STEP    = 1.0F / static_cast<float>(AudioSamples::AUDIO_SAMPLE_LEN - 1);
  static constexpr auto HALFWAY_T = 0.5F;
  auto currentTStep               = T_STEP;
  auto t                          = 0.0F;

  auto audioPoints = std::vector<PointAndColor>{};
  audioPoints.reserve(audioData.size());

  for (auto i = 0U; i < audioData.size(); ++i)
  {
    audioPoints.emplace_back(
        GetNextPointData(m_srcePoints[i], GetMainColor(lineColor, t), randColor, audioData[i]));

    if (t >= HALFWAY_T)
    {
      currentTStep = -T_STEP;
    }
    t += currentTStep;
  }

  if ((m_srceLineParams.lineType == LineType::CIRCLE) and (m_lineLerpParam >= 1.0F))
  {
    // This is a complete circle -- lerp the last few points to nicely join back to start.
    static constexpr auto NUM_POINTS_TO_LERP = 50U;
    SmoothTheCircleJoinAtEnds(audioPoints, NUM_POINTS_TO_LERP);
  }

  return audioPoints;
}

auto LineMorph::GetNextPointData(const LinePoint& linePoint,
                                 const Pixel& mainColor,
                                 const Pixel& randColor,
                                 const float dataVal) const noexcept -> PointAndColor
{
  Expects(m_goomInfo.GetSoundEvents().GetSoundInfo().GetAllTimesMinVolume() <=
          (dataVal + SMALL_FLOAT));
  Expects(m_minAudioValue <= (dataVal + SMALL_FLOAT));
  Expects(dataVal <= ((m_minAudioValue + m_audioRange) + SMALL_FLOAT));

  const auto tData = (dataVal - m_minAudioValue) / m_audioRange;
  assert((0.0F <= tData) && (tData <= 1.0F));

  const auto cosAngle          = std::cos(linePoint.angle);
  const auto sinAngle          = std::sin(linePoint.angle);
  const auto normalizedDataVal = m_maxNormalizedPeak * tData;
  assert(normalizedDataVal >= 0.0F);
  // TODO - Is 'm_srceLineParams.amplitude' the right abstraction level?
  const auto nextPointData =
      Point2dInt{static_cast<int32_t>(linePoint.point.x +
                                      (m_srceLineParams.amplitude * cosAngle * normalizedDataVal)),
                 static_cast<int32_t>(linePoint.point.y +
                                      (m_srceLineParams.amplitude * sinAngle * normalizedDataVal))};

  const auto brightness = m_currentBrightness * tData;
  const auto modColor =
      m_colorAdjust.GetAdjustment(brightness, IColorMap::GetColorMix(mainColor, randColor, tData));

  return {nextPointData, modColor};
}

inline auto LineMorph::GetMainColor(const Pixel& lineColor, const float t) const noexcept -> Pixel
{
  if (m_useLineColor)
  {
    return lineColor;
  }
  return m_colorMapsManager.GetColorMap(m_currentColorMapID).GetColor(t);
}

} // namespace GOOM::VISUAL_FX::LINES
