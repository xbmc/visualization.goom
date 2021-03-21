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
static const std::vector<vivid::srgb_t> Deep_10
{
  {   0.99216f,   0.99608f,   0.80000f },
  {   0.76863f,   0.91373f,   0.68627f },
  {   0.52157f,   0.82745f,   0.63922f },
  {   0.36471f,   0.72941f,   0.64314f },
  {   0.30196f,   0.61569f,   0.63137f },
  {   0.26667f,   0.50196f,   0.60784f },
  {   0.24314f,   0.39216f,   0.58431f },
  {   0.25490f,   0.27451f,   0.51765f },
  {   0.22353f,   0.18431f,   0.33333f },
  {   0.15686f,   0.10196f,   0.17255f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
