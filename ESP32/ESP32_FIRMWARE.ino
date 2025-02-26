/**
 * @file main.ino
 * @brief Main code for controlling the ESP32-CAM in the MAW vehicle.
 * 
 * This code initializes and manages WiFi communication, the camera, and UART
 * using FreeRTOS for concurrent task execution.
 * 
 * @author Guerrico Leonel (lguerrico99@gmail.com) & Ossola Florencia (flor.ossola13@gmail.com)
 * @date 10-02-2024
 * @version 1.0
 */

 #include "LibreriaWIFI.h"       // Library for WiFi server setup and TCP/IP communication.
 #include "LibreriaFreeRTOS.h"   // Library for task management in FreeRTOS.
 #include "messagesUtilities.h"  // Library for handling messages and communication buffers.
 
 #define ledPin 4  ///< Pin assigned to the status LED.
 
 /**
  * @brief Initial setup for the ESP32.
  * 
  * This function runs once at the start of the program and initializes:
  * - Message buffers.
  * - Semaphores for task synchronization.
  * - UART communication with the EDU-CIAA.
  * - WiFi network setup and server configuration.
  * - Camera configuration.
  * - FreeRTOS tasks for concurrent process handling.
  */
 void setup() {
   initBuffers();     ///< Initializes buffers for message storage.
   initSemaphores();  ///< Sets up semaphores for task synchronization.
   uartSetup();       ///< Configures UART communication with the EDU-CIAA.
   startWiFi();       ///< Establishes the WiFi network and configures the server.
   serverSetup();     ///< Initializes the TCP/IP server for communication with the PC.
   cameraSetup();     ///< Sets up the camera for real-time video streaming.
   createTasks();     ///< Creates and assigns tasks in FreeRTOS for concurrent execution.
 }
 
 /**
  * @brief Main loop of the ESP32.
  * 
  * In this case, the `loop()` function is empty because execution is handled 
  * through FreeRTOS tasks.
  */
 void loop() {
   // No code is executed in the main loop as everything is managed by FreeRTOS.
 }
 