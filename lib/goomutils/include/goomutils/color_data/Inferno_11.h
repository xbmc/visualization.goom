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
static const std::vector<vivid::srgb_t> Inferno_11
{
  {   0.00000f,   0.00000f,   0.01569f },
  {   0.09412f,   0.04706f,   0.23529f },
  {   0.25882f,   0.03922f,   0.40784f },
  {   0.41569f,   0.09020f,   0.43137f },
  {   0.57647f,   0.14902f,   0.40392f },
  {   0.73725f,   0.21569f,   0.32941f },
  {   0.86667f,   0.31765f,   0.22745f },
  {   0.95294f,   0.46275f,   0.10588f },
  {   0.98824f,   0.64706f,   0.03922f },
  {   0.96471f,   0.84314f,   0.27451f },
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
