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
static const std::vector<vivid::srgb_t> Tokyo_20
{
  {   0.10196f,   0.05490f,   0.20392f },
  {   0.18039f,   0.08235f,   0.24706f },
  {   0.26275f,   0.12157f,   0.29412f },
  {   0.34118f,   0.16863f,   0.34510f },
  {   0.41961f,   0.22745f,   0.39216f },
  {   0.47451f,   0.29020f,   0.43137f },
  {   0.51373f,   0.35294f,   0.46275f },
  {   0.53333f,   0.40392f,   0.48627f },
  {   0.54902f,   0.45490f,   0.50196f },
  {   0.55686f,   0.50588f,   0.51765f },
  {   0.56863f,   0.55294f,   0.52941f },
  {   0.57647f,   0.60000f,   0.54510f },
  {   0.58431f,   0.64706f,   0.55686f },
  {   0.59608f,   0.69804f,   0.57255f },
  {   0.62353f,   0.75686f,   0.59216f },
  {   0.66667f,   0.82353f,   0.62745f },
  {   0.75294f,   0.89804f,   0.68235f },
  {   0.84314f,   0.95294f,   0.74118f },
  {   0.92941f,   0.98431f,   0.80000f },
  {   0.99608f,   0.99608f,   0.84706f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
