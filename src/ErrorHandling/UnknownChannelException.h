#ifndef UNKNOWNCHANNELEXCEPTION_H
#define UNKNOWNCHANNELEXCEPTION_H

#include <stdexcept>
#include <string>

class UnknownChannelException : public std::runtime_error {
public:
    UnknownChannelException(const std::string& channel);
};

#endif  // UNKNOWNCHANNELEXCEPTION_H