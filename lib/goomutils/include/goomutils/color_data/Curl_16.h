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
static const std::vector<vivid::srgb_t> Curl_16
{
  {   0.08235f,   0.11373f,   0.26667f },
  {   0.10588f,   0.24314f,   0.34118f },
  {   0.10196f,   0.36471f,   0.41569f },
  {   0.06667f,   0.49020f,   0.47451f },
  {   0.23137f,   0.60784f,   0.50588f },
  {   0.49020f,   0.70196f,   0.56471f },
  {   0.71373f,   0.79608f,   0.68627f },
  {   0.90588f,   0.90196f,   0.85882f },
  {   0.95686f,   0.88235f,   0.84706f },
  {   0.90196f,   0.71765f,   0.63529f },
  {   0.85882f,   0.54902f,   0.46667f },
  {   0.79216f,   0.38824f,   0.38824f },
  {   0.68235f,   0.25098f,   0.37647f },
  {   0.54118f,   0.13725f,   0.37647f },
  {   0.37647f,   0.07843f,   0.33333f },
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
