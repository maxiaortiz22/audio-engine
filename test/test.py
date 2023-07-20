from build.audio_engine import PureTone, WarbleTone, Noise
import numpy as np
import sounddevice as sd

class TestAudio():

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

        if self.audioinstance.getChannel() == 'Left':
            for i in range(0, len(self.data), 2):
                aux_data.append(self.data[i])
        elif self.audioinstance.getChannel() == 'Right':
            for i in range(1, len(self.data), 2):
                aux_data.append(self.data[i])

        self.data = np.array(aux_data[:int(sr*self.duration)])


if __name__ == '__main__':

    #Parameters:
    sr = 48000
    buffer = 256
    
    PureToneTest = TestAudio(sr, buffer, Noise)
    PureToneTest.audioinstance.setNoiseType("Pink Noise", 1)
    #PureToneTest.audioinstance.setChannel('Right')
    #PureToneTest.audioinstance.setFreq(6000)
    print(PureToneTest.audioinstance.getChannel())
    PureToneTest.gen_data()
    PureToneTest.play_data()