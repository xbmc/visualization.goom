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
static const std::vector<vivid::srgb_t> Bilbao_14
{
  {   1.00000f,   1.00000f,   1.00000f },
  {   0.89804f,   0.89804f,   0.89412f },
  {   0.81961f,   0.81176f,   0.78824f },
  {   0.76863f,   0.74902f,   0.67843f },
  {   0.73725f,   0.70196f,   0.58039f },
  {   0.70588f,   0.63922f,   0.47843f },
  {   0.67451f,   0.56471f,   0.41569f },
  {   0.65490f,   0.49412f,   0.38431f },
  {   0.63529f,   0.42745f,   0.35294f },
  {   0.61176f,   0.35294f,   0.31765f },
  {   0.56078f,   0.27451f,   0.26275f },
  {   0.48235f,   0.18431f,   0.18039f },
  {   0.39608f,   0.09804f,   0.10196f },
  {   0.30196f,   0.00000f,   0.00392f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
