/**
 * @file main.ino
 * @brief Código principal para el control del ESP32-CAM en el vehículo MAW.
 * 
 * Este código inicializa y gestiona la comunicación WiFi, la cámara y la UART
 * utilizando FreeRTOS para la ejecución concurrente de tareas. 
 * 
 * @author [Tu Nombre]
 * @date [Fecha]
 * @version 1.0
 */

 #include "LibreriaWIFI.h"       // Librería para la configuración del servidor WiFi y la comunicación TCP/IP.
 #include "LibreriaFreeRTOS.h"   // Librería para la gestión de tareas en FreeRTOS.
 #include "messagesUtilities.h"  // Librería para el manejo de mensajes y buffers de comunicación.
 
 #define ledPin 4  ///< Pin asignado al LED de estado.
 
 /**
  * @brief Configuración inicial del ESP32.
  * 
  * Esta función se ejecuta una única vez al inicio del programa e inicializa:
  * - Buffers de mensajes.
  * - Semáforos para la sincronización de tareas.
  * - Comunicación UART con la EDU-CIAA.
  * - Configuración y activación del servidor WiFi.
  * - Configuración de la cámara.
  * - Creación de tareas en FreeRTOS para el manejo concurrente de procesos.
  */
 void setup() {
   initBuffers();     ///< Inicializa los buffers para el almacenamiento de mensajes.
   initSemaphores();  ///< Configura los semáforos para la sincronización de tareas.
   uartSetup();       ///< Configura la comunicación UART con la EDU-CIAA.
   startWiFi();       ///< Establece la red WiFi y configura el servidor.
   serverSetup();     ///< Inicializa el servidor TCP/IP para la comunicación con la PC.
   cameraSetup();     ///< Configura la cámara para la transmisión de video en tiempo real.
   createTasks();     ///< Crea y asigna tareas en FreeRTOS para la ejecución concurrente.
 }
 
 /**
  * @brief Bucle principal del ESP32.
  * 
  * En este caso, el bucle `loop()` está vacío porque la ejecución se maneja mediante
  * tareas en FreeRTOS.
  */
 void loop() {
   // No se ejecuta código en el loop principal ya que todo se gestiona con FreeRTOS.
 }
 