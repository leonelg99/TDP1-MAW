/**
 * @file LibreriaUART.c
 * @brief Implementation of UART communication between the ESP32-CAM and the EDU-CIAA.
 * 
 * This implementation allows for the initialization of UART and continuous 
 * communication to receive and send data between the ESP32 and the EDU-CIAA.
 * 
 * @author Guerrico Leonel (lguerrico99@gmail.com) & Ossola Florencia (flor.ossola13@gmail.com)
 * @date 14-02-2024
 * @version 1.0
 */

 #include "LibreriaUART.h"

 String msg; ///< Variable to store messages received via UART.
 
  /**
   * @brief Configures UART at a speed of 115200 baud.
   * 
   * This function initializes UART communication on the ESP32-CAM, 
   * allowing serial data transmission and reception.
   */
  void uartSetup() {
      Serial.begin(115200);
  }
 
  /**
   * @brief Manages UART communication in a continuous loop.
   * 
   * - If data is available on UART, it reads and stores it in the WiFi buffer.
   * - If a message is ready to be sent, it transmits it via UART.
   * - Introduces a small delay to avoid overloading the CPU.
   */
  void uartStart() {
      while (1) {
          // If data is available on UART, reads it and stores it in the WiFi buffer.
          if (Serial.available()) {
              msg = Serial.readStringUntil('\n');
              saveInBufferWIFI(msg);
          }
 
          // If there is a message in the buffer for the EDU-CIAA, it sends it.
          if (getCommand(&msg)) {
              Serial.println(msg);
          }
 
          // Clears the message variable and waits for the next iteration.
          msg = "";
          vTaskDelay(10);
      }
  }
 