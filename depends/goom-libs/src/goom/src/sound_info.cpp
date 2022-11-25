#include "sound_info.h"

#include "goom_config.h"

#include <algorithm>
#include <array>
#include <cstddef>
#include <vector>

namespace GOOM
{

AudioSamples::AudioSamples(const size_t numSampleChannels, const std::vector<float>& floatAudioData)
  : m_numDistinctChannels{numSampleChannels}, m_sampleArrays{GetSampleArrays(floatAudioData)}
{
  Expects((0 < numSampleChannels) && (numSampleChannels <= 2));
}

auto AudioSamples::GetSampleArrays(const std::vector<float>& floatAudioData)
    -> std::array<SampleArray, NUM_AUDIO_SAMPLES>
{
  Expects((NUM_AUDIO_SAMPLES * AUDIO_SAMPLE_LEN) == floatAudioData.size());

  auto sampleArrays = std::array<SampleArray, NUM_AUDIO_SAMPLES>{};

  auto fpos = 0U;
  for (size_t j = 0; j < AUDIO_SAMPLE_LEN; ++j)
  {
    for (auto i = 0U; i < NUM_AUDIO_SAMPLES; ++i)
    {
      sampleArrays.at(i).at(j) = GetPositiveValue(floatAudioData[fpos]);
      ++fpos;
    }
  }

  return sampleArrays;
}

auto AudioSamples::GetMinMaxSampleValues(
    const std::array<SampleArray, NUM_AUDIO_SAMPLES>& sampleArrays)
    -> std::array<MinMaxValues, NUM_AUDIO_SAMPLES>
{
  auto minMaxSampleValues = std::array<MinMaxValues, NUM_AUDIO_SAMPLES>{};

  for (auto i = 0U; i < NUM_AUDIO_SAMPLES; ++i)
  {
    const auto& sampleArray         = sampleArrays.at(i);
    const auto& [minVal, maxVal]    = std::minmax_element(cbegin(sampleArray), cend(sampleArray));
    minMaxSampleValues.at(i).minVal = *minVal;
    minMaxSampleValues.at(i).maxVal = *maxVal;
  }

  return minMaxSampleValues;
}

void SoundInfo::ProcessSample(const AudioSamples& samples)
{
  ++m_updateNum;

  const auto prevVolume = m_volume;
  UpdateVolume(samples);

  const auto prevSpeed = m_speed;
  UpdateSpeed(prevVolume);
  UpdateAcceleration(prevSpeed);
}

inline void SoundInfo::UpdateVolume(const AudioSamples& samples)
{
  m_volume = samples.GetSampleOverallMinMax().maxVal;

  if (m_volume > m_allTimesMaxVolume)
  {
    m_allTimesMaxVolume = m_volume;
  }
  if (samples.GetSampleOverallMinMax().minVal < m_allTimesMinVolume)
  {
    m_allTimesMinVolume = samples.GetSampleOverallMinMax().minVal;
  }

  Ensures(0.0F <= m_volume && m_volume <= 1.0F);
}

inline void SoundInfo::UpdateSpeed(const float prevVolume)
{
  m_speed = AudioSamples::GetPositiveValue(m_volume - prevVolume);
  Ensures(0.0F <= m_speed && m_speed <= 1.0F);
}

inline void SoundInfo::UpdateAcceleration(const float prevSpeed)
{
  m_acceleration = AudioSamples::GetPositiveValue(m_speed - prevSpeed);
  Ensures(0.0F <= m_acceleration && m_acceleration <= 1.0F);
}

} // namespace GOOM
