/**
 * @file MotorShield2.h
 * @brief Definitions and declarations for motor shield control on the EDU-CIAA platform
 * 
 * This file contains macro definitions and function declarations to control the vehicle's motors. 
 * It includes pin configurations, available motor commands, and functions to initialize and control the motors.
 * 
 * @version 1.0
 * @date 2025-03-12
 * 
 * @note
 * - Ensure the components are correctly connected to the hardware.
 * - Call 'motorsInit' before invoking other functions.
 * 
 * @author Pérez Balcedo Octavio
 * 
 */

#ifndef PROGRAM_MAW_INC_MOTORSHIELD2_H_
#define PROGRAM_MAW_INC_MOTORSHIELD2_H_

#include "sapi.h"
#include <stdio.h>

#define BV(b) (1 << (b))

// Motor pin definitions
#define MOTOR1_A 2
#define MOTOR1_B 3
#define MOTOR2_A 1
#define MOTOR2_B 4
#define MOTOR4_A 0
#define MOTOR4_B 6
#define MOTOR3_A 5
#define MOTOR3_B 7

// Motor commands
#define FORWARD 1
#define BACKWARD 2
#define BRAKE 3
#define RELEASE 4
#define ROTATERIGHT 5
#define ROTATELEFT 6
#define TURNRIGHT 7
#define TURNLEFT 8
#define TURNRIGHTBACKWARD 9
#define TURNLEFTBACKWARD 10

// Speed limits
#define VEL_MIN 150
#define VEL_MAX 254

// EDU-CIAA_NXP pin names
#define MOTORLATCH GPIO1
#define MOTORCLK GPIO7
#define MOTORENABLE GPIO5
#define MOTORDATA GPIO3

// Function declarations
void motorsInit(void);
uint8_t vehicleCmd(uint8_t cmd, uint16_t angles, uint8_t speed);

#endif /* PROGRAM_MAW_INC_MOTORSHIELD2_H_ */
