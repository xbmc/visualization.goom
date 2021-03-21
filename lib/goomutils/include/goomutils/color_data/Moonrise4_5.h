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
static const std::vector<vivid::srgb_t> Moonrise4_5
{
  {   0.48235f,   0.52941f,   0.38039f },
  {   0.75686f,   0.65098f,   0.18039f },
  {   0.30980f,   0.56078f,   0.41961f },
  {   0.23137f,   0.27059f,   0.23529f },
  {   0.62353f,   0.19608f,   0.03137f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
