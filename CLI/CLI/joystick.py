"""
This module reads joystick events, including button presses and analog stick movements, 
and processes them for further use. It applies a dead zone filter to the analog inputs, 
calculates the angle and percentage of movement, and sends messages with the processed data. 
The code also ensures that events are only processed if a certain amount of time (MARGIN_TIME) 
has passed since the last analog event.
"""
import pygame
import time
from interfaz import add_message
from connection import sendMessage
import math
import time

# Define the margin of time in seconds
MARGIN_TIME = 0.5

# Variable to store the time of the last analog event
last_analog_event_time = 0

# Define the threshold for the dead zone
DEADZONE_THRESHOLD = 0.1

# Button mapping
KEY_MAPS = {
    0: "1",
    1: "2",
    2: "3",
    3: "4",
    4: "L1",
    5: "R1",
    6: "L2",
    7: "R2",
    8: "Select",
    9: "Start",
    10: "SLL",
    11: "SRR"
}


def joystickInit():
    """
    This function initializes the joystick for the application. It waits for the joystick 
    to be connected and then initializes the first available joystick.

    Returns:
        joystick (pygame.joystick.Joystick): The initialized joystick object.
    """
    pygame.init()
    pygame.joystick.init()
    
    # Wait until the joystick is connected
    while(pygame.joystick.get_count()<=0):
        add_message("Conecte un joystick","warning")
        time.sleep(2)

    joystick = pygame.joystick.Joystick(0)  # Select the first joystick
    joystick.init()
    return joystick


def joystickRead():
    """
    This function continuously reads joystick events. It processes button presses 
    and analog stick movements, applies a dead zone filter, and calculates the 
    angle and percentage of movement. Messages with the processed data are sent 
    via the `add_message` function.

    - Button presses are processed and displayed.
    - Analog movements are read and filtered based on the dead zone threshold.
    - The angle of movement is calculated, and the data is displayed in degrees and percentage.
    - A margin of time is used to prevent redundant analog events.
    """
    joystick = joystickInit()
    if joystick:
        global last_analog_event_time
        while True:
            try:
                for event in pygame.event.get():
                    if event.type == pygame.JOYBUTTONDOWN:
                        # Process button events
                        button = event.button
                        add_message(KEY_MAPS[button], "normal")
                        #sendMessage(KEY_MAPS[button], 0, 0)
                    elif event.type == pygame.JOYAXISMOTION:
                        # Process analog stick events
                        axis = event.axis
                        percent = value = event.value

                        if axis == 0 or axis == 1:
                            name = "SL"
                            x_axis = joystick.get_axis(0)
                            y_axis = joystick.get_axis(1)
                        elif axis == 2 or axis == 3:
                            name = "SR"
                            x_axis = joystick.get_axis(2)
                            y_axis = joystick.get_axis(3)
                        else:
                            continue

                        # Apply the dead zone filter
                        if abs(x_axis) < DEADZONE_THRESHOLD:
                            x_axis = 0
                        if abs(y_axis) < DEADZONE_THRESHOLD:
                            y_axis = 0

                        # Calculate the angle in radians
                        radians = math.atan2(-y_axis, x_axis)
                        degrees = math.degrees(radians)
                        percent = round(percent*100)
                      
                        if degrees < 0:
                            degrees += 360
                       
                        degrees_int = int(degrees)

                        message = f"{name} Ángulo: {degrees_int} grados Porcentaje: {percent}"

                        # Check if the margin of time has passed since the last analog event
                        if time.time() - last_analog_event_time > MARGIN_TIME:
                            # If time has passed, update the last event time and process the current event
                            last_analog_event_time = time.time()
                            print(f"{name}",degrees_int,f"{percent}")
                            add_message(message, "normal")

            except KeyboardInterrupt:
                pass
            
            time.sleep(0.5)
