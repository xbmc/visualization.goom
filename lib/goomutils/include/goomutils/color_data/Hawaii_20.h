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
static const std::vector<vivid::srgb_t> Hawaii_20
{
  {   0.54902f,   0.00784f,   0.45098f },
  {   0.56078f,   0.09804f,   0.40000f },
  {   0.57255f,   0.16078f,   0.35294f },
  {   0.57647f,   0.21176f,   0.30980f },
  {   0.58431f,   0.26667f,   0.27059f },
  {   0.59216f,   0.31765f,   0.23529f },
  {   0.60000f,   0.37255f,   0.19608f },
  {   0.60784f,   0.42353f,   0.16471f },
  {   0.61176f,   0.48235f,   0.12941f },
  {   0.61569f,   0.55294f,   0.10980f },
  {   0.60392f,   0.62353f,   0.12549f },
  {   0.57647f,   0.69020f,   0.20000f },
  {   0.53333f,   0.74510f,   0.29804f },
  {   0.48627f,   0.78431f,   0.40392f },
  {   0.43529f,   0.82353f,   0.52549f },
  {   0.39216f,   0.85490f,   0.63529f },
  {   0.37255f,   0.89412f,   0.76078f },
  {   0.42745f,   0.92157f,   0.86275f },
  {   0.56078f,   0.94118f,   0.94510f },
  {   0.70196f,   0.94902f,   0.99216f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
