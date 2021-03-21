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
static const std::vector<vivid::srgb_t> Darjeeling4_5
{
  {   0.45490f,   0.40392f,   0.40784f },
  {   0.40784f,   0.27843f,   0.38431f },
  {   0.50196f,   0.03137f,   0.02353f },
  {   0.73725f,   0.51765f,   0.05490f },
  {   0.68235f,   0.34902f,   0.36078f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
