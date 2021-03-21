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
static const std::vector<vivid::srgb_t> Bamako_15
{
  {   0.00000f,   0.25098f,   0.29804f },
  {   0.05098f,   0.27843f,   0.27451f },
  {   0.09412f,   0.30588f,   0.24706f },
  {   0.14118f,   0.33725f,   0.21569f },
  {   0.19216f,   0.37255f,   0.18824f },
  {   0.24706f,   0.40784f,   0.15294f },
  {   0.30588f,   0.44706f,   0.12157f },
  {   0.38039f,   0.49412f,   0.07843f },
  {   0.46275f,   0.53725f,   0.03137f },
  {   0.55686f,   0.56471f,   0.01176f },
  {   0.66667f,   0.60784f,   0.08627f },
  {   0.78431f,   0.69020f,   0.21176f },
  {   0.87451f,   0.77255f,   0.35294f },
  {   0.93725f,   0.83922f,   0.47843f },
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
