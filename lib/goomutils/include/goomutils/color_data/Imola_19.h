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
static const std::vector<vivid::srgb_t> Imola_19
{
  {   0.10196f,   0.20000f,   0.70196f },
  {   0.12157f,   0.23922f,   0.68235f },
  {   0.14118f,   0.27451f,   0.66275f },
  {   0.16078f,   0.31373f,   0.64314f },
  {   0.18039f,   0.34902f,   0.62353f },
  {   0.20000f,   0.38431f,   0.60392f },
  {   0.22353f,   0.41961f,   0.58039f },
  {   0.25490f,   0.45098f,   0.54902f },
  {   0.28627f,   0.48235f,   0.52157f },
  {   0.32941f,   0.52549f,   0.49804f },
  {   0.37647f,   0.57255f,   0.48235f },
  {   0.42745f,   0.62745f,   0.47059f },
  {   0.48235f,   0.68235f,   0.45490f },
  {   0.53725f,   0.73725f,   0.44314f },
  {   0.59608f,   0.79608f,   0.42745f },
  {   0.66667f,   0.85490f,   0.41176f },
  {   0.76863f,   0.91765f,   0.40392f },
  {   0.88627f,   0.96078f,   0.40000f },
  {   1.00000f,   1.00000f,   0.40000f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
