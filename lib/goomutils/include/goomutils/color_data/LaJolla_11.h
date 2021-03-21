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
static const std::vector<vivid::srgb_t> LaJolla_11
{
  {   1.00000f,   1.00000f,   0.80000f },
  {   0.98824f,   0.93333f,   0.61569f },
  {   0.96471f,   0.83137f,   0.43922f },
  {   0.93333f,   0.70196f,   0.34118f },
  {   0.90588f,   0.58039f,   0.32157f },
  {   0.87059f,   0.45490f,   0.30980f },
  {   0.76078f,   0.33333f,   0.29020f },
  {   0.58824f,   0.25882f,   0.24314f },
  {   0.40784f,   0.20784f,   0.16471f },
  {   0.24314f,   0.15294f,   0.08627f },
  {   0.10196f,   0.10196f,   0.00392f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
