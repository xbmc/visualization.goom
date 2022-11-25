#pragma once

#include "filter_fx/filter_buffers.h"
#include "filter_fx/normalized_coords.h"
#include "point2d.h"
#include "utils/graphics/image_bitmaps.h"
#include "utils/math/goom_rand_base.h"

#include <memory>
#include <stdexcept>

namespace GOOM::FILTER_FX::FILTER_UTILS
{

class ImageDisplacement
{
public:
  ImageDisplacement(const std::string& imageFilename, const UTILS::MATH::IGoomRand& goomRand);
  ImageDisplacement(const ImageDisplacement&) noexcept = delete;
  ImageDisplacement(ImageDisplacement&&) noexcept      = default;
  ~ImageDisplacement() noexcept;
  auto operator=(const ImageDisplacement&) noexcept -> ImageDisplacement& = delete;
  auto operator=(ImageDisplacement&&) noexcept -> ImageDisplacement&      = delete;

  [[nodiscard]] auto GetImageFilename() const -> std::string;
  [[nodiscard]] auto GetXColorCutoff() const -> float;
  [[nodiscard]] auto GetYColorCutoff() const -> float;
  auto SetXyColorCutoffs(float xColorCutoff, float yColorCutoff) -> void;

  [[nodiscard]] auto GetZoomFactor() const -> float;
  auto SetZoomFactor(float value) -> void;

  [[nodiscard]] auto GetAmplitude() const -> float;
  auto SetAmplitude(float value) -> void;

  [[nodiscard]] auto GetDisplacementVector(const NormalizedCoords& normalizedCoords) const
      -> Point2dFlt;

private:
  std::unique_ptr<UTILS::GRAPHICS::ImageBitmap> m_imageBuffer;
  const std::string m_imageFilename;
  const int32_t m_xMax{static_cast<int32_t>(m_imageBuffer->GetWidth() - 1)};
  const int32_t m_yMax{static_cast<int32_t>(m_imageBuffer->GetHeight() - 1)};
  const NormalizedCoordsConverter m_normalizedCoordsConverter{
      {m_imageBuffer->GetWidth(), m_imageBuffer->GetHeight()},
      ZoomFilterBuffers::MIN_SCREEN_COORD_ABS_VAL,
      false
  };
  float m_zoomFactor                    = 1.0F;
  float m_amplitude                     = 1.0F;
  static constexpr float INITIAL_CUTOFF = 0.5F;
  float m_xColorCutoff                  = INITIAL_CUTOFF;
  float m_yColorCutoff                  = INITIAL_CUTOFF;
  [[nodiscard]] auto NormalizedCoordsToImagePoint(const NormalizedCoords& normalizedCoords) const
      -> Point2dInt;
  [[nodiscard]] auto ColorToNormalizedDisplacement(const Pixel& color) const -> Point2dFlt;
};

inline auto ImageDisplacement::GetImageFilename() const -> std::string
{
  return m_imageFilename;
}

inline auto ImageDisplacement::GetXColorCutoff() const -> float
{
  return m_xColorCutoff;
}

inline auto ImageDisplacement::GetYColorCutoff() const -> float
{
  return m_yColorCutoff;
}

inline auto ImageDisplacement::SetXyColorCutoffs(const float xColorCutoff, const float yColorCutoff)
    -> void
{
  m_xColorCutoff = xColorCutoff;
  m_yColorCutoff = yColorCutoff;
}

inline auto ImageDisplacement::GetZoomFactor() const -> float
{
  return m_zoomFactor;
}

inline auto ImageDisplacement::SetZoomFactor(const float value) -> void
{
  if (value <= 0.0F)
  {
    throw std::logic_error("Negative zoom factor.");
  }
  m_zoomFactor = value;
}

inline auto ImageDisplacement::GetAmplitude() const -> float
{
  return m_amplitude;
}

inline auto ImageDisplacement::SetAmplitude(const float value) -> void
{
  if (value <= 0.0F)
  {
    throw std::logic_error("Negative amplitude.");
  }
  m_amplitude = value;
}

} // namespace GOOM::FILTER_FX::FILTER_UTILS
