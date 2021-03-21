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
static const std::vector<vivid::srgb_t> Magma_18
{
  {   0.00000f,   0.00000f,   0.01569f },
  {   0.03529f,   0.02745f,   0.12549f },
  {   0.10196f,   0.06275f,   0.25882f },
  {   0.19216f,   0.06667f,   0.39608f },
  {   0.29020f,   0.06275f,   0.47451f },
  {   0.38431f,   0.09804f,   0.50196f },
  {   0.47451f,   0.13333f,   0.50980f },
  {   0.56863f,   0.16863f,   0.50588f },
  {   0.66667f,   0.20000f,   0.49020f },
  {   0.76078f,   0.23137f,   0.45882f },
  {   0.85098f,   0.27451f,   0.41961f },
  {   0.92549f,   0.34510f,   0.37647f },
  {   0.96863f,   0.44706f,   0.36078f },
  {   0.98824f,   0.55686f,   0.39216f },
  {   0.99608f,   0.66667f,   0.45490f },
  {   0.99608f,   0.77647f,   0.54118f },
  {   0.99216f,   0.88627f,   0.63922f },
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
