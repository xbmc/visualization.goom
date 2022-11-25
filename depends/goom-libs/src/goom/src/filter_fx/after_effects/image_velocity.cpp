#include "image_velocity.h"

#include "utils/name_value_pairs.h"

#include <string>

namespace GOOM::FILTER_FX::AFTER_EFFECTS
{

using UTILS::GetFullParamGroup;
using UTILS::NameValuePairs;
using UTILS::MATH::IGoomRand;

static constexpr auto AMPLITUDE_RANGE    = IGoomRand::NumberRange<float>{0.0025F, 0.0500F};
static constexpr auto COLOR_CUTOFF_RANGE = IGoomRand::NumberRange<float>{0.1F, 0.9F};
static constexpr auto ZOOM_FACTOR_RANGE  = IGoomRand::NumberRange<float>{0.5F, 1.0F};

static constexpr auto PROB_XY_COLOR_CUTOFFS_EQUAL = 0.5F;

ImageVelocity::ImageVelocity(const IGoomRand& goomRand, const std::string& resourcesDirectory)
  : m_goomRand{goomRand}, m_imageDisplacementList{resourcesDirectory, m_goomRand}
{
  if (!resourcesDirectory.empty())
  {
    SetRandomParams();
  }
}

auto ImageVelocity::SetRandomParams() -> void
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

auto ImageVelocity::GetNameValueParams(const std::string& paramGroup) const -> NameValuePairs
{
  return m_imageDisplacementList.GetNameValueParams(
      GetFullParamGroup({paramGroup, "ImageVelocity"}));
}

} // namespace GOOM::FILTER_FX::AFTER_EFFECTS
