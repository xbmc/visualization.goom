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
static const std::vector<vivid::srgb_t> Inferno_9
{
  {   0.00000f,   0.00000f,   0.01569f },
  {   0.12941f,   0.04706f,   0.29020f },
  {   0.34118f,   0.06275f,   0.43137f },
  {   0.54118f,   0.13333f,   0.41569f },
  {   0.73725f,   0.21569f,   0.32941f },
  {   0.89020f,   0.34902f,   0.20000f },
  {   0.97647f,   0.54902f,   0.03922f },
  {   0.97647f,   0.78824f,   0.19608f },
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
