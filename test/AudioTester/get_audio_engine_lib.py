from shutil import copy
from glob import glob

def get_lib():
    for file in glob('build/*.pyd'):
        copy(file, 'AudioTester/')

    for file in glob('build/*.exp'):
        copy(file, 'AudioTester/')

    for file in glob('build/*.lib'):
        copy(file, 'AudioTester/')