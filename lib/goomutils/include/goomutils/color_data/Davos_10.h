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
static const std::vector<vivid::srgb_t> Davos_10
{
  {   0.00000f,   0.01961f,   0.29020f },
  {   0.06667f,   0.17255f,   0.44314f },
  {   0.16078f,   0.32157f,   0.56863f },
  {   0.26275f,   0.43922f,   0.61569f },
  {   0.36863f,   0.52157f,   0.59608f },
  {   0.47451f,   0.58824f,   0.55294f },
  {   0.60000f,   0.67843f,   0.53333f },
  {   0.78824f,   0.82353f,   0.61961f },
  {   0.95294f,   0.95294f,   0.82353f },
  {   0.99608f,   0.99608f,   0.99608f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
