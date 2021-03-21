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
static const std::vector<vivid::srgb_t> Imola_14
{
  {   0.10196f,   0.20000f,   0.70196f },
  {   0.12941f,   0.25490f,   0.67451f },
  {   0.15686f,   0.30588f,   0.64706f },
  {   0.18039f,   0.35686f,   0.62353f },
  {   0.21176f,   0.40392f,   0.59216f },
  {   0.25098f,   0.44706f,   0.55294f },
  {   0.29804f,   0.49804f,   0.51373f },
  {   0.36078f,   0.55686f,   0.48627f },
  {   0.43137f,   0.63137f,   0.46667f },
  {   0.50980f,   0.70980f,   0.44706f },
  {   0.58824f,   0.78824f,   0.42745f },
  {   0.69020f,   0.87451f,   0.40784f },
  {   0.83529f,   0.94118f,   0.40000f },
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
