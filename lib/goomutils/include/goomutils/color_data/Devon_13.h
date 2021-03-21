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
static const std::vector<vivid::srgb_t> Devon_13
{
  {   0.17255f,   0.10196f,   0.29804f },
  {   0.16471f,   0.17647f,   0.37647f },
  {   0.15294f,   0.25490f,   0.45490f },
  {   0.16078f,   0.34510f,   0.56078f },
  {   0.21176f,   0.41176f,   0.67843f },
  {   0.32549f,   0.48235f,   0.78824f },
  {   0.49412f,   0.56078f,   0.86667f },
  {   0.63922f,   0.63137f,   0.91765f },
  {   0.72941f,   0.70196f,   0.94510f },
  {   0.79216f,   0.77647f,   0.95686f },
  {   0.85882f,   0.84706f,   0.97255f },
  {   0.92941f,   0.92549f,   0.98431f },
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
