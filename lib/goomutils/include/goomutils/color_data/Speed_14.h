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
static const std::vector<vivid::srgb_t> Speed_14
{
  {   1.00000f,   0.99216f,   0.80392f },
  {   0.94510f,   0.89804f,   0.63529f },
  {   0.89020f,   0.81569f,   0.47451f },
  {   0.81569f,   0.74510f,   0.30980f },
  {   0.70980f,   0.69020f,   0.16863f },
  {   0.58431f,   0.64314f,   0.05882f },
  {   0.44314f,   0.59608f,   0.02353f },
  {   0.30980f,   0.54902f,   0.07451f },
  {   0.17255f,   0.49020f,   0.12941f },
  {   0.06275f,   0.42353f,   0.16471f },
  {   0.04706f,   0.35686f,   0.17647f },
  {   0.08235f,   0.28235f,   0.16078f },
  {   0.09804f,   0.21176f,   0.12941f },
  {   0.09020f,   0.13725f,   0.07451f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
