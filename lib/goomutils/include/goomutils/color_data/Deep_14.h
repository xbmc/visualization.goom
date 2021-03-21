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
static const std::vector<vivid::srgb_t> Deep_14
{
  {   0.99216f,   0.99608f,   0.80000f },
  {   0.83137f,   0.93725f,   0.71373f },
  {   0.67451f,   0.88235f,   0.65882f },
  {   0.50588f,   0.82353f,   0.63922f },
  {   0.39216f,   0.75686f,   0.64314f },
  {   0.32941f,   0.67451f,   0.63922f },
  {   0.29412f,   0.59608f,   0.62745f },
  {   0.27059f,   0.52157f,   0.61176f },
  {   0.25098f,   0.44314f,   0.59216f },
  {   0.24314f,   0.36078f,   0.57647f },
  {   0.25490f,   0.28235f,   0.52941f },
  {   0.24314f,   0.21569f,   0.40392f },
  {   0.20784f,   0.16078f,   0.28627f },
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
