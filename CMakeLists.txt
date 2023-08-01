cmake_minimum_required(VERSION 3.12)

project(AudioEngine)

# Configura la versión del estándar de C++
#set(CMAKE_CXX_STANDARD 11)
#set(CMAKE_CXX_STANDARD_REQUIRED True)
#cmake_policy(SET CMP0079 NEW)


# Crea la biblioteca compartida o estática
add_library(AudioEngine SHARED STATIC
    src/AudioEngine.cpp
    src/AudioExceptions.cpp
    src/Noise.cpp
    src/PureTone.cpp
    src/WarbleTone.cpp
    src/LibKissFFT/kiss_fft.c
    src/LibKissFFT/kiss_fftr.c
)

# Establece los directorios de inclusión de la biblioteca
target_include_directories(AudioEngine PUBLIC
    "include/"
)