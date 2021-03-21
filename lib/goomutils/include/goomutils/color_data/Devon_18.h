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
static const std::vector<vivid::srgb_t> Devon_18
{
  {   0.17255f,   0.10196f,   0.29804f },
  {   0.16471f,   0.15686f,   0.35294f },
  {   0.16078f,   0.21176f,   0.41176f },
  {   0.15294f,   0.26667f,   0.47059f },
  {   0.15686f,   0.32941f,   0.54118f },
  {   0.18039f,   0.38431f,   0.62353f },
  {   0.23137f,   0.42745f,   0.70588f },
  {   0.31765f,   0.47843f,   0.78431f },
  {   0.43529f,   0.53333f,   0.84314f },
  {   0.54902f,   0.58431f,   0.88627f },
  {   0.64314f,   0.63529f,   0.92157f },
  {   0.70980f,   0.68627f,   0.94118f },
  {   0.76078f,   0.73725f,   0.94902f },
  {   0.80784f,   0.78824f,   0.96078f },
  {   0.85490f,   0.83922f,   0.96863f },
  {   0.90196f,   0.89412f,   0.98039f },
  {   0.94902f,   0.94510f,   0.98824f },
  {   1.00000f,   1.00000f,   1.00000f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
