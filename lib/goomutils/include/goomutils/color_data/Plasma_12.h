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
static const std::vector<vivid::srgb_t> Plasma_12
{
  {   0.05098f,   0.03137f,   0.52941f },
  {   0.24314f,   0.01569f,   0.61176f },
  {   0.38824f,   0.00000f,   0.65490f },
  {   0.52941f,   0.02745f,   0.65098f },
  {   0.65098f,   0.12549f,   0.59608f },
  {   0.75294f,   0.22745f,   0.51373f },
  {   0.83529f,   0.32941f,   0.43137f },
  {   0.90588f,   0.43529f,   0.35294f },
  {   0.96078f,   0.54902f,   0.27451f },
  {   0.99216f,   0.68235f,   0.19608f },
  {   0.98824f,   0.82353f,   0.14510f },
  {   0.94118f,   0.97647f,   0.12941f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
