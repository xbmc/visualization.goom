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
static const std::vector<vivid::srgb_t> Hawaii_6
{
  {   0.54902f,   0.00784f,   0.45098f },
  {   0.58431f,   0.25490f,   0.27843f },
  {   0.61176f,   0.45882f,   0.14118f },
  {   0.56078f,   0.71373f,   0.23529f },
  {   0.38431f,   0.86275f,   0.66275f },
  {   0.70196f,   0.94902f,   0.99216f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
