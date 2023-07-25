import sys; sys.path.append('AudioTester')

#Copy the last compile version of the audio_engine library
from AudioTester.get_audio_engine_lib import get_lib
get_lib()

from AudioTester.test_maker import run



if __name__ == '__main__':

    #Parameters:
    sr = 48000
    buffer = 256
    
    #Run tests:
    run(sr, buffer)