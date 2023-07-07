#ifndef WARBLETONE_H
#define WARBLETONE_H

#include "AudioEngine.h"

class WarbleTone : public AudioEngine {

private:
    float freq = 1000.0;
    float fm = 5.0; //Modulating frequency (between 4 Hz and 20 Hz)
    float offset;
    float angle = 0.0;

public:
    WarbleTone(int sampleRate, int buffer);

    void genSignal() override;
    float genSample() override;
    void setFreq(float freq);

};

#endif //WARBLETONE_H