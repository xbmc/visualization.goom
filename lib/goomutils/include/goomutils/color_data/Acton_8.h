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
static const std::vector<vivid::srgb_t> Acton_8
{
  {   0.18039f,   0.12941f,   0.30196f },
  {   0.32941f,   0.25882f,   0.43137f },
  {   0.51373f,   0.37255f,   0.54510f },
  {   0.67843f,   0.40392f,   0.58431f },
  {   0.82745f,   0.49804f,   0.65882f },
  {   0.82745f,   0.62353f,   0.74902f },
  {   0.85098f,   0.75686f,   0.84314f },
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
