#include "goom_image_buffers.h"

#include "goom_graphic.h"

#include <cstdint>
#include <memory>

#if __cplusplus <= 201402L
namespace GOOM
{
namespace CONTROL
{
#else
namespace GOOM::CONTROL
{
#endif


GoomImageBuffers::GoomImageBuffers(const uint32_t width, const uint32_t height) noexcept
{
  SetResolution(width, height);
}

GoomImageBuffers::~GoomImageBuffers() noexcept = default;

void GoomImageBuffers::SetResolution(const uint32_t width, const uint32_t height)
{
  for (auto& b : m_buffs)
  {
    b = std::make_unique<PixelBuffer>(width, height);
  }

  m_p1 = m_buffs[0].get();
  m_p2 = m_buffs[1].get();
}

void GoomImageBuffers::RotateBuffers()
{
  std::swap(m_p1, m_p2);
}

#if __cplusplus <= 201402L
} // namespace CONTROL
} // namespace GOOM
#else
} // namespace GOOM::CONTROL
#endif
