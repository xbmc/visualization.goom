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
static const std::vector<vivid::srgb_t> Acton_7
{
  {   0.18039f,   0.12941f,   0.30196f },
  {   0.35686f,   0.28235f,   0.45098f },
  {   0.57255f,   0.38824f,   0.56471f },
  {   0.76863f,   0.43137f,   0.60784f },
  {   0.83137f,   0.58431f,   0.72157f },
  {   0.84314f,   0.72941f,   0.82353f },
  {   0.90196f,   0.90196f,   0.94118f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
