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
static const std::vector<vivid::srgb_t> Devon_12
{
  {   0.17255f,   0.10196f,   0.29804f },
  {   0.16471f,   0.18431f,   0.38431f },
  {   0.15294f,   0.27059f,   0.47451f },
  {   0.16863f,   0.36471f,   0.59608f },
  {   0.24314f,   0.43529f,   0.72157f },
  {   0.40392f,   0.51765f,   0.82745f },
  {   0.57647f,   0.59608f,   0.89804f },
  {   0.69804f,   0.67843f,   0.93725f },
  {   0.77647f,   0.75294f,   0.95294f },
  {   0.85098f,   0.83529f,   0.96863f },
  {   0.92549f,   0.91765f,   0.98431f },
  {   1.00000f,   1.00000f,   1.00000f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
