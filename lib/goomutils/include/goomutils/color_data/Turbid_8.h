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
static const std::vector<vivid::srgb_t> Turbid_8
{
  {   0.91373f,   0.96471f,   0.67059f },
  {   0.83922f,   0.80000f,   0.47059f },
  {   0.77255f,   0.64314f,   0.31373f },
  {   0.69020f,   0.50196f,   0.24314f },
  {   0.56863f,   0.38431f,   0.22745f },
  {   0.42745f,   0.29412f,   0.21176f },
  {   0.27451f,   0.20784f,   0.16863f },
  {   0.13333f,   0.12157f,   0.10588f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
