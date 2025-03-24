/**
 * @file MotorShield2.c
 * @brief Implementation of control functions for the motor shield on the EDU-CIAA platform
 * 
 * This file contains the functions to initialize and control the motors of the vehicle. 
 * It includes functions to configure PWM, control the direction and speed of the motors, 
 * and execute specific commands for the vehicle's movement.
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

#include "../inc/MotorShield2.h"

// MACROS

#define SCALATE(value) (((value) > 100) ? 255 : ((uint8_t)(((uint16_t)(value) * 155) / 100 + 100)))

// Function Prototypes
static void latchTx(void);
static void motorsEnable(void);
static inline uint8_t initPWM1(void);
static inline uint8_t initPWM2(void);
static inline uint8_t initPWM3(void);
static inline uint8_t initPWM4(void);
static inline uint8_t setPWM1(uint8_t);
static inline uint8_t setPWM2(uint8_t);
static inline uint8_t setPWM3(uint8_t);
static inline uint8_t setPWM4(uint8_t);
static void setSpeed(uint8_t, uint8_t);
static void run(uint8_t, uint8_t);
static uint8_t goForward(uint8_t);
static uint8_t goBackward(uint8_t);
static uint8_t goRelease(void);
static uint8_t goRotateRight(uint8_t);
static uint8_t goRotateLeft(uint8_t);
static uint8_t goTurnRight(uint8_t, uint8_t);
static uint8_t goTurnLeft(uint8_t, uint8_t);
static uint8_t goTurnRightBackward(uint8_t, uint8_t);
static uint8_t goTurnLeftBackward(uint8_t, uint8_t);

/******************************************
           LATCH CONTROLLER
******************************************/
uint8_t latch_state = 0;

/*
 * latchTx(): This function performs the bit sequence that will be sent to the latch 
 * within the L293D driver for controlling the DC motors.
 */
static void latchTx(void) {
    uint8_t i;
    gpioWrite(MOTORLATCH, LOW);
    gpioWrite(MOTORDATA, LOW);

    for (i = 0; i < 8; i++) {
        gpioWrite(MOTORCLK, LOW);

        if (latch_state & BV(7 - i)) {
            gpioWrite(MOTORDATA, HIGH);
        } else {
            gpioWrite(MOTORDATA, LOW);
        }
        gpioWrite(MOTORCLK, HIGH);
    }
    gpioWrite(MOTORLATCH, HIGH);
}

/*
 * motorsEnable(): This function initializes the pin control of the driver.
 */
static void motorsEnable(void) {
    // Configure the latch
    gpioInit(MOTORLATCH, GPIO_OUTPUT);
    gpioInit(MOTORENABLE, GPIO_OUTPUT);
    gpioInit(MOTORDATA, GPIO_OUTPUT);
    gpioInit(MOTORCLK, GPIO_OUTPUT);

    latch_state = 0;

    latchTx();  // "reset"

    gpioWrite(MOTORENABLE, LOW); // Enable the chip outputs!
}

/******************************************
               MOTORS
******************************************/

/*
 * initPWM1(): Initializes the "PWM 1" signal that will be used for the corresponding motor.
 */
static inline uint8_t initPWM1() {
    return (pwmInit(PWM0, PWM_ENABLE));
}

/*
 * setPWM1(WCvalue): Sets the duty cycle of the "PWM 1" signal with a value "WCvalue".
 */
static inline uint8_t setPWM1(uint8_t WCvalue) {
    uint8_t error = 1;

    if (!pwmInit(PWM0, PWM_ENABLE_OUTPUT)) {
        error = 0;
    }
    if (!pwmWrite(PWM0, WCvalue)) {
        error = -1;
    }
    return (error);
}

/*
 * initPWM2(): Initializes the "PWM 2" signal that will be used for the corresponding motor.
 */
static inline uint8_t initPWM2() {
    return (pwmInit(PWM1, PWM_ENABLE));
}

/*
 * setPWM2(WCvalue): Sets the duty cycle of the "PWM 2" signal with a value "WCvalue".
 */
static inline uint8_t setPWM2(uint8_t WCvalue) {
    uint8_t error = 1;
    if (!pwmInit(PWM1, PWM_ENABLE_OUTPUT)) {
        error = 0;
    }
    if (!pwmWrite(PWM1, WCvalue)) {
        error = -1;
    }
    return (error);
}

/*
 * initPWM3(): Initializes the "PWM 3" signal that will be used for the corresponding motor.
 */
static inline uint8_t initPWM3() {
    return (pwmInit(PWM2, PWM_ENABLE));
}

/*
 * setPWM3(WCvalue): Sets the duty cycle of the "PWM 3" signal with a value "WCvalue".
 */
static inline uint8_t setPWM3(uint8_t WCvalue) {
    uint8_t error = 1;
    if (!pwmInit(PWM2, PWM_ENABLE_OUTPUT)) {
        error = 0;
    }
    if (!pwmWrite(PWM2, WCvalue)) {
        error = -1;
    }
    return (error);
}

/*
 * initPWM4(): Initializes the "PWM 4" signal that will be used for the corresponding motor.
 */
static inline uint8_t initPWM4() {
    return (pwmInit(PWM3, PWM_ENABLE));
}

/*
 * setPWM4(WCvalue): Sets the duty cycle of the "PWM 4" signal with a value "WCvalue".
 */
static inline uint8_t setPWM4(uint8_t WCvalue) {
    uint8_t error = 1;
    if (!pwmInit(PWM3, PWM_ENABLE_OUTPUT)) {
        error = 0;
    }
    if (!pwmWrite(PWM1, WCvalue)) {
        error = -1;
    }
    return (error);
}

/*
 * motorsInit(): Forces an initial value upon the 4 motors of the robot. This is done so that
 * the motors have a known value during the start up of the system.
 */
void motorsInit() {
    motorsEnable();
    for (int num = 1; num <= 4; num++) {
        switch (num) {
            case 1:
                latch_state &= ~BV(MOTOR1_A) & ~BV(MOTOR1_B); // set both motor pins to 0
                latchTx();
                initPWM1();
                break;
            case 2:
                latch_state &= ~BV(MOTOR2_A) & ~BV(MOTOR2_B); // set both motor pins to 0
                latchTx();
                initPWM2();
                break;
            case 3:
                latch_state &= ~BV(MOTOR3_A) & ~BV(MOTOR3_B); // set both motor pins to 0
                latchTx();
                initPWM3();
                break;
            case 4:
                latch_state &= ~BV(MOTOR4_A) & ~BV(MOTOR4_B); // set both motor pins to 0
                latchTx();
                initPWM4();
                break;
        }
    }
}

/*
 * setSpeed(motornum, WCvalue): This function sets the value "WCvalue" as the duty cycle
 * value of the "motornum" PWM signal. For example, setSpeed(1, 255) would set the value of
 * the PWM 1 signal's duty cycle at a value of 255.
 */
static void setSpeed(uint8_t motornum, uint8_t WCvalue) {
    switch (motornum) {
        case 1:
            setPWM1(WCvalue);
            break;
        case 2:
            setPWM2(WCvalue);
            break;
        case 3:
            setPWM3(WCvalue);
            break;
        case 4:
            setPWM4(WCvalue);
            break;
    }
}

/*
 * run(motornum, cmd): Executes the command "cmd" on the "motornum" motor. The available
 * commands for the motors are:
 *      - BRAKE: stops the wheels from moving
 *      - FORWARD: spins the wheels forward
 *      - BACKWARD: spins the wheels backward
 *      - RELEASE: lets the wheels spin freely
 */
static void run(uint8_t motornum, uint8_t cmd) {
    uint8_t a, b;
    switch (motornum) {
        case 1:
            a = MOTOR1_A;
            b = MOTOR1_B;
            break;
        case 2:
            a = MOTOR2_A;
            b = MOTOR2_B;
            break;
        case 3:
            a = MOTOR3_A;
            b = MOTOR3_B;
            break;
        case 4:
            a = MOTOR4_A;
            b = MOTOR4_B;
            break;
        default:
            break;
    }

    switch (cmd) {
        case BRAKE:
            latch_state |= BV(a);
            latch_state |= BV(b);
            latchTx();
            break;
        case FORWARD:
            latch_state |= BV(a);
            latch_state &= ~BV(b);
            latchTx();
            break;
        case BACKWARD:
            latch_state &= ~BV(a);
            latch_state |= BV(b);
            latchTx();
            break;
        case RELEASE:
            latch_state &= ~BV(a);
            latch_state &= ~BV(b);
            latchTx();
            break;
    }
}

/*
 *
 * M1 |------| M4
 *       |
 *       |
 * M2 |------| M3
 *
 */

/*
 * goForward(speed): Makes the robot go forward at a "speed" velocity.
 */
static uint8_t goForward(uint8_t speed) {
    for (int i = 1; i <= 4; i++) {
        if (i == 2)
            setSpeed(i, ((speed * 80) / 100));
        else if (i == 1)
            setSpeed(i, ((speed * 120) / 100));
        else
            setSpeed(i, speed);
    }
    for (int i = 1; i <= 4; i++) {
        run(i, FORWARD);
    }
}

/*
 * goBackward(speed): Makes the robot go backward at a "speed" velocity.
 */
static uint8_t goBackward(uint8_t speed) {
    for (int i = 1; i <= 4; i++) {
        setSpeed(i, speed);
    }
    run(1, BACKWARD);
    delay(10);
    run(3, BACKWARD);
    run(4, BACKWARD);
    delay(30);
    run(2, BACKWARD);
}

/*
 * goRelease(): Releases the wheels of the robot.
 */
static uint8_t goRelease() {
    for (int i = 1; i <= 4; i++) {
        setSpeed(i, 0);
    }
    for (int i = 1; i <= 4; i++) {
        run(i, RELEASE);
    }
    return 0;
}

/*
 * goRotateRight(speed): The robot makes a clockwise spin over its own axis at a "speed" velocity.
 */
static uint8_t goRotateRight(uint8_t speed) {
    for (int i = 1; i <= 4; i++) {
        setSpeed(i, speed);
    }
    for (int i = 1; i <= 2; i++) {
        run(i, FORWARD);
    }
    for (int i = 3; i <= 4; i++) {
        run(i, BACKWARD);
    }

    return 0;
}

/*
 * goRotateLeft(speed): The robot makes a counter-clockwise spin over its own axis
 * at a "speed" velocity.
 */
static uint8_t goRotateLeft(uint8_t speed) {
    for (int i = 1; i <= 4; i++) {
        setSpeed(i, speed);
    }
    for (int i = 1; i <= 2; i++) {
        run(i, BACKWARD);
    }
    for (int i = 3; i <= 4; i++) {
        run(i, FORWARD);
    }
    return 0;
}

/*
 * goBrake(): Brakes the wheels of the robot.
 */
static uint8_t goBrake() {
    for (int i = 1; i <= 4; i++) {
        setSpeed(i, 0);
    }
    for (int i = 1; i <= 4; i++) {
        run(i, BRAKE);
    }
    return 0;
}

/*
 * forwardBasedOnRightSegment(speed, segmentNumber): Makes the robot move forward while turning to
 * its right. The turning angle is determined by "segmentNumber" and the speed in which turns its
 * between "speed * 1/8" and "speed * 7/8".
 */
static void forwardBasedOnRightSegment(uint8_t speed, uint8_t segmentNumber) {
    uint8_t aux = speed * (segmentNumber / 8);
    if (aux < VEL_MIN) aux = VEL_MIN;

    for (int i = 1; i <= 2; i++) {
        setSpeed(i, speed);
    }
    for (int i = 3; i <= 4; i++) {
        setSpeed(i, aux);
    }
    for (int i = 1; i <= 4; i++) {
        run(i, FORWARD);
    }
}

/*
 * forwardBasedOnLeftSegment(speed, segmentNumber): Makes the robot move forward while turning to
 * its left. The turning angle is determined by "segmentNumber" and the speed in which turns its
 * between "speed * 1/8" and "speed * 7/8".
 */
static void forwardBasedOnLeftSegment(uint8_t speed, uint8_t segmentNumber) {
    uint8_t aux = speed * (segmentNumber / 8);
    if (aux < VEL_MIN) aux = VEL_MIN;

    for (int i = 1; i <= 2; i++) {
        setSpeed(i, aux);
    }
    for (int i = 3; i <= 4; i++) {
        setSpeed(i, speed);
    }
    for (int i = 1; i <= 4; i++) {
        run(i, FORWARD);
    }
}

// AUX = 0 means error
// AUX = 1 means it executed correctly

/*
 * goTurnRight(angle, speed): Determines the aforementioned "segmentNumber" that the
 * forwardBasedOnRightSegment function will use. The segmentations of the possible angles
 * is done by dividing the range between 10° to 80° in 8 segments.
 */
static uint8_t goTurnRight(uint8_t angle, uint8_t speed) {
    uint8_t aux = 0;

    if (speed < VEL_MIN) speed = VEL_MIN;

    for (int i = 1; i < 8; i++) {
        if (angle <= (i + 1) * 10) { // Checks if the angle is between 10 degrees and 80 degrees
            forwardBasedOnRightSegment(speed, i);
            aux = 1;
            break;
        }
    }
    return aux;
}

// AUX = 0 means error
// AUX = 1 means it executed correctly

/*
 * goTurnLeft(angle, speed): Determines the aforementioned "segmentNumber" that the
 * forwardBasedOnLeftSegment function will use. The segmentations of the possible angles
 * is done by dividing the range between 170° to 100° in 8 segments.
 */
static uint8_t goTurnLeft(uint8_t angle, uint8_t speed) {
    uint8_t aux = 0;

    if (speed < VEL_MIN) speed = VEL_MIN;

    for (int i = 1; i < 8; i++) {
        if (angle <= (i + 1 + 9) * 10) { // Checks if the angle is between 100 and 170 degrees
            forwardBasedOnLeftSegment(speed, i);
            aux = 1;
            break;
        }
    }
    return aux;
}

//---------------------------------------------------------------------
/*
 * backwardBasedOnRightSegment(speed, segmentNumber): Makes the robot move backwards while turning to
 * its right. The turning angle is determined by "segmentNumber" and the speed in which turns its
 * between "speed * 1/8" and "speed * 7/8".
 */
static void backwardBasedOnRightSegment(uint8_t speed, uint8_t segmentNumber) {
    uint8_t aux = speed * (segmentNumber / 8);
    if (aux < VEL_MIN) aux = VEL_MIN;

    for (int i = 1; i <= 2; i++) {
        setSpeed(i, speed);
    }
    for (int i = 3; i <= 4; i++) {
        setSpeed(i, aux);
    }
    for (int i = 1; i <= 4; i++) {
        run(i, BACKWARD);
    }
}

/*
 * backwardBasedOnLeftSegment(speed, segmentNumber): Makes the robot move backwards while turning to
 * its left. The turning angle is determined by "segmentNumber" and the speed in which turns its
 * between "speed * 1/8" and "speed * 7/8".
 */
static void backwardBasedOnLeftSegment(uint8_t speed, uint8_t segmentNumber) {
    uint8_t aux = speed * (segmentNumber / 8);
    if (aux < VEL_MIN) aux = VEL_MIN;

    for (int i = 1; i <= 2; i++) {
        setSpeed(i, aux);
    }
    for (int i = 3; i <= 4; i++) {
        setSpeed(i, speed);
    }
    for (int i = 1; i <= 4; i++) {
        run(i, BACKWARD);
    }
}

// AUX = 0 means error
// AUX = 1 means it executed correctly

/*
 * goTurnRightBackward(angle, speed): Determines the aforementioned "segmentNumber" that the
 * backwardBasedOnRightSegment function will use. The segmentations of the possible angles
 * is done by dividing the range between 280° to 350° in 8 segments.
 */
static uint8_t goTurnRightBackward(uint8_t angle, uint8_t speed) {
    uint8_t aux = 0;

    if (speed < VEL_MIN) speed = VEL_MIN;

    for (int i = 1; i < 8; i++) {
        if (angle <= (i + 1 + 27) * 10) { // Checks if the angle is between 280 degrees and 350 degrees
            backwardBasedOnRightSegment(speed, i);
            aux = 1;
            break;
        }
    }
    return aux;
}

// AUX = 0 means error
// AUX = 1 means it executed correctly

/*
 * goTurnLeftBackward(angle, speed): Determines the aforementioned "segmentNumber" that the
 * backwardBasedOnLeftSegment function will use. The segmentations of the possible angles
 * is done by dividing the range between 190° to 260° in 8 segments.
 */
static uint8_t goTurnLeftBackward(uint8_t angle, uint8_t speed) {
    uint8_t aux = 0;

    if (speed < VEL_MIN) speed = VEL_MIN;

    for (int i = 1; i < 8; i++) {
        if (angle <= (i + 1 + 18) * 10) { // Checks if the angle is between 190 and 260 degrees
            backwardBasedOnLeftSegment(speed, i);
            aux = 1;
            break;
        }
    }
    return aux;
}
//---------------------------------------------------------------------

/*
 * vehicleCmd(cmd, angle, speed): This function calls the previously introduced functions based on
 * the requirements made by the "cmd" command. Although they're not always used, the "angle" and
 * "speed" variables are also included in the function call, so they're used when needed to.
 */
uint8_t vehicleCmd(uint8_t cmd, uint16_t angle, uint8_t speed) {

    uint8_t sp = SCALATE(speed);

    switch (cmd) {
        case FORWARD:
            goForward(speed);
            break;
        case BACKWARD:
            goBackward(speed);
            break;
        case RELEASE:
            goRelease();
            break;
        case ROTATERIGHT:
            goRotateRight(speed);
            break;
        case ROTATELEFT:
            goRotateLeft(speed);
            break;
        case TURNRIGHT:
            goTurnRight(angle, speed);
            break;
        case TURNLEFT:
            goTurnLeft(angle, speed);
            break;
        case TURNRIGHTBACKWARD:
            goTurnRightBackward(angle, speed);
            break;
        case TURNLEFTBACKWARD:
            goTurnLeftBackward(angle, speed);
            break;
        case BRAKE:
            goBrake();
            break;
    }
}
