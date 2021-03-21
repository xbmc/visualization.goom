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
static const std::vector<vivid::srgb_t> Cube1_18
{
  {   0.47059f,   0.00000f,   0.52157f },
  {   0.51373f,   0.04314f,   0.69020f },
  {   0.50196f,   0.20392f,   0.84314f },
  {   0.45490f,   0.34118f,   0.96863f },
  {   0.40000f,   0.45882f,   0.97647f },
  {   0.34118f,   0.56078f,   0.91765f },
  {   0.27059f,   0.64706f,   0.81569f },
  {   0.22353f,   0.72549f,   0.69804f },
  {   0.26667f,   0.78824f,   0.56863f },
  {   0.30588f,   0.83529f,   0.43529f },
  {   0.34902f,   0.88235f,   0.29412f },
  {   0.47059f,   0.91765f,   0.30588f },
  {   0.61569f,   0.92549f,   0.32941f },
  {   0.74118f,   0.92549f,   0.34510f },
  {   0.82745f,   0.91373f,   0.35686f },
  {   0.89020f,   0.83529f,   0.36471f },
  {   0.95686f,   0.72941f,   0.36863f },
  {   0.97647f,   0.58824f,   0.35686f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
