#ifndef NOISE_H
#define NOISE_H

#include "AudioEngine.h"
#include <random>
#include "frequency_cut.h"
#include "db.h"
#include "filter.h"
#include "engine_params.h"

class Noise : public AudioEngine{
private:
    //Generator parameters:s
    std::default_random_engine generator;
    std::uniform_real_distribution<float> distribution;
    NoiseType noiseType;
    int freqBand;
    bool noiseTypeBypass;

public:
    Noise(int sampleRate);

    void genSignal(float *data, int buffer) override;
    void genSample() override;
    void filterSignal(float* data, int buffer);
    void setNarrowBandFc();
    void setNoiseByType();
    void setNoiseType(NoiseType noiseType);
    NoiseType getNoiseType();
    void setFreqBand(int freqBand);
    int getFreqBand();

    //REESCRIBIR GETTER Y SETTER DEL GAIN

};

#endif // NOISE_H