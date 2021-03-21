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
static const std::vector<vivid::srgb_t> Ice_12
{
  {   0.01569f,   0.02353f,   0.07451f },
  {   0.09804f,   0.09804f,   0.20392f },
  {   0.17255f,   0.16863f,   0.34118f },
  {   0.23137f,   0.24314f,   0.49804f },
  {   0.24706f,   0.32941f,   0.62745f },
  {   0.24706f,   0.43137f,   0.69804f },
  {   0.28235f,   0.52941f,   0.73725f },
  {   0.35294f,   0.62353f,   0.76863f },
  {   0.44706f,   0.72157f,   0.80784f },
  {   0.58431f,   0.81569f,   0.84706f },
  {   0.75294f,   0.90196f,   0.90980f },
  {   0.91765f,   0.99216f,   0.99216f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
