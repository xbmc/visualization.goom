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
static const std::vector<vivid::srgb_t> Inferno_12
{
  {   0.00000f,   0.00000f,   0.01569f },
  {   0.07843f,   0.04314f,   0.20392f },
  {   0.22353f,   0.03529f,   0.38824f },
  {   0.38039f,   0.07451f,   0.43137f },
  {   0.52157f,   0.12941f,   0.41961f },
  {   0.66275f,   0.18039f,   0.36863f },
  {   0.79608f,   0.25490f,   0.28627f },
  {   0.90196f,   0.36471f,   0.18431f },
  {   0.96863f,   0.50980f,   0.07059f },
  {   0.98824f,   0.68235f,   0.07059f },
  {   0.96078f,   0.85882f,   0.29804f },
  {   0.98824f,   1.00000f,   0.64314f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
