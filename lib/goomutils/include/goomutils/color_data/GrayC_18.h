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
static const std::vector<vivid::srgb_t> GrayC_18
{
  {   1.00000f,   1.00000f,   1.00000f },
  {   0.93333f,   0.93333f,   0.93333f },
  {   0.86667f,   0.86667f,   0.86667f },
  {   0.80392f,   0.80392f,   0.80392f },
  {   0.74118f,   0.74118f,   0.74118f },
  {   0.67843f,   0.67843f,   0.67843f },
  {   0.61569f,   0.61569f,   0.61569f },
  {   0.55294f,   0.55294f,   0.55294f },
  {   0.49412f,   0.49412f,   0.49412f },
  {   0.43922f,   0.43922f,   0.43922f },
  {   0.38039f,   0.38039f,   0.38039f },
  {   0.32549f,   0.32549f,   0.32549f },
  {   0.27059f,   0.27059f,   0.27059f },
  {   0.21961f,   0.21961f,   0.21961f },
  {   0.16863f,   0.16863f,   0.16863f },
  {   0.12157f,   0.12157f,   0.12157f },
  {   0.07451f,   0.07451f,   0.07451f },
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
