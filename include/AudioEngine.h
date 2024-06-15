#ifndef AUDIOENGINE_H
#define AUDIOENGINE_H

#include "AudioExceptions.h"
#include "usoundlib_params.h"
#include "db.h"

class AudioEngine{

protected:
    float sampleRate;
    int buffer;
    float sample = 0.0;
    bool bypass;
    ChannelType channel;
    //Gain management:
    float gain;
    float actualGain = -120.0;
    int increaseGain = 1;
    float gainIncrement;
    float interval = 150;
    float intervalGain;
    bool gainChanged = true;
    bool stopEmissionFlag = false;
    int samplesToStop = 0;
    int samplesToStopCounter = 0;
    float intercomVolume = 10;
    bool secondGenerator = false;


public:
    AudioEngine(float sampleRate); //Constructor

    virtual void genSignal(float* data, int buffer) = 0;
    virtual void genSample() = 0;

    void signalEmissionEnabled();
    virtual void stopEmission();
    bool isBypassed();
    void setChannel(ChannelType Channel);
    ChannelType getChannel() const;
    int getBufferSize() const;
    float getSampleRate() const;
    virtual void setGain(float gain);
    float getGain();
    void setInitGain(float actualGain);
    float getInitGain();
    void setInterval(float interval);
    float getInterval();
    virtual void getGainIncrement();
    virtual void applyGain();
    void setSampleInBuffer(float *data, float sample, int index);
    void setIntercomVolume(float intercomVolume);
    float getIntercomVolume();
    void setSecondGenerator(bool secondGenerator);
    bool isSecondGenerator();
};

#endif //AUDIOENGINE_H