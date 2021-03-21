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
static const std::vector<vivid::srgb_t> Vik_6
{
  {   0.00000f,   0.07059f,   0.38039f },
  {   0.06667f,   0.39216f,   0.58824f },
  {   0.65490f,   0.78824f,   0.85490f },
  {   0.88235f,   0.72157f,   0.62745f },
  {   0.71765f,   0.35294f,   0.14902f },
  {   0.34902f,   0.00000f,   0.03137f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
