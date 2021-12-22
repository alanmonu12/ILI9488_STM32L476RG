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
#include "i2c.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdbool.h"
#include "../lvgl/lvgl.h"
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
static lv_obj_t * chart;
static lv_chart_series_t * ser;
static lv_chart_cursor_t * cursor;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
static void hal_init(void);
void my_input_read(lv_indev_drv_t * drv, lv_indev_data_t*data);
void my_flush_cb(lv_disp_drv_t * disp_drv, const lv_area_t * area, lv_color_t * color_p);
static void event_handler(lv_event_t * e);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
bool button_state;
uint8_t command[2] = {0x80, 0x40};
uint8_t command2[2] = {0x81, 0x4E};
uint8_t command3[2] = {0x81, 0x46};
uint8_t command4[2] = {0x81, 0x47};
uint8_t command5[2] = {0x81, 0x48};
uint8_t command6[2] = {0x81, 0x49};
uint8_t command7[3] = {0x80, 0x40, 0x00};
uint8_t buffer;
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
  MX_I2C1_Init();
  /* USER CODE BEGIN 2 */

  //HAL_I2C_Mem_Read(&hi2c1, 0xBA, 0x804C, 1, &buffer, 1, 10000);

  lv_init();

  hal_init();

  button_state = false;
  chart = lv_chart_create(lv_scr_act());
  lv_obj_set_size(chart, 200, 150);
  lv_obj_align(chart, LV_ALIGN_CENTER, 0, -10);

  lv_chart_set_axis_tick(chart, LV_CHART_AXIS_PRIMARY_Y, 10, 5, 6, 5, true, 40);
  lv_chart_set_axis_tick(chart, LV_CHART_AXIS_PRIMARY_X, 10, 5, 10, 1, true, 30);

  lv_obj_add_event_cb(chart, event_handler, LV_EVENT_ALL, NULL);
  lv_obj_refresh_ext_draw_size(chart);

  cursor = lv_chart_add_cursor(chart, lv_palette_main(LV_PALETTE_BLUE), LV_DIR_LEFT | LV_DIR_BOTTOM);

  ser = lv_chart_add_series(chart, lv_palette_main(LV_PALETTE_RED), LV_CHART_AXIS_PRIMARY_Y);
  uint32_t i;
  for(i = 0; i < 10; i++) {
      lv_chart_set_next_value(chart, ser, lv_rand(10,90));
  }

  lv_chart_set_zoom_x(chart, 500);

  lv_obj_t * label = lv_label_create(lv_scr_act());
  lv_label_set_text(label, "Click on a point");
  lv_obj_align_to(label, chart, LV_ALIGN_OUT_TOP_MID, 0, -5);
//-------------------------------------------------------------------
  // lv_obj_t * label;

  // lv_obj_t * btn1 = lv_btn_create(lv_scr_act());
  //   lv_obj_add_event_cb(btn1, event_handler, LV_EVENT_ALL, NULL);
  //   lv_obj_align(btn1, LV_ALIGN_CENTER, 0, -40);
  //   lv_obj_add_flag(btn1, LV_OBJ_FLAG_CHECKABLE);
  //   lv_obj_set_height(btn1, LV_SIZE_CONTENT);

  // label = lv_label_create(btn1);
  // lv_label_set_text(label, "Toggle");
  // lv_obj_center(label);

  // lv_obj_t * btn2 = lv_btn_create(lv_scr_act());
  // lv_obj_add_event_cb(btn2, event_handler, LV_EVENT_ALL, NULL);
  // lv_obj_align(btn2, LV_ALIGN_CENTER, -100, -40);
  // lv_obj_add_flag(btn2, LV_OBJ_FLAG_CHECKABLE);
  // lv_obj_set_height(btn2, LV_SIZE_CONTENT);

  // label = lv_label_create(btn2);
  // lv_label_set_text(label, "Button");
  // lv_obj_center(label);
  
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* Periodically call the lv_task handler.
    * It could be done in a timer interrupt or an OS task too.*/
    lv_timer_handler();
    // poolong mode read touch
    //HAL_I2C_Master_Transmit(&hi2c1, 0xBA, command2, 2, 1000);
    //HAL_I2C_Master_Receive(&hi2c1, 0xBB, &buffer, 1, 1000);

    //uint16_t cmd = 0xA881;
    //HAL_I2C_Master_Transmit(&hi2c1, 0xBA, (uint8_t*)&cmd, 2, 1000);
    //HAL_I2C_Master_Receive(&hi2c1, 0xBB, &buffer, 1, 1000);
    //Read xfor point 1
    // HAL_I2C_Master_Transmit(&hi2c1, 0xBA, command3, 2, 1000);
    // HAL_I2C_Master_Receive(&hi2c1, 0xBB, x_cor[0], 1, 1000);
    // HAL_I2C_Master_Transmit(&hi2c1, 0xBA, command4, 2, 1000);
    // HAL_I2C_Master_Receive(&hi2c1, 0xBB, x_cor[1], 1, 1000);
    // // Read y for point 
    // HAL_I2C_Master_Transmit(&hi2c1, 0xBA, command5, 2, 1000);
    // HAL_I2C_Master_Receive(&hi2c1, 0xBB, y_cor[0], 1, 1000);
    // HAL_I2C_Master_Transmit(&hi2c1, 0xBA, command6, 2, 1000);
    // HAL_I2C_Master_Receive(&hi2c1, 0xBB, y_cor[1], 1, 1000);
    //HAL_Delay(1000);

    // uint8_t buffer;
    // uint16_t cmd = 0x4E81;
    // HAL_I2C_Master_Transmit(&hi2c1, 0x28, (uint8_t*)&cmd, 2, 1000);
    // HAL_I2C_Master_Receive(&hi2c1, 0x29, &buffer, 1, 1000);

    // if((buffer & 0x80) && (buffer & 0x01 == 0x01)) {
    //   cmd = 0x5081;
    //   HAL_I2C_Master_Transmit(&hi2c1, 0x28, &cmd, 2, 1000);
    //   HAL_I2C_Master_Receive(&hi2c1, 0x29, x_cor[0], 1, 1000);

    //   cmd = 0x5181;
    //   HAL_I2C_Master_Transmit(&hi2c1, 0x28, &cmd, 2, 1000);
    //   HAL_I2C_Master_Receive(&hi2c1, 0x29, x_cor[1], 1, 1000);

    //   // Read y for point 
    //   cmd = 0x5281;
    //   HAL_I2C_Master_Transmit(&hi2c1, 0x28, &cmd, 2, 1000);
    //   HAL_I2C_Master_Receive(&hi2c1, 0x29, y_cor[0], 1, 1000);

    //   cmd = 0x5381;
    //   HAL_I2C_Master_Transmit(&hi2c1, 0x28, &cmd, 2, 1000);
    //   HAL_I2C_Master_Receive(&hi2c1, 0x29, y_cor[1], 1, 1000);

    //   uint8_t cmd2[3] = {0x81, 0x4E, (buffer & 0x7E)};
    //   HAL_I2C_Master_Transmit(&hi2c1, 0x28, cmd2, 3, 1000);
    // }
    // else if((buffer & 0x80)) {
    //   uint8_t cmd2[3] = {0x81, 0x4E, (buffer & 0x7E)};
    //   HAL_I2C_Master_Transmit(&hi2c1, 0x28, cmd2, 3, 1000);
    // }
    // HAL_Delay(1);
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
  /* Use the 'monitor' driver which creates window on PC's monitor to simulate a display*/
  //monitor_init();
  ILI9488_init();
  /* Tick init.
   * You have to call 'lv_tick_inc()' in periodically to inform LittelvGL about
   * how much time were elapsed Create an SDL thread to do this*/
  //SDL_CreateThread(tick_thread, "tick", NULL);

  /*Create a display buffer*/
  static lv_disp_draw_buf_t disp_buf1;
  static lv_color_t buf1_1[ILI9488_HOR_RES * 60];
  //static lv_color_t buf1_2[ILI9488_VER_RES * 40];
  lv_disp_draw_buf_init(&disp_buf1, buf1_1, NULL, ILI9488_HOR_RES * 60);

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
  lv_indev_t *mouse_indev = lv_indev_drv_register(&indev_drv_1);

  // keyboard_init();
  // static lv_indev_drv_t indev_drv_2;
  // lv_indev_drv_init(&indev_drv_2); /*Basic initialization*/
  // indev_drv_2.type = LV_INDEV_TYPE_KEYPAD;
  // indev_drv_2.read_cb = keyboard_read;
  // lv_indev_t *kb_indev = lv_indev_drv_register(&indev_drv_2);
  // lv_indev_set_group(kb_indev, g);
  // mousewheel_init();
  // static lv_indev_drv_t indev_drv_3;
  // lv_indev_drv_init(&indev_drv_3); /*Basic initialization*/
  // indev_drv_3.type = LV_INDEV_TYPE_ENCODER;
  // indev_drv_3.read_cb = mousewheel_read;

  // lv_indev_t * enc_indev = lv_indev_drv_register(&indev_drv_3);
  // lv_indev_set_group(enc_indev, g);

  // /*Set a cursor for the mouse*/
  // LV_IMG_DECLARE(mouse_cursor_icon); /*Declare the image file.*/
  // lv_obj_t * cursor_obj = lv_img_create(lv_scr_act()); /*Create an image object for the cursor */
  // lv_img_set_src(cursor_obj, &mouse_cursor_icon);           /*Set the image source*/
  // lv_indev_set_cursor(mouse_indev, cursor_obj);             /*Connect the image  object to the driver*/
}

void my_input_read(lv_indev_drv_t * drv, lv_indev_data_t*data) {

  uint8_t buffer;
  uint16_t cmd = 0x4E81;
  HAL_I2C_Master_Transmit(&hi2c1, 0x28, (uint8_t*)&cmd, 2, 1000);
  HAL_I2C_Master_Receive(&hi2c1, 0x29, &buffer, 1, 1000);

  if((buffer & 0x80) && (buffer & 0x01 == 0x01)) {
    uint8_t x1 = 0;
    uint8_t x2 = 0;
    uint8_t y1 = 0;
    uint8_t y2 = 0;
    
    cmd = 0x5081;
    HAL_I2C_Master_Transmit(&hi2c1, 0x28, &cmd, 2, 1000);
    HAL_I2C_Master_Receive(&hi2c1, 0x29, &x1, 1, 1000);

    cmd = 0x5181;
    HAL_I2C_Master_Transmit(&hi2c1, 0x28, &cmd, 2, 1000);
    HAL_I2C_Master_Receive(&hi2c1, 0x29, &x2, 1, 1000);

    // Read y for point 
    cmd = 0x5281;
    HAL_I2C_Master_Transmit(&hi2c1, 0x28, &cmd, 2, 1000);
    HAL_I2C_Master_Receive(&hi2c1, 0x29, &y1, 1, 1000);

    cmd = 0x5381;
    HAL_I2C_Master_Transmit(&hi2c1, 0x28, &cmd, 2, 1000);
    HAL_I2C_Master_Receive(&hi2c1, 0x29, &y2, 1, 1000);

    uint8_t cmd2[3] = {0x81, 0x4E, (buffer & 0x7E)};
    HAL_I2C_Master_Transmit(&hi2c1, 0x28, cmd2, 3, 1000);
    data->point.x = (x1) | (x2 << 8);
    data->point.y = (y1) | (y2 << 8);
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
    int32_t x, y;
    for(y = area->y1; y <= area->y2; y++) {
        for(x = area->x1; x <= area->x2; x++) {
            ILI9488_draw_pixel(x,y,color_p->ch.red,color_p->ch.green,color_p->ch.blue);
            //put_px(x, y, *color_p);
            color_p++;
        }
    }

    /* IMPORTANT!!!
     * Inform the graphics library that you are ready with the flushing*/
    lv_disp_flush_ready(disp_drv);
}

static void event_handler(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_target(e);

    static int32_t last_id = -1;

    if(code == LV_EVENT_CLICKED) {
        LV_LOG_USER("Clicked");
    }
    else if(code == LV_EVENT_VALUE_CHANGED) {
        LV_LOG_USER("Toggled");
    }
    if(code == LV_EVENT_VALUE_CHANGED) {
        last_id = lv_chart_get_pressed_point(obj);
        if(last_id != LV_CHART_POINT_NONE) {
            lv_chart_set_cursor_point(obj, cursor, NULL, last_id);
        }
    }
    else if(code == LV_EVENT_DRAW_PART_END) {
        lv_obj_draw_part_dsc_t * dsc = lv_event_get_draw_part_dsc(e);
        if(dsc->part == LV_PART_CURSOR && dsc->p1 && dsc->p2 && dsc->p1->y == dsc->p2->y && last_id >= 0) {
            lv_coord_t * data_array = lv_chart_get_y_array(chart, ser);
            lv_coord_t v = data_array[last_id];
            char buf[16];
            lv_snprintf(buf, sizeof(buf), "%d", v);

            lv_point_t size;
            lv_txt_get_size(&size, buf, LV_FONT_DEFAULT, 0, 0, LV_COORD_MAX, LV_TEXT_FLAG_NONE);

            lv_area_t a;
            a.y2 = dsc->p1->y - 5;
            a.y1 = a.y2 - size.y - 10;
            a.x1 = dsc->p1->x + 10;
            a.x2 = a.x1 + size.x + 10;

            lv_draw_rect_dsc_t draw_rect_dsc;
            lv_draw_rect_dsc_init(&draw_rect_dsc);
            draw_rect_dsc.bg_color = lv_palette_main(LV_PALETTE_BLUE);
            draw_rect_dsc.radius = 3;

            lv_draw_rect(&a, dsc->clip_area, &draw_rect_dsc);

            lv_draw_label_dsc_t draw_label_dsc;
            lv_draw_label_dsc_init(&draw_label_dsc);
            draw_label_dsc.color = lv_color_white();
            a.x1 += 5;
            a.x2 -= 5;
            a.y1 += 5;
            a.y2 -= 5;
            lv_draw_label(&a, dsc->clip_area, &draw_label_dsc, buf, NULL);
        }
    }
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

