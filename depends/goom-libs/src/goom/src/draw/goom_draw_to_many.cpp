#include "goom_draw_to_many.h"

#include "goom_config.h"
#include "goom_graphic.h"
#include "goom_types.h"

#include <cstdint>
#include <vector>

namespace GOOM::DRAW
{

GoomDrawToMany::GoomDrawToMany(const Dimensions& dimensions,
                               const std::vector<IGoomDraw*>& manyDraws) noexcept
  : IGoomDraw{dimensions}, m_manyDraws{manyDraws}
{
  Expects(not manyDraws.empty());
}

auto GoomDrawToMany::GetPixel(const Point2dInt point) const noexcept -> Pixel
{
  return m_manyDraws[0]->GetPixel(point);
}

auto GoomDrawToMany::DrawPixelsUnblended(const Point2dInt point,
                                         const MultiplePixels& colors) noexcept -> void
{
  for (auto* const draw : m_manyDraws)
  {
    draw->DrawPixelsUnblended(point, colors);
  }
}

auto GoomDrawToMany::DrawPixelsToDevice(const Point2dInt point,
                                        const MultiplePixels& colors,
                                        [[maybe_unused]] const uint32_t intBuffIntensity) noexcept
    -> void
{
  for (auto* const draw : m_manyDraws)
  {
    draw->DrawPixels(point, colors);
  }
}

} // namespace GOOM::DRAW
