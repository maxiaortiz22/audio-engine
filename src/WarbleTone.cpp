#define _USE_MATH_DEFINES
#include "WarbleTone.h"
#include <cmath>

WarbleTone::WarbleTone(int sampleRate, int buffer) : AudioEngine(sampleRate, buffer) {
    offset = 2 * M_PI * this->freq / (float) sampleRate;
    offsetFm = 2.0 * M_PI * fm / (float) sampleRate;
    df = freq*(deviation/(100*2));
    modulationIndex =  df / fm;
}

void WarbleTone::genSignal() {

    if (gainChanged){
        WarbleTone::getGainIncrement();
    }
    gainChanged = false;

    if (actualGain <= -130) {

        for (int idx = 0; idx < buffer*2; idx += 2) {
            sample = 0.0;
            WarbleTone::setSampleInBuffer(sample, idx);
        }

        angle = 0.0;
        angleFm = 0.0;
        actualGain = -120;
        enableBypass = false;
        bypass = true;
    }
    else {

         //main working loop:
        for (int idx = 0; idx < buffer*2; idx += 2) {
            WarbleTone::genSample();
            WarbleTone::setSampleInBuffer(sample, idx);
        }

    }
}

void WarbleTone::genSample() {

    sample = sin(angle + modulationIndex*sin(angleFm));
    angle += offset;
    angleFm += offsetFm;

    WarbleTone::applyGain();

    // Substract 2PI to avoid large angles.
    if (angle > 2.0 * M_PI) {
        angle -= 2.0 * M_PI;
    }
    if (angleFm > 2.0 * M_PI) {
        angleFm -= 2.0 * M_PI;
    }

}

void WarbleTone::setFreq(float freq) {
    this->freq = freq;
    offset = 2 * M_PI * this->freq / (float) sampleRate;
    angle = 0.0;
    angleFm = 0.0;
    df = this->freq*(deviation/(100*2));
    modulationIndex =  df / fm;
}

float WarbleTone::getFreq(){
    return this->freq;
}

void WarbleTone::setFm(float fm) {
    this->fm = fm;
    this->offsetFm = 2.0 * M_PI * this->fm / (float) sampleRate;
    angle = 0.0;
    angleFm = 0.0;
    df = freq*(deviation/(100*2));
    modulationIndex =  df / this->fm;
}

float WarbleTone::getFm(){
    return this->fm;
}

void WarbleTone::setDeviation(float deviation) {
    this->deviation = deviation;
    angle = 0.0;
    angleFm = 0.0;
    df = freq*(this->deviation/(100*2));
    modulationIndex =  df / this->fm;
}

float WarbleTone::getDeviation() {
    return this->deviation;
}