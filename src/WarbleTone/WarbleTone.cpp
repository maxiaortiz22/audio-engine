#define _USE_MATH_DEFINES
#include "WarbleTone.h"
#include <cmath>

WarbleTone::WarbleTone(int sampleRate, int buffer) : AudioEngine(sampleRate, buffer) {
    offset = 2.0 * M_PI * fm / sampleRate; // fm = frecuencia moduladora (valor entre 4 y 20 Hz)
}