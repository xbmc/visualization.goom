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
static const std::vector<vivid::srgb_t> Davos_16
{
  {   0.00000f,   0.01961f,   0.29020f },
  {   0.03529f,   0.11765f,   0.38431f },
  {   0.08627f,   0.20392f,   0.47451f },
  {   0.13725f,   0.29020f,   0.54902f },
  {   0.20000f,   0.37255f,   0.59608f },
  {   0.26275f,   0.43922f,   0.61569f },
  {   0.32941f,   0.49020f,   0.61176f },
  {   0.39216f,   0.53333f,   0.58824f },
  {   0.45490f,   0.57647f,   0.56078f },
  {   0.51765f,   0.61961f,   0.53725f },
  {   0.60000f,   0.67843f,   0.53333f },
  {   0.70588f,   0.75686f,   0.56471f },
  {   0.83137f,   0.85882f,   0.65882f },
  {   0.92941f,   0.93725f,   0.78039f },
  {   0.97647f,   0.97647f,   0.89804f },
  {   0.99608f,   0.99608f,   0.99608f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
