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
static const std::vector<vivid::srgb_t> Imola_12
{
  {   0.10196f,   0.20000f,   0.70196f },
  {   0.13333f,   0.26275f,   0.67059f },
  {   0.16471f,   0.32157f,   0.63922f },
  {   0.19608f,   0.38431f,   0.60784f },
  {   0.23922f,   0.43529f,   0.56471f },
  {   0.29412f,   0.49020f,   0.51765f },
  {   0.36471f,   0.56471f,   0.48627f },
  {   0.45098f,   0.65098f,   0.46275f },
  {   0.54118f,   0.74118f,   0.43922f },
  {   0.65098f,   0.84314f,   0.41569f },
  {   0.81176f,   0.93333f,   0.40000f },
  {   1.00000f,   1.00000f,   0.40000f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
