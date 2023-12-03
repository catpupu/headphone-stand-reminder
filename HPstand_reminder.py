# -*- coding: utf-8 -*-
"""
Created on Sat Dec  2 20:06:55 2023

@author: lucas
"""
import os
import pyaudio
import pygame
import time
import tkinter as tk

def get_current_output_device():
    audio = pyaudio.PyAudio()
    current_device = audio.get_default_output_device_info()
    audio.terminate()
    return current_device

def play_alert_sound( file_path ):
    pygame.mixer.init()
    pygame.mixer.music.load( file_path )
    pygame.mixer.music.play()
    
def end_program( alert_window ):
    if alert_window.winfo_exists():
        alert_window.destroy()
    
def popup_window():
    pop_up = tk.Tk()
    pop_up.geometry("200x110+1150+600")
    pop_up.title("")
    
    
    label = tk.Label(pop_up, text="put it back!")
    label.pack(pady=10)
    
    
    button = tk.Button( pop_up, text="ok", width=10, height=2, command=lambda:end_program( pop_up ) )
    button.pack(pady=15)
    pop_up.mainloop()
    
if __name__ == "__main__":
    
    # 獲取py檔本身所在目錄並將其設為工作目錄
    script_directory = os.path.dirname(os.path.realpath(__file__))
    os.chdir(script_directory)
    
    with open('set.txt', 'r', encoding='utf-8') as set_file:
        name = set_file.readline()
        name = name.strip()
        media_file = set_file.readline()
        media = media_file.strip()
        # print( name + ", " + media_file )
        
    '''
    name = "耳機 (Realtek USB2.0 Audio)"
    file = "E:\專案作品\耳機架\media.mp3"
    '''
    
    while True:
        current_output_device = get_current_output_device()

        if current_output_device['name'] != name :
            play_alert_sound( media_file )
            popup_window()
            break
            
        time.sleep(60)