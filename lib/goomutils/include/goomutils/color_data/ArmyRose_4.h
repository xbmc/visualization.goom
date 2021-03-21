#pragma once

#include "vivid/types.h"
#include <vector>

#if __cplusplus > 201402L
namespace GOOM::UTILS::COLOR_DATA
{
#else
namespace GOOM
{
namespace UTILS
{
namespace COLOR_DATA
{
#endif

// clang-format off
static const std::vector<vivid::srgb_t> ArmyRose_4
{
  {   0.47451f,   0.50980f,   0.20392f },
  {   0.81569f,   0.82745f,   0.63529f },
  {   0.94118f,   0.77647f,   0.76471f },
  {   0.83137f,   0.40392f,   0.50196f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
