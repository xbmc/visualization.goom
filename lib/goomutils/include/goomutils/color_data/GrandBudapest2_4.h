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
static const std::vector<vivid::srgb_t> GrandBudapest2_4
{
  {   1.00000f,   0.65098f,   0.55686f },
  {   0.98431f,   0.80000f,   0.71765f },
  {   0.54902f,   0.06667f,   0.03137f },
  {   0.16078f,   0.04314f,   0.01569f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
