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
static const std::vector<vivid::srgb_t> agGrnYl_5
{
  {   0.14118f,   0.33725f,   0.40784f },
  {   0.05098f,   0.56078f,   0.50588f },
  {   0.22353f,   0.67059f,   0.49412f },
  {   0.43137f,   0.77255f,   0.45490f },
  {   0.92941f,   0.93725f,   0.36471f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
