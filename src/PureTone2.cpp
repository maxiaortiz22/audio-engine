#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <chrono>
#include <thread>

class PureTone {
public:
    PureTone(double initialFrequency, double maxAmplitude, double targetAmplitude, double decreaseAmplitude) :
            frequency(initialFrequency),
            maxAmplitude(maxAmplitude),
            targetAmplitude(targetAmplitude),
            decreaseAmplitude(decreaseAmplitude) {}

    // Genera un tono puro con envolvente personalizada durante el tiempo especificado y almacena los valores en el buffer.
    void generateTone(double *buffer, int bufferSize, double sampleRate) {
        const double attackDuration = 0.065;  // Duración del ataque en segundos (65 ms)
        const double sustainDuration = 1.0;   // Duración de la sostenida en segundos
        const double decayDuration = 0.065;   // Duración del decaimiento en segundos (65 ms)
        const double totalDuration = attackDuration + sustainDuration + decayDuration;

        for (int i = 0; i < bufferSize; ++i) {
            double time = static_cast<double>(i) / sampleRate;
            double envelope = 0.0;

            if (time < attackDuration) {
                envelope = time / attackDuration;  // Envolvente de ataque lineal
            } else if (time < (attackDuration + sustainDuration)) {
                envelope = 1.0;  // Sostenido
            } else if (time < totalDuration) {
                double decayTime = time - (attackDuration + sustainDuration);
                envelope = 1.0 - decayTime / decayDuration;  // Envolvente de decaimiento lineal
            }

            double amplitude = maxAmplitude * envelope;
            buffer[i] = amplitude * std::sin(2.0 * M_PI * frequency * time);
        }
    }

private:
    double frequency;        // Frecuencia en Hz
    double maxAmplitude;     // Máxima amplitud normalizada (0 a 1)
    double targetAmplitude;  // Amplitud objetivo durante el ataque
    double decreaseAmplitude;  // Amplitud objetivo durante el decaimiento
};

int main() {
    const double sampleRate = 44100.0;
    const double frequency = 440.0;
    const double maxAmplitude = 0.7;
    const double targetAmplitude = 1.0;
    const double decreaseAmplitude = 0.7;

    const int bufferSize = static_cast<int>(sampleRate) * 2;  // 2 segundos de audio
    double audioBuffer[bufferSize];

    PureTone toneGenerator(frequency, maxAmplitude, targetAmplitude, decreaseAmplitude);
    toneGenerator.generateTone(audioBuffer, bufferSize, sampleRate);

    // En este punto, el audio generado con la envolvente personalizada se encuentra en audioBuffer.
    // Puedes procesarlo más, guardarlo en un archivo, etc.

    return 0;
}


