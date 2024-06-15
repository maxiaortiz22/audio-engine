from Tester import ToneTester
from progress.bar import IncrementalBar
import audio_engine
import numpy as np
from scipy.fft import fft, fftfreq
import matplotlib.pyplot as plt

class PureToneTest(ToneTester):

    def __init__(self, sr, buffer):
        super().__init__(sr, buffer)
        audio_engine.tone_generator_setValue(audio_engine.ToneGenParam.TG_TONE_TYPE, audio_engine.ToneType.CONTINUOUS_TONE)
        self.bands = [125, 250, 500, 750, 1000, 1500, 2000, 3000, 4000, 6000, 8000]
        self.ftick = [125, 250, 500, 750, 1000, 1500, 2000, 3000, 4000, 6000, 8000]
        self.labels = ['125', '250', '500', '750', '1k', '1.5k', '2k', '3k', '4k', '6k', '8k']
        self.N = 0
        self.T = 1.0 / self.sr
        self.fft = 0
        self.f = 0

    def test(self):

        bar = IncrementalBar('Pure tone test', max = len(self.bands)*2)

        for channel in [audio_engine.ChannelType.LEFT_CHANNEL, audio_engine.ChannelType.RIGHT_CHANNEL]:

            self.set_channel(channel)

            for freq in self.bands:
                audio_engine.tone_generator_setValue(audio_engine.ToneGenParam.TG_FREQ, freq)
                self.gen_data()
                print(np.min(self.tone), np.max(self.tone))
                self.play_data()
                signal = self.tone

                plt.plot(signal)
                plt.show()

                #Check the level of the signals
                #assert np.max(signal) >= 1.0, f"The amplitude of {freq} is not greater than 1.0: {max(signal)}"
                #assert np.min(signal) >= -1.0, f"The amplitude of {freq} is not lower than 1.0: {min(signal)}"

                """
                #Plot the fft of the signal
                self.N = len(signal)
                self.fft = np.zeros(self.N//2)
                self.f = fftfreq(self.N, self.T)[:self.N//2]

                self.fft = fft(signal)
                self.fft = 2.0/self.N * np.abs(self.fft[0:self.N//2])

                if channel == ChannelType.Left:
                    ax1.semilogx(self.f, self.fft / np.max(self.fft),'b')
                    ax1.set_xticks(self.ftick)
                    ax1.set_xticklabels(self.labels, rotation=45)
                    ax1.set_xlim(100, 10000)

                elif channel == ChannelType.Right:
                    ax2.semilogx(self.f, self.fft / np.max(self.fft), 'r')
                    ax2.set_xticks(self.ftick)
                    ax2.set_xticklabels(self.labels, rotation=45)
                    ax2.set_xlim(100, 10000)

                """

                bar.next()
        bar.finish()
        audio_engine.tone_generator_free()

        #ax1.set_title('Left ear')
        #ax2.set_title('Right ear')
        
        #fig.tight_layout()
        #plt.show()
        