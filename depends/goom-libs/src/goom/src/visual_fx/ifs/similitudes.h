#pragma once

#include "goom_graphic.h"
#include "ifs_types.h"
#include "utils/math/goom_rand_base.h"

#include <array>
#include <cstdint>
#include <functional>
#include <memory>
#include <vector>

namespace GOOM
{

namespace COLOR
{
class IColorMap;
class RandomColorMaps;
}

namespace UTILS::GRAPHICS
{
class ImageBitmap;
class SmallImageBitmaps;
}

namespace VISUAL_FX::IFS
{

class Similitude
{
public:
  [[nodiscard]] auto GetCPoint() const -> FltPoint;
  [[nodiscard]] auto GetColor() const -> Pixel;
  [[nodiscard]] auto GetColorMap() const -> const COLOR::IColorMap*;
  [[nodiscard]] auto GetCurrentPointBitmap() const -> const UTILS::GRAPHICS::ImageBitmap*;

private:
  friend class Similitudes;
  Dbl m_dbl_cx                                             = 0;
  Dbl m_dbl_cy                                             = 0;
  Dbl m_dbl_r1                                             = 0;
  Dbl m_dbl_r2                                             = 0;
  Dbl m_dbl_A1                                             = 0;
  Dbl m_dbl_A2                                             = 0;
  Flt m_cx                                                 = 0;
  Flt m_cy                                                 = 0;
  Flt m_r1                                                 = 0;
  Flt m_r2                                                 = 0;
  Flt m_cosA1                                              = 0;
  Flt m_sinA1                                              = 0;
  Flt m_cosA2                                              = 0;
  Flt m_sinA2                                              = 0;
  const COLOR::IColorMap* m_colorMap                       = nullptr;
  Pixel m_color                                            = BLACK_PIXEL;
  const UTILS::GRAPHICS::ImageBitmap* m_currentPointBitmap = nullptr;
};

class Similitudes
{
public:
  Similitudes(const UTILS::MATH::IGoomRand& goomRand,
              const UTILS::GRAPHICS::SmallImageBitmaps& smallBitmaps);
  Similitudes(const Similitudes&) noexcept                    = default;
  Similitudes(Similitudes&&) noexcept                         = default;
  ~Similitudes() noexcept;
  auto operator=(const Similitudes&) noexcept -> Similitudes& = delete;
  auto operator=(Similitudes&&) noexcept -> Similitudes&      = delete;

  auto Init() -> void;

  auto SetWeightedColorMaps(const std::shared_ptr<const COLOR::RandomColorMaps>& weightedColorMaps)
      -> void;

  auto UpdateMainSimis(Dbl uValue) -> void;
  auto IterateSimis() -> void;

  [[nodiscard]] auto GetNumSimis() const -> size_t;
  [[nodiscard]] auto GetMainSimiGroup() const -> const std::vector<Similitude>&;
  [[nodiscard]] auto GetSimiDepth() const -> uint32_t;

  auto ResetCurrentIfsFunc() -> void;
  [[nodiscard]] auto Transform(const Similitude& simi, const FltPoint& point0) const -> FltPoint;

private:
  using SimiGroup = std::vector<Similitude>;
  SimiGroup m_mainSimiGroup{};
  static constexpr size_t NUM_EXTRA_SIMI_GROUPS = 4;
  using ExtraSimiGroups                         = std::array<SimiGroup, NUM_EXTRA_SIMI_GROUPS>;
  ExtraSimiGroups m_extraSimiGroups{};
  uint32_t m_numSimis = 0;
  auto ResetSimiGroups() -> void;
  auto ResetSimiGroup(SimiGroup& simiGroup) -> void;
  auto RandomizeSimiGroup(SimiGroup& simiGroup) const -> void;
  auto UpdateMainSimisDblPart(Dbl uValue) -> void;
  using UValuesArray = std::array<Dbl, NUM_EXTRA_SIMI_GROUPS>;
  auto UpdateMainSimiDblPart(const UValuesArray& uValues,
                             size_t extraSimiIndex,
                             Similitude& mainSimi) -> void;
  auto UpdateMainSimisFltPart() -> void;
  [[nodiscard]] auto GetSimiBitmap(bool useBitmaps) const -> const UTILS::GRAPHICS::ImageBitmap*;

  const UTILS::MATH::IGoomRand& m_goomRand;
  const UTILS::GRAPHICS::SmallImageBitmaps& m_smallBitmaps;
  std::shared_ptr<const COLOR::RandomColorMaps> m_colorMaps;

  using IfsFunc = std::function<FltPoint(const Similitude& simi, Flt x1, Flt y1, Flt x2, Flt y2)>;
  IfsFunc m_currentIfsFunc{};

  struct CentreType
  {
    uint32_t depth;
    Dbl r1Mean;
    Dbl r2Mean;
    Dbl dr1Mean;
    Dbl dr2Mean;
  };
  // clang-format off
  static constexpr std::array CENTRE_LIST{
      CentreType{/*.depth = */ 10, /*.r1Mean = */ 0.7F, /*.r2Mean = */ 0.0F, /*.dr1Mean = */ 0.3F, /*.dr2Mean = */ 0.4F},
      CentreType{/*.depth = */  6, /*.r1Mean = */ 0.6F, /*.r2Mean = */ 0.0F, /*.dr1Mean = */ 0.4F, /*.dr2Mean = */ 0.3F},
      CentreType{/*.depth = */  4, /*.r1Mean = */ 0.5F, /*.r2Mean = */ 0.0F, /*.dr1Mean = */ 0.4F, /*.dr2Mean = */ 0.3F},
      CentreType{/*.depth = */  2, /*.r1Mean = */ 0.4F, /*.r2Mean = */ 0.0F, /*.dr1Mean = */ 0.5F, /*.dr2Mean = */ 0.3F},
  };
  // clang-format on
  enum class CentreNums
  {
    NUM0 = 0,
    NUM1,
    NUM2,
    NUM3,
    _num // unused, and marks the enum end
  };
  const UTILS::MATH::Weights<CentreNums> m_centreWeights;
  CentreType m_centreAttributes{};
  auto InitCentre() -> void;

  [[nodiscard]] auto GaussRand(Dbl c, Dbl S, Dbl A_mult_1_minus_exp_neg_S) const -> Dbl;
  [[nodiscard]] auto HalfGaussRand(Dbl c, Dbl S, Dbl A_mult_1_minus_exp_neg_S) const -> Dbl;
  [[nodiscard]] static auto Get_1_minus_exp_neg_S(Dbl S) -> Dbl;
};

inline auto Similitudes::GetNumSimis() const -> size_t
{
  return m_numSimis;
}

inline auto Similitudes::GetMainSimiGroup() const -> const std::vector<Similitude>&
{
  return m_mainSimiGroup;
}

inline auto Similitudes::GetSimiDepth() const -> uint32_t
{
  return m_centreAttributes.depth;
}

inline auto Similitudes::Transform(const Similitude& simi, const FltPoint& point0) const -> FltPoint
{
  const auto x1 = DivByUnit((point0.x - simi.m_cx) * simi.m_r1);
  const auto y1 = DivByUnit((point0.y - simi.m_cy) * simi.m_r1);

  const auto x2 = DivByUnit((+x1 - simi.m_cx) * simi.m_r2);
  const auto y2 = DivByUnit((-y1 - simi.m_cy) * simi.m_r2);

  return m_currentIfsFunc(simi, x1, y1, x2, y2);
}

inline auto Similitude::GetCPoint() const -> FltPoint
{
  return {m_cx, m_cy};
}

inline auto Similitude::GetColor() const -> Pixel
{
  return m_color;
}

inline auto Similitude::GetColorMap() const -> const COLOR::IColorMap*
{
  return m_colorMap;
}

inline auto Similitude::GetCurrentPointBitmap() const -> const UTILS::GRAPHICS::ImageBitmap*
{
  return m_currentPointBitmap;
}

} // namespace VISUAL_FX::IFS
} // namespace GOOM
