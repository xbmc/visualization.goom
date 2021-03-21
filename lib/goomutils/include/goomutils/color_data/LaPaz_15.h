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
static const std::vector<vivid::srgb_t> LaPaz_15
{
  {   0.10196f,   0.04706f,   0.39216f },
  {   0.12549f,   0.13725f,   0.45098f },
  {   0.14510f,   0.21176f,   0.50588f },
  {   0.16471f,   0.29020f,   0.55686f },
  {   0.18824f,   0.36078f,   0.59608f },
  {   0.22745f,   0.42745f,   0.62353f },
  {   0.28235f,   0.49020f,   0.63922f },
  {   0.36078f,   0.54902f,   0.63922f },
  {   0.45098f,   0.59608f,   0.62745f },
  {   0.54510f,   0.62745f,   0.60392f },
  {   0.64706f,   0.65490f,   0.58431f },
  {   0.76471f,   0.70196f,   0.60392f },
  {   0.89412f,   0.78824f,   0.69804f },
  {   0.96863f,   0.87451f,   0.82745f },
  {   0.99608f,   0.94902f,   0.95294f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
