/**
 * @file LibreriaFreeRTOS.c
 * @brief Implementation of tasks in FreeRTOS for the ESP32-CAM.
 * 
 * Tasks are defined for managing the WiFi server, UART communication, and
 * eventually video transmission. Each task is executed on a specific core
 * of the ESP32 using `xTaskCreatePinnedToCore()`.
 * 
 * @author Guerrico Leonel (lguerrico99@gmail.com) & Ossola Florencia (flor.ossola13@gmail.com)
 * @date 14-02-2024
 * @version 1.0
 */

 #include "LibreriaFreeRTOS.h"

 // Private function declarations
 static void conexionTask(void *); ///< Task to handle the WiFi server.
 static void uartTask(void *);     ///< Task to handle UART communication.
 // static void videoTask(void *);  ///< (Pending) Task to handle video transmission.
 
 /**
  * @brief Creates and assigns tasks in FreeRTOS.
  * 
  * The server and UART communication tasks are assigned to core 0 of the ESP32.
  */
 void createTasks() {
 
     // Task for managing the WiFi server (Core 0)
     xTaskCreatePinnedToCore(
         conexionTask,      ///< Task function.
         "Server",          ///< Task name.
         STACK_SIZE_SERVER, ///< Stack size.
         NULL,              ///< Parameters (not used).
         1,                 ///< Task priority.
         NULL,              ///< Task handler (not used).
         0                  ///< Core to run on (Core 0).
     );
 
     // Task for UART communication with the EDU-CIAA (Core 0)
     xTaskCreatePinnedToCore(
         uartTask,
         "UART",
         STACK_SIZE_UART,
         NULL,
         1,
         NULL,
         0
     );
     
     // (Optional) A task for video transmission could be added on Core 1 if needed.
 }
 
 /**
  * @brief Task that manages the WiFi server.
  * 
  * Calls `serverExecute()` to initialize and manage communication with the PC.
  * 
  * @param parameter Not used.
  */
 static void conexionTask(void *parameter) {
     serverExecute();
 }
 
 /**
  * @brief Task that handles UART communication with the EDU-CIAA.
  * 
  * Calls `uartStart()` to receive and send data serially.
  * 
  * @param parameter Not used.
  */
 static void uartTask(void *parameter) {
     uartStart();
 }
 