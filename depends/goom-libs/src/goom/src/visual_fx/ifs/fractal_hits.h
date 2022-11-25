#pragma once

#include "goom_graphic.h"
#include "goom_types.h"
#include "ifs_types.h"
#include "similitudes.h"

#include <cstdint>
#include <vector>

namespace GOOM::VISUAL_FX::IFS
{

class FractalHits
{
public:
  FractalHits() noexcept = delete;
  explicit FractalHits(const Dimensions& dimensions) noexcept;
  ~FractalHits() noexcept;
  FractalHits(const FractalHits&) noexcept                    = default;
  FractalHits(FractalHits&&) noexcept                         = default;
  auto operator=(const FractalHits&) noexcept -> FractalHits& = delete;
  auto operator=(FractalHits&&) noexcept -> FractalHits&      = delete;

  void Reset();
  void AddHit(int32_t x, int32_t y, const Similitude& simi);
  [[nodiscard]] auto GetBuffer() -> const std::vector<IfsPoint>&;
  [[nodiscard]] auto GetMaxHitCount() const -> uint32_t;

private:
  const Dimensions m_dimensions;
  struct HitInfo
  {
    uint32_t count = 0;
    Pixel color    = BLACK_PIXEL;
    const Similitude* simi{};
  };
  std::vector<std::vector<HitInfo>> m_hitInfo{GetHitInfo(m_dimensions)};
  [[nodiscard]] static auto GetHitInfo(const Dimensions& dimensions) noexcept
      -> std::vector<std::vector<HitInfo>>;
  uint32_t m_maxHitCount                = 0;
  static constexpr size_t HITS_ESTIMATE = 1000;
  std::vector<IfsPoint> m_hits{};
  std::vector<IfsPoint> m_buffer{};
};

inline auto FractalHits::GetMaxHitCount() const -> uint32_t
{
  return m_maxHitCount;
}

} // namespace GOOM::VISUAL_FX::IFS
