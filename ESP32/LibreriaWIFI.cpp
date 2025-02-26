/**
 * @file LibreriaWIFI.c
 * @brief Implementación de la gestión de la conexión WiFi en el ESP32-CAM.
 * 
 * Esta implementación configura el ESP32 como un Access Point (AP), inicia el servidor
 * WiFi, maneja la comunicación con clientes y ejecuta comandos recibidos.
 * 
 * @author [Tu Nombre]
 * @date [Fecha]
 * @version 1.0
 */

 #include "LibreriaWIFI.h"

 #define LED_PIN 4 ///< Pin del LED indicador de estado.
 
 // Parámetros de la red WiFi
 const char* ssid = "ESP32";         ///< Nombre de la red WiFi (SSID).
 const char* password = "esp32123";  ///< Contraseña de la red WiFi.
 
 // Configuración de la red
 IPAddress staticIP(192, 168, 4, 2); ///< Dirección IP estática del ESP32.
 IPAddress local_ip(192, 168, 4, 1); ///< Dirección IP del servidor.
 IPAddress gateway(192, 168, 4, 1);  ///< Dirección IP de la puerta de enlace.
 IPAddress subnet(255, 255, 255, 0); ///< Máscara de subred.
 
 // Variables para el procesamiento de comandos
 String message_aux; ///< Mensaje capturado.
 String message;     ///< Mensaje procesado.
 String resp;        ///< Tipo de mensaje recibido (cmd, cam, led, etc.).
 
 WiFiServer server(80); ///< Servidor WiFi en el puerto 80.
 
 /**
  * @brief Configura el ESP32 como un Access Point (AP).
  * 
  * Se establece la red WiFi con el SSID y la contraseña definidos. Si falla,
  * se reintenta hasta que la conexión sea exitosa.
  */
 void startWiFi() {
     int estado = 0;
     while (estado == 0) {
         pinMode(LED_PIN, OUTPUT);
         WiFi.mode(WIFI_AP); // Configura el ESP32 en modo Access Point.
         WiFi.softAPConfig(local_ip, gateway, subnet);
         if (!WiFi.softAP(ssid, password)) {
             log_e("Error al crear el Access Point.");
             delay(500);
         } else {
             estado = 1;
         }
     }
 }
 
 /**
  * @brief Verifica si hay un cliente conectado al servidor y lo retorna.
  * 
  * @return WiFiClient Cliente conectado, o vacío si no hay ninguno.
  */
 WiFiClient getClient() {
     WiFiClient client = server.available();
     return client;
 }
 
 /**
  * @brief Inicia el servidor WiFi en el puerto 80.
  * 
  * Esta función habilita la escucha de conexiones entrantes en el servidor.
  */
 void serverSetup() {
     server.begin();
 }
 
 String MSG = ""; ///< Variable auxiliar para almacenar mensajes.
 
 /**
  * @brief Gestiona la comunicación con los clientes conectados al servidor.
  * 
  * - Recibe y procesa los mensajes de los clientes.
  * - Determina el destinatario del mensaje y lo reenvía si es necesario.
  * - Devuelve respuestas a los clientes.
  */
 void serverExecute() {
     while (1) {
         WiFiClient client = getClient();
         if (client) {
             // Captura el mensaje recibido
             message_aux = client.readStringUntil('\n');
 
             // Procesa el mensaje y obtiene su tipo y contenido
             processMessage(message_aux, &resp, &message);
 
             // Si el mensaje es un comando para la EDU-CIAA, se reenvía por UART
             if (resp.equals("cmd")) {
                 saveInBufferUART(message);
             } 
             else {
                 // Si el comando es para la cámara o el LED, se ejecuta en el ESP32
                 if (resp.equals("cam") || resp.equals("led")) {
                     if (resp.equals("cam")) {
                         changeResolution();
                     } else {
                         led();
                     }
                 } 
                 else {
                     // Si es una solicitud de información, se responde con el mensaje almacenado
                     if (resp.equals("get")) {
                         if (getMsg(&MSG)) {
                             client.print(MSG);
                         } else {
                             client.print("");
                         }
                     } 
                     // Si el comando no es válido, se envía un mensaje de error
                     else {
                         client.print("ESP - Error: comando no válido.");
                     }
                 }
             }
             // Cierra la conexión con el cliente
             client.stop();
         }
         vTaskDelay(2); // Pequeña espera para evitar sobrecarga de la CPU
     }
 }
 