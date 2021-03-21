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
static const std::vector<vivid::srgb_t> Broc_16
{
  {   0.17255f,   0.10196f,   0.29804f },
  {   0.16471f,   0.20000f,   0.40000f },
  {   0.16078f,   0.30588f,   0.50196f },
  {   0.24706f,   0.41961f,   0.60000f },
  {   0.39216f,   0.53725f,   0.67843f },
  {   0.54510f,   0.65490f,   0.76078f },
  {   0.70196f,   0.77255f,   0.84314f },
  {   0.86275f,   0.89412f,   0.92157f },
  {   0.92941f,   0.93333f,   0.87451f },
  {   0.86275f,   0.85882f,   0.72157f },
  {   0.77255f,   0.77255f,   0.56078f },
  {   0.63922f,   0.63922f,   0.41176f },
  {   0.50588f,   0.50588f,   0.29804f },
  {   0.38039f,   0.37647f,   0.19216f },
  {   0.25882f,   0.25882f,   0.09412f },
  {   0.14902f,   0.14902f,   0.00000f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
