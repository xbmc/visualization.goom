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
static const std::vector<vivid::srgb_t> Cube1_20
{
  {   0.47059f,   0.00000f,   0.52157f },
  {   0.50980f,   0.03529f,   0.66667f },
  {   0.50588f,   0.16471f,   0.81569f },
  {   0.47451f,   0.30196f,   0.92941f },
  {   0.41961f,   0.40784f,   0.99216f },
  {   0.37255f,   0.50980f,   0.95294f },
  {   0.31373f,   0.59608f,   0.87843f },
  {   0.24706f,   0.67059f,   0.78824f },
  {   0.22745f,   0.73725f,   0.68235f },
  {   0.27059f,   0.79216f,   0.55686f },
  {   0.30196f,   0.83137f,   0.44314f },
  {   0.34118f,   0.87843f,   0.30588f },
  {   0.42745f,   0.90980f,   0.29412f },
  {   0.55686f,   0.92157f,   0.32157f },
  {   0.68627f,   0.92549f,   0.34118f },
  {   0.78431f,   0.92549f,   0.34902f },
  {   0.84706f,   0.88627f,   0.35686f },
  {   0.90588f,   0.81569f,   0.36471f },
  {   0.96078f,   0.71373f,   0.36863f },
  {   0.97647f,   0.58824f,   0.35686f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
