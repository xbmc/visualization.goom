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
static const std::vector<vivid::srgb_t> Balance_11
{
  {   0.09412f,   0.10980f,   0.26275f },
  {   0.16078f,   0.24706f,   0.60392f },
  {   0.08627f,   0.43922f,   0.73725f },
  {   0.34902f,   0.61176f,   0.73333f },
  {   0.66667f,   0.76078f,   0.79608f },
  {   0.94510f,   0.92549f,   0.92157f },
  {   0.86275f,   0.69804f,   0.64314f },
  {   0.79216f,   0.47451f,   0.36471f },
  {   0.70196f,   0.21961f,   0.14902f },
  {   0.49412f,   0.05490f,   0.16078f },
  {   0.23529f,   0.03529f,   0.07059f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
