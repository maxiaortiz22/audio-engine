from Tester import Tester
from progress.bar import IncrementalBar
from audio_engine import Noise, ChannelType, NoiseType
from scipy.fft import rfft, rfftfreq
import numpy as np
import sys
from matplotlib.axes import Axes
from matplotlib.figure import Figure
import matplotlib.pyplot as plt

class NoiseTest(Tester):

    def __init__(self, sr, buffer, audioclass=Noise):
        super().__init__(sr, buffer, audioclass)
        self.noise_type = [NoiseType.White, NoiseType.Pink, NoiseType.Brown, NoiseType.NBN]
        self.eps = sys.float_info.epsilon
        self.ftick = [20, 31.5, 63, 125, 250, 500, 1000, 2000, 4000, 8000, 16000, 20000]
        self.labels = ['20', '31.5', '63', '125', '250', '500', '1k', '2k', '4k', '8k', '16k', '20k']
    
    def test(self):
        
        bar = IncrementalBar('Noise test', max = len(self.noise_type)*2)

        for channel in [ChannelType.Left, ChannelType.Right]:
            self.set_channel(channel)

            for type in self.noise_type:

                self.audioinstance.setNoiseType(type, 1)
                self.gen_data()
                #self.play_data()

                N = len(self.data)

                yf = np.abs(np.array(rfft(self.data))) / (N/np.sqrt(2))
                xf = rfftfreq(N, 1 / self.sr)

                yf_db = 20*np.log10(yf / (20*10**(-6)) + self.eps)


                fig, ax = plt.subplots(figsize=(5, 4))
                ax.plot(xf, yf_db, label=type)
                ax.set_title(label=type)
                ax.set_xlabel('Frecuencia [Hz]', color='black')
                ax.set_ylabel('Nivel [dBSPL]', color='black')
                ax.set_xscale('log')
                ax.set_xticks(self.ftick)
                ax.set_xticklabels(self.labels, rotation=90)
                ax.set_xlim(20, 20000)
                ax.legend()
                plt.tight_layout()
                plt.show()

                bar.next()
            
            bar.finish()
            
            
