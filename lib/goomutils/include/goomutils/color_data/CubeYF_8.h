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
static const std::vector<vivid::srgb_t> CubeYF_8
{
  {   0.48235f,   0.00784f,   0.56471f },
  {   0.50588f,   0.24314f,   0.87451f },
  {   0.39608f,   0.46667f,   0.98431f },
  {   0.27059f,   0.65490f,   0.81569f },
  {   0.26667f,   0.78824f,   0.56863f },
  {   0.34902f,   0.87843f,   0.31765f },
  {   0.60392f,   0.92549f,   0.32941f },
  {   0.81961f,   0.92157f,   0.35686f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
