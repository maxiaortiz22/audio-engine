#include "AudioEngine.h"


AudioEngine::AudioEngine(int sr, int buffer) : sampleRate(sr), buffer(buffer), data(nullptr), channel("Left") {
    data = new float[buffer*2];
}

AudioEngine::~AudioEngine() {
    delete[] data;
}

void AudioEngine::setChannel(std::string Channel){
    if (Channel == "Left" || Channel == "Right" || Channel == "Stereo") {
        this->channel = Channel;
    }
    else{
        throw UnknownChannelException(Channel);
    }
};

std::string AudioEngine::getChannel() const {
    return channel;
}

float* AudioEngine::getData() const {
    return data;
}

int AudioEngine::getSampleRate() const {
    return sampleRate;
}

void AudioEngine::setAmplitude(float amp) {
    amplitude = amp;
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
    if (channel == "Left") {
        data[index] = sample;
        data[index + 1] = 0;
    } else if (channel == "Right") {
        data[index] = 0;
        data[index + 1] = sample;
    } else if (channel == "Stereo") {
        data[index] = sample;
        data[index + 1] = sample;
    } else {
        throw UnknownChannelException(channel);
    }

}