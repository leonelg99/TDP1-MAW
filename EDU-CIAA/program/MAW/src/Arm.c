/**
 * @file Arm.c
 * @brief Implementation of the robotic arm control library for the EDU-CIAA platform
 * 
 * This file implements the functions for initializing and controlling the robotic arm. 
 * It includes functions to initialize the servomotors, rotate the arm, extend/retract the arm, 
 * control the elevation, operate the gripper, and return the arm to the home position.
 * 
 * @version 1.0
 * @date 2025-03-12
 * 
 * @note
 * - Ensure the servomotors are connected correctly to the hardware.
 * - Call 'armInit' before invoking other functions.
 * 
 * @author Guerrico Leonel
 */

#include "../inc/Arm.h"

//Actual position of servo motors
static uint8_t angleR=0;
static uint8_t angleEX=0;
static uint8_t angleE=0;
static uint8_t angleG=0;

/*==================[internal functions declaration]=========================*/

static void servoInits(void);
static void rotate(uint8_t);
static void extend(uint8_t);

/*
 * @brief This function initializes the arm servomotors.
 */
static void servosInits(){
    servoConfig( 0, SERVO_ENABLE );
    servoConfig( SERVO_R,  SERVO_ENABLE_OUTPUT);
    servoConfig( SERVO_EX, SERVO_ENABLE_OUTPUT);
    servoConfig( SERVO_E,  SERVO_ENABLE_OUTPUT);
    servoConfig( SERVO_G,  SERVO_ENABLE_OUTPUT);
}

/*
 * @brief This function initializes the arm servomotors and sets them into the correct position.
 */
void armInit(){
    servosInits();
    servoWrite(SERVO_R,90);
}

/*
 * @brief This function rotates the arm base between 0 and 180 degrees.
 * @param value: The angle of rotation used to discern to which side to rotate.
 */
static void rotate(uint8_t value){
    angleR = servoRead(SERVO_R);
    if((value>=180-MARGIN) && (value<=180+MARGIN)){	//LEFT
        if(angleR<ROTATION_MAX_LEFT)
            servoWrite(SERVO_R,(angleR+ANGLE_GAP));
        else sendMsg(11);
    }else if(((value>=0) && (value<=10))||((value>=350)&&(value<360))){		//RIGHT
        if(angleR>ROTATION_MAX_RIGHT)
                    servoWrite(SERVO_R,(angleR-ANGLE_GAP));
         else sendMsg(11);
    }
}

/*
 * @brief This function extends and retracts the arm.
 * @param value: The angle of rotation used to discern if extend or retract the arm.
 */
static void extend(uint8_t value){
    angleEX = servoRead(SERVO_EX);
    if((value>=90-MARGIN) && (value<=90+MARGIN)){
        if(angleEX<EXTENSION_MAX_ANGLE)
            servoWrite(SERVO_EX,(angleEX+ANGLE_GAP));
        else sendMsg(3);
    }else if ((value>=270-MARGIN) && (value<=270+MARGIN)){
        if(angleEX>0)
            servoWrite(SERVO_EX,(angleEX-ANGLE_GAP));
        else sendMsg(3);
    }
}

/*
 * @brief This function controls the elevation of the arm.
 * @param value: The angle of rotation used to discern if elevate or lower the arm.
 */
static void elevation(uint8_t value){
    angleE = servoRead(SERVO_E);
    if((value>=90-MARGIN) && (value<=90+MARGIN)){
        if(angleE<ELEVATION_MAX_ANGLE)
            servoWrite(SERVO_E,(angleE+ANGLE_GAP));
        else sendMsg(3);
    }else if ((value>=270-MARGIN) && (value<=270+MARGIN)){
        if(angleE>ELEVATION_MIN_ANGLE)
            servoWrite(SERVO_E,(angleE-ANGLE_GAP));
        else sendMsg(3);
    }
}

/*
 * @brief This function opens or closes the arm gripper.
 * @param value: A value to discern between close, open, fully close or fully open the gripper.
 */
static void gripper(uint16_t value){
    angleG = servoRead(SERVO_G);
    if(value < 2){
        if(value == 0){
            if(angleG>0)
                servoWrite(SERVO_G,angleG-ANGLE_GAP);
            else sendMsg(12);
        }else{
            if(angleG<90)
                servoWrite(SERVO_G,angleG+ANGLE_GAP);
            else sendMsg(13);
        }
    }else {
        if(value == 2){
            if(angleG < 90)
                servoWrite(SERVO_G,90);
            else sendMsg(13);
        }else{
            if(angleG > 0)
                servoWrite(SERVO_G,0);
            else sendMsg(12);
        }
    }
}

/*
 * @brief This function manages the arm to return to home position based on the actual position of the servomotors.
 */
static void goHome(){
    angleG = servoRead(SERVO_G);
    angleR = servoRead(SERVO_R);
    angleE = servoRead(SERVO_E);
    angleEX = servoRead(SERVO_EX);
    if(angleG<=90) gripper(2); //Open full gripper

    //Elevation depends on extension grade
    //
}

/*
 * @brief This function executes one of the possible actions of the arm based on the cmd value.
 * @param cmd: The value used to discern which action to execute.
 * @param value: A parameter used by the different actions.
 */
void armCmd(uint8_t cmd, uint16_t value){

    switch(cmd){
    case ROTATE:
        rotate(value);
        break;
    case EXTENSION:
        extend(value);
        break;
    case ALTITUDE:
        elevation(value);
        break;
    case GRIPPER:
        gripper(value);
        break;
    case HOME:
        goHome();
        break;
    }
}
