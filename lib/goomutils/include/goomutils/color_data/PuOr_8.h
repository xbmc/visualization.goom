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
static const std::vector<vivid::srgb_t> PuOr_8
{
  {   0.70196f,   0.34510f,   0.02353f },
  {   0.87843f,   0.50980f,   0.07843f },
  {   0.99216f,   0.72157f,   0.38824f },
  {   0.99608f,   0.87843f,   0.71373f },
  {   0.84706f,   0.85490f,   0.92157f },
  {   0.69804f,   0.67059f,   0.82353f },
  {   0.50196f,   0.45098f,   0.67451f },
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
