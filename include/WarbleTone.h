#ifndef WARBLETONE_H
#define WARBLETONE_H

#include "AudioEngine.h"

class WarbleTone : public AudioEngine {

private:
    float freq = 1000.0;
    float fm = 5.0; //Modulating frequency (between 4 Hz and 20 Hz)
    float deviation = 5.0; //Frequency deviation (between 5 and 25%)
    float offset;
    float offsetFm;
    float df;
    float modulationIndex;
    float angle = 0.0;
    float angleFm = 0.0;

public:
    WarbleTone(int sampleRate, int buffer);

    void genSignal() override;
    void genSample() override;
    void setFreq(float freq);
    float getFreq();
    void setFm(float fm);
    float getFm();
    void setDeviation(float deviation);
    float getDeviation();

};

#endif //WARBLETONE_H