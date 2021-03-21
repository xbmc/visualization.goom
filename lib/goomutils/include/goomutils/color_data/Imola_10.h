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
static const std::vector<vivid::srgb_t> Imola_10
{
  {   0.10196f,   0.20000f,   0.70196f },
  {   0.14118f,   0.27451f,   0.66275f },
  {   0.18039f,   0.34902f,   0.62353f },
  {   0.22353f,   0.41961f,   0.58039f },
  {   0.28627f,   0.48235f,   0.52157f },
  {   0.37647f,   0.57255f,   0.48235f },
  {   0.48235f,   0.68235f,   0.45490f },
  {   0.59608f,   0.79608f,   0.42745f },
  {   0.76863f,   0.91765f,   0.40392f },
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
