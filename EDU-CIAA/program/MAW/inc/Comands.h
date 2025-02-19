/*
 * Comands.h
 *
 *  Created on: 13 oct. 2023
 *      Author: lguer
 */

#ifndef PROGRAM_MAW_INC_COMANDS_H_
#define PROGRAM_MAW_INC_COMANDS_H_

/*==================[inclusions]=============================================*/

#include "../inc/MotorShield2.h"
#include "../inc/Arm.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/*==================[external functions declaration]=========================*/
/*
 * excuteCmd(): this function receive a string and according to it, execute different actions.
 * programInit(): this function config and initialize the main components and variables for
 * the correct functioning of the system
 * checkPower(): this function read the ADC and check the batteries levels.
 */

uint8_t executeCmd(uint8_t []);
void programInit(void);
void checkPower(void);

#endif /* PROGRAM_MAW_INC_COMANDS_H_ */
