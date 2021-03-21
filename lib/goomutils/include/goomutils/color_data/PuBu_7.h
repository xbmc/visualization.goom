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
static const std::vector<vivid::srgb_t> PuBu_7
{
  {   0.94510f,   0.93333f,   0.96471f },
  {   0.81569f,   0.81961f,   0.90196f },
  {   0.65098f,   0.74118f,   0.85882f },
  {   0.45490f,   0.66275f,   0.81176f },
  {   0.21176f,   0.56471f,   0.75294f },
  {   0.01961f,   0.43922f,   0.69020f },
  {   0.01176f,   0.30588f,   0.48235f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
