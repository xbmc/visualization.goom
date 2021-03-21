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
static const std::vector<vivid::srgb_t> Magma_8
{
  {   0.00000f,   0.00000f,   0.01569f },
  {   0.13333f,   0.06667f,   0.31373f },
  {   0.37255f,   0.09412f,   0.49804f },
  {   0.59608f,   0.17647f,   0.50196f },
  {   0.82745f,   0.26275f,   0.43137f },
  {   0.97255f,   0.46275f,   0.36078f },
  {   0.99608f,   0.73333f,   0.50588f },
  {   0.98824f,   0.99216f,   0.74902f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
