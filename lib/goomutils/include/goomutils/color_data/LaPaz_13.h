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
static const std::vector<vivid::srgb_t> LaPaz_13
{
  {   0.10196f,   0.04706f,   0.39216f },
  {   0.12941f,   0.14902f,   0.45882f },
  {   0.14902f,   0.23529f,   0.52157f },
  {   0.17647f,   0.32549f,   0.57647f },
  {   0.21176f,   0.40392f,   0.61569f },
  {   0.27059f,   0.47843f,   0.63529f },
  {   0.36078f,   0.54902f,   0.63922f },
  {   0.46667f,   0.60000f,   0.62353f },
  {   0.58039f,   0.63529f,   0.59608f },
  {   0.70196f,   0.67451f,   0.58824f },
  {   0.85098f,   0.75294f,   0.65490f },
  {   0.96078f,   0.85882f,   0.80392f },
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
