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
static const std::vector<vivid::srgb_t> BlueDarkRed18_8
{
  {   0.14118f,   0.00000f,   0.84706f },
  {   0.15686f,   0.34118f,   1.00000f },
  {   0.45882f,   0.82745f,   1.00000f },
  {   0.73725f,   0.97647f,   1.00000f },
  {   1.00000f,   0.94510f,   0.73725f },
  {   1.00000f,   0.67451f,   0.45882f },
  {   0.96863f,   0.15294f,   0.20784f },
  {   0.64706f,   0.00000f,   0.12941f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
