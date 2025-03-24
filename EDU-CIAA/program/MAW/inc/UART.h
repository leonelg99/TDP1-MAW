/**
 * @file UART.h
 * @brief Definitions and declarations for UART communication on the EDU-CIAA platform
 * 
 * This file contains macro definitions and function declarations for initializing and configuring the UART. 
 * It includes functions to send and receive standard messages through the UART channel.
 * 
 * @version 1.0
 * @date 2025-03-12
 * 
 * @note
 * - Ensure the components are correctly connected to the hardware.
 * - Call 'serialInit' before invoking other functions.
 * 
 * @author Guerrico Leonel
 * 
 */

#ifndef PROGRAM_MAW_INC_UART_H_
#define PROGRAM_MAW_INC_UART_H_

/*
 * Libraries
 */
#include "sapi.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define UART UART_232	// Mask to avoid writing UART_232

/*
 * Public functions
 * serialInit(): Initializes the UART.
 * receiveMsg(): Checks if there is data to receive and if it is in the correct format.
 * If so, it stores the data and returns 0.
 * sendMsg(): Sends one of the standard messages (see UART.c file) indicated by the parameter (index).
 */
void serialInit(void);
uint8_t receiveMsg(uint8_t *, uint8_t);
void sendMsg(uint8_t);

#endif /* PROGRAM_MAW_INC_UART_H_ */
