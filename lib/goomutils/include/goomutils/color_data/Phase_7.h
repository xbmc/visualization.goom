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
static const std::vector<vivid::srgb_t> Phase_7
{
  {   0.65882f,   0.47059f,   0.05098f },
  {   0.84314f,   0.28627f,   0.34118f },
  {   0.81569f,   0.18431f,   0.81569f },
  {   0.49020f,   0.45098f,   0.94118f },
  {   0.11765f,   0.57647f,   0.65882f },
  {   0.19216f,   0.60000f,   0.27451f },
  {   0.65882f,   0.47059f,   0.05098f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
