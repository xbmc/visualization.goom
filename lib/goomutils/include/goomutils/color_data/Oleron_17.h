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
static const std::vector<vivid::srgb_t> Oleron_17
{
  {   0.10196f,   0.14902f,   0.34902f },
  {   0.19608f,   0.24706f,   0.44706f },
  {   0.29804f,   0.34902f,   0.54902f },
  {   0.40392f,   0.45490f,   0.65490f },
  {   0.51373f,   0.56471f,   0.76471f },
  {   0.63137f,   0.67843f,   0.87843f },
  {   0.73725f,   0.78824f,   0.95294f },
  {   0.82353f,   0.87059f,   0.98039f },
  {   0.10196f,   0.29804f,   0.00000f },
  {   0.24314f,   0.34118f,   0.00000f },
  {   0.37647f,   0.38824f,   0.03529f },
  {   0.52157f,   0.47059f,   0.16471f },
  {   0.65882f,   0.56078f,   0.30588f },
  {   0.80000f,   0.66667f,   0.45098f },
  {   0.92549f,   0.78039f,   0.60392f },
  {   0.97255f,   0.88627f,   0.75294f },
  {   0.99216f,   0.99216f,   0.90196f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
