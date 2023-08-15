#ifndef AUDIOENGINE_H
#define AUDIOENGINE_H

#include "AudioExceptions.h"
#include "db.h"

enum class ChannelType {
    Left,
    Right,
    Stereo
};

class AudioEngine{

protected:
    int sampleRate;
    int buffer;
    float* data;
    float gain;
    float amplitude;
    ChannelType channel;

public:
    AudioEngine(int sampleRate, int buffer); //Constructor
    virtual ~AudioEngine();

    virtual void genSignal() = 0;
    virtual float genSample() = 0;

    void setChannel(ChannelType Channel);
    ChannelType getChannel() const;
    float* getData() const;
    int getBufferSize() const;
    int getSampleRate() const;
    virtual void setGain(float gain);
    void freeBuffer();
    void setSampleInBuffer(float sample, int index);
};

#endif //AUDIOENGINE_H