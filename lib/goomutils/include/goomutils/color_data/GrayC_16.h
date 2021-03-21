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
static const std::vector<vivid::srgb_t> GrayC_16
{
  {   1.00000f,   1.00000f,   1.00000f },
  {   0.92549f,   0.92549f,   0.92549f },
  {   0.85098f,   0.85098f,   0.85098f },
  {   0.77647f,   0.77647f,   0.77647f },
  {   0.70588f,   0.70588f,   0.70588f },
  {   0.63529f,   0.63529f,   0.63529f },
  {   0.56863f,   0.56863f,   0.56863f },
  {   0.49804f,   0.49804f,   0.49804f },
  {   0.43529f,   0.43529f,   0.43529f },
  {   0.36863f,   0.36863f,   0.36863f },
  {   0.30588f,   0.30588f,   0.30588f },
  {   0.24706f,   0.24706f,   0.24706f },
  {   0.18824f,   0.18824f,   0.18824f },
  {   0.13333f,   0.13333f,   0.13333f },
  {   0.08235f,   0.08235f,   0.08235f },
  {   0.00000f,   0.00000f,   0.00000f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
