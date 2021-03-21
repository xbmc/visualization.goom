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
static const std::vector<vivid::srgb_t> LaJolla_20
{
  {   1.00000f,   1.00000f,   0.80000f },
  {   0.99608f,   0.96863f,   0.70980f },
  {   0.98824f,   0.92941f,   0.61176f },
  {   0.97647f,   0.88235f,   0.51765f },
  {   0.96078f,   0.81569f,   0.42353f },
  {   0.94510f,   0.74902f,   0.36471f },
  {   0.92941f,   0.67843f,   0.33725f },
  {   0.91765f,   0.61569f,   0.32549f },
  {   0.90196f,   0.55686f,   0.32157f },
  {   0.88235f,   0.49020f,   0.31373f },
  {   0.85490f,   0.42353f,   0.30588f },
  {   0.79216f,   0.35686f,   0.29412f },
  {   0.70980f,   0.30196f,   0.27451f },
  {   0.61569f,   0.26667f,   0.25098f },
  {   0.51765f,   0.23922f,   0.21569f },
  {   0.43137f,   0.21176f,   0.17647f },
  {   0.33725f,   0.18431f,   0.12941f },
  {   0.25490f,   0.15686f,   0.09020f },
  {   0.16863f,   0.12941f,   0.05098f },
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
