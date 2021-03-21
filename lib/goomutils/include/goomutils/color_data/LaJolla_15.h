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
static const std::vector<vivid::srgb_t> LaJolla_15
{
  {   1.00000f,   1.00000f,   0.80000f },
  {   0.99216f,   0.95294f,   0.67451f },
  {   0.98039f,   0.89804f,   0.54510f },
  {   0.96078f,   0.81176f,   0.41569f },
  {   0.93725f,   0.71765f,   0.34902f },
  {   0.91765f,   0.63137f,   0.32549f },
  {   0.90196f,   0.54902f,   0.31765f },
  {   0.87059f,   0.45490f,   0.30980f },
  {   0.80392f,   0.36471f,   0.29804f },
  {   0.68627f,   0.29412f,   0.27059f },
  {   0.56078f,   0.25098f,   0.23137f },
  {   0.43529f,   0.21569f,   0.17647f },
  {   0.30980f,   0.17255f,   0.11765f },
  {   0.20000f,   0.13725f,   0.06667f },
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
