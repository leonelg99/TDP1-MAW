<h1>MAW EDU-CIAA — Firmware y Configuración</h1>

<h2>Descripción</h2>
<p>Este subdirectorio contiene el código fuente y las instrucciones para programar la placa <strong>EDU-CIAA-NXP</strong>, encargada de la gestión de motores, sensores y lógica embebida del robot MAW.</p>
<blockquote>El firmware está basado en la biblioteca sAPI v3 y organización modular descrita en el informe final. </blockquote>

<details>
  <summary>📝 Módulos Principales</summary>
  <ul>
    <li><code>motorShield2.c/h</code>: Control de drivers L293D y expansión 74HC595</li>
    <li><code>comandos.c/h</code>: Interpretación y envío de comandos</li>
    <li><code>arm.c/h</code>: Lógica de movimiento del brazo (servos)</li>
    <li><code>sapi.c</code>: Adaptación de funciones del firmware sAPI v3</li>
  </ul>
</details>

<details>
  <summary>🚀 Funcionalidad Clave</summary>
  <ul>
    <li>Control de velocidad y dirección de los motores DC</li>
    <li>Lectura de sensores de nivel de batería y disparo de alerta</li>
    <li>Gestión de interrupciones para botones de emergencia</li>
    <li>Comunicación UART/TCP con ESP32-CAM para sinergia de tareas</li>
  </ul>
</details>

<h2>📚 Tabla de Contenidos</h2>
<ol>
  <li><a href="#prerequisitos">Prerequisitos</a></li>
  <li><a href="#instalacion-ide">Instalación IDE (CIAA Launcher)</a></li>
  <li><a href="#compilacion-y-flasheo">Compilación y Flasheo</a></li>
  <li><a href="#uso">Uso y Verificación</a></li>
  <li><a href="#estructura-de-archivos">Estructura de Archivos</a></li>
</ol>
<hr>

<h2 id="prerequisitos">🛠️ Prerequisitos</h2>
<ul>
  <li>Placa <strong>EDU-CIAA-NXP</strong></li>
  <li><strong>CIAA Launcher</strong> instalado (Eclipse + toolchain ARM)</li>
  <li>Firmware sAPI v3 (incluido en <code>lib_sapi/</code>)</li>
  <li>Cables USB y drivers de la EDU-CIAA</li>
</ul>
<hr>

<h2 id="instalacion-ide">⚙️ Instalación IDE (CIAA Launcher)</h2>
<ol>
  <li>Descarga e instala CIAA Launcher desde el sitio oficial de la UNLP.</li>
  <li>Abre <code>firmware_ciaa/MAW_EDU_CIAA.workspace</code> en Eclipse.</li>
  <li>Importa el proyecto C desde el directorio <code>firmware_ciaa/</code>.</li>
  <li>Verifica que las rutas a <code>lib_sapi/</code> estén configuradas en las propiedades del proyecto.</li>
</ol>
<hr>

<h2 id="compilacion-y-flasheo">💾 Compilación y Flasheo</h2>
<ol>
  <li>Selecciona la configuración <strong>Debug</strong> o <strong>Release</strong>.</li>
  <li>Haz clic en <em>Build Project</em> para compilar el firmware.</li>
  <li>Conecta la placa EDU-CIAA al PC vía USB.</li>
  <li>Presiona el botón <em>Debug</em> o <em>Run</em> para flashear el firmware.</li>
  <li>Verifica que el LED frontal parpadee indicando arranque exitoso.</li>
</ol>
<hr>

<h2 id="uso">📈 Uso y Verificación</h2>
<ol>
  <li>Montar la EDU-CIAA en el shield del chasis.</li>
  <li>Conectar drivers de motores y sensores según diagrama en <code>pcb_design/</code>.</li>
  <li>Conectar la fuente de alimentación (5 V para lógica, 12 V para motores).</li>
  <li>Observa mensajes de inicio en la consola serial (115200 bps).</li>
  <li>Envía comandos de prueba desde el CLI o vía terminal UART.</li>
</ol>
<hr>

<h2 id="estructura-de-archivos">📂 Estructura de Archivos</h2>
<pre><code>EDU-CIAA/
├── lib_sapi/               # Biblioteca sAPI v3
├── MAW_EDU_CIAA.workspace  # Workspace de Eclipse
├── src/                    # Código fuente C
│   ├── motorShield2.c
│   ├── comandos.c
│   └── arm.c
├── include/                # Headers personalizados
│   ├── motorShield2.h
│   ├── comandos.h
│   └── arm.h
└── debug/                  # Binaries compilados
</code></pre>


<h2 id="licencia">📄 Licencia</h2>
<p>Este subdirectorio forma parte del proyecto MAW, licenciado bajo MIT. Consulta el archivo raíz <code>LICENSE</code> para más detalles.</p>
