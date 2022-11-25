#define CATCH_CONFIG_NO_POSIX_SIGNALS

#ifndef GOOM_DEBUG
#define GOOM_DEBUG
#endif

#include "catch2/catch.hpp"
#include "goom_config.h"
#include "goom_graphic.h"
#include "utils/graphics/pixel_utils.h"
#include "utils/math/misc.h"

#include <chrono>
#include <cstdint>
#include <cstring>
#include <memory>
#include <vector>

namespace GOOM::UNIT_TESTS
{

using UTILS::GRAPHICS::MakePixel;
using UTILS::GRAPHICS::MultiplyChannelColorByScalar;
using UTILS::GRAPHICS::MultiplyColorChannels;
using UTILS::MATH::FloatsEqual;
using namespace std::chrono_literals;
using std::chrono::high_resolution_clock;
using std::chrono::microseconds;

static constexpr size_t WIDTH            = 1280;
static constexpr size_t HEIGHT           = 720;
static constexpr PixelChannelType TEST_R = 200;
static constexpr PixelChannelType TEST_G = 100;
static constexpr PixelChannelType TEST_B = 50;

TEST_CASE("Pixels")
{
  SECTION("Pixel RGB")
  {
    static constexpr auto PIXEL = Pixel{
        {TEST_R, TEST_G, TEST_B}
    };
    REQUIRE(FloatsEqual(static_cast<float>(TEST_R) / channel_limits<float>::max(), PIXEL.RFlt()));
    REQUIRE(FloatsEqual(static_cast<float>(TEST_G) / channel_limits<float>::max(), PIXEL.GFlt()));
    REQUIRE(FloatsEqual(static_cast<float>(TEST_B) / channel_limits<float>::max(), PIXEL.BFlt()));
  }
  SECTION("Pixel uint32_t RGB")
  {
    static constexpr uint32_t RED   = 299;
    static constexpr uint32_t GREEN = 200;
    static constexpr uint32_t BLUE  = MAX_CHANNEL_VALUE_HDR + 10;
    static constexpr uint32_t ALPHA = 256;
    static constexpr auto PIXEL     = MakePixel(RED, GREEN, BLUE, ALPHA);
    REQUIRE(PIXEL.R() == RED);
    REQUIRE(PIXEL.G() == GREEN);
    REQUIRE(PIXEL.B() == MAX_CHANNEL_VALUE_HDR);
    REQUIRE(PIXEL.A() == 255);
  }
  SECTION("Pixel Set")
  {
    auto pixel = Pixel{
        {TEST_R, TEST_G, TEST_B}
    };
    pixel.SetA(1);
    REQUIRE(1 == pixel.A());
    pixel.SetR(10);
    REQUIRE(10 == pixel.R());
    pixel.SetG(20);
    REQUIRE(20 == pixel.G());
    pixel.SetB(30);
    REQUIRE(30 == pixel.B());
  }
  SECTION("Pixel ==")
  {
    static constexpr auto PIXEL1 = Pixel{
        {TEST_R, TEST_G, TEST_B}
    };
    static constexpr auto PIXEL2 = Pixel{PIXEL1};
    static constexpr auto PIXEL3 = Pixel{
        {TEST_R + 1, TEST_G, TEST_B}
    };
    REQUIRE(PIXEL1 == PIXEL2);
    REQUIRE(not(PIXEL1 == PIXEL3));
    static constexpr auto EXPECTED_BLACK = Pixel{
        {0, 0, 0, 255}
    };
    REQUIRE(EXPECTED_BLACK == BLACK_PIXEL);
    static constexpr auto EXPECTED_WHITE = Pixel{
        {MAX_COLOR_VAL, MAX_COLOR_VAL, MAX_COLOR_VAL, MAX_ALPHA}
    };
    REQUIRE(EXPECTED_WHITE == WHITE_PIXEL);
  }
  SECTION("Pixel Multiply Scalar")
  {
    static constexpr auto PIXEL = Pixel{
        {TEST_R, TEST_G, TEST_B}
    };
    static constexpr auto R_CHANNEL  = PIXEL.R();
    static constexpr uint32_t SCALAR = 32;
    REQUIRE(MultiplyChannelColorByScalar(SCALAR, PIXEL.R()) ==
            ((SCALAR * R_CHANNEL) / MAX_COLOR_VAL));
  }
  SECTION("Pixel Multiply Channels")
  {
    static constexpr auto PIXEL = Pixel{
        {TEST_R, TEST_G, TEST_B}
    };
    static constexpr auto R_CHANNEL  = PIXEL.R();
    static constexpr auto G_CHANNEL  = PIXEL.G();
    static constexpr auto RG_PRODUCT = R_CHANNEL * G_CHANNEL;
    REQUIRE(MultiplyColorChannels(PIXEL.R(), PIXEL.G()) == RG_PRODUCT / MAX_COLOR_VAL);
  }
}

auto GetPixelCount(const PixelBuffer& buffer, const Pixel& pixel) -> uint32_t
{
  auto count = 0U;
  for (size_t y = 0; y < HEIGHT; ++y)
  {
    for (size_t x = 0; x < WIDTH; ++x)
    {
      if (buffer(x, y) == pixel)
      {
        count++;
      }
    }
  }
  return count;
}

TEST_CASE("PixelBuffers")
{
  SECTION("PixelBuffer copy")
  {
    auto srceBuffer = PixelBuffer{
        {WIDTH, HEIGHT}
    };
    REQUIRE(srceBuffer.GetWidth() == WIDTH);
    REQUIRE(srceBuffer.GetHeight() == HEIGHT);
    static constexpr auto TEST_PIXEL = Pixel{
        {TEST_R, TEST_G, TEST_B}
    };
    srceBuffer.Fill(TEST_PIXEL);

    auto destBuffer = PixelBuffer{
        {WIDTH, HEIGHT}
    };
    srceBuffer.CopyTo(destBuffer);

    REQUIRE(destBuffer.GetWidth() == WIDTH);
    REQUIRE(destBuffer.GetHeight() == HEIGHT);
    REQUIRE(GetPixelCount(srceBuffer, TEST_PIXEL) == GetPixelCount(destBuffer, TEST_PIXEL));
  }

  SECTION("PixelBuffer copy time")
  {
    static constexpr size_t NUM_LOOPS = 100;
    static constexpr auto TEST_PIXEL  = Pixel{
         {TEST_R, TEST_G, TEST_B}
    };

    auto intSrceBuff        = std::make_unique<std::vector<PixelIntType>>(WIDTH * HEIGHT);
    const auto intTestPixel = TEST_PIXEL.Rgba();
    std::fill(intSrceBuff->begin(), intSrceBuff->end(), intTestPixel);
    auto intDestBuff = std::make_unique<std::vector<PixelIntType>>(WIDTH * HEIGHT);

    auto startTime = high_resolution_clock::now();
    for (auto i = 0U; i < NUM_LOOPS; ++i)
    {
      std::memmove(intDestBuff->data(), intSrceBuff->data(), WIDTH * HEIGHT * sizeof(PixelIntType));
    }
    auto finishTime            = high_resolution_clock::now();
    const auto durationMemmove = std::chrono::duration_cast<microseconds>(finishTime - startTime);

    REQUIRE(std::count(intSrceBuff->cbegin(), intSrceBuff->cend(), intTestPixel) ==
            std::count(intDestBuff->cbegin(), intDestBuff->cend(), intTestPixel));

    auto srceBuffer = std::make_unique<PixelBuffer>(Dimensions{WIDTH, HEIGHT});
    srceBuffer->Fill(TEST_PIXEL);
    auto destBuffer = std::make_unique<PixelBuffer>(Dimensions{WIDTH, HEIGHT});

    startTime = high_resolution_clock::now();
    for (auto i = 0U; i < NUM_LOOPS; ++i)
    {
      srceBuffer->CopyTo(*destBuffer);
    }
    finishTime                = high_resolution_clock::now();
    const auto durationCopyTo = std::chrono::duration_cast<microseconds>(finishTime - startTime);

    REQUIRE(GetPixelCount(*srceBuffer, TEST_PIXEL) == GetPixelCount(*destBuffer, TEST_PIXEL));

    const auto tolerance = (durationCopyTo * 10) / 100;
    UNSCOPED_INFO("durationCopyTo.count() = " << durationCopyTo.count());
    UNSCOPED_INFO("durationMemmove.count() = " << durationMemmove.count());
    UNSCOPED_INFO("tolerance.count() = " << tolerance.count());
    REQUIRE(durationCopyTo < (durationMemmove + tolerance));
  }

  SECTION("PixelBuffer Get4RHBNeighbours")
  {
    auto buffer = PixelBuffer{
        {WIDTH, HEIGHT}
    };
    static constexpr auto TEST_PIXEL1 = Pixel{
        {TEST_R + 0, TEST_G + 0, TEST_B + 0}
    };
    static constexpr auto TEST_PIXEL2 = Pixel{
        {TEST_R + 1, TEST_G + 1, TEST_B + 1}
    };
    static constexpr auto TEST_PIXEL3 = Pixel{
        {TEST_R + 2, TEST_G + 2, TEST_B + 2}
    };
    static constexpr auto TEST_PIXEL4 = Pixel{
        {TEST_R + 3, TEST_G + 3, TEST_B + 3}
    };
    buffer.Fill(WHITE_PIXEL);

    static constexpr size_t X = 20;
    static constexpr size_t Y = 40;
    buffer(X, Y)              = TEST_PIXEL1;
    buffer(X + 1, Y)          = TEST_PIXEL2;
    buffer(X, Y + 1)          = TEST_PIXEL3;
    buffer(X + 1, Y + 1)      = TEST_PIXEL4;

    const auto pixel4RHBNeighbours = buffer.Get4RHBNeighbours(X, Y);

    REQUIRE(TEST_PIXEL1 == pixel4RHBNeighbours[0]);
    REQUIRE(TEST_PIXEL2 == pixel4RHBNeighbours[1]);
    REQUIRE(TEST_PIXEL3 == pixel4RHBNeighbours[2]);
    REQUIRE(TEST_PIXEL4 == pixel4RHBNeighbours[3]);
  }

  SECTION("PixelBuffer RowIter")
  {
    static constexpr auto TEST_PIXEL = Pixel{
        {TEST_R, TEST_G, TEST_B}
    };
    auto buffer = PixelBuffer{
        {WIDTH, HEIGHT}
    };
    buffer.Fill(WHITE_PIXEL);
    static constexpr size_t Y = 10;
    for (auto x = 0U; x < WIDTH; ++x)
    {
      buffer(x, Y) = TEST_PIXEL;
    }

    uint32_t count          = 0;
    const auto destRowIter  = buffer.GetRowIter(Y);
    const auto destRowBegin = std::get<0>(destRowIter);
    const auto destRowEnd   = std::get<1>(destRowIter);
    for (auto destRowBuff = destRowBegin; destRowBuff != destRowEnd; ++destRowBuff)
    {
      if (*destRowBuff == TEST_PIXEL)
      {
        count++;
      }
    }
    REQUIRE(count == WIDTH);
  }
}

} // namespace GOOM::UNIT_TESTS
