/*
 *  Goom
 *  Copyright (c) 2000-2003 iOS-software. All rights reserved.
 *
 *	- converted to C++14 2021-02-01 (glk)
 */

#include "lines_fx.h"

#include "goom_config.h"
#include "goom_draw.h"
#include "goom_graphic.h"
#include "goom_plugin_info.h"
#include "goom_stats.h"
#include "goomutils/colormaps.h"
#include "goomutils/colorutils.h"
#include "goomutils/goomrand.h"
#include "goomutils/graphics/image_bitmaps.h"
#include "goomutils/graphics/small_image_bitmaps.h"
#include "goomutils/logging_control.h"
#undef NO_LOGGING
#include "goomutils/logging.h"
#include "goomutils/mathutils.h"
#include "goomutils/random_colormaps.h"
#include "sound_info.h"
#include "stats/line_stats.h"
#include "v2d.h"

#undef NDEBUG
#include <cassert>
#include <cmath>
#include <cstdint>
#include <memory>
#include <stdexcept>
#include <tuple>
#include <utility>
#include <vector>

namespace GOOM
{

using namespace UTILS;
using UTILS::floats_equal;
using UTILS::SMALL_FLOAT;

constexpr float MIN_MAX_NORMALIZED_PEAK = 10.0F;
constexpr float MAX_MAX_NORMALIZED_PEAK = 150.0F;

class LinesFx::LinesImpl
{
public:
  ~LinesImpl() noexcept = default;
  // construit un effet de line (une ligne horitontale pour commencer)
  LinesImpl(const IGoomDraw* draw,
            std::shared_ptr<const PluginInfo> goomInfo,
            LineType srceLineType,
            float srceParam,
            const Pixel& srceColor,
            LineType destLineType,
            float destParam,
            const Pixel& destColor);
  LinesImpl(const LinesImpl&) noexcept = delete;
  LinesImpl(LinesImpl&&) noexcept = delete;
  auto operator=(const LinesImpl&) -> LinesImpl& = delete;
  auto operator=(LinesImpl&&) -> LinesImpl& = delete;

  [[nodiscard]] auto GetResourcesDirectory() const -> const std::string&;
  void SetResourcesDirectory(const std::string& dirName);

  void SetSmallImageBitmaps(const SmallImageBitmaps& smallBitmaps);
  void SetWeightedColorMaps(std::shared_ptr<UTILS::RandomColorMaps> weightedMaps);

  void Start();

  auto GetRandomLineColor() const -> Pixel;

  [[nodiscard]] auto GetPower() const -> float;
  void SetPower(float val);

  [[nodiscard]] auto CanResetDestLine() const -> bool;

  void ResetDestLine(LineType newLineType,
                     float newParam,
                     float newAmplitude,
                     const Pixel& newColor);

  void DrawLines(const std::vector<int16_t>& soundData,
                 const AudioSamples::MaxMinValues& soundMinMax);

  void Log(const GoomStats::LogStatsValueFunc& l) const;
  void Finish();

private:
  const IGoomDraw* const m_draw;
  const std::shared_ptr<const PluginInfo> m_goomInfo;
  std::shared_ptr<RandomColorMaps> m_colorMaps{};
  const IColorMap* m_currentColorMap{};
  std::string m_resourcesDirectory{};
  GammaCorrection m_gammaCorrect{4.2F, 0.1F};
  float m_currentBrightness = 1.0F;

  mutable LineStats m_stats{};

  struct LinePoint
  {
    float x;
    float y;
    float angle;
  };
  std::vector<LinePoint> m_srcePoints{};
  std::vector<LinePoint> m_srcePointsCopy{};
  LineType m_srcLineType;
  std::vector<LinePoint> m_destPoints{};
  LineType m_destLineType = LineType::circle;
  static constexpr float LINE_LERP_FINISHED_VAL = 1.1F;
  static constexpr float LINE_LERP_INC = 1.0F / static_cast<float>(MIN_LINE_DURATION - 1);
  float m_lineLerpFactor = 0.0;
  bool m_useLineColor = true;
  void GenerateLinePoints(LineType lineType, float lineParam, std::vector<LinePoint>& line);
  auto GetRandomColorMap() const -> const IColorMap&;

  float m_power = 0;
  float m_powinc = 0;
  // This factor gives height to the audio samples lines. This value seems pleasing.
  float m_maxNormalizedPeak = MIN_MAX_NORMALIZED_PEAK;

  float m_param = 0;
  float m_newAmplitude = 1;
  float m_amplitude = 1;
  float m_audioRange{};
  float m_minAudioValue{};
  static constexpr size_t MIN_IMAGE_DOT_SIZE = 3;
  static constexpr size_t MAX_IMAGE_DOT_SIZE = 15;
  static_assert(MAX_IMAGE_DOT_SIZE <= SmallImageBitmaps::MAX_IMAGE_SIZE, "Max dot size mismatch.");
  size_t m_currentDotSize = MIN_IMAGE_DOT_SIZE;
  bool m_beadedLook = false;
  static auto GetNextDotSize(size_t maxSize) -> size_t;
  const SmallImageBitmaps* m_smallBitmaps{};
  auto GetImageBitmap(size_t size) -> const ImageBitmap&;

  // pour l'instant je stocke la couleur a terme, on stockera le mode couleur et l'on animera
  Pixel m_color1{};
  Pixel m_color2{};

  struct PointAndColor
  {
    V2dInt point;
    Pixel color;
  };
  auto GetAudioPoints(const Pixel& lineColor, const std::vector<float>& audioData) const
      -> std::vector<PointAndColor>;
  auto GetNextPointData(const LinePoint& pt,
                        const Pixel& mainColor,
                        const Pixel& randColor,
                        float dataVal) const -> PointAndColor;
  auto GetMainColor(const Pixel& lineColor, float t) const -> Pixel;
  auto GetNormalizedData(float data) const -> float;
  void MoveSrceLineCloserToDest();
  void DrawDots(const V2dInt& pt, const std::vector<Pixel>& colors);
  static void SmoothCircleJoin(std::vector<PointAndColor>& audioPoints);
};

LinesFx::LinesFx(const IGoomDraw* const draw,
                 const std::shared_ptr<const PluginInfo>& goomInfo,
                 const LineType srceLineType,
                 const float srceParam,
                 const Pixel& srceColor,
                 const LineType destLineType,
                 const float destParam,
                 const Pixel& destColor) noexcept
  : m_fxImpl{new LinesImpl{draw, goomInfo, srceLineType, srceParam, srceColor, destLineType,
                           destParam, destColor}}
{
}

LinesFx::~LinesFx() noexcept = default;

auto LinesFx::GetResourcesDirectory() const -> const std::string&
{
  return m_fxImpl->GetResourcesDirectory();
}

void LinesFx::SetResourcesDirectory(const std::string& dirName)
{
  m_fxImpl->SetResourcesDirectory(dirName);
}

void LinesFx::SetWeightedColorMaps(std::shared_ptr<UTILS::RandomColorMaps> weightedMaps)
{
  m_fxImpl->SetWeightedColorMaps(weightedMaps);
}

void LinesFx::SetSmallImageBitmaps(const SmallImageBitmaps& smallBitmaps)
{
  m_fxImpl->SetSmallImageBitmaps(smallBitmaps);
}

void LinesFx::Start()
{
  m_fxImpl->Start();
}

void LinesFx::Log(const GoomStats::LogStatsValueFunc& l) const
{
  m_fxImpl->Log(l);
}

void LinesFx::Finish()
{
  m_fxImpl->Finish();
}

auto LinesFx::GetRandomLineColor() const -> Pixel
{
  return m_fxImpl->GetRandomLineColor();
}

auto LinesFx::GetPower() const -> float
{
  return m_fxImpl->GetPower();
}

void LinesFx::SetPower(const float val)
{
  m_fxImpl->SetPower(val);
}

auto LinesFx::CanResetDestLine() const -> bool
{
  return m_fxImpl->CanResetDestLine();
}

void LinesFx::ResetDestLine(const LineType newLineType,
                            const float newParam,
                            const float newAmplitude,
                            const Pixel& newColor)
{
  m_fxImpl->ResetDestLine(newLineType, newParam, newAmplitude, newColor);
}

void LinesFx::DrawLines(const std::vector<int16_t>& soundData,
                        const AudioSamples::MaxMinValues& soundMinMax)
{
  m_fxImpl->DrawLines(soundData, soundMinMax);
}

LinesFx::LinesImpl::LinesImpl(const IGoomDraw* const draw,
                              std::shared_ptr<const PluginInfo> info,
                              const LineType srceLineType,
                              const float srceParam,
                              const Pixel& srceColor,
                              const LineType destLineType,
                              const float destParam,
                              const Pixel& destColor)
  : m_draw{draw},
    m_goomInfo{std::move(info)},
    m_colorMaps{GetAllSlimMaps()},
    m_srcePoints(AUDIO_SAMPLE_LEN),
    m_srcePointsCopy(AUDIO_SAMPLE_LEN),
    m_srcLineType{srceLineType},
    m_destPoints(AUDIO_SAMPLE_LEN),
    m_destLineType{destLineType},
    m_param{destParam},
    m_color1{srceColor},
    m_color2{destColor}
{
  GenerateLinePoints(m_srcLineType, srceParam, m_srcePoints);
  m_srcePointsCopy = m_srcePoints;
  ResetDestLine(m_destLineType, destParam, 1.0, destColor);
}

auto LinesFx::LinesImpl::GetRandomColorMap() const -> const IColorMap&
{
  assert(m_colorMaps);
  return m_colorMaps->GetRandomColorMap(m_colorMaps->GetRandomGroup());
}

void LinesFx::LinesImpl::Start()
{
}

void LinesFx::LinesImpl::Log(const GoomStats::LogStatsValueFunc& l) const
{
  m_stats.Log(l);
}

void LinesFx::LinesImpl::SetWeightedColorMaps(std::shared_ptr<UTILS::RandomColorMaps> weightedMaps)
{
  m_colorMaps = weightedMaps;
}

void LinesFx::LinesImpl::Finish()
{
}

void LinesFx::LinesImpl::GenerateLinePoints(const LineType lineType,
                                            const float lineParam,
                                            std::vector<LinePoint>& line)
{
  m_currentColorMap = &GetRandomColorMap();
  m_useLineColor = ProbabilityOfMInN(10, 20);

  switch (lineType)
  {
    case LineType::hline:
    {
      const float xStep = static_cast<float>(m_goomInfo->GetScreenInfo().width - 1) /
                          static_cast<float>(AUDIO_SAMPLE_LEN - 1);
      float x = 0;
      for (auto& pt : line)
      {
        pt.angle = m_half_pi;
        pt.x = x;
        pt.y = lineParam;

        x += xStep;
      }
      return;
    }
    case LineType::vline:
    {
      const float yStep = static_cast<float>(m_goomInfo->GetScreenInfo().height - 1) /
                          static_cast<float>(AUDIO_SAMPLE_LEN - 1);
      float y = 0;
      for (auto& pt : line)
      {
        pt.angle = 0;
        pt.x = lineParam;
        pt.y = y;

        y += yStep;
      }
      return;
    }
    case LineType::circle:
    {
      const float cx = 0.5F * static_cast<float>(m_goomInfo->GetScreenInfo().width);
      const float cy = 0.5F * static_cast<float>(m_goomInfo->GetScreenInfo().height);
      // Make sure the circle joins at each end so use symmetry about x-axis.
      static_assert(AUDIO_SAMPLE_LEN % 2 == 0, "AUDIO_SAMPLE_LEN must divide by 2");
      const float angleStep = m_pi / (0.5F * static_cast<float>(AUDIO_SAMPLE_LEN) - 1.0F);
      float angle = 0;
      for (size_t i = 0; i < AUDIO_SAMPLE_LEN / 2; i++)
      {
        line[i].angle = angle;
        line[i].x = cx + lineParam * std::cos(angle);
        line[i].y = cy + lineParam * std::sin(angle);
        angle += angleStep;
      }
      size_t j = AUDIO_SAMPLE_LEN - 1;
      for (size_t i = 0; i < AUDIO_SAMPLE_LEN / 2; i++)
      {
        line[j].angle = m_two_pi - line[i].angle;
        line[j].x = line[i].x;
        line[j].y = 2.0F * cy - line[i].y;
        j--;
      }

      assert(floats_equal(line[0].x, line[line.size() - 1].x));
      assert(floats_equal(line[0].y, line[line.size() - 1].y));

      return;
    }
    default:
      throw std::logic_error("Unknown LineType enum.");
  }
}

void LinesFx::LinesImpl::MoveSrceLineCloserToDest()
{
  m_lineLerpFactor += LINE_LERP_INC;
  const float t = std::min(1.0F, m_lineLerpFactor);
  for (uint32_t i = 0; i < AUDIO_SAMPLE_LEN; i++)
  {
    m_srcePoints[i].x = stdnew::lerp(m_srcePointsCopy[i].x, m_destPoints[i].x, t);
    m_srcePoints[i].y = stdnew::lerp(m_srcePointsCopy[i].y, m_destPoints[i].y, t);
    m_srcePoints[i].angle = stdnew::lerp(m_srcePointsCopy[i].angle, m_destPoints[i].angle, t);
  }
  if (m_lineLerpFactor >= 1.0F)
  {
    m_srcLineType = m_destLineType;
    m_currentBrightness = GetRandInRange(2.0F, 3.0F);
  }

  assert(m_srcLineType != LineType::circle || m_lineLerpFactor < 1.0F ||
         (floats_equal(m_srcePoints[0].x, m_srcePoints[AUDIO_SAMPLE_LEN - 1].x) &&
          floats_equal(m_srcePoints[0].y, m_srcePoints[AUDIO_SAMPLE_LEN - 1].y)));

  constexpr float COLOR_MIX_AMOUNT = 1.0F / 64.0F;
  m_color1 = IColorMap::GetColorMix(m_color1, m_color2, COLOR_MIX_AMOUNT);

  constexpr float MIN_POW_INC = 0.03F;
  constexpr float MAX_POW_INC = 0.10F;
  constexpr float MIN_POWER = 1.1F;
  constexpr float MAX_POWER = 17.5F;
  m_power += m_powinc;
  if (m_power < MIN_POWER)
  {
    m_power = MIN_POWER;
    m_powinc = GetRandInRange(MIN_POW_INC, MAX_POW_INC);
  }
  if (m_power > MAX_POWER)
  {
    m_power = MAX_POWER;
    m_powinc = -GetRandInRange(MIN_POW_INC, MAX_POW_INC);
  }

  constexpr float AMP_MIX_AMOUNT = 0.01F;
  m_amplitude = stdnew::lerp(m_amplitude, m_newAmplitude, AMP_MIX_AMOUNT);
}

auto LinesFx::LinesImpl::CanResetDestLine() const -> bool
{
  return m_lineLerpFactor > LINE_LERP_FINISHED_VAL;
}

void LinesFx::LinesImpl::ResetDestLine(const LineType newLineType,
                                       const float newParam,
                                       const float newAmplitude,
                                       const Pixel& newColor)
{
  GenerateLinePoints(newLineType, m_param, m_destPoints);
  m_destLineType = newLineType;
  m_param = newParam;
  m_newAmplitude = newAmplitude;
  m_color2 = newColor;
  m_lineLerpFactor = 0.0;
  m_currentBrightness = GetRandInRange(1.0F, 1.9F);
  m_beadedLook = ProbabilityOfMInN(1, 20);
  m_maxNormalizedPeak = GetRandInRange(MIN_MAX_NORMALIZED_PEAK, MAX_MAX_NORMALIZED_PEAK);

  m_srcePointsCopy = m_srcePoints;
}

inline auto LinesFx::LinesImpl::GetResourcesDirectory() const -> const std::string&
{
  return m_resourcesDirectory;
}

inline void LinesFx::LinesImpl::SetResourcesDirectory(const std::string& dirName)
{
  m_resourcesDirectory = dirName;
}

inline void LinesFx::LinesImpl::SetSmallImageBitmaps(const SmallImageBitmaps& smallBitmaps)
{
  m_smallBitmaps = &smallBitmaps;
}

inline auto LinesFx::LinesImpl::GetImageBitmap(const size_t size) -> const ImageBitmap&
{
  return m_smallBitmaps->GetImageBitmap(
      SmallImageBitmaps::ImageNames::CIRCLE,
      stdnew::clamp(size, MIN_IMAGE_DOT_SIZE, MAX_IMAGE_DOT_SIZE));
}

inline auto LinesFx::LinesImpl::GetPower() const -> float
{
  return m_power;
}

inline void LinesFx::LinesImpl::SetPower(const float val)
{
  m_power = val;
}

// les modes couleur possible (si tu mets un autre c'est noir)
#define GML_BLEUBLANC 0
#define GML_RED 1
#define GML_ORANGE_V 2
#define GML_ORANGE_J 3
#define GML_VERT 4
#define GML_BLEU 5
#define GML_BLACK 6

inline auto GetColor(const int mode) -> Pixel
{
  switch (mode)
  {
    case GML_RED:
      return GetIntColor(230, 120, 18);
    case GML_ORANGE_J:
      return GetIntColor(120, 252, 18);
    case GML_ORANGE_V:
      return GetIntColor(160, 236, 40);
    case GML_BLEUBLANC:
      return GetIntColor(40, 220, 140);
    case GML_VERT:
      return GetIntColor(200, 80, 18);
    case GML_BLEU:
      return GetIntColor(250, 30, 80);
    case GML_BLACK:
      return GetIntColor(16, 16, 16);
    default:
      throw std::logic_error("Unknown line color.");
  }
}

auto GetBlackLineColor() -> Pixel
{
  return GetColor(GML_BLACK);
}

auto GetGreenLineColor() -> Pixel
{
  return GetColor(GML_VERT);
}

auto GetRedLineColor() -> Pixel
{
  return GetColor(GML_RED);
}

auto LinesFx::LinesImpl::GetRandomLineColor() const -> Pixel
{
  if (ProbabilityOfMInN(1, 50))
  {
    return GetColor(static_cast<int>(GetNRand(6)));
  }
  assert(m_colorMaps);
  return RandomColorMaps::GetRandomColor(GetRandomColorMap(), 0.0F, 1.0F);
}

auto SimpleMovingAverage(const std::vector<int16_t>& x, const uint32_t winLen) -> std::vector<float>
{
  int32_t temp = 0;
  for (size_t i = 0; i < winLen - 1; i++)
  {
    temp += x[i];
  }

  std::vector<float> result{};
  result.reserve(AUDIO_SAMPLE_LEN - winLen + 1);
  for (size_t i = 0; i < AUDIO_SAMPLE_LEN - winLen + 1; i++)
  {
    temp += x[winLen - 1 + i];
    result.push_back(static_cast<float>(temp) / winLen);
    temp -= x[i];
  }

  return result;
}

inline auto GetDataPoints(const std::vector<int16_t>& x) -> std::vector<float>
{
  return std::vector<float>{x.data(), x.data() + AUDIO_SAMPLE_LEN};
  if (ProbabilityOfMInN(9999, 10000))
  {
    return std::vector<float>{x.data(), x.data() + AUDIO_SAMPLE_LEN};
  }

  return SimpleMovingAverage(x, 3);
}

void LinesFx::LinesImpl::DrawLines(const std::vector<int16_t>& soundData,
                                   const AudioSamples::MaxMinValues& soundMinMax)
{
  m_stats.UpdateStart();

  constexpr size_t LAST_POINT_INDEX = AUDIO_SAMPLE_LEN - 1;

  assert(m_srcLineType != LineType::circle || m_lineLerpFactor < 1.0F ||
         (floats_equal(m_srcePoints[0].x, m_srcePoints[LAST_POINT_INDEX].x) &&
          floats_equal(m_srcePoints[0].y, m_srcePoints[LAST_POINT_INDEX].y)));

  const LinePoint& pt0 = m_srcePoints[0];
  const LinePoint& ptN = m_srcePoints[LAST_POINT_INDEX];
  const Pixel lineColor = GetLightenedColor(m_color1, m_power);

  m_audioRange = static_cast<float>(soundMinMax.maxVal - soundMinMax.minVal);
  assert(m_audioRange >= 0.0);
  m_minAudioValue = static_cast<float>(soundMinMax.minVal);

  if (m_audioRange < SMALL_FLOAT)
  {
    // No range - flatline audio
    const std::vector<Pixel> colors = {lineColor, lineColor};
    m_draw->Line(static_cast<int>(pt0.x), static_cast<int>(pt0.y), static_cast<int>(ptN.x),
                 static_cast<int>(pt0.y), colors, 1);
    MoveSrceLineCloserToDest();
    return;
  }

  constexpr uint8_t THICKNESS = 1;
  const std::vector<float> data = GetDataPoints(soundData);
  const std::vector<PointAndColor> audioPoints = GetAudioPoints(lineColor, data);

  V2dInt point1 = audioPoints[0].point;
  V2dInt point2{};

  for (size_t i = 1; i < audioPoints.size(); i++)
  {
    const PointAndColor& nextPointData = audioPoints[i];

    point2 = nextPointData.point;
    const Pixel modColor = nextPointData.color;
    const std::vector<Pixel> colors = {lineColor, modColor};

    m_draw->Line(point1.x, point1.y, point2.x, point2.y, colors, THICKNESS);
    DrawDots(point2, colors);

    point1 = point2;
  }

  MoveSrceLineCloserToDest();

  constexpr size_t MAX_DOT_SIZE = 7;
  m_currentDotSize = GetNextDotSize(MAX_DOT_SIZE);

  m_stats.UpdateEnd();
}

auto LinesFx::LinesImpl::GetAudioPoints(const Pixel& lineColor,
                                        const std::vector<float>& audioData) const
    -> std::vector<PointAndColor>
{
  const Pixel randColor = GetRandomLineColor();

  constexpr float T_STEP = 1.0F / static_cast<float>(AUDIO_SAMPLE_LEN - 1);
  constexpr float halfwayT = 0.5F;
  float currentTStep = T_STEP;
  float t = 0.0;

  std::vector<PointAndColor> audioPoints{};
  audioPoints.reserve(audioData.size());

  for (size_t i = 0; i < audioData.size(); i++)
  {
    audioPoints.emplace_back(
        GetNextPointData(m_srcePoints[i], GetMainColor(lineColor, t), randColor, audioData[i]));

    if (t >= halfwayT)
    {
      currentTStep = -T_STEP;
    }
    t += currentTStep;
  }

  if (m_srcLineType == LineType::circle && m_lineLerpFactor >= 1.0F)
  {
    // It's a complete circle - lerp the last few points to nicely join back to start.
    SmoothCircleJoin(audioPoints);
  }

  return audioPoints;
}

void LinesFx::LinesImpl::SmoothCircleJoin(std::vector<PointAndColor>& audioPoints)
{
  constexpr size_t NUM_POINTS_TO_LERP = 50;
  assert(NUM_POINTS_TO_LERP < audioPoints.size());

  constexpr float T_STEP = 1.0F / static_cast<float>(NUM_POINTS_TO_LERP);

  const size_t lastPointIndex = audioPoints.size() - 1;
  const V2dInt endDiff = audioPoints[0].point - audioPoints[lastPointIndex].point;
  if (endDiff.x == 0 && endDiff.y == 0)
  {
    return;
  }

  V2dInt diff = endDiff;
  float t = 1.0F - T_STEP;
  for (size_t i = lastPointIndex; i > audioPoints.size() - NUM_POINTS_TO_LERP; i--)
  {
    audioPoints[i].point += diff;

    diff = {static_cast<int32_t>(std::round(t * static_cast<float>(endDiff.x))),
            static_cast<int32_t>(std::round(t * static_cast<float>(endDiff.y)))};

    t -= T_STEP;
  }

  assert(audioPoints[0].point.x == audioPoints[audioPoints.size() - 1].point.x);
  assert(audioPoints[0].point.y == audioPoints[audioPoints.size() - 1].point.y);
}

auto LinesFx::LinesImpl::GetNextPointData(const LinePoint& pt,
                                          const Pixel& mainColor,
                                          const Pixel& randColor,
                                          const float dataVal) const -> PointAndColor
{
  assert(m_goomInfo->GetSoundInfo().GetAllTimesMinVolume() <= dataVal);
  const float cosAngle = std::cos(pt.angle);
  const float sinAngle = std::sin(pt.angle);
  const float normalizedDataVal = GetNormalizedData(dataVal);
  assert(normalizedDataVal >= 0.0);
  const V2dInt nextPointData{static_cast<int>(pt.x + m_amplitude * cosAngle * normalizedDataVal),
                             static_cast<int>(pt.y + m_amplitude * sinAngle * normalizedDataVal)};
  const float tData = normalizedDataVal / static_cast<float>(m_maxNormalizedPeak);
  const float brightness = m_currentBrightness * tData;
  const Pixel modColor =
      m_gammaCorrect.GetCorrection(brightness, IColorMap::GetColorMix(mainColor, randColor, tData));
  return {nextPointData, modColor};
}

inline auto LinesFx::LinesImpl::GetMainColor(const Pixel& lineColor, const float t) const -> Pixel
{
  if (m_useLineColor)
  {
    return lineColor;
  }
  assert(m_currentColorMap);
  return m_currentColorMap->GetColor(t);
}

inline auto LinesFx::LinesImpl::GetNormalizedData(const float data) const -> float
{
  return m_maxNormalizedPeak * (data - m_minAudioValue) / m_audioRange;
}

void LinesFx::LinesImpl::DrawDots(const V2dInt& pt, const std::vector<Pixel>& colors)
{
  size_t dotSize = m_currentDotSize;
  if (m_beadedLook)
  {
    dotSize = GetNextDotSize(MAX_IMAGE_DOT_SIZE);
  }

  if (dotSize > 1)
  {
    const auto getModColor = [&]([[maybe_unused]] const size_t x, [[maybe_unused]] const size_t y,
                                 const Pixel& b) -> Pixel {
      return GetColorMultiply(b, colors[0], true);
    };
    const auto getLineColor = [&]([[maybe_unused]] const size_t x, [[maybe_unused]] const size_t y,
                                  const Pixel& b) -> Pixel {
      return GetColorMultiply(b, colors[1], false);
    };
    const std::vector<IGoomDraw::GetBitmapColorFunc> getColors{getModColor, getLineColor};
    const ImageBitmap& bitmap = GetImageBitmap(m_currentDotSize);
    m_draw->Bitmap(pt.x, pt.y, bitmap, getColors, false);
  }
}

inline auto LinesFx::LinesImpl::GetNextDotSize(const size_t maxSize) -> size_t
{
  // TODO Fix this hack
  static const Weights<size_t> s_dotSizesMin{{
      {1, 100},
      {3, 50},
      {5, 5},
      {7, 1},
  }};
  constexpr size_t MAX_MIN_DOT_SIZE = 7;
  if (maxSize <= MAX_MIN_DOT_SIZE)
  {
    return s_dotSizesMin.GetRandomWeighted();
  }

  static const Weights<size_t> s_dotSizes{{
      {1, 50},
      {3, 20},
      {5, 5},
      {7, 1},
      {9, 1},
      {11, 1},
      {13, 1},
      {15, 1},
  }};
  return s_dotSizes.GetRandomWeighted();
}

} // namespace GOOM
