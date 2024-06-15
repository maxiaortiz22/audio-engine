#include <stdlib.h>
#include "filter.h"

//Initialize filter
Filter *FilterInit(double rate) {
    Filter *filter = (Filter *) malloc(sizeof(Filter));
    filter->fs = rate;
    filter->gain = 1.0f;
    filter->freq = 100.0f;
    filter->q = 1.0f;
    filter->enable = 0.0f;
    filter->iType = 0;

    //Interpolations
    filter->freqInter = pow(10.0f, FREQ_INTER_DEC_SECOND / (float) rate);
    filter->gainInter = pow(10.0f, 0.05f * GAIN_INTER_DB_SECOND) / (float) rate;
    filter->QInter = pow(10.0f, Q_INTER_DEC_SECOND / (float) rate);

    return filter;
}

//Destroy a filter instance
void FilterClean(Filter *filter) {
    free(filter);
}

//Clean buffers
void flushBuffers(Buffers *buf) {
    buf->buf_0 = 0.0;
    buf->buf_1 = 0.0;
    buf->buf_2 = 0.0;
    buf->buf_e0 = 0.0;
    buf->buf_e1 = 0.0;
    buf->buf_e2 = 0.0;
}
