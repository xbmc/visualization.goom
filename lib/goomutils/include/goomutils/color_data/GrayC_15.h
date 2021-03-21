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
static const std::vector<vivid::srgb_t> GrayC_15
{
  {   1.00000f,   1.00000f,   1.00000f },
  {   0.92157f,   0.92157f,   0.92157f },
  {   0.84314f,   0.84314f,   0.84314f },
  {   0.76078f,   0.76078f,   0.76078f },
  {   0.68627f,   0.68627f,   0.68627f },
  {   0.61176f,   0.61176f,   0.61176f },
  {   0.53725f,   0.53725f,   0.53725f },
  {   0.46275f,   0.46275f,   0.46275f },
  {   0.39608f,   0.39608f,   0.39608f },
  {   0.32941f,   0.32941f,   0.32941f },
  {   0.26275f,   0.26275f,   0.26275f },
  {   0.20392f,   0.20392f,   0.20392f },
  {   0.14118f,   0.14118f,   0.14118f },
  {   0.08627f,   0.08627f,   0.08627f },
  {   0.00000f,   0.00000f,   0.00000f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
