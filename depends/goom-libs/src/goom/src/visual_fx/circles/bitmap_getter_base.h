#pragma once

#include "utils/graphics/image_bitmaps.h"

#include <cstddef>

namespace GOOM::VISUAL_FX::CIRCLES
{

class IBitmapGetter
{
public:
  IBitmapGetter() noexcept                               = default;
  IBitmapGetter(const IBitmapGetter&) noexcept           = delete;
  IBitmapGetter(IBitmapGetter&&) noexcept                = delete;
  virtual ~IBitmapGetter()                               = default;
  auto operator=(const IBitmapGetter&) -> IBitmapGetter& = delete;
  auto operator=(IBitmapGetter&&) -> IBitmapGetter&      = delete;

  [[nodiscard]] virtual auto GetBitmap(size_t size) const noexcept
      -> const UTILS::GRAPHICS::ImageBitmap& = 0;
};

} // namespace GOOM::VISUAL_FX::CIRCLES
