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
static const std::vector<vivid::srgb_t> purple_16
{
  {   0.00000f,   0.00000f,   0.00000f },
  {   0.05882f,   0.05490f,   0.13725f },
  {   0.12157f,   0.10980f,   0.26667f },
  {   0.18431f,   0.16863f,   0.38824f },
  {   0.24706f,   0.23137f,   0.49804f },
  {   0.30980f,   0.29412f,   0.59608f },
  {   0.37647f,   0.35686f,   0.68235f },
  {   0.44314f,   0.41961f,   0.76078f },
  {   0.50980f,   0.48627f,   0.82745f },
  {   0.57647f,   0.55686f,   0.88235f },
  {   0.64314f,   0.62745f,   0.92941f },
  {   0.71373f,   0.69804f,   0.96471f },
  {   0.78431f,   0.76863f,   0.98824f },
  {   0.85490f,   0.84314f,   1.00000f },
  {   0.92549f,   0.92157f,   1.00000f },
  {   1.00000f,   1.00000f,   1.00000f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
