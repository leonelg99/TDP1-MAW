/**
 * @file messagesUtilities.h
 * @brief Librería para la gestión de buffers de comunicación en el ESP32-CAM.
 * 
 * Esta librería proporciona funciones para el manejo de buffers en la comunicación
 * UART y WiFi, utilizando semáforos de FreeRTOS para garantizar acceso seguro.
 * 
 * @author [Tu Nombre]
 * @date [Fecha]
 * @version 1.0
 */

 #ifndef MESSAGES_UTILITIES_H
 #define MESSAGES_UTILITIES_H
 
 #include <Arduino.h>
 #include <freertos/FreeRTOS.h>
 #include <freertos/semphr.h>  ///< Manejo de semáforos en FreeRTOS.
 
 /**
  * @brief Inicializa los semáforos para la sincronización de buffers.
  */
 void initSemaphores(void);
 
 /**
  * @brief Procesa un mensaje recibido, separando el tipo de comando y su contenido.
  * 
  * @param message_aux Mensaje recibido en formato "tipo:comando".
  * @param resp Puntero donde se almacenará el tipo del mensaje (cmd, cam, led, etc.).
  * @param message Puntero donde se almacenará el contenido del mensaje.
  */
 void processMessage(String message_aux, String *resp, String *message);
 
 /**
  * @brief Inicializa los buffers de almacenamiento para UART y WiFi.
  */
 void initBuffers(void);
 
 /**
  * @brief Guarda un mensaje recibido por WiFi en el buffer UART para enviarlo a la EDU-CIAA.
  * 
  * @param msg Mensaje a almacenar.
  * @return `true` si hubo error al guardar, `false` si se guardó correctamente.
  */
 bool saveInBufferUART(String msg);
 
 /**
  * @brief Guarda un mensaje recibido por UART en el buffer WiFi para enviarlo posteriormente.
  * 
  * @param msg Mensaje a almacenar.
  * @return `true` si hubo error al guardar, `false` si se guardó correctamente.
  */
 bool saveInBufferWIFI(String msg);
 
 /**
  * @brief Obtiene un comando almacenado en el buffer UART.
  * 
  * @param cmd Puntero donde se almacenará el comando recuperado.
  * @return `true` si se obtuvo un comando, `false` si no hay comandos disponibles.
  */
 bool getCommand(String *cmd);
 
 /**
  * @brief Obtiene un mensaje almacenado en el buffer WiFi.
  * 
  * @param msg Puntero donde se almacenará el mensaje recuperado.
  * @return `true` si se obtuvo un mensaje, `false` si no hay mensajes disponibles.
  */
 bool getMsg(String *msg);
 
 #endif // MESSAGES_UTILITIES_H
 