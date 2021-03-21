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
static const std::vector<vivid::srgb_t> Tokyo_15
{
  {   0.10196f,   0.05490f,   0.20392f },
  {   0.21176f,   0.09412f,   0.26275f },
  {   0.31765f,   0.15294f,   0.32941f },
  {   0.42353f,   0.23529f,   0.39608f },
  {   0.49412f,   0.31765f,   0.44706f },
  {   0.52941f,   0.39216f,   0.48235f },
  {   0.54902f,   0.46275f,   0.50588f },
  {   0.56471f,   0.52941f,   0.52549f },
  {   0.57255f,   0.59608f,   0.54118f },
  {   0.58824f,   0.65882f,   0.56078f },
  {   0.60784f,   0.73333f,   0.58431f },
  {   0.66275f,   0.81569f,   0.62353f },
  {   0.78039f,   0.91765f,   0.69804f },
  {   0.90196f,   0.97647f,   0.78039f },
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
