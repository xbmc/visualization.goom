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
static const std::vector<vivid::srgb_t> Nuuk_9
{
  {   0.01961f,   0.34902f,   0.54902f },
  {   0.17647f,   0.39216f,   0.51373f },
  {   0.32549f,   0.46667f,   0.52157f },
  {   0.49020f,   0.56078f,   0.56863f },
  {   0.63137f,   0.65098f,   0.59608f },
  {   0.70980f,   0.70980f,   0.56863f },
  {   0.76471f,   0.76078f,   0.52157f },
  {   0.86275f,   0.85882f,   0.54118f },
  {   0.99608f,   0.99608f,   0.69804f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
