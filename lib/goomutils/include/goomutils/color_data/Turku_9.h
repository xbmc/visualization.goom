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
static const std::vector<vivid::srgb_t> Turku_9
{
  {   0.00000f,   0.00000f,   0.00000f },
  {   0.15686f,   0.15686f,   0.13725f },
  {   0.28627f,   0.28627f,   0.22745f },
  {   0.41961f,   0.41569f,   0.28627f },
  {   0.57647f,   0.54902f,   0.35686f },
  {   0.76078f,   0.63922f,   0.45098f },
  {   0.89412f,   0.66667f,   0.56078f },
  {   0.98431f,   0.76471f,   0.74118f },
  {   1.00000f,   0.90196f,   0.90196f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
