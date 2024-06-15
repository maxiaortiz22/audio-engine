#ifndef PURETONE_H
#define PURETONE_H

#include "AudioEngine.h"

class PureTone : public AudioEngine {

private:
    float freq = 1000.0;
    float offset;
    float angle = 0.0;

public:
    PureTone(float sampleRate);

    void genSignal(float* data, int buffer) override;
    void genSample() override;
    void setFreq(float freq);
    float getFreq();

};

#endif //PURETONE_H