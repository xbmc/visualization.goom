#pragma once

#include "utils/math/goom_rand_base.h"

namespace GOOM::FILTER_FX
{

template<typename T>
struct Amplitude_t
{
  T x;
  T y;
};
using Amplitude    = Amplitude_t<float>;
using IntAmplitude = Amplitude_t<int32_t>;
struct FrequencyFactor
{
  float x;
  float y;
};
struct SqDistMult
{
  float x;
  float y;
};
struct SqDistOffset
{
  float x;
  float y;
};

struct AmplitudeRange
{
  UTILS::MATH::IGoomRand::NumberRange<float> xRange;
  UTILS::MATH::IGoomRand::NumberRange<float> yRange;
};
struct FrequencyFactorRange
{
  UTILS::MATH::IGoomRand::NumberRange<float> xRange;
  UTILS::MATH::IGoomRand::NumberRange<float> yRange;
};
struct SqDistMultRange
{
  UTILS::MATH::IGoomRand::NumberRange<float> xRange;
  UTILS::MATH::IGoomRand::NumberRange<float> yRange;
};
struct SqDistOffsetRange
{
  UTILS::MATH::IGoomRand::NumberRange<float> xRange;
  UTILS::MATH::IGoomRand::NumberRange<float> yRange;
};

} // namespace GOOM::FILTER_FX
