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
static const std::vector<vivid::srgb_t> Imola_8
{
  {   0.10196f,   0.20000f,   0.70196f },
  {   0.15294f,   0.29804f,   0.65098f },
  {   0.20392f,   0.39216f,   0.60000f },
  {   0.27451f,   0.47451f,   0.52941f },
  {   0.39216f,   0.58824f,   0.47843f },
  {   0.52941f,   0.72941f,   0.44314f },
  {   0.70980f,   0.88627f,   0.40784f },
  {   1.00000f,   1.00000f,   0.40000f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
