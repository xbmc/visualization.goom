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
static const std::vector<vivid::srgb_t> Ice_20
{
  {   0.01569f,   0.02353f,   0.07451f },
  {   0.06275f,   0.06667f,   0.14510f },
  {   0.11373f,   0.10980f,   0.22745f },
  {   0.15686f,   0.14902f,   0.30588f },
  {   0.19608f,   0.19216f,   0.39216f },
  {   0.22745f,   0.23137f,   0.47843f },
  {   0.24314f,   0.28235f,   0.56471f },
  {   0.24706f,   0.33333f,   0.63137f },
  {   0.24314f,   0.38824f,   0.67843f },
  {   0.25098f,   0.45098f,   0.70588f },
  {   0.27059f,   0.50588f,   0.72941f },
  {   0.30588f,   0.56471f,   0.74902f },
  {   0.34902f,   0.61961f,   0.76863f },
  {   0.39608f,   0.67451f,   0.78824f },
  {   0.45882f,   0.73333f,   0.81176f },
  {   0.53333f,   0.78431f,   0.83137f },
  {   0.62745f,   0.83922f,   0.86275f },
  {   0.72549f,   0.88627f,   0.89804f },
  {   0.82745f,   0.93725f,   0.94510f },
  {   0.91765f,   0.99216f,   0.99216f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
