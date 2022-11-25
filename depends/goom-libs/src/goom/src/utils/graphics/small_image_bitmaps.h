#pragma once

#include "utils/enum_utils.h"
#include "utils/graphics/image_bitmaps.h"

#include <array>
#include <map>
#include <memory>

namespace GOOM::UTILS::GRAPHICS
{

class SmallImageBitmaps
{
public:
  enum class ImageNames
  {
    CIRCLE,
    SPHERE,
    PINK_FLOWER,
    RED_FLOWER,
    ORANGE_FLOWER,
    WHITE_FLOWER,
    _num // unused, and marks the enum end
  };
  static constexpr size_t MIN_IMAGE_SIZE = 3;
  static constexpr size_t MAX_IMAGE_SIZE = 21;

  explicit SmallImageBitmaps(const std::string& resourcesDirectory);
  SmallImageBitmaps(const SmallImageBitmaps&) noexcept = delete;
  SmallImageBitmaps(SmallImageBitmaps&&) noexcept      = delete;
  ~SmallImageBitmaps() noexcept;
  auto operator=(const SmallImageBitmaps&) noexcept -> SmallImageBitmaps& = delete;
  auto operator=(SmallImageBitmaps&&) noexcept -> SmallImageBitmaps&      = delete;

  auto GetImageBitmap(ImageNames name, size_t res) const -> const ImageBitmap&;
  // void AddImageBitmap(const std::string& name, size_t res);

private:
  static const std::array<std::string, NUM<ImageNames>> IMAGE_NAMES;
  std::string m_resourcesDirectory;
  std::map<std::string, std::unique_ptr<const ImageBitmap>, std::less<>> m_bitmapImages{};
  auto GetImageBitmapPtr(ImageNames name, size_t sizeOfImageSquare) const
      -> std::unique_ptr<const ImageBitmap>;
  static auto GetImageKey(ImageNames name, size_t sizeOfImageSquare) -> std::string;
  auto GetImageFilename(ImageNames name, size_t sizeOfImageSquare) const -> std::string;
};

} // namespace GOOM::UTILS::GRAPHICS
