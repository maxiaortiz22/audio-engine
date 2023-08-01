#include "Noise.h"
#include "kiss_fft.h"
#include "kiss_fftr.h"

Noise::Noise(int sampleRate, int buffer) : AudioEngine(sampleRate, buffer), generator(std::random_device()()), distribution(-1.0f, 1.0f) {}

void Noise::genSignal() {

    //main working loop:
    for (int idx = 0; idx < buffer*2; idx += 2) {
        float sample = Noise::genSample();
        Noise::setSampleInBuffer(sample, idx);
    }
}

float Noise::genSample() {

    switch (noiseType) {
        case NoiseType::White:
            return amplitude * distribution(generator);
            break;
        case NoiseType::Pink:
            return amplitude * distribution(generator);
            break;
        case NoiseType::Brown:
            return amplitude * distribution(generator);
            break;
        case NoiseType::NBN:
            return amplitude * distribution(generator);
            break;
        default:
            throw UnknownNoiseTypeException("Unknown type of noise.");
    }

}

void Noise::setNoiseType(NoiseType noiseType, float freq) {
    this->noiseType = noiseType;
    this->freq = freq;
}