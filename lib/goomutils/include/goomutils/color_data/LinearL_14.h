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
static const std::vector<vivid::srgb_t> LinearL_14
{
  {   0.01569f,   0.01569f,   0.01569f },
  {   0.15686f,   0.06667f,   0.13725f },
  {   0.17647f,   0.10588f,   0.36078f },
  {   0.11765f,   0.20000f,   0.48235f },
  {   0.08235f,   0.29020f,   0.52157f },
  {   0.00000f,   0.40392f,   0.41961f },
  {   0.00000f,   0.50588f,   0.30980f },
  {   0.00000f,   0.60392f,   0.20392f },
  {   0.17647f,   0.68627f,   0.00000f },
  {   0.41569f,   0.75686f,   0.00000f },
  {   0.74510f,   0.78824f,   0.00000f },
  {   0.90980f,   0.82353f,   0.60784f },
  {   0.96863f,   0.90196f,   0.84706f },
  {   1.00000f,   1.00000f,   1.00000f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
