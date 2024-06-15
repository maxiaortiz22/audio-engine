from Tester import NoiseTester
from progress.bar import IncrementalBar
import audio_engine
import numpy as np
import matplotlib.pyplot as plt

class NBNTest(NoiseTester):

    def __init__(self, sr, buffer):
        super().__init__(sr, buffer)
        audio_engine.noise_generator_setValue(audio_engine.NoiseGeneratorParam.NSG_NOISE_TYPE, audio_engine.NoiseType.NARROW_BAND_WHITE_NOISE)
        self.bands = [125, 250, 500, 750, 1000, 1500, 2000, 3000, 4000, 6000, 8000]
        self.ftick = [125, 250, 500, 750, 1000, 1500, 2000, 3000, 4000, 6000, 8000]
        self.labels = ['125', '250', '500', '750', '1k', '1.5k', '2k', '3k', '4k', '6k', '8k']

    def test(self):
        bar = IncrementalBar('NBN test', max = int(len(self.bands)*2))

        for channel in [audio_engine.ChannelType.LEFT_CHANNEL, audio_engine.ChannelType.RIGHT_CHANNEL]:

            self.set_channel(channel)

            for freq in self.bands:
                audio_engine.noise_generator_setValue(audio_engine.NoiseGeneratorParam.NSG_FREQ_BAND, freq)
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