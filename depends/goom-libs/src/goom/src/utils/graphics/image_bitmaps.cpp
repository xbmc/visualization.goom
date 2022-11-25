#include "image_bitmaps.h"

#define STB_IMAGE_IMPLEMENTATION
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable : 4068) // unknown pragma 'GCC'
#pragma warning(disable : 4296) // '>=': expression is always true
#endif
#include "../stb_image.h"
#ifdef _MSC_VER
#pragma warning(pop)
#endif

#include <format>
#include <stdexcept>

namespace GOOM::UTILS::GRAPHICS
{

auto ImageBitmap::Resize(const size_t width, const size_t height) noexcept -> void
{
  m_width  = static_cast<uint32_t>(width);
  m_height = static_cast<uint32_t>(height);
  m_buff.resize(static_cast<size_t>(m_width) * static_cast<size_t>(m_height));
}

inline auto ImageBitmap::SetPixel(const size_t x, const size_t y, const RGB& pixel) noexcept -> void
{
  m_buff.at((y * m_width) + x) = pixel;
}

void ImageBitmap::Load(const std::string& imageFilename)
{
  m_filename = imageFilename;
  const auto [rgbImage, width, height, bpp] = GetRGBImage();

  const auto* rgbPtr = rgbImage;
  Resize(static_cast<size_t>(width), static_cast<size_t>(height));
  for (auto y = 0U; y < GetHeight(); ++y)
  {
    for (auto x = 0U; x < GetWidth(); ++x)
    {
      auto blue = *rgbPtr;
      ++rgbPtr;
      auto green = *rgbPtr;
      ++rgbPtr;
      auto red = *rgbPtr;
      ++rgbPtr;
      const auto alpha = *rgbPtr;
      ++rgbPtr;

      if (0 == alpha)
      {
        red   = 0;
        green = 0;
        blue  = 0;
      }

      SetPixel(x, y, RGB{/*.r = */ red, /*.g = */ green, /*.b = */ blue, /*.a = */ alpha});
    }
  }

  ::stbi_image_free(rgbImage);
}

auto ImageBitmap::GetRGBImage() const -> std::tuple<uint8_t*, int32_t, int32_t, int32_t>
{
  try
  {
    static constexpr auto DESIRED_CHANNELS = 4;

    auto width  = 0;
    auto height = 0;
    auto bpp    = 0;
    auto* rgbImage = ::stbi_load(m_filename.c_str(), &width, &height, &bpp, DESIRED_CHANNELS);
    if (!rgbImage)
    {
      throw std::runtime_error(std20::format(R"(Could not load image file "{}".)", m_filename));
    }
    if ((0 == width) || (0 == height) || (0 == bpp))
    {
      throw std::runtime_error(
          std20::format("Error loading image \"{}\". width = {}, height = {}, bpp = {}.",
                        m_filename,
                        width,
                        height,
                        bpp));
    }

    return {rgbImage, width, height, bpp};
  }
  catch (const std::exception& e)
  {
    throw std::runtime_error(
        std20::format(R"(Could not load image file "{}". Exception: "{}".)", m_filename, e.what()));
  }
}

} // namespace GOOM::UTILS::GRAPHICS
