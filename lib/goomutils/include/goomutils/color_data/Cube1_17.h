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
static const std::vector<vivid::srgb_t> Cube1_17
{
  {   0.47059f,   0.00000f,   0.52157f },
  {   0.51373f,   0.04706f,   0.69804f },
  {   0.49804f,   0.23137f,   0.86275f },
  {   0.44314f,   0.36471f,   0.98824f },
  {   0.38431f,   0.49020f,   0.96471f },
  {   0.31765f,   0.59216f,   0.88627f },
  {   0.23529f,   0.68235f,   0.77255f },
  {   0.24314f,   0.75686f,   0.63922f },
  {   0.28627f,   0.81569f,   0.49412f },
  {   0.32941f,   0.86275f,   0.35294f },
  {   0.40784f,   0.90588f,   0.29020f },
  {   0.56863f,   0.92157f,   0.32157f },
  {   0.71373f,   0.92549f,   0.34118f },
  {   0.81569f,   0.92157f,   0.35294f },
  {   0.87843f,   0.84314f,   0.36078f },
  {   0.95294f,   0.73725f,   0.36863f },
  {   0.97647f,   0.58824f,   0.35686f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
