# Cliente - MAW

Este cliente fue desarrollado para el proyecto **MAW** con el objetivo de facilitar la interacción entre el usuario y el vehículo. Está programado en **Python** e integra diversas librerías necesarias para su funcionamiento.

---

## 📌 Funcionalidad
El cliente permite la comunicación entre el usuario y el vehículo, abarcando las siguientes tareas:

### 🔹 Visualización de datos
Durante la ejecución del cliente, el usuario podrá observar información relevante incluyendo:
- **Transmisión de video** del vehículo.
- **Mensajes entrantes y salientes**

### 🔹 Control del vehículo
- **Envío de instrucciones mediante un joystick** para manejar el vehículo.

### 🔹 Intercambio de mensajes
- **Comunicación bidireccional con el ESP32**, permitiendo el envío y recepción de datos.

---

## 📂 Estructura del Cliente
El cliente está compuesto por las siguientes librerías, ubicadas dentro de la carpeta `CLI`:

| Módulo               | Descripción |
|----------------------|-------------|
| **CLI**             | Programa principal, crea la ventana e inicializa los threads necesarios. |
| **Connection**      | Manejo de mensajes: creación, envío y recepción. |
| **Interfaz**        | Crea la ventana principal y actualiza la cámara. |
| **Joystick**        | Configuración y lectura del joystick. |
| **Shared_variables**| Contiene las variables de configuración de la IP y puerto del ESP32-CAM. |
| **Video**           | Maneja la transmisión del video y la recepción de imágenes de la cámara. |

---

## ⚙️ Pasos Previos a la Ejecución

### 📌 Requisitos
Para ejecutar el cliente correctamente, es necesario instalar las siguientes librerías:
```sh
pip install tkinter pygame opencv-python pillow urllib3 numpy
```

### 📌 Configuración previa
El cliente debe estar conectado a la red generada por el **ESP32**. Aunque existen valores predeterminados para la IP y el puerto, estos pueden modificarse en los siguientes archivos:

- **`shared_variables.py`**:
  ```python
  ESP32_CAM_IP = "192.168.4.1"
  ESP32_CAM_PORT = 80
  ```

- **`video.py`**:
  ```python
  URL = "http://192.168.4.1:8020"
  ```

---

## 🚀 Ejecución del Cliente
Para ejecutar el cliente, se debe el siguiente comando en la terminal desde el directorio CLI del proyecto del cliente:
```sh
python CLI.py
```
Esto iniciará la interfaz del cliente y establecerá la conexión con el ESP32.

---

## 🎮 Controles

### ✅ Controles testeados y funcionando
- **2**: Encender/Apagar LED de la cámara.
- **Start**: Encender/Apagar LEDs frontales.
- **SR**: Adelante/Atrás/Rotar/Doblar.

### ⚠️ Controles no implementados o no testeados
- **1**: Cambio de resolución de la cámara.
- **Select**: Activar/Desactivar brazo robótico.
- **R2**: Freno/Abrir garra.
- **R1**: Cerrar garra.
- **L1**: Abrir garra completamente.
- **L2**: Cerrar garra completamente.
- **R3**: Brazo regresa a su posición de estacionamiento.
- **SL**: Control del brazo (elevar/bajar).

---

## ⚠️ Advertencias
- **No presionar el botón MODE** conectado al vehículo, ya que podría generar un error que requiera reiniciar el sistema.