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
static const std::vector<vivid::srgb_t> BluGrn_7
{
  {   0.76863f,   0.90196f,   0.76471f },
  {   0.58824f,   0.82353f,   0.64314f },
  {   0.42745f,   0.73725f,   0.56471f },
  {   0.30196f,   0.63529f,   0.51765f },
  {   0.21176f,   0.52941f,   0.47843f },
  {   0.14902f,   0.41961f,   0.43137f },
  {   0.11373f,   0.30980f,   0.37647f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
