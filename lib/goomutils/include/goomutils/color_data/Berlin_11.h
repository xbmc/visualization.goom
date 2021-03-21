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
static const std::vector<vivid::srgb_t> Berlin_11
{
  {   0.61961f,   0.69020f,   1.00000f },
  {   0.37647f,   0.64706f,   0.87451f },
  {   0.19608f,   0.50196f,   0.65098f },
  {   0.12549f,   0.32157f,   0.41569f },
  {   0.06667f,   0.15294f,   0.19608f },
  {   0.09804f,   0.04706f,   0.03529f },
  {   0.21569f,   0.06275f,   0.00000f },
  {   0.37255f,   0.12157f,   0.03922f },
  {   0.58824f,   0.29020f,   0.21176f },
  {   0.79216f,   0.48235f,   0.44314f },
  {   1.00000f,   0.67843f,   0.67843f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
