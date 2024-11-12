/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx_hal.h"

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
#define CO_uart huart4
#define RF_SPI hspi1
#define RTC_THS_i2c hi2c2
#define PM2p5_uart huart3
#define RTL_uart huart2
#define i2c_Display hi2c1
#define nLCD_Backlight_btn_Pin GPIO_PIN_13
#define nLCD_Backlight_btn_GPIO_Port GPIOC
#define CO_RX_Pin GPIO_PIN_0
#define CO_RX_GPIO_Port GPIOA
#define CO_TX_Pin GPIO_PIN_1
#define CO_TX_GPIO_Port GPIOA
#define MCU_RTL_RX_Pin GPIO_PIN_2
#define MCU_RTL_RX_GPIO_Port GPIOA
#define MCU_RTL_TX_Pin GPIO_PIN_3
#define MCU_RTL_TX_GPIO_Port GPIOA
#define Buzzer_Pin GPIO_PIN_4
#define Buzzer_GPIO_Port GPIOA
#define RF_MISO_Dout_Pin GPIO_PIN_6
#define RF_MISO_Dout_GPIO_Port GPIOA
#define RF_MOSI_Din_Pin GPIO_PIN_7
#define RF_MOSI_Din_GPIO_Port GPIOA
#define RF_nIRQ_Pin GPIO_PIN_0
#define RF_nIRQ_GPIO_Port GPIOB
#define PM2p5_RX_Pin GPIO_PIN_10
#define PM2p5_RX_GPIO_Port GPIOB
#define PM2p5_TX_Pin GPIO_PIN_11
#define PM2p5_TX_GPIO_Port GPIOB
#define LCD_Backlight_Pin GPIO_PIN_13
#define LCD_Backlight_GPIO_Port GPIOB
#define LED_RF_Pin GPIO_PIN_14
#define LED_RF_GPIO_Port GPIOB
#define LED_CO_Pin GPIO_PIN_15
#define LED_CO_GPIO_Port GPIOB
#define SCL_Display_Pin GPIO_PIN_9
#define SCL_Display_GPIO_Port GPIOA
#define SDA_Display_Pin GPIO_PIN_10
#define SDA_Display_GPIO_Port GPIOA
#define SCL_RTC_THS_Pin GPIO_PIN_11
#define SCL_RTC_THS_GPIO_Port GPIOA
#define SDA_RTC_THS_Pin GPIO_PIN_12
#define SDA_RTC_THS_GPIO_Port GPIOA
#define RF_nSEL_Pin GPIO_PIN_15
#define RF_nSEL_GPIO_Port GPIOA
#define RF_SCK_Pin GPIO_PIN_3
#define RF_SCK_GPIO_Port GPIOB
#define PWR_State_D3_Pin GPIO_PIN_4
#define PWR_State_D3_GPIO_Port GPIOB
#define PWR_State_D2_Pin GPIO_PIN_5
#define PWR_State_D2_GPIO_Port GPIOB
#define PWR_State_D1_Pin GPIO_PIN_6
#define PWR_State_D1_GPIO_Port GPIOB
#define nRF_Config_btn_Pin GPIO_PIN_7
#define nRF_Config_btn_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
