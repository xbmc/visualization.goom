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
static const std::vector<vivid::srgb_t> Gray_19
{
  {   0.00000f,   0.00000f,   0.00000f },
  {   0.02745f,   0.02745f,   0.02745f },
  {   0.08627f,   0.08235f,   0.08235f },
  {   0.13725f,   0.13725f,   0.13725f },
  {   0.19216f,   0.18824f,   0.18824f },
  {   0.24314f,   0.23922f,   0.23922f },
  {   0.29020f,   0.29020f,   0.28627f },
  {   0.34118f,   0.33725f,   0.33725f },
  {   0.39216f,   0.38824f,   0.38824f },
  {   0.44706f,   0.44314f,   0.44314f },
  {   0.49804f,   0.49412f,   0.49412f },
  {   0.55294f,   0.54902f,   0.54902f },
  {   0.60784f,   0.60392f,   0.60392f },
  {   0.66667f,   0.66275f,   0.65882f },
  {   0.72549f,   0.72549f,   0.72157f },
  {   0.78824f,   0.78431f,   0.78039f },
  {   0.85882f,   0.85490f,   0.85098f },
  {   0.92549f,   0.92549f,   0.92157f },
  {   1.00000f,   1.00000f,   0.99216f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
