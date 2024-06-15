//
// Created by alex on 22/05/17.
//

#ifndef USOUND_ANDROID_ULOG_H
#define USOUND_ANDROID_ULOG_H

//#define __ULOG_CORE__
//#define __ULOG_ENG__
//#define __ULOG_IO__
//#define __ULOG_AUDIO_DEVICE__
//#define __ULOG_OPENSL_ES__
//#define __ULOG_DSP_COM__
//#define __ULOG_DSP_EQU__
//#define __ULOG_DSP_VU__
//#define __ULOG_DSP_EXP__
//#define __ULOG_DSP_FCT__
//#define __ULOG_DSP_LMR__
//#define __ULOG_DSP_MSM__
//#define __ULOG_DSP_NGT__
//#define __ULOG_DSP_TGR__
//#define __ULOG_DPS_FFT__

// DEFAULT LOGGING
#if defined __ANDROID__ && defined __DEBUG__
    #include <android/log.h>
    #include <string.h>
    #define FILETAG (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1  : __FILE__)
    #define GETLINE_(x) #x
    #define GETLINE(x) GETLINE_(x)
#endif

// USOUND CORE LOGGING
#if defined __ANDROID__ && defined __DEBUG__ && defined __ULOG_CORE__
    #define uLogCore_d(...)  __android_log_print(ANDROID_LOG_DEBUG, FILETAG , "CORE:-l" GETLINE(__LINE__) ": " __VA_ARGS__)
    #define uLogCore_i(...)  __android_log_print(ANDROID_LOG_INFO, FILETAG,  "CORE:-l" GETLINE(__LINE__) ": " __VA_ARGS__)
    #define uLogCore_e(...)  __android_log_print(ANDROID_LOG_ERROR, FILETAG,  "CORE:-l" GETLINE(__LINE__) ": " __VA_ARGS__)
    #define uLogCore_w(...)  __android_log_print(ANDROID_LOG_WARN, FILETAG, "CORE:-l" GETLINE(__LINE__) ": " __VA_ARGS__)
#else
    #define uLogCore_d(...)
    #define uLogCore_i(...)
    #define uLogCore_e(...)
    #define uLogCore_w(...)
#endif

// USOUND ENGINE LOGGING
#if defined __ANDROID__ && defined __DEBUG__ && defined __ULOG_ENG__
    #define uLogEng_d(...)  __android_log_print(ANDROID_LOG_DEBUG, FILETAG , "ENG -l" GETLINE(__LINE__) ": " __VA_ARGS__)
    #define uLogEng_i(...)  __android_log_print(ANDROID_LOG_INFO, FILETAG,  "ENG -l" GETLINE(__LINE__) ": " __VA_ARGS__)
    #define uLogEng_e(...)  __android_log_print(ANDROID_LOG_ERROR, FILETAG,  "ENG -l" GETLINE(__LINE__) ": " __VA_ARGS__)
    #define uLogEng_w(...)  __android_log_print(ANDROID_LOG_WARN, FILETAG, "ENG -l" GETLINE(__LINE__) ": " __VA_ARGS__)
#else
    #define uLogEng_d(...)
    #define uLogEng_i(...)
    #define uLogEng_e(...)
    #define uLogEng_w(...)
#endif

// USOUND IO LOGGING
#if defined __ANDROID__ && defined __DEBUG__ && defined __ULOG_IO__
    #define uLogIo_d(...)  __android_log_print(ANDROID_LOG_DEBUG, FILETAG , "IO -l" GETLINE(__LINE__) ": " __VA_ARGS__)
    #define uLogIo_i(...)  __android_log_print(ANDROID_LOG_INFO, FILETAG,  "IO -l" GETLINE(__LINE__) ": " __VA_ARGS__)
    #define uLogIo_e(...)  __android_log_print(ANDROID_LOG_ERROR, FILETAG,  "IO -l" GETLINE(__LINE__) ": " __VA_ARGS__)
    #define uLogIo_w(...)  __android_log_print(ANDROID_LOG_WARN, FILETAG, "IO -l" GETLINE(__LINE__) ": " __VA_ARGS__)
#else
    #define uLogIo_d(...)
    #define uLogIo_i(...)
    #define uLogIo_e(...)
    #define uLogIo_w(...)
#endif

// USOUND AUDIO_DEVICE LOGGING
#if defined __ANDROID__ && defined __DEBUG__ && defined __ULOG_AUDIO_DEVICE__
    #define uLogAudioDevice_d(...)  __android_log_print(ANDROID_LOG_DEBUG, FILETAG , "AUDIO_DEVICE -l" GETLINE(__LINE__) ": " __VA_ARGS__)
    #define uLogAudioDevice_i(...)  __android_log_print(ANDROID_LOG_INFO, FILETAG,  "AUDIO_DEVICE -l" GETLINE(__LINE__) ": " __VA_ARGS__)
    #define uLogAudioDevice_e(...)  __android_log_print(ANDROID_LOG_ERROR, FILETAG,  "AUDIO_DEVICE -l" GETLINE(__LINE__) ": " __VA_ARGS__)
    #define uLogAudioDevice_w(...)  __android_log_print(ANDROID_LOG_WARN, FILETAG, "AUDIO_DEVICE -l" GETLINE(__LINE__) ": " __VA_ARGS__)
#else
    #define uLogAudioDevice_d(...)
    #define uLogAudioDevice_i(...)
    #define uLogAudioDevice_e(...)
    #define uLogAudioDevice_w(...)
#endif

// USOUND OPENSL_ES LOGGING
#if defined __ANDROID__ && defined __DEBUG__ && defined __ULOG_OPENSL_ES__
    #define uLogOpenSL_ES_d(...)  __android_log_print(ANDROID_LOG_DEBUG, FILETAG , "OPENSL_ES -l" GETLINE(__LINE__) ": " __VA_ARGS__)
    #define uLogOpenSL_ES_i(...)  __android_log_print(ANDROID_LOG_INFO, FILETAG , "OPENSL_ES -l" GETLINE(__LINE__) ": " __VA_ARGS__)
    #define uLogOpenSL_ES_e(...)  __android_log_print(ANDROID_LOG_ERROR, FILETAG,  "OPENSL_ES -l" GETLINE(__LINE__) ": " __VA_ARGS__)
    #define uLogOpenSL_ES_w(...)  __android_log_print(ANDROID_LOG_WARN, FILETAG, "OPENSL_ES -l" GETLINE(__LINE__) ": " __VA_ARGS__)
#else
    #define uLogOpenSL_ES_d(...)
    #define uLogOpenSL_ES_i(...)
    #define uLogOpenSL_ES_e(...)
    #define uLogOpenSL_ES_w(...)
#endif

// USOUND DSP COMPRESSOR LOGGING
#if defined __ANDROID__ && defined __DEBUG__ && defined __ULOG_DSP_COM__
    #define uLogDspCom_d(...)  __android_log_print(ANDROID_LOG_DEBUG, FILETAG , "DSP_COM -l" GETLINE(__LINE__) ": " __VA_ARGS__)
    #define uLogDspCom_i(...)  __android_log_print(ANDROID_LOG_INFO, FILETAG , "DSP_COM -l" GETLINE(__LINE__) ": " __VA_ARGS__)
    #define uLogDspCom_e(...)  __android_log_print(ANDROID_LOG_ERROR, FILETAG,  "DSP_COM -l" GETLINE(__LINE__) ": " __VA_ARGS__)
    #define uLogDspCom_w(...)  __android_log_print(ANDROID_LOG_WARN, FILETAG, "DSP_COM -l" GETLINE(__LINE__) ": " __VA_ARGS__)
#else
    #define uLogDspCom_d(...)
    #define uLogDspCom_i(...)
    #define uLogDspCom_e(...)
    #define uLogDspCom_w(...)
#endif

// USOUND DSP EQUALIZER LOGGING
#if defined __ANDROID__ && defined __DEBUG__ && defined __ULOG_DSP_EQU__
    #define uLogDspEqu_d(...)  __android_log_print(ANDROID_LOG_DEBUG, FILETAG , "DSP_EQU -l" GETLINE(__LINE__) ": " __VA_ARGS__)
    #define uLogDspEqu_i(...)  __android_log_print(ANDROID_LOG_INFO, FILETAG , "DSP_EQU -l" GETLINE(__LINE__) ": " __VA_ARGS__)
    #define uLogDspEqu_e(...)  __android_log_print(ANDROID_LOG_ERROR, FILETAG,  "DSP_EQU -l" GETLINE(__LINE__) ": " __VA_ARGS__)
    #define uLogDspEqu_w(...)  __android_log_print(ANDROID_LOG_WARN, FILETAG, "DSP_EQU -l" GETLINE(__LINE__) ": " __VA_ARGS__)
#else
    #define uLogDspEqu_d(...)
    #define uLogDspEqu_i(...)
    #define uLogDspEqu_e(...)
    #define uLogDspEqu_w(...)
#endif

// USOUND DSP EXPANDER LOGGING
#if defined __ANDROID__ && defined __DEBUG__ && defined __ULOG_DSP_EXP__
    #define uLogDspExp_d(...)  __android_log_print(ANDROID_LOG_DEBUG, FILETAG , "DSP_EXP -l" GETLINE(__LINE__) ": " __VA_ARGS__)
    #define uLogDspExp_i(...)  __android_log_print(ANDROID_LOG_INFO, FILETAG , "DSP_EXP -l" GETLINE(__LINE__) ": " __VA_ARGS__)
    #define uLogDspExp_e(...)  __android_log_print(ANDROID_LOG_ERROR, FILETAG,  "DSP_EXP -l" GETLINE(__LINE__) ": " __VA_ARGS__)
    #define uLogDspExp_w(...)  __android_log_print(ANDROID_LOG_WARN, FILETAG, "DSP_EXP -l" GETLINE(__LINE__) ": " __VA_ARGS__)
#else
    #define uLogDspExp_d(...)
    #define uLogDspExp_i(...)
    #define uLogDspExp_e(...)
    #define uLogDspExp_w(...)
#endif

// USOUND DSP FREQUENCY CUT LOGGING
#if defined __ANDROID__ && defined __DEBUG__ && defined __ULOG_DSP_FCT__
    #define uLogDspFct_d(...)  __android_log_print(ANDROID_LOG_DEBUG, FILETAG , "DSP_FCT -l" GETLINE(__LINE__) ": " __VA_ARGS__)
    #define uLogDspFct_i(...)  __android_log_print(ANDROID_LOG_INFO, FILETAG , "DSP_FCT -l" GETLINE(__LINE__) ": " __VA_ARGS__)
    #define uLogDspFct_e(...)  __android_log_print(ANDROID_LOG_ERROR, FILETAG,  "DSP_FCT -l" GETLINE(__LINE__) ": " __VA_ARGS__)
    #define uLogDspFct_w(...)  __android_log_print(ANDROID_LOG_WARN, FILETAG, "DSP_FCT -l" GETLINE(__LINE__) ": " __VA_ARGS__)
#else
    #define uLogDspFct_d(...)
    #define uLogDspFct_i(...)
    #define uLogDspFct_e(...)
    #define uLogDspFct_w(...)
#endif

// USOUND DSP LIMITER LOGGING
#if defined __ANDROID__ && defined __DEBUG__ && defined __ULOG_DSP_LMR__
    #define uLogDspLmr_d(...)  __android_log_print(ANDROID_LOG_DEBUG, FILETAG , "DSP_LMR -l" GETLINE(__LINE__) ": " __VA_ARGS__)
    #define uLogDspLmr_i(...)  __android_log_print(ANDROID_LOG_INFO, FILETAG , "DSP_LMR -l" GETLINE(__LINE__) ": " __VA_ARGS__)
    #define uLogDspLmr_e(...)  __android_log_print(ANDROID_LOG_ERROR, FILETAG,  "DSP_LMR -l" GETLINE(__LINE__) ": " __VA_ARGS__)
    #define uLogDspLmr_w(...)  __android_log_print(ANDROID_LOG_WARN, FILETAG, "DSP_LMR -l" GETLINE(__LINE__) ": " __VA_ARGS__)
#else
    #define uLogDspLmr_d(...)
    #define uLogDspLmr_i(...)
    #define uLogDspLmr_e(...)
    #define uLogDspLmr_w(...)
#endif

// USOUND DSP MS MATRIX LOGGING
#if defined __ANDROID__ && defined __DEBUG__ && defined __ULOG_DSP_MSM__
    #define uLogDspMsm_d(...)  __android_log_print(ANDROID_LOG_DEBUG, FILETAG , "DSP_MSM -l" GETLINE(__LINE__) ": " __VA_ARGS__)
    #define uLogDspMsm_i(...)  __android_log_print(ANDROID_LOG_INFO, FILETAG , "DSP_MSM -l" GETLINE(__LINE__) ": " __VA_ARGS__)
    #define uLogDspMsm_e(...)  __android_log_print(ANDROID_LOG_ERROR, FILETAG,  "DSP_MSM -l" GETLINE(__LINE__) ": " __VA_ARGS__)
    #define uLogDspMsm_w(...)  __android_log_print(ANDROID_LOG_WARN, FILETAG, "DSP_MSM -l" GETLINE(__LINE__) ": " __VA_ARGS__)
#else
    #define uLogDspMsm_d(...)
    #define uLogDspMsm_i(...)
    #define uLogDspMsm_e(...)
    #define uLogDspMsm_w(...)
#endif

// USOUND DSP NOISE GATE LOGGING
#if defined __ANDROID__ && defined __DEBUG__ && defined __ULOG_DSP_NGT__
    #define uLogDspNgt_d(...)  __android_log_print(ANDROID_LOG_DEBUG, FILETAG , "DSP_NGT -l" GETLINE(__LINE__) ": " __VA_ARGS__)
    #define uLogDspNgt_i(...)  __android_log_print(ANDROID_LOG_INFO, FILETAG , "DSP_NGT -l" GETLINE(__LINE__) ": " __VA_ARGS__)
    #define uLogDspNgt_e(...)  __android_log_print(ANDROID_LOG_ERROR, FILETAG,  "DSP_NGT -l" GETLINE(__LINE__) ": " __VA_ARGS__)
    #define uLogDspNgt_w(...)  __android_log_print(ANDROID_LOG_WARN, FILETAG, "DSP_NGT -l" GETLINE(__LINE__) ": " __VA_ARGS__)
#else
    #define uLogDspNgt_d(...)
    #define uLogDspNgt_i(...)
    #define uLogDspNgt_e(...)
    #define uLogDspNgt_w(...)
#endif

// USOUND DSP TONE GENERATOR LOGGING
#if defined __ANDROID__ && defined __DEBUG__ && defined __ULOG_DSP_TGR__
    #define uLogDspTgr_d(...)  __android_log_print(ANDROID_LOG_DEBUG, FILETAG , "DSP_TGR -l" GETLINE(__LINE__) ": " __VA_ARGS__)
    #define uLogDspTgr_i(...)  __android_log_print(ANDROID_LOG_INFO, FILETAG , "DSP_TGR -l" GETLINE(__LINE__) ": " __VA_ARGS__)
    #define uLogDspTgr_e(...)  __android_log_print(ANDROID_LOG_ERROR, FILETAG,  "DSP_TGR -l" GETLINE(__LINE__) ": " __VA_ARGS__)
    #define uLogDspTgr_w(...)  __android_log_print(ANDROID_LOG_WARN, FILETAG, "DSP_TGR -l" GETLINE(__LINE__) ": " __VA_ARGS__)
#else
    #define uLogDspTgr_d(...)
    #define uLogDspTgr_i(...)
    #define uLogDspTgr_e(...)
    #define uLogDspTgr_w(...)
#endif


// USOUND DSP VUMETER LOGGING
#if defined __ANDROID__ && defined __DEBUG__ && defined __ULOG_DSP_VU__
#define uLogDspVU_d(...)  __android_log_print(ANDROID_LOG_DEBUG, FILETAG , "DSP_VU -l" GETLINE(__LINE__) ": " __VA_ARGS__)
#define uLogDspVU_i(...)  __android_log_print(ANDROID_LOG_INFO, FILETAG , "DSP_VU -l" GETLINE(__LINE__) ": " __VA_ARGS__)
#define uLogDspVU_e(...)  __android_log_print(ANDROID_LOG_ERROR, FILETAG,  "DSP_VU -l" GETLINE(__LINE__) ": " __VA_ARGS__)
#define uLogDspVU_w(...)  __android_log_print(ANDROID_LOG_WARN, FILETAG, "DSP_VU -l" GETLINE(__LINE__) ": " __VA_ARGS__)
#else
#define uLogDspVU_d(...)
    #define uLogDspVU_i(...)
    #define uLogDspVU_e(...)
    #define uLogDspVU_w(...)
#endif

// USOUND DSP FFT LOGGING
#if defined __ANDROID__ && defined __DEBUG__ && defined __ULOG_DPS_FFT__
    #define uLogDspFft_d(...)  __android_log_print(ANDROID_LOG_DEBUG, FILETAG , "DPS_FFT -l" GETLINE(__LINE__) ": " __VA_ARGS__)
    #define uLogDspFft_i(...)  __android_log_print(ANDROID_LOG_INFO, FILETAG , "DPS_FFT -l" GETLINE(__LINE__) ": " __VA_ARGS__)
    #define uLogDspFft_e(...)  __android_log_print(ANDROID_LOG_ERROR, FILETAG,  "DPS_FFT -l" GETLINE(__LINE__) ": " __VA_ARGS__)
    #define uLogDspFft_w(...)  __android_log_print(ANDROID_LOG_WARN, FILETAG, "DPS_FFT -l" GETLINE(__LINE__) ": " __VA_ARGS__)
#else
    #define uLogDspFft_d(...)
    #define uLogDspFft_i(...)
    #define uLogDspFft_e(...)
    #define uLogDspFft_w(...)
#endif

#endif //USOUND_ANDROID_ULOG_H
