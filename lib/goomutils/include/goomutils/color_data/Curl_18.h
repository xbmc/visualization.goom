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
static const std::vector<vivid::srgb_t> Curl_18
{
  {   0.08235f,   0.11373f,   0.26667f },
  {   0.10588f,   0.22745f,   0.32941f },
  {   0.10588f,   0.33725f,   0.40000f },
  {   0.07451f,   0.44706f,   0.45882f },
  {   0.12157f,   0.55294f,   0.49412f },
  {   0.34118f,   0.64706f,   0.52157f },
  {   0.56078f,   0.72941f,   0.59216f },
  {   0.74902f,   0.81176f,   0.71373f },
  {   0.91765f,   0.90980f,   0.87059f },
  {   0.96078f,   0.89412f,   0.86275f },
  {   0.90980f,   0.74510f,   0.67059f },
  {   0.87451f,   0.60000f,   0.50980f },
  {   0.82353f,   0.45490f,   0.40784f },
  {   0.74510f,   0.32157f,   0.37647f },
  {   0.63529f,   0.20784f,   0.37647f },
  {   0.50588f,   0.11765f,   0.37255f },
  {   0.35294f,   0.07843f,   0.32157f },
  {   0.20392f,   0.05098f,   0.20784f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
