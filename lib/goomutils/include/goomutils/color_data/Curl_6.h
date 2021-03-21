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
static const std::vector<vivid::srgb_t> Curl_6
{
  {   0.08235f,   0.11373f,   0.26667f },
  {   0.06667f,   0.49020f,   0.47451f },
  {   0.71373f,   0.79608f,   0.68627f },
  {   0.90196f,   0.71765f,   0.63529f },
  {   0.68235f,   0.25098f,   0.37647f },
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
