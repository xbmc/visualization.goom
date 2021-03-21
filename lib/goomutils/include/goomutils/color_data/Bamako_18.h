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
static const std::vector<vivid::srgb_t> Bamako_18
{
  {   0.00000f,   0.25098f,   0.29804f },
  {   0.04314f,   0.27451f,   0.27843f },
  {   0.07843f,   0.29804f,   0.25490f },
  {   0.11765f,   0.32157f,   0.23529f },
  {   0.15686f,   0.34902f,   0.20784f },
  {   0.20000f,   0.37647f,   0.18431f },
  {   0.24314f,   0.40392f,   0.15686f },
  {   0.29412f,   0.43529f,   0.12941f },
  {   0.34902f,   0.47059f,   0.09804f },
  {   0.41176f,   0.50980f,   0.06275f },
  {   0.48627f,   0.54510f,   0.02353f },
  {   0.56078f,   0.56471f,   0.01176f },
  {   0.65098f,   0.60000f,   0.07451f },
  {   0.75294f,   0.66667f,   0.17255f },
  {   0.83529f,   0.73725f,   0.28627f },
  {   0.89804f,   0.79608f,   0.39608f },
  {   0.94902f,   0.84706f,   0.49804f },
  {   1.00000f,   0.89804f,   0.60000f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
