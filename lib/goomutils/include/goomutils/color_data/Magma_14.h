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
static const std::vector<vivid::srgb_t> Magma_14
{
  {   0.00000f,   0.00000f,   0.01569f },
  {   0.05490f,   0.04314f,   0.16863f },
  {   0.15294f,   0.07059f,   0.34510f },
  {   0.28627f,   0.06275f,   0.47059f },
  {   0.40392f,   0.10588f,   0.50196f },
  {   0.52549f,   0.15294f,   0.50588f },
  {   0.65098f,   0.19216f,   0.49020f },
  {   0.77255f,   0.23529f,   0.45490f },
  {   0.89020f,   0.30588f,   0.39608f },
  {   0.96471f,   0.42353f,   0.36078f },
  {   0.98824f,   0.56471f,   0.39608f },
  {   0.99608f,   0.71373f,   0.48627f },
  {   0.99608f,   0.84706f,   0.60392f },
  {   0.98824f,   0.99216f,   0.74902f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
