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
static const std::vector<vivid::srgb_t> Oleron_14
{
  {   0.10196f,   0.14902f,   0.34902f },
  {   0.22353f,   0.27059f,   0.47059f },
  {   0.34510f,   0.39216f,   0.59216f },
  {   0.47843f,   0.52941f,   0.72941f },
  {   0.61569f,   0.66667f,   0.86275f },
  {   0.74902f,   0.79608f,   0.95686f },
  {   0.85490f,   0.90196f,   0.98824f },
  {   0.19216f,   0.32549f,   0.00000f },
  {   0.36078f,   0.38039f,   0.02353f },
  {   0.54118f,   0.48235f,   0.18039f },
  {   0.70196f,   0.59216f,   0.34902f },
  {   0.87843f,   0.72941f,   0.53725f },
  {   0.96471f,   0.86275f,   0.71765f },
  {   0.99216f,   0.99216f,   0.90196f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
