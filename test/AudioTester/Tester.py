import numpy as np
import sounddevice as sd
import audio_engine

class ToneTester():

    def __init__(self, sr, buffer):
        self.sr = sr
        self.buffer = buffer
        self.duration = 2
        self.gain = 0
        self.data = np.zeros(self.buffer, dtype=np.float32)
        self.tone = np.array([])
        audio_engine.tone_generator_alloc(self.sr)
        audio_engine.tone_generator_setValue(audio_engine.ToneGenParam.TG_TONE_TYPE, audio_engine.ToneType.CONTINUOUS_TONE)
        self.channel = audio_engine.tone_generator_getValue(audio_engine.ToneGenParam.TG_PAN)

    def gen_data(self):
        self.tone = np.array([])
        iteration = self._total_iterations(self.duration)
    
        audio_engine.tone_generator_setValue(audio_engine.ToneGenParam.TG_GAIN, self.gain)
        audio_engine.tone_generator_setValue(audio_engine.ToneGenParam.TG_BYPASS, 0)
        
        for _ in range(int(iteration/3)):
            audio_engine.tone_generator_interval_process(self.data, self.buffer)
            #print(type(self.data.flatten()))
            self.tone = np.append(self.tone, self.data.flatten())

        audio_engine.tone_generator_setValue(audio_engine.ToneGenParam.TG_GAIN, self.gain - 5)

        for _ in range(int(iteration/3)):
            audio_engine.tone_generator_interval_process(self.data, self.buffer)
            #print(type(self.data.flatten()))
            self.tone = np.append(self.tone, self.data.flatten())

        audio_engine.tone_generator_setValue(audio_engine.ToneGenParam.TG_GAIN, self.gain - 2)

        for _ in range(int(iteration/3)):
            audio_engine.tone_generator_interval_process(self.data, self.buffer)
            #print(type(self.data.flatten()))
            self.tone = np.append(self.tone, self.data.flatten())

        audio_engine.tone_generator_setValue(audio_engine.ToneGenParam.TG_BYPASS, 1)

        while not audio_engine.tone_generator_is_bypassed():
            audio_engine.tone_generator_interval_process(self.data, self.buffer)
            self.tone = np.append(self.tone, self.data.flatten())

        print(len(self.tone))
        self._get_data_by_channel()

    def play_data(self):
        sd.play(self.tone, self.sr)
        sd.wait()

    def _total_iterations(self, duration):
        """Total number of iterations to obtain the desired 
        duration with the chosen buffer size."""
        iteration = (self.sr * duration) / self.buffer
        return int(np.ceil(iteration))

    def _get_data_by_channel(self):

        aux_data = []

        if self.get_channel() == audio_engine.ChannelType.LEFT_CHANNEL:
            for i in range(0, len(self.tone), 2):
                aux_data.append(self.tone[i])
        elif self.get_channel() == audio_engine.ChannelType.RIGHT_CHANNEL:
            for i in range(1, len(self.tone), 2):
                aux_data.append(self.tone[i])

        self.tone = aux_data
    
    def set_channel(self, channel):
        audio_engine.tone_generator_setValue(audio_engine.ToneGenParam.TG_PAN, channel)
        self.channel = audio_engine.tone_generator_getValue(audio_engine.ToneGenParam.TG_PAN)
    
    def get_channel(self):
        return audio_engine.tone_generator_getValue(audio_engine.ToneGenParam.TG_PAN)
    

class NoiseTester():

    def __init__(self, sr, buffer):
        self.sr = sr
        self.buffer = buffer
        self.duration = 2
        self.gain = 0
        self.data = np.zeros(self.buffer, dtype=np.float32)
        self.noise = np.array([])
        audio_engine.noise_generator_alloc(self.sr)
        audio_engine.noise_generator_setValue(audio_engine.NoiseGeneratorParam.NSG_NOISE_TYPE, audio_engine.NoiseType.WHITE_NOISE)
        self.channel = audio_engine.noise_generator_getValue(audio_engine.ToneGenParam.TG_PAN)

    def gen_data(self):
        self.noise = np.array([])
        iteration = self._total_iterations(self.duration)
    
        audio_engine.noise_generator_setValue(audio_engine.NoiseGeneratorParam.NSG_GAIN, self.gain)
        audio_engine.noise_generator_setValue(audio_engine.NoiseGeneratorParam.NSG_BYPASS, 0)
        
        for _ in range(iteration//3):
            audio_engine.noise_generator_process(self.data, self.buffer)
            self.noise = np.append(self.noise, self.data.flatten())

        audio_engine.noise_generator_setValue(audio_engine.NoiseGeneratorParam.NSG_GAIN, -3)
            
        for _ in range(iteration//3):
            audio_engine.noise_generator_process(self.data, self.buffer)
            self.noise = np.append(self.noise, self.data.flatten())

        audio_engine.noise_generator_setValue(audio_engine.NoiseGeneratorParam.NSG_GAIN, -5)
            
        for _ in range(iteration//3):
            audio_engine.noise_generator_process(self.data, self.buffer)
            self.noise = np.append(self.noise, self.data.flatten())

        audio_engine.noise_generator_setValue(audio_engine.NoiseGeneratorParam.NSG_BYPASS, 1)

        while not audio_engine.noise_generator_is_bypassed():
            audio_engine.noise_generator_process(self.data, self.buffer)
            self.noise = np.append(self.noise, self.data.flatten())


        print(len(self.noise))
        self._get_data_by_channel()

    def play_data(self):
        sd.play(self.noise, self.sr)
        sd.wait()

    def _total_iterations(self, duration):
        """Total number of iterations to obtain the desired 
        duration with the chosen buffer size."""
        iteration = (self.sr * duration) / self.buffer
        return int(np.ceil(iteration))

    def _get_data_by_channel(self):

        aux_data = []
        if self.get_channel() == audio_engine.ChannelType.LEFT_CHANNEL:
            for i in range(0, len(self.noise), 2):
                aux_data.append(self.noise[i])
        elif self.get_channel() == audio_engine.ChannelType.RIGHT_CHANNEL:
            for i in range(1, len(self.noise), 2):
                aux_data.append(self.noise[i])

        self.noise = aux_data
    
    def set_channel(self, channel):
        audio_engine.noise_generator_setValue(audio_engine.NoiseGeneratorParam.NSG_CHANNEL, channel)
        self.channel = audio_engine.noise_generator_getValue(audio_engine.NoiseGeneratorParam.NSG_CHANNEL)
    
    def get_channel(self):
        return audio_engine.noise_generator_getValue(audio_engine.NoiseGeneratorParam.NSG_CHANNEL)