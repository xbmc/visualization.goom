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
static const std::vector<vivid::srgb_t> Broc_20
{
  {   0.17255f,   0.10196f,   0.29804f },
  {   0.16471f,   0.17647f,   0.37647f },
  {   0.15686f,   0.26275f,   0.45882f },
  {   0.18039f,   0.34510f,   0.53725f },
  {   0.27059f,   0.44314f,   0.61176f },
  {   0.38039f,   0.52941f,   0.67451f },
  {   0.50980f,   0.62745f,   0.74118f },
  {   0.62745f,   0.71765f,   0.80392f },
  {   0.74902f,   0.81176f,   0.86667f },
  {   0.87843f,   0.90588f,   0.92549f },
  {   0.93333f,   0.93725f,   0.89020f },
  {   0.88235f,   0.88235f,   0.76863f },
  {   0.82353f,   0.82353f,   0.64706f },
  {   0.74510f,   0.74510f,   0.52157f },
  {   0.63137f,   0.63137f,   0.40392f },
  {   0.52941f,   0.52941f,   0.31765f },
  {   0.42353f,   0.42353f,   0.22745f },
  {   0.32941f,   0.32941f,   0.14902f },
  {   0.23137f,   0.23137f,   0.07059f },
  {   0.14902f,   0.14902f,   0.00000f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
