#include "AudioEngine.h"


AudioEngine::AudioEngine(int sr, int buffer) : sampleRate(sr), buffer(buffer), data(nullptr), channel(ChannelType::Left) {
    data = new float[buffer*2];
    gain = 0.0;
    amplitude = dB2Lin(gain);
}

AudioEngine::~AudioEngine() {
    delete[] data;
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

void AudioEngine::setGain(float gain) {
    this->gain = gain;
    amplitude = dB2Lin(this->gain);
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