/**
 * @file Comands.c
 * @brief Implementation of control functions for the vehicle and robotic arm system on the EDU-CIAA platform
 * 
 * This file implements the functions to initialize and control the system, including message decoding,
 * executing actions on the motors and the robotic arm, and checking the battery level.
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

/*==================[inclusions]=============================================*/

#include "../inc/Comands.h"

/*==================[macros and definitions]===================================*/
/*
 * LEDSON/LEDSOFF: as their names indicate, they are used to turn on/off a pair of LEDs
 * by activating/deactivating ENET_TXD0.
 * MARGIN: literally a margin, a value used later for angle operations.
 * LOWBATERY: the limit at which the battery level of the EDU-CIAA is considered low.
 * WARNINGBATERY: the limit at which the battery level of the EDU-CIAA is considered very low.
 * DEADBATERY: the limit at which the battery level of the EDU-CIAA is considered extremely low,
 * which can cause malfunction and damage.
 */

#define LEDSON 			gpioWrite( GPIO4 , ON );
#define LEDSOFF 		gpioWrite( GPIO4 , OFF );
#define MARGIN 			30
#define LOWBATERY 		765
#define WARNINGBATERY 	644
#define DEADBATERY 		564
#define MESSAGE_LONG 	30

/*=====[Private global variable definitions]=============================*/

/*
 * MODE: indicates the operating mode of the system. 0 indicates vehicle mode,
 * in this mode we operate the motors to move the vehicle. While with 1, it is arm mode,
 * in which case, we operate the robotic arm.
 * leds: a flag variable used to indicate whether the LEDs are on or off.
 */

static volatile uint8_t MODE=0, leds=0; // VEHICLE MODE
const char m [] = "Execute\n";

/*==================[internal function declarations]=========================*/

/*
 * decodeMessage(): this function decodes the command/message/data received by UART
 * motorAction(): this function activates the motors according to the received command and configuration parameters
 * armAction(): similar to the previous function, this operates the robotic arm according to the received command and configuration parameters.
 */

static void decodeMessage(uint8_t [], uint8_t [], uint16_t *, uint8_t *);
static void motorAction(uint8_t [], uint16_t, uint8_t);
static void armAction(uint8_t [], uint16_t, uint8_t);
static void stickAction (uint8_t [], uint16_t , uint8_t);

/*
 * @brief This function configures and initializes ADC, UART, GPIO4, MotorShield, and system tick.
 */
void programInit(){

    adcConfig( ADC_ENABLE ); /* ADC */
    motorsInit();
    armInit();
    gpioInit(GPIO4,GPIO_OUTPUT);
    serialInit();
    tickWrite(0);
}

/*
 * @brief This function reads channels 1 and 2 of the ADC and determines if the battery level of the EDU-CIAA and/or motors is low.
 * Depending on the battery level, a message can be sent based on how low it is.
 * The battery levels are 4: normal, in which case nothing happens; LOW, meaning the battery level has dropped enough to be considered;
 * WARNING, meaning the battery levels are very low and the battery needs to be charged; and DEAD, in this case the battery level is so low
 * that it could imply not only malfunction but even damage to the system.
 */
void checkPower(){
    uint16_t MotorBatery,CIAABatery;
    char x[20];
    MotorBatery = adcRead(CH2);
    CIAABatery = adcRead(CH1);

    if(MotorBatery <= LOWBATERY)
        sendMsg(1);
    if((CIAABatery <= LOWBATERY) && (CIAABatery > WARNINGBATERY))
        sendMsg(2);
    else if((CIAABatery <= WARNINGBATERY) && (CIAABatery > DEADBATERY))
        sendMsg(3);
    else if(CIAABatery <= DEADBATERY)
        sendMsg(4);

}

/*
 * @brief This function receives the message previously obtained by UART and processes and executes it.
 * The message is processed to obtain 3 values: the command (cmd), value1, and value2
 * (usually angle and speed). Then, depending on the cmd, it will execute different actions,
 * basically, changing MODE (arm or vehicle), turning LEDs on/off, or executing some action
 * through the motors or the arm (depending on the MODE) in which case it will call a specific function for it.
 * @param msg: the instruction to execute and its parameters.
 */
uint8_t executeCmd(uint8_t msg[]){
    uint8_t cmd[7]="";
    uint16_t value1=0;
    uint8_t value2=0;

    gpioWrite( LED2, ON );
    decodeMessage(msg,cmd,&value1,&value2);
    if(strcmp(cmd,"")==0) {
        gpioWrite(LED2,ON);
        delay(300);
        gpioWrite(LED2,OFF);
    }

    if(strcmp(cmd,"Select")==0){
        MODE=!MODE;
        if (MODE == 1)
            sendMsg(9);
        else sendMsg(10);
        return 0;
    }
    if(strcmp(cmd,"Start")==0){
        sendMsg(0);
        if(leds==0) {
            LEDSON;
            leds=!leds;
        } else{
            LEDSOFF;
            leds=!leds;
        }
        return 0;
    }

    if(!MODE){
        motorAction(cmd,value1,value2);
    }else{
        armAction(cmd,value1,value2);
    }
    return 0;
}

/*
 * @brief This function is used to split the message (msg) into 3 variables: cmd, v1, and v2.
 * @param cadena: the string to decode.
 * @param palabra: the first value to obtain from the string. It is a string.
 * @param valor1: the second value to obtain from the string. It is a number from 0 to 360.
 * @param valor2: the third and last value to obtain from the string. It is a number from 0 to 100.
 */
static void decodeMessage(uint8_t cadena[], uint8_t palabra[], uint16_t *valor1, uint8_t *valor2) {
    // Copy the string to avoid modifying the original
    char copia[strlen(cadena) + 1];
    strcpy(copia, cadena);
    float aux=0;

    // Use strtok to split the string into tokens using the ":" delimiter
    char *token = strtok(copia, ":");

    // The first word
    if (token != NULL) {
        strcpy(palabra, token);
    }

    // The first value
    token = strtok(NULL, ":");
    if (token != NULL) {
        sscanf(token, "%hu", valor1);
    }

    // The second value
    token = strtok(NULL, ":");
    if (token != NULL) {
         unsigned int temp_value;
         sscanf(token, "%u", &temp_value);
         *valor2 = (uint8_t)temp_value;
    }
}

/*
 * @brief This function orders the motors to execute an action depending on the cmd, and does so according to value1 and value2 (angle and speed).
 * @param cmd: the pressed button.
 * @param value1: the angle value (0 to 360).
 * @param value2: the analog position (0 to 100).
 */
static void motorAction(uint8_t cmd[], uint16_t value1, uint8_t value2){
    if(strcmp(cmd,"R2")==0){
        vehicleCmd(BRAKE,value1,value2);
    }
    else if ((value1==0) && (value2==0)){
        vehicleCmd(RELEASE,0,0);
    }
    else{
        if((strcmp(cmd,"SR")==0) && (value2!=0)){ //SR STICK RIGHT
            if ((value1>=80) && (value1<=100)){
                vehicleCmd(FORWARD,value1,value2);

            }else if((value1>=170) && (value1<=190)){
                vehicleCmd(ROTATELEFT,value1,value2);

            }else if((value1>=260) && (value1<=280)){
                vehicleCmd(BACKWARD,value1,value2);

            }else if(((value1>=0) && (value1<=10))||((value1>=350)&&(value1<360))){
                vehicleCmd(ROTATERIGHT,value1,value2);

            }else if ((value1<80) && (value1>10)){
                vehicleCmd(TURNRIGHT,value1,value2);

            }else if((value1>100) && (value1<170)){
                vehicleCmd(TURNLEFT,value1,value2);

            }else if((value1>190) && (value1<260)){
                vehicleCmd(TURNLEFTBACKWARD,value1,value2);

            }else if(((value1<370) && (value1>280))){
                vehicleCmd(TURNRIGHTBACKWARD,value1,value2);
            }
        }
    }
}

/*
 * @brief This function orders the arm to execute an action depending on the cmd, and does so according to value1 (angle).
 * @param cmd: the pressed button.
 * @param value1: the angle value (0 to 360).
 * @param value2: the analog position (0 to 100).
 */
static void armAction(uint8_t cmd[], uint16_t value1, uint8_t value2){

    uint8_t aux=0,stop=0;
    uint8_t cmd2[7]="";
    uint16_t value10=0;
    uint8_t value20=0;
    uint8_t msg[MESSAGE_LONG]={};

    if(((strcmp(cmd,"SR")==0) || (strcmp(cmd,"SL")==0)) && (value2 != 0) ){
        while(!stop){
                 stickAction(cmd,value1,value2);
                 delay(500);
                 if(receiveMsg(msg,MESSAGE_LONG)){
                     decodeMessage(msg,cmd2,&value10,&value20);
                     if((strcmp(cmd2,"SR") || (strcmp(cmd2,"SL"))) && (value10==0) && (value20==0))
                         stop=!stop;
                     memset(msg,'\0',sizeof(msg));
                 }
            }
        aux=1;
        }

    if(!aux && strcmp(cmd,"R2")==0){
        //Close
        armCmd(GRIPPER,0);
        aux=1;
    }
    if(!aux && strcmp(cmd,"R1")==0){
        //OPEN
        armCmd(GRIPPER,1);
        aux=1;
    }

    if(!aux && strcmp(cmd,"L1")==0){
        //OPEN FULL
        armCmd(GRIPPER,2);
        aux=1;
    }
    if(!aux && strcmp(cmd,"L2")==0){
        //CLOSE FULL only if full open otherwise servo could be damage
        armCmd(GRIPPER,3);
        aux=1;
    }

    if(!aux && strcmp(cmd,"SLL")==0){
        amdCmd(HOME,0);
    }
    delay(500);

}

/*
 * @brief This function encompasses the arm actions generated using the analog sticks.
 * @param cmd: the pressed button.
 * @param value1: the angle value (0 to 360).
 * @param value2: the analog position (0 to 100).
 */
static void stickAction (uint8_t cmd[], uint16_t value1, uint8_t value2){
    if(strcmp(cmd,"SR")==0){
        if ((value1>=(90-MARGIN)) && (value1<=(90+MARGIN))){
                armCmd(EXTENSION,value1);
        }else if((value1>=(270-MARGIN)) && (value1<=(270+MARGIN))){
                armCmd(EXTENSION,value1);
        }else if((value1>=(180-MARGIN)) && (value1<=(180+MARGIN))){
                armCmd(ROTATE,value1);
        }else if(((value1>=0) && (value1<=MARGIN))||((value1>=(360-MARGIN))&&(value1<360))){
                armCmd(ROTATE,value1);
        }
     }else
        if(strcmp(cmd,"SL")==0){
            if((value1 >= 90-MARGIN) && (value1 <= 90+MARGIN))
                armCmd(ALTITUDE,0);
            else if ((value1 >= 270-MARGIN) && (value1 <= 270+MARGIN))
                armCmd(ALTITUDE,1);
        }
}
