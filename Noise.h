#ifndef NOISE_H
#define NOISE_H

#include "AudioEngine.h"
#include <random>
#include <string>

class Noise : public AudioEngine {
private:
    std::default_random_engine generator;
    std::uniform_real_distribution<float> distribution;
    std::string noiseType;
    float freq;

public:
    Noise(int sampleRate, int buffer);

    void genSignal() override;
    float genSample() override;
    void setNoiseType(std::string noiseType, float freq = 0.0);

};

#endif //NOISE_H