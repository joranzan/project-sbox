/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * File Name          : freertos.c
 * Description        : Code for freertos applications
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2024 STMicroelectronics.
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
#include <stdio.h>
#include "mpu6050.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
extern I2C_HandleTypeDef hi2c1;
extern MPU6050_t MPU6050;
extern uint16_t recoil;
extern uint16_t started;
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */
/* USER CODE END Variables */
/* Definitions for aimTask */
osThreadId_t aimTaskHandle;
const osThreadAttr_t aimTask_attributes = {
  .name = "aimTask",
  .stack_size = 256 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for buttonTask */
osThreadId_t buttonTaskHandle;
const osThreadAttr_t buttonTask_attributes = {
  .name = "buttonTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for recoilTask */
osThreadId_t recoilTaskHandle;
const osThreadAttr_t recoilTask_attributes = {
  .name = "recoilTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartAimTask(void *argument);
void StartButtonTask(void *argument);
void StartRecoilTask(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
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
  /* creation of aimTask */
  aimTaskHandle = osThreadNew(StartAimTask, NULL, &aimTask_attributes);

  /* creation of buttonTask */
  buttonTaskHandle = osThreadNew(StartButtonTask, NULL, &buttonTask_attributes);

  /* creation of recoilTask */
  recoilTaskHandle = osThreadNew(StartRecoilTask, NULL, &recoilTask_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */

  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_StartAimTask */
/**
* @brief Function implementing the aimTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartAimTask */
void StartAimTask(void *argument)
{
  /* USER CODE BEGIN StartAimTask */
  /* Infinite loop */
  for(;;)
    {
      started = 1;
      if (started) {
    	  read_gyro(&hi2c1, &MPU6050, 0);
    	  read_accel(&hi2c1, &MPU6050, 0);
        get_angle(&hi2c1, &MPU6050);
        printf("point,%3.2f,%3.2f,%3.2f\r\n", MPU6050.filtered_x_angle, MPU6050.filtered_y_angle, MPU6050.filtered_z_angle);
      }
      osDelay(10);
    }
  /* USER CODE END StartAimTask */
}

/* USER CODE BEGIN Header_StartButtonTask */
/**
* @brief Function implementing the buttonTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartButtonTask */
void StartButtonTask(void *argument)
{
  /* USER CODE BEGIN StartButtonTask */
  /* Infinite loop */
  for(;;)
  {
    if (HAL_GPIO_ReadPin (TRIGGER_BTN_GPIO_Port, TRIGGER_BTN_Pin) == 0) {
    	printf("trigger\r\n");
    }
    if (HAL_GPIO_ReadPin (RELOAD_GPIO_Port, RELOAD_Pin) == 0) {
    	printf("reload\r\n");
    }
    if (HAL_GPIO_ReadPin (ZERO_POINT_GPIO_Port, ZERO_POINT_Pin) == 0) {
      printf("zero\r\n");
    }
    osDelay(10);
  }
  /* USER CODE END StartButtonTask */
}

/* USER CODE BEGIN Header_StartRecoilTask */
/**
* @brief Function implementing the recoilTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartRecoilTask */
void StartRecoilTask(void *argument)
{
  /* USER CODE BEGIN StartRecoilTask */
  /* Infinite loop */
  for(;;)
    {

      if (started && recoil) {
    	  recoil = 0;
    	  HAL_GPIO_WritePin(RECOIL_SIG_GPIO_Port, RECOIL_SIG_Pin, SET);
    	  HAL_Delay(100);
    	  HAL_GPIO_WritePin(RECOIL_SIG_GPIO_Port, RECOIL_SIG_Pin, RESET);
    	  printf("recoil\r\n");
      }
      osDelay(10);
    }
  /* USER CODE END StartRecoilTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

