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
static const std::vector<vivid::srgb_t> Tempo_17
{
  {   1.00000f,   0.96471f,   0.95686f },
  {   0.91373f,   0.90588f,   0.86667f },
  {   0.82353f,   0.85098f,   0.78039f },
  {   0.72941f,   0.80392f,   0.70196f },
  {   0.63137f,   0.75686f,   0.63137f },
  {   0.52549f,   0.71373f,   0.57647f },
  {   0.41176f,   0.67059f,   0.53725f },
  {   0.28627f,   0.62745f,   0.51373f },
  {   0.16471f,   0.57647f,   0.49804f },
  {   0.08627f,   0.52549f,   0.48627f },
  {   0.06667f,   0.46667f,   0.46667f },
  {   0.09020f,   0.40784f,   0.43922f },
  {   0.10588f,   0.34902f,   0.40784f },
  {   0.10980f,   0.29412f,   0.37255f },
  {   0.10588f,   0.23529f,   0.33725f },
  {   0.09412f,   0.17647f,   0.29804f },
  {   0.08235f,   0.11373f,   0.26667f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
