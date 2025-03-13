<!-- Titulo del proyecto -->

# Proyecto - MAW (Movil Arm Wifi)

<!-- Logo -->
<div align="center">
  <img src="https://github.com/tpII/2024-A2-LIDAR-Vl53l0/blob/master/Doc/Img/IMG-20250205-WA0008.jpg" width="35%">
</div>

<!-- Descripción del proyecto -->

Desde el momento en que decidimos inscribirnos en la materia de **Taller de Proyecto 1** debatimos distintas ideas para llevar a cabo en la misma. 
Para ello nos basamos en 2 ejes principales, que sea móvil, es decir que proyectó fuera “algo” que se mueva y no algo estático; y por otro lado algo que a criterio personal nuestro, fuera divertido y desafiante, al mismo tiempo que nos permitiera sacar provecho de la placa (**EDU-CIAA**) dentro de los límites de la materia.
A partir de estas premisas, se nos ocurrieron varias ideas que en principio nos gustaron para llevar a cabo, terminando por elegir el diseño e implementacion de un vehiculo robot.
No obstante, la idea de un vehículo a criterio personal no nos parecía suficiente por sí misma, por lo que decidimos complementar la misma con un brazo robótico y una cámara, que además podremos controlar mediante una conexión WIFI.
Este vehículo se inspira principalmente en los robots para desactivación de artefactos explosivos que las fuerzas de seguridad utilizan alrededor del mundo, los cuales generalmente constan de un vehículo con un brazo robótico, una cámara y medio de control a distancia.


<details>
  <summary><i>:memo: Características del proyecto</i></summary>
  <ol>
    <li><b>Transmision de Video<b></li>
    <p>Se puede decir que es la base del proyecto. Se realiza mediante el **ESP32-CAM** (version del ESP32 con una camara integrada) el cual establece un transmision de video mediante HTTP, la cual es captada por el CLI. De esta manera se puede controlar el vehiculo a distancia.</p>
    <li>Access Point</li>
    <p>El ESP32 actúa como punto de acceso (AP) para la conexión. De este modo la pc donde se ejectute el cliente (CLI) debe conectarse al la red del ESP32.</p>
    <li>Desarrollo Modular</li>
    <p>El programa está diseñado de manera modular, con componentes separados por funcionalidad, facilitando el mantenimiento y la extensión del proyecto.</p>
    <li>Replicabilidad</li>
    <p>El proyecto está documentado lo suficiente como para permitir replicar el control de un robot similar utilizando el hardware indicado.</p>
    <li>Extensibilidad</li>
    <p>Es posible ampliar el sistema para añadir mejoras de rendimiento o nuevas funcionalidades.</p>
  </ol>
</details>

<details> 
  <summary><i>:satellite: Tecnologías utilizadas</i></summary>
  <ol> 
    <li>Aplicación web</li>
    <ul> 
      <li>Angular 18: framework frontend utilizado para la construcción de la interfaz de usuario, con un enfoque en componentes independientes y organización modular.</li>
      <li>Angular Material: utilizado para el diseño de la interfaz, proporcionando componentes estilizados y responsivos para una experiencia de usuario consistente.</li>
      <li>HTML, CSS y TypeScript: fundamentales para la estructura, estilo y lógica de la aplicación web, aprovechando las capacidades tipadas de TypeScript para un desarrollo más robusto.</li>
    </ul> 
    <li>Backend</li>
    <ul>
      <li>Java (Spring Boot): framework utilizado para construir el servidor backend, gestionando las solicitudes HTTP y la lógica de negocio.</li>
      <li>Maven: herramienta de gestión de dependencias y construcción del proyecto backend, asegurando un ciclo de desarrollo eficiente.</li>
      <li>MongoDB: base de datos NoSQL utilizada para almacenar la información persistente de la aplicación, con un enfoque en flexibilidad y escalabilidad.</li>
    </ul>
    <li>Comunicación en tiempo real</li>
    <ul>
      <li>Mosquitto Broker (MQTT): utilizado para la comunicación en tiempo real entre la aplicación web y el ESP32, permitiendo la transmisión de datos de forma eficiente y ligera.</li>
    </ul> 
    <li>ESP32</li>
    <ul>
      <li>Modo Soft AP: configurado como punto de acceso para permitir la conexión directa de dispositivos al ESP32.</li>
      <li>Programación en C: se utilizó para implementar la lógica de control del ESP32, incluyendo el manejo de sensores, motores y comunicación MQTT.</li>
      <li>PlatformIO: entorno de desarrollo integrado en Visual Studio Code para la programación y gestión del firmware del ESP32.</li>
      <li>DC Motors: utilizados para el movimiento del dispositivo, controlados mediante PWM para un desplazamiento preciso.</li>
      <li>Servo: utilizado para movimientos angulares específicos, controlado también mediante PWM.</li>
      <li>Sensores I2C: dos sensores conectados al ESP32 mediante el protocolo I2C para la recopilación de datos en tiempo real.</li>
    </ul>
  </ol>
</details>

<!-- Tabla de contenidos -->
<h1 id="table-of-contents">:book: Tabla de contenidos</h1>
<details open="open">
  <summary>Tabla de contenidos</summary>
  <ol>
    <li><a href="#prerequisites-software">➤ Prerequisitos-Software</a></li>
    <li><a href="#installation-esp32">➤ Instalación y Configuración del ESP32</a></li>
    <li><a href="#installation-mosquitto-broker">➤ Instalación y Configuración del Broker MQTT</a></li>
    <li><a href="#installation-backend">➤ Instalación y Configuración del Backend</a></li>
    <li><a href="#installation-mongodb">➤ Instalación y Configuración de MongoDB</a></li>
    <li><a href="#installation-frontend">➤ Instalación y Configuración del Frontend<</a></li>
    <li><a href="#execution-steps">➤ Pasos para la Ejecución del Proyecto</a></li>
    <li><a href="#video">➤ Video demostrativo</a></li>
    <li><a href="#bitacora">➤ Bitácora</a></li>
    <li><a href="#authors">➤ Autores</a></li>
    <li><a href="#coordinador">➤ Coordinador</a></li>
  </ol>
</details>

<!-- Prerequisitos SOFTWARE -->
<h1 id="prerequisites-software">🛠️ Prerequisitos-Software</h1>
<details>
  <summary>Prerequisitos-Software</summary>
  <p>El proyecto requiere la instalación de los siguientes componentes de software:</p>
  <ul>
    <li>
      <b>Visual Studio Code:</b> Editor de código necesario para el desarrollo tanto del frontend y backend, como del firmware para el ESP32.
    </li>
    <li>
      <b>PlatformIO:</b> Extensión de Visual Studio Code utilizada para compilar y cargar el firmware en el ESP32.
    </li>
    <li>
      <b>Java:</b> Requerido para ejecutar el backend en Spring Boot.
    </li>
    <li>
      <b>Maven:</b> Herramienta de gestión de dependencias y construcción para el backend en Spring Boot.
    </li>
    <li>
      <b>Node.js:</b> Necesario para Angular, incluyendo el uso de npm para la instalación de dependencias.
    </li>
    <li>
      <b>MongoDB:</b> Base de datos NoSQL utilizada para el almacenamiento de datos de la aplicación.
    </li>
    <li>
      <b>Broker Mosquitto:</b> Servidor MQTT utilizado para la comunicación en tiempo real con el ESP32.
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

---

<!-- Prerequisitos BROKER MQTT-->
<h1 id="installation-mosquitto-broker">🕸️ Instalación y Configuración del Broker MQTT</h1>
<details>
  <summary>Instalación y Configuración del Broker Mosquitto</summary>
  <ol>
    <li>Descarga el instalador de Mosquitto MQTT Broker desde el sitio oficial de Eclipse Mosquitto: <a href="https://mosquitto.org/download/">https://mosquitto.org/download/</a>.</li>
    <li>Ejecuta el instalador y sigue las instrucciones para completar la instalación.</li>
    <li>Dirígete a la carpeta de instalación. Por defecto, se encuentra en:
      <pre><code>C:\Program Files\mosquitto</code></pre>
    </li>
    <li>Configura el Broker editando el archivo <code>mosquitto.conf</code> con un editor de texto (ej. Notepad++ o Visual Studio Code). Añade las siguientes líneas para permitir conexiones anónimas y habilitar la salida de eventos por consola:
      <pre><code>
listener 1883
allow_anonymous true
log_type all
connection_messages true
log_timestamp true
      </code></pre>
    </li>
    <li>Guarda los cambios en el archivo de configuración.</li>
    <li>Abre una consola en modo administrador y navega hasta la carpeta de instalación:
      <pre><code>cd "C:\Program Files\mosquitto"</code></pre>
    </li>
    <li>Inicia el Broker Mosquitto utilizando el siguiente comando:
      <pre><code>mosquitto -v -c mosquitto.conf</code></pre>
      <p>Este comando inicia el Broker en modo verbose, mostrando todos los eventos y conexiones en tiempo real en la consola.</p>
    </li>
    <li>El Broker MQTT ahora debería estar en funcionamiento y listo para gestionar las conexiones.</li>
  </ol>
</details>

---

<!-- Prerequisitos BACKEND -->
<h1 id="installation-backend">🔧 Instalación y Configuración del Backend</h1>
<details>
  <summary>Instalación y Configuración del Servidor Backend</summary>
  <ol>
    <li>Abre Visual Studio Code y clona el repositorio.</li>
    <li>Posicionate en la carpeta del repositorio: <code>2024-A2-LIDAR-VL53L0X</code>.</li>
    <li>Accede a la carpeta del backend con el siguiente comando:</li>
    <pre><code>cd backend</code></pre>
    <li>En la consola, ejecuta el siguiente comando para instalar las dependencias del proyecto:</li>
    <pre><code>mvn clean install</code></pre>
    <li>Para levantar el servidor, ejecuta el siguiente comando:</li>
    <pre><code>mvn spring-boot:run</code></pre>
    <li>El servidor se iniciará y quedará a la espera de conectarse a la red del ESP32.</li>
  </ol>
  <p>El backend estará listo para funcionar con el ESP32.</p>
</details>

---

<!-- Prerequisitos MongoDB -->
<h1 id="installation-mongodb">📦 Instalación y Configuración de MongoDB</h1>
<details>
  <summary>Instalación de MongoDB</summary>
  <ol>
    <li>Descarga e instala MongoDB desde el instalador oficial.</li>
    <li>No es necesaria ninguna configuración adicional, solo asegúrate de habilitar la ejecución en segundo plano.</li>
    <li>El backend se conectará automáticamente a MongoDB al levantarse el servidor.</li>
  </ol>
  <p>MongoDB estará listo para almacenar los datos del proyecto.</p>
</details>

---

<!-- Prerequisitos FRONTEND -->
<h1 id="installation-frontend">🌐 Instalación y Configuración del Frontend</h1>
<details>
  <summary>Instalación y Configuración del Servidor Frontend</summary>
  <ol>
    <li>Abre Visual Studio Code y clona el repositorio.</li>
    <li>Posicionate en la carpeta del repositorio: <code>2024-A2-LIDAR-VL53L0X</code>.</li>
    <li>Accede a la carpeta del frontend con el siguiente comando:</li>
    <pre><code>cd Frontend</code></pre>
    <li>En la consola, ejecuta el siguiente comando para instalar las dependencias del proyecto:</li>
    <pre><code>npm install</code></pre>
    <li>Verifica la correcta instalación de Angular ejecutando el siguiente comando:</li>
    <pre><code>ng version</code></pre>
    <li>Para levantar el servidor, ejecuta el siguiente comando:</li>
    <pre><code>ng serve</code></pre>
    <li>La página estará accesible en el siguiente enlace: <a href="http://localhost:4200">http://localhost:4200</a>.</li>
  </ol>
  <p>El frontend estará listo para interactuar con el backend y el ESP32.</p>
</details>


---

<!-- video explicativo-->
<h1 id="video">:clapper: Video del Proyecto </h1>
<p>A continuacion se deja un link, a un video explicativo sobre el robot y su funcionamiento: <a href="https://drive.google.com/file/d/1UwNFf568G4iCPq6gYDLypO1Pdrs1-ocO/view?usp=drive_link">Video</a></p>

<h1 id="bitacora">:bookmark_tabs: Bitácora</h1>

<p>Como parte del proyecto se redacto una bitacora con el "dia a dia" del mismo: <a href="https://github.com/tpII/2024-A4-QLEARNING-ESP32/wiki/Bitacora-A4-%E2%80%90-Crawler-Robot-con-ESP32)">Bitacora</a>.</p>

<h1 id="authors">✒️ Autores</h1>

| Autor                     | GitHub                                                                                                           |
| ------------------------- | ---------------------------------------------------------------------------------------------------------------- |
| **Guerrico Leonel**       | [![Repo](https://badgen.net/badge/icon/leonelg99?icon=github&label)](https://github.com/leonelg99)               |
| **Octavio Perez Balcedo** | [![Repo](https://badgen.net/badge/icon/OctavioPB1?icon=github&label)](https://github.com/OctavioPB1)       |
| **Ossola Florencia**      | [![Repo](https://badgen.net/badge/icon/florencia-ossola?icon=github&label)](https://github.com/florencia-ossola) |

---

<h1 id="coordinador">📌 Coordinador</h1>

| Coordinador                                    | GitHub                                                                                                 |
| ---------------------------------------------- | ------------------------------------------------------------------------------------------------------ |
| **Alan Fabián Castelli** _Profesor - Ayudante_ | [![Repo](https://badgen.net/badge/icon/aCastelli95?icon=github&label)](https://github.com/aCastelli95) |

<!-- Licencia -->
<h1 id="license">📄 Licencia</h1>
<details>
  <summary>Licencia</summary>
  <p>Este proyecto está bajo la Licencia <b>GPL-3.0 license</b>.</p>
  <p>Mira el archivo <code>LICENSE</code> para más detalles.</p>
</details>
