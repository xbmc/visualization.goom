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
static const std::vector<vivid::srgb_t> Emrld_6
{
  {   0.82745f,   0.94902f,   0.63922f },
  {   0.59216f,   0.88235f,   0.58824f },
  {   0.42353f,   0.75294f,   0.54510f },
  {   0.12941f,   0.47843f,   0.47451f },
  {   0.06275f,   0.34902f,   0.39608f },
  {   0.02745f,   0.25098f,   0.31373f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
