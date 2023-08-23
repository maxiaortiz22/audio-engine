#define _USE_MATH_DEFINES
#include "PureTone.h"
#include <cmath>

PureTone::PureTone(int sampleRate, int buffer) : AudioEngine(sampleRate, buffer) {
    offset = 2 * M_PI * this->freq / (float) sampleRate;
}

void PureTone::genSignal() {

    if (gainChanged){
        PureTone::getGainIncrement();
    }
    gainChanged = false;

    if (actualGain <= -130) {

        for (int idx = 0; idx < buffer*2; idx += 2) {
            sample = 0.0;
            PureTone::setSampleInBuffer(sample, idx);
        }

        angle = 0.0;
        actualGain = -120;
        enableBypass = false;
        bypass = true;
    }
    else {

         //main working loop:
        for (int idx = 0; idx < buffer*2; idx += 2) {
            PureTone::genSample();
            PureTone::setSampleInBuffer(sample, idx);
        }

    }
}

void PureTone::genSample() {

    sample = sin(angle);
    angle += offset;

    PureTone::applyGain();

    // Substract 2PI to avoid large angles.
    if (angle> 2.0 * M_PI) {
        angle -= 2.0 * M_PI;
    }
}

void PureTone::setFreq(float freq) {
    this->freq = freq;
    offset = 2 * M_PI * freq / (float) sampleRate;
}

float PureTone::getFreq() {
    return this->freq;
}
