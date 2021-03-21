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
static const std::vector<vivid::srgb_t> cubehelix1_16
{
  {   0.00000f,   0.00000f,   0.00000f },
  {   0.10588f,   0.05882f,   0.00000f },
  {   0.25490f,   0.09020f,   0.01569f },
  {   0.40784f,   0.10588f,   0.12549f },
  {   0.52157f,   0.12941f,   0.29412f },
  {   0.57647f,   0.17647f,   0.49412f },
  {   0.56471f,   0.25882f,   0.68627f },
  {   0.50588f,   0.37647f,   0.82353f },
  {   0.43529f,   0.51373f,   0.89020f },
  {   0.38824f,   0.65098f,   0.88627f },
  {   0.39608f,   0.77255f,   0.82745f },
  {   0.47059f,   0.85882f,   0.76078f },
  {   0.60000f,   0.91373f,   0.72549f },
  {   0.75686f,   0.94118f,   0.74902f },
  {   0.90196f,   0.96078f,   0.84706f },
  {   1.00000f,   1.00000f,   1.00000f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
