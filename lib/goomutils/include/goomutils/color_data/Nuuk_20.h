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
static const std::vector<vivid::srgb_t> Nuuk_20
{
  {   0.01961f,   0.34902f,   0.54902f },
  {   0.09804f,   0.36471f,   0.53333f },
  {   0.15686f,   0.38431f,   0.51765f },
  {   0.21176f,   0.40784f,   0.50980f },
  {   0.27451f,   0.43922f,   0.51373f },
  {   0.34118f,   0.47451f,   0.52549f },
  {   0.41569f,   0.51765f,   0.54510f },
  {   0.48235f,   0.55686f,   0.56863f },
  {   0.54510f,   0.59216f,   0.58431f },
  {   0.60392f,   0.63137f,   0.59608f },
  {   0.65098f,   0.66275f,   0.59216f },
  {   0.68627f,   0.69020f,   0.58039f },
  {   0.71373f,   0.71373f,   0.56471f },
  {   0.73333f,   0.73333f,   0.54510f },
  {   0.75686f,   0.75686f,   0.52549f },
  {   0.78431f,   0.78431f,   0.51373f },
  {   0.82745f,   0.82745f,   0.52157f },
  {   0.88235f,   0.88235f,   0.56078f },
  {   0.94510f,   0.94510f,   0.62745f },
  {   0.99608f,   0.99608f,   0.69804f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
