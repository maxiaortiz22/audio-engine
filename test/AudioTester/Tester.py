import numpy as np
import sounddevice as sd
from audio_engine import ChannelType

class Tester():

    def __init__(self, sr, buffer, audioclass):
        self.sr = sr
        self.buffer = buffer
        self.duration = 2
        self.data = np.array([])
        self.audioinstance = audioclass(sr, buffer)
        self.channel = self.audioinstance.getChannel()

    def gen_data(self):
        self.data = np.array([])
        iteration = self._total_iterations(self.duration)
        
        for _ in range(iteration):
            self.audioinstance.genSignal()
            self.data = np.append(self.data, self.audioinstance.getData.flat)

        self._get_data_by_channel()

    def play_data(self):
        sd.play(self.data, self.sr)
        sd.wait()

    def _total_iterations(self, duration):
        """Total number of iterations to obtain the desired 
        duration with the chosen buffer size."""
        iteration = (self.sr * duration) / self.buffer
        return int(np.ceil(iteration))

    def _get_data_by_channel(self):

        aux_data = []

        if self.audioinstance.getChannel() == ChannelType.Left:
            for i in range(0, len(self.data), 2):
                aux_data.append(self.data[i])
        elif self.audioinstance.getChannel() == ChannelType.Right:
            for i in range(1, len(self.data), 2):
                aux_data.append(self.data[i])

        self.data = np.array(aux_data[:int(self.sr*self.duration)])
    
    def set_channel(self, channel):
        self.channel = self.audioinstance.setChannel(channel)
    
    def get_channel(self):
        return self.audioinstance.getChannel()