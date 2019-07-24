#ifndef _SOUND_TESTER_H
#define _SOUND_TESTER_H

#include "goom.h"
#include "goom_plugin_info.h"
#include "goom_config.h"

/** change les donnees du SoundInfo */
void evaluate_sound(const gint16 data[NUM_AUDIO_SAMPLES][AUDIO_SAMPLE_LEN], SoundInfo *sndInfo);

#endif

