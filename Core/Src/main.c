/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "dma.h"
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdbool.h"
#include "../lvgl/lvgl.h"
#include "demo_widgets.h"
#include "gui.h"
#include "ILI9488.h"
#include "GT911.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
static void hal_init(void);
void my_input_read(lv_indev_drv_t * drv, lv_indev_data_t*data);
void my_flush_cb(lv_disp_drv_t * disp_drv, const lv_area_t * area, lv_color_t * color_p);

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
ILI9488_Typedef* driver;

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART2_UART_Init();
  MX_TIM2_Init();
  MX_DMA_Init();
  MX_I2C1_Init();
  /* USER CODE BEGIN 2 */
  HAL_NVIC_DisableIRQ(EXTI9_5_IRQn);

  driver = ILI9488_Create();

  driver->init(driver);

  lv_init();

  hal_init();

  gui_init();

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* Periodically call the lv_task handler.
    * It could be done in a timer interrupt or an OS task too.*/
    lv_timer_handler();
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 1;
  RCC_OscInitStruct.PLL.PLLN = 10;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV7;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
/**
 * Initialize the Hardware Abstraction Layer (HAL) for the LVGL graphics
 * library
 */
static void hal_init(void)
{
  
  driver->init(driver);

  /*Create a display buffer*/
  static lv_disp_draw_buf_t disp_buf1;
  static lv_color_t buf1_1[ILI9488_VER_RES * 30];
  //static lv_color_t buf1_2[ILI9488_VER_RES * 30];
  lv_disp_draw_buf_init(&disp_buf1, buf1_1, NULL, ILI9488_VER_RES * 30);

  /*Create a display*/
  static lv_disp_drv_t disp_drv;
  lv_disp_drv_init(&disp_drv); /*Basic initialization*/
  disp_drv.draw_buf = &disp_buf1;
  disp_drv.flush_cb = my_flush_cb;
  disp_drv.hor_res = ILI9488_HOR_RES;
  disp_drv.ver_res = ILI9488_VER_RES;
  disp_drv.antialiasing = 1;
  disp_drv.rotated = 0;

  lv_disp_t * disp = lv_disp_drv_register(&disp_drv);

  lv_theme_t * th = lv_theme_default_init(disp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED), LV_THEME_DEFAULT_DARK, LV_FONT_DEFAULT);
  lv_disp_set_theme(disp, th);

  lv_group_t * g = lv_group_create();
  lv_group_set_default(g);

  /* Add the mouse as input device
   * Use the 'mouse' driver which reads the PC's mouse*/
  // Init touch pad
  GT911_init();
  // mouse_init();
  static lv_indev_drv_t indev_drv_1;
  lv_indev_drv_init(&indev_drv_1); /*Basic initialization*/
  indev_drv_1.type = LV_INDEV_TYPE_POINTER;

  /*This function will be called periodically (by the library) to get the mouse position and state*/
  indev_drv_1.read_cb = my_input_read;
  lv_indev_drv_register(&indev_drv_1);

}

void my_input_read(lv_indev_drv_t * drv, lv_indev_data_t*data) {

  uint8_t buffer;
  uint16_t cmd = 0x4E81;
  HAL_I2C_Master_Transmit(&hi2c1, 0x28, (uint8_t*)&cmd, 2, 1000);
  HAL_I2C_Master_Receive(&hi2c1, 0x29, &buffer, 1, 1000);

  if((buffer & 0x80) && ((buffer & 0x01) == 0x01)) {
    uint8_t x1 = 0;
    uint8_t x2 = 0;
    uint8_t y1 = 0;
    uint8_t y2 = 0;
    
    cmd = 0x5081;
    HAL_I2C_Master_Transmit(&hi2c1, 0x28, (uint8_t*)&cmd, 2, 1000);
    HAL_I2C_Master_Receive(&hi2c1, 0x29, &x1, 1, 1000);

    cmd = 0x5181;
    HAL_I2C_Master_Transmit(&hi2c1, 0x28, (uint8_t*)&cmd, 2, 1000);
    HAL_I2C_Master_Receive(&hi2c1, 0x29, &x2, 1, 1000);

    // Read y for point 
    cmd = 0x5281;
    HAL_I2C_Master_Transmit(&hi2c1, 0x28, (uint8_t*)&cmd, 2, 1000);
    HAL_I2C_Master_Receive(&hi2c1, 0x29, &y1, 1, 1000);

    cmd = 0x5381;
    HAL_I2C_Master_Transmit(&hi2c1, 0x28, (uint8_t*)&cmd, 2, 1000);
    HAL_I2C_Master_Receive(&hi2c1, 0x29, &y2, 1, 1000);

    uint8_t cmd2[3] = {0x81, 0x4E, (buffer & 0x7E)};
    HAL_I2C_Master_Transmit(&hi2c1, 0x28, cmd2, 3, 1000);
    
    #if (ILI9488_LANDSCAPE)
    data->point.y = ((x1) | (x2 << 8));
    data->point.x = 480 - ((y1) | (y2 << 8));
    #endif
    #if (ILI9488_PORTRAIT)
    data->point.y = ((y1) | (y2 << 8));
    data->point.x = ((x1) | (x2 << 8));
    #endif
    
    data->state = LV_INDEV_STATE_PRESSED;
  } else {
    uint8_t cmd2[3] = {0x81, 0x4E, (buffer & 0x7E)};
    HAL_I2C_Master_Transmit(&hi2c1, 0x28, cmd2, 3, 1000);
    data->state = LV_INDEV_STATE_RELEASED; 
  }
}

void my_flush_cb(lv_disp_drv_t * disp_drv, const lv_area_t * area, lv_color_t * color_p) {

    /*The most simple case (but also the slowest) to put all pixels to the screen one-by-one
     *`put_px` is just an example, it needs to implemented by you.*/
    ILI9488_column_addr_set((uint16_t)area->x1, (uint16_t)area->x2);
    ILI9488_page_addr_set((uint16_t)area->y1, (uint16_t)area->y2);
    driver->draw_buffer((uint16_t*)color_p, (uint16_t)lv_area_get_size(area));

    /* IMPORTANT!!!
     * Inform the graphics library that you are ready with the flushing*/
    lv_disp_flush_ready(disp_drv);
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

