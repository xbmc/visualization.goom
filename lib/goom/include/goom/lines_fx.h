#ifndef VISUALIZATION_GOOM_LINES_FX_H
#define VISUALIZATION_GOOM_LINES_FX_H

#include "goom_config.h"
#include "goom_graphic.h"
#include "goom_stats.h"
#include "sound_info.h"

#include <cstddef>
#include <istream>
#include <memory>
#include <ostream>
#include <string>
#include <vector>

namespace GOOM
{

class IGoomDraw;
class PluginInfo;

namespace UTILS
{
class RandomColorMaps;
class SmallImageBitmaps;
} // namespace UTILS

auto GetBlackLineColor() -> Pixel;
auto GetGreenLineColor() -> Pixel;
auto GetRedLineColor() -> Pixel;

class LinesFx
{
public:
  enum class LineType
  {
    circle = 0, // (param = radius)
    hline, // (param = y)
    vline, // (param = x)
    _size // must be last - gives number of enums
  };
  static constexpr size_t NUM_LINE_TYPES = static_cast<size_t>(LineType::_size);

  LinesFx() noexcept = delete;

  // construit un effet de line (une ligne horitontale pour commencer)
  LinesFx(const IGoomDraw* draw,
          const std::shared_ptr<const PluginInfo>& goomInfo,
          LineType srceLineType,
          float srceParam,
          const Pixel& srceColor,
          LineType destLineType,
          float destParam,
          const Pixel& destColor) noexcept;
  LinesFx(const LinesFx&) noexcept = delete;
  LinesFx(LinesFx&&) noexcept = delete;
  ~LinesFx() noexcept;
  auto operator=(const LinesFx&) -> LinesFx& = delete;
  auto operator=(LinesFx&&) -> LinesFx& = delete;

  [[nodiscard]] auto GetFxName() const -> std::string;

  [[nodiscard]] auto GetResourcesDirectory() const -> const std::string&;
  void SetResourcesDirectory(const std::string& dirName);

  void SetWeightedColorMaps(std::shared_ptr<UTILS::RandomColorMaps> weightedMaps);
  void SetSmallImageBitmaps(const UTILS::SmallImageBitmaps& smallBitmaps);

  void Start();
  auto GetRandomLineColor() const -> Pixel;

  [[nodiscard]] auto GetPower() const -> float;
  void SetPower(float val);

  static constexpr uint32_t MIN_LINE_DURATION = 80;
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
  bool m_enabled = true;
  class LinesImpl;
  const std::unique_ptr<LinesImpl> m_fxImpl;
};

} // namespace GOOM
#endif
