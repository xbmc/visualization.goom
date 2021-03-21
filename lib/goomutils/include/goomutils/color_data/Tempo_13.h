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
static const std::vector<vivid::srgb_t> Tempo_13
{
  {   1.00000f,   0.96471f,   0.95686f },
  {   0.88627f,   0.88627f,   0.83922f },
  {   0.76471f,   0.81961f,   0.72941f },
  {   0.63137f,   0.75686f,   0.63137f },
  {   0.49020f,   0.70196f,   0.56471f },
  {   0.33725f,   0.64314f,   0.52157f },
  {   0.16471f,   0.57647f,   0.49804f },
  {   0.07059f,   0.50588f,   0.48235f },
  {   0.08235f,   0.42745f,   0.45098f },
  {   0.10588f,   0.34902f,   0.40784f },
  {   0.10980f,   0.27451f,   0.36078f },
  {   0.09804f,   0.19608f,   0.30980f },
  {   0.08235f,   0.11373f,   0.26667f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
