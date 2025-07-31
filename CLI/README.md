<h1>MAW CLI — Cliente de Control (Python)</h1>

<h2>Descripción</h2>
<p><strong>MAW CLI</strong> es la interfaz de usuario desarrollada en Python para controlar el robot MAW desde una PC. Permite enviar comandos de movimiento, encender/apagar luces y visualizar el video en tiempo real procedente del módulo ESP32-CAM.</p>
<blockquote>El CLI se ejecuta en paralelo con múltiples hilos (<em>threads</em>) para gestionar la ventana principal, lectura del joystick, recepción de mensajes y streaming de video según el diseño descrito en el informe final.</blockquote>

<details>
  <summary>📝 Características Principales</summary>
  <ul>
    <li>Interfaz gráfica con <code>Tkinter</code> para video y consola de mensajes</li>
    <li>Lectura de joystick mediante <code>pygame</code></li>
    <li>Arquitectura de 4 <em>threads</em> para concurrencia: GUI, joystick, conexión, y video</li>
  </ul>
</details>

<details>
  <summary>🚁️ Tecnologías y Librerías</summary>
  <ul>
    <li><strong>Python 3.x</strong></li>
    <li><strong>Tkinter</strong> — Interfaz gráfica de la ventana principal</li>
    <li><strong>Pillow (PIL)</strong> — Procesamiento de imágenes</li>
    <li><strong>Pygame</strong> — Lectura de joystick</li>
    <li><strong>Threading</strong> — Ejecución concurrente</li>
    <li><strong>Socket/TCP</strong> — Comunicación con ESP32-CAM</li>
  </ul>
</details>

<h2>📚 Tabla de Contenidos</h2>
<ol>
  <li><a href="#prerequisitos">Prerequisitos</a></li>
  <li><a href="#instalacion">Instalación</a></li>
  <li><a href="#ejecucion">Ejecución</a></li>
  <li><a href="#estructura-de-archivos">Estructura de Archivos</a></li>
</ol>
<hr>

<h2 id="prerequisitos">🛠️ Prerequisitos</h2>
<ul>
  <li><strong>Python 3.8 o superior</strong></li>
  <li><strong>Joystick USB</strong> compatible</li>
  <li>Paquetes de Python:</li>
</ul>
<pre><code>pip install tkinter pygame pillow
</code></pre>
<ul>
  <li>Red Wi-Fi con acceso al ESP32-CAM (SSID y contraseña definidos en el firmware)</li>
</ul>
<hr>

<h2 id="instalacion">⚙️ Instalación</h2>
<ol>
  <li>Navega al directorio del CLI:</li>
</ol>
<pre><code>cd CLI
</code></pre>
<ol start="2">
  <li>Instala dependencias si es necesario:</li>
</ol>
<pre><code>pip install tkinter pygame pillow
</code></pre>
<hr>

<h2 id="ejecucion">🚀 Ejecución</h2>
<ol>
  <li>Conecta el joystick a la PC.</li>
  <li>Asegúrate de estar en la red Wi-Fi generada por el ESP32-CAM.</li>
  <li>Ejecuta el cliente:</li>
</ol>
<pre><code>python main.py
</code></pre>
<ol start="4">
  <li>La interfaz mostrará el video a la izquierda y la consola de mensajes a la derecha.</li>
  <li>Controles del joystick:</li>
</ol>
<ul>
  <li>Stick derecho: movimiento (adelante, atrás, girar)</li>
  <li>Botón 2: flash de cámara</li>
  <li>R2: frenar vehículo</li>
</ul>
<hr>

<h2 id="estructura-de-archivos">📂 Estructura de Archivos</h2>
<pre><code>CLI/
├── main.py        # Punto de entrada de la aplicación
├── connection.py  # Envío y recepción de mensajes TCP
├── joystick.py    # Inicialización y lectura de joystick
├── gui.py         # Diseño de ventana con Tkinter
├── video.py       # Streaming de video con receiveImage()
└── utils.py       # add_message(), update_camera(), formato de mensajes
</code></pre>
<hr>
