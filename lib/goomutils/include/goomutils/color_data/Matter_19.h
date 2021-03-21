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
static const std::vector<vivid::srgb_t> Matter_19
{
  {   0.99608f,   0.92941f,   0.69020f },
  {   0.98824f,   0.85490f,   0.61569f },
  {   0.98039f,   0.77647f,   0.54902f },
  {   0.96863f,   0.70196f,   0.48627f },
  {   0.95686f,   0.62353f,   0.42745f },
  {   0.94118f,   0.54510f,   0.38039f },
  {   0.92157f,   0.47059f,   0.34510f },
  {   0.89412f,   0.40000f,   0.32549f },
  {   0.85882f,   0.32941f,   0.32549f },
  {   0.80784f,   0.26275f,   0.33725f },
  {   0.75294f,   0.21176f,   0.35686f },
  {   0.69020f,   0.17255f,   0.37255f },
  {   0.62353f,   0.14118f,   0.38431f },
  {   0.55294f,   0.11765f,   0.38824f },
  {   0.47843f,   0.10588f,   0.38431f },
  {   0.40392f,   0.09804f,   0.36471f },
  {   0.32549f,   0.08627f,   0.32941f },
  {   0.25490f,   0.07451f,   0.29020f },
  {   0.18431f,   0.05882f,   0.24314f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
