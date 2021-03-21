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
static const std::vector<vivid::srgb_t> Matter_13
{
  {   0.99608f,   0.92941f,   0.69020f },
  {   0.98431f,   0.81569f,   0.58039f },
  {   0.96863f,   0.70196f,   0.48627f },
  {   0.94902f,   0.58431f,   0.40392f },
  {   0.92157f,   0.47059f,   0.34510f },
  {   0.87843f,   0.36471f,   0.32549f },
  {   0.80784f,   0.26275f,   0.33725f },
  {   0.72157f,   0.19216f,   0.36471f },
  {   0.62353f,   0.14118f,   0.38431f },
  {   0.51765f,   0.10980f,   0.38824f },
  {   0.40392f,   0.09804f,   0.36471f },
  {   0.29020f,   0.08235f,   0.30980f },
  {   0.18431f,   0.05882f,   0.24314f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
