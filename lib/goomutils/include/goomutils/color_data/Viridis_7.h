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
static const std::vector<vivid::srgb_t> Viridis_7
{
  {   0.26667f,   0.00392f,   0.32941f },
  {   0.26667f,   0.22353f,   0.51373f },
  {   0.19216f,   0.40784f,   0.55686f },
  {   0.12941f,   0.56863f,   0.54902f },
  {   0.20784f,   0.71765f,   0.47451f },
  {   0.55686f,   0.83922f,   0.27059f },
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
