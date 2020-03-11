#ifndef AUDIO_DATA_HPP
#define AUDIO_DATA_HPP

#include <stdint.h>
extern "C" {
  #include "goom.h"
  #include "goom_config.h"
}


static inline int16_t FloatToInt16(float f)
{
  if (f >= 1.0f)
    return INT16_MAX;
  else if (f < -1.0f)
    return -INT16_MAX;
  else
    return static_cast<int16_t>((f * static_cast<float>(INT16_MAX)));
}

static inline void FillAudioDataBuffer(int16_t audioData[NUM_AUDIO_SAMPLES][AUDIO_SAMPLE_LEN], 
  const float floatAudioData[NUM_AUDIO_SAMPLES*AUDIO_SAMPLE_LEN], int numChannels)
{
  if (numChannels == 1) 
  {
    for (int i=0; i < AUDIO_SAMPLE_LEN; i++) 
    {
      audioData[0][i] = FloatToInt16(floatAudioData[i]);
      audioData[1][i] = audioData[0][i];
    }
  } else 
  {
    int fpos = 0;
    for (int i=0; i < AUDIO_SAMPLE_LEN; i++) 
    {
      audioData[0][i] = FloatToInt16(floatAudioData[fpos]);
      fpos++;
      audioData[1][i] = FloatToInt16(floatAudioData[fpos]);
      fpos++;
    }
  }
}
  
#endif
