#ifndef NOISE_H
#define NOISE_H

#include "AudioEngine.h"
#include <random>
#include <array>
#include <string>

class Noise : public AudioEngine {
private:
    //White noise:
    std::default_random_engine generator;
    std::uniform_real_distribution<float> distribution;
    std::string noiseType = "White Noise";
    //Pink noise (Voss-McCartney algorithm):
    static constexpr int kMaxKey = 0x1f; // Five bits set
    static constexpr int kNumWhiteValues = 5;
    std::array<float, kMaxKey> gValues;
    float gRange = 0.5;
    std::mt19937 gRandom;
    //NBN:
    float freq;

public:
    Noise(int sampleRate, int buffer);

    void genSignal() override;
    float genSample() override;
    void setNoiseType(std::string noiseType, float freq = 1000.0); // noiseType: "White Noise", "NBN" or "Pink Noise"

};

#endif //NOISE_H