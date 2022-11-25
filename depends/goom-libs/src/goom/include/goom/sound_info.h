#pragma once

#include "goom_config.h"

#include <array>
#include <cstddef>
#include <cstdint>
#include <limits>
#include <vector>

namespace GOOM
{

class AudioSamples
{
public:
  static constexpr size_t NUM_AUDIO_SAMPLES = 2;
  static constexpr size_t AUDIO_SAMPLE_LEN  = 512;
  [[nodiscard]] static constexpr auto GetPositiveValue(float audioValue) -> float;

  // AudioSample object: numSampleChannels = 1 or 2.
  //   If numSampleChannels = 1, then the first AUDIO_SAMPLE_LEN values of 'floatAudioData'
  //   are used for the two channels.
  //   If numSampleChannels = 2, then the 'floatAudioData' must interleave the two channels,
  //   one after the other. So 'floatAudioData[0]' is channel 0, 'floatAudioData[1]' is
  //   channel 1, 'floatAudioData[2]' is channel 0, 'floatAudioData[3]' is channel 1, etc.
  AudioSamples(size_t numSampleChannels, const std::vector<float>& floatAudioData);

  [[nodiscard]] auto GetNumDistinctChannels() const -> size_t;

  struct MinMaxValues
  {
    float minVal;
    float maxVal;
  };
  using SampleArray = std::array<float, AUDIO_SAMPLE_LEN>;
  [[nodiscard]] auto GetSample(size_t channelIndex) const -> const SampleArray&;
  [[nodiscard]] auto GetSampleMinMax(size_t channelIndex) const -> const MinMaxValues&;
  [[nodiscard]] auto GetSampleOverallMinMax() const -> const MinMaxValues&;

private:
  const size_t m_numDistinctChannels;
  const std::array<SampleArray, NUM_AUDIO_SAMPLES> m_sampleArrays;
  const std::array<MinMaxValues, NUM_AUDIO_SAMPLES> m_minMaxSampleValues{
      GetMinMaxSampleValues(m_sampleArrays)};
  static_assert(2 == NUM_AUDIO_SAMPLES);
  const MinMaxValues m_overallMinMaxSampleValues{
      std::min(m_minMaxSampleValues[0].minVal, m_minMaxSampleValues[1].minVal),
      std::max(m_minMaxSampleValues[0].maxVal, m_minMaxSampleValues[1].maxVal)};
  [[nodiscard]] static auto GetSampleArrays(const std::vector<float>& floatAudioData)
      -> std::array<SampleArray, NUM_AUDIO_SAMPLES>;
  [[nodiscard]] static auto GetMinMaxSampleValues(
      const std::array<SampleArray, NUM_AUDIO_SAMPLES>& sampleArrays)
      -> std::array<MinMaxValues, NUM_AUDIO_SAMPLES>;
};

class SoundInfo
{
public:
  SoundInfo() noexcept = default;

  void ProcessSample(const AudioSamples& samples);

  // Volume of the sound [0..1]
  [[nodiscard]] auto GetVolume() const -> float;

  // Speed of the sound [0..1]
  [[nodiscard]] auto GetSpeed() const -> float;
  static constexpr auto SPEED_MIDPOINT = 0.5F;

  // Acceleration of the sound [0..1]
  [[nodiscard]] auto GetAcceleration() const -> float;
  static constexpr auto ACCELERATION_MIDPOINT = 0.5F;

  [[nodiscard]] auto GetAllTimesMaxVolume() const -> float;
  [[nodiscard]] auto GetAllTimesMinVolume() const -> float;

private:
  uint32_t m_updateNum = 0;

  float m_volume       = 0.0F;
  float m_acceleration = 0.0F;
  float m_speed        = 0.0F;

  float m_allTimesMaxVolume = std::numeric_limits<float>::min();
  float m_allTimesMinVolume = std::numeric_limits<float>::max();

  void UpdateVolume(const AudioSamples& samples);
  void UpdateSpeed(float prevVolume);
  void UpdateAcceleration(float prevSpeed);
};

constexpr auto AudioSamples::GetPositiveValue(const float audioValue) -> float
{
  constexpr auto MIN_AUDIO_VALUE = -1.0F;
  constexpr auto MAX_AUDIO_VALUE = +1.0F;
  Expects(MIN_AUDIO_VALUE <= audioValue);
  Expects(audioValue <= MAX_AUDIO_VALUE);

  return (1.0F + audioValue) / (MAX_AUDIO_VALUE - MIN_AUDIO_VALUE);
}

inline auto AudioSamples::GetNumDistinctChannels() const -> size_t
{
  return m_numDistinctChannels;
}

inline auto AudioSamples::GetSample(const size_t channelIndex) const -> const SampleArray&
{
  return m_sampleArrays.at(channelIndex);
}

inline auto AudioSamples::GetSampleMinMax(const size_t channelIndex) const -> const MinMaxValues&
{
  return m_minMaxSampleValues.at(channelIndex);
}

inline auto AudioSamples::GetSampleOverallMinMax() const -> const MinMaxValues&
{
  return m_overallMinMaxSampleValues;
}

inline auto SoundInfo::GetVolume() const -> float
{
  return m_volume;
}

inline auto SoundInfo::GetSpeed() const -> float
{
  return m_speed;
}

inline auto SoundInfo::GetAcceleration() const -> float
{
  return m_acceleration;
}

inline auto SoundInfo::GetAllTimesMaxVolume() const -> float
{
  return m_allTimesMaxVolume;
}

inline auto SoundInfo::GetAllTimesMinVolume() const -> float
{
  return m_allTimesMinVolume;
}

} // namespace GOOM
