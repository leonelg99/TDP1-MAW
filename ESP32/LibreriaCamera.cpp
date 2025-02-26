/**
 * @file LibreriaCamera.c
 * @brief Implementación de la librería para la gestión de la cámara en el ESP32-CAM.
 *
 * Esta implementación incluye la inicialización de la cámara, la configuración
 * de la transmisión de video, el cambio dinámico de resolución y el control del LED flash.
 *
 * @author [Tu Nombre]
 * @date [Fecha]
 * @version 1.0
 */

#include "LibreriaCamera.h"
#include "esp_timer.h"
#include "img_converters.h"
#include "fb_gfx.h"
#include "soc/soc.h"           ///< Deshabilita problemas de brownout.
#include "soc/rtc_cntl_reg.h"  ///< Deshabilita problemas de brownout.
#include "esp_http_server.h"

#define PART_BOUNDARY "123456789000000000000987654321"
#define LED_PIN 4 ///< Pin donde está conectado el LED del ESP32-CAM.

static const char* _STREAM_CONTENT_TYPE = "multipart/x-mixed-replace;boundary=" PART_BOUNDARY;
static const char* _STREAM_BOUNDARY = "\r\n--" PART_BOUNDARY "\r\n";
static const char* _STREAM_PART = "Content-Type: image/jpeg\r\nContent-Length: %u\r\n\r\n";

static bool led_state = false; ///< Estado actual del LED (encendido/apagado).

// Resoluciones y calidades de imagen
const int videoFramesizeUXGA = 10;
const int videoFramesizeSVGA = 7;
const int videoQualityLow = 12;
const int videoQualityHigh = 10;
int framesize = videoFramesizeSVGA;

httpd_handle_t stream_httpd = NULL; ///< Manejador del servidor HTTP.

camera_config_t config; ///< Estructura de configuración de la cámara.

/**
 * @brief Configura e inicializa la cámara conectada al ESP32-CAM.
 * 
 * Inicializa los parámetros de la cámara como la resolución, calidad de imagen
 * y configuración de los pines. También maneja errores de inicialización.
 */
void cameraSetup() {
    pinMode(LED_PIN, OUTPUT);
    WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0); // Deshabilita el detector de brownout.

    // Configuración de los pines de la cámara
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

    // Inicializa la cámara
    esp_err_t err = esp_camera_init(&config);
    if (err != ESP_OK) {
        return;
    }

    cameraExecute();
}

/**
 * @brief Maneja la transmisión de video en tiempo real por HTTP.
 * 
 * Captura y envía imágenes en formato JPEG de forma continua.
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
 * @brief Inicia el servidor HTTP para la transmisión de video.
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
 * @brief Cambia la resolución de la cámara en tiempo de ejecución.
 */
void changeResolution() {
    framesize = (framesize == videoFramesizeSVGA) ? videoFramesizeUXGA : videoFramesizeSVGA;
    config.frame_size = (framesize_t)framesize;
    esp_camera_init(&config);
}

/**
 * @brief Controla el encendido y apagado del LED flash del ESP32-CAM.
 */
void led() {
    led_state = !led_state;
    digitalWrite(LED_PIN, led_state ? HIGH : LOW);
}
