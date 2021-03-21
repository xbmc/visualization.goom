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
static const std::vector<vivid::srgb_t> Berlin_14
{
  {   0.61961f,   0.69020f,   1.00000f },
  {   0.43529f,   0.66275f,   0.90980f },
  {   0.26275f,   0.58431f,   0.76471f },
  {   0.17255f,   0.44314f,   0.57255f },
  {   0.11765f,   0.30588f,   0.39608f },
  {   0.07451f,   0.17647f,   0.22745f },
  {   0.06667f,   0.07451f,   0.09020f },
  {   0.13725f,   0.04706f,   0.00784f },
  {   0.23529f,   0.06667f,   0.00392f },
  {   0.36471f,   0.11765f,   0.03529f },
  {   0.52549f,   0.23137f,   0.14902f },
  {   0.68235f,   0.37647f,   0.31765f },
  {   0.83529f,   0.52157f,   0.49020f },
  {   1.00000f,   0.67843f,   0.67843f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
