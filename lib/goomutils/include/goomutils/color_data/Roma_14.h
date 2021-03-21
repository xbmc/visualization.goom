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
static const std::vector<vivid::srgb_t> Roma_14
{
  {   0.49804f,   0.09804f,   0.00000f },
  {   0.58431f,   0.28627f,   0.06667f },
  {   0.65882f,   0.43529f,   0.12941f },
  {   0.73333f,   0.59216f,   0.20784f },
  {   0.81961f,   0.75686f,   0.34902f },
  {   0.88627f,   0.88235f,   0.56471f },
  {   0.85490f,   0.92157f,   0.73333f },
  {   0.71373f,   0.90980f,   0.82353f },
  {   0.49804f,   0.82745f,   0.84314f },
  {   0.34118f,   0.69412f,   0.80784f },
  {   0.26667f,   0.56471f,   0.75686f },
  {   0.21176f,   0.43529f,   0.70196f },
  {   0.16471f,   0.31765f,   0.65098f },
  {   0.10196f,   0.20000f,   0.60000f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
