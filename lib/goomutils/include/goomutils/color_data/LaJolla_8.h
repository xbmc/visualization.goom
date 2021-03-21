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
static const std::vector<vivid::srgb_t> LaJolla_8
{
  {   1.00000f,   1.00000f,   0.80000f },
  {   0.98039f,   0.89804f,   0.54510f },
  {   0.93725f,   0.71765f,   0.34902f },
  {   0.90196f,   0.54902f,   0.31765f },
  {   0.80392f,   0.36471f,   0.29804f },
  {   0.56078f,   0.25098f,   0.23137f },
  {   0.30980f,   0.17255f,   0.11765f },
  {   0.10196f,   0.10196f,   0.00392f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
