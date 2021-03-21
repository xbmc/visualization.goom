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
static const std::vector<vivid::srgb_t> Devon_14
{
  {   0.17255f,   0.10196f,   0.29804f },
  {   0.16471f,   0.17255f,   0.37255f },
  {   0.15686f,   0.24314f,   0.44314f },
  {   0.15294f,   0.32549f,   0.53333f },
  {   0.18824f,   0.39216f,   0.63922f },
  {   0.27059f,   0.45098f,   0.74902f },
  {   0.41961f,   0.52549f,   0.83529f },
  {   0.56078f,   0.58824f,   0.89020f },
  {   0.67843f,   0.65882f,   0.93333f },
  {   0.74902f,   0.72549f,   0.94902f },
  {   0.80784f,   0.79216f,   0.96078f },
  {   0.87059f,   0.86275f,   0.97255f },
  {   0.93333f,   0.92941f,   0.98824f },
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
