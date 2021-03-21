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
static const std::vector<vivid::srgb_t> classic_16
{
  {   0.00000f,   0.00000f,   0.00000f },
  {   0.08627f,   0.03922f,   0.13333f },
  {   0.09412f,   0.12549f,   0.26667f },
  {   0.06275f,   0.24314f,   0.32549f },
  {   0.05490f,   0.36863f,   0.29020f },
  {   0.13725f,   0.45490f,   0.20000f },
  {   0.31373f,   0.49020f,   0.13725f },
  {   0.54118f,   0.47843f,   0.17647f },
  {   0.74510f,   0.45882f,   0.33333f },
  {   0.85490f,   0.47451f,   0.56863f },
  {   0.85882f,   0.54118f,   0.79608f },
  {   0.80000f,   0.65490f,   0.94118f },
  {   0.74902f,   0.78824f,   0.98431f },
  {   0.76471f,   0.89804f,   0.95686f },
  {   0.86275f,   0.96471f,   0.93725f },
  {   1.00000f,   1.00000f,   1.00000f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
