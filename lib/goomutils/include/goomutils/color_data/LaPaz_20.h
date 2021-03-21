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
static const std::vector<vivid::srgb_t> LaPaz_20
{
  {   0.10196f,   0.04706f,   0.39216f },
  {   0.12157f,   0.11373f,   0.43529f },
  {   0.13333f,   0.17255f,   0.47843f },
  {   0.14902f,   0.22745f,   0.51765f },
  {   0.16078f,   0.28627f,   0.55294f },
  {   0.18039f,   0.33725f,   0.58431f },
  {   0.20392f,   0.38824f,   0.60784f },
  {   0.23529f,   0.43922f,   0.62745f },
  {   0.27451f,   0.48235f,   0.63922f },
  {   0.32941f,   0.52941f,   0.64314f },
  {   0.38824f,   0.56471f,   0.63529f },
  {   0.46275f,   0.60000f,   0.62353f },
  {   0.52941f,   0.62353f,   0.60784f },
  {   0.60000f,   0.64314f,   0.59216f },
  {   0.68235f,   0.66667f,   0.58431f },
  {   0.77255f,   0.70588f,   0.60784f },
  {   0.87059f,   0.76471f,   0.67059f },
  {   0.94118f,   0.83137f,   0.76078f },
  {   0.98039f,   0.89804f,   0.86275f },
  {   0.99608f,   0.94902f,   0.95294f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
