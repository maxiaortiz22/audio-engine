#define _USE_MATH_DEFINES
#include "PulseTone.h"
#include <cmath>

PulseTone::PulseTone(int sampleRate, int buffer) : AudioEngine(sampleRate, buffer) {
    offset = 2 * M_PI * this->freq / (float) sampleRate;
}

void PulseTone::genSignal() {

    if (gainChanged){
        PulseTone::getGainIncrement();
    }
    gainChanged = false;

    if (actualGain <= -130) {

        for (int idx = 0; idx < buffer*2; idx += 2) {
            sample = 0.0;
            PulseTone::setSampleInBuffer(sample, idx);
        }

        angle = 0.0;
        actualGain = -120;
        enableBypass = false;
        bypass = true;
    }
    else {

         //main working loop:
        for (int idx = 0; idx < buffer*2; idx += 2) {
            PulseTone::genSample();
            PulseTone::setSampleInBuffer(sample, idx);
        }

    }
}

void PulseTone::genSample() {

    sample = sin(angle);
    angle += offset;

    PulseTone::applyGain();

    // Substract 2PI to avoid large angles.
    if (angle> 2.0 * M_PI) {
        angle -= 2.0 * M_PI;
    }
}

void PulseTone::setFreq(float freq) {
    this->freq = freq;
    offset = 2 * M_PI * freq / (float) sampleRate;
}

float PulseTone::getFreq() {
    return this->freq;
}
