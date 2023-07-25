from Tester import Tester
from progress.bar import IncrementalBar
from audio_engine import PureTone

class PureToneTest(Tester):

    def __init__(self, sr, buffer, audioclass=PureTone):
        super().__init__(sr, buffer, audioclass)
        self.bands = [125, 250, 500, 750, 1000, 1500, 2000, 3000, 4000, 6000, 8000]

    def test(self):

        bar = IncrementalBar('Pure tone test', max = len(self.bands)*2)

        for channel in ['Left', 'Right']:
            self.set_channel(channel)

            for freq in self.bands:
                self.audioinstance.setFreq(freq)
                self.gen_data()
                self.play_data()
                bar.next()
        bar.finish()
        