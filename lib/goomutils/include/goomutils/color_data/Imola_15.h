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
static const std::vector<vivid::srgb_t> Imola_15
{
  {   0.10196f,   0.20000f,   0.70196f },
  {   0.12941f,   0.25098f,   0.67451f },
  {   0.15294f,   0.29804f,   0.65098f },
  {   0.17647f,   0.34510f,   0.62745f },
  {   0.20392f,   0.39216f,   0.60000f },
  {   0.23529f,   0.43137f,   0.56863f },
  {   0.27451f,   0.47451f,   0.52941f },
  {   0.32941f,   0.52549f,   0.49804f },
  {   0.39216f,   0.58824f,   0.47843f },
  {   0.45882f,   0.65882f,   0.46275f },
  {   0.52941f,   0.72941f,   0.44314f },
  {   0.60784f,   0.80392f,   0.42353f },
  {   0.70980f,   0.88627f,   0.40784f },
  {   0.85098f,   0.94902f,   0.40000f },
  {   1.00000f,   1.00000f,   0.40000f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
