#define _USE_MATH_DEFINES
#include "WarbleTone.h"
#include <cmath>

WarbleTone::WarbleTone(float sampleRate) : AudioEngine(sampleRate) {
    offset = 2 * M_PI * this->freq / sampleRate;
    offsetFm = 2.0 * M_PI * fm / sampleRate;
    df = freq*(deviation/(100*2));
    modulationIndex =  df / fm;
    samplesToStop = std::ceil(sampleRate*interval*std::pow(10, -3));
}

void WarbleTone::genSignal(float* data, int buffer) {

    if (gainChanged){
        WarbleTone::getGainIncrement();
    }

    if (stopEmissionFlag) {

        if (samplesToStopCounter >= samplesToStop){
            for (int idx = 0; idx < buffer; idx += 2) {
                sample = 0.0;
                WarbleTone::setSampleInBuffer(data, sample, idx);
            }

            angle = 0.0;
            actualGain = -120;
            bypass = true;
            stopEmissionFlag = false;
            samplesToStopCounter = 0;
        }

        else {
            for (int idx = 0; idx < buffer; idx += 2) {
                WarbleTone::genSample();
                WarbleTone::setSampleInBuffer(data, sample, idx);
                samplesToStopCounter++;
            }
        }
    }
    else {

        //main working loop:
        for (int idx = 0; idx < buffer; idx += 2) {
            WarbleTone::genSample();
            WarbleTone::setSampleInBuffer(data, sample, idx);
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
    offset = 2 * M_PI * this->freq / sampleRate;
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
    this->offsetFm = 2.0 * M_PI * this->fm / sampleRate;
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