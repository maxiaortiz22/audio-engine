#ifndef PULSETONE_H
#define PULSETONE_H

#include "AudioEngine.h"

enum class PulseState {
    rise,
    on,
    fall,
    off
};

enum class GainIncrementCase {
    rise,
    fall,
    firstPulse,
    stop,
    none
};

class PulseTone : public AudioEngine {

protected:
    //Tone values
    float freq = 1000.0;
    float offset;
    float angle = 0.0;
    //Pulse time values
    int riseTime = 110;
    int fallTime = 110;
    int onTime = 170;
    int offTime = 40;
    int stopTime = 150;
    //Gain management values
    PulseState pulseState = PulseState::rise;
    int pulseGainVariation = 70;
    int pulseGainOppositeLimit = -120;
    int samplesCount = 0;
    int samplesToStopCounter = 0;
    int riseSamples;
    int fallSamples;
    int onSamples;
    int offSamples;
    float pulseGain;
    bool pulseGainFlag;
    bool firstPulseFlag;
    bool gainIncreased;
    int samplesToStop;



public:
    PulseTone(float sampleRate);

    void genSignal(float* data, int buffer) override;
    void genSample() override;
    void setGain(float gain) override;
    void stopEmission() override;
    void applyGain() override;
    void setFreq(float freq);
    float getFreq();
    void setStateFromSamplesCount();
    void setIntervalPerState();
    void getGainIncrement() override;
    GainIncrementCase gainIncrementCases();

};

#endif //PULSETONE_H