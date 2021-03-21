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
static const std::vector<vivid::srgb_t> Viridis_18
{
  {   0.26667f,   0.00392f,   0.32941f },
  {   0.28235f,   0.09020f,   0.41176f },
  {   0.27843f,   0.16471f,   0.47843f },
  {   0.26275f,   0.23922f,   0.51765f },
  {   0.23922f,   0.30588f,   0.54118f },
  {   0.20784f,   0.36863f,   0.55294f },
  {   0.18039f,   0.42745f,   0.55686f },
  {   0.16078f,   0.48235f,   0.55686f },
  {   0.13725f,   0.53725f,   0.55686f },
  {   0.12157f,   0.59216f,   0.54510f },
  {   0.12941f,   0.64706f,   0.52157f },
  {   0.18039f,   0.70196f,   0.48627f },
  {   0.27451f,   0.75294f,   0.43529f },
  {   0.39608f,   0.79608f,   0.36863f },
  {   0.53725f,   0.83529f,   0.28235f },
  {   0.69020f,   0.86667f,   0.18431f },
  {   0.84706f,   0.88627f,   0.09804f },
  {   0.99216f,   0.90588f,   0.14510f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
