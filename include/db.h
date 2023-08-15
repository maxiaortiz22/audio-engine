#ifndef _DB_2_LINEAR_H_
#define _DB_2_LINEAR_H_

#include "dblut.h"
#include "math.h"

//Converts a value from dB to Linear 1 Linear = 0 dB
static inline float dB2Lin(float dbIn) {
//	float db = dbIn < -80 ? -80 : dbIn;
//	db = dbIn > 60 ? 60 : dbIn;
//	return (float)pow(10.0,db/20.0);
	return (float)pow(10.0,dbIn/20.0);
}

//Converts a value from Linear to dB 1 Linear = 0 dB
static inline float Lin2dB(float LinIn)
{
	int index = (int)(LIN2DB_M*LinIn + LIN2DB_N);
	index = index > 0 ? index : 0;
	index = index > LUT_TOP_INDEX ? LUT_TOP_INDEX : index;
	return Lin2dB_LUT[index];
}


#endif
