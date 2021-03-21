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
static const std::vector<vivid::srgb_t> Ice_14
{
  {   0.01569f,   0.02353f,   0.07451f },
  {   0.09020f,   0.09020f,   0.18431f },
  {   0.15294f,   0.14510f,   0.29804f },
  {   0.20784f,   0.20784f,   0.42353f },
  {   0.24314f,   0.27059f,   0.54902f },
  {   0.24706f,   0.34902f,   0.64706f },
  {   0.24706f,   0.43922f,   0.70196f },
  {   0.27843f,   0.52157f,   0.73333f },
  {   0.33333f,   0.60392f,   0.76078f },
  {   0.41176f,   0.68627f,   0.79216f },
  {   0.50196f,   0.76471f,   0.82353f },
  {   0.63529f,   0.83922f,   0.86275f },
  {   0.77647f,   0.90980f,   0.92157f },
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
