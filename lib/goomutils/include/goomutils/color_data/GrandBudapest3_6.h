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
static const std::vector<vivid::srgb_t> GrandBudapest3_6
{
  {   1.00000f,   0.86275f,   0.71373f },
  {   0.14510f,   0.21961f,   0.27059f },
  {   0.90588f,   0.67843f,   0.61569f },
  {   0.40000f,   0.45882f,   0.43137f },
  {   0.54510f,   0.24706f,   0.19216f },
  {   0.58824f,   0.42745f,   0.20784f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
