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
static const std::vector<vivid::srgb_t> Solar_20
{
  {   0.20000f,   0.07843f,   0.09412f },
  {   0.26275f,   0.09804f,   0.11765f },
  {   0.33333f,   0.11765f,   0.13333f },
  {   0.39608f,   0.13725f,   0.14118f },
  {   0.46667f,   0.15686f,   0.14118f },
  {   0.52157f,   0.18039f,   0.12941f },
  {   0.57647f,   0.21961f,   0.11373f },
  {   0.62353f,   0.26275f,   0.09804f },
  {   0.65882f,   0.30980f,   0.08627f },
  {   0.69804f,   0.36471f,   0.07843f },
  {   0.72941f,   0.41961f,   0.07451f },
  {   0.75686f,   0.47843f,   0.07843f },
  {   0.78039f,   0.53333f,   0.09020f },
  {   0.80392f,   0.59216f,   0.10588f },
  {   0.82745f,   0.65490f,   0.12941f },
  {   0.84314f,   0.71765f,   0.15686f },
  {   0.85882f,   0.78431f,   0.19216f },
  {   0.87059f,   0.85098f,   0.22353f },
  {   0.87843f,   0.92157f,   0.25882f },
  {   0.88235f,   0.99216f,   0.29412f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
