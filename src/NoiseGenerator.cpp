#include "Noise.h"
#include <memory>

struct noise_gen {
    int bypass;
    int freqBand;
    ChannelType pan;
    float gain;
    float sampleRate;
    NoiseType noiseType;
    int noiseInstanceExists;
    int valueChanged;
    std::unique_ptr<Noise> noise;
};

static struct noise_gen *pNoiseGen;

extern "C" void noise_generator_alloc(float sampleRate) {

    if (pNoiseGen == nullptr) {
        pNoiseGen = new noise_gen;
    }

    pNoiseGen->sampleRate = sampleRate;
    pNoiseGen->freqBand = 1000;
    pNoiseGen->pan = LEFT_CHANNEL;
    pNoiseGen->gain = 0;
    pNoiseGen->noiseType = WHITE_NOISE;
    pNoiseGen->noiseInstanceExists = 0;
    pNoiseGen->valueChanged = 0;
    pNoiseGen->noise = nullptr;

}

extern "C" void noise_generator_setValue(int param, float value) {

    switch (param & MASK_PARAM) {

        case NSG_BYPASS:

            pNoiseGen->bypass = (int) value;

            switch (pNoiseGen->bypass) {

                case 0:
                    pNoiseGen->valueChanged = 1;
                    if (pNoiseGen->noise) {
                        pNoiseGen->noise->signalEmissionEnabled();
                    }
                    break;

                case 1:
                    pNoiseGen->valueChanged = 1;
                    if (pNoiseGen->noise) {
                        pNoiseGen->noise->stopEmission();
                        pNoiseGen->gain = -120.0;
                    }
                    break;

                default:
                    break;
            }

            break;
        case NSG_FREQ_BAND:
            pNoiseGen->freqBand = value;
            pNoiseGen->valueChanged = 1;
            break;
        case NSG_CHANNEL:
            pNoiseGen->pan = (ChannelType)((int)value);
            pNoiseGen->valueChanged = 1;
            break;
        case NSG_GAIN:
            pNoiseGen->gain = value;
            pNoiseGen->valueChanged = 1;
            break;

        case NSG_NOISE_TYPE:
            printf("[SET]pNoiseGen->noiseType : %3.1f\n", value);
            pNoiseGen->noise = std::make_unique<Noise>(pNoiseGen->sampleRate); //ESTÁ BIEN QUE GENERE LA INSTANCIA ACÁ O DEBERÍA GENERARLA ANTES?
            pNoiseGen->noiseType = (NoiseType)((int)value);
            pNoiseGen->valueChanged = 1;
            break;
        default:
            printf("TGR %s", "error!!\n");
            break;
    }

}

extern "C" float noise_generator_getValue(int param) {
    if (pNoiseGen == nullptr) {
        return 0.0;
    }

    switch (param & MASK_PARAM) {
        case NSG_BYPASS:
            return (float) pNoiseGen->bypass;
        case NSG_FREQ_BAND:
            return (float) pNoiseGen->freqBand;
        case NSG_CHANNEL:
            return (float) pNoiseGen->pan;
        case NSG_GAIN:
            return pNoiseGen->gain;
        case NSG_NOISE_TYPE:
            return pNoiseGen->noiseType;
        default:
            printf("TGR %s", "error!!\n");
            return 0.0;
    }
}

extern "C" void update_noise_generator_params() {
    if (pNoiseGen->valueChanged) {

        if (pNoiseGen->noise->getFreqBand() != pNoiseGen->freqBand) { pNoiseGen->noise->setFreqBand(pNoiseGen->freqBand); }
        if (pNoiseGen->noise->getChannel() != pNoiseGen->pan) { pNoiseGen->noise->setChannel(pNoiseGen->pan); }
        if (pNoiseGen->noise->getGain() != pNoiseGen->gain) { pNoiseGen->noise->setGain(pNoiseGen->gain); }
        if (pNoiseGen->noise->getNoiseType() != pNoiseGen->noiseType) { pNoiseGen->noise->setNoiseType(pNoiseGen->noiseType); }

        pNoiseGen->valueChanged = 0;
    }
}

extern "C" void noise_generator_is_instantiated() {
    //Check if there is an instance of any of the generators
    if (pNoiseGen->noise) {
        pNoiseGen->noiseInstanceExists = 1;
        update_noise_generator_params();
    }
    else {
        pNoiseGen->noiseInstanceExists = 0;
    }
}

extern "C" int noise_generator_is_bypassed() {

    if (pNoiseGen->noiseInstanceExists) {
        return static_cast<int>(pNoiseGen->noise->isBypassed());

    } else {
        return 1;
    }
}

extern "C" void noise_generator_process(float* data, int buffer_size) {

    noise_generator_is_instantiated();

    if (pNoiseGen->noiseInstanceExists) {

        if (!noise_generator_is_bypassed()) {
            pNoiseGen->noise->genSignal(data, buffer_size);

        } else {
            for (int pos = 0; pos < buffer_size; pos += 2) {
                data[pos] = 0;
                data[pos + 1] = 0;
            }
        }
    } else {
        for (int pos = 0; pos < buffer_size; pos += 2) {
            data[pos] = 0;
            data[pos + 1] = 0;
        }
    }
}

extern "C" void noise_generator_free() {
    pNoiseGen->noise = nullptr;
    delete pNoiseGen;
    pNoiseGen = nullptr;
}