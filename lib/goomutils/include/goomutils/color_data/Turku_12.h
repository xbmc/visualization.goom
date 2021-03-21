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
static const std::vector<vivid::srgb_t> Turku_12
{
  {   0.00000f,   0.00000f,   0.00000f },
  {   0.12157f,   0.12157f,   0.10980f },
  {   0.21569f,   0.21569f,   0.18039f },
  {   0.31373f,   0.30980f,   0.23922f },
  {   0.40392f,   0.40392f,   0.28235f },
  {   0.50980f,   0.49804f,   0.32549f },
  {   0.64314f,   0.58824f,   0.38824f },
  {   0.77647f,   0.64314f,   0.45882f },
  {   0.87059f,   0.65882f,   0.53725f },
  {   0.95294f,   0.70980f,   0.65882f },
  {   0.99216f,   0.80392f,   0.79216f },
  {   1.00000f,   0.90196f,   0.90196f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
