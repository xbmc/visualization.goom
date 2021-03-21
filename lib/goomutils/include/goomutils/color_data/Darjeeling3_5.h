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
static const std::vector<vivid::srgb_t> Darjeeling3_5
{
  {   0.65882f,   0.67059f,   0.31373f },
  {   1.00000f,   0.90980f,   0.23922f },
  {   0.66275f,   0.82745f,   0.82353f },
  {   0.14118f,   0.27843f,   0.49020f },
  {   0.35294f,   0.56863f,   0.48627f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
