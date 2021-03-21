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
static const std::vector<vivid::srgb_t> LaJolla_16
{
  {   1.00000f,   1.00000f,   0.80000f },
  {   0.99216f,   0.95686f,   0.68235f },
  {   0.98039f,   0.90588f,   0.56078f },
  {   0.96471f,   0.83137f,   0.43922f },
  {   0.94510f,   0.74118f,   0.36078f },
  {   0.92549f,   0.65882f,   0.33333f },
  {   0.90588f,   0.58039f,   0.32157f },
  {   0.88627f,   0.50196f,   0.31373f },
  {   0.84706f,   0.41569f,   0.30588f },
  {   0.76078f,   0.33333f,   0.29020f },
  {   0.64706f,   0.27843f,   0.25882f },
  {   0.52549f,   0.24314f,   0.21569f },
  {   0.40784f,   0.20784f,   0.16471f },
  {   0.29804f,   0.16863f,   0.11373f },
  {   0.19216f,   0.13725f,   0.06667f },
  {   0.10196f,   0.10196f,   0.00392f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
