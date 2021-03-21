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
static const std::vector<vivid::srgb_t> Magma_17
{
  {   0.00000f,   0.00000f,   0.01569f },
  {   0.03922f,   0.03137f,   0.13333f },
  {   0.11373f,   0.06667f,   0.27843f },
  {   0.21176f,   0.06275f,   0.41961f },
  {   0.31765f,   0.07059f,   0.48627f },
  {   0.41569f,   0.10980f,   0.50588f },
  {   0.51373f,   0.14902f,   0.50588f },
  {   0.61176f,   0.18039f,   0.49804f },
  {   0.71765f,   0.21569f,   0.47451f },
  {   0.81176f,   0.25098f,   0.43922f },
  {   0.89804f,   0.31373f,   0.39216f },
  {   0.95686f,   0.41176f,   0.36078f },
  {   0.98431f,   0.52941f,   0.38039f },
  {   0.99608f,   0.64706f,   0.44314f },
  {   0.99608f,   0.76078f,   0.52941f },
  {   0.99216f,   0.87843f,   0.63137f },
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
