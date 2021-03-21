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
static const std::vector<vivid::srgb_t> Turbid_10
{
  {   0.91373f,   0.96471f,   0.67059f },
  {   0.85490f,   0.83529f,   0.51373f },
  {   0.80392f,   0.70980f,   0.37255f },
  {   0.74902f,   0.59216f,   0.27843f },
  {   0.67843f,   0.49020f,   0.23922f },
  {   0.58431f,   0.39608f,   0.22745f },
  {   0.47451f,   0.32549f,   0.21961f },
  {   0.36078f,   0.25882f,   0.19608f },
  {   0.24314f,   0.18824f,   0.15686f },
  {   0.13333f,   0.12157f,   0.10588f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
