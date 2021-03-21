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
static const std::vector<vivid::srgb_t> Royal2_5
{
  {   0.76078f,   0.67059f,   0.72941f },
  {   0.54902f,   0.23137f,   0.28627f },
  {   0.71373f,   0.67451f,   0.65098f },
  {   0.12941f,   0.12549f,   0.32549f },
  {   0.81961f,   0.82745f,   0.83529f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
