<!-- Titulo del proyecto -->

# Proyecto - MAW (Movil Arm Wifi)

<!-- Logo -->
<div align="center">
  <img src="https://github.com/leonelg99/TDP1-MAW/blob/main/docs/maw.jpg" width="35%">
</div>

<!-- Descripción del proyecto -->

<h2 id="resumen-del-proyecto">Resumen del Proyecto</h2>
<p><strong>MAW (Mobile Arm Wifi)</strong> es un robot de cuatro ruedas controlado remotamente por Wi-Fi con video en tiempo real mediante una cámara integrada. Utiliza una EDU-CIAA-NXP para el control de sensores y motores, y un ESP32-CAM para la conectividad. Incluye una estructura física impresa en 3D y un shield electrónico personalizado.</p>
<p>Una aplicación en Python permite controlar el robot desde una PC con joystick.</p>
<blockquote>Nota: Las consideraciones específicas para el Cliente, ESP32 y EDU-CIAA se encuentran en sus respectivos README dentro de cada subdirectorio.</blockquote>


<details>
  <summary><i>:memo: Características del proyecto</i></summary>
  <ol>
  <li>Control remoto por joystick (movimiento, luces, cámara)</li>
  <li>Transmisión de video SVGA (800x600)</li>
  <li>Diseño modular (ESP32-CAM / EDU-CIAA / App PC)</li>
  <li>Código embebido con FreeRTOS y sAPI</li>
  </ol>
</details>

<details> 
  <summary><i>:satellite: Tecnologías utilizadas</i></summary>
  <ol> 
    <li>Cliente (CLI)</li>
    <ul> 
      <li>Python</li>
      <li>Tkinter: libreria para la implementacion de la interfaz grafica</li>
      <li>PIL: para el procesamiento y manejo de imagenes</li>
      <li>Threading: para la ejecucion de tareas concurrentes</li>
    </ul> 
    <li>Firmware(ESP32-CAM)</li>
    <ul>
      <li>Arduino: libreria e IDE para programar el ESP32-CAM</li>
      <li>FreeRTOS: para la gestión de tareas en tiempo real</li>
    </ul>
    <li>EDU-CIAA</li>
    <ul>
      <li>C: como lenguaje de programacion</li>
      <li>Firmware v3: libreria oficial para la programacion de la EDU-CIAA.</li>
    </ul>
  </ol>
</details>

<!-- Tabla de contenidos -->
<h1 id="table-of-contents">:book: Tabla de contenidos</h1>
<details open="open">
  <summary>Tabla de contenidos</summary>
  <ol>
    <li><a href="#prerequisites">➤ Prerequisitos</a></li>
    <li><a href="#installation-esp32">➤ Instalación y Configuración del ESP32</a></li>
    <li><a href="#installation-edu-ciaa">➤ Instalacion y Configuracion del IDE, herramiente y Firmware para la EDU-CIAA</a></li>
    <li><a href="#installation-cli">➤ Instalacion y Ejecucion del Cliente</a></li>
    <li><a href="#execution-steps">➤ Pasos para la Ejecución del Proyecto</a></li>
    <li><a href="#authors">➤ Autores</a></li>
    <li><a href="#coordinador">➤ Coordinador</a></li>
  </ol>
</details>

<!-- Prerequisitos SOFTWARE -->
<h1 id="prerequisites">🛠️ Prerequisitos</h1>
<details>
  <summary>Prerequisitos</summary>
  <p>El proyecto requiere la instalación de los siguientes componentes de software:</p>
  <ul>
    <li>
      <b>Visual Studio Code:</b> Editor de código necesario para el desarrollo del Cliente.
    </li>
    <li>
      <b>Arduino IDE:</b> Ide para la programacion ESP32.
    </li>
    <li>
      <b>Python:</b> Lenguaje para desarrollar el CLI.
    </li>
    <li>
      <b>IDE EDU-CIAA:</b> Version de Eclipse con todas las herramientas necesarias para programar y testear la EDU-CIAA.
    </li>
  </ul>
</details>

---

<!-- Prerequisitos ESP32 -->
<h1 id="installation-esp32">🛠️ Instalación y Configuración del ESP32</h1>
<details>
  <summary>Instalación y Configuración del ESP32</summary>
  <ol>
    <li>Abre <b>Visual Studio Code</b> y navega a la carpeta del proyecto: <code>2024-A2-LIDAR-VL53L0X</code>.</li>
    <li>Posiciónate en la carpeta <code>Microcontroller</code> (donde se encuentra el código en C).</li>
    <li>Conecta el ESP32 a un puerto USB de la computadora.</li>
    <li>Abrir <b>platformion.ini</b> y modificar <b>upload_port</b> con el numero de puerto al que se conecto el ESP32.</li>
    <li>Desde el menú inferior de <b>PlatformIO</b>, presiona el botón de subida de programa para compilar y cargar el firmware al ESP32.</li>
    <li>O en la consola, ejecutar <b>pio run -t upload<b></li>
  </ol>
  <p>Tras estos pasos, el ESP32 estará configurado y listo para ejecutar las instrucciones del proyecto.</p>
</details>


<h1 id="authors">✒️ Autores</h1>

| Autor                     | GitHub                                                                                                           |
| ------------------------- | ---------------------------------------------------------------------------------------------------------------- |
| **Guerrico Leonel**       | [![Repo](https://badgen.net/badge/icon/leonelg99?icon=github&label)](https://github.com/leonelg99)               |
| **Octavio Perez Balcedo** | [![Repo](https://badgen.net/badge/icon/OctavioPB1?icon=github&label)](https://github.com/OctavioPB1)       |
| **Ossola Florencia**      | [![Repo](https://badgen.net/badge/icon/florencia-ossola?icon=github&label)](https://github.com/florencia-ossola) |

---

<h1 id="coordinador">📌 Coordinador</h1>

<p>Profesores a cargo de la cátedra “Taller de Proyecto 1” de la Facultad de Ingeniería de la Universidad Nacional de La Plata.</p>

<!-- Licencia -->
<h1 id="license">📄 Licencia</h1>
<details>
  <summary>Licencia</summary>
  <p>Este proyecto está bajo la Licencia <b>GPL-3.0 license</b>.</p>
  <p>Mira el archivo <code>LICENSE</code> para más detalles.</p>
</details>
