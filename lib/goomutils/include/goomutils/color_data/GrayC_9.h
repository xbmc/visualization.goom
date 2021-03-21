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
static const std::vector<vivid::srgb_t> GrayC_9
{
  {   1.00000f,   1.00000f,   1.00000f },
  {   0.85882f,   0.85882f,   0.85882f },
  {   0.72157f,   0.72157f,   0.72157f },
  {   0.59216f,   0.59216f,   0.59216f },
  {   0.46275f,   0.46275f,   0.46275f },
  {   0.34902f,   0.34902f,   0.34902f },
  {   0.23529f,   0.23529f,   0.23529f },
  {   0.12941f,   0.12941f,   0.12941f },
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
