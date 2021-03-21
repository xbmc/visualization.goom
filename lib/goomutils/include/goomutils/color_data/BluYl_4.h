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
static const std::vector<vivid::srgb_t> BluYl_4
{
  {   0.96863f,   0.99608f,   0.68235f },
  {   0.48627f,   0.79608f,   0.63529f },
  {   0.03137f,   0.56471f,   0.60000f },
  {   0.01569f,   0.32157f,   0.45882f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
