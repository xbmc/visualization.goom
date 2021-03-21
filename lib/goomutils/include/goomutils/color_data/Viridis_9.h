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
static const std::vector<vivid::srgb_t> Viridis_9
{
  {   0.26667f,   0.00392f,   0.32941f },
  {   0.27843f,   0.17647f,   0.48235f },
  {   0.23137f,   0.32157f,   0.54510f },
  {   0.17255f,   0.44706f,   0.55686f },
  {   0.12941f,   0.56863f,   0.54902f },
  {   0.15294f,   0.67843f,   0.50588f },
  {   0.36078f,   0.78431f,   0.38824f },
  {   0.66667f,   0.86275f,   0.19608f },
  {   0.99216f,   0.90588f,   0.14510f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
