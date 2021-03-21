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
static const std::vector<vivid::srgb_t> Inferno_14
{
  {   0.00000f,   0.00000f,   0.01569f },
  {   0.06275f,   0.03529f,   0.17647f },
  {   0.17647f,   0.04314f,   0.34902f },
  {   0.30980f,   0.05098f,   0.42353f },
  {   0.42745f,   0.09412f,   0.43137f },
  {   0.55294f,   0.13725f,   0.41176f },
  {   0.67843f,   0.18824f,   0.36471f },
  {   0.78431f,   0.24706f,   0.29412f },
  {   0.88235f,   0.33725f,   0.20784f },
  {   0.94902f,   0.45490f,   0.10980f },
  {   0.98431f,   0.58824f,   0.02353f },
  {   0.98431f,   0.73725f,   0.12941f },
  {   0.95686f,   0.88235f,   0.33725f },
  {   0.98824f,   1.00000f,   0.64314f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
