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
static const std::vector<vivid::srgb_t> Broc_17
{
  {   0.17255f,   0.10196f,   0.29804f },
  {   0.16471f,   0.19216f,   0.39216f },
  {   0.16078f,   0.29412f,   0.49020f },
  {   0.22353f,   0.40000f,   0.58431f },
  {   0.35686f,   0.50980f,   0.66275f },
  {   0.49804f,   0.61961f,   0.73725f },
  {   0.64706f,   0.73333f,   0.81569f },
  {   0.79608f,   0.84706f,   0.89412f },
  {   0.92157f,   0.93333f,   0.92549f },
  {   0.90588f,   0.90588f,   0.81176f },
  {   0.83137f,   0.83137f,   0.66667f },
  {   0.73725f,   0.73725f,   0.51373f },
  {   0.60784f,   0.60784f,   0.38431f },
  {   0.48235f,   0.48235f,   0.27843f },
  {   0.36471f,   0.36471f,   0.17647f },
  {   0.25098f,   0.25098f,   0.08627f },
  {   0.14902f,   0.14902f,   0.00000f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
