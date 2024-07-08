#include "ToneGenerator.h"
#include "PureTone.h"
#include "PulseTone.h"
#include "WarbleTone.h"
#include <memory>
#include <stdio.h>

struct tone_gen {
    int bypass;
    float freq;
    ChannelType pan;
    float gain;
    float initGain;
    float sampleRate;
    int toneType;
    float intercomVolume;
    float interval;
    int toneInstanceExists;
    int valueChanged;
    bool secondGenerator;
    std::unique_ptr<PureTone> pureTone;
    std::unique_ptr<PulseTone> pulseTone;
    std::unique_ptr<WarbleTone> warbleTone;
};

struct second_tone_gen {
    int bypass;
    float freq;
    ChannelType pan;
    float gain;
    float initGain;
    float sampleRate;
    int toneType;
    float intercomVolume;
    float interval;
    int toneInstanceExists;
    int valueChanged;
    bool secondGenerator;
    std::unique_ptr<PureTone> pureTone;
    std::unique_ptr<PulseTone> pulseTone;
    std::unique_ptr<WarbleTone> warbleTone;
};

static struct tone_gen *pToneGen;
static struct second_tone_gen *pToneGen2;

extern "C" UsoundResult tone_generator_alloc(float sampleRate) {

    if (pToneGen == nullptr) {
        pToneGen = new tone_gen;
    }
    pToneGen->bypass = 1;
    pToneGen->sampleRate = sampleRate;
    pToneGen->freq = 1000;
    pToneGen->interval = 150;
    pToneGen->pan = LEFT_CHANNEL;
    pToneGen->gain = 0;
    pToneGen->initGain = -120.0;
    pToneGen->toneType = CONTINUOUS_TONE;
    pToneGen->intercomVolume = 10;
    pToneGen->toneInstanceExists = 0;
    pToneGen->valueChanged = 0;
    pToneGen->secondGenerator = false;
    pToneGen->pureTone = nullptr;
    pToneGen->pulseTone = nullptr;
    pToneGen->warbleTone = nullptr;


    return USOUND_SUCCESS;
}

extern "C" UsoundResult second_tone_generator_alloc(float sampleRate) {

    if (pToneGen2 == nullptr) {
        pToneGen2 = new second_tone_gen;
    }
    pToneGen2->bypass = 1;
    pToneGen2->sampleRate = sampleRate;
    pToneGen2->freq = 1000;
    pToneGen2->interval = 150;
    pToneGen2->pan = LEFT_CHANNEL;
    pToneGen2->gain = 0;
    pToneGen2->initGain = -120.0;
    pToneGen2->toneType = CONTINUOUS_TONE;
    pToneGen2->intercomVolume = 10;
    pToneGen2->toneInstanceExists = 0;
    pToneGen2->valueChanged = 0;
    pToneGen2->secondGenerator = true;
    pToneGen2->pureTone = nullptr;
    pToneGen2->pulseTone = nullptr;
    pToneGen2->warbleTone = nullptr;

    return USOUND_SUCCESS;
}

extern "C" UsoundResult tone_generator_setValue(int param, float value) {

    UsoundResult res = USOUND_SUCCESS;

    switch (param & MASK_PARAM) {

        case TG_BYPASS:

            pToneGen->bypass = (int) value;

            switch (pToneGen->bypass) {

                case 0:
                    pToneGen->valueChanged = 1;
                    if (pToneGen->pureTone || pToneGen->pulseTone || pToneGen->warbleTone) {
                        if (pToneGen->pureTone) {
                            pToneGen->pureTone->signalEmissionEnabled();
                        }
                        else if (pToneGen->pulseTone) {
                            pToneGen->pulseTone->signalEmissionEnabled();
                        }
                        else if (pToneGen->warbleTone) {
                            pToneGen->warbleTone->signalEmissionEnabled();
                        }
                    }
                    break;

                case 1:
                    pToneGen->valueChanged = 1;
                    if (pToneGen->pureTone || pToneGen->pulseTone || pToneGen->warbleTone) {
                        if (pToneGen->pureTone) {
                            pToneGen->pureTone->stopEmission();
                            pToneGen->gain = -120.0;
                        }
                        else if (pToneGen->pulseTone) {
                            pToneGen->pulseTone->stopEmission();
                        }
                        else if (pToneGen->warbleTone) {
                            pToneGen->warbleTone->stopEmission();
                            pToneGen->gain = -120.0;
                        }
                    }
                    break;

                default:
                    break;

            }

            break;
        case TG_FREQ:
            pToneGen->freq = value;
            pToneGen->valueChanged = 1;
            break;
        case TG_PAN:
            pToneGen->pan = (ChannelType)((int)value);
            pToneGen->valueChanged = 1;
            break;
        case TG_GAIN:
            pToneGen->gain = value;
            pToneGen->valueChanged = 1;
            break;
        case TG_INIT_GAIN:
            pToneGen->initGain = value;
            pToneGen->valueChanged = 1;
            break;
        case TG_INTERVAL:
            pToneGen->interval = value;
            pToneGen->valueChanged = 1;
            break;
        case TG_TONE_TYPE:
            printf("[SET]tone_gen->toneType : %3.1f\n", value);
            pToneGen->toneType = (int) value;
            switch (pToneGen->toneType){
                case CONTINUOUS_TONE:
                    pToneGen->pureTone = std::make_unique<PureTone>(pToneGen->sampleRate);
                    pToneGen->pureTone->setSecondGenerator(pToneGen->secondGenerator);
                    pToneGen->valueChanged = 1;
                    pToneGen->pulseTone = nullptr;
                    pToneGen->warbleTone = nullptr;
                    break;
                case PULSE_TONE_HALF_SEC:
                    pToneGen->pulseTone = std::make_unique<PulseTone>(pToneGen->sampleRate);
                    pToneGen->pulseTone->setSecondGenerator(pToneGen->secondGenerator);
                    pToneGen->valueChanged = 1;
                    pToneGen->pureTone = nullptr;
                    pToneGen->warbleTone = nullptr;
                    break;
                case PULSE_TONE_ONE_SEC:
                    pToneGen->pulseTone = std::make_unique<PulseTone>(pToneGen->sampleRate);
                    pToneGen->pulseTone->setSecondGenerator(pToneGen->secondGenerator);
                    pToneGen->valueChanged = 1;
                    pToneGen->pureTone = nullptr;
                    pToneGen->warbleTone = nullptr;
                    break;
                case WARBLE_TONE:
                    pToneGen->warbleTone = std::make_unique<WarbleTone>(pToneGen->sampleRate);
                    pToneGen->warbleTone->setSecondGenerator(pToneGen->secondGenerator);
                    pToneGen->valueChanged = 1;
                    pToneGen->pureTone = nullptr;
                    pToneGen->pulseTone = nullptr;
                    break;
                default:
                    break;
            }
            break;
        case TG_INTERCOM_VOLUME:
            pToneGen->intercomVolume = value;
            pToneGen->valueChanged = 1;
            break;
        default:
            printf("TGR %s", "error!!\n");
            res = USOUND_ERROR_TONE_GENERATOR_SET_PARAMETER_ERROR;
            break;
    }

    return res;
}

extern "C" UsoundResult second_tone_generator_setValue(int param, float value) {

    UsoundResult res = USOUND_SUCCESS;

    switch (param & MASK_PARAM) {
        case TG_BYPASS:
            pToneGen2->bypass = (int) value;

            switch (pToneGen2->bypass) {

                case 0:
                    pToneGen2->valueChanged = 1;
                    if (pToneGen2->pureTone || pToneGen2->pulseTone || pToneGen2->warbleTone) {
                        if (pToneGen2->pureTone) {
                            pToneGen2->pureTone->signalEmissionEnabled();
                        }
                        else if (pToneGen2->pulseTone) {
                            pToneGen2->pulseTone->signalEmissionEnabled();
                        }
                        else if (pToneGen2->warbleTone) {
                            pToneGen2->warbleTone->signalEmissionEnabled();
                        }
                    }
                    break;

                case 1:
                    pToneGen2->valueChanged = 1;
                    if (pToneGen2->pureTone || pToneGen2->pulseTone || pToneGen2->warbleTone) {
                        if (pToneGen2->pureTone) {
                            pToneGen2->pureTone->stopEmission();
                            pToneGen->gain = -120.0;
                        }
                        else if (pToneGen2->pulseTone) {
                            pToneGen2->pulseTone->stopEmission();
                        }
                        else if (pToneGen2->warbleTone) {
                            pToneGen2->warbleTone->stopEmission();
                            pToneGen->gain = -120.0;
                        }
                    }
                    break;

                default:
                    break;

            }

            break;
        case TG_FREQ:
            pToneGen2->freq = value;
            pToneGen2->valueChanged = 1;
            break;
        case TG_PAN:
            pToneGen2->pan = (ChannelType)((int)value);
            pToneGen2->valueChanged = 1;
            break;
        case TG_GAIN:
            pToneGen2->gain = value;
            pToneGen2->valueChanged = 1;
            break;
        case TG_INIT_GAIN:
            pToneGen2->initGain = value;
            pToneGen2->valueChanged = 1;
            break;
        case TG_INTERVAL:
            pToneGen2->interval = value;
            pToneGen2->valueChanged = 1;
            break;
        case TG_TONE_TYPE:
            printf("[SET]tone_gen->toneType : %3.1f\n", value);
            pToneGen2->toneType = (int) value;
            switch (pToneGen2->toneType){
                case CONTINUOUS_TONE:
                    pToneGen2->pureTone = std::make_unique<PureTone>(pToneGen2->sampleRate);
                    pToneGen2->pureTone->setSecondGenerator(pToneGen2->secondGenerator);
                    pToneGen2->valueChanged = 1;
                    pToneGen2->pulseTone = nullptr;
                    pToneGen2->warbleTone = nullptr;
                    break;
                case PULSE_TONE_HALF_SEC:
                    pToneGen2->pulseTone = std::make_unique<PulseTone>(pToneGen2->sampleRate);
                    pToneGen2->pulseTone->setSecondGenerator(pToneGen2->secondGenerator);
                    pToneGen2->valueChanged = 1;
                    pToneGen2->pureTone = nullptr;
                    pToneGen2->warbleTone = nullptr;
                    break;
                case PULSE_TONE_ONE_SEC:
                    pToneGen2->pulseTone = std::make_unique<PulseTone>(pToneGen2->sampleRate);
                    pToneGen2->pulseTone->setSecondGenerator(pToneGen2->secondGenerator);
                    pToneGen2->valueChanged = 1;
                    pToneGen2->pureTone = nullptr;
                    pToneGen2->warbleTone = nullptr;
                    break;
                case WARBLE_TONE:
                    pToneGen2->warbleTone = std::make_unique<WarbleTone>(pToneGen2->sampleRate);
                    pToneGen2->warbleTone->setSecondGenerator(pToneGen2->secondGenerator);
                    pToneGen2->valueChanged = 1;
                    pToneGen2->pureTone = nullptr;
                    pToneGen2->pulseTone = nullptr;
                    break;
                default:
                    break;
            }
            break;
        case TG_INTERCOM_VOLUME:
            pToneGen2->intercomVolume = value;
            pToneGen2->valueChanged = 1;
            break;
        default:
            printf("TGR %s", "error!!\n");
            res = USOUND_ERROR_TONE_GENERATOR_SET_PARAMETER_ERROR;
            break;
    }

    return res;

}

extern "C" float tone_generator_getValue(int param) {
    if (pToneGen == nullptr) {
        return 0.0;
    }

    switch (param & MASK_PARAM) {
        case TG_BYPASS:
            return (float) pToneGen->bypass;
        case TG_FREQ:
            return pToneGen->freq;
        case TG_PAN:
            return (float) pToneGen->pan;
        case TG_GAIN:
            return pToneGen->gain;
        case TG_TONE_TYPE:
            return pToneGen->toneType;
        case TG_INTERCOM_VOLUME:
            return pToneGen->intercomVolume;
        default:
            printf("TGR %s", "error!!\n");
            return 0.0;
    }
}

extern "C" float second_tone_generator_getValue(int param) {
    if (pToneGen2 == nullptr) {
        return 0.0;
    }

    switch (param & MASK_PARAM) {
        case TG_BYPASS:
            return (float) pToneGen2->bypass;
        case TG_FREQ:
            return pToneGen2->freq;
        case TG_PAN:
            return (float) pToneGen2->pan;
        case TG_GAIN:
            return pToneGen2->gain;
        case TG_TONE_TYPE:
            return pToneGen2->toneType;
        case TG_INTERCOM_VOLUME:
            return pToneGen2->intercomVolume;
        default:
            printf("TGR %s", "error!!\n");
            return 0.0;
    }

}

extern "C" void tone_generator_is_instantiated() {
    //Check if there is an instance of any of the generators
    if (pToneGen->pureTone || pToneGen->pulseTone || pToneGen->warbleTone) {
        pToneGen->toneInstanceExists = 1;
        update_tone_generator_params();
    }
    else {
        pToneGen->toneInstanceExists = 0;
    }
}

extern "C" void second_tone_generator_is_instantiated() {
    //Check if there is an instance of any of the generators
    if (pToneGen2->pureTone || pToneGen2->pulseTone || pToneGen2->warbleTone) {
        pToneGen2->toneInstanceExists = 1;
        update_second_tone_generator_params();
    }
    else {
        pToneGen2->toneInstanceExists = 0;
    }
}

extern "C" void tone_generator_interval_process(float* data, int buffer_size) {

    tone_generator_is_instantiated();

    if (pToneGen->toneInstanceExists) {

        if (!tone_generator_is_bypassed()) {

            switch (pToneGen->toneType) {
                case CONTINUOUS_TONE:
                    pToneGen->pureTone->genSignal(data, buffer_size);
                    break;
                case PULSE_TONE_HALF_SEC:
                    pToneGen->pulseTone->genSignal(data, buffer_size);
                    break;
                case PULSE_TONE_ONE_SEC:
                    pToneGen->pulseTone->genSignal(data, buffer_size);
                    break;
                case WARBLE_TONE:
                    pToneGen->warbleTone->genSignal(data, buffer_size);
                    break;
            }
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

extern "C" void second_tone_generator_interval_process(float* data, int buffer_size) {

    second_tone_generator_is_instantiated();

    if (pToneGen2->toneInstanceExists) {

        if (!second_tone_generator_is_bypassed()) {

            switch (pToneGen2->toneType) {
                case CONTINUOUS_TONE:
                    pToneGen2->pureTone->genSignal(data, buffer_size);
                    break;
                case PULSE_TONE_HALF_SEC:
                    pToneGen2->pulseTone->genSignal(data, buffer_size);
                    break;
                case PULSE_TONE_ONE_SEC:
                    pToneGen2->pulseTone->genSignal(data, buffer_size);
                    break;
                case WARBLE_TONE:
                    pToneGen2->warbleTone->genSignal(data, buffer_size);
                    break;
            }
        }

    }

}

extern "C" void update_tone_generator_params() {

    if (pToneGen->valueChanged) {

        switch (pToneGen->toneType) {

            case CONTINUOUS_TONE:
                if (pToneGen->pureTone->getFreq() != pToneGen->freq) { pToneGen->pureTone->setFreq(pToneGen->freq); }
                if (pToneGen->pureTone->getChannel() != pToneGen->pan) { pToneGen->pureTone->setChannel(pToneGen->pan); }
                if (pToneGen->pureTone->getGain() != pToneGen->gain) { pToneGen->pureTone->setGain(pToneGen->gain); }
                if (pToneGen->pureTone->getInitGain() != pToneGen->initGain) { pToneGen->pureTone->setInitGain(pToneGen->initGain); }
                if (pToneGen->pureTone->getInterval() != pToneGen->interval) { pToneGen->pureTone->setInterval(pToneGen->interval); }
                if (pToneGen->pureTone->getIntercomVolume() != pToneGen->intercomVolume) { pToneGen->pureTone->setIntercomVolume(pToneGen->intercomVolume); }
                break;
            case PULSE_TONE_HALF_SEC:
                if (pToneGen->pulseTone->getFreq() != pToneGen->freq) { pToneGen->pulseTone->setFreq(pToneGen->freq); }
                if (pToneGen->pulseTone->getChannel() != pToneGen->pan) { pToneGen->pulseTone->setChannel(pToneGen->pan); }
                if (pToneGen->pulseTone->getGain() != pToneGen->gain) { pToneGen->pulseTone->setGain(pToneGen->gain); }
                //if (pToneGen->pulseTone->getInitGain() != pToneGen->initGain) { pToneGen->pulseTone->setInitGain(pToneGen->initGain); }
                if (pToneGen->pulseTone->getIntercomVolume() != pToneGen->intercomVolume) { pToneGen->pulseTone->setIntercomVolume(pToneGen->intercomVolume); }
                break;
            case PULSE_TONE_ONE_SEC:
                if (pToneGen->pulseTone->getFreq() != pToneGen->freq) { pToneGen->pulseTone->setFreq(pToneGen->freq); }
                if (pToneGen->pulseTone->getChannel() != pToneGen->pan) { pToneGen->pulseTone->setChannel(pToneGen->pan); }
                if (pToneGen->pulseTone->getGain() != pToneGen->gain) { pToneGen->pulseTone->setGain(pToneGen->gain); }
                //if (pToneGen->pulseTone->getInitGain() != pToneGen->initGain) { pToneGen->pulseTone->setInitGain(pToneGen->initGain); }
                if (pToneGen->pulseTone->getIntercomVolume() != pToneGen->intercomVolume) { pToneGen->pulseTone->setIntercomVolume(pToneGen->intercomVolume); }
                break;
            case WARBLE_TONE:
                if (pToneGen->warbleTone->getFreq() != pToneGen->freq) { pToneGen->warbleTone->setFreq(pToneGen->freq); }
                if (pToneGen->warbleTone->getChannel() != pToneGen->pan) { pToneGen->warbleTone->setChannel(pToneGen->pan); }
                if (pToneGen->warbleTone->getGain() != pToneGen->gain) { pToneGen->warbleTone->setGain(pToneGen->gain); }
                if (pToneGen->warbleTone->getInitGain() != pToneGen->initGain) { pToneGen->warbleTone->setInitGain(pToneGen->initGain); }
                if (pToneGen->warbleTone->getInterval() != pToneGen->interval) { pToneGen->warbleTone->setInterval(pToneGen->interval); }
                if (pToneGen->warbleTone->getIntercomVolume() != pToneGen->intercomVolume) { pToneGen->warbleTone->setIntercomVolume(pToneGen->intercomVolume); }
                break;

        }

        pToneGen->valueChanged = 0;
    }
}

extern "C" void update_second_tone_generator_params() {

    if (pToneGen2->valueChanged) {

        switch (pToneGen2->toneType) {

            case CONTINUOUS_TONE:
                if (pToneGen2->pureTone->getFreq() != pToneGen2->freq) { pToneGen2->pureTone->setFreq(pToneGen2->freq); }
                if (pToneGen2->pureTone->getChannel() != pToneGen2->pan) { pToneGen2->pureTone->setChannel(pToneGen2->pan); }
                if (pToneGen2->pureTone->getGain() != pToneGen2->gain) { pToneGen2->pureTone->setGain(pToneGen2->gain); }
                if (pToneGen2->pureTone->getInitGain() != pToneGen2->initGain) { pToneGen2->pureTone->setInitGain(pToneGen2->initGain); }
                if (pToneGen2->pureTone->getInterval() != pToneGen2->interval) { pToneGen2->pureTone->setInterval(pToneGen2->interval); }
                if (pToneGen2->pureTone->getIntercomVolume() != pToneGen2->intercomVolume) { pToneGen2->pureTone->setIntercomVolume(pToneGen2->intercomVolume); }
                break;
            case PULSE_TONE_HALF_SEC:
                if (pToneGen2->pulseTone->getFreq() != pToneGen2->freq) { pToneGen2->pulseTone->setFreq(pToneGen2->freq); }
                if (pToneGen2->pulseTone->getChannel() != pToneGen2->pan) { pToneGen2->pulseTone->setChannel(pToneGen2->pan); }
                if (pToneGen2->pulseTone->getGain() != pToneGen2->gain) { pToneGen2->pulseTone->setGain(pToneGen2->gain); }
                //if (pToneGen2->pulseTone->getInitGain() != pToneGen2->initGain) { pToneGen2->pulseTone->setInitGain(pToneGen2->initGain); }
                if (pToneGen2->pulseTone->getIntercomVolume() != pToneGen2->intercomVolume) { pToneGen2->pulseTone->setIntercomVolume(pToneGen2->intercomVolume); }
                break;
            case PULSE_TONE_ONE_SEC:
                if (pToneGen2->pulseTone->getFreq() != pToneGen2->freq) { pToneGen2->pulseTone->setFreq(pToneGen2->freq); }
                if (pToneGen2->pulseTone->getChannel() != pToneGen2->pan) { pToneGen2->pulseTone->setChannel(pToneGen2->pan); }
                if (pToneGen2->pulseTone->getGain() != pToneGen2->gain) { pToneGen2->pulseTone->setGain(pToneGen2->gain); }
                //if (pToneGen2->pulseTone->getInitGain() != pToneGen2->initGain) { pToneGen2->pulseTone->setInitGain(pToneGen2->initGain); }
                if (pToneGen2->pulseTone->getIntercomVolume() != pToneGen2->intercomVolume) { pToneGen2->pulseTone->setIntercomVolume(pToneGen2->intercomVolume); }
                break;
            case WARBLE_TONE:
                if (pToneGen2->warbleTone->getFreq() != pToneGen2->freq) { pToneGen2->warbleTone->setFreq(pToneGen2->freq); }
                if (pToneGen2->warbleTone->getChannel() != pToneGen2->pan) { pToneGen2->warbleTone->setChannel(pToneGen2->pan); }
                if (pToneGen2->warbleTone->getGain() != pToneGen2->gain) { pToneGen2->warbleTone->setGain(pToneGen2->gain); }
                if (pToneGen2->warbleTone->getInitGain() != pToneGen2->initGain) { pToneGen2->warbleTone->setInitGain(pToneGen2->initGain); }
                if (pToneGen2->warbleTone->getInterval() != pToneGen2->interval) { pToneGen2->warbleTone->setInterval(pToneGen2->interval); }
                if (pToneGen2->warbleTone->getIntercomVolume() != pToneGen2->intercomVolume) { pToneGen2->warbleTone->setIntercomVolume(pToneGen2->intercomVolume); }
                break;

        }
    }

}

extern "C" int tone_generator_is_bypassed() {

    if (pToneGen->toneInstanceExists) {

        switch (pToneGen->toneType) {

            case CONTINUOUS_TONE:
                return static_cast<int>(pToneGen->pureTone->isBypassed());
            case PULSE_TONE_HALF_SEC:
                return static_cast<int>(pToneGen->pulseTone->isBypassed());
            case PULSE_TONE_ONE_SEC:
                return static_cast<int>(pToneGen->pulseTone->isBypassed());
            case WARBLE_TONE:
                return static_cast<int>(pToneGen->warbleTone->isBypassed());

        }

    } else {
        return 1;
    }

}

extern "C" int second_tone_generator_is_bypassed() {

    if (pToneGen2->toneInstanceExists) {

        switch (pToneGen2->toneType) {

            case CONTINUOUS_TONE:
                return static_cast<int>(pToneGen2->pureTone->isBypassed());
            case PULSE_TONE_HALF_SEC:
                return static_cast<int>(pToneGen2->pulseTone->isBypassed());
            case PULSE_TONE_ONE_SEC:
                return static_cast<int>(pToneGen2->pulseTone->isBypassed());
            case WARBLE_TONE:
                return static_cast<int>(pToneGen2->warbleTone->isBypassed());

        }

    } else {
        return 1;
    }

}

extern "C" void tone_generator_free() {
    pToneGen->pureTone = nullptr;
    pToneGen->pulseTone = nullptr;
    pToneGen->warbleTone = nullptr;
    delete pToneGen;
    pToneGen = nullptr;
}

extern "C" void second_tone_generator_free() {
    pToneGen2->pureTone = nullptr;
    pToneGen2->pulseTone = nullptr;
    pToneGen2->warbleTone = nullptr;
    delete pToneGen2;
    pToneGen2 = nullptr;
}