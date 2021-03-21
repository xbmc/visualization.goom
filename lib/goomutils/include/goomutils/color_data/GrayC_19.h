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
static const std::vector<vivid::srgb_t> GrayC_19
{
  {   1.00000f,   1.00000f,   1.00000f },
  {   0.93725f,   0.93725f,   0.93725f },
  {   0.87843f,   0.87843f,   0.87843f },
  {   0.81569f,   0.81569f,   0.81569f },
  {   0.75294f,   0.75294f,   0.75294f },
  {   0.69412f,   0.69412f,   0.69412f },
  {   0.63529f,   0.63529f,   0.63529f },
  {   0.58039f,   0.58039f,   0.58039f },
  {   0.52157f,   0.52157f,   0.52157f },
  {   0.46275f,   0.46275f,   0.46275f },
  {   0.41176f,   0.41176f,   0.41176f },
  {   0.35686f,   0.35686f,   0.35686f },
  {   0.30588f,   0.30588f,   0.30588f },
  {   0.25882f,   0.25882f,   0.25882f },
  {   0.20784f,   0.20784f,   0.20784f },
  {   0.16471f,   0.16471f,   0.16471f },
  {   0.11373f,   0.11373f,   0.11373f },
  {   0.07059f,   0.07059f,   0.07059f },
  {   0.00000f,   0.00000f,   0.00000f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
