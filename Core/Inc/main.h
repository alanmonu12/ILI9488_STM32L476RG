/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l4xx_hal.h"

#include "stm32l4xx_ll_system.h"
#include "stm32l4xx_ll_gpio.h"
#include "stm32l4xx_ll_exti.h"
#include "stm32l4xx_ll_bus.h"
#include "stm32l4xx_ll_cortex.h"
#include "stm32l4xx_ll_rcc.h"
#include "stm32l4xx_ll_utils.h"
#include "stm32l4xx_ll_pwr.h"
#include "stm32l4xx_ll_dma.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define B1_Pin LL_GPIO_PIN_13
#define B1_GPIO_Port GPIOC
#define ILI9488_D0_Pin LL_GPIO_PIN_0
#define ILI9488_D0_GPIO_Port GPIOC
#define ILI9488_D1_Pin LL_GPIO_PIN_1
#define ILI9488_D1_GPIO_Port GPIOC
#define ILI9488_D2_Pin LL_GPIO_PIN_2
#define ILI9488_D2_GPIO_Port GPIOC
#define ILI9488_D3_Pin LL_GPIO_PIN_3
#define ILI9488_D3_GPIO_Port GPIOC
#define ILI9488_RS_Pin LL_GPIO_PIN_0
#define ILI9488_RS_GPIO_Port GPIOA
#define ILI9488_RD_Pin LL_GPIO_PIN_1
#define ILI9488_RD_GPIO_Port GPIOA
#define USART_TX_Pin LL_GPIO_PIN_2
#define USART_TX_GPIO_Port GPIOA
#define USART_RX_Pin LL_GPIO_PIN_3
#define USART_RX_GPIO_Port GPIOA
#define ILI9488_CS_Pin LL_GPIO_PIN_4
#define ILI9488_CS_GPIO_Port GPIOA
#define ILI9488_RST_Pin LL_GPIO_PIN_7
#define ILI9488_RST_GPIO_Port GPIOA
#define ILI9488_D4_Pin LL_GPIO_PIN_4
#define ILI9488_D4_GPIO_Port GPIOC
#define ILI9488_D5_Pin LL_GPIO_PIN_5
#define ILI9488_D5_GPIO_Port GPIOC
#define ILI9488_WR_Pin LL_GPIO_PIN_0
#define ILI9488_WR_GPIO_Port GPIOB
#define ILI9488_D6_Pin LL_GPIO_PIN_6
#define ILI9488_D6_GPIO_Port GPIOC
#define ILI9488_D7_Pin LL_GPIO_PIN_7
#define ILI9488_D7_GPIO_Port GPIOC
#define ILI9488_D6A9_Pin LL_GPIO_PIN_9
#define ILI9488_D6A9_GPIO_Port GPIOA
#define TMS_Pin LL_GPIO_PIN_13
#define TMS_GPIO_Port GPIOA
#define TCK_Pin LL_GPIO_PIN_14
#define TCK_GPIO_Port GPIOA
#define ILI9488_CRST_Pin LL_GPIO_PIN_8
#define ILI9488_CRST_GPIO_Port GPIOB
#define ILI9488_INT_Pin LL_GPIO_PIN_9
#define ILI9488_INT_GPIO_Port GPIOB
#define ILI9488_INT_EXTI_IRQn EXTI9_5_IRQn
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
