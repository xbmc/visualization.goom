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
static const std::vector<vivid::srgb_t> Thermal_14
{
  {   0.01569f,   0.13725f,   0.20000f },
  {   0.04314f,   0.18824f,   0.36471f },
  {   0.14510f,   0.20392f,   0.56078f },
  {   0.30588f,   0.21961f,   0.61961f },
  {   0.41569f,   0.27059f,   0.58431f },
  {   0.52157f,   0.31765f,   0.55686f },
  {   0.63529f,   0.35686f,   0.52941f },
  {   0.74510f,   0.38824f,   0.48235f },
  {   0.85882f,   0.43137f,   0.40784f },
  {   0.94510f,   0.50196f,   0.30980f },
  {   0.98431f,   0.60000f,   0.24706f },
  {   0.98431f,   0.72549f,   0.24314f },
  {   0.96078f,   0.84706f,   0.28627f },
  {   0.90980f,   0.98039f,   0.35686f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
