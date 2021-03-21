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
static const std::vector<vivid::srgb_t> Magma_12
{
  {   0.00000f,   0.00000f,   0.01569f },
  {   0.07059f,   0.05098f,   0.19216f },
  {   0.20000f,   0.06275f,   0.40392f },
  {   0.35294f,   0.08627f,   0.49412f },
  {   0.49412f,   0.14118f,   0.50980f },
  {   0.63922f,   0.18824f,   0.49412f },
  {   0.78431f,   0.24314f,   0.45098f },
  {   0.91373f,   0.32941f,   0.38431f },
  {   0.97647f,   0.48235f,   0.36471f },
  {   0.99608f,   0.66275f,   0.45098f },
  {   0.99608f,   0.82745f,   0.58431f },
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
