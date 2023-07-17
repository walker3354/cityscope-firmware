/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * File Name          : freertos.c
 * Description        : Code for freertos applications
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2023 STMicroelectronics.
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
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "hc_sr04.h"
#include "ws2812.h"
#include "tim.h"
#include "can.h"
#include "CO_app_STM32.h"
#include "OD.h"
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
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
/* Definitions for ReadDistance */

/* Definitions for UITask */

/* Definitions for canopenTask */
osThreadId_t canopenTaskHandle;
const osThreadAttr_t canopenTask_attributes = {
    .name = "canopenTask",
    .stack_size = 128 * 4,
    .priority = (osPriority_t)osPriorityRealtime,
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartReadDistance(void *argument);
void StartUITask(void *argument);
void canopen_task(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
 * @brief  FreeRTOS initialization
 * @param  None
 * @retval None
 */
void MX_FREERTOS_Init(void)
{
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of ReadDistance */

  /* creation of UITask */

  /* creation of canopenTask */
  canopenTaskHandle = osThreadNew(canopen_task, NULL, &canopenTask_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */
}

/* USER CODE BEGIN Header_StartReadDistance */
/**
 * @brief  Function implementing the ReadDistance thread.
 * @param  argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartReadDistance */

/* USER CODE BEGIN Header_StartUITask */
/**
 * @brief Function implementing the UITask thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartUITask */

/* USER CODE BEGIN Header_canopen_task */
/**
 * @brief Function implementing the canopenTask thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_canopen_task */
void canopen_task(void *argument)
{
  /* USER CODE BEGIN canopen_task */
  CANopenNodeSTM32 canOpenNodeSTM32;
  canOpenNodeSTM32.CANHandle = &hcan;
  canOpenNodeSTM32.HWInitFunction = MX_CAN_Init;
  canOpenNodeSTM32.timerHandle = &htim17;
  canOpenNodeSTM32.desiredNodeID = (uint8_t)get_NodeID();
  canOpenNodeSTM32.baudrate = 125;
  canopen_app_init(&canOpenNodeSTM32);
  /* Infinite loop */
  for (;;)
  {
    canopen_app_process();
    if (OD_PERSIST_COMM.x6001_light_control_data == 0) // breath
    {
      sendPixel(255, 255, 255);
      bool flag = 0;
      for (int j = 10; j < 255; (flag == 0 ? j++ : j--))
      {
        for (int i = 0; i < WS2821_MAX_LED; i++)
        {
          sendPixel(j, j, j);
        }
        ws2812_reset();
        osDelay(20);
        if (j == 254)
        {
          flag = 1;
        }
        else if (j == 10)
        {
          flag = 0;
        }
        canopen_app_process();
        if (OD_PERSIST_COMM.x6001_light_control_data != 0)
        {
          clear();
          osDelay(50);
          break;
        }
      }
    }

    else if ((OD_PERSIST_COMM.x6001_light_control_data >= 10 && OD_PERSIST_COMM.x6001_light_control_data < 13) || (OD_PERSIST_COMM.x6001_light_control_data > 36 && OD_PERSIST_COMM.x6001_light_control_data <=  43)) // check area
    {
      switch (OD_PERSIST_COMM.x6001_light_control_data)
      {
      case 37:
        for (int i = 0; i < 100; i++)
        {
          sendPixel(255, 255, 255);
        }
        ws2812_reset();
        break;
      case 38:
        for (int i = 0; i < 45; i++)
        {
          sendPixel(0, 0, 0);
        }
        for (int i = 0; i < 105; i++)
        {
          sendPixel(255, 255, 255);
        }
        ws2812_reset();
        break;
      case 39:
        for (int i = 0; i < 90; i++)
        {
          sendPixel(0, 0, 0);
        }
        for (int i = 0; i < 100; i++)
        {
          sendPixel(255,255,255);
        }
        ws2812_reset();
        break;
      case 40:
        for (int i = 0; i < 140; i++)
        {
          sendPixel(0, 0, 0);
        }
        for (int i = 0; i < 100; i++)
        {
          sendPixel(255, 255, 255);
        }
        ws2812_reset();
        break;
      case 41:
        for (int i = 0; i < 185; i++)
        {
          sendPixel(0, 0, 0);
        }
        for (int i = 0; i < 100; i++)
        {
          sendPixel(255, 255, 255);
        }
        ws2812_reset();
        break;
      case 42:
        for (int i = 0; i < 230; i++)
        {
          sendPixel(0, 0, 0);
        }
        for (int i = 0; i < 100; i++)
        {
          sendPixel(255, 255, 255);
        }
        ws2812_reset();
        break;
      case 43:
        for (int i = 0; i < 285; i++)
        {
          sendPixel(0, 0, 0);
        }
        for (int i = 0; i < 100; i++)
        {
          sendPixel(255, 255, 255);
        }
        ws2812_reset();
        break;
      case 10:
        for (int i = 0; i < 325; i++)
        {
          sendPixel(0, 0, 0);
        }
        for (int i = 0; i < 115; i++)
        {
          sendPixel(255, 255, 255);
        }
        ws2812_reset();
        break;
      case 11:
        for (int i = 0; i < 375; i++)
        {
          sendPixel(0, 0, 0);
        }
        for (int i = 0; i < 105; i++)
        {
          sendPixel(255, 255, 255);
        }
        ws2812_reset();
        break;
      case 12:
        for (int i = 0; i < 415; i++)
        {
          sendPixel(0, 0, 0);
        }
        for (int i = 0; i < 150; i++)
        {
          sendPixel(255, 255, 255);
        }
        ws2812_reset();
        break;
      }
      
      for (;;)
      {
        canopen_app_process();
        if (OD_PERSIST_COMM.x6001_light_control_data == 0)
        {
          break;
        }
        osDelay(50);
      }
    }
    vTaskDelay(pdMS_TO_TICKS(1));
  }
}
/* USER CODE END canopen_task */

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */
