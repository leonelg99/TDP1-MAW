/**
 * @file Comands.h
 * @brief Definitions and declarations of control functions for the vehicle and robotic arm system on the EDU-CIAA platform
 * 
 * This file contains macro definitions and function declarations to control the system. 
 * It includes the configuration of the main components, system initialization, and battery level checking.
 * 
 * @version 1.0
 * @date 2025-03-12
 * 
 * @note
 * - Ensure the components are correctly connected to the hardware.
 * - Call 'programInit' before invoking other functions.
 * 
 * @author Guerrico Leonel - Pérez Balcedo Octavio
 * 
 */

#ifndef PROGRAM_MAW_INC_COMANDS_H_
#define PROGRAM_MAW_INC_COMANDS_H_

/*==================[inclusions]=============================================*/

#include "../inc/MotorShield2.h"
#include "../inc/Arm.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/*==================[external function declarations]=========================*/
/*
 * executeCmd(): this function receives a string and, based on it, executes different actions.
 * programInit(): this function configures and initializes the main components and variables for the proper functioning of the system.
 * checkPower(): this function reads the ADC and checks the battery levels.
 */

uint8_t executeCmd(uint8_t []);
void programInit(void);
void checkPower(void);

#endif /* PROGRAM_MAW_INC_COMANDS_H_ */
