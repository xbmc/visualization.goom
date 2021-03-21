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
static const std::vector<vivid::srgb_t> LaPaz_12
{
  {   0.10196f,   0.04706f,   0.39216f },
  {   0.12941f,   0.15686f,   0.46667f },
  {   0.15294f,   0.25098f,   0.53333f },
  {   0.18431f,   0.34902f,   0.58824f },
  {   0.23137f,   0.43529f,   0.62353f },
  {   0.30980f,   0.51373f,   0.64314f },
  {   0.41569f,   0.58039f,   0.63137f },
  {   0.53725f,   0.62353f,   0.60392f },
  {   0.66667f,   0.66275f,   0.58431f },
  {   0.82745f,   0.73725f,   0.63922f },
  {   0.95686f,   0.85098f,   0.78824f },
  {   0.99608f,   0.94902f,   0.95294f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
