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
static const std::vector<vivid::srgb_t> Magma_13
{
  {   0.00000f,   0.00000f,   0.01569f },
  {   0.06275f,   0.04314f,   0.17647f },
  {   0.17255f,   0.06667f,   0.37255f },
  {   0.31765f,   0.07059f,   0.48627f },
  {   0.44706f,   0.12157f,   0.50588f },
  {   0.57647f,   0.16863f,   0.50196f },
  {   0.71765f,   0.21569f,   0.47451f },
  {   0.84706f,   0.27059f,   0.42353f },
  {   0.94510f,   0.37647f,   0.36471f },
  {   0.98431f,   0.52941f,   0.38039f },
  {   0.99608f,   0.68235f,   0.46667f },
  {   0.99608f,   0.84314f,   0.60000f },
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
