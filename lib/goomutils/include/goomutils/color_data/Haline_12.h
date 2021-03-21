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
static const std::vector<vivid::srgb_t> Haline_12
{
  {   0.16471f,   0.09412f,   0.42353f },
  {   0.16863f,   0.14118f,   0.62745f },
  {   0.06275f,   0.28235f,   0.60000f },
  {   0.07843f,   0.38039f,   0.55686f },
  {   0.14902f,   0.45882f,   0.54118f },
  {   0.20784f,   0.53725f,   0.53333f },
  {   0.25882f,   0.61569f,   0.52157f },
  {   0.31765f,   0.69804f,   0.49020f },
  {   0.43137f,   0.77647f,   0.42745f },
  {   0.62745f,   0.83922f,   0.36078f },
  {   0.83137f,   0.88235f,   0.43922f },
  {   0.99216f,   0.93725f,   0.60392f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
