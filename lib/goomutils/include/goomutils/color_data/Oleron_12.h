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
static const std::vector<vivid::srgb_t> Oleron_12
{
  {   0.10196f,   0.14902f,   0.34902f },
  {   0.23922f,   0.29020f,   0.49020f },
  {   0.39216f,   0.43922f,   0.63922f },
  {   0.55686f,   0.60784f,   0.80784f },
  {   0.71765f,   0.76863f,   0.94510f },
  {   0.84314f,   0.89412f,   0.98431f },
  {   0.20784f,   0.32941f,   0.00000f },
  {   0.40392f,   0.40392f,   0.05490f },
  {   0.60784f,   0.52549f,   0.25098f },
  {   0.81961f,   0.67843f,   0.47059f },
  {   0.96078f,   0.84314f,   0.69020f },
  {   0.99216f,   0.99216f,   0.90196f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
