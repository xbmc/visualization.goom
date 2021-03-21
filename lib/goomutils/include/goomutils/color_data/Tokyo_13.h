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
static const std::vector<vivid::srgb_t> Tokyo_13
{
  {   0.10196f,   0.05490f,   0.20392f },
  {   0.22745f,   0.10196f,   0.27451f },
  {   0.35294f,   0.17647f,   0.34902f },
  {   0.46275f,   0.27451f,   0.42353f },
  {   0.52157f,   0.36863f,   0.47059f },
  {   0.54902f,   0.45098f,   0.50196f },
  {   0.56471f,   0.52941f,   0.52549f },
  {   0.57647f,   0.60392f,   0.54510f },
  {   0.59216f,   0.68235f,   0.56863f },
  {   0.63137f,   0.77255f,   0.60000f },
  {   0.72941f,   0.88235f,   0.66667f },
  {   0.88235f,   0.96863f,   0.76863f },
  {   0.99608f,   0.99608f,   0.84706f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
