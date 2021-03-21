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
static const std::vector<vivid::srgb_t> Imola_20
{
  {   0.10196f,   0.20000f,   0.70196f },
  {   0.12157f,   0.23529f,   0.68235f },
  {   0.14118f,   0.27451f,   0.66275f },
  {   0.15686f,   0.30588f,   0.64706f },
  {   0.17647f,   0.34118f,   0.62745f },
  {   0.19216f,   0.37647f,   0.61176f },
  {   0.21569f,   0.40784f,   0.58824f },
  {   0.24314f,   0.43922f,   0.56078f },
  {   0.27059f,   0.46667f,   0.53333f },
  {   0.30588f,   0.50588f,   0.50588f },
  {   0.34902f,   0.54510f,   0.49020f },
  {   0.40000f,   0.59608f,   0.47843f },
  {   0.44706f,   0.64706f,   0.46275f },
  {   0.49804f,   0.69804f,   0.45098f },
  {   0.55294f,   0.75294f,   0.43922f },
  {   0.61176f,   0.80784f,   0.42353f },
  {   0.68627f,   0.87059f,   0.41176f },
  {   0.77647f,   0.92157f,   0.40392f },
  {   0.89412f,   0.96471f,   0.40000f },
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
