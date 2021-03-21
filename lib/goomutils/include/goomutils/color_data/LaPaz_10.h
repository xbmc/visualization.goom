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
static const std::vector<vivid::srgb_t> LaPaz_10
{
  {   0.10196f,   0.04706f,   0.39216f },
  {   0.13725f,   0.17647f,   0.48235f },
  {   0.16471f,   0.29804f,   0.56078f },
  {   0.21176f,   0.40392f,   0.61569f },
  {   0.29804f,   0.50196f,   0.63922f },
  {   0.43137f,   0.58431f,   0.63137f },
  {   0.58039f,   0.63529f,   0.59608f },
  {   0.74902f,   0.69412f,   0.60000f },
  {   0.93725f,   0.82745f,   0.75294f },
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
