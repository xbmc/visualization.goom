#include "goom_image_buffers.h"

#include "goom_graphic.h"
#include "goom_types.h"

#include <memory>

namespace GOOM::CONTROL
{

auto GoomImageBuffers::GetBuffs(const Dimensions& dimensions) noexcept
    -> std::array<std::unique_ptr<PixelBuffer>, MAX_NUM_BUFFS>
{
  auto buffs = std::array<std::unique_ptr<PixelBuffer>, MAX_NUM_BUFFS>{};
  for (auto& buff : buffs)
  {
    buff = std::make_unique<PixelBuffer>(dimensions);
  }
  return buffs;
}

GoomImageBuffers::GoomImageBuffers(const Dimensions& dimensions) noexcept
  : m_buffs{GetBuffs(dimensions)}
{
}

GoomImageBuffers::~GoomImageBuffers() noexcept = default;

void GoomImageBuffers::RotateBuffers() noexcept
{
  std::swap(m_p1, m_p2);
}

} // namespace GOOM::CONTROL
