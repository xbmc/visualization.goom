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
static const std::vector<vivid::srgb_t> Viridis_13
{
  {   0.26667f,   0.00392f,   0.32941f },
  {   0.28235f,   0.12157f,   0.43922f },
  {   0.26667f,   0.22353f,   0.51373f },
  {   0.23137f,   0.32157f,   0.54510f },
  {   0.19216f,   0.40784f,   0.55686f },
  {   0.15686f,   0.48627f,   0.55686f },
  {   0.12941f,   0.56863f,   0.54902f },
  {   0.12549f,   0.64314f,   0.52549f },
  {   0.20784f,   0.71765f,   0.47451f },
  {   0.36078f,   0.78431f,   0.38824f },
  {   0.55686f,   0.83922f,   0.27059f },
  {   0.78431f,   0.87843f,   0.12549f },
  {   0.99216f,   0.90588f,   0.14510f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
