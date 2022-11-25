#include "image_zoom_in_coeffs.h"

#include "goom_config.h"
#include "utils/name_value_pairs.h"

#include <string>

namespace GOOM::FILTER_FX::FILTER_EFFECTS
{

using GOOM::UTILS::NameValuePairs;
using GOOM::UTILS::MATH::IGoomRand;

static constexpr auto AMPLITUDE_RANGE    = IGoomRand::NumberRange<float>{0.0025F, 0.01000F};
static constexpr auto COLOR_CUTOFF_RANGE = IGoomRand::NumberRange<float>{0.1F, 0.9F};
static constexpr auto ZOOM_FACTOR_RANGE  = IGoomRand::NumberRange<float>{0.10F, 1.0F};

static constexpr auto PROB_XY_COLOR_CUTOFFS_EQUAL = 0.5F;

ImageZoomInCoefficients::ImageZoomInCoefficients(const std::string& resourcesDirectory,
                                                 const IGoomRand& goomRand)
  : m_goomRand{goomRand}, m_imageDisplacementList{resourcesDirectory, m_goomRand}
{
  if (!resourcesDirectory.empty())
  {
    DoSetRandomParams();
  }
}

auto ImageZoomInCoefficients::SetRandomParams() noexcept -> void
{
  DoSetRandomParams();

  Ensures(GetZoomInCoefficientsViewport().GetViewportWidth() == NormalizedCoords::COORD_WIDTH);
}

inline auto ImageZoomInCoefficients::DoSetRandomParams() noexcept -> void
{
  m_imageDisplacementList.SetRandomImageDisplacement();

  const auto xColorCutoff = m_goomRand.GetRandInRange(COLOR_CUTOFF_RANGE);

  m_imageDisplacementList.SetParams({
      m_goomRand.GetRandInRange(AMPLITUDE_RANGE),
      xColorCutoff,
      m_goomRand.ProbabilityOf(PROB_XY_COLOR_CUTOFFS_EQUAL)
          ? xColorCutoff
          : m_goomRand.GetRandInRange(COLOR_CUTOFF_RANGE),
      m_goomRand.GetRandInRange(ZOOM_FACTOR_RANGE),
  });
}

auto ImageZoomInCoefficients::GetZoomInCoefficientsEffectNameValueParams() const noexcept
    -> NameValuePairs
{
  static constexpr auto* IMAGE_PARAM_GROUP = "ImageZoomInCoeffs";
  return m_imageDisplacementList.GetNameValueParams(IMAGE_PARAM_GROUP);
}

} // namespace GOOM::FILTER_FX::FILTER_EFFECTS
