import pygame
import time

def read_joystick():
    pygame.init()
    joystick = pygame.joystick.Joystick(0)
    joystick.init()

    last_sent_time = time.time()
    interval = 1  # Intervalo de tiempo entre cada envío en segundos
    threshold = 0.1  # Umbral de cambio mínimo para enviar una lectura

    last_x_axis = 0
    last_y_axis = 0
    last_sent_x_axis = None
    last_sent_y_axis = None

    while True:
        current_time = time.time()
        time_since_last_sent = current_time - last_sent_time

        # Leer el estado del joystick
        pygame.event.get()
        x_axis = joystick.get_axis(0)
        y_axis = joystick.get_axis(1)

        # Verificar si ha pasado suficiente tiempo desde el último envío o si hay un cambio significativo
        if (time_since_last_sent >= interval and
                (x_axis != last_sent_x_axis or y_axis != last_sent_y_axis) or
                abs(x_axis - last_x_axis) >= threshold or
                abs(y_axis - last_y_axis) >= threshold):
            send_to_esp32(x_axis, y_axis)

            # Actualizar los valores anteriores y el tiempo de envío
            last_x_axis = x_axis
            last_y_axis = y_axis
            last_sent_x_axis = x_axis
            last_sent_y_axis = y_axis
            last_sent_time = current_time

        # Esperar un pequeño tiempo antes de la próxima iteración
        time.sleep(0.01)

def send_to_esp32(x_axis, y_axis):
    # Aquí puedes enviar los valores al ESP32 para realizar ciertas acciones
    print("X axis:", x_axis, "Y axis:", y_axis)

read_joystick()
