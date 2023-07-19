#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/numpy.h>
#include <string>
#include "AudioEngine.h"
#include "Noise.h"
#include "PureTone.h"
#include "WarbleTone.h"

namespace py = pybind11;

// Define the trampoline helper classes
class PyAudioEngine : public AudioEngine {
public:
    using AudioEngine::AudioEngine; // Inherit constructors
    void genSignal() override { PYBIND11_OVERRIDE_PURE(void, AudioEngine, genSignal, ); }
    float genSample() override { PYBIND11_OVERRIDE_PURE(float, AudioEngine, genSample, ); }
};

class PyPureTone : public PureTone {
public:
    using PureTone::PureTone; // Inherit constructors
    void genSignal() override { PYBIND11_OVERRIDE(void, PureTone, genSignal, ); }
    float genSample() override { PYBIND11_OVERRIDE(float, PureTone, genSample, ); }
};

class PyNoise : public Noise {
public:
    using Noise::Noise; // Inherit constructors
    void genSignal() override { PYBIND11_OVERRIDE(void, Noise, genSignal, ); }
    float genSample() override { PYBIND11_OVERRIDE(float, Noise, genSample, ); }
};

class PyWarbleTone : public WarbleTone {
public:
    using WarbleTone::WarbleTone; // Inherit constructors
    void genSignal() override { PYBIND11_OVERRIDE(void, WarbleTone, genSignal, ); }
    float genSample() override { PYBIND11_OVERRIDE(float, WarbleTone, genSample, ); }
};

PYBIND11_MODULE(audio_engine, m) {

    m.doc() = "C++ to python wrapper for testing AudioEngine library.";

    // AudioEngine
    py::class_<AudioEngine, PyAudioEngine>(m, "AudioEngine")
        .def(py::init<int, int>())
        .def("genSignal", &AudioEngine::genSignal)
        .def("genSample", &AudioEngine::genSample)
        //.def_property("channel", &AudioEngine::getChannel, &AudioEngine::setChannel)
        .def("setChannel", &AudioEngine::setChannel)
        .def("getChannel", &AudioEngine::getChannel)
        //.def("getData", &AudioEngine::getData, py::return_value_policy::take_ownership, py::return_value_policy::reference_internal)
        .def_property_readonly("getData", [](const AudioEngine &self) {
            int buffer = self.getBufferSize();
            py::array_t<float> out({buffer * 2}, {sizeof(float)});
            float* data_ptr = self.getData();
            std::memcpy(out.mutable_data(), data_ptr, buffer * 2 * sizeof(float));
            return out;
        })
        .def("getSampleRate", &AudioEngine::getSampleRate)
        .def("setAmplitude", &AudioEngine::setAmplitude)
        .def("freeBuffer", &AudioEngine::freeBuffer)
        .def("setSampleInBuffer", &AudioEngine::setSampleInBuffer);

    // PureTone
    py::class_<PureTone, AudioEngine, PyPureTone>(m, "PureTone")
        .def(py::init<int, int>())
        .def("genSignal", &PureTone::genSignal)
        .def("genSample", &PureTone::genSample)
        //.def_property("freq", &PureTone::getFreq, &PureTone::setFreq)
        .def("setFreq", &PureTone::setFreq)
        .def("getFreq", &PureTone::getFreq);

    // Noise
    py::class_<Noise, AudioEngine, PyNoise>(m, "Noise")
        .def(py::init<int, int>())
        .def("genSignal", &Noise::genSignal)
        .def("genSample", &Noise::genSample)
        .def("setNoiseType", &Noise::setNoiseType);

    // WarbleTone
    py::class_<WarbleTone, AudioEngine, PyWarbleTone>(m, "WarbleTone")
        .def(py::init<int, int>())
        .def("genSignal", &WarbleTone::genSignal)
        .def("genSample", &WarbleTone::genSample)
        .def("setFreq", &WarbleTone::setFreq)
        .def("getFreq", &WarbleTone::getFreq)
        .def("setFm", &WarbleTone::setFm)
        .def("getFm", &WarbleTone::getFm)
        .def("setDeviation", &WarbleTone::setDeviation)
        .def("getDeviation", &WarbleTone::getDeviation);
}