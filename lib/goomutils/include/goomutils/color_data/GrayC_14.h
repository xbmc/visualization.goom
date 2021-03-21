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
static const std::vector<vivid::srgb_t> GrayC_14
{
  {   1.00000f,   1.00000f,   1.00000f },
  {   0.90980f,   0.90980f,   0.90980f },
  {   0.82745f,   0.82745f,   0.82745f },
  {   0.74510f,   0.74510f,   0.74510f },
  {   0.66275f,   0.66275f,   0.66275f },
  {   0.58431f,   0.58431f,   0.58431f },
  {   0.50196f,   0.50196f,   0.50196f },
  {   0.43137f,   0.43137f,   0.43137f },
  {   0.35294f,   0.35294f,   0.35294f },
  {   0.28235f,   0.28235f,   0.28235f },
  {   0.21569f,   0.21569f,   0.21569f },
  {   0.14902f,   0.14902f,   0.14902f },
  {   0.09020f,   0.09020f,   0.09020f },
  {   0.00000f,   0.00000f,   0.00000f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
