/**
 * @file messagesUtilities.h
 * @brief Library for managing communication buffers on the ESP32-CAM.
 * 
 * This library provides functions for handling buffers in UART and WiFi communication,
 * using FreeRTOS semaphores to ensure safe access.
 * 
 * @author Guerrico Leonel (lguerrico99@gmail.com) & Ossola Florencia (flor.ossola13@gmail.com)
 * @date 14-02-2024
 * @version 1.0
 */

 #ifndef MESSAGES_UTILITIES_H
 #define MESSAGES_UTILITIES_H
 
 #include <Arduino.h>
 #include <freertos/FreeRTOS.h>
 #include <freertos/semphr.h>  ///< Semaphore handling in FreeRTOS.
 
 /**
  * @brief Initializes semaphores for buffer synchronization.
  */
 void initSemaphores(void);
 
 /**
  * @brief Processes a received message, separating the command type and content.
  * 
  * @param message_aux Received message in "type:command" format.
  * @param resp Pointer where the message type (cmd, cam, led, etc.) will be stored.
  * @param message Pointer where the content of the message will be stored.
  */
 void processMessage(String message_aux, String *resp, String *message);
 
 /**
  * @brief Initializes storage buffers for UART and WiFi.
  */
 void initBuffers(void);
 
 /**
  * @brief Saves a received WiFi message in the UART buffer to send it to the EDU-CIAA.
  * 
  * @param msg Message to store.
  * @return `true` if there was an error saving, `false` if saved successfully.
  */
 bool saveInBufferUART(String msg);
 
 /**
  * @brief Saves a received UART message in the WiFi buffer to be sent later.
  * 
  * @param msg Message to store.
  * @return `true` if there was an error saving, `false` if saved successfully.
  */
 bool saveInBufferWIFI(String msg);
 
 /**
  * @brief Retrieves a command stored in the UART buffer.
  * 
  * @param cmd Pointer where the retrieved command will be stored.
  * @return `true` if a command was retrieved, `false` if no commands are available.
  */
 bool getCommand(String *cmd);
 
 /**
  * @brief Retrieves a message stored in the WiFi buffer.
  * 
  * @param msg Pointer where the retrieved message will be stored.
  * @return `true` if a message was retrieved, `false` if no messages are available.
  */
 bool getMsg(String *msg);
 
 #endif // MESSAGES_UTILITIES_H
 