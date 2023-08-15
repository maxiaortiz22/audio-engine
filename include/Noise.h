#ifndef NOISE_H
#define NOISE_H

#include "AudioEngine.h"
#include <random>
#include "AudioExceptions.h"
#include "ButterworthFilter.h"
#include <vector>
#include <tuple>

enum class NoiseType {
    White,
    Pink,
    NBN
};

class Noise : public AudioEngine {
private:
    //White noise:
    std::default_random_engine generator;
    std::uniform_real_distribution<float> distribution;
    NoiseType noiseType = NoiseType::White;
    //Pink noise:
    std::vector<float> auxBuffer;
    std::vector<float> filteredSignal;
    std::tuple<std::vector<double>, std::vector<double>> coeff;
    std::vector<double> b; //b filter coefficients
    std::vector<double> a; //a filter coefficients
    bool analog = false; //Set a digital filter
    std::vector<double> fc; //Cut-off frequency
    int N; //Order of the filter
    FilterType btype; //Type of filter
    //NBN:
    float freq;
    double lowcut;
    double highcut;

public:
    Noise(int sampleRate, int buffer);

    void genSignal() override;
    float genSample() override;
    void setNoiseType(NoiseType type, float freq = 1000.0);
    void filterSignal(std::vector<float> signal);

};

#endif //NOISE_H