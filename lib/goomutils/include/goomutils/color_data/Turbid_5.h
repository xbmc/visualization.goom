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
static const std::vector<vivid::srgb_t> Turbid_5
{
  {   0.91373f,   0.96471f,   0.67059f },
  {   0.79216f,   0.68235f,   0.34510f },
  {   0.63137f,   0.43922f,   0.23137f },
  {   0.38824f,   0.27451f,   0.20392f },
  {   0.13333f,   0.12157f,   0.10588f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
