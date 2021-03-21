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
static const std::vector<vivid::srgb_t> Hawaii_17
{
  {   0.54902f,   0.00784f,   0.45098f },
  {   0.56471f,   0.11373f,   0.38824f },
  {   0.57255f,   0.18039f,   0.33333f },
  {   0.58431f,   0.24314f,   0.28627f },
  {   0.59216f,   0.30588f,   0.24314f },
  {   0.60000f,   0.36863f,   0.20000f },
  {   0.60784f,   0.43529f,   0.15686f },
  {   0.61569f,   0.50588f,   0.12157f },
  {   0.61176f,   0.58824f,   0.10980f },
  {   0.58824f,   0.66667f,   0.16863f },
  {   0.54118f,   0.73725f,   0.28235f },
  {   0.48235f,   0.78824f,   0.41176f },
  {   0.42353f,   0.83137f,   0.54902f },
  {   0.37647f,   0.87059f,   0.69020f },
  {   0.40000f,   0.90980f,   0.82745f },
  {   0.52941f,   0.93725f,   0.93333f },
  {   0.70196f,   0.94902f,   0.99216f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
