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
static const std::vector<vivid::srgb_t> Oleron_20
{
  {   0.10196f,   0.14902f,   0.34902f },
  {   0.18039f,   0.22745f,   0.42745f },
  {   0.26667f,   0.31373f,   0.51373f },
  {   0.34902f,   0.40000f,   0.60000f },
  {   0.44706f,   0.49412f,   0.69412f },
  {   0.53725f,   0.58824f,   0.78824f },
  {   0.63922f,   0.68627f,   0.88235f },
  {   0.72549f,   0.77647f,   0.94902f },
  {   0.79608f,   0.84706f,   0.97255f },
  {   0.87059f,   0.91765f,   0.99216f },
  {   0.16471f,   0.31765f,   0.00000f },
  {   0.28627f,   0.35294f,   0.00392f },
  {   0.39608f,   0.40000f,   0.04706f },
  {   0.51373f,   0.46275f,   0.15686f },
  {   0.63137f,   0.54118f,   0.27843f },
  {   0.74510f,   0.62353f,   0.39608f },
  {   0.87059f,   0.72157f,   0.52549f },
  {   0.94902f,   0.81569f,   0.65490f },
  {   0.97647f,   0.90588f,   0.78039f },
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
