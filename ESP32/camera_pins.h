/**
 * @file camera_pins.h
 * @brief Definición de los pines para la cámara AI-Thinker en el ESP32-CAM.
 * 
 * Este archivo define los pines utilizados por la cámara AI-Thinker, incluyendo los
 * pines de datos, sincronización, reloj, alimentación y control del LED flash.
 * 
 * @author [Tu Nombre]
 * @date [Fecha]
 * @version 1.0
 */

 #ifndef CAMERA_PINS_H
 #define CAMERA_PINS_H
 
 #if defined(CAMERA_MODEL_AI_THINKER)
 
 /** @brief Pin de encendido/apagado de la cámara (no siempre utilizado). */
 #define PWDN_GPIO_NUM     32
 
 /** @brief Pin de reinicio de la cámara (no conectado en AI-Thinker). */
 #define RESET_GPIO_NUM    -1
 
 /** @brief Pin de entrada del reloj de la cámara. */
 #define XCLK_GPIO_NUM      0
 
 /** @brief Pin de datos SDA del bus I2C para control de la cámara. */
 #define SIOD_GPIO_NUM     26
 
 /** @brief Pin de reloj SCL del bus I2C para control de la cámara. */
 #define SIOC_GPIO_NUM     27
 
 /** @brief Pines de datos de la cámara (Y2-Y9). */
 #define Y9_GPIO_NUM       35
 #define Y8_GPIO_NUM       34
 #define Y7_GPIO_NUM       39
 #define Y6_GPIO_NUM       36
 #define Y5_GPIO_NUM       21
 #define Y4_GPIO_NUM       19
 #define Y3_GPIO_NUM       18
 #define Y2_GPIO_NUM        5
 
 /** @brief Pines de sincronización y reloj de la cámara. */
 #define VSYNC_GPIO_NUM    25  ///< Pin de sincronización vertical.
 #define HREF_GPIO_NUM     23  ///< Pin de referencia de línea.
 #define PCLK_GPIO_NUM     22  ///< Pin de reloj de píxeles.
 
 /** @brief Pin del LED de la cámara (Flash o indicador). */
 #define LED_GPIO_NUM       4  
 
 #else
 #error "Camera model not selected"
 #endif
 
 #endif // CAMERA_PINS_H
 