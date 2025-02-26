/**
 * @file LibreriaCamera.h
 * @brief Librería para la configuración y gestión de la cámara en el ESP32-CAM.
 * 
 * Esta librería permite inicializar la cámara, transmitir video por HTTP, cambiar 
 * la resolución y controlar el LED flash incorporado. También gestiona la comunicación 
 * con otros módulos a través de WiFi y UART.
 * 
 * @author [Tu Nombre]
 * @date [Fecha]
 * @version 1.0
 */

 #ifndef LIBRERIACAMERA_H
 #define LIBRERIACAMERA_H
 
 #include <Arduino.h>
 #include "esp_camera.h"
 #define CAMERA_MODEL_AI_THINKER ///< Definición del modelo de cámara utilizado.
 #include "camera_pins.h"        ///< Archivo que define los pines de la cámara.
 #include <WiFi.h>
 #include "messagesUtilities.h"  ///< Utilidades para la gestión de mensajes.
 
 /**
  * @brief Configura e inicializa la cámara del ESP32-CAM.
  * 
  * Esta función define los pines, la calidad de imagen y otros parámetros
  * necesarios para el funcionamiento de la cámara.
  */
 void cameraSetup(void);
 
 /**
  * @brief Inicia la transmisión de video en tiempo real mediante HTTP.
  * 
  * Configura un servidor web en el puerto 8020 y gestiona la captura de imágenes
  * en formato JPEG, transmitiéndolas de manera continua.
  */
 void cameraExecute(void);
 
 /**
  * @brief Cambia la resolución de la cámara durante la ejecución.
  * 
  * Alterna entre resoluciones predefinidas (SVGA y UXGA). En caso de error, reinicia la cámara.
  */
 void changeResolution(void);
 
 /**
  * @brief Activa o desactiva el LED del ESP32-CAM.
  * 
  * Esta función enciende o apaga el LED flash del ESP32-CAM.
  */
 void led(void);
 
 #endif // LIBRERIACAMERA_H
 