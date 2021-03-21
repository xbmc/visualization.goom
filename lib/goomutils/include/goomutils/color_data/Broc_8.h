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
static const std::vector<vivid::srgb_t> Broc_8
{
  {   0.17255f,   0.10196f,   0.29804f },
  {   0.16471f,   0.31765f,   0.51373f },
  {   0.43529f,   0.57255f,   0.70196f },
  {   0.76863f,   0.82353f,   0.87843f },
  {   0.89412f,   0.89412f,   0.78431f },
  {   0.68235f,   0.68235f,   0.45098f },
  {   0.39216f,   0.39216f,   0.20392f },
  {   0.14902f,   0.14902f,   0.00000f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
