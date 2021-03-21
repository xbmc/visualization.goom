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
static const std::vector<vivid::srgb_t> Viridis_12
{
  {   0.26667f,   0.00392f,   0.32941f },
  {   0.28235f,   0.12941f,   0.45098f },
  {   0.26275f,   0.24314f,   0.52157f },
  {   0.21961f,   0.34902f,   0.54902f },
  {   0.17647f,   0.43922f,   0.55686f },
  {   0.14510f,   0.52157f,   0.55686f },
  {   0.11765f,   0.60784f,   0.54118f },
  {   0.16471f,   0.69020f,   0.49804f },
  {   0.31373f,   0.76863f,   0.41569f },
  {   0.52549f,   0.83529f,   0.28627f },
  {   0.76078f,   0.87451f,   0.13725f },
  {   0.99216f,   0.90588f,   0.14510f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
