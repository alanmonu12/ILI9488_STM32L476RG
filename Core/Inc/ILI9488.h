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
#include "ILI9488_conf.h"
/* USER CODE END Includes */

/* USER CODE BEGIN Private defines */
/**
 * @brief Command address 
 * 
 */
#define NOP_CMD         0x00
#define SOFT_RESET_CMD    0x01
#define SLEEP_IN_CMD  0x10
#define SLEEP_OUT_CMD  0x11
#define NORMAL_DISPLAY_MODE_ON_CMD  0x13
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

#if (ILI9488_LANDSCAPE)
#define ILI9488_HOR_RES     480
#define ILI9488_VER_RES     320
#endif

#if (ILI9488_PORTRAIT)
#define ILI9488_HOR_RES     320
#define ILI9488_VER_RES     480
#endif

#if defined(ILI9488_DBI_8BITS_INTERFACE)
#endif


#define SLEEP_OUT       false
#define SLEEP_IN        true
/**
 * @brief Color for clear the GRAM
 * 
 */
#define BLACK   0x00
#define WHITE   0xFF

/**
 * @brief 
 * 
 */
#if (ILI9488_SPI_INTERFACE == 1)
#define MAX6675_SPI hspi3
#endif

/**
 * @brief 
 * 
 */
#if (ILI9488_DBI_INTERFACE == 1)
#define ILI9488_GPIO_PORT GPIOC
#endif

#define ILI9488_enable_driver()         LL_GPIO_ResetOutputPin(ILI9488_CS_GPIO_Port, ILI9488_CS_Pin)
#define ILI9488_disable_driver()        LL_GPIO_SetOutputPin(ILI9488_CS_GPIO_Port, ILI9488_CS_Pin)
#define ILI9488_command_mode()          LL_GPIO_ResetOutputPin(ILI9488_RS_GPIO_Port, ILI9488_RS_Pin)
#define ILI9488_data_mode()             LL_GPIO_SetOutputPin(ILI9488_RS_GPIO_Port, ILI9488_RS_Pin)
#define ILI9488_write_cmd(cmd)          LL_GPIO_ResetOutputPin(ILI9488_WR_GPIO_Port, ILI9488_WR_Pin); LL_GPIO_WriteOutputPort(GPIOC, (uint32_t)cmd); LL_GPIO_SetOutputPin(ILI9488_WR_GPIO_Port, ILI9488_WR_Pin);
#define ILI9488_write_data(data)        LL_GPIO_ResetOutputPin(ILI9488_WR_GPIO_Port, ILI9488_WR_Pin); LL_GPIO_WriteOutputPort(GPIOC, (uint32_t)data); LL_GPIO_SetOutputPin(ILI9488_WR_GPIO_Port, ILI9488_WR_Pin);

/* USER CODE END Private defines */

typedef struct ILI9488_ID_Typedef ILI9488_ID_Typedef;

struct ILI9488_ID_Typedef{

    uint8_t ID1;
    uint8_t ID2;
    uint8_t ID3;
};

typedef struct ILI9488_status_Typedef ILI9488_status_Typedef;

struct ILI9488_status_Typedef{

    uint8_t Gamma_curve_selection;
    uint8_t Interface_color_pixel_format;
    bool Booster_voltage_status;
    bool Row_address_order;
    bool Column_address_order;
    bool Row_Column_exchange;
    bool Vertical_refresh;
    bool RGB_BGR_order;
    bool Horizontal_refresh;
    bool Idle_mode_status;
    bool Partial_mode_status;
    bool sleep_mode_status;
    bool Normal_mode_status;
    bool Vertical_scrolling_status;
    bool Display_status;
    bool Tearing_effect_status;
    bool Tearing_effect_line_mode;
};

typedef struct ILI9488_column_address_Typedef ILI9488_column_address_Typedef;

struct ILI9488_column_address_Typedef {
    uint16_t SC;
    uint16_t EC;
};

typedef struct ILI9488_page_address_Typedef ILI9488_page_address_Typedef;

struct ILI9488_page_address_Typedef {
    uint16_t SP;
    uint16_t EP;
};

typedef struct ILI9488_Typedef ILI9488_Typedef;

struct ILI9488_Typedef{

    ILI9488_ID_Typedef ID;
    ILI9488_status_Typedef status;
    ILI9488_column_address_Typedef Column_address;
    ILI9488_page_address_Typedef Page_address;

    bool Display_inversion_status;

    void (*init)(ILI9488_Typedef* const driver);
	//uint16_t (*MAX6675_getValue)(MAX6675_Typedef* const sensor);
	//float (*MAX6675_getTemp)(MAX6675_Typedef* const sensor);
	//bool (*MAX6675_getState)(MAX6675_Typedef* const sensor);
};

/* USER CODE BEGIN Prototypes */

/**
 * @brief 
 * 
 * @return ILI9488_Typedef* 
 */
ILI9488_Typedef* ILI9488_Create(void);

/**
 * @brief 
 * 
 * @param driver 
 */
void ILI9488_Init(ILI9488_Typedef* const driver);

void ILI9488_hardware_reset();
void ILI9488_normal_display_mode_on();
void ILI9488_all_pixels_off();
void ILI9488_display_on();
void ILI9488_sleep_out();
void ILI9488_display_inversion_on();
void ILI9488_WR_commnad(uint8_t command);
uint8_t ILI9488_READ_commnad(uint8_t command);
void ILI9488_WRITE_GRAM(uint8_t byte);

void ILI9488_CONTROL_DISPLAY(uint8_t BCTRL, uint8_t DD, uint8_t BL);
void ILI9488_Clear(uint8_t Color);
void ILI9488_MEMORY_ACCESS_CONTROL(bool MY, bool MX, bool MV, bool ML, bool BGR, bool MH);
void ILI9488_interface_pixel_format(uint8_t dpi, uint8_t dbi);

void ILI9488_init(void);
void ILI9488_draw_pixel(uint16_t x, uint16_t y, uint8_t R_color, uint8_t G_color, uint8_t B_color);

void ILI9488_column_addr_set(uint16_t SC, uint16_t EC);
void ILI9488_page_addr_set(uint16_t SP, uint16_t EP);
/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif
#endif /*__ GPIO_H__ */

