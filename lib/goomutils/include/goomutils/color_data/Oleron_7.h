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
static const std::vector<vivid::srgb_t> Oleron_7
{
  {   0.10196f,   0.14902f,   0.34902f },
  {   0.36471f,   0.41176f,   0.61176f },
  {   0.66667f,   0.71765f,   0.90980f },
  {   0.10196f,   0.29804f,   0.00000f },
  {   0.47843f,   0.44314f,   0.12157f },
  {   0.84314f,   0.70196f,   0.49804f },
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
