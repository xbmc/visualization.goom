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
static const std::vector<vivid::srgb_t> Ice_16
{
  {   0.01569f,   0.02353f,   0.07451f },
  {   0.07843f,   0.07843f,   0.16863f },
  {   0.13725f,   0.13333f,   0.26667f },
  {   0.18824f,   0.18431f,   0.37255f },
  {   0.22745f,   0.23529f,   0.48235f },
  {   0.24706f,   0.29412f,   0.58824f },
  {   0.24314f,   0.36863f,   0.66275f },
  {   0.24706f,   0.44314f,   0.70588f },
  {   0.27451f,   0.51765f,   0.73333f },
  {   0.32157f,   0.58824f,   0.75686f },
  {   0.38039f,   0.65882f,   0.78039f },
  {   0.45490f,   0.72941f,   0.80784f },
  {   0.54902f,   0.79608f,   0.83922f },
  {   0.67059f,   0.85882f,   0.87843f },
  {   0.79608f,   0.92157f,   0.93333f },
  {   0.91765f,   0.99216f,   0.99216f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
