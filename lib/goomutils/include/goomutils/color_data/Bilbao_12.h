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
static const std::vector<vivid::srgb_t> Bilbao_12
{
  {   1.00000f,   1.00000f,   1.00000f },
  {   0.88627f,   0.88235f,   0.87843f },
  {   0.79608f,   0.78431f,   0.74902f },
  {   0.74902f,   0.72157f,   0.61961f },
  {   0.71373f,   0.65882f,   0.50196f },
  {   0.67843f,   0.56863f,   0.41961f },
  {   0.65490f,   0.49020f,   0.38039f },
  {   0.63137f,   0.40784f,   0.34510f },
  {   0.59216f,   0.32157f,   0.29804f },
  {   0.50980f,   0.21569f,   0.21176f },
  {   0.40784f,   0.11373f,   0.11373f },
  {   0.30196f,   0.00000f,   0.00392f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
