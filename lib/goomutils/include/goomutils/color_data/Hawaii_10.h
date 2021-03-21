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
static const std::vector<vivid::srgb_t> Hawaii_10
{
  {   0.54902f,   0.00784f,   0.45098f },
  {   0.57255f,   0.16471f,   0.34902f },
  {   0.58824f,   0.27843f,   0.25882f },
  {   0.60000f,   0.38824f,   0.18824f },
  {   0.61569f,   0.51373f,   0.11765f },
  {   0.59216f,   0.66275f,   0.16471f },
  {   0.50196f,   0.77255f,   0.37255f },
  {   0.40000f,   0.84706f,   0.61176f },
  {   0.42353f,   0.92157f,   0.85882f },
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
