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
static const std::vector<vivid::srgb_t> Lisbon_16
{
  {   0.90196f,   0.89804f,   1.00000f },
  {   0.72157f,   0.76863f,   0.89412f },
  {   0.54510f,   0.63922f,   0.78824f },
  {   0.37647f,   0.51373f,   0.68235f },
  {   0.21961f,   0.38431f,   0.56078f },
  {   0.11765f,   0.26275f,   0.40784f },
  {   0.07451f,   0.16471f,   0.25882f },
  {   0.07059f,   0.10196f,   0.13333f },
  {   0.12157f,   0.11765f,   0.09412f },
  {   0.21961f,   0.20784f,   0.13333f },
  {   0.34118f,   0.31765f,   0.20392f },
  {   0.46667f,   0.43922f,   0.27843f },
  {   0.60392f,   0.56863f,   0.37647f },
  {   0.74118f,   0.71373f,   0.50980f },
  {   0.87059f,   0.85490f,   0.67451f },
  {   1.00000f,   1.00000f,   0.85098f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
