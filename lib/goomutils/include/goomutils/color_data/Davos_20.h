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
static const std::vector<vivid::srgb_t> Davos_20
{
  {   0.00000f,   0.01961f,   0.29020f },
  {   0.02353f,   0.09412f,   0.36471f },
  {   0.06667f,   0.16863f,   0.43922f },
  {   0.10196f,   0.23529f,   0.50196f },
  {   0.14902f,   0.30588f,   0.56078f },
  {   0.19608f,   0.36863f,   0.59608f },
  {   0.24706f,   0.42353f,   0.61569f },
  {   0.29804f,   0.46667f,   0.61569f },
  {   0.34510f,   0.50588f,   0.60392f },
  {   0.39608f,   0.54118f,   0.58431f },
  {   0.44706f,   0.56863f,   0.56471f },
  {   0.49804f,   0.60392f,   0.54510f },
  {   0.55294f,   0.64314f,   0.53333f },
  {   0.61961f,   0.69412f,   0.53333f },
  {   0.71373f,   0.76471f,   0.56863f },
  {   0.81176f,   0.83922f,   0.63529f },
  {   0.90196f,   0.91373f,   0.73725f },
  {   0.95294f,   0.95686f,   0.83137f },
  {   0.98431f,   0.98431f,   0.92157f },
  {   0.99608f,   0.99608f,   0.99608f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
