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
static const std::vector<vivid::srgb_t> Magma_11
{
  {   0.00000f,   0.00000f,   0.01569f },
  {   0.08235f,   0.05490f,   0.21961f },
  {   0.23137f,   0.05882f,   0.43922f },
  {   0.39216f,   0.10196f,   0.50196f },
  {   0.54902f,   0.16078f,   0.50588f },
  {   0.71765f,   0.21569f,   0.47451f },
  {   0.87059f,   0.28627f,   0.40784f },
  {   0.96471f,   0.43137f,   0.36078f },
  {   0.99608f,   0.62353f,   0.42745f },
  {   0.99608f,   0.81176f,   0.57255f },
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
