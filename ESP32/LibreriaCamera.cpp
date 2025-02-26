/**
 * @file LibreriaCamera.c
 * @brief Implementation of the library for managing the camera on the ESP32-CAM.
 *
 * This implementation includes the camera initialization, video streaming configuration,
 * dynamic resolution changes, and flash LED control.
 *
 * @author Guerrico Leonel (lguerrico99@gmail.com) & Ossola Florencia (flor.ossola13@gmail.com)
 * @date 14-02-2024
 * @version 1.0
 */

 #include "LibreriaCamera.h"
 #include "esp_timer.h"
 #include "img_converters.h"
 #include "fb_gfx.h"
 #include "soc/soc.h"           ///< Disables brownout issues.
 #include "soc/rtc_cntl_reg.h"  ///< Disables brownout issues.
 #include "esp_http_server.h"
 
 #define PART_BOUNDARY "123456789000000000000987654321"
 #define LED_PIN 4 ///< Pin where the ESP32-CAM LED is connected.
 
 static const char* _STREAM_CONTENT_TYPE = "multipart/x-mixed-replace;boundary=" PART_BOUNDARY;
 static const char* _STREAM_BOUNDARY = "\r\n--" PART_BOUNDARY "\r\n";
 static const char* _STREAM_PART = "Content-Type: image/jpeg\r\nContent-Length: %u\r\n\r\n";
 
 static bool led_state = false; ///< Current LED state (on/off).
 
 // Resolutions and image qualities
 const int videoFramesizeUXGA = 10;
 const int videoFramesizeSVGA = 7;
 const int videoQualityLow = 12;
 const int videoQualityHigh = 10;
 int framesize = videoFramesizeSVGA;
 
 httpd_handle_t stream_httpd = NULL; ///< HTTP server handler.
 
 camera_config_t config; ///< Camera configuration structure.
 
 /**
  * @brief Configures and initializes the camera connected to the ESP32-CAM.
  * 
  * Initializes camera parameters such as resolution, image quality, and pin configuration.
  * It also handles initialization errors.
  */
 void cameraSetup() {
     pinMode(LED_PIN, OUTPUT);
     WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0); // Disables the brownout detector.
 
     // Camera pin configuration
     config.ledc_channel = LEDC_CHANNEL_0;
     config.ledc_timer = LEDC_TIMER_0;
     config.pin_d0 = Y2_GPIO_NUM;
     config.pin_d1 = Y3_GPIO_NUM;
     config.pin_d2 = Y4_GPIO_NUM;
     config.pin_d3 = Y5_GPIO_NUM;
     config.pin_d4 = Y6_GPIO_NUM;
     config.pin_d5 = Y7_GPIO_NUM;
     config.pin_d6 = Y8_GPIO_NUM;
     config.pin_d7 = Y9_GPIO_NUM;
     config.pin_xclk = XCLK_GPIO_NUM;
     config.pin_pclk = PCLK_GPIO_NUM;
     config.pin_vsync = VSYNC_GPIO_NUM;
     config.pin_href = HREF_GPIO_NUM;
     config.pin_sscb_sda = SIOD_GPIO_NUM;
     config.pin_sscb_scl = SIOC_GPIO_NUM;
     config.pin_pwdn = PWDN_GPIO_NUM;
     config.pin_reset = RESET_GPIO_NUM;
     config.xclk_freq_hz = 32000000;
     config.pixel_format = PIXFORMAT_JPEG;
 
     if (psramFound()) {
         config.frame_size = FRAMESIZE_SVGA;
         config.jpeg_quality = 5;
         config.fb_count = 3;
         framesize = 7;
     } else {
         config.frame_size = FRAMESIZE_SVGA;
         config.jpeg_quality = 12;
         config.fb_count = 1;
         framesize = 7;
     }
 
     // Initialize the camera
     esp_err_t err = esp_camera_init(&config);
     if (err != ESP_OK) {
         return;
     }
 
     cameraExecute();
 }
 
 /**
  * @brief Handles real-time video streaming over HTTP.
  * 
  * Continuously captures and sends JPEG images.
  */
 static esp_err_t stream_handler(httpd_req_t *req) {
     camera_fb_t *fb = NULL;
     esp_err_t res = ESP_OK;
     size_t _jpg_buf_len = 0;
     uint8_t * _jpg_buf = NULL;
     char part_buf[64];
 
     res = httpd_resp_set_type(req, _STREAM_CONTENT_TYPE);
     if (res != ESP_OK) {
         return res;
     }
 
     while (true) {
         fb = esp_camera_fb_get();
         if (!fb) {
             res = ESP_FAIL;
         } else {
             if (fb->width > 400 && fb->format != PIXFORMAT_JPEG) {
                 bool jpeg_converted = frame2jpg(fb, 80, &_jpg_buf, &_jpg_buf_len);
                 esp_camera_fb_return(fb);
                 fb = NULL;
                 if (!jpeg_converted) {
                     res = ESP_FAIL;
                 }
             } else {
                 _jpg_buf_len = fb->len;
                 _jpg_buf = fb->buf;
             }
         }
 
         if (res == ESP_OK) {
             size_t hlen = snprintf((char *)part_buf, 64, _STREAM_PART, _jpg_buf_len);
             res = httpd_resp_send_chunk(req, (const char *)part_buf, hlen);
         }
         if (fb) {
             esp_camera_fb_return(fb);
         } else if (_jpg_buf) {
             free(_jpg_buf);
         }
         if (res != ESP_OK) {
             break;
         }
     }
     return res;
 }
 
 /**
  * @brief Starts the HTTP server for video streaming.
  */
 void cameraExecute() {
     httpd_config_t config = HTTPD_DEFAULT_CONFIG();
     config.server_port = 8020;
 
     httpd_uri_t index_uri = {
         .uri       = "/",
         .method    = HTTP_GET,
         .handler   = stream_handler,
         .user_ctx  = NULL
     };
 
     if (httpd_start(&stream_httpd, &config) == ESP_OK) {
         httpd_register_uri_handler(stream_httpd, &index_uri);
     }
 }
 
 /**
  * @brief Changes the camera resolution at runtime.
  */
 void changeResolution() {
     framesize = (framesize == videoFramesizeSVGA) ? videoFramesizeUXGA : videoFramesizeSVGA;
     config.frame_size = (framesize_t)framesize;
     esp_camera_init(&config);
 }
 
 /**
  * @brief Controls the turning on and off of the ESP32-CAM's flash LED.
  */
 void led() {
     led_state = !led_state;
     digitalWrite(LED_PIN, led_state ? HIGH : LOW);
 }
 