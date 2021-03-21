#include "graphics/image_bitmaps.h"

#include "goom/goom_graphic.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../stb_image.h"

#include <format>
#include <stdexcept>

#if __cplusplus <= 201402L
namespace GOOM
{
namespace UTILS
{
#else
namespace GOOM::UTILS
{
#endif

void ImageBitmap::Load(std::string imageFilename)
{
  m_filename = std::move(imageFilename);

  int width{};
  int height{};
  int bpp{};
  const uint8_t* rgbImage{};
  try
  {
    rgbImage = stbi_load(m_filename.c_str(), &width, &height, &bpp, 4);
  }
  catch (std::exception& e)
  {
    throw std::runtime_error(
        std20::format(R"(Could not load image file "{}". Exception: "{}".)", m_filename, e.what()));
  }

  if (!rgbImage)
  {
    throw std::runtime_error(std20::format(R"(Could not load image file "{}".)", m_filename));
  }

  if (width == 0 || height == 0 || bpp == 0)
  {
    throw std::runtime_error(
        std20::format("Error loading image \"{}\". width = {}, height = {}, bpp = {}.", m_filename,
                      width, height, bpp));
  }

  const uint8_t* rgbPtr = rgbImage;
  Resize(static_cast<size_t>(width), static_cast<size_t>(height));
  for (size_t y = 0; y < GetHeight(); ++y)
  {
    for (size_t x = 0; x < GetWidth(); ++x)
    {
      uint8_t r = *rgbPtr;
      rgbPtr++;
      uint8_t g = *rgbPtr;
      rgbPtr++;
      uint8_t b = *rgbPtr;
      rgbPtr++;
      const uint8_t a = *rgbPtr;
      rgbPtr++;

      if (a == 0)
      {
        r = 0;
        g = 0;
        b = 0;
      }

      (*this)(x, y) = Pixel{/*.channels*/ {/*.r = */ r, /*.g = */ g, /*.b = */ b, /*.a = */ a}};
    }
  }

  stbi_image_free((void*)(rgbImage));
}

#if __cplusplus <= 201402L
} // namespace UTILS
} // namespace GOOM
#else
} // namespace GOOM::UTILS
#endif
