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
static const std::vector<vivid::srgb_t> Deep_16
{
  {   0.99216f,   0.99608f,   0.80000f },
  {   0.85882f,   0.94510f,   0.72549f },
  {   0.71765f,   0.89804f,   0.67059f },
  {   0.57255f,   0.84706f,   0.64314f },
  {   0.44314f,   0.79216f,   0.63922f },
  {   0.36471f,   0.72941f,   0.64314f },
  {   0.32157f,   0.65882f,   0.63922f },
  {   0.29412f,   0.59216f,   0.62745f },
  {   0.27059f,   0.52549f,   0.61176f },
  {   0.25098f,   0.45882f,   0.59608f },
  {   0.24314f,   0.39216f,   0.58431f },
  {   0.24706f,   0.32157f,   0.56078f },
  {   0.25490f,   0.25098f,   0.48235f },
  {   0.23529f,   0.20000f,   0.37255f },
  {   0.20000f,   0.15294f,   0.26667f },
  {   0.15686f,   0.10196f,   0.17255f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
