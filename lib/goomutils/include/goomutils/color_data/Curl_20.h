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
static const std::vector<vivid::srgb_t> Curl_20
{
  {   0.08235f,   0.11373f,   0.26667f },
  {   0.10196f,   0.21569f,   0.32549f },
  {   0.10980f,   0.31373f,   0.38431f },
  {   0.08627f,   0.41176f,   0.44314f },
  {   0.07451f,   0.51373f,   0.48235f },
  {   0.21961f,   0.60000f,   0.50588f },
  {   0.42745f,   0.67843f,   0.54118f },
  {   0.61176f,   0.74902f,   0.62353f },
  {   0.77647f,   0.82745f,   0.73725f },
  {   0.92941f,   0.91765f,   0.88235f },
  {   0.96471f,   0.90196f,   0.87451f },
  {   0.91765f,   0.77255f,   0.70196f },
  {   0.88235f,   0.63922f,   0.54510f },
  {   0.84314f,   0.50588f,   0.43529f },
  {   0.78431f,   0.38039f,   0.38431f },
  {   0.70588f,   0.27059f,   0.37647f },
  {   0.60000f,   0.17647f,   0.38039f },
  {   0.47843f,   0.10588f,   0.36863f },
  {   0.34118f,   0.07451f,   0.31373f },
  {   0.20392f,   0.05098f,   0.20784f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
