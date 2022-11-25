#include "catch2/catch.hpp"
#include "control/goom_sound_events.h"
#include "sound_info.h"
#include "utils/math/misc.h"

#include <memory>

namespace GOOM::UNIT_TESTS
{

using CONTROL::GoomSoundEvents;
using UTILS::MATH::SMALL_FLOAT;

[[nodiscard]] static auto GetAudioData(const float xMin0,
                                       const float xMax0,
                                       const float xMin1,
                                       const float xMax1) -> std::vector<float>
{
  std::vector<float> audioData(AudioSamples::NUM_AUDIO_SAMPLES * AudioSamples::AUDIO_SAMPLE_LEN);

  float x = xMin0;
  float xStep = (xMax0 - xMin0) / static_cast<float>(AudioSamples::AUDIO_SAMPLE_LEN - 1);
  for (size_t i = 0; i < audioData.size(); i += 2)
  {
    audioData.at(i) = x;
    x += xStep;
  }

  x = xMin1;
  xStep = (xMax1 - xMin1) / static_cast<float>(AudioSamples::AUDIO_SAMPLE_LEN - 1);
  for (size_t i = 1; i < audioData.size(); i += 2)
  {
    audioData.at(i) = x;
    x += xStep;
  }

  return audioData;
}


//static constexpr size_t NUM_SAMPLE_CHANNELS = AudioSamples::NUM_AUDIO_SAMPLES;
const size_t NUM_SAMPLE_CHANNELS = AudioSamples::NUM_AUDIO_SAMPLES;
static constexpr float X_MIN0 = -0.9F;
static constexpr float X_MAX0 = +0.1F;
static constexpr float X_MIN1 = +0.2F;
static constexpr float X_MAX1 = +0.9F;

static constexpr auto EXPECTED_X_MIN0 = X_MIN0;
static constexpr auto EXPECTED_X_MAX0 = X_MAX0;
static constexpr auto EXPECTED_X_MIN1 = X_MIN1;
static constexpr auto EXPECTED_X_MAX1 = X_MAX1;

TEST_CASE("Test AudioSamples MinMax")
{
  const std::vector<float> audioData = GetAudioData(X_MIN0, X_MAX0, X_MIN1, X_MAX1);
  const AudioSamples audioSamples{NUM_SAMPLE_CHANNELS, audioData};

  REQUIRE(AudioSamples::NUM_AUDIO_SAMPLES == 2);
  REQUIRE(AudioSamples::AUDIO_SAMPLE_LEN == 512);
  REQUIRE(audioSamples.GetNumDistinctChannels() == NUM_SAMPLE_CHANNELS);

  REQUIRE(audioSamples.GetSampleMinMax(0).minVal ==
          Approx(AudioSamples::GetPositiveValue(EXPECTED_X_MIN0)));
  REQUIRE(audioSamples.GetSampleMinMax(0).maxVal ==
          Approx(AudioSamples::GetPositiveValue(EXPECTED_X_MAX0)));

  REQUIRE(audioSamples.GetSampleMinMax(1).minVal ==
          Approx(AudioSamples::GetPositiveValue(EXPECTED_X_MIN1)));
  REQUIRE(audioSamples.GetSampleMinMax(1).maxVal ==
          Approx(AudioSamples::GetPositiveValue(EXPECTED_X_MAX1)));
}

TEST_CASE("Test AudioSamples Arrays")
{
  const std::vector<float> audioData = GetAudioData(X_MIN0, X_MAX0, X_MIN1, X_MAX1);
  const AudioSamples audioSamples{NUM_SAMPLE_CHANNELS, audioData};

  REQUIRE(audioData.at(0) == Approx(X_MIN0));

  REQUIRE(audioSamples.GetSample(0).at(0) ==
          Approx(AudioSamples::GetPositiveValue(EXPECTED_X_MIN0)));

  REQUIRE(audioData.at(audioData.size() - 2) == Approx(X_MAX0).margin(SMALL_FLOAT));

  REQUIRE(audioSamples.GetSample(0).at(AudioSamples::AUDIO_SAMPLE_LEN - 1) ==
          Approx(AudioSamples::GetPositiveValue(EXPECTED_X_MAX0)));

  REQUIRE(audioData.at(1) == Approx(X_MIN1));

  REQUIRE(audioSamples.GetSample(1).at(0) ==
          Approx(AudioSamples::GetPositiveValue(EXPECTED_X_MIN1)));

  REQUIRE(audioData.at(audioData.size() - 1) == Approx(X_MAX1));

  REQUIRE(audioSamples.GetSample(1).at(AudioSamples::AUDIO_SAMPLE_LEN - 1) ==
          Approx(AudioSamples::GetPositiveValue(EXPECTED_X_MAX1)));
}

TEST_CASE("Test SoundInfo ProcessSample Defaults")
{
  SoundInfo soundInfo{};
  GoomSoundEvents goomSoundEvents{soundInfo};

  REQUIRE(soundInfo.GetVolume() == Approx(0.0F));
  REQUIRE(goomSoundEvents.GetTimeSinceLastGoom() == 0);
  REQUIRE(goomSoundEvents.GetTimeSinceLastBigGoom() == 0);
  REQUIRE(goomSoundEvents.GetTotalGoomsInCurrentCycle() == 0);

  const std::vector<float> audioData = GetAudioData(X_MIN0, X_MAX0, X_MIN1, X_MAX1);
  const AudioSamples audioSamples{NUM_SAMPLE_CHANNELS, audioData};

  soundInfo.ProcessSample(audioSamples);
  goomSoundEvents.Update();

  REQUIRE(soundInfo.GetVolume() == Approx(AudioSamples::GetPositiveValue(X_MAX1)));
  REQUIRE(goomSoundEvents.GetTimeSinceLastGoom() == 1);
  REQUIRE(goomSoundEvents.GetTimeSinceLastBigGoom() == 1);
  REQUIRE(goomSoundEvents.GetTotalGoomsInCurrentCycle() == 0);
}

TEST_CASE("Test SoundInfo Volume")
{
  SoundInfo soundInfo{};

  std::vector<float> audioData = GetAudioData(X_MIN0, X_MAX0, X_MIN1, X_MAX1);
  auto audioSamples = std::make_unique<AudioSamples>(NUM_SAMPLE_CHANNELS, audioData);

  // First update - defaults
  static constexpr float ALL_TIMES_MAX = AudioSamples::GetPositiveValue(EXPECTED_X_MAX1);
  static constexpr float ALL_TIMES_MIN = AudioSamples::GetPositiveValue(EXPECTED_X_MIN0);
  soundInfo.ProcessSample(*audioSamples);
  REQUIRE(soundInfo.GetVolume() == Approx(ALL_TIMES_MAX));
  REQUIRE(soundInfo.GetAllTimesMaxVolume() == Approx(ALL_TIMES_MAX));
  REQUIRE(soundInfo.GetAllTimesMinVolume() == Approx(ALL_TIMES_MIN));

  // Second update - flat line, new volume
  static constexpr float FLAT_VOL = 0.1F;
  static constexpr float EXPECTED_NEW_VOLUME = AudioSamples::GetPositiveValue(FLAT_VOL);

  std::fill(begin(audioData), end(audioData), FLAT_VOL);
  audioSamples = std::make_unique<AudioSamples>(NUM_SAMPLE_CHANNELS, audioData);
  soundInfo.ProcessSample(*audioSamples);
  REQUIRE(soundInfo.GetVolume() == Approx(EXPECTED_NEW_VOLUME));
  REQUIRE(soundInfo.GetAllTimesMaxVolume() == Approx(ALL_TIMES_MAX));
  REQUIRE(soundInfo.GetAllTimesMinVolume() == Approx(ALL_TIMES_MIN));

  // Third update - new max volume
  static constexpr float NEW_MAX_VOL = X_MAX1 + 0.02F;
  audioData.at(10) = NEW_MAX_VOL;
  audioSamples = std::make_unique<AudioSamples>(NUM_SAMPLE_CHANNELS, audioData);
  soundInfo.ProcessSample(*audioSamples);
  REQUIRE(soundInfo.GetVolume() == Approx(AudioSamples::GetPositiveValue(NEW_MAX_VOL)));
  REQUIRE(soundInfo.GetAllTimesMaxVolume() == Approx(AudioSamples::GetPositiveValue(NEW_MAX_VOL)));
  REQUIRE(soundInfo.GetAllTimesMinVolume() == Approx(ALL_TIMES_MIN));

  // Fourth update - negative sound values
  static constexpr float NEGATIVE_VOL = -0.2F;
  std::fill(begin(audioData), end(audioData), NEGATIVE_VOL);
  audioSamples = std::make_unique<AudioSamples>(NUM_SAMPLE_CHANNELS, audioData);
  soundInfo.ProcessSample(*audioSamples);
  REQUIRE(soundInfo.GetVolume() == Approx(AudioSamples::GetPositiveValue(NEGATIVE_VOL)));
  REQUIRE(soundInfo.GetAllTimesMaxVolume() == Approx(AudioSamples::GetPositiveValue(NEW_MAX_VOL)));
  REQUIRE(soundInfo.GetAllTimesMinVolume() == Approx(ALL_TIMES_MIN));
}

} // namespace GOOM::UNIT_TESTS
