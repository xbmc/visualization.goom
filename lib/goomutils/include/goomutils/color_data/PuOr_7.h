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
static const std::vector<vivid::srgb_t> PuOr_7
{
  {   0.70196f,   0.34510f,   0.02353f },
  {   0.94510f,   0.63922f,   0.25098f },
  {   0.99608f,   0.87843f,   0.71373f },
  {   0.96863f,   0.96863f,   0.96863f },
  {   0.84706f,   0.85490f,   0.92157f },
  {   0.60000f,   0.55686f,   0.76471f },
  {   0.32941f,   0.15294f,   0.53333f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
