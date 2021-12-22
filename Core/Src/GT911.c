/**
 * @file GT911.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-12-14
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "GT911.h"

static uint8_t command[2] = {0x80, 0x40};
static uint8_t command2[2] = {0x81, 0x4E};
static uint8_t command3[2] = {0x81, 0x46};
static uint8_t command4[2] = {0x81, 0x47};
static uint8_t command5[2] = {0x81, 0x48};
static uint8_t command6[2] = {0x81, 0x49};
static uint8_t command7[3] = {0x80, 0x40, 0x00};
static uint8_t buffer;
static uint8_t x_cor[2] = {0,0};
static uint8_t y_cor[2] = {0,0};

void GT911_init(){
      // Reset GT911
  HAL_NVIC_DisableIRQ(EXTI9_5_IRQn);
  LL_GPIO_ResetOutputPin(ILI9488_INT_GPIO_Port, ILI9488_INT_Pin);
  LL_GPIO_ResetOutputPin(ILI9488_CRST_GPIO_Port, ILI9488_CRST_Pin);
  HAL_Delay(1);
  LL_GPIO_SetOutputPin(ILI9488_CRST_GPIO_Port, ILI9488_CRST_Pin);
  HAL_Delay(10);
  LL_GPIO_SetOutputPin(ILI9488_INT_GPIO_Port, ILI9488_INT_Pin);

  HAL_I2C_Master_Transmit(&hi2c1, 0x28, command, 2, 1000);
  HAL_I2C_Master_Receive(&hi2c1, 0x29, &buffer, 1, 1000);

  HAL_I2C_Master_Transmit(&hi2c1, 0x29, command7, 3, 1000);
  //HAL_I2C_Master_Receive(&hi2c1, 0xBB, &buffer, 1, 1000);

  HAL_I2C_Master_Transmit(&hi2c1, 0x28, command, 2, 1000);
  HAL_I2C_Master_Receive(&hi2c1, 0x29, &buffer, 1, 1000);

  //HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);


  HAL_Delay(100);
  uint8_t cmd2[3] = {0x81, 0x4E, (buffer & 0x7E)};
  HAL_I2C_Master_Transmit(&hi2c1, 0x28, &cmd2, 3, 1000);
}
