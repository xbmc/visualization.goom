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
static const std::vector<vivid::srgb_t> Dense_13
{
  {   0.90196f,   0.94510f,   0.94510f },
  {   0.76078f,   0.87451f,   0.90196f },
  {   0.63529f,   0.80784f,   0.88627f },
  {   0.52549f,   0.72549f,   0.89020f },
  {   0.46275f,   0.64314f,   0.89804f },
  {   0.45490f,   0.54510f,   0.88627f },
  {   0.47059f,   0.44314f,   0.83529f },
  {   0.47451f,   0.34902f,   0.75294f },
  {   0.46275f,   0.25882f,   0.64706f },
  {   0.43529f,   0.18039f,   0.52157f },
  {   0.38431f,   0.11765f,   0.38824f },
  {   0.30980f,   0.07843f,   0.25098f },
  {   0.21176f,   0.05490f,   0.14118f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
