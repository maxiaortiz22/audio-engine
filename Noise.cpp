#include "Noise.h"

Noise::Noise(int sampleRate, int buffer) : AudioEngine(sampleRate, buffer), generator(std::random_device()()), distribution(-1.0f, 1.0f) {}

void Noise::genSignal() {

    //main working loop:
    for (int idx = 0; idx < buffer*2; idx += 2) {
        float sample = distribution(generator);
        Noise::setSampleInBuffer(sample, idx);
    }
}

float Noise::genSample() {
    if (noiseType == "White Noise"){
        return amplitude * distribution(generator);
    } else if (noiseType == "NBN") { 
        return amplitude * distribution(generator); //IMPLEMENT FILTERS!!!
    } else if (noiseType == "Pink Noise") { 
        return amplitude * distribution(generator); //IMPLEMENT FILTERS!!!
    }
}

void Noise::setNoiseType(std::string noiseType, float freq = 0.0) {
    this->noiseType = noiseType;
    this->freq = freq;
}