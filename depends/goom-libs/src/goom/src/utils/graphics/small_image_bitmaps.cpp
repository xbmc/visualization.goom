#include "small_image_bitmaps.h"

//#undef NO_LOGGING

#include "goom_config.h"
#include "logging.h"
#include "utils/enum_utils.h"
#include "utils/math/misc.h"

#include <array>
#include <format>
#include <string>

namespace GOOM::UTILS::GRAPHICS
{

using MATH::IsEven;

const std::array<std::string, NUM<SmallImageBitmaps::ImageNames>> SmallImageBitmaps::IMAGE_NAMES{
    "circle",
    "sphere",
    "pink-flower",
    "red-flower",
    "orange-flower",
    "white-flower",
};

SmallImageBitmaps::SmallImageBitmaps(const std::string& resourcesDirectory)
  : m_resourcesDirectory{resourcesDirectory}
{
  static constexpr auto BY_TWO = 2U;
  for (auto res = MIN_IMAGE_SIZE; res <= MAX_IMAGE_SIZE; res += BY_TWO)
  {
    for (auto i = 0U; i < NUM<ImageNames>; ++i)
    {
      const auto name = static_cast<ImageNames>(i);
      m_bitmapImages.try_emplace(GetImageKey(name, res), GetImageBitmapPtr(name, res));
      LogInfo("Loaded image bitmap: '{}'.", GetImageKey(name, res)); // NOLINT
    }
  }
}

SmallImageBitmaps::~SmallImageBitmaps() noexcept = default;

auto SmallImageBitmaps::GetImageBitmap(const ImageNames name, const size_t res) const
    -> const ImageBitmap&
{
  auto imageRes = res;
  if (IsEven(imageRes))
  {
    static constexpr auto MIN_EVEN_RES = 2U;
    imageRes                           = (MIN_EVEN_RES == res) ? (res + 1) : (res - 1);
  }
  return *m_bitmapImages.at(GetImageKey(name, imageRes));
}

auto SmallImageBitmaps::GetImageBitmapPtr(const ImageNames name,
                                          const size_t sizeOfImageSquare) const
    -> std::unique_ptr<const ImageBitmap>
{
  return std::make_unique<const ImageBitmap>(GetImageFilename(name, sizeOfImageSquare));
}

inline auto SmallImageBitmaps::GetImageKey(const ImageNames name, const size_t sizeOfImageSquare)
    -> std::string
{
  return std20::format("{}_{:02}", IMAGE_NAMES.at(static_cast<size_t>(name)), sizeOfImageSquare);
}

auto SmallImageBitmaps::GetImageFilename(const ImageNames name,
                                         const size_t sizeOfImageSquare) const -> std::string
{
  const auto imagesDir = m_resourcesDirectory + PATH_SEP + IMAGES_DIR;
  return std20::format("{}/{}{:02}x{:02}.png",
                       imagesDir,
                       IMAGE_NAMES.at(static_cast<size_t>(name)),
                       sizeOfImageSquare,
                       sizeOfImageSquare);
}

} // namespace GOOM::UTILS::GRAPHICS
