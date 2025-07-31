# MAW CLI — Cliente de Control (Python)

## Descripción

**MAW CLI** es la interfaz de usuario desarrollada en Python para controlar el robot MAW desde una PC. Permite enviar comandos de movimiento, encender/apagar luces y visualizar el video en tiempo real procedente del módulo ESP32-CAM.

> El CLI se ejecuta en paralelo con múltiples hilos (*threads*) para gestionar la ventana principal, lectura del joystick, recepción de mensajes y streaming de video según el diseño descrito en el informe final. fileciteturn1file0

<details>
<summary>📝 Características Principales</summary>

* Interfaz gráfica con `Tkinter` para video y consola de mensajes
* Lectura de joystick mediante `pygame`
* Arquitectura de 4 *threads* para concurrencia: GUI, joystick, conexión, y video

</details>

<details>
<summary>🛰️ Tecnologías y Librerías</summary>

* **Python 3.x**
* **Tkinter** — Interfaz gráfica de la ventana principal fileciteturn1file2
* **Pillow (PIL)** — Procesamiento de imágenes
* **Pygame** — Lectura de joystick
* **Threading** — Ejecución concurrente
* **Socket/TCP** — Comunicación con ESP32-CAM

</details>

## 📚 Tabla de Contenidos

1. [Prerequisitos](#prerequisitos)
2. [Instalación](#instalaci%C3%B3n)
3. [Ejecución](#ejecuci%C3%B3n)
4. [Estructura de Archivos](#estructura-de-archivos)
5. [Contribuciones](#contribuciones)
6. [Licencia](#licencia)

---

🛠️ ##Prerequisitos

* **Python 3.8 o superior**
* **Joystick USB** compatible
* Paquetes de Python:

  ```bash
  pip install tkinter pygame pillow
  ```
* Red Wi-Fi con acceso al ESP32-CAM (SSID y contraseña definidos en el firmware)

---

## ⚙️ Instalación

1. Navega al directorio del CLI:

   ```bash
   cd control_pc
   ```
2. Instala dependencias si es necesario:

   ```bash
   pip install tkinter pygame pillow
   ```

---

## 🚀 Ejecución

1. Conecta el joystick a la PC.
2. Asegúrate de estar en la red Wi-Fi generada por el ESP32-CAM.
3. Ejecuta el cliente:

   ```bash
   python main.py
   ```
4. La interfaz mostrará el video a la izquierda y la consola de mensajes a la derecha.
5. Controles del joystick:

   * Stick derecho: movimiento (adelante, atrás, girar)
   * Botón 2: flash de cámara
   * R2: frenar vehículo

---

## 📂 Estructura de Archivos {#estructura-de-archivos}

```
control_pc/
├── main.py        # Punto de entrada de la aplicación
├── connection.py  # Envío y recepción de mensajes TCP
├── joystick.py    # Inicialización y lectura de joystick
├── gui.py         # Diseño de ventana con Tkinter
├── video.py       # Streaming de video con receiveImage()
└── utils.py       # add_message(), update_camera(), formato de mensajes
```

## 📄 Licencia {#licencia}

Este subdirectorio forma parte del proyecto MAW, licenciado bajo MIT. Consulta el archivo raíz `LICENSE` para más detalles.
