#include "UnknownChannelException.h"

UnknownChannelException::UnknownChannelException(const std::string& channel)
    : std::runtime_error("Unknown Channel: " + channel) {}