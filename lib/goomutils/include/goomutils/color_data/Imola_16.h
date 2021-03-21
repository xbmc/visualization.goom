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
static const std::vector<vivid::srgb_t> Imola_16
{
  {   0.10196f,   0.20000f,   0.70196f },
  {   0.12549f,   0.24706f,   0.67843f },
  {   0.14902f,   0.29020f,   0.65490f },
  {   0.17255f,   0.33333f,   0.63137f },
  {   0.19608f,   0.37647f,   0.60784f },
  {   0.22353f,   0.41961f,   0.58039f },
  {   0.25882f,   0.45490f,   0.54510f },
  {   0.30196f,   0.49804f,   0.50980f },
  {   0.35686f,   0.55294f,   0.49020f },
  {   0.41569f,   0.61569f,   0.47059f },
  {   0.48235f,   0.68235f,   0.45490f },
  {   0.54902f,   0.74902f,   0.43922f },
  {   0.62353f,   0.82353f,   0.41961f },
  {   0.72549f,   0.89412f,   0.40784f },
  {   0.85882f,   0.95294f,   0.40000f },
  {   1.00000f,   1.00000f,   0.40000f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
