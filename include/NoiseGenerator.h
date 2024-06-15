#ifndef NOISEGENERATOR_H
#define NOISEGENERATOR_H

#include "usoundlib_params.h"
#include "engine_params.h"
#include "ulog.h"

#ifdef __cplusplus
extern "C" {
#endif

void noise_generator_alloc(float sampleRate);
void noise_generator_setValue(int param, float value);
void noise_generator_process(float* data, int buffer_size);
float noise_generator_getValue(int param);
void noise_generator_is_instantiated();
void update_noise_generator_params();
int noise_generator_is_bypassed();
void noise_generator_free();

#ifdef __cplusplus
}
#endif


#endif //NOISEGENERATOR_H