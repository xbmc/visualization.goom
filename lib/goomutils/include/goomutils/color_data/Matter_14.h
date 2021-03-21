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
static const std::vector<vivid::srgb_t> Matter_14
{
  {   0.99608f,   0.92941f,   0.69020f },
  {   0.98431f,   0.81961f,   0.58824f },
  {   0.97255f,   0.71765f,   0.49804f },
  {   0.95294f,   0.61176f,   0.41961f },
  {   0.92941f,   0.50980f,   0.36078f },
  {   0.89804f,   0.40392f,   0.32941f },
  {   0.84314f,   0.30588f,   0.32941f },
  {   0.77255f,   0.23137f,   0.34902f },
  {   0.68627f,   0.16863f,   0.37647f },
  {   0.58824f,   0.12941f,   0.38824f },
  {   0.49020f,   0.10588f,   0.38431f },
  {   0.38431f,   0.09412f,   0.35686f },
  {   0.28627f,   0.08235f,   0.30588f },
  {   0.18431f,   0.05882f,   0.24314f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
