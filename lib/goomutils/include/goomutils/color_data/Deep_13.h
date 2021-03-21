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
static const std::vector<vivid::srgb_t> Deep_13
{
  {   0.99216f,   0.99608f,   0.80000f },
  {   0.82353f,   0.93333f,   0.70980f },
  {   0.64706f,   0.87451f,   0.65490f },
  {   0.47059f,   0.80784f,   0.63922f },
  {   0.36471f,   0.72941f,   0.64314f },
  {   0.31373f,   0.64314f,   0.63529f },
  {   0.28235f,   0.55686f,   0.61961f },
  {   0.25882f,   0.47451f,   0.60000f },
  {   0.24314f,   0.39216f,   0.58431f },
  {   0.25098f,   0.30196f,   0.54902f },
  {   0.25098f,   0.22745f,   0.43137f },
  {   0.20784f,   0.16471f,   0.29020f },
  {   0.15686f,   0.10196f,   0.17255f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
