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
static const std::vector<vivid::srgb_t> Speed_18
{
  {   1.00000f,   0.99216f,   0.80392f },
  {   0.96078f,   0.92157f,   0.67843f },
  {   0.91765f,   0.85490f,   0.55294f },
  {   0.87059f,   0.79608f,   0.42353f },
  {   0.80784f,   0.74118f,   0.29804f },
  {   0.72941f,   0.69804f,   0.18824f },
  {   0.63529f,   0.66275f,   0.09804f },
  {   0.53333f,   0.62745f,   0.03137f },
  {   0.43137f,   0.59216f,   0.02745f },
  {   0.32157f,   0.55294f,   0.07059f },
  {   0.21961f,   0.51373f,   0.11373f },
  {   0.12157f,   0.46667f,   0.14902f },
  {   0.05490f,   0.41569f,   0.16863f },
  {   0.04706f,   0.36078f,   0.17647f },
  {   0.07451f,   0.30588f,   0.16863f },
  {   0.09412f,   0.24706f,   0.14902f },
  {   0.09804f,   0.19216f,   0.11765f },
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
