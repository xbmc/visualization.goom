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
static const std::vector<vivid::srgb_t> Dense_16
{
  {   0.90196f,   0.94510f,   0.94510f },
  {   0.78824f,   0.89020f,   0.90980f },
  {   0.68235f,   0.83137f,   0.89020f },
  {   0.58824f,   0.77255f,   0.88627f },
  {   0.50980f,   0.70980f,   0.89020f },
  {   0.46275f,   0.64314f,   0.89804f },
  {   0.45098f,   0.56471f,   0.89020f },
  {   0.46275f,   0.48627f,   0.86275f },
  {   0.47451f,   0.40784f,   0.80784f },
  {   0.47451f,   0.32941f,   0.73333f },
  {   0.46275f,   0.25882f,   0.64706f },
  {   0.44314f,   0.19608f,   0.54902f },
  {   0.40784f,   0.14118f,   0.44314f },
  {   0.35686f,   0.09804f,   0.32941f },
  {   0.29020f,   0.07451f,   0.22745f },
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
