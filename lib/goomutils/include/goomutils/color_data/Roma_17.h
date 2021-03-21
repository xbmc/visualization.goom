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
static const std::vector<vivid::srgb_t> Roma_17
{
  {   0.49804f,   0.09804f,   0.00000f },
  {   0.56863f,   0.25098f,   0.05490f },
  {   0.63137f,   0.38039f,   0.10980f },
  {   0.69020f,   0.50196f,   0.16078f },
  {   0.75686f,   0.63529f,   0.23529f },
  {   0.83137f,   0.77647f,   0.37255f },
  {   0.88235f,   0.87451f,   0.54510f },
  {   0.87843f,   0.91765f,   0.69020f },
  {   0.79216f,   0.92157f,   0.78824f },
  {   0.65098f,   0.89020f,   0.83529f },
  {   0.47843f,   0.81569f,   0.84314f },
  {   0.34902f,   0.70588f,   0.81569f },
  {   0.28235f,   0.59608f,   0.77255f },
  {   0.23529f,   0.49020f,   0.72549f },
  {   0.19608f,   0.39216f,   0.68235f },
  {   0.15294f,   0.29412f,   0.63922f },
  {   0.10196f,   0.20000f,   0.60000f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
