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
static const std::vector<vivid::srgb_t> Inferno_15
{
  {   0.00000f,   0.00000f,   0.01569f },
  {   0.05098f,   0.03137f,   0.16078f },
  {   0.15686f,   0.04314f,   0.32549f },
  {   0.28627f,   0.04314f,   0.41569f },
  {   0.39608f,   0.08235f,   0.43137f },
  {   0.50980f,   0.12549f,   0.42353f },
  {   0.62353f,   0.16471f,   0.38824f },
  {   0.73725f,   0.21569f,   0.32941f },
  {   0.83137f,   0.28235f,   0.25882f },
  {   0.90980f,   0.37647f,   0.17647f },
  {   0.96078f,   0.49020f,   0.08235f },
  {   0.98431f,   0.61569f,   0.02745f },
  {   0.98039f,   0.76078f,   0.15686f },
  {   0.95294f,   0.89804f,   0.36471f },
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
