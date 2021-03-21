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
static const std::vector<vivid::srgb_t> Tempo_20
{
  {   1.00000f,   0.96471f,   0.95686f },
  {   0.92941f,   0.91765f,   0.88235f },
  {   0.85098f,   0.86667f,   0.80392f },
  {   0.77647f,   0.82745f,   0.73725f },
  {   0.69412f,   0.78431f,   0.67451f },
  {   0.61176f,   0.74902f,   0.62353f },
  {   0.52157f,   0.70980f,   0.57647f },
  {   0.42745f,   0.67843f,   0.54118f },
  {   0.32941f,   0.64314f,   0.51765f },
  {   0.21961f,   0.60000f,   0.50588f },
  {   0.12941f,   0.55686f,   0.49412f },
  {   0.07059f,   0.50980f,   0.48235f },
  {   0.07059f,   0.46275f,   0.46275f },
  {   0.08627f,   0.41176f,   0.44314f },
  {   0.10196f,   0.36078f,   0.41569f },
  {   0.10980f,   0.31373f,   0.38431f },
  {   0.10980f,   0.26275f,   0.35294f },
  {   0.10196f,   0.21569f,   0.32549f },
  {   0.09412f,   0.16471f,   0.29412f },
  {   0.08235f,   0.11373f,   0.26667f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
