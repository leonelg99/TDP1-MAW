/**
 * @file MAW.c
 * @brief Implementation of the main program for the vehicle and robotic arm system on the EDU-CIAA platform
 * 
 * This file contains the main function of the program, which is responsible for initializing the system and executing the main loop.
 * The main loop handles executing commands received via UART and checking battery levels every minute.
 * 
 * @version 1.0
 * @date 2025-03-12
 * 
 * @note
 * - Ensure the components are correctly connected to the hardware.
 * - Call 'programInit' before invoking other functions.
 * 
* @author Guerrico Leonel - Ossola Florencia - Pérez Balcedo Octavio
 * 
 */

/*=====[Inclusions of function dependencies]=================================*/

#include "../inc/MAW.h"
#include "sapi.h"
#include "../inc/Comands.h"
#include "../inc/UART.h"
#include "../inc/MotorShield2.h"

/*=====[Definition macros of private constants]==============================*/

#define MESSAGE_LONG 30

/*=====[Definitions of extern global variables]==============================*/

/*=====[Definitions of public global variables]==============================*/

/*=====[Definitions of private global variables]=============================*/

/*=====[Main function, program entry point after power on or reset]==========*/
/*
 * @brief: The main function of the program starts by calling functions to configure the system and
 * initialize the necessary variables, and finally executes a loop (while(true)) where everything happens.
 * The loop essentially does two things: execute a command if there is one incoming via UART and
 * check the battery levels every minute.
 */

int main( void )
{

     boardConfig();
     programInit();
     uint8_t volatile msg[MESSAGE_LONG]={};
     tick_t tiempoEnTicks = 0;
     uint8_t x=0;

     while(1){
         
         if(receiveMsg(msg,MESSAGE_LONG)){
             executeCmd(msg);
             uartWriteString( UART, msg);
          }

        tiempoEnTicks = tickRead();


          if( tiempoEnTicks >= 6000 ){
              checkPower();
              tickWrite(0);
         }
         
         memset(msg,'\0',sizeof(msg));

     }

     return 0;
}
