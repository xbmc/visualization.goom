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
static const std::vector<vivid::srgb_t> Tempo_14
{
  {   1.00000f,   0.96471f,   0.95686f },
  {   0.89020f,   0.89020f,   0.84314f },
  {   0.78431f,   0.83137f,   0.74510f },
  {   0.66275f,   0.77255f,   0.65098f },
  {   0.54118f,   0.71765f,   0.58431f },
  {   0.39608f,   0.66667f,   0.53333f },
  {   0.23922f,   0.61176f,   0.50588f },
  {   0.10980f,   0.54902f,   0.49412f },
  {   0.06667f,   0.47451f,   0.47059f },
  {   0.09020f,   0.40000f,   0.43529f },
  {   0.10980f,   0.33333f,   0.39608f },
  {   0.10980f,   0.25882f,   0.35294f },
  {   0.09804f,   0.19216f,   0.30980f },
  {   0.08235f,   0.11373f,   0.26667f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
