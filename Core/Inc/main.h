/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
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
#include "stm32h7xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "app_tle5012b.h"
#include "Vofa.h"
#include "fw.h"
#include "motor.h"
#include "dwt.h"
#include "math.h"
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */
typedef struct {
	uint8_t mode;
	uint8_t angle;
	uint8_t amp;
}DataFrame;
typedef struct {
	uint16_t X;
	uint16_t Y;
}Angle;
typedef struct {
	float AX;
	float AY;
}Amp;
typedef struct{
	uint16_t p_x;
	uint16_t p_y;
}WavePointer;
typedef struct{
	float pwm;
	uint8_t dir;
}Motor;
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
#define LED_Pin GPIO_PIN_3
#define LED_GPIO_Port GPIOE
#define frontEn_Pin GPIO_PIN_0
#define frontEn_GPIO_Port GPIOA
#define backEn_Pin GPIO_PIN_1
#define backEn_GPIO_Port GPIOA
#define leftEn_Pin GPIO_PIN_2
#define leftEn_GPIO_Port GPIOA
#define rightEn_Pin GPIO_PIN_3
#define rightEn_GPIO_Port GPIOA
#define frontPh_Pin GPIO_PIN_4
#define frontPh_GPIO_Port GPIOA
#define backPh_Pin GPIO_PIN_5
#define backPh_GPIO_Port GPIOA
#define leftPh_Pin GPIO_PIN_6
#define leftPh_GPIO_Port GPIOA
#define rightPh_Pin GPIO_PIN_7
#define rightPh_GPIO_Port GPIOA
#define X_Pin GPIO_PIN_5
#define X_GPIO_Port GPIOD
#define Y_Pin GPIO_PIN_6
#define Y_GPIO_Port GPIOD
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
