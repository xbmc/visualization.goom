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
static const std::vector<vivid::srgb_t> Hawaii_16
{
  {   0.54902f,   0.00784f,   0.45098f },
  {   0.56471f,   0.11765f,   0.38824f },
  {   0.57647f,   0.18824f,   0.32941f },
  {   0.58431f,   0.25490f,   0.27843f },
  {   0.59216f,   0.32157f,   0.23137f },
  {   0.60000f,   0.38824f,   0.18824f },
  {   0.61176f,   0.45882f,   0.14118f },
  {   0.61569f,   0.54118f,   0.10980f },
  {   0.60392f,   0.63137f,   0.13333f },
  {   0.56078f,   0.71373f,   0.23529f },
  {   0.50196f,   0.77255f,   0.37255f },
  {   0.43922f,   0.81961f,   0.51373f },
  {   0.38431f,   0.86275f,   0.66275f },
  {   0.38824f,   0.90588f,   0.81176f },
  {   0.51765f,   0.93725f,   0.92549f },
  {   0.70196f,   0.94902f,   0.99216f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
