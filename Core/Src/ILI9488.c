#include "ILI9488.h"

/**
 * @brief 
 * 
 */
void ILI9488_hardware_reset() {
  LL_GPIO_ResetOutputPin(ILI9488_RST_GPIO_Port, ILI9488_RST_Pin);
  HAL_Delay(50);
  LL_GPIO_SetOutputPin(ILI9488_RST_GPIO_Port, ILI9488_RST_Pin);
  HAL_Delay(1000);
}

/**
 * @brief 
 * 
 * @param command 
 */
void ILI9488_WR_commnad(uint8_t command) {
  
  // CS select low to enable the driver
  LL_GPIO_ResetOutputPin(ILI9488_CS_GPIO_Port, ILI9488_CS_Pin);
  
  // RS in low state to enable command mode
  LL_GPIO_ResetOutputPin(ILI9488_RS_GPIO_Port, ILI9488_RS_Pin);
  
  // WR Low to prepare the command
  LL_GPIO_ResetOutputPin(ILI9488_WR_GPIO_Port, ILI9488_WR_Pin);
    

  /*Set parallel data*/
  LL_GPIO_WriteOutputPort(GPIOC, (uint32_t)command);

  // WR to high, driver get the data from the parallel port
  LL_GPIO_SetOutputPin(ILI9488_WR_GPIO_Port, ILI9488_WR_Pin);

  // High state for RS
  LL_GPIO_SetOutputPin(ILI9488_RS_GPIO_Port, ILI9488_RS_Pin);

  //High state CS disable driver
  LL_GPIO_SetOutputPin(ILI9488_CS_GPIO_Port, ILI9488_CS_Pin);
  
}

uint8_t ILI9488_READ_commnad(uint8_t command) {

  uint8_t read_data1 = 0;
  
  // CS select low to enable the driver
  LL_GPIO_ResetOutputPin(ILI9488_CS_GPIO_Port, ILI9488_CS_Pin);
  HAL_Delay(10);
  // RS in low state to enable command mode
  LL_GPIO_ResetOutputPin(ILI9488_RS_GPIO_Port, ILI9488_RS_Pin);
  HAL_Delay(10);
  // WR Low to prepare the command
  LL_GPIO_ResetOutputPin(ILI9488_WR_GPIO_Port, ILI9488_WR_Pin);
  HAL_Delay(10);  

  /*Set parallel data*/
  LL_GPIO_WriteOutputPort(GPIOC, (uint32_t)command);

  // WR to high, driver get the data from the parallel port
  LL_GPIO_SetOutputPin(ILI9488_WR_GPIO_Port, ILI9488_WR_Pin);
  HAL_Delay(10);

  // High state for RS
  LL_GPIO_SetOutputPin(ILI9488_RS_GPIO_Port, ILI9488_RS_Pin);
  HAL_Delay(10);

  // Change the parallel pins to inputs
  LL_GPIO_SetPinMode(ILI9488_D0_GPIO_Port, ILI9488_D0_Pin, LL_GPIO_MODE_INPUT);
  LL_GPIO_SetPinMode(ILI9488_D1_GPIO_Port, ILI9488_D1_Pin, LL_GPIO_MODE_INPUT);
  LL_GPIO_SetPinMode(ILI9488_D2_GPIO_Port, ILI9488_D2_Pin, LL_GPIO_MODE_INPUT);
  LL_GPIO_SetPinMode(ILI9488_D3_GPIO_Port, ILI9488_D3_Pin, LL_GPIO_MODE_INPUT);
  LL_GPIO_SetPinMode(ILI9488_D4_GPIO_Port, ILI9488_D4_Pin, LL_GPIO_MODE_INPUT);
  LL_GPIO_SetPinMode(ILI9488_D5_GPIO_Port, ILI9488_D5_Pin, LL_GPIO_MODE_INPUT);
  LL_GPIO_SetPinMode(ILI9488_D6_GPIO_Port, ILI9488_D6_Pin, LL_GPIO_MODE_INPUT);
  LL_GPIO_SetPinMode(ILI9488_D7_GPIO_Port, ILI9488_D7_Pin, LL_GPIO_MODE_INPUT);

  // Read signal for dummy
  LL_GPIO_ResetOutputPin(ILI9488_RD_GPIO_Port, ILI9488_RD_Pin);
  HAL_Delay(10);  
  LL_GPIO_SetOutputPin(ILI9488_RD_GPIO_Port, ILI9488_RD_Pin);
  HAL_Delay(10);

  LL_GPIO_ResetOutputPin(ILI9488_RD_GPIO_Port, ILI9488_RD_Pin);
  HAL_Delay(10);  
  LL_GPIO_SetOutputPin(ILI9488_RD_GPIO_Port, ILI9488_RD_Pin);
  HAL_Delay(10);
  //Read data
  read_data1 = (LL_GPIO_IsInputPinSet(ILI9488_D0_GPIO_Port,ILI9488_D0_Pin) << 0) | (LL_GPIO_IsInputPinSet(ILI9488_D1_GPIO_Port,ILI9488_D1_Pin) << 1) |
  (LL_GPIO_IsInputPinSet(ILI9488_D2_GPIO_Port,ILI9488_D2_Pin) << 2) |
  (LL_GPIO_IsInputPinSet(ILI9488_D3_GPIO_Port,ILI9488_D3_Pin) << 3) |
  (LL_GPIO_IsInputPinSet(ILI9488_D4_GPIO_Port,ILI9488_D4_Pin) << 4) |
  (LL_GPIO_IsInputPinSet(ILI9488_D5_GPIO_Port,ILI9488_D5_Pin) << 5) |
  (LL_GPIO_IsInputPinSet(ILI9488_D6_GPIO_Port,ILI9488_D6_Pin) << 6) |
  (LL_GPIO_IsInputPinSet(ILI9488_D7_GPIO_Port,ILI9488_D7_Pin) << 7);

  //High state CS disable driver
  LL_GPIO_SetOutputPin(ILI9488_CS_GPIO_Port, ILI9488_CS_Pin);
  HAL_Delay(10);

  LL_GPIO_SetPinMode(ILI9488_D0_GPIO_Port, ILI9488_D0_Pin, LL_GPIO_MODE_OUTPUT);
  LL_GPIO_SetPinMode(ILI9488_D1_GPIO_Port, ILI9488_D1_Pin, LL_GPIO_MODE_OUTPUT);
  LL_GPIO_SetPinMode(ILI9488_D2_GPIO_Port, ILI9488_D2_Pin, LL_GPIO_MODE_OUTPUT);
  LL_GPIO_SetPinMode(ILI9488_D3_GPIO_Port, ILI9488_D3_Pin, LL_GPIO_MODE_OUTPUT);
  LL_GPIO_SetPinMode(ILI9488_D4_GPIO_Port, ILI9488_D4_Pin, LL_GPIO_MODE_OUTPUT);
  LL_GPIO_SetPinMode(ILI9488_D5_GPIO_Port, ILI9488_D5_Pin, LL_GPIO_MODE_OUTPUT);
  LL_GPIO_SetPinMode(ILI9488_D6_GPIO_Port, ILI9488_D6_Pin, LL_GPIO_MODE_OUTPUT);
  LL_GPIO_SetPinMode(ILI9488_D7_GPIO_Port, ILI9488_D7_Pin, LL_GPIO_MODE_OUTPUT);

  return read_data1;
}

void ILI9488_WRITE_GRAM(uint8_t byte) {

    // CS select low to enable the driver
  LL_GPIO_ResetOutputPin(ILI9488_CS_GPIO_Port, ILI9488_CS_Pin);

  // RS in low state to enable command mode
  LL_GPIO_ResetOutputPin(ILI9488_RS_GPIO_Port, ILI9488_RS_Pin);
  
  // WR Low to prepare the command
  LL_GPIO_ResetOutputPin(ILI9488_WR_GPIO_Port, ILI9488_WR_Pin);

  /*Set parallel data*/
  LL_GPIO_WriteOutputPort(GPIOC, (uint32_t)MEMORY_WRITE_CMD);

  // WR to high, driver get the data from the parallel port
  LL_GPIO_SetOutputPin(ILI9488_WR_GPIO_Port, ILI9488_WR_Pin);

  // High state for RS
  LL_GPIO_SetOutputPin(ILI9488_RS_GPIO_Port, ILI9488_RS_Pin);

  //High state CS disable driver
  //LL_GPIO_SetOutputPin(ILI9488_CS_GPIO_Port, ILI9488_CS_Pin);
  //HAL_Delay(10);

}

void ILI9488_COLUMN_ADDR_SET(uint8_t SC_1, uint8_t SC_2, uint8_t EC_1, uint8_t EC_2){
      // CS select low to enable the driver
  LL_GPIO_ResetOutputPin(ILI9488_CS_GPIO_Port, ILI9488_CS_Pin);
  //HAL_Delay(10);
  // RS in low state to enable command mode
  LL_GPIO_ResetOutputPin(ILI9488_RS_GPIO_Port, ILI9488_RS_Pin);
  //HAL_Delay(10);
  // WR Low to prepare the command
  LL_GPIO_ResetOutputPin(ILI9488_WR_GPIO_Port, ILI9488_WR_Pin);
  //HAL_Delay(10);  

  /*Set parallel data*/
  LL_GPIO_WriteOutputPort(GPIOC, (uint32_t)COLUMN_ADDR_SET_CMD);

  // WR to high, driver get the data from the parallel port
  LL_GPIO_SetOutputPin(ILI9488_WR_GPIO_Port, ILI9488_WR_Pin);
  //HAL_Delay(10);

  // High state for RS
  LL_GPIO_SetOutputPin(ILI9488_RS_GPIO_Port, ILI9488_RS_Pin);
  //HAL_Delay(10);

  // WR Low to prepare the command
  LL_GPIO_ResetOutputPin(ILI9488_WR_GPIO_Port, ILI9488_WR_Pin);
  //HAL_Delay(10);  

  /*Set parallel data*/
  LL_GPIO_WriteOutputPort(GPIOC, (uint32_t)SC_1);

  // WR to high, driver get the data from the parallel port
  LL_GPIO_SetOutputPin(ILI9488_WR_GPIO_Port, ILI9488_WR_Pin);
  //HAL_Delay(10);

    // WR Low to prepare the command
  LL_GPIO_ResetOutputPin(ILI9488_WR_GPIO_Port, ILI9488_WR_Pin);
  //HAL_Delay(10);  

  /*Set parallel data*/
    LL_GPIO_WriteOutputPort(GPIOC, (uint32_t)SC_2);

  // WR to high, driver get the data from the parallel port
  LL_GPIO_SetOutputPin(ILI9488_WR_GPIO_Port, ILI9488_WR_Pin);
  //HAL_Delay(10);

      // WR Low to prepare the command
  LL_GPIO_ResetOutputPin(ILI9488_WR_GPIO_Port, ILI9488_WR_Pin);
  //HAL_Delay(10);  

  /*Set parallel data*/
  LL_GPIO_WriteOutputPort(GPIOC, (uint32_t)EC_1);

  // WR to high, driver get the data from the parallel port
  LL_GPIO_SetOutputPin(ILI9488_WR_GPIO_Port, ILI9488_WR_Pin);
  //HAL_Delay(10);

      // WR Low to prepare the command
  LL_GPIO_ResetOutputPin(ILI9488_WR_GPIO_Port, ILI9488_WR_Pin);
  //HAL_Delay(10);  

  /*Set parallel data*/
  LL_GPIO_WriteOutputPort(GPIOC, (uint32_t)EC_2);

  // WR to high, driver get the data from the parallel port
  LL_GPIO_SetOutputPin(ILI9488_WR_GPIO_Port, ILI9488_WR_Pin);
  //HAL_Delay(10);

  //High state CS disable driver
  LL_GPIO_SetOutputPin(ILI9488_CS_GPIO_Port, ILI9488_CS_Pin);
  //HAL_Delay(10);
}

void ILI9488_PAGE_ADDR_SET(uint8_t SP_1, uint8_t SP_2, uint8_t EP_1, uint8_t EP_2){
      // CS select low to enable the driver
  LL_GPIO_ResetOutputPin(ILI9488_CS_GPIO_Port, ILI9488_CS_Pin);
  //HAL_Delay(10);
  // RS in low state to enable command mode
  LL_GPIO_ResetOutputPin(ILI9488_RS_GPIO_Port, ILI9488_RS_Pin);
  //HAL_Delay(10);
  // WR Low to prepare the command
  LL_GPIO_ResetOutputPin(ILI9488_WR_GPIO_Port, ILI9488_WR_Pin);
  //HAL_Delay(10);  

  /*Set parallel data*/
  LL_GPIO_WriteOutputPort(GPIOC, (uint32_t)PAGE_ADDR_SET_CMD);

  // WR to high, driver get the data from the parallel port
  LL_GPIO_SetOutputPin(ILI9488_WR_GPIO_Port, ILI9488_WR_Pin);
  //HAL_Delay(10);

  // High state for RS
  LL_GPIO_SetOutputPin(ILI9488_RS_GPIO_Port, ILI9488_RS_Pin);
  //HAL_Delay(10);

  // WR Low to prepare the command
  LL_GPIO_ResetOutputPin(ILI9488_WR_GPIO_Port, ILI9488_WR_Pin);
  //HAL_Delay(10);  

  /*Set parallel data*/
  LL_GPIO_WriteOutputPort(GPIOC, (uint32_t)SP_1);

  // WR to high, driver get the data from the parallel port
  LL_GPIO_SetOutputPin(ILI9488_WR_GPIO_Port, ILI9488_WR_Pin);
  //HAL_Delay(10);

    // WR Low to prepare the command
  LL_GPIO_ResetOutputPin(ILI9488_WR_GPIO_Port, ILI9488_WR_Pin);
  //HAL_Delay(10);  

  /*Set parallel data*/
  LL_GPIO_WriteOutputPort(GPIOC, (uint32_t)SP_2);

  // WR to high, driver get the data from the parallel port
  LL_GPIO_SetOutputPin(ILI9488_WR_GPIO_Port, ILI9488_WR_Pin);
  //HAL_Delay(10);

      // WR Low to prepare the command
  LL_GPIO_ResetOutputPin(ILI9488_WR_GPIO_Port, ILI9488_WR_Pin);
  //HAL_Delay(10);  

  /*Set parallel data*/
  LL_GPIO_WriteOutputPort(GPIOC, (uint32_t)EP_1);

  // WR to high, driver get the data from the parallel port
  LL_GPIO_SetOutputPin(ILI9488_WR_GPIO_Port, ILI9488_WR_Pin);
  //HAL_Delay(10);

      // WR Low to prepare the command
  LL_GPIO_ResetOutputPin(ILI9488_WR_GPIO_Port, ILI9488_WR_Pin);
  //HAL_Delay(10);  

  /*Set parallel data*/
  LL_GPIO_WriteOutputPort(GPIOC, (uint32_t)EP_2);

  // WR to high, driver get the data from the parallel port
  LL_GPIO_SetOutputPin(ILI9488_WR_GPIO_Port, ILI9488_WR_Pin);
  //HAL_Delay(10);

  //High state CS disable driver
  LL_GPIO_SetOutputPin(ILI9488_CS_GPIO_Port, ILI9488_CS_Pin);
  //HAL_Delay(10);
}

void ILI9488_CONTROL_DISPLAY(uint8_t BCTRL, uint8_t DD, uint8_t BL){
      // CS select low to enable the driver
  LL_GPIO_ResetOutputPin(ILI9488_CS_GPIO_Port, ILI9488_CS_Pin);
  HAL_Delay(10);
  // RS in low state to enable command mode
  LL_GPIO_ResetOutputPin(ILI9488_RS_GPIO_Port, ILI9488_RS_Pin);
  HAL_Delay(10);
  // WR Low to prepare the command
  LL_GPIO_ResetOutputPin(ILI9488_WR_GPIO_Port, ILI9488_WR_Pin);
  HAL_Delay(10);  

  /*Set parallel data*/
  LL_GPIO_WriteOutputPort(GPIOC, (uint32_t)WRITE_CTRL_DISPLAY_VALUE);

  // WR to high, driver get the data from the parallel port
  LL_GPIO_SetOutputPin(ILI9488_WR_GPIO_Port, ILI9488_WR_Pin);
  HAL_Delay(10);

  // High state for RS
  LL_GPIO_SetOutputPin(ILI9488_RS_GPIO_Port, ILI9488_RS_Pin);
  HAL_Delay(10);

  // WR Low to prepare the command
  LL_GPIO_ResetOutputPin(ILI9488_WR_GPIO_Port, ILI9488_WR_Pin);
  HAL_Delay(10);  

  /*Set parallel data*/
  LL_GPIO_WriteOutputPort(GPIOC, (uint32_t)(0x00 | (BL << 2) | (DD << 3) | (BCTRL << 5)));

  // WR to high, driver get the data from the parallel port
  LL_GPIO_SetOutputPin(ILI9488_WR_GPIO_Port, ILI9488_WR_Pin);
  HAL_Delay(10);

  //High state CS disable driver
  LL_GPIO_SetOutputPin(ILI9488_CS_GPIO_Port, ILI9488_CS_Pin);
  HAL_Delay(10);
}

void ILI9488_Clear(uint8_t Color) {
  
  // RS in low state to enable command mode
  LL_GPIO_SetOutputPin(ILI9488_RS_GPIO_Port, ILI9488_RS_Pin);

  // CS select low to enable the driver
  LL_GPIO_ResetOutputPin(ILI9488_CS_GPIO_Port, ILI9488_CS_Pin);

  /*Set parallel data*/
  LL_GPIO_WriteOutputPort(GPIOC, (uint32_t)Color);
  
  for (int i = 0; i < ((320 * 480)*2); i++) {
      // WR Low to prepare the command
    LL_GPIO_ResetOutputPin(ILI9488_WR_GPIO_Port, ILI9488_WR_Pin);

    // WR to high, driver get the data from the parallel port
    LL_GPIO_SetOutputPin(ILI9488_WR_GPIO_Port, ILI9488_WR_Pin);
  }

  //High state CS disable driver
  LL_GPIO_SetOutputPin(ILI9488_CS_GPIO_Port, ILI9488_CS_Pin);
}

void ILI9488_MEMORY_ACCESS_CONTROL(bool MY, bool MX, bool MV, bool ML, bool BGR, bool MH){
      // CS select low to enable the driver
  LL_GPIO_ResetOutputPin(ILI9488_CS_GPIO_Port, ILI9488_CS_Pin);
  HAL_Delay(10);
  // RS in low state to enable command mode
  LL_GPIO_ResetOutputPin(ILI9488_RS_GPIO_Port, ILI9488_RS_Pin);
  HAL_Delay(10);
  // WR Low to prepare the command
  LL_GPIO_ResetOutputPin(ILI9488_WR_GPIO_Port, ILI9488_WR_Pin);
  HAL_Delay(10);  

  /*Set parallel data*/
  LL_GPIO_WriteOutputPort(GPIOC, (uint32_t)MEMORY_ACCESS_CONTROL_CMD);

  // WR to high, driver get the data from the parallel port
  LL_GPIO_SetOutputPin(ILI9488_WR_GPIO_Port, ILI9488_WR_Pin);
  HAL_Delay(10);

  // High state for RS
  LL_GPIO_SetOutputPin(ILI9488_RS_GPIO_Port, ILI9488_RS_Pin);
  HAL_Delay(10);

        // WR Low to prepare the command
  LL_GPIO_ResetOutputPin(ILI9488_WR_GPIO_Port, ILI9488_WR_Pin);
  HAL_Delay(10);  

  /*Set parallel data*/
  LL_GPIO_WriteOutputPort(GPIOC, (uint32_t)(0x00 | (MH << 2) | (BGR << 3) | (ML << 4) | (MV << 5) | (MX << 6) | (MY << 7)));

  // WR to high, driver get the data from the parallel port
  LL_GPIO_SetOutputPin(ILI9488_WR_GPIO_Port, ILI9488_WR_Pin);
  HAL_Delay(10);

  //High state CS disable driver
  LL_GPIO_SetOutputPin(ILI9488_CS_GPIO_Port, ILI9488_CS_Pin);
  HAL_Delay(10);
}

/**
 * @brief 
 * 
 * @param dpi 
 * @param dbi 
 */
void ILI9488_interface_pixel_format(uint8_t dpi, uint8_t dbi) {
    // CS select low to enable the driver
  LL_GPIO_ResetOutputPin(ILI9488_CS_GPIO_Port, ILI9488_CS_Pin);
  //HAL_Delay(10);
  // RS in low state to enable command mode
  LL_GPIO_ResetOutputPin(ILI9488_RS_GPIO_Port, ILI9488_RS_Pin);
  //HAL_Delay(10);
  // WR Low to prepare the command
  LL_GPIO_ResetOutputPin(ILI9488_WR_GPIO_Port, ILI9488_WR_Pin);
  //HAL_Delay(10);  

  /*Set parallel data*/
  LL_GPIO_WriteOutputPort(GPIOC, (uint32_t)INTERFACE_PIXEL_FORMAT_CMD);

  // WR to high, driver get the data from the parallel port
  LL_GPIO_SetOutputPin(ILI9488_WR_GPIO_Port, ILI9488_WR_Pin);
  //HAL_Delay(10);

  // High state for RS
  LL_GPIO_SetOutputPin(ILI9488_RS_GPIO_Port, ILI9488_RS_Pin);

          // WR Low to prepare the command
  LL_GPIO_ResetOutputPin(ILI9488_WR_GPIO_Port, ILI9488_WR_Pin);
  //HAL_Delay(10);  

  /*Set parallel data*/
  LL_GPIO_WriteOutputPort(GPIOC, (uint32_t)(dbi | (dpi << 4)));

  // WR to high, driver get the data from the parallel port
  LL_GPIO_SetOutputPin(ILI9488_WR_GPIO_Port, ILI9488_WR_Pin);
  //HAL_Delay(10);

  //High state CS disable driver
  LL_GPIO_SetOutputPin(ILI9488_CS_GPIO_Port, ILI9488_CS_Pin);
  //HAL_Delay(10);

}

/**
 * @brief 
 * 
 * @param x 
 * @param y 
 * @param R_color 
 * @param G_color 
 * @param B_color
 * @todo Detect the pixel interface
 */
void ILI9488_draw_pixel(uint16_t x, uint16_t y, uint8_t R_color, uint8_t G_color, uint8_t B_color) {
  uint8_t x1,x2;
  uint8_t y1,y2;

  x1 = x & 0x00FF;
  x2 = x >> 8;

  y1 = y & 0x00FF;
  y2 = y >> 8;

  ILI9488_COLUMN_ADDR_SET(x2, x1, 0x01, 0xE0);
  ILI9488_PAGE_ADDR_SET(y2, y1, 0X01, 0X40);

  ILI9488_WRITE_GRAM(0x00);

  // RS in low state to enable command mode
  LL_GPIO_SetOutputPin(ILI9488_RS_GPIO_Port, ILI9488_RS_Pin);

  // CS select low to enable the driver
  LL_GPIO_ResetOutputPin(ILI9488_CS_GPIO_Port, ILI9488_CS_Pin);

  /*Set parallel data*/
  LL_GPIO_WriteOutputPort(GPIOC, (uint32_t)((B_color << 3) | ((G_color & 0x38) >> 3)));
  // (G_color & (1 << 3)) ? LL_GPIO_SetOutputPin(ILI9488_D0_GPIO_Port, ILI9488_D0_Pin) : LL_GPIO_ResetOutputPin(ILI9488_D0_GPIO_Port, ILI9488_D0_Pin);
  // (G_color & (1 << 4)) ? LL_GPIO_SetOutputPin(ILI9488_D1_GPIO_Port, ILI9488_D1_Pin) : LL_GPIO_ResetOutputPin(ILI9488_D1_GPIO_Port, ILI9488_D1_Pin);
  // (G_color & (1 << 5)) ? LL_GPIO_SetOutputPin(ILI9488_D2_GPIO_Port, ILI9488_D2_Pin) : LL_GPIO_ResetOutputPin(ILI9488_D2_GPIO_Port, ILI9488_D2_Pin);
  // (B_color & (1 << 0)) ? LL_GPIO_SetOutputPin(ILI9488_D3_GPIO_Port, ILI9488_D3_Pin) : LL_GPIO_ResetOutputPin(ILI9488_D3_GPIO_Port, ILI9488_D3_Pin);
  // (B_color & (1 << 1)) ? LL_GPIO_SetOutputPin(ILI9488_D4_GPIO_Port, ILI9488_D4_Pin) : LL_GPIO_ResetOutputPin(ILI9488_D4_GPIO_Port, ILI9488_D4_Pin);
  // (B_color & (1 << 2)) ? LL_GPIO_SetOutputPin(ILI9488_D5_GPIO_Port, ILI9488_D5_Pin) : LL_GPIO_ResetOutputPin(ILI9488_D5_GPIO_Port, ILI9488_D5_Pin);
  // (B_color & (1 << 3)) ? LL_GPIO_SetOutputPin(ILI9488_D6_GPIO_Port, ILI9488_D6_Pin) : LL_GPIO_ResetOutputPin(ILI9488_D6_GPIO_Port, ILI9488_D6_Pin);
  // (B_color & (1 << 4)) ? LL_GPIO_SetOutputPin(ILI9488_D7_GPIO_Port, ILI9488_D7_Pin) : LL_GPIO_ResetOutputPin(ILI9488_D7_GPIO_Port, ILI9488_D7_Pin);
  // WR Low to prepare the command
  LL_GPIO_ResetOutputPin(ILI9488_WR_GPIO_Port, ILI9488_WR_Pin);

  // WR to high, driver get the data from the parallel port
  LL_GPIO_SetOutputPin(ILI9488_WR_GPIO_Port, ILI9488_WR_Pin);

  /*Set parallel data*/
  LL_GPIO_WriteOutputPort(GPIOC, (uint32_t)((R_color & 0x1F) | ((G_color & 0x07) << 5)));
  // (R_color & (1 << 0)) ? LL_GPIO_SetOutputPin(ILI9488_D0_GPIO_Port, ILI9488_D0_Pin) : LL_GPIO_ResetOutputPin(ILI9488_D0_GPIO_Port, ILI9488_D0_Pin);
  // (R_color & (1 << 1)) ? LL_GPIO_SetOutputPin(ILI9488_D1_GPIO_Port, ILI9488_D1_Pin) : LL_GPIO_ResetOutputPin(ILI9488_D1_GPIO_Port, ILI9488_D1_Pin);
  // (R_color & (1 << 2)) ? LL_GPIO_SetOutputPin(ILI9488_D2_GPIO_Port, ILI9488_D2_Pin) : LL_GPIO_ResetOutputPin(ILI9488_D2_GPIO_Port, ILI9488_D2_Pin);
  // (R_color & (1 << 3)) ? LL_GPIO_SetOutputPin(ILI9488_D3_GPIO_Port, ILI9488_D3_Pin) : LL_GPIO_ResetOutputPin(ILI9488_D3_GPIO_Port, ILI9488_D3_Pin);
  // (R_color & (1 << 4)) ? LL_GPIO_SetOutputPin(ILI9488_D4_GPIO_Port, ILI9488_D4_Pin) : LL_GPIO_ResetOutputPin(ILI9488_D4_GPIO_Port, ILI9488_D4_Pin);
  // (G_color & (1 << 0)) ? LL_GPIO_SetOutputPin(ILI9488_D5_GPIO_Port, ILI9488_D5_Pin) : LL_GPIO_ResetOutputPin(ILI9488_D5_GPIO_Port, ILI9488_D5_Pin);
  // (G_color & (1 << 1)) ? LL_GPIO_SetOutputPin(ILI9488_D6_GPIO_Port, ILI9488_D6_Pin) : LL_GPIO_ResetOutputPin(ILI9488_D6_GPIO_Port, ILI9488_D6_Pin);
  // (G_color & (1 << 3)) ? LL_GPIO_SetOutputPin(ILI9488_D7_GPIO_Port, ILI9488_D7_Pin) : LL_GPIO_ResetOutputPin(ILI9488_D7_GPIO_Port, ILI9488_D7_Pin);
  // WR Low to prepare the command
  LL_GPIO_ResetOutputPin(ILI9488_WR_GPIO_Port, ILI9488_WR_Pin);

  // WR to high, driver get the data from the parallel port
  LL_GPIO_SetOutputPin(ILI9488_WR_GPIO_Port, ILI9488_WR_Pin);

  //High state CS disable driver
  LL_GPIO_SetOutputPin(ILI9488_CS_GPIO_Port, ILI9488_CS_Pin);

  ILI9488_WR_commnad(NOP_CMD);

}

void ILI9488_init(void){
  ILI9488_hardware_reset();
  ILI9488_WR_commnad(0x11);
  ILI9488_COLUMN_ADDR_SET(0x00, 0x00, 0x01, 0xE0);
  ILI9488_PAGE_ADDR_SET(0X00, 0X00, 0X01, 0X40);
  ILI9488_MEMORY_ACCESS_CONTROL(true, true, true, false, false, false);
  ILI9488_interface_pixel_format(0x05, 0x05);
  ILI9488_WRITE_GRAM(0x00);
  ILI9488_Clear(WHITE);

  ILI9488_WR_commnad(NOP_CMD);
  ILI9488_WR_commnad(DISPLAY_ON_CMD);
}
