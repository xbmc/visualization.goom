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
static const std::vector<vivid::srgb_t> PiYG_4
{
  {   0.81569f,   0.10980f,   0.54510f },
  {   0.94510f,   0.71373f,   0.85490f },
  {   0.72157f,   0.88235f,   0.52549f },
  {   0.30196f,   0.67451f,   0.14902f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
