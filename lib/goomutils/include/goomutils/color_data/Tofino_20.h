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
static const std::vector<vivid::srgb_t> Tofino_20
{
  {   0.87059f,   0.85098f,   1.00000f },
  {   0.73333f,   0.75294f,   0.94118f },
  {   0.58824f,   0.65098f,   0.87451f },
  {   0.45098f,   0.55294f,   0.80784f },
  {   0.31765f,   0.44314f,   0.70588f },
  {   0.22745f,   0.34902f,   0.57647f },
  {   0.16863f,   0.25882f,   0.43529f },
  {   0.12157f,   0.18824f,   0.30980f },
  {   0.08235f,   0.12157f,   0.19608f },
  {   0.05490f,   0.08235f,   0.10196f },
  {   0.05490f,   0.10196f,   0.06667f },
  {   0.08235f,   0.16471f,   0.09020f },
  {   0.11373f,   0.24314f,   0.12549f },
  {   0.15294f,   0.32941f,   0.17255f },
  {   0.20392f,   0.42745f,   0.22353f },
  {   0.26667f,   0.52941f,   0.27843f },
  {   0.39216f,   0.64314f,   0.36078f },
  {   0.54510f,   0.73333f,   0.44314f },
  {   0.70980f,   0.81961f,   0.52941f },
  {   0.85882f,   0.90196f,   0.60784f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
