from PureTone import PureToneTest
from WarbleTone import WarbleToneTest
from Noise import NoiseTest

def run(sr, buffer):

    #Test Pure Tone:
    pure_tone = PureToneTest(sr, buffer)
    pure_tone.test()

    #Test Warble Tone:
    warble_tone = WarbleToneTest(sr, buffer)
    warble_tone.test()

    #Test Noise:
    noise = NoiseTest(sr, buffer)
    noise.test()

