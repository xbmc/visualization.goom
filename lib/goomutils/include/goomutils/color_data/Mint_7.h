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
static const std::vector<vivid::srgb_t> Mint_7
{
  {   0.89412f,   0.94510f,   0.88235f },
  {   0.70588f,   0.85098f,   0.80000f },
  {   0.53725f,   0.75294f,   0.71373f },
  {   0.38824f,   0.65098f,   0.62745f },
  {   0.26667f,   0.54902f,   0.54118f },
  {   0.15686f,   0.44706f,   0.45490f },
  {   0.05098f,   0.34510f,   0.37255f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
