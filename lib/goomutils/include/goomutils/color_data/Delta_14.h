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
static const std::vector<vivid::srgb_t> Delta_14
{
  {   0.06667f,   0.12549f,   0.25098f },
  {   0.14902f,   0.22353f,   0.51765f },
  {   0.10588f,   0.38039f,   0.62353f },
  {   0.17255f,   0.52941f,   0.65490f },
  {   0.32941f,   0.67059f,   0.69020f },
  {   0.62745f,   0.78824f,   0.75686f },
  {   0.87451f,   0.91373f,   0.86275f },
  {   0.94902f,   0.90196f,   0.64706f },
  {   0.81961f,   0.74902f,   0.31765f },
  {   0.58431f,   0.64314f,   0.05882f },
  {   0.30980f,   0.54902f,   0.07451f },
  {   0.06667f,   0.42745f,   0.16471f },
  {   0.08235f,   0.28235f,   0.16078f },
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
