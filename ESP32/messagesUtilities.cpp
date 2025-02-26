/**
 * @file messagesUtilities.c
 * @brief Implementación de la gestión de buffers de comunicación en el ESP32-CAM.
 * 
 * Se implementan funciones para almacenar y recuperar mensajes en los buffers de WiFi y UART,
 * con acceso controlado mediante semáforos de FreeRTOS.
 * 
 * @author [Tu Nombre]
 * @date [Fecha]
 * @version 1.0
 */

 #include "messagesUtilities.h"

 #define MAX 15 ///< Capacidad máxima de los buffers WiFi y UART.
 
 // Buffers para la comunicación WiFi y UART
 String bufferWIFI[MAX];
 String bufferUART[MAX];
 
 // Índices y flags para WiFi
 int indexWIFI_rx = 0;
 int indexWIFI_tx = 0;
 int wifiFlag = 0;
 
 // Índices y flags para UART
 int indexUART_rx = 0;
 int indexUART_tx = 0;
 int uartFlag = 0;
 
 // Semáforos para la sincronización de acceso a los buffers
 SemaphoreHandle_t semUART, semWIFI;
 
 // Prototipos de funciones internas
 static void updateBufferWIFI(void);
 static void updateBufferUART(void);
 
 /**
  * @brief Crea un semáforo binario en FreeRTOS.
  * 
  * @return Handle del semáforo creado.
  */
 SemaphoreHandle_t createSemaphore() {
     return xSemaphoreCreateBinary();
 }
 
 /**
  * @brief Inicializa los semáforos para el acceso a los buffers de comunicación.
  */
 void initSemaphores() {
     semUART = createSemaphore();
     if (semUART != NULL) {
         xSemaphoreGive(semUART);
     }
     semWIFI = createSemaphore();
     if (semWIFI != NULL) {
         xSemaphoreGive(semWIFI);
     }
 }
 
 /**
  * @brief Procesa un mensaje recibido, separando el tipo de comando y su contenido.
  * 
  * @param message_aux Mensaje recibido en formato "tipo:comando".
  * @param resp Puntero donde se almacenará el tipo del mensaje (cmd, cam, led, etc.).
  * @param message Puntero donde se almacenará el contenido del mensaje.
  */
 void processMessage(String message_aux, String *resp, String *message) {
     int ind1 = message_aux.indexOf(':');  // Encuentra la posición del primer ":"
     *resp = message_aux.substring(0, ind1);  // Extrae el tipo de mensaje
     *message = message_aux.substring(ind1 + 1);  // Extrae el contenido del mensaje
 }
 
 /**
  * @brief Inicializa los buffers WiFi y UART, limpiando su contenido.
  */
 void initBuffers() {
     for (uint8_t i = 0; i < MAX; i++) {
         bufferWIFI[i] = "";
         bufferUART[i] = "";
     }
 }
 
 /* ========== MANEJO DEL BUFFER UART ========== */
 
 /**
  * @brief Recupera un comando almacenado en el buffer UART.
  * 
  * @param cmd Puntero donde se almacenará el comando recuperado.
  * @return `true` si se obtuvo un comando, `false` si no hay comandos disponibles.
  */
 bool getCommand(String *cmd) {
     bool exito = false;
     String msg;
 
     if (xSemaphoreTake(semUART, (TickType_t)5) == pdTRUE) {
         if (uartFlag) {
             uartFlag--;
             msg = bufferUART[indexUART_tx];
             bufferUART[indexUART_tx] = "";
             indexUART_tx++;
             updateBufferUART();
             exito = true;
             *cmd = msg;
         }
         xSemaphoreGive(semUART);
     }
     return exito;
 }
 
 /**
  * @brief Actualiza los índices del buffer UART para evitar desbordamientos.
  */
 static void updateBufferUART() {
     if (indexUART_rx >= MAX) indexUART_rx = 0;
     if (indexUART_tx >= MAX) indexUART_tx = 0;
 }
 
 /**
  * @brief Guarda un mensaje en el buffer UART para ser enviado posteriormente.
  * 
  * @param msg Mensaje a almacenar.
  * @return `true` si hubo error al guardar, `false` si se guardó correctamente.
  */
 bool saveInBufferUART(String msg) {
     bool error = true;
 
     if (xSemaphoreTake(semUART, (TickType_t)5) == pdTRUE) {
         if (indexUART_rx < MAX) {
             bufferUART[indexUART_rx] = msg;
             indexUART_rx++;
             uartFlag++;
             error = false;
         }
         xSemaphoreGive(semUART);
     }
     return error;
 }
 
 /* ========== MANEJO DEL BUFFER WIFI ========== */
 
 /**
  * @brief Recupera un mensaje almacenado en el buffer WiFi.
  * 
  * @param msg Puntero donde se almacenará el mensaje recuperado.
  * @return `true` si se obtuvo un mensaje, `false` si no hay mensajes disponibles.
  */
 bool getMsg(String *msg) {
     bool exito = false;
     String str;
 
     if (xSemaphoreTake(semWIFI, (TickType_t)5) == pdTRUE) {
         if (wifiFlag) {
             wifiFlag--;
             str = bufferWIFI[indexWIFI_tx];
             indexWIFI_tx++;
             updateBufferWIFI();
             exito = true;
             *msg = str;
         }
         xSemaphoreGive(semWIFI);
     }
     return exito;
 }
 
 /**
  * @brief Actualiza los índices del buffer WiFi para evitar desbordamientos.
  */
 static void updateBufferWIFI() {
     if (indexWIFI_rx >= MAX) indexWIFI_rx = 0;
     if (indexWIFI_tx >= MAX) indexWIFI_tx = 0;
 }
 
 /**
  * @brief Guarda un mensaje en el buffer WiFi para ser enviado posteriormente.
  * 
  * @param msg Mensaje a almacenar.
  * @return `true` si hubo error al guardar, `false` si se guardó correctamente.
  */
 bool saveInBufferWIFI(String msg) {
     bool error = true;
 
     if (xSemaphoreTake(semWIFI, (TickType_t)5) == pdTRUE) {
         if (indexWIFI_rx < MAX) {
             bufferWIFI[indexWIFI_rx] = msg;
             indexWIFI_rx++;
             wifiFlag++;
             error = false;
         }
         xSemaphoreGive(semWIFI);
     }
     return error;
 }
 