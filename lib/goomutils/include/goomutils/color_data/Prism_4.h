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
static const std::vector<vivid::srgb_t> Prism_4
{
  {   0.37255f,   0.27451f,   0.56471f },
  {   0.11373f,   0.41176f,   0.58824f },
  {   0.21961f,   0.65098f,   0.64706f },
  {   0.05882f,   0.52157f,   0.32941f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
