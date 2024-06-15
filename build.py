import argparse
import os
from shutil import copy
from glob import glob


def main():

    main_dir = os.getcwd()

    #Parser object:
    parser = argparse.ArgumentParser(description='audio_engine library compilation settings')

    #Adding building argument:
    parser.add_argument('--build', default='all', help="Compilation types: 'library', 'test', 'all'.")

    # Analizar los argumentos de la línea de comandos
    args = parser.parse_args()
    
    if (args.build == 'library'):

        print('Compilation mode:', args.build)
        compile_library(main_dir)
        print('Compilation completed')

    elif (args.build == 'test'):

        print('Compilation mode:', args.build)
        compile_test(main_dir)
        print('Compilation completed')
    
    elif (args.build == 'all'):

        print('Compilation mode:', args.build)
        compile_library(main_dir)
        compile_test(main_dir)
        print('Compilation completed')
    
    else:
        raise ValueError("Invalid compilation type, try: 'library', 'test' or 'all'.")


def compile_library(main_dir):

    #Compile the library
    os.chdir(main_dir + '/build')
    os.system("cmake ..")
    os.system("cmake --build . --config Release")

    #Copy the library to the build folder:
    for file in glob('Release/*.lib'):
        copy(file, main_dir + '/build')

    
def compile_test(main_dir):
    #Compile the library
    os.chdir(main_dir + '/test/build')
    os.system("cmake ..")
    os.system("cmake --build . --config Release")

    #Copy the library to the build folder:
    for file in glob('Release/*.pyd'):
        copy(file, main_dir + '/test/build')

    for file in glob('Release/*.exp'):
        copy(file, main_dir + '/test/build')

    for file in glob('Release/*.lib'):
        copy(file, main_dir + '/test/build')


if __name__ == '__main__':
    """Building script for Windows"""
    main()