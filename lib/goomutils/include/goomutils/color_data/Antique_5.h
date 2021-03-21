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
static const std::vector<vivid::srgb_t> Antique_5
{
  {   0.52157f,   0.36078f,   0.45882f },
  {   0.85098f,   0.68627f,   0.41961f },
  {   0.68627f,   0.39216f,   0.34510f },
  {   0.45098f,   0.43529f,   0.29804f },
  {   0.32157f,   0.41569f,   0.51373f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
