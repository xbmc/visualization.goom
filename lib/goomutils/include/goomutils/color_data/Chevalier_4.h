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
static const std::vector<vivid::srgb_t> Chevalier_4
{
  {   0.20784f,   0.32157f,   0.26275f },
  {   0.99608f,   0.79216f,   0.28627f },
  {   0.78824f,   0.83529f,   0.83529f },
  {   0.73333f,   0.63529f,   0.53725f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
