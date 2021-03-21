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
static const std::vector<vivid::srgb_t> BrwnYl_7
{
  {   0.92941f,   0.89804f,   0.81176f },
  {   0.87843f,   0.76078f,   0.63529f },
  {   0.82745f,   0.61176f,   0.51373f },
  {   0.75686f,   0.46275f,   0.43529f },
  {   0.65098f,   0.32941f,   0.38039f },
  {   0.50588f,   0.21569f,   0.32549f },
  {   0.32941f,   0.12157f,   0.24706f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
