#pragma once

#include "filter_fx/filter_settings_service.h"

#include <memory>

namespace GOOM
{

namespace UTILS
{
namespace MATH
{
class IGoomRand;
}
class Parallel;
}

namespace FILTER_FX::FILTER_EFFECTS
{

[[nodiscard]] extern auto CreateZoomInCoefficientsEffect(ZoomFilterMode filterMode,
                                                         const UTILS::MATH::IGoomRand& goomRand,
                                                         const std::string& resourcesDirectory)
    -> std::shared_ptr<IZoomInCoefficientsEffect>;

} // namespace FILTER_FX::FILTER_EFFECTS
} // namespace GOOM
