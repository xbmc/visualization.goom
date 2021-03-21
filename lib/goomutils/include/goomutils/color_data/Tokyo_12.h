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
static const std::vector<vivid::srgb_t> Tokyo_12
{
  {   0.10196f,   0.05490f,   0.20392f },
  {   0.23922f,   0.10980f,   0.27843f },
  {   0.37647f,   0.19216f,   0.36471f },
  {   0.48235f,   0.30588f,   0.43922f },
  {   0.53333f,   0.40000f,   0.48235f },
  {   0.55686f,   0.48627f,   0.51373f },
  {   0.56863f,   0.56863f,   0.53725f },
  {   0.58431f,   0.65098f,   0.56078f },
  {   0.61569f,   0.74510f,   0.58824f },
  {   0.71373f,   0.86667f,   0.65490f },
  {   0.87059f,   0.96471f,   0.76078f },
  {   0.99608f,   0.99608f,   0.84706f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
