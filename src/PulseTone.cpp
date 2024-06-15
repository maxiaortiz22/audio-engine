#define _USE_MATH_DEFINES
#include "PulseTone.h"
#include <cmath>

PulseTone::PulseTone(float sampleRate) : AudioEngine(sampleRate){
    offset = 2 * M_PI * this->freq / (float) sampleRate;

    pulseState = PulseState::rise;
    interval = riseTime;
    pulseGainFlag = true;
    firstPulseFlag = true;
    stopEmissionFlag = false;
    pulseGain = gain;

    riseSamples = static_cast<int>(sampleRate*riseTime*std::pow(10, -3));
    onSamples = static_cast<int>(sampleRate*onTime*std::pow(10, -3)) + riseSamples;
    fallSamples = static_cast<int>(sampleRate*fallTime*std::pow(10, -3)) + onSamples;
    offSamples = static_cast<int>(sampleRate*offTime*std::pow(10, -3)) + fallSamples;

    samplesToStop = static_cast<int>(sampleRate*stopTime*std::pow(10, -3));
}

void PulseTone::genSignal(float* data, int buffer) {

    if (pulseGainFlag){ //Activates when rising or falling
        PulseTone::getGainIncrement();
    }

    if (stopEmissionFlag && (pulseState == PulseState::fall)) {

        if (samplesToStopCounter >= samplesToStop){
            for (int idx = 0; idx < buffer; idx += 2) {
                sample = 0.0;
                PulseTone::setSampleInBuffer(data, sample, idx);
            }

            angle = 0.0;
            actualGain = -120;
            pulseGainOppositeLimit = -120;
            stopEmissionFlag = false;
            samplesToStopCounter = 0;
            samplesCount = 0;
            pulseState = PulseState::rise;
            increaseGain = 1;
            interval = riseTime;
            pulseGainFlag = true;
            firstPulseFlag = true;
            bypass = true;
        }

        else {
            for (int idx = 0; idx < buffer; idx += 2) {
                PulseTone::genSample();
                PulseTone::setSampleInBuffer(data, sample, idx);
                samplesToStopCounter++;
            }
        }
    }
    else {

        //main working loop:
        for (int idx = 0; idx < buffer; idx += 2) {
            PulseTone::genSample();
            PulseTone::setSampleInBuffer(data, sample, idx);
            samplesCount = ((samplesCount + 1) <= offSamples) ? samplesCount + 1 : 0;
            PulseTone::setStateFromSamplesCount();
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

void PulseTone::applyGain() {

    switch (increaseGain) {

        case 1: // Increased amplitude

            actualGain = (actualGain + gainIncrement < pulseGain) ? actualGain + gainIncrement : pulseGain;

            if (actualGain < pulseGainOppositeLimit) {
                actualGain = pulseGainOppositeLimit;
            }

            sample = sample * dB2Lin(actualGain);

            break;

        case -1: //Amplitude is reduced

            actualGain = (actualGain + gainIncrement > pulseGain) ? actualGain + gainIncrement : pulseGain;

            if (actualGain > pulseGainOppositeLimit) {
                actualGain = pulseGainOppositeLimit;
            }

            sample = sample * dB2Lin(actualGain);

            break;

        default:
            throw UnknownGainException("increaseGain must be 1 or -1 to increase or decrease the gain");
            break;
    }

}

void PulseTone::setGain(float gain) {
    gainIncreased = (this->gain < gain);
    this->gain = gain;
    gainChanged = true;
}

void PulseTone::setFreq(float freq) {
    this->freq = freq;
    offset = 2 * M_PI * freq / sampleRate;
}

float PulseTone::getFreq() {
    return this->freq;
}

void PulseTone::stopEmission() {
    PulseTone::setGain(-120.0);
    stopEmissionFlag = true;
}

void PulseTone::setStateFromSamplesCount() {

    if (samplesCount == 0) { //Rise
        pulseState = PulseState::rise;
        pulseGain = pulseGain + pulseGainVariation;
        pulseGainOppositeLimit = pulseGain - pulseGainVariation;
        PulseTone::setIntervalPerState();
        pulseGainFlag = true;
        increaseGain = 1;

    }
    else if (samplesCount == riseSamples) { //On
        pulseState = PulseState::on;
        PulseTone::setIntervalPerState();
    }
    else if (samplesCount == onSamples) { //Fall
        pulseState = PulseState::fall;
        pulseGain = pulseGain - pulseGainVariation;
        pulseGainOppositeLimit = pulseGain + pulseGainVariation;
        PulseTone::setIntervalPerState();
        pulseGainFlag = true;
        increaseGain = -1;
    }
    else if (samplesCount == fallSamples) { //Off
        pulseState = PulseState::off;
        PulseTone::setIntervalPerState();
    }

}

void PulseTone::setIntervalPerState() {
    switch (pulseState)
    {
        case PulseState::rise :
            interval = riseTime;
            break;

        case PulseState::on :
            interval = onTime;
            break;

        case PulseState::fall :
            interval = fallTime;
            break;

        case PulseState::off :
            interval = offTime;
            break;

        default:
            throw UnknownIntervalException("Unknown interval pulse state.");
            break;
    }
}

void PulseTone::getGainIncrement(){

    switch (PulseTone::gainIncrementCases()){

        case GainIncrementCase::rise:
            pulseGain = gain;
            gainChanged = false;
            break;

        case GainIncrementCase::fall:
            pulseGain = gain - pulseGainVariation;
            gainChanged = false;
            break;

        case GainIncrementCase::firstPulse:
            pulseGain = gain;
            pulseGainOppositeLimit = -120;
            gainChanged = false;
            firstPulseFlag = false;
            break;

        case GainIncrementCase::stop:
            pulseGain = gain - pulseGainVariation;
            interval = stopTime;
            break;

        default:
            break;
    }

    intervalGain = fabsf(pulseGain - actualGain);
    gainIncrement = (float)increaseGain * intervalGain / ((interval * 0.001) * sampleRate);
    pulseGainFlag = false;
}

GainIncrementCase PulseTone::gainIncrementCases(){

    if (gainChanged && !firstPulseFlag && !stopEmissionFlag && gainIncreased && (pulseState == PulseState::rise)) {
        return GainIncrementCase::rise;
    }

    else if (gainChanged && !firstPulseFlag && !stopEmissionFlag && !gainIncreased && (pulseState == PulseState::fall)) {
        return GainIncrementCase::fall;
    }

    else if (gainChanged && firstPulseFlag) {
        return GainIncrementCase::firstPulse;
    }

    else if (stopEmissionFlag && !gainIncreased && (pulseState == PulseState::fall)) {
        return GainIncrementCase::stop;
    }

    else {
        return GainIncrementCase::none;
    }
}