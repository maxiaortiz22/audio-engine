cmake_minimum_required(VERSION 3.12)

#Nombre del proyecto
project(AudioTest)

#Directorios a los que va a revisar
add_subdirectory(pybind11)

# Configurar la ubicación de la biblioteca AudioEngine y los encabezados
set(EXTERNAL_LIB_DIR ${CMAKE_CURRENT_LIST_DIR}/../build)
set(EXTERNAL_INCLUDE_DIR ${CMAKE_CURRENT_LIST_DIR}/../include)

# Encuentra la biblioteca externa (AudioEngine.lib en este caso)
find_library(EXTERNAL_LIBRARY_NAME NAMES AudioEngine HINTS ${EXTERNAL_LIB_DIR})

#Genero el wrapper a partir de lo definido en main.cpp y creo la librería audio_engine
pybind11_add_module(audio_engine main.cpp)

# Enlazar con la biblioteca AudioEngine.lib
target_link_libraries(audio_engine PRIVATE ${EXTERNAL_LIBRARY_NAME} pybind11::module)

# Incluir los encabezados de AudioEngine.h
target_include_directories(audio_engine PRIVATE ${EXTERNAL_INCLUDE_DIR})