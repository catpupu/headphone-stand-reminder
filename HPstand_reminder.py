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

def print_all_Headphones_device():
    audio = pyaudio.PyAudio()
    
    print("Print all headphones device name:")
    for i in range(audio.get_device_count()):
        device_info = audio.get_device_info_by_index(i)
        if ( device_info['maxOutputChannels'] > 0 ) and ( "Headphones" in device_info['name'] ) :
            print(f"{device_info['name']}")

    print("\n")
    audio.terminate()

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
    
def load_setfile( name, media_file ):
    if os.path.isfile("setting.txt"):
        with open("setting.txt", 'r', encoding='utf-8') as setting:
            name = setting.readline().strip()
            media_file = setting.readline().strip()
            # print( name + ", " + media_file )
    else :
        with open("setting.txt", 'w', encoding='utf-8') as setting:
            # Traverse output device names and print
            print_all_Headphones_device()
            
            name = input("headphone device name : ")
            media_file = input("music file path : ")
            setting.write( name + "\n" )
            setting.write( media_file + "\n" )
    
# main function
if __name__ == "__main__":
    
    # Get py file directory and set it as the working directory
    script_directory = os.path.dirname(os.path.realpath(__file__))
    os.chdir(script_directory)
    
    headphone_name = "耳機 (Realtek USB2.0 Audio)"
    media_file = "E:\專案作品\耳機架\media.mp3"
    load_setfile( headphone_name, media_file )
    
    while True:
        current_output_device = get_current_output_device()

        if current_output_device['name'] != headphone_name :
            play_alert_sound( media_file )
            popup_window()
            break
            
        time.sleep(60)