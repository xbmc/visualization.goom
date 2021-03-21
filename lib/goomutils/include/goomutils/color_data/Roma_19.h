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
static const std::vector<vivid::srgb_t> Roma_19
{
  {   0.49804f,   0.09804f,   0.00000f },
  {   0.56078f,   0.23529f,   0.04706f },
  {   0.61569f,   0.34902f,   0.09412f },
  {   0.67059f,   0.45490f,   0.14118f },
  {   0.72549f,   0.57647f,   0.20000f },
  {   0.78824f,   0.69412f,   0.28627f },
  {   0.85098f,   0.81176f,   0.42745f },
  {   0.88627f,   0.88627f,   0.57647f },
  {   0.87451f,   0.91765f,   0.69804f },
  {   0.79216f,   0.92157f,   0.78824f },
  {   0.66275f,   0.89412f,   0.83529f },
  {   0.50980f,   0.83137f,   0.84706f },
  {   0.38039f,   0.74118f,   0.82745f },
  {   0.30588f,   0.64314f,   0.78824f },
  {   0.25882f,   0.54902f,   0.74902f },
  {   0.22353f,   0.45882f,   0.71373f },
  {   0.18431f,   0.36863f,   0.67059f },
  {   0.14902f,   0.28235f,   0.63529f },
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
