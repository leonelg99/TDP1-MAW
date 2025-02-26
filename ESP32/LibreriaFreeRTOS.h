/**
 * @file LibreriaFreeRTOS.h
 * @brief Library for task management in FreeRTOS on the ESP32-CAM.
 * 
 * This library is responsible for creating and managing tasks in FreeRTOS,
 * assigning different functions to the cores of the ESP32-CAM. Tasks are 
 * defined for server management, UART communication, and camera control.
 * 
 * @author [Your Name]
 * @date [Date]
 * @version 1.0
 */

 #ifndef LIBRERIA_FREERTOS_H
 #define LIBRERIA_FREERTOS_H
 
 #include <Arduino.h>
 #include <freertos/FreeRTOS.h>
 #include <freertos/task.h>
 #include "LibreriaWIFI.h"   ///< WiFi server management.
 #include "LibreriaUART.h"   ///< Serial communication with the EDU-CIAA.
 #include "LibreriaCamera.h" ///< ESP32-CAM camera control.
 
 /// Stack size for the server task (4 KB).
 #define STACK_SIZE_SERVER 10000
 
 /// Stack size for the UART task (4 KB).
 #define STACK_SIZE_UART   10000
 
 /// Recommended stack size for the camera task (Adjust as needed).
 #define STACK_SIZE_CAM    400000
 
 /**
  * @brief Creates and assigns the main tasks in FreeRTOS.
  * 
  * Initializes the server connection tasks and UART communication,
  * assigning them to the ESP32 cores.
  */
 void createTasks(void);
 
 #endif // LIBRERIA_FREERTOS_H
 