import pygame
import time
from interfaz import add_message
from connection import sendMessage
import math
import time

# Define el margen de tiempo en segundos
MARGIN_TIME = 0.5

# Variable para almacenar el tiempo del último evento de analógico
last_analog_event_time = 0

# Define el umbral para la zona muerta
DEADZONE_THRESHOLD = 0.1

#Mapeo de botones
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

# Inicializa el joystick
def joystickInit():
    pygame.init()# Inicializar el joystick
    pygame.joystick.init()
    
    while(pygame.joystick.get_count()<=0):
        add_message("Conecte un joystick","warning")
        time.sleep(2)

    joystick = pygame.joystick.Joystick(0)  # Selecciona el primer joystick
    joystick.init()
    return joystick

# Lee los eventos del joystick
def joystickRead():
    joystick = joystickInit()
    if joystick:
        global last_analog_event_time
        while True:
            try:
                for event in pygame.event.get():
                    if event.type == pygame.JOYBUTTONDOWN:
                        # Procesa los eventos de botón
                        button = event.button
                        add_message(KEY_MAPS[button], "normal")
                        #sendMessage(KEY_MAPS[button], 0, 0)
                    elif event.type == pygame.JOYAXISMOTION:
                        # Procesa los eventos de movimiento de los analógicos
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

                        # Aplica el filtro de zona muerta
                        if abs(x_axis) < DEADZONE_THRESHOLD:
                            x_axis = 0
                        if abs(y_axis) < DEADZONE_THRESHOLD:
                            y_axis = 0

                        # Calcula el ángulo en radianes
                        radians = math.atan2(-y_axis, x_axis)
                        degrees = math.degrees(radians)
                        percent = round(percent*100)
                      
                        if degrees < 0:
                            degrees += 360
                       
                        degrees_int = int(degrees)

                        message = f"{name} Ángulo: {degrees_int} grados Porcentaje: {percent}"

                        # Verifica si ha pasado el margen de tiempo desde el último evento de analógico
                        if time.time() - last_analog_event_time > MARGIN_TIME:
                            # Si ha pasado, actualiza el tiempo del último evento y procesa el evento actual
                            last_analog_event_time = time.time()
                            print(f"{name}",degrees_int,f"{percent}")
                            add_message(message, "normal")

            except KeyboardInterrupt:
                pass
            
            time.sleep(0.5)
