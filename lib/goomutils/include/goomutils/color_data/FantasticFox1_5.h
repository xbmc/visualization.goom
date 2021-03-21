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
static const std::vector<vivid::srgb_t> FantasticFox1_5
{
  {   0.97647f,   0.85882f,   0.12549f },
  {   0.57647f,   0.29412f,   0.30588f },
  {   0.25882f,   0.09020f,   0.05098f },
  {   0.76078f,   0.47451f,   0.13333f },
  {   0.88627f,   0.78431f,   0.65490f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
