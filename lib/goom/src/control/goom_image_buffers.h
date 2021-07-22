#ifndef VISUALIZATION_GOOM_GOOM_IMAGE_BUFFERS_H
#define VISUALIZATION_GOOM_GOOM_IMAGE_BUFFERS_H

#include <array>
#include <cstdint>
#include <memory>

#if __cplusplus <= 201402L
namespace GOOM
{

class PixelBuffer;

namespace CONTROL
{
#else
namespace GOOM::CONTROL
{
#endif

class GoomImageBuffers
{
public:
  GoomImageBuffers() noexcept = delete;
  GoomImageBuffers(uint32_t width, uint32_t height) noexcept;
  ~GoomImageBuffers() noexcept;
  GoomImageBuffers(const GoomImageBuffers&) noexcept = delete;
  GoomImageBuffers(GoomImageBuffers&&) noexcept = delete;
  auto operator=(const GoomImageBuffers&) -> GoomImageBuffers& = delete;
  auto operator=(GoomImageBuffers&&) -> GoomImageBuffers& = delete;

  void SetResolution(uint32_t width, uint32_t height);

  [[nodiscard]] auto GetP1() const -> PixelBuffer& { return *m_p1; }
  [[nodiscard]] auto GetP2() const -> PixelBuffer& { return *m_p2; }

  [[nodiscard]] auto GetOutputBuff() const -> PixelBuffer& { return *m_outputBuff; }
  void SetOutputBuff(PixelBuffer& val) { m_outputBuff = &val; }

  void RotateBuffers();

private:
  static constexpr size_t MAX_NUM_BUFFS = 2;
  std::array<std::unique_ptr<PixelBuffer>, MAX_NUM_BUFFS> m_buffs{};
  PixelBuffer* m_p1{};
  PixelBuffer* m_p2{};
  PixelBuffer* m_outputBuff{};
};

#if __cplusplus <= 201402L
} // namespace CONTROL
} // namespace GOOM
#else
} // namespace GOOM::CONTROL
#endif

#endif //VISUALIZATION_GOOM_GOOM_IMAGE_BUFFERS_H
