import socket
from shared_variables import ESP32_CAM_IP, ESP32_CAM_PORT
from interfaz import WINDOW,add_message
import time

# Crea el mensaje a enviar
def makeMessage(data,data2,data3):
    message= "cmd:"+str(data)+":"+str(data2)+":"+str(data3)+"\n"  
    return message.encode()

# Envia el mensaje
def sendMessage(data,data2,data3):
    try:
        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
         s.connect((ESP32_CAM_IP,ESP32_CAM_PORT))
         s.sendall(makeMessage(data,data2,data3))
    except Exception as e:
       add_message("Error al enviar comando: "+str(e),"error")
    finally:
        s.close()  

# Recibe los mensajes
def reciveMessages():
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
    