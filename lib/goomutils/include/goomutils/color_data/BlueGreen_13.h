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
static const std::vector<vivid::srgb_t> BlueGreen_13
{
  {   0.00000f,   0.00000f,   1.00000f },
  {   0.20000f,   0.20000f,   1.00000f },
  {   0.39608f,   0.39608f,   1.00000f },
  {   0.60000f,   0.60000f,   1.00000f },
  {   0.69804f,   0.69804f,   1.00000f },
  {   0.79608f,   0.79608f,   1.00000f },
  {   0.89804f,   0.89804f,   1.00000f },
  {   0.79608f,   1.00000f,   0.79608f },
  {   0.69804f,   1.00000f,   0.69804f },
  {   0.60000f,   1.00000f,   0.60000f },
  {   0.39608f,   1.00000f,   0.39608f },
  {   0.20000f,   1.00000f,   0.20000f },
  {   0.00000f,   1.00000f,   0.00000f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
