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
static const std::vector<vivid::srgb_t> GrayC_13
{
  {   1.00000f,   1.00000f,   1.00000f },
  {   0.90588f,   0.90588f,   0.90588f },
  {   0.81569f,   0.81569f,   0.81569f },
  {   0.72157f,   0.72157f,   0.72157f },
  {   0.63529f,   0.63529f,   0.63529f },
  {   0.54902f,   0.54902f,   0.54902f },
  {   0.46275f,   0.46275f,   0.46275f },
  {   0.38431f,   0.38431f,   0.38431f },
  {   0.30588f,   0.30588f,   0.30588f },
  {   0.23529f,   0.23529f,   0.23529f },
  {   0.16471f,   0.16471f,   0.16471f },
  {   0.09412f,   0.09412f,   0.09412f },
  {   0.00000f,   0.00000f,   0.00000f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
