<h1>MAW ESP32-CAM — Firmware y Configuración</h1>

<h2>Descripción</h2>
<p>Este subdirectorio incluye el firmware y los recursos necesarios para el módulo <strong>ESP32-CAM</strong>, responsable de la conectividad Wi-Fi y la transmisión de video en el proyecto MAW.</p>
<blockquote>El código está organizado con FreeRTOS para manejar tareas de cámara, Wi-Fi y comunicación con la EDU-CIAA. El diseño modular se detalla en el informe final. :contentReference[oaicite:1]{index=1}</blockquote>

<details>
  <summary>📝 Módulos Principales</summary>
  <ul>
    <li><code>camera_task.c/h</code>: Captura y envío de frames</li>
    <li><code>wifi_task.c/h</code>: Gestión de conexión Wi-Fi y servidor web</li>
    <li><code>conn_task.c/h</code>: Comunicación UART/TCP con EDU-CIAA</li>
    <li><code>main.c</code>: Inicialización de FreeRTOS y creación de tareas</li>
  </ul>
</details>

<details>
  <summary>🚀 Funcionalidad Clave</summary>
  <ul>
    <li>Captura de imágenes con sensor OV2640 y buffer DMA</li>
    <li>Servidor web para streaming MJPEG por HTTP</li>
    <li>Modo AP</li>
    <li>Intercambio de comandos y datos con EDU-CIAA vía UART/TCP</li>
  </ul>
</details>

<h2>📚 Tabla de Contenidos</h2>
<ol>
  <li><a href="#prerequisitos">Prerequisitos</a></li>
  <li><a href="#instalacion-ide">Instalación IDE (Arduino IDE)</a></li>
  <li><a href="#configuracion">Configuración de Variables</a></li>
  <li><a href="#compilacion-y-flasheo">Compilación y Flasheo</a></li>
  <li><a href="#uso">Uso y Pruebas</a></li>
  <li><a href="#estructura-de-archivos">Estructura de Archivos</a></li>
  <li><a href="#contribuciones">Contribuciones</a></li>
  <li><a href="#licencia">Licencia</a></li>
</ol>
<hr>

<h2 id="prerequisitos">🛠️ Prerequisitos</h2>
<ul>
  <li>Arduino IDE con soporte para ESP32 (<em>Espressif</em> board manager)</li>
  <li>Bibliotecas: <code>esp32-camera</code>, <code>WiFi</code>, <code>ESPAsyncWebServer</code></li>
  <li>Cable USB y drivers para ESP32-CAM</li>
</ul>
<hr>

<h2 id="instalacion-ide">⚙️ Instalación IDE (Arduino IDE)</h2>
<ol>
  <li>Abre Arduino IDE y añade el URL de placas ESP32 en <em>Preferences &gt; Additional Boards Manager URLs</em>.</li>
  <li>Instala el paquete <strong>esp32 by Espressif Systems</strong> desde Boards Manager.</li>
  <li>Asegúrate de tener las bibliotecas instaladas:
    <ul>
      <li><code>esp32-camera</code></li>
      <li><code>WiFi</code></li>
      <li><code>ESPAsyncWebServer</code></li>
    </ul>
  </li>
</ol>
<hr>

<h2 id="configuracion">🔧 Configuración de Variables</h2>
<ol>
  <li>Abre <code>firmware_esp32/firmware_esp32.ino</code> o <code>main.c</code>.</li>
  <li>Define tu SSID y PASSWORD en las constantes:
    <pre><code>#define WIFI_SSID "Tu_SSID"
#define WIFI_PASS "Tu_PASSWORD"
</code></pre>
  </li>
  <li>Configura el pin de reset de la cámara si tu módulo lo requiere.</li>
</ol>
<hr>

<h2 id="compilacion-y-flasheo">💾 Compilación y Flasheo</h2>
<ol>
  <li>Selecciona la placa <strong>AI Thinker ESP32-CAM</strong> en <em>Tools &gt; Board</em>.</li>
  <li>Selecciona el puerto serial correcto.</li>
  <li>Haz clic en <em>Upload</em> para compilar y flashear el firmware.</li>
  <li>Abre el <em>Serial Monitor</em> a 115200 bps para ver mensajes de arranque.</li>
</ol>
<hr>

<h2 id="uso">📈 Uso y Pruebas</h2>
<ol>
  <li>Tras flashear, el ESP32-CAM intentará conectarse a tu red Wi-Fi.</li>
  <li>Si tiene éxito, mostrará la IP asignada en el Serial Monitor.</li>
  <li>Abre un navegador y navega a <code>http://IP_ASIGNADA:8080</code> para ver el streaming.</li>
  <li>Prueba enviar comandos desde el CLI MAW para verificar la comunicación con EDU-CIAA.</li>
</ol>
<hr>

<h2 id="estructura-de-archivos">📂 Estructura de Archivos</h2>
<pre><code>firmware_esp32/
├── camera_task.c
├── wifi_task.c
├── conn_task.c
├── main.c
├── platformio.ini  # Si usas PlatformIO
├── firmware_esp32.ino  # Si usas Arduino IDE
└── README.html       # Este archivo
</code></pre>
<hr>

