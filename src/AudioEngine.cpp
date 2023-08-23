#include "AudioEngine.h"


AudioEngine::AudioEngine(int sr, int buffer) : sampleRate(sr), buffer(buffer), data(nullptr), channel(ChannelType::Left) {
    data = new float[buffer*2];
    gain = 0.0;
    actualGain = -120;
    gainChanged = true;
}

AudioEngine::~AudioEngine() {
    delete[] data;
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

float* AudioEngine::getData() const {
    return data;
}

int AudioEngine::getBufferSize() const {
        return buffer;
    }

int AudioEngine::getSampleRate() const {
    return sampleRate;
}

void AudioEngine::stopEmission() {
    AudioEngine::setGain(-130.0);
}

void AudioEngine::setGain(float gain) {
    increaseGain = (actualGain < gain) ? 1 : -1;
    this->gain = gain;
    gainChanged = true;
}

void AudioEngine::getGainIncrement(){
    intervalGain = fabsf(gain - actualGain);
    gainIncrement = (float)increaseGain * intervalGain / ((interval * 0.001) * (float)sampleRate);
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

void AudioEngine::freeBuffer() {
    if (data != nullptr) {
        delete data;
        data = nullptr; 
    }
}

void AudioEngine::setSampleInBuffer(float sample, int index) {

    //Check if data is null.
    if (data == nullptr){
        data = new float[buffer*2];
    }

    //Add data in buffer
    switch (channel) {
        case ChannelType::Left:
            data[index] = sample;
            data[index + 1] = 0;
            break;
        case ChannelType::Right:
            data[index] = 0;
            data[index + 1] = sample;
            break;
        case ChannelType::Stereo:
            data[index] = sample;
            data[index + 1] = sample;
            break;
        default:
            throw UnknownChannelException("Unknown channel type.");
    }

}