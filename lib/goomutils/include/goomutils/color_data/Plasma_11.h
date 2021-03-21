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
static const std::vector<vivid::srgb_t> Plasma_11
{
  {   0.05098f,   0.03137f,   0.52941f },
  {   0.26275f,   0.01176f,   0.61961f },
  {   0.41569f,   0.00000f,   0.65882f },
  {   0.56078f,   0.05098f,   0.64314f },
  {   0.69412f,   0.16471f,   0.56471f },
  {   0.80000f,   0.27843f,   0.47059f },
  {   0.88235f,   0.39216f,   0.38431f },
  {   0.94510f,   0.51373f,   0.29804f },
  {   0.98824f,   0.65098f,   0.21176f },
  {   0.98824f,   0.80784f,   0.14510f },
  {   0.94118f,   0.97647f,   0.12941f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
