#include "fractal_hits.h"

#include "color/color_utils.h"

namespace GOOM::VISUAL_FX::IFS
{

using COLOR::GetColorAverage;

FractalHits::FractalHits(const Dimensions& dimensions) noexcept : m_dimensions{dimensions}
{
  m_hits.reserve(HITS_ESTIMATE);
}

FractalHits::~FractalHits() noexcept = default;

auto FractalHits::GetHitInfo(const Dimensions& dimensions) noexcept
    -> std::vector<std::vector<HitInfo>>
{
  auto hitInfo = std::vector<std::vector<HitInfo>>(dimensions.GetHeight());
  for (auto& xHit : hitInfo)
  {
    xHit.resize(dimensions.GetWidth());
  }
  return hitInfo;
}

void FractalHits::Reset()
{
  for (const auto& hit : m_hits)
  {
    auto& hitInfo = m_hitInfo[hit.GetY()][hit.GetX()];
    hitInfo.count = 0;
  }

  m_hits.clear();
  m_maxHitCount = 0;
}

void FractalHits::AddHit(const int32_t x, const int32_t y, const Similitude& simi)
{
  if ((x < 0) or (y < 0))
  {
    return;
  }
  if ((x >= m_dimensions.GetIntWidth()) or (y >= m_dimensions.GetIntHeight()))
  {
    return;
  }

  const auto ux = static_cast<uint32_t>(x);
  const auto uy = static_cast<uint32_t>(y);

  auto& hitInfo = m_hitInfo[uy][ux];

  ++hitInfo.count;
  if (hitInfo.count > m_maxHitCount)
  {
    m_maxHitCount = hitInfo.count;
  }

  hitInfo.simi  = &simi;
  if (hitInfo.count > 1)
  {
    hitInfo.color = GetColorAverage(hitInfo.color, simi.GetColor());
  }
  else
  {
    hitInfo.color = simi.GetColor();
    m_hits.emplace_back(ux, uy, 1);
  }
}

auto FractalHits::GetBuffer() -> const std::vector<IfsPoint>&
{
  m_buffer.clear();
  m_buffer.reserve(m_hits.size());

  for (const auto& hit : m_hits)
  {
    auto updatedHit     = hit;
    const auto& hitInfo = m_hitInfo[hit.GetY()][hit.GetX()];

    updatedHit.SetCount(hitInfo.count);
    updatedHit.SetColor(hitInfo.color);
    updatedHit.SetSimi(hitInfo.simi);

    m_buffer.emplace_back(updatedHit);
  }

  return m_buffer;
}

} // namespace GOOM::VISUAL_FX::IFS
