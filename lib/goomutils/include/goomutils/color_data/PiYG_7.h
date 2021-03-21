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
static const std::vector<vivid::srgb_t> PiYG_7
{
  {   0.77255f,   0.10588f,   0.49020f },
  {   0.91373f,   0.63922f,   0.78824f },
  {   0.99216f,   0.87843f,   0.93725f },
  {   0.96863f,   0.96863f,   0.96863f },
  {   0.90196f,   0.96078f,   0.81569f },
  {   0.63137f,   0.84314f,   0.41569f },
  {   0.30196f,   0.57255f,   0.12941f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
