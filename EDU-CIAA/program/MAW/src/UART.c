/**
 * @file UART.c
 * @brief Implementation of UART communication functions for the EDU-CIAA platform
 * 
 * This file implements the functions for initializing and configuring the UART of the EDU-CIAA. 
 * It includes functions to send and receive standard messages through the UART channel.
 * 
 * @version 1.0
 * @date 2025-03-12
 * 
 * @note
 * - Ensure the UART pins are correctly connected to the hardware.
 * - Call 'serialInit' before invoking other functions.
 * 
 * @author Guerrico Leonel
 * 
 */

#include "../inc/UART.h"

/*
 * These messages are standard messages that the EDU-CIAA might send to the user at any time.
 * Each one is based on different situations that may or should occur at some point.
 */
const uint8_t * messages[] = {
        "EDU-CIAA READY\n",
        "ALERTA: BATERIA BAJA MOTORES!\n",
        "ALERTA: SE ESTA AGOTANDO LA BATERIA DE LA EDU-CIAA!\n",
        "WARNING: BATERIA BAJA DE LA EDU-CIAA!\n",
        "WARNING: BATERIA EN ESTADO CRITICO - APAGUE EL SISTEMA!!!\n",
        "ERROR 1: COMMAND NOT FOUND\n",
        "ERROR 2: COMMAND WRONG FORMAT\n",
        "ERROR 3: COMMAND TOO LONG\n",
        "ERROR 4: LIMITE ALCANZADO\n",
        "BRAZO ACTIVADO\n",
        "BRAZO DESACTIVADO\n",
        "ERROR: LIMITE ALCANZADO!\n",
        "ERROR: LA GARRA YA ESTA CERRADA",
        "ERROR: LA GARRA YA ESTA COMPLETAMENTE ABIERTA"

};

/*
 * @brief Initializes and configures the UART of the EDU-CIAA.
 * 
 * This function sets up the UART_232 channel with a baud rate of 115200 bps.
 */
void serialInit(){
    uartConfig( UART, 115200 );
}

/*
 * @brief Checks for incoming data on the UART channel and validates its format.
 * 
 * This function reads data from the UART channel. If the data has the correct format, 
 * it is stored in the memory location pointed to by the 'msg' parameter, and the function 
 * returns 0 (true). If the format is incorrect, it returns 1.
 * 
 * @param msg Pointer to the memory location where the received data will be stored.
 * @param length Maximum length of the message to be received.
 * @return 0 if the data format is correct, 1 otherwise.
 */
uint8_t receiveMsg(uint8_t * msg, uint8_t length){
    uint8_t dato = 0, reading = 1, index = 0, ready = 0;
    if(uartReadByte(UART, &dato)){
        if(dato == '\n'){
            sendMsg(6);
        } else{
            msg[index++] = dato;
            while(reading){
                if(index <= length && (dato != '\n')){
                    if(uartReadByte(UART, &dato)){
                        msg[index++] = dato;
                    }
                } else {
                    if(index > length) sendMsg(7);
                    else ready = 1;
                    reading = 0;
                }
            }
        }
    }
    return ready;
}

/*
 * @brief Sends a standard message through the UART channel.
 * 
 * This function sends one of the predefined standard messages stored in the 'messages' array.
 * The message to be sent is selected using the 'numMsg' parameter.
 * 
 * @param numMsg Index of the message to be sent from the 'messages' array.
 */
void sendMsg(uint8_t numMsg){
    uartWriteString(UART, messages[numMsg]);
}
