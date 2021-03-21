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
static const std::vector<vivid::srgb_t> Margot1_5
{
  {   0.53725f,   0.46667f,   0.07059f },
  {   0.95294f,   0.76078f,   0.64314f },
  {   0.96471f,   0.62353f,   0.59216f },
  {   0.99608f,   0.83922f,   0.54902f },
  {   0.38431f,   0.56471f,   0.45882f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
