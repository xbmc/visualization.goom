#include "bitmap_getter.h"

#include "utils/graphics/image_bitmaps.h"
#include "utils/graphics/small_image_bitmaps.h"
#include "utils/math/goom_rand_base.h"

namespace GOOM::VISUAL_FX::CIRCLES
{

using UTILS::GRAPHICS::SmallImageBitmaps;

static constexpr auto IMAGE_NAMES_CIRCLE_WEIGHT        = 05.0F;
static constexpr auto IMAGE_NAMES_SPHERE_WEIGHT        = 05.0F;
static constexpr auto IMAGE_NAMES_ORANGE_FLOWER_WEIGHT = 20.0F;
static constexpr auto IMAGE_NAMES_PINK_FLOWER_WEIGHT   = 20.0F;
static constexpr auto IMAGE_NAMES_RED_FLOWER_WEIGHT    = 20.0F;
static constexpr auto IMAGE_NAMES_WHITE_FLOWER_WEIGHT  = 10.0F;

BitmapGetter::BitmapGetter(const UTILS::MATH::IGoomRand& goomRand,
                           const SmallImageBitmaps& smallBitmaps) noexcept
  : m_smallBitmaps{smallBitmaps},
    m_bitmapTypes{
      goomRand,
      {
        {SmallImageBitmaps::ImageNames::CIRCLE,        IMAGE_NAMES_CIRCLE_WEIGHT},
        {SmallImageBitmaps::ImageNames::SPHERE,        IMAGE_NAMES_SPHERE_WEIGHT},
        {SmallImageBitmaps::ImageNames::ORANGE_FLOWER, IMAGE_NAMES_ORANGE_FLOWER_WEIGHT},
        {SmallImageBitmaps::ImageNames::PINK_FLOWER,   IMAGE_NAMES_PINK_FLOWER_WEIGHT},
        {SmallImageBitmaps::ImageNames::RED_FLOWER,    IMAGE_NAMES_RED_FLOWER_WEIGHT},
        {SmallImageBitmaps::ImageNames::WHITE_FLOWER,  IMAGE_NAMES_WHITE_FLOWER_WEIGHT},
      }
    }
{
}

auto BitmapGetter::GetBitmap(const size_t size) const noexcept
    -> const UTILS::GRAPHICS::ImageBitmap&
{
  return m_smallBitmaps.GetImageBitmap(m_currentBitmapName,
                                       std::clamp(size, MIN_DOT_DIAMETER, MAX_DOT_DIAMETER));
}

auto BitmapGetter::ChangeCurrentBitmap() noexcept -> void
{
  m_currentBitmapName = m_bitmapTypes.GetRandomWeighted();
}

} // namespace GOOM::VISUAL_FX::CIRCLES
