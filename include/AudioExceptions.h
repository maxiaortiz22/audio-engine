#ifndef AUDIOEXCEPTIONS_H
#define AUDIOEXCEPTIONS_H

#include <stdexcept>
#include <string>

class UnknownChannelException : public std::runtime_error {
public:
    UnknownChannelException(const std::string& message);
};

class UnknownNoiseTypeException : public std::runtime_error {
public:
    UnknownNoiseTypeException(const std::string& message);
};

class UnknownGainException : public std::runtime_error {
public:
    UnknownGainException(const std::string& message);
};

#endif  // AUDIOEXCEPTIONS_H