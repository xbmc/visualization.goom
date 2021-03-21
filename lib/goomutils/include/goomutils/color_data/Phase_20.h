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
static const std::vector<vivid::srgb_t> Phase_20
{
  {   0.65882f,   0.47059f,   0.05098f },
  {   0.72941f,   0.41961f,   0.13725f },
  {   0.79216f,   0.36078f,   0.22745f },
  {   0.83529f,   0.29412f,   0.32549f },
  {   0.86667f,   0.21961f,   0.46275f },
  {   0.87059f,   0.15686f,   0.61569f },
  {   0.83137f,   0.16471f,   0.78039f },
  {   0.76471f,   0.24314f,   0.88627f },
  {   0.67451f,   0.32941f,   0.94510f },
  {   0.56078f,   0.41176f,   0.95686f },
  {   0.43137f,   0.47843f,   0.92157f },
  {   0.27843f,   0.53333f,   0.83529f },
  {   0.16471f,   0.56471f,   0.72941f },
  {   0.10196f,   0.58039f,   0.62745f },
  {   0.05490f,   0.59608f,   0.51765f },
  {   0.07451f,   0.60392f,   0.40000f },
  {   0.23529f,   0.60000f,   0.23529f },
  {   0.41961f,   0.56471f,   0.09020f },
  {   0.56078f,   0.51765f,   0.05098f },
  {   0.65882f,   0.47059f,   0.05098f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
