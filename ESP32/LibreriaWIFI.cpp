/**
 * @file LibreriaWIFI.c
 * @brief Implementation of WiFi connection management on the ESP32-CAM.
 * 
 * This implementation configures the ESP32 as an Access Point (AP), starts the server, 
 * manages communication with clients, and executes received commands.
 * 
 * @author Guerrico Leonel (lguerrico99@gmail.com) & Ossola Florencia (flor.ossola13@gmail.com)
 * @date 14-02-2024
 * @version 1.0
 */

 #include "LibreriaWIFI.h"

 #define LED_PIN 4 ///< Pin for the status LED.
 
  // WiFi network parameters
  const char* ssid = "ESP32";         ///< Name of the WiFi network (SSID).
  const char* password = "esp32123";  ///< Password for the WiFi network.
  
  // Network configuration
  IPAddress staticIP(192, 168, 4, 2); ///< Static IP address of the ESP32.
  IPAddress local_ip(192, 168, 4, 1); ///< IP address of the server.
  IPAddress gateway(192, 168, 4, 1);  ///< Gateway IP address.
  IPAddress subnet(255, 255, 255, 0); ///< Subnet mask.
  
  // Variables for command processing
  String message_aux; ///< Captured message.
  String message;     ///< Processed message.
  String resp;        ///< Type of received message (cmd, cam, led, etc.).
  
  WiFiServer server(80); ///< WiFi server on port 80.
 
  /**
   * @brief Configures the ESP32 as an Access Point (AP).
   * 
   * The WiFi network is set up with the defined SSID and password. If it fails,
   * it retries until the connection is successful.
   */
  void startWiFi() {
      int estado = 0;
      while (estado == 0) {
          pinMode(LED_PIN, OUTPUT);
          WiFi.mode(WIFI_AP); // Sets the ESP32 to Access Point mode.
          WiFi.softAPConfig(local_ip, gateway, subnet);
          if (!WiFi.softAP(ssid, password)) {
              log_e("Error creating the Access Point.");
              delay(500);
          } else {
              estado = 1;
          }
      }
  }
 
  /**
   * @brief Checks if a client is connected to the server and returns it.
   * 
   * @return WiFiClient Connected client, or empty if there is none.
   */
  WiFiClient getClient() {
      WiFiClient client = server.available();
      return client;
  }
 
  /**
   * @brief Starts the WiFi server on port 80.
   * 
   * This function enables listening for incoming connections on the server.
   */
  void serverSetup() {
      server.begin();
  }
 
  String MSG = ""; ///< Auxiliary variable to store messages.
 
  /**
   * @brief Manages communication with clients connected to the server.
   * 
   * - Receives and processes messages from clients.
   * - Determines the message's destination and forwards it if necessary.
   * - Returns responses to the clients.
   */
  void serverExecute() {
      while (1) {
          WiFiClient client = getClient();
          if (client) {
              // Captures the received message
              message_aux = client.readStringUntil('\n');
  
              // Processes the message and gets its type and content
              processMessage(message_aux, &resp, &message);
  
              // If the message is a command for the EDU-CIAA, it is forwarded via UART
              if (resp.equals("cmd")) {
                  saveInBufferUART(message);
              } 
              else {
                  // If the command is for the camera or LED, it is executed on the ESP32
                  if (resp.equals("cam") || resp.equals("led")) {
                      if (resp.equals("cam")) {
                          changeResolution();
                      } else {
                          led();
                      }
                  } 
                  else {
                      // If it's a request for information, it responds with the stored message
                      if (resp.equals("get")) {
                          if (getMsg(&MSG)) {
                              client.print(MSG);
                          } else {
                              client.print("");
                          }
                      } 
                      // If the command is invalid, an error message is sent
                      else {
                          client.print("ESP - Error: invalid command.");
                      }
                  }
              }
              // Closes the connection with the client
              client.stop();
          }
          vTaskDelay(2); // Small wait to avoid CPU overload
      }
  }
 