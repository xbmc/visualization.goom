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
static const std::vector<vivid::srgb_t> Magma_16
{
  {   0.00000f,   0.00000f,   0.01569f },
  {   0.04314f,   0.03529f,   0.14118f },
  {   0.12549f,   0.06667f,   0.29412f },
  {   0.23137f,   0.05882f,   0.43922f },
  {   0.34118f,   0.08235f,   0.49412f },
  {   0.44706f,   0.12157f,   0.50588f },
  {   0.54902f,   0.16078f,   0.50588f },
  {   0.65882f,   0.19608f,   0.49020f },
  {   0.76863f,   0.23529f,   0.45882f },
  {   0.87059f,   0.28627f,   0.40784f },
  {   0.94510f,   0.37647f,   0.36471f },
  {   0.98039f,   0.49804f,   0.36863f },
  {   0.99608f,   0.62353f,   0.42745f },
  {   0.99608f,   0.74902f,   0.51765f },
  {   0.99216f,   0.87059f,   0.62745f },
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
