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
static const std::vector<vivid::srgb_t> Teal_6
{
  {   0.81961f,   0.93333f,   0.91765f },
  {   0.65882f,   0.85882f,   0.85098f },
  {   0.52157f,   0.76863f,   0.78824f },
  {   0.30980f,   0.56471f,   0.65098f },
  {   0.23137f,   0.45098f,   0.56078f },
  {   0.16471f,   0.33725f,   0.45490f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
