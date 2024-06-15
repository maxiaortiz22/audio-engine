#ifndef TONEGENERATOR_H
#define TONEGENERATOR_H

#include "usoundlib_params.h"
#include "engine_params.h"
#include "ulog.h"

#ifdef __cplusplus
extern "C" {
#endif

UsoundResult tone_generator_alloc(float sampleRate);
UsoundResult second_tone_generator_alloc(float sampleRate);
UsoundResult tone_generator_setValue(int param, float value);
UsoundResult second_tone_generator_setValue(int param, float value);
void tone_generator_is_instantiated();
void second_tone_generator_is_instantiated();
void update_tone_generator_params();
void update_second_tone_generator_params();
int tone_generator_is_bypassed();
int second_tone_generator_is_bypassed();
void tone_generator_interval_process(float* data, int buffer_size);
void second_tone_generator_interval_process(float* data, int buffer_size);
void tone_generator_free();
void second_tone_generator_free();
float tone_generator_getValue(int param);
float second_tone_generator_getValue(int param);

#ifdef __cplusplus
}
#endif


#endif //TONEGENERATOR_H
