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
static const std::vector<vivid::srgb_t> Magma_15
{
  {   0.00000f,   0.00000f,   0.01569f },
  {   0.04706f,   0.03529f,   0.14902f },
  {   0.13333f,   0.06667f,   0.31373f },
  {   0.25882f,   0.05882f,   0.45882f },
  {   0.37255f,   0.09412f,   0.49804f },
  {   0.48235f,   0.13725f,   0.50980f },
  {   0.59608f,   0.17647f,   0.50196f },
  {   0.71765f,   0.21569f,   0.47451f },
  {   0.82745f,   0.26275f,   0.43137f },
  {   0.92157f,   0.34118f,   0.37647f },
  {   0.97255f,   0.46275f,   0.36078f },
  {   0.99216f,   0.59608f,   0.41176f },
  {   0.99608f,   0.73333f,   0.50588f },
  {   0.99216f,   0.86275f,   0.61961f },
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
