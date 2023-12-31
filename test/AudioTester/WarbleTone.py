from Tester import Tester
from progress.bar import IncrementalBar
from audio_engine import WarbleTone, ChannelType
from scipy.fft import rfft, rfftfreq
from scipy.signal import butter, sosfilt, find_peaks
import numpy as np
from statistics import mode
import pandas as pd

class WarbleToneTest(Tester):

    def __init__(self, sr, buffer, audioclass=WarbleTone):
        super().__init__(sr, buffer, audioclass)
        self.bands = [125, 250, 500, 750, 1000, 1500, 2000, 3000, 4000, 6000, 8000]
        self.order = 4
        self.result = {'Carrier frequency [Hz]': [],
                       'Modulating frequency [Hz]': [],
                       'Channel': []}

    def test(self):

        bar = IncrementalBar('Warble tone test', max = len(self.bands)*2)
        
        for channel in [ChannelType.Left, ChannelType.Right]:
            self.set_channel(channel)

            for freq in self.bands:
                self.audioinstance.setFreq(freq)
                self.gen_data()
                #self.play_data()}
                
                fm, fc = self.get_frec_mod(self.data, freq)

                self.result['Carrier frequency [Hz]'].append(fc)
                self.result['Modulating frequency [Hz]'].append(fm)
                self.result['Channel'].append(channel)

                bar.next()
        bar.finish()

        df = pd.DataFrame(self.result)

        print(df)
    
    def filter_signal(self, data, band):

        order = self.order

        lowcut = band/np.sqrt(2) 
        highcut = band*np.sqrt(2)

        sos = butter(order, [lowcut, highcut], fs=self.sr, btype='bandpass', output='sos')

        filtered_audio = sosfilt(sos, data)

        return filtered_audio
    
    def get_frec_mod(self, data, band):

        fc = 0
        fm = 0

        filtered_data = self.filter_signal(data, band)

        audio = filtered_data / np.max(np.abs(filtered_data))

        N = len(audio)
        yf = np.array(rfft(audio))
        xf = rfftfreq(N, 1 / self.sr)

        yf = 20 * np.log10(np.abs(yf) / np.max(np.abs(yf)))

        local_max_idx, _ = find_peaks(yf, height=-30)

        xf_max_list = [xf[i] for i in local_max_idx]

        fm_calc = []
        for t in range(len(xf_max_list)-1):
            fm_calc.append(xf_max_list[t+1]-xf_max_list[t])

        #Calculate Carrier and Modulating frequency:
        fm = mode(fm_calc)
        fc = band

        return fm, fc