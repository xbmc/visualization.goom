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
static const std::vector<vivid::srgb_t> Matter_20
{
  {   0.99608f,   0.92941f,   0.69020f },
  {   0.98824f,   0.85882f,   0.62353f },
  {   0.98039f,   0.78431f,   0.55294f },
  {   0.97255f,   0.71373f,   0.49412f },
  {   0.96078f,   0.63922f,   0.43922f },
  {   0.94510f,   0.56863f,   0.39216f },
  {   0.92549f,   0.49412f,   0.35294f },
  {   0.90588f,   0.42353f,   0.33333f },
  {   0.87451f,   0.35686f,   0.32549f },
  {   0.83529f,   0.29412f,   0.32941f },
  {   0.78431f,   0.23922f,   0.34510f },
  {   0.72549f,   0.19608f,   0.36471f },
  {   0.66667f,   0.16078f,   0.38039f },
  {   0.60392f,   0.13333f,   0.38824f },
  {   0.53333f,   0.11373f,   0.38824f },
  {   0.46275f,   0.10196f,   0.38039f },
  {   0.38824f,   0.09412f,   0.35686f },
  {   0.32157f,   0.08627f,   0.32549f },
  {   0.25098f,   0.07451f,   0.28627f },
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
