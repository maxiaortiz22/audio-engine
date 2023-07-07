#define _USE_MATH_DEFINES
#include "PureTone.h"
#include <cmath>

PureTone::PureTone(int sampleRate, int buffer) : AudioEngine(sampleRate, buffer) {
    offset = 2 * M_PI * this->freq / (float) sampleRate;
}

void PureTone::genSignal() {

    // Substract 2PI to avoid large angles.
    if (angle> 2.0 * M_PI) {
        angle -= 2.0 * M_PI;
    }

    //main working loop:
    for (int idx = 0; idx < buffer*2; idx += 2) {
        float sample = PureTone::genSample();
        PureTone::setSampleInBuffer(sample, idx);
    }
}

float PureTone::genSample() {
    float sample = amplitude * sin(angle);
    angle += offset;
}


void PureTone::setFreq(float freq) {
    //Set freq and reset other parameters
    this->freq = freq;
    offset = 2 * M_PI * freq / (float) sampleRate;
    angle = 0.0;
}
