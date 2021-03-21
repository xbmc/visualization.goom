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
static const std::vector<vivid::srgb_t> Cork_15
{
  {   0.17255f,   0.10196f,   0.29804f },
  {   0.16471f,   0.20392f,   0.40000f },
  {   0.17255f,   0.30980f,   0.50588f },
  {   0.27059f,   0.43529f,   0.60784f },
  {   0.41569f,   0.55294f,   0.69020f },
  {   0.56863f,   0.67451f,   0.77255f },
  {   0.72941f,   0.79608f,   0.85882f },
  {   0.85882f,   0.90196f,   0.89804f },
  {   0.77255f,   0.86667f,   0.78431f },
  {   0.63137f,   0.78431f,   0.64314f },
  {   0.49020f,   0.70196f,   0.50588f },
  {   0.35294f,   0.61176f,   0.36471f },
  {   0.25882f,   0.49020f,   0.20784f },
  {   0.25490f,   0.38824f,   0.09804f },
  {   0.25882f,   0.30196f,   0.01176f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
