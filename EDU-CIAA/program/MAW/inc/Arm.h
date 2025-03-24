/**
 * @file Arm.h
 * @brief Definitions and declarations of the robotic arm control library for the EDU-CIAA platform
 * 
 * This file contains the macro definitions and function declarations to control the robotic arm. 
 * It includes the configuration of the servomotors and the functions to initialize and execute commands on the arm.
 * 
 * @version 1.0
 * @date 2025-03-12
 * 
 * @note
 * - Ensure the servomotors are connected correctly to the hardware.
 * - Call 'armInit' before invoking other functions.
 * 
 * @author Guerrico Leonel
 * 
 */

#ifndef PROGRAM_MAW_INC_ARM_H_
#define PROGRAM_MAW_INC_ARM_H_

/*==================[inclusions]=============================================*/

#include "sapi.h"
#include "UART.h"

/*==================[macros and definitions]===================================*/

#define SERVO_R 	SERVO2	// SERVO2 <---> T_FIL2 of EDU-CIAA-NXP
#define SERVO_EX	SERVO6  // SERVO6 <---> LCD2 of EDU-CIAA-NXP
#define SERVO_E		SERVO7  // SERVO7 <---> LCD3 of EDU-CIAA-NXP
#define SERVO_G		SERVO3  // SERVO3 <---> T_FIL3 of EDU-CIAA-NXP

#define ROTATE 	  	1
#define EXTENSION 	2
#define ALTITUDE  	3
#define GRIPPER	  	4
#define HOME		5

#define ANGLE_GAP 			5
#define MARGIN 				30
#define EXTENSION_MAX_ANGLE 180
#define ELEVATION_MAX_ANGLE 180
#define ELEVATION_MIN_ANGLE 0
#define ROTATION_MAX_LEFT	180
#define ROTATION_MAX_RIGHT	0

/*==================[external function declarations]=======================*/

void armInit(void);
void armCmd(uint8_t, uint16_t);

#endif /* PROGRAM_MAW_INC_ARM_H_ */
