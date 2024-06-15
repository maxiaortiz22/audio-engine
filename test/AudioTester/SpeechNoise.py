from Tester import NoiseTester
from progress.bar import IncrementalBar
import audio_engine
import numpy as np
import matplotlib.pyplot as plt

class SpeechNoiseTest(NoiseTester):

    def __init__(self, sr, buffer):
        super().__init__(sr, buffer)
        audio_engine.noise_generator_setValue(audio_engine.NoiseGeneratorParam.NSG_NOISE_TYPE, audio_engine.NoiseType.SPEECH_TEST_WHITE_NOISE)

    def test(self):
        bar = IncrementalBar('Speech Noise test', max = 2)

        for channel in [audio_engine.ChannelType.LEFT_CHANNEL, audio_engine.ChannelType.RIGHT_CHANNEL]:

            self.set_channel(channel)

            self.gen_data()
            print(np.min(self.noise), np.max(self.noise))
            self.play_data()

            #Plot FFT:
            fft_result = np.fft.fft(self.noise)
            fft_freq = np.fft.fftfreq(len(self.noise), d=1/self.sr)

            half_n = len(self.noise) // 2
            fft_result_positive = fft_result[1:half_n]
            fft_freq_positive = fft_freq[1:half_n]

            fft_magnitude_db = 20 * np.log10(np.abs(fft_result_positive))

            plt.plot(fft_freq_positive, fft_magnitude_db)
            plt.show()

            bar.next()
        
        bar.finish()
        audio_engine.noise_generator_free()