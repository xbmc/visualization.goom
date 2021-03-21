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
static const std::vector<vivid::srgb_t> Oleron_19
{
  {   0.10196f,   0.14902f,   0.34902f },
  {   0.18431f,   0.23137f,   0.43529f },
  {   0.27059f,   0.32157f,   0.52157f },
  {   0.36471f,   0.41176f,   0.61176f },
  {   0.46667f,   0.51765f,   0.71765f },
  {   0.56471f,   0.61569f,   0.81569f },
  {   0.66667f,   0.71765f,   0.90980f },
  {   0.75294f,   0.80392f,   0.96078f },
  {   0.82745f,   0.87843f,   0.98039f },
  {   0.10196f,   0.29804f,   0.00000f },
  {   0.23529f,   0.33725f,   0.00000f },
  {   0.35294f,   0.37647f,   0.01961f },
  {   0.47843f,   0.44314f,   0.12157f },
  {   0.60000f,   0.51765f,   0.24314f },
  {   0.71765f,   0.60392f,   0.36863f },
  {   0.84314f,   0.70196f,   0.49804f },
  {   0.94510f,   0.80784f,   0.64314f },
  {   0.97255f,   0.90196f,   0.77255f },
  {   0.99216f,   0.99216f,   0.90196f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
