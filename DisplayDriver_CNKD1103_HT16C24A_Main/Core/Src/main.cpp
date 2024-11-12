/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
//#include <cstdint>

#include "DisplayDriver_CNKD1103_HT16C24A.h"
#ifdef debug
//#include <stdio.h>  // For s_print_f function
//#include "string.h"
#endif

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
//DisplayDriver_CNKD1103_HT16C24A lcd(&i2c_Display, &lcdAddress, &uart);
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef hi2c1;
I2C_HandleTypeDef hi2c2;

SPI_HandleTypeDef hspi1;

UART_HandleTypeDef huart2;
UART_HandleTypeDef huart3;
UART_HandleTypeDef huart4;

/* USER CODE BEGIN PV */
//const uint16_t lcdAddress = { 0x3D << 1 };
const uint16_t lcdAddress = 0x3D;
//DisplayDriver_CNKD1103_HT16C24A lcd;
//char msg[300] = {"\0"};
//
//uint8_t Buffer[25] = {0};
//uint8_t Space[] = " - ";
//uint8_t StartMSG[] = "Starting I2C Scanning: \r\n";
//uint8_t EndMSG[] = "Done! \r\n\r\n";

DisplayDriver_CNKD1103_HT16C24A::weather_t weather;
DisplayDriver_CNKD1103_HT16C24A::degree_t degree;
DisplayDriver_CNKD1103_HT16C24A::weekday_t weekday;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C1_Init(void);
static void MX_I2C2_Init(void);
static void MX_SPI1_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_USART3_UART_Init(void);
static void MX_USART4_UART_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

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
#define uart CO_uart
  HAL_Delay(50); /// Power up Sequence Delay for LCD to work flawlessly.
//  (); //lcd;(&hi2c1, &lcdAddress, &huart4)

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_I2C1_Init();
  MX_I2C2_Init();
  MX_SPI1_Init();
  MX_USART2_UART_Init();
  MX_USART3_UART_Init();
  MX_USART4_UART_Init();
  /* USER CODE BEGIN 2 */

//	uint8_t i = 0, ret;
//	/*-[ I2C Bus Scanning ]-*/
//	HAL_UART_Transmit(&CO_uart, StartMSG, sizeof(StartMSG), 10000);
//	for(i=1; i<128; i++)
//	{
//	  ret = HAL_I2C_IsDeviceReady(&i2c_Display, (uint16_t)(i<<1), 3, 5);
//	  if (ret != HAL_OK) /* No ACK Received At That Address */
//	  {
//		  HAL_UART_Transmit(&CO_uart, Space, sizeof(Space), 10000);
//	  }
//	  else if(ret == HAL_OK)
//	  {
//		  sprintf((char*)Buffer, "0x%X", i);
//		  HAL_UART_Transmit(&CO_uart, Buffer, sizeof(Buffer), 10000);
//	  }
//	}
//	HAL_UART_Transmit(&CO_uart, EndMSG, sizeof(EndMSG), 10000);
//	/*--[ Scanning Done ]--*/

//  size_t size = 0;
//  HAL_Delay(300); /// Power up Sequence Delay for LCD to work flawlessly.
  DisplayDriver_CNKD1103_HT16C24A lcd(&i2c_Display, &lcdAddress, &uart);

  HAL_GPIO_WritePin(LCD_Backlight_GPIO_Port, LCD_Backlight_Pin, GPIO_PIN_SET);
  /// LCD Initialization
  if(lcd.lcdPortInit() == HAL_OK) //0x10 //&i2c_Display, &lcdAddress, &uart
  {
#ifdef debug
	  size = sprintf((char*)msg,  "LCD Initialization Success\r\n");// 	  memset(msg,, (size_t) sizeof("LCD Failed"));
#endif
  }
  else
  {
#ifdef debug
	  size = sprintf((char*)msg,  "LCD Initialization Failed\r\n");//memset(msg, "LCD Success", (size_t) sizeof("LCD Success"));
#endif
  }
#ifdef debug
  HAL_UART_Transmit(&uart, (uint8_t*)msg, sizeof(msg), HAL_MAX_DELAY); memset(msg, 0, (size_t) sizeof(msg));
#endif
  HAL_Delay(10);


  /// LCD Initialization
  if(lcd.displayInit() == HAL_OK) //0x10
  {
//	  lcd.displayFill();
#ifdef debug
	  size = sprintf((char*)msg,  "LCD Initialization Success\r\n");// 	  memset(msg,, (size_t) sizeof("LCD Failed"));
#endif
  }
  else
  {
#ifdef debug
	  size = sprintf((char*)msg,  "LCD Initialization Failed\r\n");//memset(msg, "LCD Success", (size_t) sizeof("LCD Success"));
#endif
  }
#ifdef debug
  HAL_UART_Transmit(&uart, (uint8_t*)msg, sizeof(msg), HAL_MAX_DELAY); memset(msg, 0, (size_t) sizeof(msg));
#endif
  HAL_Delay(10);


//  ;

//  for(uint8_t i = 0; i <= 10; i++)
//   {
//
// 	  lcd.hubBatteryStatus(i);
//
// 	  lcd.nodeBatteryStatus(i);
//
// 	  lcd.nodeRfSignals(i);
//
// 	  lcd.printNodeNumber(i);
// 	  HAL_Delay(1000);
//   }

//  for(float i = -2.1; i <= 200.1; i = i + (float)(0.1))
//  {
//
//	  lcd.hubBatteryStatus((uint8_t)i);
//
//	  lcd.nodeBatteryStatus((uint8_t)i);
//
//	  lcd.nodeRfSignals((uint8_t)i);
//
//	  lcd.printNodeNumber((uint8_t)i);
//
//	  lcd.printHubTemperature((uint8_t)i);
//
//	  lcd.printNodeTemperature((uint8_t)i);
//
//	  if(i>=0)
//	  {
//		  //if(i < (float)25.5)
//		  {
//
//			  lcd.printHubHumidity((uint16_t)(i*10));
//
//			  lcd.printNodeHumidity((uint16_t)(i*10));
//
//			  lcd.printSunriseTime((uint16_t)(i), (uint16_t)(i));
//			  lcd.printSunsetTime((uint16_t)(i), (uint16_t)(i));
//
//			  lcd.printDate((uint16_t)(i), (uint16_t)(i), lcd.Monday);
//
//			  if(((uint8_t)(i)) < 12)
//				  lcd.printTime((uint16_t)(i), (uint16_t)(i), lcd.AM);
//			  else if(((uint8_t)(i)) <= 24)
//				  lcd.printTime((uint16_t)(i), (uint16_t)(i), lcd.PM);
//			  else
//				  lcd.printTime((uint16_t)(i), (uint16_t)(i), lcd.NA);
//		  }
//
//		  lcd.printIndoorAirQualityIndex((uint16_t)(i*10));
//
//		  lcd.printIndoorCoLevel((uint16_t)(i*10));
//
//		  lcd.printOutdoorAirQualityIndex((uint16_t)(i*10));
//
//	  }
//	  HAL_Delay(100);
//  }


	/// Bias
//  	size = sprintf((char*)msg, "Bias Set: \t\t\t\r\n"); HAL_UART_Transmit(&uart, (uint8_t*)msg, size, HAL_MAX_DELAY); memset(msg, 0, (size_t) sizeof(msg));
  	/*
		LCD display off address 80H
		- { 0	0	0	0	Duty1	Bias1	Duty0	Bias0 }	LSB
		Select		Bias the Display
		[Value]		[Bias]
		 - 0		  1/3
		 - 1		  1/4
		 - 2		  1/5
	*/
//  if(lcd.biasOfDisplay(0x02) == HAL_OK)	// 0x00: is 1/3 Bias mode. 0x01 = 1/4 and 0x02 = 1/5
//  {
//	  size = sprintf((char*)msg, "Bias Set: Success\r\n");
//  }
//  else
//  {
//	  size = sprintf((char*)msg, "Bias Set: Fail\r\n");
//  }
//  HAL_UART_Transmit(&uart, (uint8_t*)msg, size, HAL_MAX_DELAY); memset(msg, 0, (size_t) sizeof(msg));
//  HAL_Delay(10);
//
//  	/// Duty
////	size = sprintf((char*)msg, "Duty Set to 1/8: \t\t\t\r\n"); HAL_UART_Transmit(&uart, (uint8_t*)msg, size, HAL_MAX_DELAY); memset(msg, 0, (size_t) sizeof(msg));
//  	/*
//		LCD display off address 80H
//		- { 0	0	0	0	Duty1	Bias1	Duty0	Bias0 }	LSB
//		Drive	Mode Selection
//		[Mode]	[Duty]
//		- 0		 1/4
//		- 1		 1/8
//		- 2		 1/16
//	*/
//  	if(lcd.dutyOfDisplay(0x01) == HAL_OK) // 0x01: is 8-COMs Selector mode.
//	{
//	  size = sprintf((char*)msg, "Duty Set to 1/8: Success\r\n");
//	}
//	else
//	{
//	  size = sprintf((char*)msg, "Duty Set to 1/8: Fail\r\n");
//	}
//	HAL_UART_Transmit(&uart, (uint8_t*)msg, size, HAL_MAX_DELAY); memset(msg, 0, (size_t) sizeof(msg));
//	HAL_Delay(10);
//
//	/// Frequency
////  	size = sprintf((char*)msg, "Frequency Set: \t\t\t\r\n"); HAL_UART_Transmit(&uart, (uint8_t*)msg, size, HAL_MAX_DELAY); memset(msg, 0, (size_t) sizeof(msg));
//	/*
//		Function to Select Frame Frequency of Display
//		- { 0	0	0	0	0	0	0	F }	LSB
//		[Frequency]	[Frame Frequency]
//		 - 0         80 Hz
//		 - 1         160 Hz
//	*/
//	if(lcd.frequency(true) == HAL_OK) // true means 160 kHz frequency
//  	{
//  	  size = sprintf((char*)msg, "Frequency Set: Success\r\n");
//  	}
//  	else
//  	{
//  	  size = sprintf((char*)msg, "Frequency Set: Fail\r\n");
//  	}
//  	HAL_UART_Transmit(&uart, (uint8_t*)msg, size, HAL_MAX_DELAY); memset(msg, 0, (size_t) sizeof(msg));
//  	HAL_Delay(10);
//
//    /// Internal Voltage Adjustment
////  	size = sprintf((char*)msg, "Internal Voltage Adjustment Enable: \r\n"); HAL_UART_Transmit(&uart, (uint8_t*)msg, size, HAL_MAX_DELAY); memset(msg, 0, (size_t) sizeof(msg));
//  	/*
//		Function to Select SEG/VLCD Settings
//		- { 0	0	DE	VE	DA3	DA2	DA1	DA0 }	LSB
//		[DE]    [VE]    [Pin Selected]  [Internal Voltage Adjestment]
//		- 0      0        VLCD Pin          off
//		- 0      1        VLCD Pin          on
//		- 1      0        SEG Pin           off
//		- 1      1        SEG Pin           on
//		-
//	*/
//  	if(lcd.segVlcdSetting(0x00) == HAL_OK)
//  	{
//  	  size = sprintf((char*)msg, "Internal Voltage Adjustment Enable: Success\r\n");
//  	}
//  	else
//  	{
//  	  size = sprintf((char*)msg, "Internal Voltage Adjustment Enable: Fail\r\n");
//  	}
//  	HAL_UART_Transmit(&uart, (uint8_t*)msg, size, HAL_MAX_DELAY); memset(msg, 0, (size_t) sizeof(msg));
//  	HAL_Delay(10);
//
//  	/// LCD Display Enable
////  	size = sprintf((char*)msg, "LCD Display Enable \t\t\r\n"); HAL_UART_Transmit(&uart, (uint8_t*)msg, size, HAL_MAX_DELAY); memset(msg, 0, (size_t) sizeof(msg));
//  	/*
//		Function to turn ON/OFF the Display
//		- { 0	0	0	0	0	0	S	E }	LSB
//		[Enable]   [Lcd Display]
//		 - 0         off
//		 - 1         on
//	*/
//  	if(lcd.display(true) == HAL_OK)
//  	{
//  	  size = sprintf((char*)msg, "LCD Display Enable: Success\r\n");
//  	}
//  	else
//  	{
//  	  size = sprintf((char*)msg, "LCD Display Enable: Fail\r\n");
//  	}
//  	HAL_UART_Transmit(&uart, (uint8_t*)msg, size, HAL_MAX_DELAY); memset(msg, 0, (size_t) sizeof(msg));
//  	HAL_Delay(10);
//
//  	/// LCD Display Driver Enable
////  	size = sprintf((char*)msg, "Display Driver Enable: \t\t\r\n"); HAL_UART_Transmit(&uart, (uint8_t*)msg, size, HAL_MAX_DELAY); memset(msg, 0, (size_t) sizeof(msg));
//  	/*
//		Function to Disable/Enable Display Driver IC (AiP16C22)
//		- { 0	0	0	0	0	0	S	E }	LSB
//		[Enable]   [Internal System Oscillator(S)]
//		 - 0         off
//		 - 1         on
//	*/
//  	if(lcd.disableDisplayDriver(true) == HAL_OK)
//  	{
//  	  size = sprintf((char*)msg, "Display Driver Enable: Success\r\n");
//  	}
//  	else
//  	{
//  	  size = sprintf((char*)msg, "Display Driver Enable: Fail\r\n");
//  	}
//  	HAL_UART_Transmit(&uart, (uint8_t*)msg, size, HAL_MAX_DELAY); memset(msg, 0, (size_t) sizeof(msg));
//  	HAL_Delay(10);
//
//  	/// Brightness Setting
////  	size = sprintf((char*)msg, "Brightness Setting: \t\t\r\n"); HAL_UART_Transmit(&uart, (uint8_t*)msg, size, HAL_MAX_DELAY); memset(msg, 0, (size_t) sizeof(msg));
//  	/*  Function to set Brightness of the LCD
//		[Bright]    [Display]
//		- 0          Low Brightness
//		- .          .
//		- .          .
//		- 15         Full Brightness
//		-
//	*/
//  	if(lcd.brightness(0x00) == HAL_OK)
//  	{
//  	  size = sprintf((char*)msg, "Brightness Setting: Success\r\n");
//  	}
//  	else
//  	{
//  	  size = sprintf((char*)msg, "Brightness Setting: Fail\r\n");
//  	}
//  	HAL_UART_Transmit(&uart, (uint8_t*)msg, size, HAL_MAX_DELAY); memset(msg, 0, (size_t) sizeof(msg));
//  	HAL_Delay(10);
//
//  	/// Clear Display
////  	size = sprintf((char*)msg, "Clear Display: \t\t\t\t\t\t\r\n"); memset(msg, 0, (size_t) sizeof(msg)); HAL_UART_Transmit(&uart, (uint8_t*)msg, size, HAL_MAX_DELAY);
//  	/*
//		Function to clear the whole screen
//		- Clear all the Memory Map and write it to the Screen.
//	*/
//  	if(lcd.displayClear() == HAL_OK)
//  	{
//  	  size = sprintf((char*)msg, "Clear Display: Success\r\n");
//  	}
//  	else
//  	{
//  	  size = sprintf((char*)msg, "Clear Display: Fail\r\n");
//  	}
//  	HAL_UART_Transmit(&uart, (uint8_t*)msg, size, HAL_MAX_DELAY); memset(msg, 0, (size_t) sizeof(msg));
//  	HAL_Delay(10);

#ifdef debug
  	/// Print LCD is Ready
  	size = sprintf((char*)msg, "LCD Device is Ready to Print!\r\n"); HAL_UART_Transmit(&uart, (uint8_t*)msg, size, HAL_MAX_DELAY); memset(msg, 0, (size_t) sizeof(msg));
  	HAL_Delay(10);
#endif
  	/// ICONs Settings
  	/*
		Function to enable or disable specified icon
		Options:
		- HUB_HOUSE_ICON			=   0	(uint8_t)
		- HUB_BATT_ICON				=	1	(uint8_t)
		- INDOOR_ICON				=	2	(uint8_t)
		- INDOOR_AQ_ICON			=	3	(uint8_t)
		- NODE_HOUSE_ICON			=	4	(uint8_t)
		- NODE_ICON					=	5	(uint8_t)
		- NODE_BATT_ICON			=	6	(uint8_t)
		- HUB_THERMO_ICON			=   7	(uint8_t)
		- HUB_DEG_F_ICON			=   8	(uint8_t)
		- HUB_DEG_C_ICON			=   9	(uint8_t)
		- HUB_AQI_ICON				=	10	(uint8_t)
		- GOOD_AQI_ICON				=	11	(uint8_t)
		- MODERATE_AQI_ICON			=	12	(uint8_t)
		- USG_AQI_ICON				=	13	(uint8_t)
		- POOR_AQI_ICON				=	14	(uint8_t)
		- V_POOR_AQI_ICON			=	15	(uint8_t)
		- HAZARD_AQI_ICON			=	16	(uint8_t)
		- PM2P5_ICON				=	17	(uint8_t)
		- NODE_THERMO_ICON			=	18	(uint8_t)
		- NODE_DEG_F_ICON			=   19  (uint8_t)
		- NODE_DEG_C_ICON			=   20  (uint8_t)
		- CO_PPM_ICON				=	21	(uint8_t)
		- HUB_HUMID_ICON			=	22	(uint8_t)
		- DRY_HUB_HUMID_ICON		=	23	(uint8_t)
		- COMFORT_HUB_HUMID_ICON	=	24	(uint8_t)
		- WET_HUB_HUMID_ICON		=	25	(uint8_t)
		- PERCENT_HUB_HUMID_ICON	=	26	(uint8_t)
		- FORECAST_ICON				=	27	(uint8_t)
		- MOON_ICON					=	28	(uint8_t)
		- STARS_ICON				=	29	(uint8_t)
		- SNOWY_CLOUD_ICON			=	30	(uint8_t)
		- SNOW_ICON					=	31	(uint8_t)
		- SUNNY_ICON				=	32	(uint8_t)
		- PARTIALY_SUNNY_ICON		=	33	(uint8_t)
		- RAINY_CLOUD_ICON			=	34	(uint8_t)
		- RAIN_ICON					=	35	(uint8_t)
		- THUNDER_ICON				=	36	(uint8_t)
		- AQI_OUT_ICON				=	37	(uint8_t)
		- SUNRISE_ICON				=	38	(uint8_t)
		- SUNSET_ICON				=	39	(uint8_t)
		- NODE_HUMID_ICON			=	40	(uint8_t)
		- DRY_NODE_HUMID_ICON		=	41	(uint8_t)
		- COMFORT_NODE_HUMID_ICON	=	42	(uint8_t)
		- WET_NODE_HUMID_ICON		=	43	(uint8_t)
		- PERCENT_NODE_HUMID_ICON	=	44	(uint8_t)
		- D_ICON					=	45	(uint8_t)
		- M_ICON					=	46	(uint8_t)
		- AM_ICON					=	47	(uint8_t)
		- PM_ICON					=	48	(uint8_t)
		- DAY_ICON					=	49	(uint8_t)
		-
	*/
  	/// All Icons ON
  	//  	size = sprintf((char*)msg, "In House Icon ON: \t\t\n\r\n"); HAL_UART_Transmit(&uart, (uint8_t*)msg, size, HAL_MAX_DELAY); memset(msg, 0, (size_t) sizeof(msg));
//  	for(uint8_t i = 0; i < 52; i++)
//  	{
//		if(lcd.icon(i, true) == HAL_OK)
//		{
//		  size = sprintf((char*)msg, "Icon Number: %d Success\r\n", i);
//		}
//		else
//		{
//		  size = sprintf((char*)msg, "In House Icon ON: Fail\r\n");
//		}
//		HAL_UART_Transmit(&uart, (uint8_t*)msg, size, HAL_MAX_DELAY); memset(msg, 0, (size_t) sizeof(msg));
//		HAL_Delay(1000);
//  	}
//  	/// HUB_BATT_ICON Icon ON
////	size = sprintf((char*)msg, "Hub Battery Icon ON: \t\t\n\r\n"); HAL_UART_Transmit(&uart, (uint8_t*)msg, size, HAL_MAX_DELAY); memset(msg, 0, (size_t) sizeof(msg));
//	if(lcd.icon(6, true) == HAL_OK)
//	{
//	  size = sprintf((char*)msg, "Hub Battery Icon ON: Success\r\n");
//	}
//	else
//	{
//	  size = sprintf((char*)msg, "Hub Battery Icon ON: Fail\r\n");
//	}
//	HAL_UART_Transmit(&uart, (uint8_t*)msg, size, HAL_MAX_DELAY); memset(msg, 0, (size_t) sizeof(msg));
//	HAL_Delay(10);
//
//	/// INDOOR_ICON Icon ON
////	size = sprintf((char*)msg, "Indoor Icon ON: \t\t\n\r\n"); HAL_UART_Transmit(&uart, (uint8_t*)msg, size, HAL_MAX_DELAY); memset(msg, 0, (size_t) sizeof(msg));
//	if(lcd.icon(7, true) == HAL_OK)
//	{
//	  size = sprintf((char*)msg, "Indoor Icon ON: Success\n");
//	}
//	else
//	{
//	  size = sprintf((char*)msg, "Indoor Icon ON: Fail\n");
//	}
//	HAL_UART_Transmit(&uart, (uint8_t*)msg, size, HAL_MAX_DELAY); memset(msg, 0, (size_t) sizeof(msg));
//	HAL_Delay(10);
//
//	/// INDOOR_AQ_ICON Icon ON
////	size = sprintf((char*)msg, "Indoor AQI Icon ON: \t\t\n\r\n"); HAL_UART_Transmit(&uart, (uint8_t*)msg, size, HAL_MAX_DELAY); memset(msg, 0, (size_t) sizeof(msg));
//	if(lcd.icon(8, true) == HAL_OK)
//	{
//	  size = sprintf((char*)msg, "Indoor AQI Icon ON: Success\r\n");
//	}
//	else
//	{
//	  size = sprintf((char*)msg, "Indoor AQI Icon ON: Fail\r\n");
//	}
//	HAL_UART_Transmit(&uart, (uint8_t*)msg, size, HAL_MAX_DELAY); memset(msg, 0, (size_t) sizeof(msg));
//	HAL_Delay(10);

//	if(lcd.displayFill() == HAL_OK)
//	{
//	  size = sprintf((char*)msg, "Fill the Display: Success\r\n");
//	}
//	else
//	{
//	  size = sprintf((char*)msg, "Fill the Display: Fail\r\n");
//	}
//	HAL_UART_Transmit(&uart, (uint8_t*)msg, size, HAL_MAX_DELAY); memset(msg, 0, (size_t) sizeof(msg));
//	HAL_Delay(10);

//	/// Read Registers
//	uint8_t registerData[52] = {0};
////	uint8_t registerAddr[5] = {0x82, 0x84, 0x86, 0x88, 0x8A};
//	uint8_t registerAddr = 0x00;
//	/// INDOOR_AQ_ICON Icon ON
//	size = sprintf((char*)msg, "Reading Display RAM: \r\n"); HAL_UART_Transmit(&uart, (uint8_t*)msg, size, HAL_MAX_DELAY); memset(msg, 0, (size_t) sizeof(msg));
//
//	if(lcd.readRAM(&registerAddr, registerData, sizeof(registerData)) == HAL_OK)
//	{
//		for(uint8_t i = 0; i < sizeof(registerData); i++)
//		{
//			size = sprintf((char*)msg, "Address: %d\t Data: 0x%x\n", i, registerData[i]);
//			HAL_UART_Transmit(&uart, (uint8_t*)msg, size, HAL_MAX_DELAY); memset(msg, 0, (size_t) sizeof(msg));
//			HAL_Delay(10);
//		}
//	}
//	else
//	{
//	  size = sprintf((char*)msg, "Failed");
//	}
//	//HAL_UART_Transmit(&uart, (uint8_t*)msg, size, HAL_MAX_DELAY); memset(msg, 0, (size_t) sizeof(msg));
//	HAL_Delay(10);

//weather = lcd.MOON_ICON;

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
//  	lcd.blinkDisplay(0x02);
  while (1)
  {


	  for(float i = -10.1; i <= 200.1; i = i + (float)(0.1))
	  {

		  if(i >= 0)
		  {
			  lcd.hubBatteryStatus((uint8_t)i);

			  lcd.nodeBatteryStatus((uint8_t)i);

			  lcd.nodeRfSignals((uint8_t)i);

			  lcd.printNodeNumber((uint8_t)i);
		  }

		  if(((uint8_t)i%10) == 0)
		  {
			  degree = lcd.degreeCelcius;
		  }
		  else if(((uint8_t)i%5) == 0)
		  {
			  degree = lcd.degreeFahrenheit;
		  }
		  lcd.printHubTemperature(i, degree);
		  lcd.printNodeTemperature(i, degree);
//			MOON_ICON,
//			STARS_ICON,
//			SNOWY_CLOUD_ICON,
//			SNOW_ICON,
//			SUNNY_ICON,
//			PARTIALY_SUNNY_ICON,
//			RAINY_CLOUD_ICON,
//			RAIN_ICON,
//			THUNDER_ICON
		  switch(((uint8_t)i%9))
		  {
		  case 8:
			  weather = lcd.MOON_ICON;
			  weekday = lcd.noDay;
			  break;
		  case 7:
			  weather = lcd.STARS_ICON;
			  weekday = lcd.noDay;
			  break;
		  case 6:
			  weather = lcd.SNOWY_CLOUD_ICON;
			  weekday = lcd.Sunday;
			  break;
		  case 5:
			  weather = lcd.SNOW_ICON;
			  weekday = lcd.Saturday;
			  break;
		  case 4:
			  weather = lcd.SUNNY_ICON;
			  weekday = lcd.Friday;
			  break;
		  case 3:
			  weather = lcd.PARTIALY_SUNNY_ICON;
			  weekday = lcd.Thursday;
			  break;
		  case 2:
			  weather = lcd.RAINY_CLOUD_ICON;
			  weekday = lcd.Wednesday;
			  break;
		  case 1:
			  weather = lcd.RAIN_ICON;
			  weekday = lcd.Tuesday;
			  break;
		  case 0:
			  weather = lcd.THUNDER_ICON;
			  weekday = lcd.Monday;
			  break;
		  default:
			  weather = lcd.SUNNY_ICON;
		  }
		  lcd.printOutdoorWeather(weather, true);

		  if(i>=0)
		  {
			  //if(i < (float)25.5)
				  {

					  lcd.printHubHumidity((uint16_t)(i));

					  lcd.printNodeHumidity((uint16_t)(i));

					  lcd.printSunriseTime((uint16_t)(i), (uint16_t)(i));
					  lcd.printSunsetTime((uint16_t)(i), (uint16_t)(i));

					  lcd.printDate((uint16_t)(i), (uint16_t)(i), weekday);

					  if(((uint8_t)(i)) < 12)
						  lcd.printTime((uint16_t)(i), (uint16_t)(i), lcd.AM);
					  else if(((uint8_t)(i)) <= 24)
						  lcd.printTime((uint16_t)(i), (uint16_t)(i), lcd.PM);
					  else
						  lcd.printTime((uint16_t)(i), (uint16_t)(i), lcd.noMeridiem);
				  }

			  lcd.printIndoorAirQualityIndex((uint16_t)(i*10));

			  lcd.printIndoorCoLevel((uint16_t)(i*10));

			  lcd.printOutdoorAirQualityIndex((uint16_t)(i*10));

		  }
		  HAL_Delay(100);
	  }
	  HAL_Delay(5000);
















//	  uint8_t serialRead = '\0';
//	  for(uint8_t i = 0; i < 52; i++)
//		  //for(uint8_t j = 0; j < 8; j++)
//		  {
//			  up:
//			  HAL_StatusTypeDef status = HAL_UART_Receive(&uart, &serialRead, 1, 100);
//
//			  if((status == HAL_OK) && (serialRead == '0'))
//			  {
//				  HAL_StatusTypeDef i2cStatus = lcd.icon(i, true);
//
//				  if(i2cStatus == HAL_OK)
//				  {
//					  size = sprintf((char*)msg, "\nIcon: %d\tSuccess\r\n", i);
//				  }
//				  else
//				  {
//					  size = sprintf((char*)msg, "Failed Segment Update...\r\n");
//				  }
//				  HAL_UART_Transmit(&uart, (uint8_t*)msg, size, HAL_MAX_DELAY); memset(msg, 0, (size_t) sizeof(msg));
//				  HAL_Delay(10);
//			  }
//			  else
//			  {
//				  HAL_Delay(200);
//				  goto up;
//			  }
//
//			  HAL_Delay(10);
//		  }
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
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL4;
  RCC_OscInitStruct.PLL.PREDIV = RCC_PREDIV_DIV1;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_I2C1;
  PeriphClkInit.I2c1ClockSelection = RCC_I2C1CLKSOURCE_HSI;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.Timing = 0x2000090E;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Analogue filter
  */
  if (HAL_I2CEx_ConfigAnalogFilter(&hi2c1, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Digital filter
  */
  if (HAL_I2CEx_ConfigDigitalFilter(&hi2c1, 0) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief I2C2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C2_Init(void)
{

  /* USER CODE BEGIN I2C2_Init 0 */

  /* USER CODE END I2C2_Init 0 */

  /* USER CODE BEGIN I2C2_Init 1 */

  /* USER CODE END I2C2_Init 1 */
  hi2c2.Instance = I2C2;
  hi2c2.Init.Timing = 0x00707CBB;
  hi2c2.Init.OwnAddress1 = 0;
  hi2c2.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c2.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c2.Init.OwnAddress2 = 0;
  hi2c2.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
  hi2c2.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c2.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c2) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Analogue filter
  */
  if (HAL_I2CEx_ConfigAnalogFilter(&hi2c2, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Digital filter
  */
  if (HAL_I2CEx_ConfigDigitalFilter(&hi2c2, 0) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C2_Init 2 */

  /* USER CODE END I2C2_Init 2 */

}

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_64;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 7;
  hspi1.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
  hspi1.Init.NSSPMode = SPI_NSS_PULSE_ENABLE;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  huart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief USART3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART3_UART_Init(void)
{

  /* USER CODE BEGIN USART3_Init 0 */

  /* USER CODE END USART3_Init 0 */

  /* USER CODE BEGIN USART3_Init 1 */

  /* USER CODE END USART3_Init 1 */
  huart3.Instance = USART3;
  huart3.Init.BaudRate = 9600;
  huart3.Init.WordLength = UART_WORDLENGTH_8B;
  huart3.Init.StopBits = UART_STOPBITS_1;
  huart3.Init.Parity = UART_PARITY_NONE;
  huart3.Init.Mode = UART_MODE_TX_RX;
  huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart3.Init.OverSampling = UART_OVERSAMPLING_16;
  huart3.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart3.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART3_Init 2 */

  /* USER CODE END USART3_Init 2 */

}

/**
  * @brief USART4 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART4_UART_Init(void)
{

  /* USER CODE BEGIN USART4_Init 0 */

  /* USER CODE END USART4_Init 0 */

  /* USER CODE BEGIN USART4_Init 1 */

  /* USER CODE END USART4_Init 1 */
  huart4.Instance = USART4;
  huart4.Init.BaudRate = 9600;
  huart4.Init.WordLength = UART_WORDLENGTH_8B;
  huart4.Init.StopBits = UART_STOPBITS_1;
  huart4.Init.Parity = UART_PARITY_NONE;
  huart4.Init.Mode = UART_MODE_TX_RX;
  huart4.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart4.Init.OverSampling = UART_OVERSAMPLING_16;
  huart4.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart4.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart4) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART4_Init 2 */

  /* USER CODE END USART4_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, Buzzer_Pin|RF_nSEL_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, LCD_Backlight_Pin|LED_RF_Pin|LED_CO_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : nLCD_Backlight_btn_Pin */
  GPIO_InitStruct.Pin = nLCD_Backlight_btn_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(nLCD_Backlight_btn_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : Buzzer_Pin RF_nSEL_Pin */
  GPIO_InitStruct.Pin = Buzzer_Pin|RF_nSEL_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PA5 PA8 */
  GPIO_InitStruct.Pin = GPIO_PIN_5|GPIO_PIN_8;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : RF_nIRQ_Pin */
  GPIO_InitStruct.Pin = RF_nIRQ_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(RF_nIRQ_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : PB1 PB2 PB12 PB8
                           PB9 */
  GPIO_InitStruct.Pin = GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_12|GPIO_PIN_8
                          |GPIO_PIN_9;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : LCD_Backlight_Pin LED_RF_Pin LED_CO_Pin */
  GPIO_InitStruct.Pin = LCD_Backlight_Pin|LED_RF_Pin|LED_CO_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : PWR_State_D3_Pin PWR_State_D2_Pin PWR_State_D1_Pin nRF_Config_btn_Pin */
  GPIO_InitStruct.Pin = PWR_State_D3_Pin|PWR_State_D2_Pin|PWR_State_D1_Pin|nRF_Config_btn_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

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
