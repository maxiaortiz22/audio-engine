#include "Noise.h"

Noise::Noise(int sampleRate, int buffer) : AudioEngine(sampleRate, buffer), generator(std::random_device()()), distribution(-1.0f, 1.0f) {
    //Pink noise initialization:
    std::random_device rd;
    gRandom.seed(rd());
    for (int i = 0; i < kMaxKey; ++i) {
        gValues[i] = ((gRandom() % kNumWhiteValues) / float(kNumWhiteValues)) - 0.5;
    }
}

void Noise::genSignal() {

    //main working loop:
    for (int idx = 0; idx < buffer*2; idx += 2) {
        float sample = Noise::genSample();
        Noise::setSampleInBuffer(sample, idx);
    }
}

float Noise::genSample() {

    if (noiseType == "White Noise"){
        return amplitude * distribution(generator);

    } else if (noiseType == "NBN") { 
        return amplitude * distribution(generator); //IMPLEMENT FILTERS!!!

    } else if (noiseType == "Pink Noise") {

        int last_key = gRandom() & kMaxKey;
        gRange += ((gRandom() % kNumWhiteValues) / float(kNumWhiteValues)) - 0.5;
        if (gRange < 0) {
            gRange = -gRange;
            gValues[last_key] = -gValues[last_key];
        }
        if (gRange >= 1) {
            gRange = 2 - gRange;
            gValues[last_key] = -gValues[last_key];
        }
        return gValues[last_key] * 2;

    }
}

void Noise::setNoiseType(std::string noiseType, float freq) {
    this->noiseType = noiseType;
    this->freq = freq;
}