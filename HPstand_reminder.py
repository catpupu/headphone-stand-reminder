# -*- coding: utf-8 -*-
"""
Created on Sat Dec  2 20:06:55 2023

@author: lucas
"""
import pyaudio
from pydub import AudioSegment
from pydub.playback import play
import time

def get_current_output_device():
    audio = pyaudio.PyAudio()
    current_device = audio.get_default_output_device_info()
    audio.terminate()
    return current_device

def play_m4a( file_path ) :
    sound = AudioSegment.from_file(file_path, format="m4a")
    play(sound)

if __name__ == "__main__":
    # name = input("head phone device name : ")
    # file = input("music name : ")
    name = "耳機 (Realtek USB2.0 Audio)"
    file = "E:\專案作品\耳機架\media.m4a"
    
    while True:
        current_output_device = get_current_output_device()

        if current_output_device['name'] != name :
            # 判斷檔案格式
            play_m4a(file)
            
        time.sleep(10)
