<!-- Titulo del proyecto -->

<h1>MAW - Mobile Arm WiFi</h1>
<p><strong>Sistema Robótico Móvil con Control Remoto y Transmisión de Video</strong></p>
<hr>

<!-- Logo -->
<div align="center">
  <img src="https://github.com/leonelg99/TDP1-MAW/blob/main/docs/maw.jpg" width="35%">
</div>

<h2>Tabla de Contenidos</h2>
<ol>
  <li><a href="#resumen-del-proyecto">Resumen del Proyecto</a></li>
  <li><a href="#autores">Autores</a></li>
  <li><a href="#características-principales">Características Principales</a></li>
  <li><a href="#tecnologías-utilizadas">Tecnologías Utilizadas</a></li>
  <li><a href="#requisitos-previos">Requisitos Previos</a></li>
  <li><a href="#guía-de-instalación">Guía de Instalación</a></li>
  <li><a href="#guía-de-uso">Guía de Uso</a></li>
  <li><a href="#licencia">Licencia</a></li>
</ol>
<hr>
<!-- Descripción del proyecto -->

<h2 id="resumen-del-proyecto">Resumen del Proyecto</h2>
<p><strong>MAW (Mobile Arm Wifi)</strong> es un robot de cuatro ruedas controlado remotamente por Wi-Fi con video en tiempo real mediante una cámara integrada. Utiliza una EDU-CIAA-NXP para el control de sensores y motores, y un ESP32-CAM para la conectividad. Incluye una estructura física impresa en 3D y un shield electrónico personalizado.</p>
<p>Una aplicación en Python permite controlar el robot desde una PC con joystick.</p>
<blockquote>Nota: Las consideraciones específicas para el Cliente, ESP32 y EDU-CIAA se encuentran en sus respectivos README dentro de cada subdirectorio.</blockquote>


<h2 id="características-principales"><i>:memo: Características del proyecto</i></h2>
<ul>
  <li>Control remoto por joystick (movimiento, luces, cámara)</li>
  <li>Transmisión de video SVGA (800x600)</li>
  <li>Lectura de nivel de batería con alertas</li>
  <li>Diseño modular (ESP32-CAM / EDU-CIAA / App PC)</li>
  <li>Código embebido con FreeRTOS y sAPI</li>
</ul>

<h2 id="tecnologías-utilizadas"><i>🛰️ Tecnologías Utilizadas</i></h2>
<p><strong>Hardware:</strong></p>
<ul>
  <li>ESP32-CAM con cámara OV2640</li>
  <li>EDU-CIAA-NXP (ARM Cortex-M4)</li>
  <li>Shield L293D + 74HC595</li>
  <li>4 Motores DC, servomotores opcionales</li>
  <li>Step-down LM2596</li>
  <li>Chasis 3D (PLA)</li>
</ul>
<p><strong>Software:</strong></p>
<ul>
  <li>C (sAPI para EDU-CIAA)</li>
  <li>Arduino + FreeRTOS (ESP32)</li>
  <li>Python 3 (Tkinter, Pygame, Pillow)</li>
  <li>Proteus (diseño de PCB)</li>
</ul>

<!-- Prerequisitos SOFTWARE -->
<h1 id="requisitos-previos">🛠️ Requisitos Previos</h1>
<ul>
  <li>Python 3.8+</li>
  <li>Arduino IDE + soporte ESP32</li>
  <li>CIAA Launcher y Firmware_v3</li>
  <li>Paquetes Python: <code>tkinter</code>, <code>pygame</code>, <code>pillow</code></li>
</ul>

---

<!-- Prerequisitos ESP32 -->
<h2 id="guía-de-instalación">🛠️ Guía de Instalación</h2>
<h3>1. Clonar el Repositorio</h3>
<pre><code>git clone https://github.com/leonelg99/TDP1-MAW.git
cd TDP1-MAW
</code></pre>

<h3>2. Programar la EDU-CIAA</h3>
<ul>
  <li>Abrir <code>EDU-CIAA/</code> con CIAA Launcher</li>
  <li>Compilar y grabar en la placa</li>
</ul>

<h3>3. Programar el ESP32-CAM</h3>
<ul>
  <li>Abrir <code>ESP32/</code> en Arduino IDE</li>
  <li>Seleccionar "AI Thinker ESP32-CAM"</li>
  <li>Subir el sketch</li>
</ul>

<h3>4. Aplicación de Control (PC)</h3>
<pre><code>pip install tkinter pygame pillow
python3 CLI/main.py
</code></pre>
<p>Conectar el joystick antes de ejecutar.</p>

<h3>5. Montaje</h3>
<ul>
  <li>Ensamblar robot con partes impresas en 3D</li>
  <li>Verificar cableado, fuente y placas</li>
</ul>

<h2 id="guía-de-uso">Guía de Uso</h2>
<ol>
  <li>Conectar joystick a la PC</li>
  <li>Encender el robot</li>
  <li>Conectarse al Wi-Fi del ESP32</li>
  <li>Ejecutar <code>control_pc/main.py</code></li>
  <li>Controlar desde joystick:
    <ul>
      <li>Movimiento</li>
      <li>Luces</li>
    </ul>
  </li>
  <li>Visualizar video y logs en la interfaz</li>
</ol>



<h1 id="autores">✒️ Autores</h1>

| Autor                     | GitHub                                                                                                           |
| ------------------------- | ---------------------------------------------------------------------------------------------------------------- |
| **Guerrico Leonel**       | [![Repo](https://badgen.net/badge/icon/leonelg99?icon=github&label)](https://github.com/leonelg99)               |
| **Octavio Perez Balcedo** | [![Repo](https://badgen.net/badge/icon/OctavioPB1?icon=github&label)](https://github.com/OctavioPB1)       |
| **Ossola Florencia**      | [![Repo](https://badgen.net/badge/icon/florencia-ossola?icon=github&label)](https://github.com/florencia-ossola) |


<h1 id="coordinador">📌 Coordinador</h1>

<p>Profesores a cargo de la cátedra “Taller de Proyecto 1” de la Facultad de Ingeniería de la Universidad Nacional de La Plata.</p>

---

<!-- Licencia -->
<h1 id="licencia">📄 Licencia</h1>
<details>
  <summary>Licencia</summary>
  <p>Este proyecto está bajo la Licencia <b>GPL-3.0 license</b>.</p>
  <p>Mira el archivo <code>LICENSE</code> para más detalles.</p>
</details>
