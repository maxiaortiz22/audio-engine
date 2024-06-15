#include "AudioExceptions.h"

UnknownChannelException::UnknownChannelException(const std::string& message)
        : std::runtime_error(message) {}

UnknownNoiseTypeException::UnknownNoiseTypeException(const std::string& message)
        : std::runtime_error(message) {}

UnknownGainException::UnknownGainException(const std::string& message)
        : std::runtime_error(message) {}

UnknownIntervalException::UnknownIntervalException(const std::string& message)
        : std::runtime_error(message) {}