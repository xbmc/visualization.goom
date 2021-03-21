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
static const std::vector<vivid::srgb_t> Dense_15
{
  {   0.90196f,   0.94510f,   0.94510f },
  {   0.78039f,   0.88627f,   0.90588f },
  {   0.67059f,   0.82745f,   0.89020f },
  {   0.56471f,   0.76078f,   0.88627f },
  {   0.49412f,   0.69020f,   0.89412f },
  {   0.45490f,   0.61569f,   0.89804f },
  {   0.45490f,   0.53333f,   0.88235f },
  {   0.47059f,   0.44314f,   0.83529f },
  {   0.47451f,   0.36078f,   0.76471f },
  {   0.47059f,   0.28627f,   0.67843f },
  {   0.45098f,   0.21569f,   0.57647f },
  {   0.41569f,   0.15294f,   0.46667f },
  {   0.36471f,   0.10196f,   0.34510f },
  {   0.29412f,   0.07451f,   0.23137f },
  {   0.21176f,   0.05490f,   0.14118f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
