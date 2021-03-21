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
static const std::vector<vivid::srgb_t> Viridis_15
{
  {   0.26667f,   0.00392f,   0.32941f },
  {   0.28235f,   0.10588f,   0.42745f },
  {   0.27451f,   0.19608f,   0.49412f },
  {   0.24706f,   0.28235f,   0.53725f },
  {   0.21176f,   0.36078f,   0.55294f },
  {   0.18039f,   0.43137f,   0.55686f },
  {   0.15294f,   0.49804f,   0.55686f },
  {   0.12941f,   0.56863f,   0.54902f },
  {   0.12157f,   0.63137f,   0.52941f },
  {   0.17647f,   0.69804f,   0.49020f },
  {   0.29020f,   0.75686f,   0.42745f },
  {   0.43922f,   0.81176f,   0.34118f },
  {   0.62745f,   0.85490f,   0.22353f },
  {   0.81569f,   0.88235f,   0.10980f },
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
