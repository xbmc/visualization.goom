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
static const std::vector<vivid::srgb_t> Matter_8
{
  {   0.99608f,   0.92941f,   0.69020f },
  {   0.97255f,   0.73333f,   0.51373f },
  {   0.93725f,   0.53725f,   0.37647f },
  {   0.87059f,   0.34902f,   0.32549f },
  {   0.73333f,   0.20000f,   0.36078f },
  {   0.56471f,   0.12157f,   0.38824f },
  {   0.36863f,   0.09412f,   0.34902f },
  {   0.18431f,   0.05882f,   0.24314f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
