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
static const std::vector<vivid::srgb_t> Devon_15
{
  {   0.17255f,   0.10196f,   0.29804f },
  {   0.16471f,   0.16471f,   0.36471f },
  {   0.15686f,   0.23137f,   0.43137f },
  {   0.15294f,   0.30980f,   0.51373f },
  {   0.17647f,   0.37647f,   0.61176f },
  {   0.23529f,   0.42745f,   0.70980f },
  {   0.34902f,   0.49020f,   0.80000f },
  {   0.49412f,   0.56078f,   0.86667f },
  {   0.61961f,   0.61961f,   0.91373f },
  {   0.70588f,   0.68235f,   0.93725f },
  {   0.76471f,   0.74510f,   0.95294f },
  {   0.82353f,   0.80392f,   0.96471f },
  {   0.88235f,   0.87059f,   0.97647f },
  {   0.94118f,   0.93333f,   0.98824f },
  {   1.00000f,   1.00000f,   1.00000f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
