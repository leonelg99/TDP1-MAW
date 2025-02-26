/**
 * @file camera_pins.h
 * @brief Definition of the pins for the AI-Thinker camera on the ESP32-CAM.
 * 
 * This file defines the pins used by the AI-Thinker camera, including data pins, synchronization, clock, power, and LED flash control pins.
 * 
 * @author Guerrico Leonel (lguerrico99@gmail.com)
 * @date 15-10-2023
 * @version 1.0
 */

 #ifndef CAMERA_PINS_H
 #define CAMERA_PINS_H
 
 #if defined(CAMERA_MODEL_AI_THINKER)
 
 /** @brief Camera power on/off pin (not always used). */
 #define PWDN_GPIO_NUM     32
 
 /** @brief Camera reset pin (not connected on AI-Thinker). */
 #define RESET_GPIO_NUM    -1
 
 /** @brief Camera clock input pin. */
 #define XCLK_GPIO_NUM      0
 
 /** @brief SDA data pin of the I2C bus for camera control. */
 #define SIOD_GPIO_NUM     26
 
 /** @brief SCL clock pin of the I2C bus for camera control. */
 #define SIOC_GPIO_NUM     27
 
 /** @brief Camera data pins (Y2-Y9). */
 #define Y9_GPIO_NUM       35
 #define Y8_GPIO_NUM       34
 #define Y7_GPIO_NUM       39
 #define Y6_GPIO_NUM       36
 #define Y5_GPIO_NUM       21
 #define Y4_GPIO_NUM       19
 #define Y3_GPIO_NUM       18
 #define Y2_GPIO_NUM        5
 
 /** @brief Camera synchronization and clock pins. */
 #define VSYNC_GPIO_NUM    25  ///< Vertical synchronization pin.
 #define HREF_GPIO_NUM     23  ///< Line reference pin.
 #define PCLK_GPIO_NUM     22  ///< Pixel clock pin.
 
 /** @brief Camera LED pin (Flash or indicator). */
 #define LED_GPIO_NUM       4  
 
 #else
 #error "Camera model not selected"
 #endif
 
 #endif // CAMERA_PINS_H
 