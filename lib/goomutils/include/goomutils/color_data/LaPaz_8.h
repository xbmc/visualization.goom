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
static const std::vector<vivid::srgb_t> LaPaz_8
{
  {   0.10196f,   0.04706f,   0.39216f },
  {   0.14510f,   0.21176f,   0.50588f },
  {   0.18824f,   0.36078f,   0.59608f },
  {   0.28235f,   0.49020f,   0.63922f },
  {   0.45098f,   0.59608f,   0.62745f },
  {   0.64706f,   0.65490f,   0.58431f },
  {   0.89412f,   0.78824f,   0.69804f },
  {   0.99608f,   0.94902f,   0.95294f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
