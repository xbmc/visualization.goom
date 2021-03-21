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
static const std::vector<vivid::srgb_t> Inferno_16
{
  {   0.00000f,   0.00000f,   0.01569f },
  {   0.04706f,   0.03137f,   0.14902f },
  {   0.14118f,   0.04706f,   0.30980f },
  {   0.25882f,   0.03922f,   0.40784f },
  {   0.36471f,   0.07059f,   0.43137f },
  {   0.47059f,   0.10980f,   0.42745f },
  {   0.57647f,   0.14902f,   0.40392f },
  {   0.68235f,   0.18824f,   0.36078f },
  {   0.78039f,   0.24314f,   0.29804f },
  {   0.86667f,   0.31765f,   0.22745f },
  {   0.92941f,   0.41176f,   0.14510f },
  {   0.97255f,   0.52157f,   0.05882f },
  {   0.98824f,   0.64706f,   0.03922f },
  {   0.98039f,   0.77647f,   0.17647f },
  {   0.94902f,   0.90196f,   0.38039f },
  {   0.98824f,   1.00000f,   0.64314f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
