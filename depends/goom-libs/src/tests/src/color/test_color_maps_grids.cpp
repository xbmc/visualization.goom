#include "catch2/catch.hpp"
#include "color/color_maps.h"
#include "color/color_maps_grids.h"
#include "color/color_utils.h"
#include "goom_graphic.h"
#include "utils/t_values.h"

#include <algorithm>
#include <string>
#include <vivid/vivid.h>

namespace GOOM::UNIT_TESTS
{

using COLOR::ColorMapsGrid;
using COLOR::GetRgbColorLerp;
using COLOR::IColorMap;
using COLOR::COLOR_DATA::ColorMapName;
using UTILS::TValue;

namespace
{

class TestColorMap : public IColorMap
{
public:
  TestColorMap(const std::string& mapName, vivid::ColorMap colorMap) noexcept;

  [[nodiscard]] auto GetNumStops() const -> size_t override { return m_vividColorMap.numStops(); }
  [[nodiscard]] auto GetMapName() const -> ColorMapName override { return ColorMapName::ACCENT; }
  [[nodiscard]] auto GetColor(float t) const -> Pixel override;

  static auto GetColorMix(const Pixel& col1, const Pixel& col2, float t) -> Pixel;

private:
  const std::string m_mapName;
  const vivid::ColorMap m_vividColorMap;
};

TestColorMap::TestColorMap(const std::string& mapName, vivid::ColorMap colorMap) noexcept
  : m_mapName{mapName}, m_vividColorMap{std::move(colorMap)}
{
}

inline auto TestColorMap::GetColor(const float t) const -> Pixel
{
  const auto rgb8 = vivid::col8_t{vivid::rgb8::fromRgb(m_vividColorMap.at(t))};
  return Pixel{
      {rgb8.r, rgb8.g, rgb8.b, MAX_ALPHA}  // NOLINT: union hard to fix here
  };
}

inline auto TestColorMap::GetColorMix(const Pixel& col1, const Pixel& col2, const float t) -> Pixel
{
  return GetRgbColorLerp(col1, col2, t);
}

inline const auto SIMPLE_WHITE_MAP_STOPS = std::vector<vivid::srgb_t>{
    {BLACK_PIXEL.RFlt(), BLACK_PIXEL.GFlt(), BLACK_PIXEL.BFlt()},
    {WHITE_PIXEL.RFlt(), WHITE_PIXEL.GFlt(), WHITE_PIXEL.BFlt()},
};
inline const auto SIMPLE_WHITE_MAP = TestColorMap{"SimpleWhiteMap", SIMPLE_WHITE_MAP_STOPS};

inline const auto SIMPLE_RED_MAP_STOPS = std::vector<vivid::srgb_t>{
    {BLACK_PIXEL.RFlt(), BLACK_PIXEL.GFlt(), BLACK_PIXEL.BFlt()},
    {              1.0F,               0.0F,               0.0F},
};
inline const auto SIMPLE_RED_MAP = TestColorMap{"SimpleRedMap", SIMPLE_RED_MAP_STOPS};

inline const auto SIMPLE_GREEN_MAP_STOPS = std::vector<vivid::srgb_t>{
    {BLACK_PIXEL.RFlt(), BLACK_PIXEL.GFlt(), BLACK_PIXEL.BFlt()},
    {              0.0F,               1.0F,               0.0F},
};
inline const auto SIMPLE_GREEN_MAP = TestColorMap{"SimpleGreenMap", SIMPLE_GREEN_MAP_STOPS};

inline const auto SIMPLE_BLUE_MAP_STOPS = std::vector<vivid::srgb_t>{
    {BLACK_PIXEL.RFlt(), BLACK_PIXEL.GFlt(), BLACK_PIXEL.BFlt()},
    {              0.0F,               0.0F,               1.0F},
};
inline const auto SIMPLE_BLUE_MAP = TestColorMap{"SimpleBlueMap", SIMPLE_BLUE_MAP_STOPS};

inline const auto VERTICAL_BASE_COLORS = std::vector<Pixel>{
    Pixel{MAX_COLOR_VAL,            0U,            0U, MAX_ALPHA},
    Pixel{           0U, MAX_COLOR_VAL,            0U, MAX_ALPHA},
    Pixel{           0U,            0U, MAX_COLOR_VAL, MAX_ALPHA},
};

}

TEST_CASE("Test GetCurrentHorizontalLineColors")
{
  static constexpr auto NUM_VERTICAL_STEPS = 4U;
  static constexpr auto COLOR_MIX_T        = 0.5F;

  static constexpr auto WIDTH = 3U;
  auto horizontalColorMaps    = std::vector<const IColorMap*>{
      &SIMPLE_WHITE_MAP,
  };
  auto verticalT         = TValue{TValue::StepType::SINGLE_CYCLE, NUM_VERTICAL_STEPS};
  auto verticalColorMaps = std::vector<const IColorMap*>{
      &SIMPLE_RED_MAP,
      &SIMPLE_GREEN_MAP,
      &SIMPLE_BLUE_MAP,
  };
  const auto colorMixingTFunc = []([[maybe_unused]] const float tX, [[maybe_unused]] const float tY)
  { return COLOR_MIX_T; };

  auto colorMapsGrid =
      ColorMapsGrid{horizontalColorMaps, verticalT, verticalColorMaps, colorMixingTFunc};

  static constexpr auto HORIZONTAL_T_STEP = 1.0F / static_cast<float>(WIDTH);
  static constexpr auto LERP_ERROR        = 1.0F / static_cast<float>(MAX_COLOR_VAL);

  REQUIRE(VERTICAL_BASE_COLORS.size() == WIDTH);

  verticalT.Reset();
  for (auto j = 0U; j < NUM_VERTICAL_STEPS; ++j)
  {
    for (auto i = 0U; i < WIDTH; ++i)
    {
      const auto tHoriz = static_cast<float>(i) * HORIZONTAL_T_STEP;

      const auto horizontalColor = GetRgbColorLerp(BLACK_PIXEL, WHITE_PIXEL, tHoriz);
      REQUIRE(horizontalColor.RFlt() == Approx(tHoriz).margin(LERP_ERROR));
      REQUIRE(horizontalColor.GFlt() == Approx(tHoriz).margin(LERP_ERROR));
      REQUIRE(horizontalColor.BFlt() == Approx(tHoriz).margin(LERP_ERROR));

      const auto currentVerticalColor =
          GetRgbColorLerp(BLACK_PIXEL, VERTICAL_BASE_COLORS.at(i), verticalT());
      const auto mixedColor = GetRgbColorLerp(currentVerticalColor, horizontalColor, COLOR_MIX_T);

      const auto gridColors = colorMapsGrid.GetCurrentHorizontalLineColors();
      REQUIRE(gridColors.size() == WIDTH);

      REQUIRE(gridColors.at(i).RFlt() == Approx(mixedColor.RFlt()).margin(LERP_ERROR));
      REQUIRE(gridColors.at(i).GFlt() == Approx(mixedColor.GFlt()).margin(LERP_ERROR));
      REQUIRE(gridColors.at(i).BFlt() == Approx(mixedColor.BFlt()).margin(LERP_ERROR));
    }
    verticalT.Increment();
  }
}

} // namespace GOOM::UNIT_TESTS
