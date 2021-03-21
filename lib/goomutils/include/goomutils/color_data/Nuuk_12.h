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
static const std::vector<vivid::srgb_t> Nuuk_12
{
  {   0.01961f,   0.34902f,   0.54902f },
  {   0.14118f,   0.37647f,   0.52157f },
  {   0.23922f,   0.41961f,   0.50980f },
  {   0.35686f,   0.48235f,   0.52941f },
  {   0.47451f,   0.55294f,   0.56471f },
  {   0.58431f,   0.61961f,   0.59216f },
  {   0.66275f,   0.67451f,   0.59216f },
  {   0.71373f,   0.71373f,   0.56471f },
  {   0.75294f,   0.75294f,   0.52941f },
  {   0.80784f,   0.80784f,   0.51373f },
  {   0.90196f,   0.90196f,   0.57647f },
  {   0.99608f,   0.99608f,   0.69804f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
