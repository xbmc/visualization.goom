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
static const std::vector<vivid::srgb_t> Delta_10
{
  {   0.06667f,   0.12549f,   0.25098f },
  {   0.12157f,   0.29020f,   0.60784f },
  {   0.16471f,   0.51373f,   0.65098f },
  {   0.42353f,   0.70980f,   0.70196f },
  {   0.81961f,   0.88235f,   0.83922f },
  {   0.92549f,   0.86275f,   0.56863f },
  {   0.66667f,   0.67451f,   0.12549f },
  {   0.28235f,   0.53725f,   0.08627f },
  {   0.05098f,   0.34902f,   0.17647f },
  {   0.09020f,   0.13725f,   0.07451f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
