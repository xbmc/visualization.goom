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
static const std::vector<vivid::srgb_t> Tempo_12
{
  {   1.00000f,   0.96471f,   0.95686f },
  {   0.87451f,   0.88235f,   0.82745f },
  {   0.74118f,   0.80784f,   0.70980f },
  {   0.59216f,   0.74118f,   0.61176f },
  {   0.43529f,   0.67843f,   0.54510f },
  {   0.25490f,   0.61569f,   0.50980f },
  {   0.10196f,   0.54118f,   0.49020f },
  {   0.07059f,   0.45882f,   0.46275f },
  {   0.10196f,   0.37255f,   0.41961f },
  {   0.10980f,   0.28627f,   0.36863f },
  {   0.10196f,   0.20392f,   0.31373f },
  {   0.08235f,   0.11373f,   0.26667f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
