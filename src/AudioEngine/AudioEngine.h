#ifndef AUDIOENGINE_H
#define AUDIOENGINE_H

#include <string>
#include "UnknownChannelException.h"

class AudioEngine{

protected:
    int sampleRate;
    int buffer;
    float* data;
    float amplitude = 1.0;
    std::string channel;

public:
    AudioEngine(int sampleRate, int buffer); //Constructor
    virtual ~AudioEngine();

    virtual void genSignal() = 0;
    virtual float genSample() = 0;

    void setChannel(std::string Channel);
    std::string getChannel() const;
    float* getData() const;
    int getSampleRate() const;
    void setAmplitude(float amp);
    void freeBuffer();
    void setSampleInBuffer(float sample, int index);
};

#endif //AUDIOENGINE_H