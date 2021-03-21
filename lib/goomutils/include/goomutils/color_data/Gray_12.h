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
static const std::vector<vivid::srgb_t> Gray_12
{
  {   0.00000f,   0.00000f,   0.00000f },
  {   0.06667f,   0.06275f,   0.06275f },
  {   0.15294f,   0.14902f,   0.14902f },
  {   0.23922f,   0.23529f,   0.23529f },
  {   0.31765f,   0.31765f,   0.31373f },
  {   0.40000f,   0.40000f,   0.39608f },
  {   0.48627f,   0.48627f,   0.48235f },
  {   0.57647f,   0.57255f,   0.57255f },
  {   0.67059f,   0.66667f,   0.66275f },
  {   0.77255f,   0.77255f,   0.76863f },
  {   0.88235f,   0.88235f,   0.87451f },
  {   1.00000f,   1.00000f,   0.99216f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
