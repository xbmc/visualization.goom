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
static const std::vector<vivid::srgb_t> Hawaii_14
{
  {   0.54902f,   0.00784f,   0.45098f },
  {   0.56471f,   0.12941f,   0.37647f },
  {   0.57647f,   0.20784f,   0.31373f },
  {   0.58824f,   0.28627f,   0.25490f },
  {   0.59608f,   0.36078f,   0.20392f },
  {   0.60784f,   0.44314f,   0.15294f },
  {   0.61569f,   0.53725f,   0.10980f },
  {   0.60000f,   0.63922f,   0.13725f },
  {   0.54902f,   0.72941f,   0.26667f },
  {   0.47451f,   0.79216f,   0.43137f },
  {   0.40784f,   0.84314f,   0.59216f },
  {   0.37647f,   0.89412f,   0.76863f },
  {   0.49020f,   0.93333f,   0.90980f },
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
