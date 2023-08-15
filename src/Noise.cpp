#include "Noise.h"
#include <iostream>

Noise::Noise(int sampleRate, int buffer) : AudioEngine(sampleRate, buffer), generator(std::random_device()()), distribution(-1.0f, 1.0f) {
    auxBuffer = std::vector<float>(buffer);
    filteredSignal = std::vector<float>(buffer);
}

void Noise::genSignal() {

    for (int i = 0; i < auxBuffer.size(); i++) {
        float sample = Noise::genSample();
        auxBuffer[i] = sample;
    }

    if (noiseType == NoiseType::White){
        filteredSignal = auxBuffer;
    }

    else {
        Noise::filterSignal(auxBuffer);
    }
    
    //main working loop:
    int i;
    for (int idx = 0; idx < buffer*2; idx += 2) {
        i = idx/2;
        float sample = filteredSignal[i];
        Noise::setSampleInBuffer(sample, idx);
    }
}

float Noise::genSample() {
   return amplitude * distribution(generator);
}

void Noise::setNoiseType(NoiseType noiseType, float freq) {
    this->noiseType = noiseType;
    this->freq = freq;

    switch (noiseType) {

    case NoiseType::White:
        printf("Seteo ruido blanco\n");
        break;

    case NoiseType::Pink:

        printf("Seteo ruido rosa\n");

        //Defining filter characteristics:
        N = 1;
        btype = FilterType::Lowpass;
        fc = {20};

        //Get the filter coefficients:
        coeff = butter(N, fc, btype, analog, AudioEngine::sampleRate);
        std::tie(b, a) = coeff;

        //Print coefficients:
        std::cout<< "b: [";
        for(auto coeff : b){
            std::cout<<coeff<<", ";
        }
        std::cout<< "]"<< std::endl;

        std::cout<< "a: [";
        for(auto coeff : a){
            std::cout<<coeff<<", ";
        }
        std::cout<< "]"<< std::endl;


        break;

    case NoiseType::NBN:

        printf("Seteo ruido NBN\n");

        //Defining filter characteristics:
        N = 2;
        btype = FilterType::Bandpass;
        lowcut = freq / sqrt(2);
        highcut = freq * sqrt(2);
        fc = {lowcut, highcut};

        //Get the filter coefficients:
        coeff = butter(N, fc, btype, analog, AudioEngine::sampleRate);
        std::tie(b, a) = coeff;

        //Print coefficients:
        std::cout<< "b: [";
        for(auto coeff : b){
            std::cout<<coeff<<", ";
        }
        std::cout<< "]"<< std::endl;

        std::cout<< "a: [";
        for(auto coeff : a){
            std::cout<<coeff<<", ";
        }
        std::cout<< "]"<< std::endl;

        break;
    
    default:
        throw UnknownNoiseTypeException("Unknown type of noise.");
    }
}

void Noise::filterSignal(std::vector<float> signal) {

    for (int n = 0; n < signal.size(); n++){
        filteredSignal[n] = b[0] * signal[n];

        for (int i = 1; i < b.size(); i++){
            if (n>=i){
                filteredSignal[n] += b[i] * signal[n-i];
            }
            else{
                break;
            }
        }

        for (int i = 1; i < a.size(); i++){
            if (n>0 && n>=i){
                filteredSignal[n] -= a[i]*filteredSignal[n-i];
            }
            else{
                break;
            }
        }
    }
}