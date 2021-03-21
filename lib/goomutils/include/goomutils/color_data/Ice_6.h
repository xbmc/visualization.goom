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
static const std::vector<vivid::srgb_t> Ice_6
{
  {   0.01569f,   0.02353f,   0.07451f },
  {   0.18824f,   0.18431f,   0.37255f },
  {   0.24314f,   0.36863f,   0.66275f },
  {   0.32157f,   0.58824f,   0.75686f },
  {   0.54902f,   0.79608f,   0.83922f },
  {   0.91765f,   0.99216f,   0.99216f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
