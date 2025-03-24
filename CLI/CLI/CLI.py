"""
This module initializes and manages the graphical user interface (GUI) for the application. 
It starts essential background threads for receiving messages, handling video streaming, 
and processing joystick input.
"""
import tkinter as tk
import threading
from connection import reciveMessages
from interfaz import WINDOW, windowsGrid, windowInit
from video import recivirImagen 
from joystick import joystickRead

def threads():
    """
    Initializes and starts the necessary background threads for the client.

    - Creates a thread for receiving messages from the ESP32 (currently commented out).
    - Creates a thread for handling video streaming (currently commented out).
    - Starts a thread for reading joystick input.

    All threads are set as daemon threads, meaning they will automatically close when the main program exits.
    """
    incoming_message_thread = threading.Thread(target=reciveMessages)
    incoming_message_thread.daemon = True
    #incoming_message_thread.start()
    video_thread = threading.Thread(target=recivirImagen)
    video_thread.daemon = True
    #video_thread.start()
    joystick_thread = threading.Thread(target=joystickRead)
    joystick_thread.daemon = True
    joystick_thread.start()


if __name__ == "__main__":
    """
    Main execution block. Initializes the GUI, sets up the window layout, 
    starts background threads, and runs the Tkinter main loop.
    """
    windowInit()
    windowsGrid()
    threads()
    WINDOW.mainloop()
