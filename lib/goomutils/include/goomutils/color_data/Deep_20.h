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
static const std::vector<vivid::srgb_t> Deep_20
{
  {   0.99216f,   0.99608f,   0.80000f },
  {   0.89020f,   0.95686f,   0.74118f },
  {   0.77647f,   0.91765f,   0.69020f },
  {   0.66667f,   0.87843f,   0.65882f },
  {   0.54510f,   0.83922f,   0.63922f },
  {   0.45098f,   0.79608f,   0.63922f },
  {   0.38039f,   0.74510f,   0.64314f },
  {   0.33725f,   0.69020f,   0.64314f },
  {   0.31373f,   0.63922f,   0.63529f },
  {   0.29020f,   0.58431f,   0.62353f },
  {   0.27451f,   0.53333f,   0.61176f },
  {   0.25882f,   0.47843f,   0.60000f },
  {   0.24706f,   0.42745f,   0.59216f },
  {   0.24314f,   0.37647f,   0.58039f },
  {   0.24706f,   0.31373f,   0.55686f },
  {   0.25882f,   0.26275f,   0.50196f },
  {   0.24706f,   0.21961f,   0.41176f },
  {   0.22353f,   0.18039f,   0.32941f },
  {   0.18824f,   0.14118f,   0.24314f },
  {   0.15686f,   0.10196f,   0.17255f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
