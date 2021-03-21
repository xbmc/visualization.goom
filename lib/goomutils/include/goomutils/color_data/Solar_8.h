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
static const std::vector<vivid::srgb_t> Solar_8
{
  {   0.20000f,   0.07843f,   0.09412f },
  {   0.37647f,   0.12941f,   0.14118f },
  {   0.54902f,   0.19608f,   0.12549f },
  {   0.66667f,   0.31765f,   0.08627f },
  {   0.75294f,   0.46667f,   0.07843f },
  {   0.81569f,   0.62745f,   0.12157f },
  {   0.86275f,   0.80392f,   0.20000f },
  {   0.88235f,   0.99216f,   0.29412f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
