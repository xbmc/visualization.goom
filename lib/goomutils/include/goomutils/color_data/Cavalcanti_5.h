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
static const std::vector<vivid::srgb_t> Cavalcanti_5
{
  {   0.81961f,   0.66667f,   0.00000f },
  {   0.03137f,   0.19608f,   0.07451f },
  {   0.57255f,   0.58039f,   0.37647f },
  {   0.43529f,   0.59608f,   0.47451f },
  {   0.51765f,   0.12941f,   0.06667f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
