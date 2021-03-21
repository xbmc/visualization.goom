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
static const std::vector<vivid::srgb_t> Oleron_9
{
  {   0.10196f,   0.14902f,   0.34902f },
  {   0.29804f,   0.34902f,   0.54902f },
  {   0.51373f,   0.56471f,   0.76471f },
  {   0.73725f,   0.78824f,   0.95294f },
  {   0.10196f,   0.29804f,   0.00000f },
  {   0.37647f,   0.38824f,   0.03529f },
  {   0.65882f,   0.56078f,   0.30588f },
  {   0.92549f,   0.78039f,   0.60392f },
  {   0.99216f,   0.99216f,   0.90196f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
