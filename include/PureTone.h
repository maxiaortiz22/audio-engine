#ifndef PURETONE_H
#define PURETONE_H

#include "AudioEngine.h"

class PureTone : public AudioEngine {

private:
    float freq = 1000.0;
    float offset;
    float sample = 0.0;
    float angle = 0.0;
    float actualGain = -120;
    int increaseGain = 1;
    float gainIncrement;
    float interval = 65; //time in ms to reach the desired gain.
    float intervalGain;
    float minFrame;
    float frameSize;
    float frameTime;
    float frameGain;
    bool toneGainChanged = true;

public:
    PureTone(int sampleRate, int buffer);

    void genSignal() override;
    float genSample() override;
    void setGain(float gain) override;
    void getGainIncrement();
    void setFreq(float freq);
    float getFreq();

};

#endif //PURETONE_H