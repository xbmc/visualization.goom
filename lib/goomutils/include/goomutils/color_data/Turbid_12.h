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
static const std::vector<vivid::srgb_t> Turbid_12
{
  {   0.91373f,   0.96471f,   0.67059f },
  {   0.86275f,   0.85882f,   0.54118f },
  {   0.82353f,   0.75686f,   0.42353f },
  {   0.78039f,   0.65490f,   0.32157f },
  {   0.73333f,   0.56078f,   0.26275f },
  {   0.67059f,   0.47843f,   0.23529f },
  {   0.59216f,   0.40784f,   0.22745f },
  {   0.50588f,   0.34510f,   0.22353f },
  {   0.41569f,   0.28627f,   0.20784f },
  {   0.31765f,   0.23137f,   0.18431f },
  {   0.22353f,   0.17647f,   0.14902f },
  {   0.13333f,   0.12157f,   0.10588f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
