#include "AudioEngine.h"
#include <cmath>


AudioEngine::AudioEngine(float sr) : sampleRate(sr), channel(LEFT_CHANNEL) {
    gain = 0.0;
    actualGain = -120;
    gainChanged = true;
}

void AudioEngine::signalEmissionEnabled(){
    bypass = false;
}

bool AudioEngine::isBypassed(){
    return bypass;
}

void AudioEngine::setChannel(ChannelType Channel){

    this->channel = Channel;
};

ChannelType AudioEngine::getChannel() const {
    return channel;
}

int AudioEngine::getBufferSize() const {
    return buffer;
}

float AudioEngine::getSampleRate() const {
    return sampleRate;
}

void AudioEngine::stopEmission() {
    stopEmissionFlag = true;
}

void AudioEngine::setGain(float gain) {
    increaseGain = (actualGain < gain) ? 1 : -1;
    this->gain = gain;
    gainChanged = true;
}

float AudioEngine::getGain() {
    return gain;
}

void AudioEngine::setInitGain(float actualGain) {
    this->actualGain = actualGain;
}

float AudioEngine::getInitGain() {
    return actualGain;
}

void AudioEngine::setInterval(float interval) {
    this->interval = interval;
}

float AudioEngine::getInterval() {
    return interval;
}

void AudioEngine::setIntercomVolume(float intercomVolume) {
    this->intercomVolume = intercomVolume;
}

float AudioEngine::getIntercomVolume() {
    return intercomVolume;
}

void AudioEngine::getGainIncrement(){
    intervalGain = fabsf(gain - actualGain);
    gainIncrement = ((float)increaseGain * intervalGain) / ((interval * 0.001) * (float)sampleRate);
    gainChanged = false;
}

void AudioEngine::applyGain() {

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

}

void AudioEngine::setSecondGenerator(bool secondGenerator) {
    this->secondGenerator = secondGenerator;
}

bool AudioEngine::isSecondGenerator() {
    return secondGenerator;
}

void AudioEngine::setSampleInBuffer(float *data, float sample, int index) {

    //Add data in buffer
    if (!secondGenerator) {
        switch (channel) {
            case LEFT_CHANNEL:
                data[index] = sample;
                data[index + 1] = 0;
                break;
            case RIGHT_CHANNEL:
                data[index] = 0;
                data[index + 1] = sample;
                break;
            case STEREO_CHANNEL:
                data[index] = sample;
                data[index + 1] = sample;
                break;
            case MIC_CHANNEL_MODE:
                data[index] = data[index] * dB2Lin(intercomVolume);
                data[index + 1] = data[index + 1] * dB2Lin(intercomVolume);
                break;
            default:
                throw UnknownChannelException("Unknown channel type.");
        }
    } else {
        switch (channel) {
            case LEFT_CHANNEL:
                data[index] += sample;
                break;
            case RIGHT_CHANNEL:
                data[index + 1] += sample;
                break;
            case STEREO_CHANNEL:
                data[index] += sample;
                data[index + 1] += sample;
                break;
            case MIC_CHANNEL_MODE:
                break;
            default:
                throw UnknownChannelException("Unknown channel type.");
        }
    }


}
