#pragma once

#include "bitmap_getter_base.h"
#include "utils/graphics/image_bitmaps.h"
#include "utils/graphics/small_image_bitmaps.h"
#include "utils/math/goom_rand_base.h"

#include <cstddef>

namespace GOOM::VISUAL_FX::CIRCLES
{

class BitmapGetter : public IBitmapGetter
{
public:
  static constexpr size_t MIN_DOT_DIAMETER = 5;
  static constexpr size_t MAX_DOT_DIAMETER = 21;

  BitmapGetter(const UTILS::MATH::IGoomRand& goomRand,
               const UTILS::GRAPHICS::SmallImageBitmaps& smallBitmaps) noexcept;

  [[nodiscard]] auto GetBitmap(size_t size) const noexcept
      -> const UTILS::GRAPHICS::ImageBitmap& override;

  auto ChangeCurrentBitmap() noexcept -> void;

private:
  const UTILS::GRAPHICS::SmallImageBitmaps& m_smallBitmaps;
  const UTILS::MATH::Weights<UTILS::GRAPHICS::SmallImageBitmaps::ImageNames> m_bitmapTypes;
  UTILS::GRAPHICS::SmallImageBitmaps::ImageNames m_currentBitmapName{
      m_bitmapTypes.GetRandomWeighted()};
};

} // namespace GOOM::VISUAL_FX::CIRCLES
