"""
This module handles communication with the ESP32-CAM using TCP sockets.
It allows sending and receiving messages to control the device and retrieve data.
"""
import socket
from shared_variables import ESP32_CAM_IP, ESP32_CAM_PORT
from interfaz import WINDOW,add_message
import time

def makeMessage(data,data2,data3):
    """
    Creates a command message in the required format.

    Args:
        data (int/str): Primary command or action.
        data2 (int/str): Additional parameter for the command.
        data3 (int/str): Additional parameter for the command.

    Returns:
        bytes: Encoded command message.
    """
    message= "cmd:"+str(data)+":"+str(data2)+":"+str(data3)+"\n"  
    return message.encode()


def sendMessage(data,data2,data3):
    """
    Sends a command message to the ESP32-CAM over a TCP connection.

    Args:
        data (int/str): Primary command or action.
        data2 (int/str): Additional parameter for the command.
        data3 (int/str): Additional parameter for the command.

    Returns:
        None
    """
    try:
        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
         s.connect((ESP32_CAM_IP,ESP32_CAM_PORT))
         s.sendall(makeMessage(data,data2,data3))
    except Exception as e:
       add_message("Error al enviar comando: "+str(e),"error")
    finally:
        s.close()  


def reciveMessages():
    """
    Continuously receives messages from the ESP32-CAM.

    - Connects to the ESP32-CAM via TCP.
    - Sends a request to retrieve data.
    - Receives and processes incoming messages.
    - Displays received messages in the GUI.

    Runs in a loop with a short delay to avoid excessive requests.

    Returns:
        None
    """
    while True:
        try:
            with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
                s.connect((ESP32_CAM_IP,ESP32_CAM_PORT))
                s.sendall("get:0:0:0\n".encode())
                data = s.recv(1024).decode('utf-8')
                if(data != ""):
                    print(data)
                    add_message(data,"success")
        except Exception as e:
            add_message("Error al recibir comando: "+str(e),"error")
        finally:
            s.close()
        time.sleep(0.2)
    