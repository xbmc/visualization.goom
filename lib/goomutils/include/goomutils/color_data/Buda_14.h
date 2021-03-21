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
static const std::vector<vivid::srgb_t> Buda_14
{
  {   0.70196f,   0.00392f,   0.70196f },
  {   0.70196f,   0.12941f,   0.63922f },
  {   0.70588f,   0.21176f,   0.60000f },
  {   0.72941f,   0.29020f,   0.57255f },
  {   0.75294f,   0.35686f,   0.54902f },
  {   0.77647f,   0.42353f,   0.52549f },
  {   0.79608f,   0.49020f,   0.50588f },
  {   0.81176f,   0.55294f,   0.48627f },
  {   0.83137f,   0.61961f,   0.47059f },
  {   0.84706f,   0.69020f,   0.45098f },
  {   0.86667f,   0.75686f,   0.43529f },
  {   0.88235f,   0.83137f,   0.41961f },
  {   0.91765f,   0.90588f,   0.40392f },
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
