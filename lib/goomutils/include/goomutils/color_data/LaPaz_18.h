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
static const std::vector<vivid::srgb_t> LaPaz_18
{
  {   0.10196f,   0.04706f,   0.39216f },
  {   0.12157f,   0.12157f,   0.44314f },
  {   0.13725f,   0.18824f,   0.48627f },
  {   0.15294f,   0.24706f,   0.52941f },
  {   0.16863f,   0.30980f,   0.56863f },
  {   0.19216f,   0.36863f,   0.60000f },
  {   0.22353f,   0.42353f,   0.61961f },
  {   0.26667f,   0.47843f,   0.63529f },
  {   0.32549f,   0.52549f,   0.64314f },
  {   0.39608f,   0.56863f,   0.63529f },
  {   0.47059f,   0.60392f,   0.62353f },
  {   0.55294f,   0.62745f,   0.60000f },
  {   0.63529f,   0.65098f,   0.58824f },
  {   0.72941f,   0.68627f,   0.59216f },
  {   0.83529f,   0.74118f,   0.64314f },
  {   0.92549f,   0.81569f,   0.74118f },
  {   0.97647f,   0.88627f,   0.84706f },
  {   0.99608f,   0.94902f,   0.95294f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
