#include "catch2/catch.hpp"
#include "color/color_utils.h"
#include "goom_graphic.h"
#include "utils/graphics/pixel_utils.h"

#include <algorithm>

namespace GOOM::UNIT_TESTS
{

using COLOR::GetBrighterChannelColor;
using COLOR::GetBrighterColor;
using COLOR::GetColorAdd;
using COLOR::GetColorChannelAdd;
using COLOR::GetEvolvedColor;
using COLOR::GetLightenedColor;
using COLOR::GetRgbColorLerp;
using GOOM::UTILS::GRAPHICS::CHANNEL_COLOR_SCALAR_DIVISOR;

TEST_CASE("Test max channels")
{
  REQUIRE(channel_limits<uint8_t>::min() == 0);
  REQUIRE(channel_limits<uint8_t>::max() == 255);
  REQUIRE(channel_limits<uint32_t>::min() == 0);
  REQUIRE(channel_limits<uint32_t>::max() == 255);
  REQUIRE(channel_limits<int>::min() == 0);
  REQUIRE(channel_limits<int>::max() == 255);
  REQUIRE(channel_limits<float>::min() == 0);
  REQUIRE(channel_limits<float>::max() == 255.0F);
}

TEST_CASE("Color channels are added")
{
  REQUIRE(GetColorChannelAdd(100, 120) == 220);
  REQUIRE(GetColorChannelAdd(200, 120) == 320);
  REQUIRE(GetColorChannelAdd(0, 120) == 120);
  REQUIRE(GetColorChannelAdd(0, 0) == 0);
}

TEST_CASE("Colors are added")
{
  static constexpr auto COLOR1 = Pixel{
      {100, 50, 20}
  };
  static constexpr auto COLOR2 = Pixel{
      {120, 250, 70}
  };
  static constexpr auto COLOR3 = GetColorAdd(COLOR1, COLOR2);
  REQUIRE(static_cast<uint32_t>(COLOR3.R()) == 220);
  REQUIRE(static_cast<uint32_t>(COLOR3.G()) == 300);
  REQUIRE(static_cast<uint32_t>(COLOR3.B()) == 90);
}

TEST_CASE("Color channels are brightened")
{
  REQUIRE(GetBrighterChannelColor(100U, 2U) == (100U * 2U) / CHANNEL_COLOR_SCALAR_DIVISOR);
  REQUIRE(GetBrighterChannelColor(11U, 20U) == (11U * 20U) / CHANNEL_COLOR_SCALAR_DIVISOR);
  REQUIRE(GetBrighterChannelColor(0U, 20U) == 0U);
  REQUIRE(
      GetBrighterChannelColor(100U, 20U) ==
      std::clamp(0U, (100U * 20U) / CHANNEL_COLOR_SCALAR_DIVISOR, CHANNEL_COLOR_SCALAR_DIVISOR));
}

TEST_CASE("Colors are brightened")
{
  static constexpr auto COLOR = Pixel{
      {100, 50, 20}
  };

  auto brighterColor = GetBrighterColor(1.0F, COLOR);
  REQUIRE(brighterColor.R() == 100);
  REQUIRE(brighterColor.G() == 50);
  REQUIRE(brighterColor.B() == 20);

  brighterColor = GetBrighterColor(0.5F, COLOR);
  REQUIRE(brighterColor.R() == 50);
  REQUIRE(brighterColor.G() == 25);
  REQUIRE(brighterColor.B() == 10);

  brighterColor = GetBrighterColor(0.01F, COLOR);
  REQUIRE(brighterColor.R() == 1);
  REQUIRE(brighterColor.G() == 0);
  REQUIRE(brighterColor.B() == 0);
}

TEST_CASE("Color Lerp")
{
  static constexpr auto LERP_T1   = 0.5F;
  const auto lerpedColor1         = GetRgbColorLerp(BLACK_PIXEL, WHITE_PIXEL, LERP_T1);
  const auto expectedLerpedColor1 = std::lround(LERP_T1 * static_cast<float>(MAX_COLOR_VAL));
  REQUIRE(lerpedColor1.R() == expectedLerpedColor1);
  REQUIRE(lerpedColor1.G() == expectedLerpedColor1);
  REQUIRE(lerpedColor1.B() == expectedLerpedColor1);

  static constexpr auto LERP_T2   = 0.333333F;
  const auto lerpedColor2         = GetRgbColorLerp(BLACK_PIXEL, WHITE_PIXEL, LERP_T2);
  const auto expectedLerpedColor2 = std::lround(LERP_T2 * static_cast<float>(MAX_COLOR_VAL));
  REQUIRE(lerpedColor2.R() == expectedLerpedColor2);
  REQUIRE(lerpedColor2.G() == expectedLerpedColor2);
  REQUIRE(lerpedColor2.B() == expectedLerpedColor2);
}

TEST_CASE("Lighten")
{
  static constexpr auto COLOR = Pixel{
      {100, 0, 0}
  };

  const Pixel lightenedColor = GetLightenedColor(COLOR, 10.0);
  REQUIRE(static_cast<uint32_t>(lightenedColor.R()) == 50);
  REQUIRE(static_cast<uint32_t>(lightenedColor.G()) == 0);
  REQUIRE(static_cast<uint32_t>(lightenedColor.B()) == 0);
}

TEST_CASE("Lightened color")
{
  static constexpr auto COLOR = Pixel{
      {100, 50, 20}
  };

  auto lightenedColor = GetLightenedColor(COLOR, 0.5);
  REQUIRE(lightenedColor.R() == 0);
  REQUIRE(lightenedColor.G() == 0);
  REQUIRE(lightenedColor.B() == 0);

  lightenedColor = GetLightenedColor(COLOR, 1.0);
  REQUIRE(lightenedColor.R() == 0);
  REQUIRE(lightenedColor.G() == 0);
  REQUIRE(lightenedColor.B() == 0);

  lightenedColor = GetLightenedColor(COLOR, 2.0);
  REQUIRE(lightenedColor.R() == 15);
  REQUIRE(lightenedColor.G() == 7);
  REQUIRE(lightenedColor.B() == 3);

  lightenedColor = GetLightenedColor(COLOR, 5.0);
  REQUIRE(lightenedColor.R() == 34);
  REQUIRE(lightenedColor.G() == 17);
  REQUIRE(lightenedColor.B() == 6);

  lightenedColor = GetLightenedColor(COLOR, 10.0);
  REQUIRE(lightenedColor.R() == 50);
  REQUIRE(lightenedColor.G() == 25);
  REQUIRE(lightenedColor.B() == 10);

  const Pixel color2 = WHITE_PIXEL;
  lightenedColor     = GetLightenedColor(color2, 1.0);
  REQUIRE(lightenedColor.R() == 0);
  REQUIRE(lightenedColor.G() == 0);
  REQUIRE(lightenedColor.B() == 0);

  lightenedColor = GetLightenedColor(color2, 2.0);
  REQUIRE(lightenedColor.R() == 38);
  REQUIRE(lightenedColor.G() == 38);
  REQUIRE(lightenedColor.B() == 38);

  lightenedColor = GetLightenedColor(color2, 5.0);
  REQUIRE(lightenedColor.R() == 89);
  REQUIRE(lightenedColor.G() == 89);
  REQUIRE(lightenedColor.B() == 89);

  lightenedColor = GetLightenedColor(color2, 10.0);
  REQUIRE(lightenedColor.R() == 127);
  REQUIRE(lightenedColor.G() == 127);
  REQUIRE(lightenedColor.B() == 127);
}

TEST_CASE("Evolved color")
{
  static constexpr auto COLOR = Pixel{
      {100, 50, 20}
  };
  auto evolvedColor = Pixel{};

  evolvedColor = GetEvolvedColor(COLOR);
  REQUIRE(evolvedColor.R() == 67);
  REQUIRE(evolvedColor.G() == 33);
  REQUIRE(evolvedColor.B() == 13);

  evolvedColor = GetEvolvedColor(evolvedColor);
  REQUIRE(evolvedColor.R() == 44);
  REQUIRE(evolvedColor.G() == 22);
  REQUIRE(evolvedColor.B() == 8);

  evolvedColor = GetEvolvedColor(evolvedColor);
  REQUIRE(evolvedColor.R() == 29);
  REQUIRE(evolvedColor.G() == 14);
  REQUIRE(evolvedColor.B() == 5);

  evolvedColor = GetEvolvedColor(evolvedColor);
  REQUIRE(evolvedColor.R() == 19);
  REQUIRE(evolvedColor.G() == 9);
  REQUIRE(evolvedColor.B() == 3);
}

} // namespace GOOM::UNIT_TESTS
