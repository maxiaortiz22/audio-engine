#ifndef NOISE_H
#define NOISE_H

#include "AudioEngine.h"
#include <random>
#include "AudioExceptions.h"

enum class NoiseType {
    White,
    Pink,
    Brown,
    NBN
};

class Noise : public AudioEngine {
private:
    //White noise:
    std::default_random_engine generator;
    std::uniform_real_distribution<float> distribution;
    NoiseType noiseType = NoiseType::White;
    //NBN:
    float freq;

public:
    Noise(int sampleRate, int buffer);

    void genSignal() override;
    float genSample() override;
    void setNoiseType(NoiseType type, float freq = 1000.0);

};

#endif //NOISE_H