from Tester import Tester
from progress.bar import IncrementalBar
from audio_engine import PureTone, ChannelType
import numpy as np
from scipy.fft import fft, fftfreq
import matplotlib.pyplot as plt

class PureToneTest(Tester):

    def __init__(self, sr, buffer, audioclass=PureTone):
        super().__init__(sr, buffer, audioclass)
        self.bands = [125, 250, 500, 750, 1000, 1500, 2000, 3000, 4000, 6000, 8000]
        self.ftick = [125, 250, 500, 750, 1000, 1500, 2000, 3000, 4000, 6000, 8000]
        self.labels = ['125', '250', '500', '750', '1k', '1.5k', '2k', '3k', '4k', '6k', '8k']
        self.N = self.sr*self.duration
        self.T = 1.0 / self.sr
        self.fft = np.zeros(self.N//2)
        self.f = fftfreq(self.N, self.T)[:self.N//2]

    def test(self):

        bar = IncrementalBar('Pure tone test', max = len(self.bands)*2)

        fig, (ax1, ax2) = plt.subplots(2)

        signal = np.zeros(self.N)
        for channel in [ChannelType.Left, ChannelType.Right]:
            self.set_channel(channel)

            for freq in self.bands:
                self.audioinstance.setFreq(freq)
                self.gen_data()
                #self.play_data()
                signal = self.data

                #Check the level of the signals
                assert np.max(signal) == 1.0, f"The amplitude of {freq} is greater than 1.0"
                assert np.min(signal) == -1.0, f"The amplitude of {freq} is lower than 1.0"

                #Plot the fft of the signal
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

                bar.next()
        bar.finish()

        ax1.set_title('Left ear')
        ax2.set_title('Right ear')
        
        fig.tight_layout()
        plt.show()
        