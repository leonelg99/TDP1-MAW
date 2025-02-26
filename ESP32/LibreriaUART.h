/**
 * @file LibreriaUART.h
 * @brief Librería para la comunicación UART entre el ESP32-CAM y la EDU-CIAA.
 * 
 * Esta librería permite la inicialización de la UART y la gestión de la 
 * comunicación en serie, asegurando el intercambio de mensajes entre el 
 * ESP32-CAM y la EDU-CIAA.
 * 
 * @author [Tu Nombre]
 * @date [Fecha]
 * @version 1.0
 */

 #ifndef LIBRERIA_UART_H
 #define LIBRERIA_UART_H
 
 #include <Arduino.h>
 #include "messagesUtilities.h" ///< Manejo de buffers de mensajes.
 
 /**
  * @brief Inicializa la comunicación UART con una velocidad de 115200 baudios.
  * 
  * Configura la UART en el ESP32-CAM para la comunicación con la EDU-CIAA.
  */
 void uartSetup(void);
 
 /**
  * @brief Gestiona la comunicación UART en un bucle continuo.
  * 
  * - Lee los datos recibidos a través de UART y los guarda en el buffer WiFi.
  * - Envía mensajes al microcontrolador si hay datos disponibles.
  */
 void uartStart(void);
 
 #endif // LIBRERIA_UART_H
 