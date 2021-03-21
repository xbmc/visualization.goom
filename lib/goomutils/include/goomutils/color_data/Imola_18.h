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
static const std::vector<vivid::srgb_t> Imola_18
{
  {   0.10196f,   0.20000f,   0.70196f },
  {   0.12549f,   0.24314f,   0.67843f },
  {   0.14510f,   0.28235f,   0.65882f },
  {   0.16471f,   0.32157f,   0.63922f },
  {   0.18431f,   0.35686f,   0.61961f },
  {   0.20392f,   0.39608f,   0.59608f },
  {   0.23529f,   0.43137f,   0.56863f },
  {   0.26667f,   0.46275f,   0.53725f },
  {   0.30588f,   0.50196f,   0.50980f },
  {   0.35294f,   0.54902f,   0.49020f },
  {   0.40392f,   0.60392f,   0.47451f },
  {   0.46275f,   0.66275f,   0.45882f },
  {   0.52157f,   0.72157f,   0.44706f },
  {   0.58431f,   0.78431f,   0.43137f },
  {   0.65490f,   0.84706f,   0.41569f },
  {   0.75294f,   0.90980f,   0.40392f },
  {   0.87451f,   0.95686f,   0.40000f },
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
