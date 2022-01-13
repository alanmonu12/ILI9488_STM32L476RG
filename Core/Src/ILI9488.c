#include "ILI9488.h"

#define _enable_driver()                 LL_GPIO_ResetOutputPin(ILI9488_CS_GPIO_Port, ILI9488_CS_Pin)
#define _disable_driver()                LL_GPIO_SetOutputPin(ILI9488_CS_GPIO_Port, ILI9488_CS_Pin)
#define _command_mode()                  LL_GPIO_ResetOutputPin(ILI9488_RS_GPIO_Port, ILI9488_RS_Pin)
#define _data_mode()                     LL_GPIO_SetOutputPin(ILI9488_RS_GPIO_Port, ILI9488_RS_Pin)
#define _write_cmd(cmd)                  LL_GPIO_ResetOutputPin(ILI9488_WR_GPIO_Port, ILI9488_WR_Pin); \
                                                LL_GPIO_WriteOutputPort(ILI9488_GPIO_PORT, (uint32_t)cmd); \
                                                LL_GPIO_SetOutputPin(ILI9488_WR_GPIO_Port, ILI9488_WR_Pin);
#define _write_8bits_data(data)                LL_GPIO_ResetOutputPin(ILI9488_WR_GPIO_Port, ILI9488_WR_Pin); \
                                                LL_GPIO_WriteOutputPort(ILI9488_GPIO_PORT, (uint32_t)data); \
                                                LL_GPIO_SetOutputPin(ILI9488_WR_GPIO_Port, ILI9488_WR_Pin);
#define _write_16bits_data(data)         LL_GPIO_ResetOutputPin(ILI9488_WR_GPIO_Port, ILI9488_WR_Pin); \
                                                LL_GPIO_WriteOutputPort(ILI9488_GPIO_PORT, (uint32_t)((data) >> 8)); \
                                                LL_GPIO_SetOutputPin(ILI9488_WR_GPIO_Port, ILI9488_WR_Pin); \
                                                LL_GPIO_ResetOutputPin(ILI9488_WR_GPIO_Port, ILI9488_WR_Pin); \
                                                LL_GPIO_WriteOutputPort(ILI9488_GPIO_PORT, (uint32_t)(data)); \
                                                LL_GPIO_SetOutputPin(ILI9488_WR_GPIO_Port, ILI9488_WR_Pin);

/**
 * @brief 
 * 
 * @param driver 
 */
static void init(ILI9488_Typedef* driver);

/**
 * @brief 
 * 
 * @param command 
 */
static void write_cmd(uint8_t command);

/**
 * @brief 
 * 
 * @param buffer 
 * @param buffer_size 
 */
static void write_gram_buffer(uint16_t* buffer, size_t buffer_size);

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
static void write_cmd(uint8_t command) {
  
  _enable_driver();

  _command_mode();

  _write_cmd(command);

  _disable_driver();
  
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

  _enable_driver();

  _command_mode();

  _write_cmd(MEMORY_WRITE_CMD);

}

void ILI9488_column_addr_set(uint16_t SC, uint16_t EC){
  
  
  _enable_driver();

  _command_mode();

  _write_cmd(COLUMN_ADDR_SET_CMD);

  _data_mode();

  _write_16bits_data(SC); 
  _write_16bits_data(EC); 

  _disable_driver();

}

void ILI9488_page_addr_set(uint16_t SP, uint16_t EP){

  _enable_driver();

  _command_mode();

  _write_cmd(PAGE_ADDR_SET_CMD);

  _data_mode();

  _write_16bits_data(SP); 
  _write_16bits_data(EP); 

  _disable_driver();

}

void ILI9488_CONTROL_DISPLAY(uint8_t BCTRL, uint8_t DD, uint8_t BL){

  _enable_driver();

  _command_mode();

  _write_cmd(WRITE_CTRL_DISPLAY_VALUE);

  _data_mode();

  _write_8bits_data((0x00 | (BL << 2) | (DD << 3) | (BCTRL << 5))); 

  _disable_driver();

}

void ILI9488_Clear(uint8_t Color) {
  
  _enable_driver();

  _data_mode();

  for (int i = 0; i < ((320 * 480)*4); i++) {
    _write_8bits_data(Color); 
  }
  
  _disable_driver();

}

void ILI9488_MEMORY_ACCESS_CONTROL(bool MY, bool MX, bool MV, bool ML, bool BGR, bool MH){

  _enable_driver();

  _command_mode();

  _write_cmd(MEMORY_ACCESS_CONTROL_CMD);

  _data_mode();

  _write_8bits_data((0x00 | (MH << 2) | (BGR << 3) | (ML << 4) | (MV << 5) | (MX << 6) | (MY << 7))); 

  _disable_driver();

}

/**
 * @brief 
 * 
 * @param dpi 
 * @param dbi 
 */
void ILI9488_interface_pixel_format(uint8_t dpi, uint8_t dbi) {

  _enable_driver();

  _command_mode();

  _write_cmd(INTERFACE_PIXEL_FORMAT_CMD);

  _data_mode();

  _write_8bits_data((dbi | (dpi << 4))); 

  _disable_driver();

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
static void ILI9488_draw_pixel(uint16_t x, uint16_t y, uint8_t R_color, uint8_t G_color, uint8_t B_color) {

  #if (ILI9488_LANDSCAPE)
  ILI9488_column_addr_set(x, 0x01E0);
  ILI9488_page_addr_set(y, 0X0140);
  #endif
  #if (ILI9488_PORTRAIT)
  ILI9488_column_addr_set(y, 0x01E0);
  ILI9488_page_addr_set(x, 0X0140);
  #endif



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

  write_cmd(NOP_CMD);

}

void ILI9488_init(void){
  ILI9488_hardware_reset();
  ILI9488_WR_commnad(0x11);
  ILI9488_MEMORY_ACCESS_CONTROL(true, true, true, false, false, false);
  ILI9488_interface_pixel_format(0x05, 0x05);
  ILI9488_WRITE_GRAM(0x00);
  ILI9488_Clear(WHITE);

  ILI9488_WR_commnad(NOP_CMD);
  ILI9488_WR_commnad(DISPLAY_ON_CMD);
}

/**
 * @brief 
 * 
 * @return ILI9488_Typedef* 
 */
ILI9488_Typedef* ILI9488_Create(void) {

  ILI9488_Typedef* const driver = (ILI9488_Typedef*)malloc(sizeof(ILI9488_Typedef));
	if (driver != NULL)
		ILI9488_Init(driver);

	return driver;
}

/**
 * @brief 
 * 
 * @param driver 
 */
void ILI9488_Init(ILI9488_Typedef* const driver) {
    driver->Page_address.SP = 0x0000;
    driver->Page_address.EP = ILI9488_VER_RES;
    driver->Column_address.SC = 0x0000;
    driver->Column_address.EC = ILI9488_HOR_RES;
    driver->ID.ID1 = 0x00;
    driver->ID.ID2 = 0x00;
    driver->ID.ID3 = 0x00;

    driver->Display_inversion_status = false;
    
    driver->status.Gamma_curve_selection = 0x00;
    driver->status.Interface_color_pixel_format = 0x00;
    driver->status.Booster_voltage_status = false;
    driver->status.Row_address_order = false;
    driver->status.Column_address_order = false;
    driver->status.Row_Column_exchange = false;
    driver->status.Vertical_refresh = false;
    driver->status.RGB_BGR_order = false;
    driver->status.Horizontal_refresh = false;
    driver->status.Idle_mode_status = false;
    driver->status.Partial_mode_status = false;
    driver->status.sleep_mode_status = false;
    driver->status.Normal_mode_status = false;
    driver->status.Vertical_scrolling_status = false;
    driver->status.Display_status = false;
    driver->status.Tearing_effect_status = false;
    driver->status.Tearing_effect_line_mode = false;

    driver->init = init;
    driver->draw_pixel = ILI9488_draw_pixel;
    driver->draw_buffer = write_gram_buffer;
}

static void init(ILI9488_Typedef* driver){
  // Reset by hardware
  ILI9488_hardware_reset();

  //Send command to get out the driver from sleep mode
  write_cmd(SLEEP_OUT_CMD);
  driver->status.sleep_mode_status = SLEEP_OUT;

  // Set column and page address
  ILI9488_column_addr_set(driver->Column_address.SC, driver->Column_address.EC);
  ILI9488_page_addr_set(driver->Page_address.SP, driver->Page_address.EP);

  #if (ILI9488_LANDSCAPE)
  ILI9488_MEMORY_ACCESS_CONTROL(true, true, true, false, true, false);
  #endif
  #if (ILI9488_PORTRAIT)
  ILI9488_MEMORY_ACCESS_CONTROL(false, true, false, false, true, false);
  #endif
  ILI9488_interface_pixel_format(0x05, 0x05);
  ILI9488_WRITE_GRAM(0x00);
  ILI9488_Clear(BLACK);

  write_cmd(NOP_CMD);
  write_cmd(DISPLAY_ON_CMD);
}

static void write_gram_buffer(uint16_t* buffer, size_t buffer_size) {

  ILI9488_WRITE_GRAM(0x00);

    // RS in low state to enable command mode
  LL_GPIO_SetOutputPin(ILI9488_RS_GPIO_Port, ILI9488_RS_Pin);

  // CS select low to enable the driver
  LL_GPIO_ResetOutputPin(ILI9488_CS_GPIO_Port, ILI9488_CS_Pin);

  for (size_t i = 0; i < buffer_size; i++)
  {

    /*Set parallel data*/
    LL_GPIO_WriteOutputPort(GPIOC, (uint32_t)(((buffer[i] >> 8) & 0x00F8 ) | ((buffer[i] >> 8 ) & 0x0007)));

    // WR Low to prepare the command
    LL_GPIO_ResetOutputPin(ILI9488_WR_GPIO_Port, ILI9488_WR_Pin);

    // WR to high, driver get the data from the parallel port
    LL_GPIO_SetOutputPin(ILI9488_WR_GPIO_Port, ILI9488_WR_Pin);

    /*Set parallel data*/
    LL_GPIO_WriteOutputPort(GPIOC, (uint32_t)((buffer[i] & 0x00E0) | (buffer[i] & 0x001F)));

    // WR Low to prepare the command
    LL_GPIO_ResetOutputPin(ILI9488_WR_GPIO_Port, ILI9488_WR_Pin);

    // WR to high, driver get the data from the parallel port
    LL_GPIO_SetOutputPin(ILI9488_WR_GPIO_Port, ILI9488_WR_Pin);

  }

  //High state CS disable driver
  LL_GPIO_SetOutputPin(ILI9488_CS_GPIO_Port, ILI9488_CS_Pin);

  write_cmd(NOP_CMD);
}
