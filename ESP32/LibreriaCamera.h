/**
 * @file LibreriaCamera.h
 * @brief Library for configuring and managing the camera on the ESP32-CAM.
 * 
 * This library allows initializing the camera, streaming video via HTTP, changing
 * the resolution, and controlling the built-in flash LED. It also manages communication
 * with other modules through WiFi and UART.
 * 
 * @author Guerrico Leonel (lguerrico99@gmail.com) & Ossola Florencia (flor.ossola13@gmail.com)
 * @date 14-02-2024
 * @version 1.0
 */

 #ifndef LIBRERIACAMERA_H
 #define LIBRERIACAMERA_H
 
 #include <Arduino.h>
 #include "esp_camera.h"
 #define CAMERA_MODEL_AI_THINKER ///< Definition of the camera model used.
 #include "camera_pins.h"        ///< File that defines the camera pins.
 #include <WiFi.h>
 #include "messagesUtilities.h"  ///< Utilities for message management.
 
 /**
  * @brief Configures and initializes the ESP32-CAM camera.
  * 
  * This function defines the pins, image quality, and other parameters necessary
  * for the camera operation.
  */
 void cameraSetup(void);
 
 /**
  * @brief Starts real-time video streaming via HTTP.
  * 
  * Configures a web server on port 8020 and manages the capture of JPEG images,
  * continuously streaming them.
  */
 void cameraExecute(void);
 
 /**
  * @brief Changes the camera resolution during runtime.
  * 
  * Switches between predefined resolutions (SVGA and UXGA). In case of error,
  * the camera is restarted.
  */
 void changeResolution(void);
 
 /**
  * @brief Turns the ESP32-CAM's LED on or off.
  * 
  * This function turns the flash LED of the ESP32-CAM on or off.
  */
 void led(void);
 
 #endif // LIBRERIACAMERA_H
 