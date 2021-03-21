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
static const std::vector<vivid::srgb_t> Tempo_18
{
  {   1.00000f,   0.96471f,   0.95686f },
  {   0.91765f,   0.90980f,   0.87059f },
  {   0.83529f,   0.85882f,   0.78824f },
  {   0.74902f,   0.81176f,   0.71373f },
  {   0.65882f,   0.76863f,   0.64706f },
  {   0.56078f,   0.72941f,   0.59216f },
  {   0.45490f,   0.68627f,   0.55294f },
  {   0.34118f,   0.64706f,   0.52157f },
  {   0.22745f,   0.60392f,   0.50588f },
  {   0.12157f,   0.55294f,   0.49412f },
  {   0.06667f,   0.50196f,   0.47843f },
  {   0.07451f,   0.44706f,   0.45882f },
  {   0.09412f,   0.39216f,   0.43137f },
  {   0.10588f,   0.33725f,   0.40000f },
  {   0.10980f,   0.28235f,   0.36471f },
  {   0.10588f,   0.22745f,   0.32941f },
  {   0.09412f,   0.17255f,   0.29804f },
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
