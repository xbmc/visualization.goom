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
static const std::vector<vivid::srgb_t> Oleron_8
{
  {   0.10196f,   0.14902f,   0.34902f },
  {   0.32549f,   0.37255f,   0.57255f },
  {   0.58039f,   0.63137f,   0.82745f },
  {   0.80784f,   0.85490f,   0.97647f },
  {   0.26667f,   0.34902f,   0.00000f },
  {   0.58039f,   0.50980f,   0.22745f },
  {   0.89804f,   0.75294f,   0.56471f },
  {   0.99216f,   0.99216f,   0.90196f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
