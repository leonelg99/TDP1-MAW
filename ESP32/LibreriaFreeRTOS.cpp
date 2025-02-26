/**
 * @file LibreriaFreeRTOS.c
 * @brief Implementación de las tareas en FreeRTOS para el ESP32-CAM.
 * 
 * Se definen tareas para la gestión del servidor WiFi, la comunicación UART y,
 * eventualmente, la transmisión de video. Cada tarea se ejecuta en un núcleo específico
 * del ESP32 mediante `xTaskCreatePinnedToCore()`.
 * 
 * @author [Tu Nombre]
 * @date [Fecha]
 * @version 1.0
 */

 #include "LibreriaFreeRTOS.h"

 // Declaraciones de funciones privadas
 static void conexionTask(void *); ///< Tarea para manejar el servidor WiFi.
 static void uartTask(void *);     ///< Tarea para manejar la comunicación UART.
 // static void videoTask(void *);  ///< (Pendiente) Tarea para manejar la transmisión de video.
 
 /**
  * @brief Crea y asigna las tareas en FreeRTOS.
  * 
  * Se asignan las tareas de servidor y comunicación UART al núcleo 0 del ESP32.
  */
 void createTasks() {
 
     // Tarea para la gestión del servidor WiFi (Core 0)
     xTaskCreatePinnedToCore(
         conexionTask,      ///< Función de la tarea.
         "Server",         ///< Nombre de la tarea.
         STACK_SIZE_SERVER, ///< Tamaño de pila.
         NULL,             ///< Parámetros (no usados).
         1,                ///< Prioridad de la tarea.
         NULL,             ///< Manejador de la tarea (no usado).
         0                 ///< Núcleo donde se ejecuta (Core 0).
     );
 
     // Tarea para la comunicación UART con la EDU-CIAA (Core 0)
     xTaskCreatePinnedToCore(
         uartTask,
         "UART",
         STACK_SIZE_UART,
         NULL,
         1,
         NULL,
         0
     );
     
     // (Opcional) Se podría agregar la tarea para la transmisión de video en Core 1 si es necesario.
 }
 
 /**
  * @brief Tarea que gestiona el servidor WiFi.
  * 
  * Llama a `serverExecute()` para inicializar y manejar la comunicación con la PC.
  * 
  * @param parameter No utilizado.
  */
 static void conexionTask(void *parameter) {
     serverExecute();
 }
 
 /**
  * @brief Tarea que maneja la comunicación UART con la EDU-CIAA.
  * 
  * Llama a `uartStart()` para recibir y enviar datos en serie.
  * 
  * @param parameter No utilizado.
  */
 static void uartTask(void *parameter) {
     uartStart();
 }
 