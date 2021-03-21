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
static const std::vector<vivid::srgb_t> Matter_17
{
  {   0.99608f,   0.92941f,   0.69020f },
  {   0.98431f,   0.84314f,   0.60784f },
  {   0.97647f,   0.75686f,   0.52941f },
  {   0.96471f,   0.67059f,   0.46275f },
  {   0.94902f,   0.58431f,   0.40392f },
  {   0.92941f,   0.49804f,   0.35686f },
  {   0.90196f,   0.41569f,   0.32941f },
  {   0.86275f,   0.33333f,   0.32549f },
  {   0.80784f,   0.26275f,   0.33725f },
  {   0.74902f,   0.21176f,   0.35686f },
  {   0.67451f,   0.16471f,   0.37647f },
  {   0.60000f,   0.13333f,   0.38824f },
  {   0.51765f,   0.10980f,   0.38824f },
  {   0.43137f,   0.09804f,   0.37255f },
  {   0.34902f,   0.09020f,   0.34118f },
  {   0.26667f,   0.07843f,   0.29412f },
  {   0.18431f,   0.05882f,   0.24314f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
