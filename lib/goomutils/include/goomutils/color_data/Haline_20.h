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
static const std::vector<vivid::srgb_t> Haline_20
{
  {   0.16471f,   0.09412f,   0.42353f },
  {   0.18039f,   0.10980f,   0.54902f },
  {   0.14902f,   0.16863f,   0.63922f },
  {   0.08627f,   0.25098f,   0.61569f },
  {   0.04706f,   0.31765f,   0.58431f },
  {   0.06667f,   0.36863f,   0.56078f },
  {   0.11373f,   0.41961f,   0.54510f },
  {   0.15294f,   0.46275f,   0.54118f },
  {   0.18824f,   0.50588f,   0.53725f },
  {   0.21961f,   0.55294f,   0.53333f },
  {   0.24706f,   0.60000f,   0.52549f },
  {   0.27843f,   0.64706f,   0.51373f },
  {   0.31765f,   0.69412f,   0.49020f },
  {   0.36863f,   0.74118f,   0.45882f },
  {   0.45098f,   0.78431f,   0.41569f },
  {   0.55294f,   0.82353f,   0.37255f },
  {   0.68627f,   0.85098f,   0.36471f },
  {   0.80000f,   0.87451f,   0.41569f },
  {   0.90588f,   0.90588f,   0.50588f },
  {   0.99216f,   0.93725f,   0.60392f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
