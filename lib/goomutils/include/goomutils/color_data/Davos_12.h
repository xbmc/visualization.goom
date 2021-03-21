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
static const std::vector<vivid::srgb_t> Davos_12
{
  {   0.00000f,   0.01961f,   0.29020f },
  {   0.05490f,   0.14902f,   0.41961f },
  {   0.12157f,   0.26667f,   0.52941f },
  {   0.20784f,   0.38039f,   0.60000f },
  {   0.29412f,   0.46275f,   0.61569f },
  {   0.38039f,   0.52549f,   0.59216f },
  {   0.46275f,   0.58431f,   0.55686f },
  {   0.56078f,   0.64706f,   0.53333f },
  {   0.69020f,   0.74902f,   0.55686f },
  {   0.86667f,   0.88627f,   0.69412f },
  {   0.96471f,   0.96471f,   0.85882f },
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
