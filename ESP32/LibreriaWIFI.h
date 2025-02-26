/**
 * @file LibreriaWIFI.h
 * @brief Librería para la configuración y gestión de la red WiFi en el ESP32-CAM.
 * 
 * Esta librería permite configurar el ESP32 como un Access Point (AP), gestionar 
 * la conexión con clientes, procesar comandos recibidos y manejar la comunicación
 * entre el ESP32 y la EDU-CIAA.
 * 
 * @author [Tu Nombre]
 * @date [Fecha]
 * @version 1.0
 */

 #ifndef LIBRERIA_WIFI_H
 #define LIBRERIA_WIFI_H
 
 #include <Arduino.h>
 #include <WiFi.h>
 #include <WiFiAP.h>
 #include <WiFiClient.h>
 #include "messagesUtilities.h"  ///< Manejo de buffers de mensajes.
 #include "LibreriaCamera.h"     ///< Control de la cámara ESP32-CAM.
 
 /**
  * @brief Inicializa el ESP32 como un Access Point (AP).
  * 
  * Configura el ESP32 en modo AP con una IP estática y contraseña definida.
  */
 void startWiFi(void);
 
 /**
  * @brief Inicia el servidor WiFi para aceptar conexiones de clientes.
  * 
  * Configura el ESP32 para escuchar conexiones en el puerto 80.
  */
 void serverSetup(void);
 
 /**
  * @brief Maneja la comunicación con los clientes conectados al servidor.
  * 
  * - Recibe mensajes de los clientes y determina el destinatario.
  * - Enruta los comandos a la EDU-CIAA o ejecuta acciones en el ESP32.
  * - Devuelve respuestas a los clientes.
  */
 void serverExecute(void);
 
 /**
  * @brief Verifica si hay un cliente conectado al servidor y lo retorna.
  * 
  * @return WiFiClient Cliente conectado, o vacío si no hay ninguno.
  */
 WiFiClient getClient(void);
 
 #endif // LIBRERIA_WIFI_H
 