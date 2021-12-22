/**
 * @file ILI9488.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-12-13
 * 
 * @copyright Copyright (c) 2021
 * 
 */
/* USER CODE END Header */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __ILI9488_H__
#define __ILI9488_H__

#ifdef __cplusplus
extern "C" {
#endif

/* USER CODE BEGIN Includes */
#include "gpio.h"
#include "stdbool.h"
/* USER CODE END Includes */

/* USER CODE BEGIN Private defines */
#define NOP_CMD         0x00
#define SOFT_RESET_CMD    0x01
#define NORMAL_DISPLAY_MODE_ON_CMD  0x13
#define SLEEP_IN_CMD  0x10
#define READ_DISPLAY_ID_INFO    0x04
#define READ_ID3_INFO    0xDB
#define DISPLAY_ON_CMD    0x29
#define DISPLAY_OFF_CMD    0x28
#define ALL_PIXELS_OFF_CMD  0x22
#define ALL_PIXELS_ON_CMD  0x23
#define MEMORY_WRITE_CMD  0x2C
#define COLUMN_ADDR_SET_CMD   0x2A
#define PAGE_ADDR_SET_CMD   0x2B
#define WRITE_CTRL_DISPLAY_VALUE    0x53
#define MEMORY_ACCESS_CONTROL_CMD   0x36
#define INTERFACE_PIXEL_FORMAT_CMD  0x3A

#define ILI9488_HOR_RES     320
#define ILI9488_VER_RES     480

#define BLACK   0x00
#define WHITE   0xFF
/* USER CODE END Private defines */

/* USER CODE BEGIN Prototypes */
void ILI9488_hardware_reset();
void ILI9488_normal_display_mode_on();
void ILI9488_all_pixels_off();
void ILI9488_display_on();
void ILI9488_sleep_out();
void ILI9488_display_inversion_on();
void ILI9488_WR_commnad(uint8_t command);
uint8_t ILI9488_READ_commnad(uint8_t command);
void ILI9488_WRITE_GRAM(uint8_t byte);
void ILI9488_COLUMN_ADDR_SET(uint8_t SC_1, uint8_t SC_2, uint8_t EC_1, uint8_t EC_2);
void ILI9488_PAGE_ADDR_SET(uint8_t SP_1, uint8_t SP_2, uint8_t EP_1, uint8_t EP_2);
void ILI9488_CONTROL_DISPLAY(uint8_t BCTRL, uint8_t DD, uint8_t BL);
void ILI9488_Clear(uint8_t Color);
void ILI9488_MEMORY_ACCESS_CONTROL(bool MY, bool MX, bool MV, bool ML, bool BGR, bool MH);
void ILI9488_interface_pixel_format(uint8_t dpi, uint8_t dbi);


void ILI9488_draw_pixel(uint16_t x, uint16_t y, uint8_t R_color, uint8_t G_color, uint8_t B_color);
void ILI9488_init(void);
/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif
#endif /*__ GPIO_H__ */

