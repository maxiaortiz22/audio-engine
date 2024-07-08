from PureTone import PureToneTest
from WarbleTone import WarbleToneTest
from PulseTone import PulseToneTest
from WhiteNoise import WhiteNoiseTest
from PinkNoise import PinkeNoiseTest
from SpeechNoise import SpeechNoiseTest
from NBN import NBNTest

def run(sr, buffer):

    #Test Pure Tone:
    #pure_tone = PureToneTest(sr, buffer)
    #pure_tone.test()

    #Test Pulse Tone:
    pulse_tone = PulseToneTest(sr, buffer)
    pulse_tone.test()

    #Test Warble Tone:
    #warble_tone = WarbleToneTest(sr, buffer)
    #warble_tone.test()

    #Test White Noise:
    #white_noise = WhiteNoiseTest(sr, buffer)
    #white_noise.test()

    #Test Pink Noise:
    #pink_noise = PinkeNoiseTest(sr, buffer)
    #pink_noise.test()

    #Test Speech Noise:
    #speech_noise = SpeechNoiseTest(sr, buffer)
    #speech_noise.test()

    #Test NBN:
    #nbn = NBNTest(sr, buffer)
    #nbn.test()