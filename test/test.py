from build.audio_engine import PureTone, WarbleTone, Noise
import numpy as np
import sounddevice as sd


if __name__ == '__main__':

    #Parameters:
    sr = 48000
    buffer = 256
    data = np.array([])

    #Instance of the class PureTone:
    tone = PureTone(sr, buffer)

    for i in range(188):
        tone.genSignal()
        data = np.append(data, tone.getData.flat)

    tone.freeBuffer()

    tono = []
    if tone.getChannel() == 'Left': #Canal izquierdo
        for i in range(0, len(data), 2):
            tono.append(data[i])
    elif tone.getChannel() == 'Right': #Canal derecho
        for i in range(1, len(data), 2):
            tono.append(data[i])

    sd.play(tono, sr)
    sd.wait()