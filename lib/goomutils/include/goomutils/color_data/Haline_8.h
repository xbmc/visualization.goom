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
static const std::vector<vivid::srgb_t> Haline_8
{
  {   0.16471f,   0.09412f,   0.42353f },
  {   0.10588f,   0.22745f,   0.62745f },
  {   0.08627f,   0.38824f,   0.55294f },
  {   0.19216f,   0.50980f,   0.53333f },
  {   0.27451f,   0.64314f,   0.51373f },
  {   0.41176f,   0.76863f,   0.43529f },
  {   0.72157f,   0.85882f,   0.37647f },
  {   0.99216f,   0.93725f,   0.60392f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
