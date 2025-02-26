/**
 * @file LibreriaUART.h
 * @brief Library for UART communication between the ESP32-CAM and the EDU-CIAA.
 * 
 * This library allows the initialization of UART and manages serial 
 * communication, ensuring message exchange between the ESP32-CAM and the EDU-CIAA.
 * 
 * @author [Your Name]
 * @date [Date]
 * @version 1.0
 */

 #ifndef LIBRERIA_UART_H
 #define LIBRERIA_UART_H
 
 #include <Arduino.h>
 #include "messagesUtilities.h" ///< Message buffer management.
 
  /**
   * @brief Initializes UART communication at a speed of 115200 baud.
   * 
   * Configures UART on the ESP32-CAM for communication with the EDU-CIAA.
   */
  void uartSetup(void);
 
  /**
   * @brief Manages UART communication in a continuous loop.
   * 
   * - Reads data received through UART and stores it in the WiFi buffer.
   * - Sends messages to the microcontroller if data is available.
   */
  void uartStart(void);
 
 #endif // LIBRERIA_UART_H
 