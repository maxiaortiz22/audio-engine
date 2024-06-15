#include "frequency_cut.h"
#include <stdlib.h>
#include <db.h>

#include "filter.h"

#include "ulog.h"

#define FREQ_CUT_BANDS 2
#define FREQ_CUT_CHANNELS 2

#define HIGHPASS 0
#define LOWPASS 1

#define FC_INPUT_GAIN 0.0001
#define FC_OUTPUT_GAIN 10000.0

UsoundResult setFilterParam(int band, int param, float val);
float getFilterParam(int band, int param);
void recalcCoefs(int band);

struct low_pass {
    float bandFreq;
    float bandQ;
    float bandActive;
    int bandType;

    Filter *filter;
    Buffers buf;
};

typedef struct freq_cut_internals {
    int bypass;
    
    float sampleRate;
    int channelType;


    float bandFreq[FREQ_CUT_BANDS];
    float bandQ[FREQ_CUT_BANDS];
    float bandActive[FREQ_CUT_BANDS];
    int bandType[FREQ_CUT_BANDS];
    
    Filter *filter[FREQ_CUT_BANDS][FREQ_CUT_CHANNELS];
    Buffers buf[FREQ_CUT_BANDS][FREQ_CUT_CHANNELS];

    struct low_pass * lowPass;
    int lpBypass;
}FreqCutInternals;

static FreqCutInternals * freqCutInternals = NULL;

void recalcCoefs(int band) {
    int channel;
    for (channel = 0; channel < FREQ_CUT_CHANNELS; channel++) {
        freqCutInternals->filter[band][channel]->freq = freqCutInternals->bandFreq[band];
        freqCutInternals->filter[band][channel]->q = freqCutInternals->bandQ[band];
        freqCutInternals->filter[band][channel]->iType = freqCutInternals->bandType[band];
        freqCutInternals->filter[band][channel]->enable = freqCutInternals->bandActive[band];
        calcCoefs(freqCutInternals->filter[band][channel], 1,
                  freqCutInternals->bandFreq[band],
                  freqCutInternals->bandQ[band],
                  freqCutInternals->bandType[band],
                  freqCutInternals->bandActive[band]
                  );
    }
}

void recalcLowPassCoefs() {

    freqCutInternals->lowPass->filter->freq = freqCutInternals->lowPass->bandFreq;
    freqCutInternals->lowPass->filter->q = freqCutInternals->lowPass->bandQ;
    freqCutInternals->lowPass->filter->iType = freqCutInternals->lowPass->bandType;
    freqCutInternals->lowPass->filter->enable = freqCutInternals->lowPass->bandActive;
    calcCoefs(freqCutInternals->lowPass->filter, 1,
              freqCutInternals->lowPass->bandFreq,
              freqCutInternals->lowPass->bandQ,
              freqCutInternals->lowPass->bandType,
              freqCutInternals->lowPass->bandActive
    );

}

UsoundResult frequency_cut_alloc(float sampleRate) {
    int ch, bd;
    
    if (freqCutInternals == NULL) {
        freqCutInternals = (FreqCutInternals *)malloc(sizeof(FreqCutInternals));
    }
    
    freqCutInternals->sampleRate = sampleRate;
    freqCutInternals->bypass = 1;
    freqCutInternals->channelType = STEREO_CHANNEL;
    
    freqCutInternals->bandFreq[HIGHPASS] = 300.0f;
    freqCutInternals->bandType[HIGHPASS] = F_HPF_ORDER_4;
    freqCutInternals->bandActive[HIGHPASS] = 1;
    freqCutInternals->bandQ[HIGHPASS] = 0.6045f;
    
    freqCutInternals->bandFreq[LOWPASS] = 4000.0f;
    freqCutInternals->bandType[LOWPASS] = F_LPF_ORDER_4;
    freqCutInternals->bandActive[LOWPASS] = 1;
    freqCutInternals->bandQ[LOWPASS] = 0.6045f;
    
    for(bd = 0; bd < FREQ_CUT_BANDS; bd++) {
        for(ch = 0; ch < FREQ_CUT_CHANNELS; ch++) {
            freqCutInternals->filter[bd][ch] = FilterInit(freqCutInternals->sampleRate);
            flushBuffers(&freqCutInternals->buf[bd][ch]);
        }
        recalcCoefs(bd);
    }

    freqCutInternals->lowPass = (struct low_pass *)malloc(sizeof(struct low_pass));
    freqCutInternals->lowPass->filter = FilterInit((double) freqCutInternals->sampleRate);
    flushBuffers(&freqCutInternals->lowPass->buf);
    freqCutInternals->lowPass->bandFreq = 4000.0F;
    freqCutInternals->lowPass->bandType = F_LPF_ORDER_2;
    freqCutInternals->lowPass->bandActive = 1;
    freqCutInternals->lowPass->bandQ = 1.0F;
    freqCutInternals->lpBypass = 1;

    recalcLowPassCoefs();
    return USOUND_SUCCESS;
}

void frequency_cut_free() {
    if (freqCutInternals == NULL) {
        return;
    }
    
    int bd, ch;
    for(bd = 0; bd < FREQ_CUT_BANDS; bd++) {
        for(ch = 0; ch < FREQ_CUT_CHANNELS; ch++) {
            FilterClean(freqCutInternals->filter[bd][ch]);
        }
    }
    free(freqCutInternals);
    freqCutInternals = NULL;
}

void frequency_cut_process(float *data, int buffer_size) {
    if (freqCutInternals == NULL) {
        return;
    }
    int bypass = freqCutInternals->bypass == 1 ? 1 : 0;
    int pos, ch, bd;
    double sample[FREQ_CUT_CHANNELS];
    if (!bypass) {
        for (pos = 0; pos < buffer_size; pos+=2) {
            sample[0] = (double)data[pos];
            sample[1] = (double)data[pos+1];

//                DENORMAL_TO_ZERO(sample[ch]);
//                sample[ch] *= FC_INPUT_GAIN;
            switch(freqCutInternals->channelType){
                case LEFT_CHANNEL:
                    for(bd = 0; bd < FREQ_CUT_BANDS; bd++) {
                        computeFilter(freqCutInternals->filter[bd][0], &freqCutInternals->buf[bd][0], &sample[0]);
                    }
                    data[pos] = (float) sample[0];
                    break;
                case RIGHT_CHANNEL:
                    for(bd = 0; bd < FREQ_CUT_BANDS; bd++) {
                        computeFilter(freqCutInternals->filter[bd][1], &freqCutInternals->buf[bd][1], &sample[1]);
                    }
                    data[pos + 1] = (float)  sample[1];
                    break;
                case STEREO_CHANNEL:
                    for(bd = 0; bd < FREQ_CUT_BANDS; bd++) {
                            computeFilter(freqCutInternals->filter[bd][0], &freqCutInternals->buf[bd][0], &sample[0]);
                            computeFilter(freqCutInternals->filter[bd][1], &freqCutInternals->buf[bd][1], &sample[1]);
                    }
                    data[pos] = (float) sample[0];
                    data[pos + 1] = (float) sample[1] ;
                    break;
                default:
                    break;
            }
//                sample[ch] *= FC_OUTPUT_GAIN;
        }
    }
}


void low_pass_process(float *data, int buffer_size, int channel) {
    if (freqCutInternals == NULL) {
        return;
    }
    int bypass = freqCutInternals->lpBypass == 1 ? 1 : 0;
    int pos;
    double sample;
    if (!bypass) {
        for (pos = 0; pos < buffer_size; pos+=2) {
            if (channel == LEFT_CHANNEL){
                sample = (double)data[pos];
            }
            else {
                sample = (double)data[pos+1];
            }

            sample *= FC_INPUT_GAIN;
            computeFilter(freqCutInternals->lowPass->filter, &freqCutInternals->lowPass->buf, &sample);
            sample *= FC_OUTPUT_GAIN;


            switch(channel) {
                case LEFT_CHANNEL:
                    data[pos] = (float) sample;
                    break;
                case RIGHT_CHANNEL:
                    data[pos + 1] = (float) sample;
                    break;
                case STEREO_CHANNEL:
                    data[pos] = (float)  sample;
                    data[pos + 1] = (float) sample;
                    break;
                default:
                    break;
            }

        }
    }
}


UsoundResult frequency_cut_setValue(int param, float val) {
    UsoundResult res;
    if (freqCutInternals == NULL) {
        res = USOUND_ERROR_FREQUENCY_CUT_IS_NULL;
        goto abort_frequency_cut_setValue;
    }
    switch (param & MASK_BAND) {
        case FC_LOWPASS:
            res = setFilterParam(LOWPASS, param, val);
            break;
        case FC_HIGHPASS:
            res = setFilterParam(HIGHPASS, param, val);
            break;
        default:
            res = USOUND_SUCCESS;
            switch (param & MASK_PARAM) {
                case FC_BYPASS:
                    uLogDspFct_d("[SET]frequency_cut->bypass : %s\n" ,(val == 1) ? "true" : "false");
                    freqCutInternals->bypass = (val == 1) ? 1 : 0;
                    break;
                case FC_LP_BYPASS:
                    uLogDspFct_d("[SET]frequency_cut->lpBypass : %s\n" ,(val == 1) ? "true" : "false");
                    freqCutInternals->lpBypass = (val == 1) ? 1 : 0;
                    break;
                case FC_CHANNEL_TYPE:
                    uLogDspFct_d("[SET]frequency_cut->channelType : %s\n", val );
                    freqCutInternals->channelType = (int) val;
                    break;
                default:
                    res = USOUND_ERROR_FREQUENCY_CUT_SET_PARAMETER_ERROR;
                    uLogDspFct_d("error!!\n");
                    goto abort_frequency_cut_setValue;
            }
            break;
    }
    return res;
abort_frequency_cut_setValue:
    return res;
}

UsoundResult setFilterParam(int band, int param, float val) {
    UsoundResult res;
    if (freqCutInternals == NULL) {
        res = USOUND_ERROR_FREQUENCY_CUT_IS_NULL;
        goto abort_setFilterParam;
    }
    res = USOUND_SUCCESS;
    switch (param & MASK_PARAM) {
        case FC_FILTER_FREQ:
            uLogDspFct_d("[SET]frequency_cut->%s->freq : %6.1f\n", band == LOWPASS ? "lowpass" : "highpass", val);
            freqCutInternals->bandFreq[band] = val;
            freqCutInternals->lowPass->bandFreq = val;
            break;
        case FC_FILTER_Q_PARAM:
            uLogDspFct_d("[SET]frequency_cut->%s->qParam : %2.5f\n", band == LOWPASS ? "lowpass" : "highpass", val);
            freqCutInternals->bandQ[band] = val;
            freqCutInternals->lowPass->bandQ = val;
            break;
        case FC_FILTER_TYPE:
            uLogDspFct_d("[SET]frequency_cut->%s->filterType : %2.0f\n", band == LOWPASS ? "lowpass" : "highpass", val);
            freqCutInternals->bandType[band] = (int) val;
            freqCutInternals->lowPass->bandType =  (int) val;
            break;
        case FC_FILTER_ENABLED:
            uLogDspFct_d("[SET]frequency_cut->%s->Enabled : %s\n", band == LOWPASS ? "lowpass" : "highpass", val == 1 ? "true" : "false");
            freqCutInternals->bandActive[band] = val == 1 ? 1 : 0;
            freqCutInternals->lowPass->bandActive = val == 1 ? 1 : 0;
            break;
        default:
            res = USOUND_ERROR_FREQUENCY_CUT_SET_PARAMETER_ERROR;
            uLogDspFct_e("error!!\n");
            goto abort_setFilterParam;
    }
    recalcCoefs(band);
    recalcLowPassCoefs();
    return res;
abort_setFilterParam:
    return res;
}

float frequency_cut_getValue(int param) {
    //    TODO put requested value in new parameter variable to return UsoundResult
    if (freqCutInternals == NULL) {
        return 0;
    }
    switch (param & MASK_BAND) {
        case FC_LOWPASS: return getFilterParam(LOWPASS, param);
        case FC_HIGHPASS: return getFilterParam(HIGHPASS, param);
        default:
            switch (param & MASK_PARAM) {
                case FC_BYPASS:
                    uLogDspFct_d("[GET]frequency_cut->bypass : %s\n" ,(freqCutInternals->bypass == 1) ? "true" : "false");
                    return freqCutInternals->bypass;
                case FC_CHANNEL_TYPE:
                    uLogDspFct_d("[GET]frequency_cut->channelType : %s\n" , freqCutInternals->channelType);
                    return freqCutInternals->channelType;
                default:
                    uLogDspFct_e("error!!\n");
                    break;
            }
            break;
    }
    return 0;
}

float getFilterParam(int band, int param) {
    //    TODO put requested value in new parameter variable to return UsoundResult
    if (freqCutInternals == NULL) {
        return 0;
    }
    switch (param & MASK_PARAM) {
        case FC_FILTER_FREQ:
            uLogDspFct_d("[GET]frequency_cut->%s->freq : %6.1f\n", band == LOWPASS ? "lowpass" : "highpass",
                         freqCutInternals->bandFreq[band]);
            return freqCutInternals->bandFreq[band];
        case FC_FILTER_Q_PARAM:
            uLogDspFct_d("[GET]frequency_cut->%s->qParam : %2.5f\n", band == LOWPASS ? "lowpass" : "highpass",
                         freqCutInternals->bandQ[band]);
            return freqCutInternals->bandQ[band];
        case FC_FILTER_TYPE:
            uLogDspFct_d("[GET]frequency_cut->%s->filterType : %2.0f\n", band == LOWPASS ? "lowpass" : "highpass",
                         freqCutInternals->bandType[band]);
            return freqCutInternals->bandType[band];
        case FC_FILTER_ENABLED:
            uLogDspFct_d("[GET]frequency_cut->%s->Enabled : %s\n", band == LOWPASS ? "lowpass" : "highpass",
                         freqCutInternals->bandActive[band] == 1 ? "true" : "false");
            return freqCutInternals->bandActive[band];
        default:
            uLogDspFct_e("error!!\n");
            break;
    }
    return 0;
}

