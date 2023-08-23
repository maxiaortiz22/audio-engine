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
    float sample = 0.0;
    bool bypass;
    bool enableBypass;
    ChannelType channel;
    //Gain management:
    float gain;
    float actualGain = -120;
    int increaseGain = 1;
    float gainIncrement;
    float interval = 60; //time in ms to reach the desired gain.
    float intervalGain;
    bool gainChanged = true;


public:
    AudioEngine(int sampleRate, int buffer); //Constructor
    virtual ~AudioEngine();

    virtual void genSignal() = 0;
    virtual void genSample() = 0;

    void signalEmissionEnabled();
    void stopEmission();
    bool isBypassed();
    void setChannel(ChannelType Channel);
    ChannelType getChannel() const;
    float* getData() const;
    int getBufferSize() const;
    int getSampleRate() const;
    void setGain(float gain);
    void getGainIncrement();
    void applyGain();
    void freeBuffer();
    void setSampleInBuffer(float sample, int index);
};

#endif //AUDIOENGINE_H