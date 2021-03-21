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
static const std::vector<vivid::srgb_t> Buda_20
{
  {   0.70196f,   0.00392f,   0.70196f },
  {   0.70196f,   0.09412f,   0.65882f },
  {   0.70196f,   0.16078f,   0.62353f },
  {   0.70980f,   0.21569f,   0.59608f },
  {   0.72157f,   0.27059f,   0.57647f },
  {   0.73725f,   0.31765f,   0.56078f },
  {   0.75686f,   0.36471f,   0.54510f },
  {   0.76863f,   0.41176f,   0.52941f },
  {   0.78431f,   0.45098f,   0.51765f },
  {   0.80000f,   0.49804f,   0.50196f },
  {   0.81176f,   0.54118f,   0.49020f },
  {   0.82353f,   0.59216f,   0.47843f },
  {   0.83529f,   0.63529f,   0.46667f },
  {   0.84706f,   0.67843f,   0.45490f },
  {   0.85882f,   0.72941f,   0.44314f },
  {   0.87059f,   0.77647f,   0.43137f },
  {   0.88235f,   0.82745f,   0.41961f },
  {   0.89804f,   0.87843f,   0.40784f },
  {   0.94118f,   0.93725f,   0.40000f },
  {   1.00000f,   1.00000f,   0.40000f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
