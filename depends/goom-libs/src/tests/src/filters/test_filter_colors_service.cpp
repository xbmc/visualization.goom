#include "catch2/catch.hpp"
#include "filter_fx/filter_buffers.h"
#include "filter_fx/filter_colors_service.h"
#include "filter_fx/filter_utils/zoom_filter_coefficients.h"
#include "goom_graphic.h"
#include "utils/format_utils.h"
#include "utils/math/goom_rand.h"

#include <array>
#include <numeric>

namespace GOOM::UNIT_TESTS
{

using FILTER_FX::FilterColorsService;
using FILTER_FX::ZoomFilterBuffers;
using FILTER_FX::FILTER_UTILS::ZOOM_FILTER_COEFFS::MAX_SUM_COEFFS;
using FILTER_FX::FILTER_UTILS::ZOOM_FILTER_COEFFS::NeighborhoodCoeffArray;
using UTILS::fmt_rgba;
using UTILS::MATH::GoomRand;

static constexpr size_t WIDTH  = 120;
static constexpr size_t HEIGHT = 70;
static const auto GOOM_RAND    = GoomRand{};

constexpr auto GetColor(const PixelChannelType red,
                        const PixelChannelType green,
                        const PixelChannelType blue) -> GOOM::Pixel
{
  return Pixel{red, green, blue, MAX_ALPHA};
}

TEST_CASE("FilterColorsService", "[FilterColorsService]")
{
  auto filterColorsService = FilterColorsService{GOOM_RAND};

  auto pixelBuffer = PixelBuffer{
      {WIDTH, HEIGHT}
  };

  static constexpr auto RED1   = 50U;
  static constexpr auto GREEN1 = 150U;
  static constexpr auto BLUE1  = 200U;
  static constexpr auto RED2   = 80U;
  static constexpr auto GREEN2 = 120U;
  static constexpr auto BLUE2  = 50U;
  static constexpr auto RED3   = 120U;
  static constexpr auto GREEN3 = 200U;
  static constexpr auto BLUE3  = 150U;
  static constexpr auto RED4   = 120U;
  static constexpr auto GREEN4 = 200U;
  static constexpr auto BLUE4  = 60U;

  static constexpr auto COEFFS = NeighborhoodCoeffArray{
      {(50 * MAX_SUM_COEFFS) / (MAX_COLOR_VAL + 1),
       (60 * MAX_SUM_COEFFS) / (MAX_COLOR_VAL + 1),
       (70 * MAX_SUM_COEFFS) / (MAX_COLOR_VAL + 1),
       (76 * MAX_SUM_COEFFS) / (MAX_COLOR_VAL + 1)}
  };
  REQUIRE(MAX_SUM_COEFFS == std::accumulate(cbegin(COEFFS), cend(COEFFS), 0U));
  REQUIRE(4 == COEFFS.size());
  // GCC Won't link with this:  REQUIRE(PixelBuffer::NUM_NBRS == coeffs.val.size());

  SECTION("Correct new color")
  {
    static constexpr auto X = 5;
    static constexpr auto Y = 5;

    static constexpr auto SOURCE_POINT_INFO = ZoomFilterBuffers::SourcePointInfo{
        {static_cast<int32_t>(X), static_cast<int32_t>(Y)},
        &COEFFS, false
    };

    pixelBuffer(X, Y)         = GetColor(RED1, GREEN1, BLUE1);
    pixelBuffer(X + 1, Y)     = GetColor(RED2, GREEN2, BLUE2);
    pixelBuffer(X, Y + 1)     = GetColor(RED3, GREEN3, BLUE3);
    pixelBuffer(X + 1, Y + 1) = GetColor(RED4, GREEN4, BLUE4);

    static constexpr auto EXPECTED_R =
        (COEFFS[0] * RED1 + COEFFS[1] * RED2 + COEFFS[2] * RED3 + COEFFS[3] * RED4) /
        MAX_SUM_COEFFS;
    static constexpr auto EXPECTED_G =
        (COEFFS[0] * GREEN1 + COEFFS[1] * GREEN2 + COEFFS[2] * GREEN3 + COEFFS[3] * GREEN4) /
        MAX_SUM_COEFFS;
    static constexpr auto EXPECTED_B =
        (COEFFS[0] * BLUE1 + COEFFS[1] * BLUE2 + COEFFS[2] * BLUE3 + COEFFS[3] * BLUE4) /
        MAX_SUM_COEFFS;

    static constexpr auto EXPECTED_COLOR = GetColor(EXPECTED_R, EXPECTED_G, EXPECTED_B);
    const auto pixelNeighbours = pixelBuffer.Get4RHBNeighbours(SOURCE_POINT_INFO.screenPoint.x,
                                                               SOURCE_POINT_INFO.screenPoint.y);
    const auto newColor = filterColorsService.GetNewColor(SOURCE_POINT_INFO, pixelNeighbours);

    UNSCOPED_INFO("expectedColor = " << fmt_rgba("{}", EXPECTED_COLOR));
    UNSCOPED_INFO("newColor = " << fmt_rgba("{}", newColor));
    REQUIRE(EXPECTED_COLOR == newColor);
  }
}

} // namespace GOOM::UNIT_TESTS
