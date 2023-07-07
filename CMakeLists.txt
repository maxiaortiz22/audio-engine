cmake_minimum_required(VERSION 3.18.1)

project("AudioEngine")

add_library(

    "src/AudioEngine/AudioEngine.cpp"
    "src/ErrorHandling/UnknownChannelException.cpp"
    "src/Noise/Noise.cpp"
    "src/PureTone/PureTone.cpp"
    "src/WarbleTone/WarbleTone.cpp"
)

include_directories(

    "src/AudioEngine/"
    "src/ErrorHandling/"
    "src/Noise/"
    "src/PureTone/"
    "src/WarbleTone/"
)