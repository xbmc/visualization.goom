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
static const std::vector<vivid::srgb_t> CubeYF_18
{
  {   0.48235f,   0.00784f,   0.56471f },
  {   0.52549f,   0.06667f,   0.70980f },
  {   0.51765f,   0.20000f,   0.83137f },
  {   0.47451f,   0.30588f,   0.94118f },
  {   0.42745f,   0.39216f,   0.99216f },
  {   0.38824f,   0.47843f,   0.97647f },
  {   0.33725f,   0.56078f,   0.90980f },
  {   0.28627f,   0.63137f,   0.83922f },
  {   0.23137f,   0.70196f,   0.74510f },
  {   0.23922f,   0.75294f,   0.65098f },
  {   0.27451f,   0.79608f,   0.54118f },
  {   0.30588f,   0.83529f,   0.43529f },
  {   0.34902f,   0.87451f,   0.32941f },
  {   0.40392f,   0.90196f,   0.28627f },
  {   0.52549f,   0.92157f,   0.31373f },
  {   0.64706f,   0.92549f,   0.33333f },
  {   0.73333f,   0.92549f,   0.34510f },
  {   0.81961f,   0.92157f,   0.35686f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
