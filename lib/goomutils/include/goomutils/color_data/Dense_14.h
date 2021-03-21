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
static const std::vector<vivid::srgb_t> Dense_14
{
  {   0.90196f,   0.94510f,   0.94510f },
  {   0.76863f,   0.87843f,   0.90196f },
  {   0.65098f,   0.81569f,   0.89020f },
  {   0.54902f,   0.74510f,   0.88627f },
  {   0.47843f,   0.67059f,   0.89412f },
  {   0.45098f,   0.58431f,   0.89412f },
  {   0.46275f,   0.49020f,   0.86275f },
  {   0.47451f,   0.40000f,   0.80392f },
  {   0.47451f,   0.31373f,   0.71373f },
  {   0.45490f,   0.23137f,   0.60784f },
  {   0.42353f,   0.16471f,   0.49412f },
  {   0.37255f,   0.10588f,   0.36471f },
  {   0.30588f,   0.07451f,   0.24314f },
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
