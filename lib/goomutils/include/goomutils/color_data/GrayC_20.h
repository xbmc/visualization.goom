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
static const std::vector<vivid::srgb_t> GrayC_20
{
  {   1.00000f,   1.00000f,   1.00000f },
  {   0.94118f,   0.94118f,   0.94118f },
  {   0.88235f,   0.88235f,   0.88235f },
  {   0.82353f,   0.82353f,   0.82353f },
  {   0.76471f,   0.76471f,   0.76471f },
  {   0.70980f,   0.70980f,   0.70980f },
  {   0.65098f,   0.65098f,   0.65098f },
  {   0.60000f,   0.60000f,   0.60000f },
  {   0.54510f,   0.54510f,   0.54510f },
  {   0.49020f,   0.49020f,   0.49020f },
  {   0.44314f,   0.44314f,   0.44314f },
  {   0.38824f,   0.38824f,   0.38824f },
  {   0.34118f,   0.34118f,   0.34118f },
  {   0.29412f,   0.29412f,   0.29412f },
  {   0.24314f,   0.24314f,   0.24314f },
  {   0.20000f,   0.20000f,   0.20000f },
  {   0.15294f,   0.15294f,   0.15294f },
  {   0.11373f,   0.11373f,   0.11373f },
  {   0.06667f,   0.06667f,   0.06667f },
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
