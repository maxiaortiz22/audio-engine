#define _USE_MATH_DEFINES
#include "PureTone.h"
#include <cmath>

PureTone::PureTone(int sampleRate, int buffer) : AudioEngine(sampleRate, buffer) {
    offset = 2 * M_PI * this->freq / (float) sampleRate;
}

void PureTone::genSignal() {

    if (toneGainChanged){
        PureTone::getGainIncrement();
    }

    //main working loop:
    for (int idx = 0; idx < buffer*2; idx += 2) {
        sample = PureTone::genSample();
        PureTone::setSampleInBuffer(sample, idx);
    }

    toneGainChanged = false;
}

float PureTone::genSample() {

    sample = amplitude * sin(angle);
    angle += offset;

    switch (increaseGain) {
    case 1: // Increased amplitude

        actualGain = (actualGain + gainIncrement < gain) ? actualGain + gainIncrement : gain;
        sample = sample * dB2Lin(actualGain);

        break;

    case -1: //Amplitude is reduced
        
        actualGain = (actualGain + gainIncrement > gain) ? actualGain + gainIncrement : gain;
        sample = sample * dB2Lin(actualGain);

        break;
    
    default:
        throw UnknownGainException("increaseGain must be 1 or -1 to increase or decrease the gain");
        break;
    }

    // Substract 2PI to avoid large angles.
    if (angle> 2.0 * M_PI) {
        angle -= 2.0 * M_PI;
    }

    return sample;
}

void PureTone::getGainIncrement(){
    intervalGain = fabsf(gain - actualGain);
    minFrame = (float)(sampleRate * 0.001);
    frameSize = (float)buffer / minFrame;
    frameTime = frameSize / interval;
    frameGain = frameTime * intervalGain;
    gainIncrement = (frameGain * increaseGain) / (float)buffer;
}

void PureTone::setGain(float gain) {
    increaseGain = (this->gain < gain) ? 1 : -1;
    this->gain = gain;
    amplitude = dB2Lin(this->gain);
    toneGainChanged = true;
}

void PureTone::setFreq(float freq) {
    //Set freq and reset other parameters
    this->freq = freq;
    offset = 2 * M_PI * freq / (float) sampleRate;
    //angle = 0.0;
    //actualGain = -120;
}

float PureTone::getFreq() {
    return this->freq;
}
