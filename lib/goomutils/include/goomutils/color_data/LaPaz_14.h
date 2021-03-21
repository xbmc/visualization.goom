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
static const std::vector<vivid::srgb_t> LaPaz_14
{
  {   0.10196f,   0.04706f,   0.39216f },
  {   0.12941f,   0.14510f,   0.45882f },
  {   0.14510f,   0.22353f,   0.51373f },
  {   0.16863f,   0.30588f,   0.56471f },
  {   0.19608f,   0.37647f,   0.60392f },
  {   0.24314f,   0.45098f,   0.63137f },
  {   0.31765f,   0.52157f,   0.64314f },
  {   0.40392f,   0.57255f,   0.63529f },
  {   0.50980f,   0.61569f,   0.61176f },
  {   0.61961f,   0.64706f,   0.58824f },
  {   0.73725f,   0.69020f,   0.59608f },
  {   0.87451f,   0.77255f,   0.67843f },
  {   0.96471f,   0.86667f,   0.81176f },
  {   0.99608f,   0.94902f,   0.95294f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
