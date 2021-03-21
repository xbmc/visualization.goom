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
static const std::vector<vivid::srgb_t> Broc_14
{
  {   0.17255f,   0.10196f,   0.29804f },
  {   0.16078f,   0.21961f,   0.41569f },
  {   0.17647f,   0.34118f,   0.53333f },
  {   0.31373f,   0.47451f,   0.63922f },
  {   0.48235f,   0.60784f,   0.72941f },
  {   0.66667f,   0.74510f,   0.82353f },
  {   0.85098f,   0.88627f,   0.91765f },
  {   0.92549f,   0.92941f,   0.86667f },
  {   0.84314f,   0.84314f,   0.68235f },
  {   0.72157f,   0.72157f,   0.49412f },
  {   0.56863f,   0.56863f,   0.34902f },
  {   0.41569f,   0.41569f,   0.21961f },
  {   0.27843f,   0.27843f,   0.10980f },
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
