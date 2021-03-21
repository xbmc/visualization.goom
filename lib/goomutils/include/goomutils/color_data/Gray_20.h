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
static const std::vector<vivid::srgb_t> Gray_20
{
  {   0.00000f,   0.00000f,   0.00000f },
  {   0.02353f,   0.02353f,   0.02353f },
  {   0.08235f,   0.07843f,   0.07843f },
  {   0.12941f,   0.12941f,   0.12941f },
  {   0.18039f,   0.18039f,   0.18039f },
  {   0.22745f,   0.22353f,   0.22353f },
  {   0.27843f,   0.27451f,   0.27451f },
  {   0.32157f,   0.32157f,   0.31765f },
  {   0.36863f,   0.36863f,   0.36471f },
  {   0.41961f,   0.41961f,   0.41569f },
  {   0.46667f,   0.46667f,   0.46275f },
  {   0.52157f,   0.51765f,   0.51765f },
  {   0.57255f,   0.56863f,   0.56863f },
  {   0.62353f,   0.62353f,   0.61961f },
  {   0.68235f,   0.67843f,   0.67843f },
  {   0.73725f,   0.73725f,   0.73333f },
  {   0.80000f,   0.80000f,   0.79608f },
  {   0.86275f,   0.86275f,   0.85882f },
  {   0.93333f,   0.92941f,   0.92549f },
  {   1.00000f,   1.00000f,   0.99216f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
