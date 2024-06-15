#define _USE_MATH_DEFINES
#include "PureTone.h"
#include <cmath>

PureTone::PureTone(float sampleRate) : AudioEngine(sampleRate) {
    offset = 2 * M_PI * this->freq / sampleRate;
    samplesToStop = std::ceil(sampleRate*interval*std::pow(10, -3));
}

void PureTone::genSignal(float* data, int buffer) {

    if (gainChanged){
        PureTone::getGainIncrement();
    }

    if (stopEmissionFlag) {

        if (samplesToStopCounter >= samplesToStop){
            for (int idx = 0; idx < buffer; idx += 2) {
                sample = 0.0;
                PureTone::setSampleInBuffer(data, sample, idx);
            }

            angle = 0.0;
            actualGain = -120;
            bypass = true;
            stopEmissionFlag = false;
            samplesToStopCounter = 0;
        }

        else {
            for (int idx = 0; idx < buffer; idx += 2) {
                PureTone::genSample();
                PureTone::setSampleInBuffer(data, sample, idx);
                samplesToStopCounter++;
            }
        }
    }
    else {

        //main working loop:
        for (int idx = 0; idx < buffer; idx += 2) {
            PureTone::genSample();
            PureTone::setSampleInBuffer(data, sample, idx);
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
    offset = 2 * M_PI * freq / sampleRate;
}

float PureTone::getFreq() {
    return this->freq;
}