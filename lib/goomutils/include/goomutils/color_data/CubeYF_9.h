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
static const std::vector<vivid::srgb_t> CubeYF_9
{
  {   0.48235f,   0.00784f,   0.56471f },
  {   0.51373f,   0.21569f,   0.84706f },
  {   0.41569f,   0.41569f,   0.99608f },
  {   0.31765f,   0.59216f,   0.87843f },
  {   0.22353f,   0.72941f,   0.69412f },
  {   0.29412f,   0.82353f,   0.47843f },
  {   0.37647f,   0.89804f,   0.27843f },
  {   0.63922f,   0.92549f,   0.33333f },
  {   0.81961f,   0.92157f,   0.35686f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
