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
static const std::vector<vivid::srgb_t> Dense_17
{
  {   0.90196f,   0.94510f,   0.94510f },
  {   0.79608f,   0.89412f,   0.90980f },
  {   0.69412f,   0.83922f,   0.89020f },
  {   0.60392f,   0.78431f,   0.88627f },
  {   0.52549f,   0.72549f,   0.89020f },
  {   0.47451f,   0.66275f,   0.89412f },
  {   0.45098f,   0.59216f,   0.89412f },
  {   0.45882f,   0.51765f,   0.87451f },
  {   0.47059f,   0.44314f,   0.83529f },
  {   0.47451f,   0.37647f,   0.78039f },
  {   0.47059f,   0.30588f,   0.70196f },
  {   0.45882f,   0.23922f,   0.61569f },
  {   0.43529f,   0.18039f,   0.52157f },
  {   0.40000f,   0.12941f,   0.42353f },
  {   0.35294f,   0.09412f,   0.31765f },
  {   0.28627f,   0.07059f,   0.21961f },
  {   0.21176f,   0.05490f,   0.14118f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
