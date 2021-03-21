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
static const std::vector<vivid::srgb_t> Buda_13
{
  {   0.70196f,   0.00392f,   0.70196f },
  {   0.70196f,   0.13725f,   0.63529f },
  {   0.70980f,   0.22353f,   0.59608f },
  {   0.73725f,   0.30588f,   0.56471f },
  {   0.76078f,   0.38039f,   0.54118f },
  {   0.78431f,   0.45098f,   0.51765f },
  {   0.80392f,   0.52157f,   0.49412f },
  {   0.82353f,   0.59216f,   0.47843f },
  {   0.84314f,   0.66667f,   0.45882f },
  {   0.85882f,   0.74118f,   0.43922f },
  {   0.87843f,   0.81569f,   0.41961f },
  {   0.91373f,   0.90196f,   0.40392f },
  {   1.00000f,   1.00000f,   0.40000f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
