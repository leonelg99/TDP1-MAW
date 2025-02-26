/**
 * @file LibreriaUART.c
 * @brief Implementación de la comunicación UART entre el ESP32-CAM y la EDU-CIAA.
 * 
 * Esta implementación permite la inicialización de la UART y la comunicación en 
 * un bucle continuo para recibir y enviar datos entre el ESP32 y la EDU-CIAA.
 * 
 * @author [Tu Nombre]
 * @date [Fecha]
 * @version 1.0
 */

 #include "LibreriaUART.h"

 String msg; ///< Variable para almacenar mensajes recibidos por UART.
 
 /**
  * @brief Configura la UART con una velocidad de 115200 baudios.
  * 
  * Esta función inicializa la comunicación UART del ESP32-CAM, 
  * permitiendo la transmisión y recepción de datos en serie.
  */
 void uartSetup() {
     Serial.begin(115200);
 }
 
 /**
  * @brief Gestiona la comunicación UART en un bucle continuo.
  * 
  * - Si hay datos disponibles en la UART, los lee y los almacena en el buffer WiFi.
  * - Si hay un mensaje listo para ser enviado, lo transmite a través de la UART.
  * - Introduce un pequeño delay para evitar sobrecarga de la CPU.
  */
 void uartStart() {
     while (1) {
         // Si hay datos en la UART, los lee y los almacena en el buffer WiFi.
         if (Serial.available()) {
             msg = Serial.readStringUntil('\n');
             saveInBufferWIFI(msg);
         }
         
         // Si hay un mensaje en el buffer para la EDU-CIAA, lo envía.
         if (getCommand(&msg)) {
             Serial.println(msg);
         }
         
         // Limpia la variable del mensaje y espera para la siguiente iteración.
         msg = "";
         vTaskDelay(10);
     }
 }
 