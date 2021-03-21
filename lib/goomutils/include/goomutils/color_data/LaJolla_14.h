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
static const std::vector<vivid::srgb_t> LaJolla_14
{
  {   1.00000f,   1.00000f,   0.80000f },
  {   0.99216f,   0.94902f,   0.65882f },
  {   0.97647f,   0.88627f,   0.52157f },
  {   0.95294f,   0.79216f,   0.39608f },
  {   0.93333f,   0.69020f,   0.34118f },
  {   0.91373f,   0.59608f,   0.32157f },
  {   0.89020f,   0.50588f,   0.31373f },
  {   0.84314f,   0.41176f,   0.30588f },
  {   0.73725f,   0.31765f,   0.28235f },
  {   0.59608f,   0.26275f,   0.24314f },
  {   0.46275f,   0.22353f,   0.19216f },
  {   0.32941f,   0.18039f,   0.12549f },
  {   0.21176f,   0.14118f,   0.07451f },
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
