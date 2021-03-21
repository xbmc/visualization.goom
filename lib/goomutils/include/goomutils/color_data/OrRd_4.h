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
static const std::vector<vivid::srgb_t> OrRd_4
{
  {   0.99608f,   0.94118f,   0.85098f },
  {   0.99216f,   0.80000f,   0.54118f },
  {   0.98824f,   0.55294f,   0.34902f },
  {   0.84314f,   0.18824f,   0.12157f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
