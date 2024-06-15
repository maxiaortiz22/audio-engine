#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/numpy.h>
#include "ToneGenerator.h"
#include "NoiseGenerator.h"
#include "usoundlib_params.h"
#include "engine_params.h"

namespace py = pybind11;

PYBIND11_MODULE(audio_engine, m) {
    m.doc() = "audio_engine binding for use the module in python";

    // Exporta las funciones de ToneGenerator.h
    m.def("tone_generator_is_instantiated", &tone_generator_is_instantiated, "Check if tone generator is instantiated");
    m.def("second_tone_generator_is_instantiated", &second_tone_generator_is_instantiated, "Check if second tone generator is instantiated");
    m.def("update_tone_generator_params", &update_tone_generator_params, "Update tone generator parameters");
    m.def("update_second_tone_generator_params", &update_second_tone_generator_params, "Update second tone generator parameters");
    m.def("tone_generator_is_bypassed", &tone_generator_is_bypassed, "Check if tone generator is bypassed");
    m.def("second_tone_generator_is_bypassed", &second_tone_generator_is_bypassed, "Check if second tone generator is bypassed");
    m.def("tone_generator_free", &tone_generator_free, "Free tone generator");
    m.def("second_tone_generator_free", &second_tone_generator_free, "Free second tone generator");
    m.def("tone_generator_getValue", &tone_generator_getValue, "Get value for tone generator");
    m.def("second_tone_generator_getValue", &second_tone_generator_getValue, "Get value for second tone generator");

    m.def("tone_generator_alloc", [](float sampleRate) -> int {
        UsoundResult result = tone_generator_alloc(sampleRate);
        return static_cast<int>(result);
    }, "Allocate tone generator");

    m.def("second_tone_generator_alloc", [](float sampleRate) -> int {
        UsoundResult result = second_tone_generator_alloc(sampleRate);
        return static_cast<int>(result);
    }, "Allocate tone generator");
    
    m.def("tone_generator_interval_process", [](py::array_t<float> py_data, int buffer_size) {
        // Obtener un puntero al arreglo de datos desde el objeto array de Python
        auto ptr = static_cast<float*>(py_data.request().ptr);

        // Llamar a la función original con los datos directamente
        tone_generator_interval_process(ptr, buffer_size);
    });

    m.def("second_tone_generator_interval_process", [](py::array_t<float> py_data, int buffer_size) {
        // Obtener un puntero al arreglo de datos desde el objeto array de Python
        auto ptr = static_cast<float*>(py_data.request().ptr);

        // Llamar a la función original con los datos directamente
        second_tone_generator_interval_process(ptr, buffer_size);
    });

    m.def("tone_generator_setValue", [](int param, float value) {
        // Llamar a la función original
        UsoundResult res = tone_generator_setValue(param, value);

        // Puedes devolver el resultado como un entero si es necesario
        return static_cast<int>(res);
    });

    m.def("second_tone_generator_setValue", [](int param, float value) {
        // Llamar a la función original
        UsoundResult res = second_tone_generator_setValue(param, value);

        // Puedes devolver el resultado como un entero si es necesario
        return static_cast<int>(res);
    });

    // Enums:
    py::enum_<ChannelType>(m, "ChannelType")
        .value("CENTER_CHANNEL", CENTER_CHANNEL)
        .value("MONO_CHANNEL", MONO_CHANNEL)
        .value("STEREO_CHANNEL", STEREO_CHANNEL)
        .value("MIC_CHANNEL_MODE", MIC_CHANNEL_MODE)
        .value("LEFT_CHANNEL", LEFT_CHANNEL)
        .value("RIGHT_CHANNEL", RIGHT_CHANNEL)
        .value("MIC_LEFT_CHANNEL_MODE", MIC_LEFT_CHANNEL_MODE)
        .value("MIC_RIGHT_CHANNEL_MODE", MIC_RIGHT_CHANNEL_MODE);

    py::enum_<ToneType>(m, "ToneType")
        .value("AUDIOMETRY_TONE", AUDIOMETRY_TONE)
        .value("REPEATED_TONE", REPEATED_TONE)
        .value("DEMO_TONE", DEMO_TONE)
        .value("USER_REPEATED_TONE", USER_REPEATED_TONE)
        .value("CONTINUOUS_TONE", CONTINUOUS_TONE)
        .value("PULSE_TONE_HALF_SEC", PULSE_TONE_HALF_SEC)
        .value("PULSE_TONE_ONE_SEC", PULSE_TONE_ONE_SEC)
        .value("MASKING_STIMULUS", MASKING_STIMULUS)
        .value("WARBLE_TONE", WARBLE_TONE)
        .value("LINEARITY_TEST", LINEARITY_TEST);

    py::enum_<ToneGenParam>(m, "ToneGenParam")
        .value("TG_BYPASS", TG_BYPASS)
        .value("TG_FREQ", TG_FREQ)
        .value("TG_GAIN", TG_GAIN)
        .value("TG_PAN", TG_PAN)
        .value("TG_INTERVAL", TG_INTERVAL)
        .value("TG_INIT_GAIN", TG_INIT_GAIN)
        .value("TG_FINAL_GAIN", TG_FINAL_GAIN)
        .value("TG_GAIN_CHANGE", TG_GAIN_CHANGE)
        .value("TG_GAIN_THRESHOLD", TG_GAIN_THRESHOLD)
        .value("TG_TONE_TYPE", TG_TONE_TYPE)
        .value("TG_PULSE_INTERVAL", TG_PULSE_INTERVAL)
        .value("TG_INTERCOM_VOLUME", TG_INTERCOM_VOLUME);

    
    //Exporta las funciones de NoiseGenerator.h
    m.def("noise_generator_alloc", &noise_generator_alloc, "Allocate noise generator");

    m.def("noise_generator_setValue", &noise_generator_setValue, "Set value for noise generator");
    m.def("noise_generator_getValue", &noise_generator_getValue, "Get value for noise generator");
    m.def("update_noise_generator_params", &update_noise_generator_params, "Update noise generator parameters");
    m.def("noise_generator_is_instantiated", &noise_generator_is_instantiated, "Check if noise generator is instantiated");
    m.def("noise_generator_is_bypassed", &noise_generator_is_bypassed, "Check if noise generator is bypassed");
    m.def("noise_generator_process", [](py::array_t<float> py_data, int buffer_size) {
        // Obtener un puntero al arreglo de datos desde el objeto array de Python
        auto ptr = static_cast<float*>(py_data.request().ptr);

        // Llamar a la función original con los datos directamente
        noise_generator_process(ptr, buffer_size);
    });

    m.def("noise_generator_free", &noise_generator_free, "Free noise generator");
    
    py::enum_<NoiseGeneratorParam>(m, "NoiseGeneratorParam")
        .value("NSG_BYPASS", NSG_BYPASS)
        .value("NSG_CHANNEL", NSG_CHANNEL)
        .value("NSG_GAIN", NSG_GAIN)
        .value("NSG_NOISE_TYPE", NSG_NOISE_TYPE)
        .value("NSG_FREQ_BAND", NSG_FREQ_BAND)
        .value("NSG_STIMULUS_MODE", NSG_STIMULUS_MODE);

    py::enum_<NoiseType>(m, "NoiseType")
        .value("PINK_NOISE", PINK_NOISE)
        .value("WHITE_NOISE", WHITE_NOISE)
        .value("NARROW_BAND_PINK_NOISE", NARROW_BAND_PINK_NOISE)
        .value("NARROW_BAND_WHITE_NOISE", NARROW_BAND_WHITE_NOISE)
        .value("NO_NOISE", NO_NOISE)
        .value("SPEECH_TEST_WHITE_NOISE", SPEECH_TEST_WHITE_NOISE);
}