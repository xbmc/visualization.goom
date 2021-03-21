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
static const std::vector<vivid::srgb_t> RdYlBu_6
{
  {   0.84314f,   0.18824f,   0.15294f },
  {   0.98824f,   0.55294f,   0.34902f },
  {   0.99608f,   0.87843f,   0.56471f },
  {   0.87843f,   0.95294f,   0.97255f },
  {   0.56863f,   0.74902f,   0.85882f },
  {   0.27059f,   0.45882f,   0.70588f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
