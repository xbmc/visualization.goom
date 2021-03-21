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
static const std::vector<vivid::srgb_t> Blues_4
{
  {   0.93725f,   0.95294f,   1.00000f },
  {   0.74118f,   0.84314f,   0.90588f },
  {   0.41961f,   0.68235f,   0.83922f },
  {   0.12941f,   0.44314f,   0.70980f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
