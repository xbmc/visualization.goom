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
static const std::vector<vivid::srgb_t> GnBu_7
{
  {   0.94118f,   0.97647f,   0.90980f },
  {   0.80000f,   0.92157f,   0.77255f },
  {   0.65882f,   0.86667f,   0.70980f },
  {   0.48235f,   0.80000f,   0.76863f },
  {   0.30588f,   0.70196f,   0.82745f },
  {   0.16863f,   0.54902f,   0.74510f },
  {   0.03137f,   0.34510f,   0.61961f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
