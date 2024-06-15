#ifndef __uSound__frequency_cut__
#define __uSound__frequency_cut__


#include "engine_params.h"
#include "usoundlib_params.h"

#ifdef __cplusplus
extern "C" {
#endif
    
    UsoundResult frequency_cut_alloc(float sr);
    void frequency_cut_free();
    void frequency_cut_process(float *data, int buffer_size);
    void low_pass_process(float *data, int buffer_size, int channel);
    UsoundResult frequency_cut_setValue(int param, float val);
    float frequency_cut_getValue(int param);
    
#ifdef __cplusplus
};
#endif

#endif /* defined(__uSound__frequency_cut__) */

