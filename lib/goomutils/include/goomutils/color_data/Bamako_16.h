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
static const std::vector<vivid::srgb_t> Bamako_16
{
  {   0.00000f,   0.25098f,   0.29804f },
  {   0.04706f,   0.27451f,   0.27451f },
  {   0.09020f,   0.30196f,   0.25098f },
  {   0.13333f,   0.33333f,   0.22353f },
  {   0.17647f,   0.36078f,   0.19608f },
  {   0.22745f,   0.39608f,   0.16471f },
  {   0.28235f,   0.43137f,   0.13333f },
  {   0.34510f,   0.47059f,   0.09804f },
  {   0.41569f,   0.51373f,   0.05882f },
  {   0.50196f,   0.55294f,   0.01569f },
  {   0.58824f,   0.57255f,   0.02353f },
  {   0.69804f,   0.62745f,   0.11765f },
  {   0.80392f,   0.70980f,   0.23922f },
  {   0.88235f,   0.78039f,   0.36863f },
  {   0.94118f,   0.84314f,   0.48627f },
  {   1.00000f,   0.89804f,   0.60000f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
