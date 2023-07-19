cmake_minimum_required(VERSION 3.12)

project(AudioEngine)

# Configura la versión del estándar de C++
#set(CMAKE_CXX_STANDARD 11)
#set(CMAKE_CXX_STANDARD_REQUIRED True)
#cmake_policy(SET CMP0079 NEW)


# Crea la biblioteca compartida o estática
add_library(AudioEngine SHARED STATIC
    src/AudioEngine.cpp
    src/UnknownChannelException.cpp
    src/Noise.cpp
    src/PureTone.cpp
    src/WarbleTone.cpp
)

# Especifica las dependencias de la biblioteca
target_link_libraries(AudioEngine
    PRIVATE ErrorHandling
    PRIVATE Noise
    PRIVATE PureTone
    PRIVATE WarbleTone

)

# Establece los directorios de inclusión de la biblioteca
target_include_directories(AudioEngine PUBLIC
    "include/"
)

#add_subdirectory(test)