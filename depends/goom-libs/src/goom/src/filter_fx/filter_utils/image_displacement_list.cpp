#include "image_displacement_list.h"

#include "goom_config.h"
#include "utils/name_value_pairs.h"

#include <cstdint>

namespace GOOM::FILTER_FX::FILTER_UTILS
{

using UTILS::GetPair;
using UTILS::NameValuePairs;
using UTILS::MATH::IGoomRand;

const std::vector<std::string> ImageDisplacementList::IMAGE_FILENAMES{
    "pattern1.jpg",
    "pattern2.jpg",
    "pattern3.jpg",
    "pattern4.jpg",
    "pattern5.jpg",
    "chameleon-tail.jpg",
    "mountain_sunset.png",
};

ImageDisplacementList::ImageDisplacementList(const std::string& resourcesDirectory,
                                             const IGoomRand& goomRand)
  : m_resourcesDirectory{resourcesDirectory}, m_goomRand{goomRand}
{
  if (m_resourcesDirectory.empty())
  {
    return;
  }

  for (const auto& imageFilename : IMAGE_FILENAMES)
  {
    m_imageDisplacements.emplace_back(GetImageFilename(imageFilename), m_goomRand);
  }
}

auto ImageDisplacementList::SetRandomImageDisplacement() -> void
{
  m_currentImageDisplacementIndex =
      m_goomRand.GetRandInRange(0U, static_cast<uint32_t>(m_imageDisplacements.size()));
}

auto ImageDisplacementList::GetImageFilename(const std::string& imageFilename) const -> std::string
{
  return m_resourcesDirectory + PATH_SEP + IMAGES_DIR + PATH_SEP + IMAGE_DISPLACEMENT_DIR +
         PATH_SEP + imageFilename;
}

auto ImageDisplacementList::GetParams() const -> Params
{
  return {GetCurrentImageDisplacement().GetAmplitude(),
          GetCurrentImageDisplacement().GetXColorCutoff(),
          GetCurrentImageDisplacement().GetYColorCutoff(),
          GetCurrentImageDisplacement().GetZoomFactor()};
}

auto ImageDisplacementList::SetParams(const Params& params) -> void
{
  GetCurrentImageDisplacement().SetAmplitude(params.amplitude);
  GetCurrentImageDisplacement().SetXyColorCutoffs(params.xColorCutoff, params.yColorCutoff);
  GetCurrentImageDisplacement().SetZoomFactor(params.zoomFactor);
}

auto ImageDisplacementList::GetNameValueParams(const std::string& paramGroup) const
    -> NameValuePairs
{
  return {
      GetPair(paramGroup, "filename", IMAGE_FILENAMES[m_currentImageDisplacementIndex]),
      GetPair(paramGroup, "zoom factor", GetCurrentImageDisplacement().GetZoomFactor()),
      GetPair(paramGroup, "amplitude", GetCurrentImageDisplacement().GetAmplitude()),
      GetPair(paramGroup,
              "cutoff",
              Point2dFlt{GetCurrentImageDisplacement().GetXColorCutoff(),
                         GetCurrentImageDisplacement().GetYColorCutoff()}),
  };
}

} // namespace GOOM::FILTER_FX::FILTER_UTILS
