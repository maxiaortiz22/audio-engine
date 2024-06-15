# Audio Engine

Audio Engine is a **C++** library created for the processing and generation of digital audio signals.

The library is based on the **OOP** paradigm, using a super class called **AudioEngine** from which 
all the other sub classes inherit to generate the signals.

The generators currently available are:

* **PureTone**
* **PulseTone**
* **WarbleTone**
* **Noise**: white, pink and NBN.

## USAGE:

As a practical example, the following script shows how to generate and print a pure tone on the console:

```cpp
#include "PureTone.h"

int main() {

    //Generator parameters:
    int sampleRate = 48000;
    int buffer = 256;
    float freq = 1000.0;
    ChannelType channel = ChannelType::Left; //Or: ChannelType::Right , ChannelType::Stereo
    float gain = 0.0; //In dBFS
    float* data;

    //Instantiate the class:
    PureTone tone(sampleRate, buffer);

    tone.setGain(gain);
    tone.setFreq(freq);

    //Flag to enable signal generation:
    tone.signalEmissionEnabled();

    //Start a loop to generate 100 iterations:
    for (int i = 0; i < 100; i++) {
        //Generate the signal
        tone.genSignal();
        data = tone.getData();

        //Print the values in console:
        for (int t = 0; t < buffer*2; ++i) { //The buffer*2 is because it is considered to be stereo.
            printf("%f\n", data[t]);
        }
    }

    //Flag to stop signal generation:
    tone.stopEmission();

    //Start a loop so that the tone gradually lowers its gain to avoid popping:
    while (tone.isBypassed()) {
        //Generate the signal
        tone.genSignal();
        data = tone.getData();

        //Print the values in console:
        for (int t = 0; t < buffer*2; ++i) {
            printf("%f\n", data[t]);
        }
   }

   //Release memory:
   tone.freeBuffer();
   delete[] data;

    return 0;
}
```

While this example is only for the pure tone, it works much the same for the other generators. 
They are all instantiated with the **sampleRate** and **buffer** variables and then their other 
parameters are set accordingly.

## BUILDING:

**CMake** is used to create and compile this library. In case you are using **Linux**, the commands 
to compile them are the following:

```bash
$ mkdir build
$ cd build
$ cmake ..
$ cmake --build .
```

On **Windows**:

```bash
$ mkdir build
$ cd build
$ cmake ..
$ cmake --build . --config Release
```

In this case the compiled version of the **AudioEngine.lib** library will be created inside the **Release** 
folder, so it is necessary to copy that file and move it one directory back. That is, from 
*'./audio-engine/build/Release/'* to *'./audio-engine/build'*.

## TESTING:

The test suite for this library is written in **Python**. For this, it is necessary to generate a wrapper from 
the library in **C++** to **Python**. This wrapper is done with the [pybind11](https://pybind11.readthedocs.io/en/stable/index.html) 
library.

To compile the wrapper we must first clone the library to our repository:

```bash
$ cd ./test
$ git clone https://github.com/pybind/pybind11.git
```

Once the library is cloned and inside the *test* directory, the wrapper must be compiled. 

This is done in the same way as before, if you are on **Linux**:

```bash
$ mkdir build
$ cd build
$ cmake ..
$ cmake --build .
```

On **Windows**:

```bash
$ mkdir build
$ cd build
$ cmake ..
$ cmake --build . --config Release
```

As in the previous case, in Windows the files must be copied from the *Release* folder to 
*build*. That is, move them from *'./audio-engine/test/build/Release/'* to *'./audio-engine/test/build'*.

Once the wrapper is compiled, from the *'./audio-engine/test'* directory you have to execute the following 
command to run the tests:

```bash
$ python test.py
```