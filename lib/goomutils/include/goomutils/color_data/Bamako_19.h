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
static const std::vector<vivid::srgb_t> Bamako_19
{
  {   0.00000f,   0.25098f,   0.29804f },
  {   0.03922f,   0.27059f,   0.27843f },
  {   0.07451f,   0.29412f,   0.25882f },
  {   0.10980f,   0.31765f,   0.23922f },
  {   0.14902f,   0.34118f,   0.21569f },
  {   0.18824f,   0.36863f,   0.19216f },
  {   0.22745f,   0.39608f,   0.16471f },
  {   0.27451f,   0.42353f,   0.14118f },
  {   0.32157f,   0.45490f,   0.10980f },
  {   0.38039f,   0.49412f,   0.07843f },
  {   0.44314f,   0.52941f,   0.04314f },
  {   0.51373f,   0.55686f,   0.01176f },
  {   0.58824f,   0.57255f,   0.02353f },
  {   0.67843f,   0.61569f,   0.09804f },
  {   0.77255f,   0.68235f,   0.19608f },
  {   0.84706f,   0.74510f,   0.30196f },
  {   0.90588f,   0.80392f,   0.40784f },
  {   0.95294f,   0.85098f,   0.50588f },
  {   1.00000f,   0.89804f,   0.60000f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
