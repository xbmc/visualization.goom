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
static const std::vector<vivid::srgb_t> Batlow_20
{
  {   0.00392f,   0.09804f,   0.34902f },
  {   0.03137f,   0.15294f,   0.36078f },
  {   0.05490f,   0.20784f,   0.36863f },
  {   0.07451f,   0.26275f,   0.37647f },
  {   0.10196f,   0.32157f,   0.38039f },
  {   0.14902f,   0.37255f,   0.37255f },
  {   0.21961f,   0.41569f,   0.34510f },
  {   0.29412f,   0.44706f,   0.30588f },
  {   0.37255f,   0.47059f,   0.26275f },
  {   0.45882f,   0.49412f,   0.21961f },
  {   0.54510f,   0.52157f,   0.18431f },
  {   0.65882f,   0.54510f,   0.18431f },
  {   0.76471f,   0.56863f,   0.23137f },
  {   0.86275f,   0.58824f,   0.30980f },
  {   0.94510f,   0.61569f,   0.41961f },
  {   0.98039f,   0.64706f,   0.52941f },
  {   0.99216f,   0.68627f,   0.64314f },
  {   0.99216f,   0.72157f,   0.74902f },
  {   0.98824f,   0.76078f,   0.86667f },
  {   0.98039f,   0.80000f,   0.98039f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
