/**
 * @file LibreriaFreeRTOS.h
 * @brief Librería para la gestión de tareas en FreeRTOS en el ESP32-CAM.
 * 
 * Esta librería se encarga de la creación y administración de tareas en FreeRTOS,
 * asignando diferentes funciones a los núcleos del ESP32-CAM. Se definen tareas
 * para el manejo del servidor, la comunicación UART y la cámara.
 * 
 * @author [Tu Nombre]
 * @date [Fecha]
 * @version 1.0
 */

 #ifndef LIBRERIA_FREERTOS_H
 #define LIBRERIA_FREERTOS_H
 
 #include <Arduino.h>
 #include <freertos/FreeRTOS.h>
 #include <freertos/task.h>
 #include "LibreriaWIFI.h"   ///< Manejo del servidor WiFi.
 #include "LibreriaUART.h"   ///< Comunicación serie con la EDU-CIAA.
 #include "LibreriaCamera.h" ///< Control de la cámara ESP32-CAM.
 
 /// Tamaño de pila para la tarea del servidor (4 KB).
 #define STACK_SIZE_SERVER 10000   
 
 /// Tamaño de pila para la tarea UART (4 KB).
 #define STACK_SIZE_UART   10000   
 
 /// Tamaño de pila recomendado para la tarea de la cámara (Ajustar según necesidades).
 #define STACK_SIZE_CAM    400000   
 
 /**
  * @brief Crea y asigna las tareas principales en FreeRTOS.
  * 
  * Se inicializan las tareas de conexión del servidor y comunicación UART,
  * asignándolas a los núcleos del ESP32.
  */
 void createTasks(void);
 
 #endif // LIBRERIA_FREERTOS_H
 