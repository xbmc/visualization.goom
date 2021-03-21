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
static const std::vector<vivid::srgb_t> Berlin_13
{
  {   0.61961f,   0.69020f,   1.00000f },
  {   0.42353f,   0.66275f,   0.90196f },
  {   0.24314f,   0.56471f,   0.73725f },
  {   0.15686f,   0.40784f,   0.52549f },
  {   0.10196f,   0.25882f,   0.33725f },
  {   0.06667f,   0.12941f,   0.16471f },
  {   0.09804f,   0.04706f,   0.03529f },
  {   0.19216f,   0.05882f,   0.00000f },
  {   0.31373f,   0.09412f,   0.01176f },
  {   0.48235f,   0.19608f,   0.10980f },
  {   0.65098f,   0.34902f,   0.28235f },
  {   0.82353f,   0.51373f,   0.47843f },
  {   1.00000f,   0.67843f,   0.67843f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
