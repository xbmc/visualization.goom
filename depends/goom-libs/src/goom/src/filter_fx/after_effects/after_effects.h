#pragma once

#include "filter_fx/after_effects/hypercos.h"
#include "filter_fx/after_effects/image_velocity.h"
#include "filter_fx/after_effects/noise.h"
#include "filter_fx/after_effects/planes.h"
#include "filter_fx/after_effects/rotation.h"
#include "filter_fx/after_effects/tan_effect.h"
#include "filter_fx/after_effects/xy_lerp_effect.h"
#include "utils/propagate_const.h"

#include <memory>

namespace GOOM::FILTER_FX::AFTER_EFFECTS
{

class AfterEffects
{
public:
  AfterEffects(std::unique_ptr<Hypercos>&& hypercos,
               std::unique_ptr<ImageVelocity>&& imageVelocity,
               std::unique_ptr<Noise>&& noise,
               std::unique_ptr<Planes>&& planes,
               std::unique_ptr<Rotation>&& rotation,
               std::unique_ptr<TanEffect>&& tanEffect,
               std::unique_ptr<XYLerpEffect>&& xyLerpEffect) noexcept;
  AfterEffects() noexcept                    = delete;
  AfterEffects(const AfterEffects&) noexcept = delete;
  AfterEffects(AfterEffects&&) noexcept      = default;
  ~AfterEffects() noexcept;
  auto operator=(const AfterEffects&) noexcept -> AfterEffects& = delete;
  auto operator=(AfterEffects&&) noexcept -> AfterEffects&      = delete;

  [[nodiscard]] auto GetHypercos() const noexcept -> const Hypercos&;
  [[nodiscard]] auto GetHypercos() noexcept -> Hypercos&;
  [[nodiscard]] auto GetImageVelocity() const noexcept -> const ImageVelocity&;
  [[nodiscard]] auto GetImageVelocity() noexcept -> ImageVelocity&;
  [[nodiscard]] auto GetNoise() const noexcept -> const Noise&;
  [[nodiscard]] auto GetNoise() noexcept -> Noise&;
  [[nodiscard]] auto GetPlanes() const noexcept -> const Planes&;
  [[nodiscard]] auto GetPlanes() noexcept -> Planes&;
  [[nodiscard]] auto GetRotation() const noexcept -> const Rotation&;
  [[nodiscard]] auto GetRotation() noexcept -> Rotation&;
  [[nodiscard]] auto GetTanEffect() const noexcept -> const TanEffect&;
  [[nodiscard]] auto GetTanEffect() noexcept -> TanEffect&;
  [[nodiscard]] auto GetXYLerpEffect() const noexcept -> const XYLerpEffect&;
  [[nodiscard]] auto GetXYLerpEffect() noexcept -> XYLerpEffect&;

private:
  std::experimental::propagate_const<std::unique_ptr<Hypercos>> m_hypercos;
  std::experimental::propagate_const<std::unique_ptr<ImageVelocity>> m_imageVelocity;
  std::experimental::propagate_const<std::unique_ptr<Noise>> m_noise;
  std::experimental::propagate_const<std::unique_ptr<Planes>> m_planes;
  std::experimental::propagate_const<std::unique_ptr<Rotation>> m_rotation;
  std::experimental::propagate_const<std::unique_ptr<TanEffect>> m_tanEffect;
  std::experimental::propagate_const<std::unique_ptr<XYLerpEffect>> m_xyLerpEffect;
};

[[nodiscard]] auto GetStandardAfterEffects(const UTILS::MATH::IGoomRand& goomRand,
                                           const std::string& resourcesDirectory) -> AfterEffects;

inline auto AfterEffects::GetHypercos() const noexcept -> const Hypercos&
{
  return *m_hypercos;
}

inline auto AfterEffects::GetHypercos() noexcept -> Hypercos&
{
  return *m_hypercos;
}

inline auto AfterEffects::GetImageVelocity() const noexcept -> const ImageVelocity&
{
  return *m_imageVelocity;
}

inline auto AfterEffects::GetImageVelocity() noexcept -> ImageVelocity&
{
  return *m_imageVelocity;
}

inline auto AfterEffects::GetNoise() const noexcept -> const Noise&
{
  return *m_noise;
}

inline auto AfterEffects::GetNoise() noexcept -> Noise&
{
  return *m_noise;
}

inline auto AfterEffects::GetPlanes() const noexcept -> const Planes&
{
  return *m_planes;
}

inline auto AfterEffects::GetPlanes() noexcept -> Planes&
{
  return *m_planes;
}

inline auto AfterEffects::GetRotation() const noexcept -> const Rotation&
{
  return *m_rotation;
}

inline auto AfterEffects::GetRotation() noexcept -> Rotation&
{
  return *m_rotation;
}

inline auto AfterEffects::GetTanEffect() const noexcept -> const TanEffect&
{
  return *m_tanEffect;
}

inline auto AfterEffects::GetTanEffect() noexcept -> TanEffect&
{
  return *m_tanEffect;
}

inline auto AfterEffects::GetXYLerpEffect() const noexcept -> const XYLerpEffect&
{
  return *m_xyLerpEffect;
}

inline auto AfterEffects::GetXYLerpEffect() noexcept -> XYLerpEffect&
{
  return *m_xyLerpEffect;
}

} // namespace GOOM::FILTER_FX::AFTER_EFFECTS
