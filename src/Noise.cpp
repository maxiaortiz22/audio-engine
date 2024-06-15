#include "Noise.h"
#include <iostream>

Noise::Noise(int sampleRate) : AudioEngine(sampleRate), generator(std::random_device()()), distribution(-1.0f, 1.0f) {
    noiseType = WHITE_NOISE;
    Noise::setNoiseByType();
    samplesToStop = std::ceil(sampleRate*interval*std::pow(10, -3));
}

void Noise::genSignal(float* data, int buffer) {

    if (gainChanged){
        Noise::getGainIncrement();
    }

    if (stopEmissionFlag) {

        if (samplesToStopCounter >= samplesToStop){
            for (int idx = 0; idx < buffer; idx += 2) {
                sample = 0.0;
                Noise::setSampleInBuffer(data, sample, idx);
            }

            actualGain = -120;
            bypass = true;
            stopEmissionFlag = false;
            samplesToStopCounter = 0;
        }

        else {
            for (int idx = 0; idx < buffer; idx += 2) {
                Noise::genSample();
                Noise::setSampleInBuffer(data, sample, idx);
                samplesToStopCounter++;
            }
            Noise::filterSignal(data, buffer);
        }
    }
    else {

        //main working loop:
        for (int idx = 0; idx < buffer; idx += 2) {
            Noise::genSample();
            Noise::setSampleInBuffer(data, sample, idx);
        }
        Noise::filterSignal(data, buffer);
    }
}

void Noise::genSample() {
    sample = distribution(generator);
    Noise::applyGain();
}

void Noise::filterSignal(float* data, int buffer){
    switch (noiseType){
        case WHITE_NOISE:
            break;
        case NARROW_BAND_WHITE_NOISE:
            frequency_cut_process(data, buffer);
            break;
        case  PINK_NOISE :
            //low_pass_process(data, buffer, channel);
            frequency_cut_process(data, buffer);
            break;
        case NARROW_BAND_PINK_NOISE:
            frequency_cut_process(data, buffer);
            break;
        case SPEECH_TEST_WHITE_NOISE :
            frequency_cut_process(data, buffer);
            break;
        default:
            break;
    }
}

void Noise::setNarrowBandFc(){
    if (noiseTypeBypass){
        frequency_cut_setValue(FC_BYPASS, 1);
    }
    else {
        float highPassFreq = fabs(static_cast<float>(freqBand) / pow(2.0f, 0.16666f));
        float lowPassFreq = fabs(static_cast<float>(freqBand) * pow(2.0f, 0.16666f));
        frequency_cut_setValue(FC_LOWPASS + FC_FILTER_TYPE, F_LPF_ORDER_2);
        frequency_cut_setValue(FC_HIGHPASS + FC_FILTER_TYPE, F_HPF_ORDER_2);

        frequency_cut_setValue(FC_LOWPASS + FC_FILTER_FREQ, lowPassFreq);
        frequency_cut_setValue(FC_HIGHPASS + FC_FILTER_FREQ, highPassFreq);
        frequency_cut_setValue(FC_CHANNEL_TYPE, static_cast<float>(channel));

        frequency_cut_setValue(FC_HIGHPASS + FC_FILTER_ENABLED, 1);
        frequency_cut_setValue(FC_LOWPASS + FC_FILTER_ENABLED, 1);

        frequency_cut_setValue(FC_BYPASS, 0);
    }
}

void Noise::setFreqBand(int freqBand){
    this->freqBand = freqBand;
    Noise::setNoiseByType();
}

int Noise::getFreqBand(){
    return freqBand;
}

void Noise::setNoiseType(NoiseType noiseType){
    this->noiseType = noiseType;
    Noise::setNoiseByType();
}

NoiseType Noise::getNoiseType(){
    return noiseType;
}

void Noise::setNoiseByType(){
    switch (noiseType){
        case WHITE_NOISE:
            noiseTypeBypass = true;
            Noise::setNarrowBandFc();
            break;
        case PINK_NOISE:
            noiseTypeBypass = true;
            Noise::setNarrowBandFc();
            frequency_cut_setValue(FC_LOWPASS + FC_FILTER_FREQ, (float)  20);
            frequency_cut_setValue(FC_LOWPASS + FC_FILTER_TYPE, F_LPF_ORDER_1);
            frequency_cut_setValue(FC_LP_BYPASS, 0);
            break;
        case NARROW_BAND_PINK_NOISE:
            frequency_cut_setValue(FC_LOWPASS + FC_FILTER_FREQ, (float)  20);
            frequency_cut_setValue(FC_LOWPASS + FC_FILTER_TYPE, F_LPF_ORDER_1);
            noiseTypeBypass = false;
            Noise::setNarrowBandFc();
            break;
        case NARROW_BAND_WHITE_NOISE:
            noiseTypeBypass = false;
            Noise::setNarrowBandFc();
            break;
        case SPEECH_TEST_WHITE_NOISE:
            noiseTypeBypass = true;
            Noise::setNarrowBandFc();
            frequency_cut_setValue(FC_LOWPASS + FC_FILTER_FREQ, (float) 1000);
            frequency_cut_setValue(FC_LOWPASS + FC_FILTER_TYPE, F_LPF_ORDER_2);
            frequency_cut_setValue(FC_LP_BYPASS, 0);
            break;
        default:
            noiseTypeBypass = true;
            Noise::setNarrowBandFc();
            break;
    }
}