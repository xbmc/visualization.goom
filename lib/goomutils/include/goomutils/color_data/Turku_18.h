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
static const std::vector<vivid::srgb_t> Turku_18
{
  {   0.00000f,   0.00000f,   0.00000f },
  {   0.09020f,   0.09020f,   0.08235f },
  {   0.14902f,   0.14902f,   0.13333f },
  {   0.21176f,   0.21176f,   0.17647f },
  {   0.27059f,   0.27059f,   0.21569f },
  {   0.33333f,   0.32941f,   0.24706f },
  {   0.39216f,   0.39216f,   0.27843f },
  {   0.45882f,   0.45098f,   0.30588f },
  {   0.52941f,   0.51373f,   0.33725f },
  {   0.61569f,   0.57647f,   0.37647f },
  {   0.70980f,   0.62353f,   0.42353f },
  {   0.78824f,   0.64706f,   0.47059f },
  {   0.85490f,   0.65490f,   0.51765f },
  {   0.90980f,   0.67451f,   0.58039f },
  {   0.95686f,   0.71373f,   0.66667f },
  {   0.98431f,   0.77255f,   0.75294f },
  {   0.99608f,   0.83922f,   0.83137f },
  {   1.00000f,   0.90196f,   0.90196f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
