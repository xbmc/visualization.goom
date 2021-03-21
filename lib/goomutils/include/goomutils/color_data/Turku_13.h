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
static const std::vector<vivid::srgb_t> Turku_13
{
  {   0.00000f,   0.00000f,   0.00000f },
  {   0.11373f,   0.11373f,   0.10196f },
  {   0.20000f,   0.19608f,   0.16863f },
  {   0.28627f,   0.28627f,   0.22745f },
  {   0.37255f,   0.37255f,   0.26667f },
  {   0.46275f,   0.45490f,   0.30588f },
  {   0.57647f,   0.54902f,   0.35686f },
  {   0.70196f,   0.61961f,   0.41961f },
  {   0.81176f,   0.65098f,   0.48627f },
  {   0.89412f,   0.66667f,   0.56078f },
  {   0.96078f,   0.72157f,   0.67843f },
  {   0.99608f,   0.81176f,   0.80000f },
  {   1.00000f,   0.90196f,   0.90196f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
