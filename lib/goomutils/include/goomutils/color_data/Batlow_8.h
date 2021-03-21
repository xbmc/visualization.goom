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
static const std::vector<vivid::srgb_t> Batlow_8
{
  {   0.00392f,   0.09804f,   0.34902f },
  {   0.06667f,   0.24706f,   0.37647f },
  {   0.18039f,   0.39216f,   0.36078f },
  {   0.38431f,   0.47451f,   0.25490f },
  {   0.63922f,   0.54118f,   0.18039f },
  {   0.91373f,   0.60000f,   0.36863f },
  {   0.99216f,   0.69412f,   0.67843f },
  {   0.98039f,   0.80000f,   0.98039f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
