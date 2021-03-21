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
static const std::vector<vivid::srgb_t> Inferno_10
{
  {   0.00000f,   0.00000f,   0.01569f },
  {   0.10588f,   0.04706f,   0.25490f },
  {   0.29804f,   0.04706f,   0.41961f },
  {   0.47059f,   0.10980f,   0.42745f },
  {   0.64706f,   0.17255f,   0.37647f },
  {   0.81176f,   0.26667f,   0.27451f },
  {   0.92941f,   0.41176f,   0.14510f },
  {   0.98431f,   0.60000f,   0.02353f },
  {   0.96863f,   0.81961f,   0.23922f },
  {   0.98824f,   1.00000f,   0.64314f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
