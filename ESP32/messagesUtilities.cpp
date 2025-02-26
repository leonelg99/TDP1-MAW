/**
 * @file messagesUtilities.c
 * @brief Implementation of communication buffer management on the ESP32-CAM.
 * 
 * Functions for storing and retrieving messages in the WiFi and UART buffers are implemented,
 * with controlled access through FreeRTOS semaphores.
 * 
 * @author Guerrico Leonel (lguerrico99@gmail.com) & Ossola Florencia (flor.ossola13@gmail.com)
 * @date 14-02-2024
 * @version 1.0
 */

 #include "messagesUtilities.h"

 #define MAX 15 ///< Maximum capacity of the WiFi and UART buffers.
 
 // Buffers for WiFi and UART communication
 String bufferWIFI[MAX];
 String bufferUART[MAX];
 
 // Indices and flags for WiFi
 int indexWIFI_rx = 0;
 int indexWIFI_tx = 0;
 int wifiFlag = 0;
 
 // Indices and flags for UART
 int indexUART_rx = 0;
 int indexUART_tx = 0;
 int uartFlag = 0;
 
 // Semaphores for synchronizing access to buffers
 SemaphoreHandle_t semUART, semWIFI;
 
 // Internal function prototypes
 static void updateBufferWIFI(void);
 static void updateBufferUART(void);
 
 /**
  * @brief Creates a binary semaphore in FreeRTOS.
  * 
  * @return Handle of the created semaphore.
  */
 SemaphoreHandle_t createSemaphore() {
     return xSemaphoreCreateBinary();
 }
 
 /**
  * @brief Initializes semaphores for access to communication buffers.
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
  * @brief Processes a received message, separating the command type and content.
  * 
  * @param message_aux Received message in "type:command" format.
  * @param resp Pointer where the message type (cmd, cam, led, etc.) will be stored.
  * @param message Pointer where the content of the message will be stored.
  */
 void processMessage(String message_aux, String *resp, String *message) {
     int ind1 = message_aux.indexOf(':');  // Finds the position of the first ":"
     *resp = message_aux.substring(0, ind1);  // Extracts the message type
     *message = message_aux.substring(ind1 + 1);  // Extracts the message content
 }
 
 /**
  * @brief Initializes WiFi and UART buffers, clearing their contents.
  */
 void initBuffers() {
     for (uint8_t i = 0; i < MAX; i++) {
         bufferWIFI[i] = "";
         bufferUART[i] = "";
     }
 }
 
 /* ========== UART BUFFER MANAGEMENT ========== */
 
 /**
  * @brief Retrieves a command stored in the UART buffer.
  * 
  * @param cmd Pointer where the retrieved command will be stored.
  * @return `true` if a command was retrieved, `false` if no commands are available.
  */
 bool getCommand(String *cmd) {
     bool success = false;
     String msg;
 
     if (xSemaphoreTake(semUART, (TickType_t)5) == pdTRUE) {
         if (uartFlag) {
             uartFlag--;
             msg = bufferUART[indexUART_tx];
             bufferUART[indexUART_tx] = "";
             indexUART_tx++;
             updateBufferUART();
             success = true;
             *cmd = msg;
         }
         xSemaphoreGive(semUART);
     }
     return success;
 }
 
 /**
  * @brief Updates UART buffer indices to prevent overflow.
  */
 static void updateBufferUART() {
     if (indexUART_rx >= MAX) indexUART_rx = 0;
     if (indexUART_tx >= MAX) indexUART_tx = 0;
 }
 
 /**
  * @brief Saves a message in the UART buffer to be sent later.
  * 
  * @param msg Message to store.
  * @return `true` if there was an error saving, `false` if saved successfully.
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
 
 /* ========== WIFI BUFFER MANAGEMENT ========== */
 
 /**
  * @brief Retrieves a message stored in the WiFi buffer.
  * 
  * @param msg Pointer where the retrieved message will be stored.
  * @return `true` if a message was retrieved, `false` if no messages are available.
  */
 bool getMsg(String *msg) {
     bool success = false;
     String str;
 
     if (xSemaphoreTake(semWIFI, (TickType_t)5) == pdTRUE) {
         if (wifiFlag) {
             wifiFlag--;
             str = bufferWIFI[indexWIFI_tx];
             indexWIFI_tx++;
             updateBufferWIFI();
             success = true;
             *msg = str;
         }
         xSemaphoreGive(semWIFI);
     }
     return success;
 }
 
 /**
  * @brief Updates WiFi buffer indices to prevent overflow.
  */
 static void updateBufferWIFI() {
     if (indexWIFI_rx >= MAX) indexWIFI_rx = 0;
     if (indexWIFI_tx >= MAX) indexWIFI_tx = 0;
 }
 
 /**
  * @brief Saves a message in the WiFi buffer to be sent later.
  * 
  * @param msg Message to store.
  * @return `true` if there was an error saving, `false` if saved successfully.
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
 