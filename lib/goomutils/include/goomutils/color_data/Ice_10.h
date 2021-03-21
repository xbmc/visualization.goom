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
static const std::vector<vivid::srgb_t> Ice_10
{
  {   0.01569f,   0.02353f,   0.07451f },
  {   0.11765f,   0.11373f,   0.23137f },
  {   0.20392f,   0.20000f,   0.41176f },
  {   0.24706f,   0.29412f,   0.58824f },
  {   0.24314f,   0.41569f,   0.69020f },
  {   0.29020f,   0.54118f,   0.74118f },
  {   0.38039f,   0.65882f,   0.78039f },
  {   0.51373f,   0.77255f,   0.82745f },
  {   0.71765f,   0.88235f,   0.89412f },
  {   0.91765f,   0.99216f,   0.99216f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
