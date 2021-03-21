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
static const std::vector<vivid::srgb_t> LaJolla_12
{
  {   1.00000f,   1.00000f,   0.80000f },
  {   0.98824f,   0.94118f,   0.63922f },
  {   0.96863f,   0.85490f,   0.47451f },
  {   0.94118f,   0.73333f,   0.35686f },
  {   0.91765f,   0.61961f,   0.32549f },
  {   0.89020f,   0.51373f,   0.31765f },
  {   0.83529f,   0.40000f,   0.30196f },
  {   0.70196f,   0.30196f,   0.27451f },
  {   0.54118f,   0.24706f,   0.22353f },
  {   0.37647f,   0.19608f,   0.14902f },
  {   0.22745f,   0.14902f,   0.08235f },
  {   0.10196f,   0.10196f,   0.00392f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
