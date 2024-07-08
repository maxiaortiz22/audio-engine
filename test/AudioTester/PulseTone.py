from Tester import ToneTester
from progress.bar import IncrementalBar
import audio_engine
from scipy.signal import hilbert, find_peaks
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import soundfile as sf

class PulseToneTest(ToneTester):

    def __init__(self, sr, buffer):
        super().__init__(sr, buffer)
        audio_engine.tone_generator_setValue(audio_engine.ToneGenParam.TG_TONE_TYPE, audio_engine.ToneType.PULSE_TONE_ONE_SEC)
        self.duration = 14
        self.bands = [125, 250, 500, 750, 1000, 1500, 2000, 3000, 4000, 6000, 8000]
        self.ftick = [125, 250, 500, 750, 1000, 1500, 2000, 3000, 4000, 6000, 8000]
        self.labels = ['125', '250', '500', '750', '1k', '1.5k', '2k', '3k', '4k', '6k', '8k']

    def test(self):

        bar = IncrementalBar('Pulse tone test', max = len(self.bands)*2)

        df = pd.DataFrame()

        for channel in [audio_engine.ChannelType.LEFT_CHANNEL, audio_engine.ChannelType.RIGHT_CHANNEL]:
            self.set_channel(channel)

            for freq in self.bands:
                audio_engine.tone_generator_setValue(audio_engine.ToneGenParam.TG_FREQ, freq)
                self.gen_data()
                print(np.min(self.tone), np.max(self.tone))
                #self.play_data()

                sf.write(f"AudioTester/audios/pulse_tone_{freq}.wav", self.tone, self.sr)

                plt.plot(self.tone)
                plt.show()

                """
                data = self.data/np.max(np.abs(self.data))
                tone = np.abs(hilbert(data))

                DISTANCE = self.sr*300*(10**(-3)) #I expect the distance between the peaks to be greater than 300ms (on-time of the pulsed tone).

                local_max_idx, _ = find_peaks(tone, height=0.5, distance=DISTANCE)

                #I cut the pitch on the second and third pulses:
                first_max = local_max_idx[1]
                second_max = local_max_idx[2]

                end_left = np.where(np.flip(tone[:first_max])<=tone[first_max]*0.1)[0][0]
                end_left = first_max - end_left

                end_right = np.where(tone[second_max:]<=tone[second_max]*0.1)[0][0]
                end_right = second_max + end_right

                tone = tone[(end_left-2000):(end_right+2000)]

                #I look for pulse times:
                local_max_idx, _ = find_peaks(tone, height=0.5, distance=DISTANCE)

                first_max = local_max_idx[0]
                second_max = local_max_idx[1]

                #First cycle times:
                first_rise_min_left = np.where(np.flip(tone[:first_max])<=tone[first_max]*0.1)[0][0]
                first_rise_min_left = first_max - first_rise_min_left

                first_rise_max_left = np.where(np.flip(tone[:first_max])<=tone[first_max]*0.9)[0][0]
                first_rise_max_left = first_max - first_rise_max_left

                first_fall_min_left = np.where(tone[first_max:]<=tone[first_max]*0.1)[0][0]
                first_fall_min_left = first_max + first_fall_min_left

                first_fall_middle_left = np.where(tone[first_max:]<=tone[first_max]*0.5)[0][0]
                first_fall_middle_left = first_max + first_fall_middle_left

                first_fall_max_left = np.where(tone[first_max:]<=tone[first_max]*0.9)[0][0]
                first_fall_max_left = first_max + first_fall_max_left

                #Second cycle times:
                second_rise_min_left = np.where(np.flip(tone[:second_max])<=tone[second_max]*0.1)[0][0]
                second_rise_min_left = second_max - second_rise_min_left

                second_rise_middle_left = np.where(np.flip(tone[:second_max])<=tone[second_max]*0.5)[0][0]
                second_rise_middle_left = second_max - second_rise_middle_left

                times = {'Rise time [ms]': np.round(((first_rise_max_left-first_rise_min_left)/self.sr)*10**3, 2),
                         'Fall time [ms]': np.round(((first_fall_min_left-first_fall_max_left)/self.sr)*10**3, 2),
                         'On time [ms]': np.round(((first_fall_max_left-first_rise_max_left)/self.sr)*10**3, 2),
                         'On/Off time [ms]': np.round(((second_rise_middle_left-first_fall_middle_left)/self.sr)*10**3, 2)}
                
                data_ = {'Freq [Hz]': [freq],
                         'Channel': [channel],
                         'Rise time [ms]': [times['Rise time [ms]']],
                         'Fall time [ms]': [times['Fall time [ms]']],
                         'On time [ms]': [times['On time [ms]']],
                         'On/Off time [ms]': [times['On/Off time [ms]']]}
                
                data_ = pd.DataFrame(data_)
                
                df = pd.concat([df, data_], ignore_index=True)
                """

                bar.next()
        bar.finish()
        """
        audio_engine.tone_generator_free()

        print(df)

        
        fig, ax = plt.subplots(figsize=(5, 4))

        muestras = np.arange(0, len(tone))
        tiempo = muestras / (self.sr*10**-3)

        ax.plot(tiempo, tone)
    
        for idx in [first_rise_min_left, first_rise_max_left, first_fall_min_left, 
                    first_fall_middle_left, first_fall_max_left, second_rise_min_left, second_rise_middle_left]:

            ax.vlines(x = idx/(self.sr*10**-3), ymin = min(tone), ymax = max(tone), colors = 'purple')

        ax.set_xlabel("Time [ms]")

        plt.tight_layout()
        plt.show()
       """
        