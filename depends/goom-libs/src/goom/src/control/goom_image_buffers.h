#pragma once

#include "goom_types.h"

#include <array>
#include <memory>

namespace GOOM
{

class PixelBuffer;

namespace CONTROL
{

class GoomImageBuffers
{
public:
  GoomImageBuffers() noexcept = delete;
  explicit GoomImageBuffers(const Dimensions& dimensions) noexcept;
  GoomImageBuffers(const GoomImageBuffers&) noexcept = delete;
  GoomImageBuffers(GoomImageBuffers&&) noexcept      = delete;
  ~GoomImageBuffers() noexcept;
  auto operator=(const GoomImageBuffers&) noexcept -> GoomImageBuffers& = delete;
  auto operator=(GoomImageBuffers&&) noexcept -> GoomImageBuffers&      = delete;

  [[nodiscard]] auto GetP1() const noexcept -> PixelBuffer&;
  [[nodiscard]] auto GetP2() const noexcept -> PixelBuffer&;

  [[nodiscard]] auto GetOutputBuff() const noexcept -> PixelBuffer&;
  auto SetOutputBuff(const std::shared_ptr<PixelBuffer>& buffer) noexcept -> void;

  void RotateBuffers() noexcept;

private:
  static constexpr size_t MAX_NUM_BUFFS = 2;
  std::array<std::unique_ptr<PixelBuffer>, MAX_NUM_BUFFS> m_buffs;
  PixelBuffer* m_p1{m_buffs[0].get()};
  PixelBuffer* m_p2{m_buffs[1].get()};
  std::shared_ptr<PixelBuffer> m_outputBuff{};
  [[nodiscard]] static auto GetBuffs(const Dimensions& dimensions) noexcept
      -> std::array<std::unique_ptr<PixelBuffer>, MAX_NUM_BUFFS>;
};

inline auto GoomImageBuffers::GetP1() const noexcept -> PixelBuffer&
{
  return *m_p1;
}

inline auto GoomImageBuffers::GetP2() const noexcept -> PixelBuffer&
{
  return *m_p2;
}

inline auto GoomImageBuffers::GetOutputBuff() const noexcept -> PixelBuffer&
{
  return *m_outputBuff;
}

inline auto GoomImageBuffers::SetOutputBuff(const std::shared_ptr<PixelBuffer>& buffer) noexcept
    -> void
{
  m_outputBuff = buffer;
}

} // namespace CONTROL
} // namespace GOOM
