#include "similitudes.h"

#include "color/color_maps.h"
#include "color/random_color_maps.h"
#include "color/random_color_maps_groups.h"
#include "goom_config.h"
#include "utils/graphics/small_image_bitmaps.h"
#include "utils/math/goom_rand_base.h"
#include "utils/math/misc.h"

namespace GOOM::VISUAL_FX::IFS
{

using COLOR::RandomColorMaps;
using COLOR::RandomColorMapsGroups;
using UTILS::GRAPHICS::ImageBitmap;
using UTILS::GRAPHICS::SmallImageBitmaps;
using UTILS::MATH::DEGREES_180;
using UTILS::MATH::IGoomRand;
using UTILS::MATH::PI;

static constexpr auto NUM0_WEIGHT = 10.0F;
static constexpr auto NUM1_WEIGHT = 05.0F;
static constexpr auto NUM2_WEIGHT = 03.0F;
static constexpr auto NUM3_WEIGHT = 01.0F;

Similitudes::Similitudes(const IGoomRand& goomRand,
                         const SmallImageBitmaps& smallBitmaps)
  : m_goomRand{goomRand},
    m_smallBitmaps{smallBitmaps},
    m_colorMaps{RandomColorMapsGroups::MakeSharedAllMapsUnweighted(m_goomRand)},
    m_centreWeights{
        m_goomRand,
        {
            {CentreNums::NUM0, NUM0_WEIGHT},
            {CentreNums::NUM1, NUM1_WEIGHT},
            {CentreNums::NUM2, NUM2_WEIGHT},
            {CentreNums::NUM3, NUM3_WEIGHT},
        }
    }
{
  assert(m_centreWeights.GetNumElements() == CENTRE_LIST.size());

  Init();
  ResetCurrentIfsFunc();
}

Similitudes::~Similitudes() noexcept = default;

auto Similitudes::SetWeightedColorMaps(
    const std::shared_ptr<const RandomColorMaps>& weightedColorMaps) -> void
{
  m_colorMaps = weightedColorMaps;
}

auto Similitudes::Init() -> void
{
  InitCentre();
  ResetSimiGroups();
}

inline auto Similitudes::InitCentre() -> void
{
  const auto numCentres = 2 + static_cast<uint32_t>(m_centreWeights.GetRandomWeighted());

  m_numSimis = numCentres;

  m_centreAttributes = CENTRE_LIST.at(numCentres - 2);
}

inline auto Similitudes::ResetSimiGroups() -> void
{
  ResetSimiGroup(m_mainSimiGroup);
  for (auto i = 0U; i < NUM_EXTRA_SIMI_GROUPS; ++i)
  {
    ResetSimiGroup(m_extraSimiGroups[i]);
  }
}

inline auto Similitudes::ResetSimiGroup(SimiGroup& simiGroup) -> void
{
  simiGroup.resize(m_numSimis);
  RandomizeSimiGroup(simiGroup);
}

auto Similitudes::UpdateMainSimis(const Dbl uValue) -> void
{
  UpdateMainSimisDblPart(uValue);

  UpdateMainSimisFltPart();
}

inline auto Similitudes::UpdateMainSimisDblPart(const Dbl uValue) -> void
{
  const auto u   = uValue;
  const auto uSq = u * u;
  const auto v   = 1.0F - u;
  const auto vSq = v * v;

  const auto uValues = UValuesArray{
      vSq * v,
      3.0F * vSq * u,
      3.0F * v * uSq,
      u * uSq,
  };

  for (auto i = 0U; i < m_numSimis; ++i)
  {
    UpdateMainSimiDblPart(uValues, i, m_mainSimiGroup[i]);
  }
}

inline auto Similitudes::UpdateMainSimiDblPart(const UValuesArray& uValues,
                                               const size_t extraSimiIndex,
                                               Similitude& mainSimi) -> void
{
  mainSimi.m_dbl_cx = 0.0F;
  mainSimi.m_dbl_cy = 0.0F;

  mainSimi.m_dbl_r1 = 0.0F;
  mainSimi.m_dbl_r2 = 0.0F;

  mainSimi.m_dbl_A1 = 0.0F;
  mainSimi.m_dbl_A2 = 0.0F;

  for (auto j = 0U; j < NUM_EXTRA_SIMI_GROUPS; ++j)
  {
    mainSimi.m_dbl_cx += uValues[j] * m_extraSimiGroups[j][extraSimiIndex].m_dbl_cx;
    mainSimi.m_dbl_cy += uValues[j] * m_extraSimiGroups[j][extraSimiIndex].m_dbl_cy;

    mainSimi.m_dbl_r1 += uValues[j] * m_extraSimiGroups[j][extraSimiIndex].m_dbl_r1;
    mainSimi.m_dbl_r2 += uValues[j] * m_extraSimiGroups[j][extraSimiIndex].m_dbl_r2;

    mainSimi.m_dbl_A1 += uValues[j] * m_extraSimiGroups[j][extraSimiIndex].m_dbl_A1;
    mainSimi.m_dbl_A2 += uValues[j] * m_extraSimiGroups[j][extraSimiIndex].m_dbl_A2;
  }
}

inline auto Similitudes::UpdateMainSimisFltPart() -> void
{
  for (auto i = 0U; i < m_numSimis; ++i)
  {
    auto& mainSimi = m_mainSimiGroup[i];

    mainSimi.m_cx = MultByUnit(mainSimi.m_dbl_cx);
    mainSimi.m_cy = MultByUnit(mainSimi.m_dbl_cy);

    mainSimi.m_r1 = MultByUnit(mainSimi.m_dbl_r1);
    mainSimi.m_r2 = MultByUnit(mainSimi.m_dbl_r2);

    mainSimi.m_cosA1 = MultByUnit(std::cos(mainSimi.m_dbl_A1));
    mainSimi.m_sinA1 = MultByUnit(std::sin(mainSimi.m_dbl_A1));
    mainSimi.m_cosA2 = MultByUnit(std::cos(mainSimi.m_dbl_A2));
    mainSimi.m_sinA2 = MultByUnit(std::sin(mainSimi.m_dbl_A2));
  }
}

auto Similitudes::IterateSimis() -> void
{
  auto& extraSimiGroup0       = m_extraSimiGroups[0];
  auto& extraSimiGroup1       = m_extraSimiGroups[1];
  const auto& extraSimiGroup2 = m_extraSimiGroups[2];
  const auto& extraSimiGroup3 = m_extraSimiGroups[3];

  for (auto i = 0U; i < m_numSimis; ++i)
  {
    static constexpr auto GROUP3_FACTOR = 2.0F;
    extraSimiGroup1[i].m_dbl_cx =
        (GROUP3_FACTOR * extraSimiGroup3[i].m_dbl_cx) - extraSimiGroup2[i].m_dbl_cx;
    extraSimiGroup1[i].m_dbl_cy =
        (GROUP3_FACTOR * extraSimiGroup3[i].m_dbl_cy) - extraSimiGroup2[i].m_dbl_cy;

    extraSimiGroup1[i].m_dbl_r1 =
        (GROUP3_FACTOR * extraSimiGroup3[i].m_dbl_r1) - extraSimiGroup2[i].m_dbl_r1;
    extraSimiGroup1[i].m_dbl_r2 =
        (GROUP3_FACTOR * extraSimiGroup3[i].m_dbl_r2) - extraSimiGroup2[i].m_dbl_r2;

    extraSimiGroup1[i].m_dbl_A1 =
        (GROUP3_FACTOR * extraSimiGroup3[i].m_dbl_A1) - extraSimiGroup2[i].m_dbl_A1;
    extraSimiGroup1[i].m_dbl_A2 =
        (GROUP3_FACTOR * extraSimiGroup3[i].m_dbl_A2) - extraSimiGroup2[i].m_dbl_A2;

    extraSimiGroup0[i] = extraSimiGroup3[i];
  }

  RandomizeSimiGroup(m_extraSimiGroups[2]);
  RandomizeSimiGroup(m_extraSimiGroups[3]);
}

auto Similitudes::RandomizeSimiGroup(SimiGroup& simiGroup) const -> void
{
#if __cplusplus <= 201703L
  static const auto c_factor             = 0.8F * Get_1_minus_exp_neg_S(4.0);
  static const auto r1_1_minus_exp_neg_S = Get_1_minus_exp_neg_S(3.0);
  static const auto r2_1_minus_exp_neg_S = Get_1_minus_exp_neg_S(2.0);
  static const auto A1_factor            = 360.0F * Get_1_minus_exp_neg_S(4.0);
  static const auto A2_factor            = A1_factor;
#else
  static const constinit auto c_factor             = 0.8f * Get_1_minus_exp_neg_S(4.0);
  static const constinit auto r1_1_minus_exp_neg_S = Get_1_minus_exp_neg_S(3.0);
  static const constinit auto r2_1_minus_exp_neg_S = Get_1_minus_exp_neg_S(2.0);
  static const constinit auto A1_factor            = 360.0F * Get_1_minus_exp_neg_S(4.0);
  static const constinit auto A2_factor            = A1_factor;
#endif

  const auto r1Factor = m_centreAttributes.dr1Mean * r1_1_minus_exp_neg_S;
  const auto r2Factor = m_centreAttributes.dr2Mean * r2_1_minus_exp_neg_S;

  const auto colorMapGroup               = m_colorMaps->GetRandomGroup();
  static constexpr auto PROB_USE_BITMAPS = 0.7F;
  const auto useBitmaps                  = m_goomRand.ProbabilityOf(PROB_USE_BITMAPS);

  for (auto i = 0U; i < m_numSimis; ++i)
  {
    auto& simi = simiGroup[i];

    simi.m_dbl_cx = GaussRand(0.0, 4.0, c_factor);
    simi.m_dbl_cy = GaussRand(0.0, 4.0, c_factor);
    simi.m_dbl_r1 = GaussRand(m_centreAttributes.r1Mean, 3.0, r1Factor);
    simi.m_dbl_r2 = HalfGaussRand(m_centreAttributes.r2Mean, 2.0, r2Factor);
    simi.m_dbl_A1 = GaussRand(0.0F, 4.0F, A1_factor) * (PI / DEGREES_180);
    simi.m_dbl_A2 = GaussRand(0.0F, 4.0F, A2_factor) * (PI / DEGREES_180);
    simi.m_cx     = 0;
    simi.m_cy     = 0;
    simi.m_r1     = 0;
    simi.m_r2     = 0;
    simi.m_cosA1  = 0;
    simi.m_sinA1  = 0;
    simi.m_cosA2  = 0;
    simi.m_sinA2  = 0;

    simi.m_colorMap = &m_colorMaps->GetRandomColorMap(colorMapGroup);
    simi.m_color    = RandomColorMaps::GetRandomColor(
        m_goomRand, m_colorMaps->GetRandomColorMap(colorMapGroup), 0.0F, 1.0F);

    simi.m_currentPointBitmap = GetSimiBitmap(useBitmaps);
  }
}

auto Similitudes::GetSimiBitmap(const bool useBitmaps) const -> const ImageBitmap*
{
  if (not useBitmaps)
  {
    return nullptr;
  }

  static constexpr auto MIN_RES = 3U;
  static constexpr auto MAX_RES = 7U;
  const auto res                = m_goomRand.GetRandInRange(MIN_RES, MAX_RES);

  if (static constexpr auto PROB_SPHERE_BITMAP = 0.6F; m_goomRand.ProbabilityOf(PROB_SPHERE_BITMAP))
  {
    return &m_smallBitmaps.GetImageBitmap(SmallImageBitmaps::ImageNames::SPHERE, res);
  }

  return &m_smallBitmaps.GetImageBitmap(SmallImageBitmaps::ImageNames::CIRCLE, res);
}

inline auto Similitudes::Get_1_minus_exp_neg_S(const Dbl S) -> Dbl
{
  return 1.0F - std::exp(-S);
}

inline auto Similitudes::GaussRand(const Dbl c,
                                   const Dbl S,
                                   const Dbl A_mult_1_minus_exp_neg_S) const -> Dbl
{
  const auto x                    = m_goomRand.GetRandInRange(0.0F, 1.0F);
  const auto y                    = A_mult_1_minus_exp_neg_S * (1.0F - std::exp(-x * x * S));
  static constexpr auto PROB_HALF = 0.5F;
  return m_goomRand.ProbabilityOf(PROB_HALF) ? (c + y) : (c - y);
}

inline auto Similitudes::HalfGaussRand(const Dbl c,
                                       const Dbl S,
                                       const Dbl A_mult_1_minus_exp_neg_S) const -> Dbl
{
  const auto x = m_goomRand.GetRandInRange(0.0F, 1.0F);
  const auto y = A_mult_1_minus_exp_neg_S * (1.0F - std::exp(-x * x * S));
  return c + y;
}

auto Similitudes::ResetCurrentIfsFunc() -> void
{
  if (static constexpr auto PROB_REVERSED_IFS_FUNC = 0.3F;
      m_goomRand.ProbabilityOf(PROB_REVERSED_IFS_FUNC))
  {
    m_currentIfsFunc =
        [](const Similitude& simi, const Flt x1, const Flt y1, const Flt x2, const Flt y2)
    {
      return FltPoint{
          DivByUnit((x1 * simi.m_sinA1) - (y1 * simi.m_cosA1) + (x2 * simi.m_sinA2) -
                    (y2 * simi.m_cosA2)) +
              simi.m_cx,
          DivByUnit((x1 * simi.m_cosA1) + (y1 * simi.m_sinA1) + (x2 * simi.m_cosA2) +
                    (y2 * simi.m_sinA2)) +
              simi.m_cy,
      };
    };
  }
  else
  {
    m_currentIfsFunc =
        [](const Similitude& simi, const Flt x1, const Flt y1, const Flt x2, const Flt y2)
    {
      return FltPoint{
          DivByUnit((x1 * simi.m_cosA1) - (y1 * simi.m_sinA1) + (x2 * simi.m_cosA2) -
                    (y2 * simi.m_sinA2)) +
              simi.m_cx,
          DivByUnit((x1 * simi.m_sinA1) + (y1 * simi.m_cosA1) + (x2 * simi.m_sinA2) +
                    (y2 * simi.m_cosA2)) +
              simi.m_cy,
      };
    };
  }
}

} // namespace GOOM::VISUAL_FX::IFS
