#ifndef PULSETONE_H
#define PULSETONE_H

#include "AudioEngine.h"

class PulseTone : public AudioEngine {

private:
    float freq = 1000.0;
    float offset;
    float angle = 0.0;
    int riseTime = 35;
    int fallTime = 35;
    int onTime = 150;
    int offTime = 175;

public:
    PulseTone(int sampleRate, int buffer);

    void genSignal() override;
    void genSample() override;
    void setFreq(float freq);
    float getFreq();

};

#endif //PULSETONE_H