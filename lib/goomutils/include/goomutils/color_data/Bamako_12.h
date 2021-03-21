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
static const std::vector<vivid::srgb_t> Bamako_12
{
  {   0.00000f,   0.25098f,   0.29804f },
  {   0.06275f,   0.28627f,   0.26667f },
  {   0.11765f,   0.32157f,   0.23137f },
  {   0.18431f,   0.36471f,   0.19216f },
  {   0.25490f,   0.41176f,   0.15294f },
  {   0.33333f,   0.46275f,   0.10588f },
  {   0.43137f,   0.52157f,   0.05098f },
  {   0.54510f,   0.56078f,   0.01176f },
  {   0.68627f,   0.61961f,   0.10588f },
  {   0.83137f,   0.73333f,   0.27843f },
  {   0.92157f,   0.81961f,   0.44314f },
  {   1.00000f,   0.89804f,   0.60000f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
