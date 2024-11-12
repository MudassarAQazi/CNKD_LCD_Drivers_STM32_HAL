// DisplayDriver_CNKD1103_HT16C24A.h

/**
*	This Driver file is Sole Property of the company named "bluell.se".
*   This display driver covers All the functionality of the CNKD1103 LCD
*   connected with HT16C24AH RAM for the LCD Segments driver.
*/
//#include<Arduino.h>
#include "stm32f0xx_hal.h"


#ifdef debug
#include <stdio.h>  // For s_print_f function
#include "string.h"	// For string manipulation
#endif

#ifndef INC_DisplayDriver_CNKD1103_HT16C24A_H_
#define INC_DisplayDriver_CNKD1103_HT16C24A_H_

class DisplayDriver_CNKD1103_HT16C24A {
public:

	// Object of the LCD Display
//	DisplayDriver_CNKD1103_HT16C24A(
//			I2C_HandleTypeDef&		hi2c,
//			const uint16_t&			address,
//			UART_HandleTypeDef&		huart); //uint8_t address););//uint8_t address);

	// Enumeration for Day Selection
	enum weekday_t
	{
		Monday,
		Tuesday,
		Wednesday,
		Thursday,
		Friday,
		Saturday,
		Sunday,
		noDay
	};

	enum meridiem_t
	{
		AM,
		PM,
		noMeridiem
	};

	enum degree_t
	{
		degreeCelcius,
		degreeFahrenheit,
		noDegree
	};

	enum weather_t
	{
		MOON_ICON,
		STARS_ICON,
		SNOWY_CLOUD_ICON,
		SNOW_ICON,
		SUNNY_ICON,
		PARTIALY_SUNNY_ICON,
		RAINY_CLOUD_ICON,
		THUNDER_ICON,
		RAIN_ICON
	};

	enum icon_t
	{
		HUB_HOUSE_ICON,
		HUB_BATT_ICON,
		INDOOR_ICON,
		INDOOR_AQ_ICON,
		NODE_HOUSE_ICON,
		NODE_OUT_ICON,
		NODE_BATT_ICON,
		HUB_THERMO_ICON,
//				HUB_DEG_F_ICON,
//				HUB_DEG_C_ICON,
		HUB_AQI_ICON,
//				GOOD_AQI_ICON,
//				MODERATE_AQI_ICON,
//				USG_AQI_ICON,
//				POOR_AQI_ICON,
//				V_POOR_AQI_ICON,
//				HAZARD_AQI_ICON,
		PM2P5_ICON,
		NODE_THERMO_ICON,
//				NODE_DEG_F_ICON,
//				NODE_DEG_C_ICON,
		CO_PPM_ICON,
		HUB_HUMID_ICON,
//				DRY_HUB_HUMID_ICON,
//				COMFORT_HUB_HUMID_ICON,
//				WET_HUB_HUMID_ICON,
		PERCENT_HUB_HUMID_ICON,
		FORECAST_ICON,
//				MOON_ICON,
//				STARS_ICON,
//				SNOWY_CLOUD_ICON,
//				SNOW_ICON,
//				SUNNY_ICON,
//				PARTIALY_SUNNY_ICON,
//				RAINY_CLOUD_ICON,
//				RAIN_ICON,
//				THUNDER_ICON,
		AQI_OUT_ICON,
		SUNRISE_ICON,
		SUNSET_ICON,
		NODE_HUMID_ICON,
//				DRY_NODE_HUMID_ICON,
//				COMFORT_NODE_HUMID_ICON,
//				WET_NODE_HUMID_ICON,
		PERCENT_NODE_HUMID_ICON,
		D_ICON,
		M_ICON,
//				AM_ICON,
//				PM_ICON,
		DAY_ICON
	}; /// Total of 23 Icons. //50 Old

	/*
		Function to initialize the I2C Port, I2C Address, and Debug UART Port of the display
		- 	LCD I2C Port
		-	LCD I2C Address
		-	Debug UART
	*/
	HAL_StatusTypeDef lcdPortInit(I2C_HandleTypeDef& hi2c, const uint16_t& address, UART_HandleTypeDef&	 huart);

	/*
		Function to initialize the display
		- LCD I2C Address
		-
	*/
	HAL_StatusTypeDef displayInit();

	/*
		LCD display off address 80H
		- { 0	0	0	0	Duty1	Bias1	Duty0	Bias0 }	LSB
		Drive	Mode Selection
		[Mode]	[Duty]
		- 0		 1/4
		- 1		 1/8
		- 2		 1/16
	*/
	HAL_StatusTypeDef dutyOfDisplay(uint8_t mode);

	/*
		LCD display off address 80H
		- { 0	0	0	0	Duty1	Bias1	Duty0	Bias0 }	LSB
		Select		Bias the Display
		[Value]		[Bias]
		 - 0		  1/3
		 - 1		  1/4
		 - 2		  1/5
	*/
	HAL_StatusTypeDef biasOfDisplay(uint8_t value);

	/*
		Function to Disable/Enable Display Driver IC (AiP16C22)
		- { 0	0	0	0	0	0	S	E }	LSB
		[Enable]   [Internal System Oscillator(S)]
		 - 0         off
		 - 1         on
	*/
	HAL_StatusTypeDef enableDisplayDriver(bool enable);

	/*
		Function to turn ON/OFF the Display
		- { 0	0	0	0	0	0	S	E }	LSB
		[Enable]   [LCD Display]
		 - 0         off
		 - 1         on
	*/
	HAL_StatusTypeDef display(bool enable);

	/*
		Function to Select Frame Frequency of Display
		- { 0	0	0	0	0	0	0	F }	LSB
		[Frequency]	[Frame Frequency]
		 - 0         80 Hz
		 - 1         160 Hz
	*/
	HAL_StatusTypeDef frequency(bool freq);

	/*
		Function to Blink Display
		- { 0	0	0	0	0	0	BK1	BK0 }	LSB
		[Mode]     [Blinking Frequency]
		- 0          Blink off
		- 1          2 Hz
		- 2          1 Hz
		- 3          0.5 Hz
		-
	*/
	HAL_StatusTypeDef blinkDisplay(uint8_t mode);

	/*
		Function to Select SEG/VLCD Settings
		- { 0	0	DE	VE	DA3	DA2	DA1	DA0 }	LSB
		[DE]    [VE]    [Pin Selected]  [Internal Voltage Adjustment]
		- 0      0        VLCD Pin          off
		- 0      1        VLCD Pin          on
		- 1      0        SEG Pin           off
		- 1      1        SEG Pin           on
		-
	*/
	HAL_StatusTypeDef segVlcdSetting(uint8_t settings);
	
	/*  Function to set Brightness of the LCD
		[Bright]    [Display]
		- 0          Low Brightness
		- .          .
		- .          .
		- 15         Full Brightness
		-
	*/
	HAL_StatusTypeDef brightness(uint8_t bright);

	/*
		Function to clear the whole screen
		- Clear all the Memory Map and write it to the Screen.
	*/
	HAL_StatusTypeDef displayClear();

	/*
		Function to clear the whole screen
		- Fill all the Memory Map and write it to the Screen.
	*/
	HAL_StatusTypeDef displayFill();
	/*
		Function to Set/Reset Division Lines
		- Enables/Disables Lines Separators..
	*/
	HAL_StatusTypeDef linesEnable(bool enable);

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
		/- HUB_DEG_F_ICON			=   8	(uint8_t)
		/- HUB_DEG_C_ICON			=   9	(uint8_t)
		- HUB_AQI_ICON				=	10	(uint8_t)
		/- GOOD_AQI_ICON			=	11	(uint8_t)
		/- MODERATE_AQI_ICON		=	12	(uint8_t)
		/- USG_AQI_ICON				=	13	(uint8_t)
		/- POOR_AQI_ICON			=	14	(uint8_t)
		/- V_POOR_AQI_ICON			=	15	(uint8_t)
		/- HAZARD_AQI_ICON			=	16	(uint8_t)
		- PM2P5_ICON				=	17	(uint8_t)
		- NODE_THERMO_ICON			=	18	(uint8_t)
		/- NODE_DEG_F_ICON			=   19  (uint8_t)
		/- NODE_DEG_C_ICON			=   20  (uint8_t)
		- CO_PPM_ICON				=	21	(uint8_t)
		- HUB_HUMID_ICON			=	22	(uint8_t)
		/- DRY_HUB_HUMID_ICON		=	23	(uint8_t)
		/- COMFORT_HUB_HUMID_ICON	=	24	(uint8_t)
		/- WET_HUB_HUMID_ICON		=	25	(uint8_t)
		- PERCENT_HUB_HUMID_ICON	=	26	(uint8_t)
		- FORECAST_ICON				=	27	(uint8_t)
		/- MOON_ICON				=	28	(uint8_t)
		/- STARS_ICON				=	29	(uint8_t)
		/- SNOWY_CLOUD_ICON			=	30	(uint8_t)
		/- SNOW_ICON				=	31	(uint8_t)
		/- SUNNY_ICON				=	32	(uint8_t)
		/- PARTIALY_SUNNY_ICON		=	33	(uint8_t)
		/- RAINY_CLOUD_ICON			=	34	(uint8_t)
		/- RAIN_ICON				=	35	(uint8_t)
		/- THUNDER_ICON				=	36	(uint8_t)
		- AQI_OUT_ICON				=	37	(uint8_t)
		- SUNRISE_ICON				=	38	(uint8_t)
		- SUNSET_ICON				=	39	(uint8_t)
		- NODE_HUMID_ICON			=	40	(uint8_t)
		/- DRY_NODE_HUMID_ICON		=	41	(uint8_t)
		/- COMFORT_NODE_HUMID_ICON	=	42	(uint8_t)
		/- WET_NODE_HUMID_ICON		=	43	(uint8_t)
		- PERCENT_NODE_HUMID_ICON	=	44	(uint8_t)
		- D_ICON					=	45	(uint8_t)
		- M_ICON					=	46	(uint8_t)
		/- AM_ICON					=	47	(uint8_t)
		/- PM_ICON					=	48	(uint8_t)
		- DAY_ICON					=	49	(uint8_t)
		-
	*/
	HAL_StatusTypeDef icon(uint8_t iconType, bool enable);

	/*  Function to set battery cells status
		[Cells]     [Status]
		- 0          Empty
		- .          .
		- .          .
		- 5          Full
		-
	*/
	HAL_StatusTypeDef hubBatteryStatus(uint8_t batteryCells);

	/*
		Function to print Hub Temperature Value on the display
		- (Temperature)
		- Address of Temperature Value,
		-
	*/
	HAL_StatusTypeDef printHubTemperature(float temperatureValue, degree_t degree);

	/*
		Function to print Hub Humidity Value on the display
		- (Humidity)
		- Address of Humidity Value,
		-
	*/
	HAL_StatusTypeDef printHubHumidity(uint8_t humidityValue);

	/*
		Function to print Dust/Air Quality Value on the display
		- (Humidity)
		- Address of Humidity Value,
		-
	*/
	HAL_StatusTypeDef printIndoorAirQualityIndex(uint16_t airQuality);

	/*
		Function to print Dust/Air Quality Value on the display
		- (Humidity)
		- Address of Humidity Value,
		-
	*/
	HAL_StatusTypeDef printIndoorCoLevel(uint16_t coLevel);

	/*
			Function to print Outdoor Node Number on the display
			- (Node_Number)
			- Address of Node Number,
			-
	*/
	HAL_StatusTypeDef printNodeNumber(uint8_t nodeNumber);

	/*  Function to set battery cells status
		[Signals]	[Strength]
		- 0          Weak
		- .          .
		- .          .
		- 4          Strong
		-
	*/
	HAL_StatusTypeDef nodeRfSignals(uint8_t strength);

	/*  Function to set battery cells status
		[Cells]     [Status]
		- 0          Empty
		- .          .
		- .          .
		- 5          Full
		-
	*/
	HAL_StatusTypeDef nodeBatteryStatus(uint8_t batteryCells);

	
	/*
		Function to print Node Temperature Value on the display
		- (Temperature)
		- Address of Temperature Value,
		-
	*/
	HAL_StatusTypeDef printNodeTemperature(float temperatureValue, degree_t degree);

	/*
		Function to print Node Humidity Value on the display
		- (Humidity)
		- Address of Node Humidity Value,
		-
	*/
	HAL_StatusTypeDef printNodeHumidity(uint8_t humidityValue);

	/*
		Function to print Outdoor Weather on the display
		- (Weather)
		-
	*/
	HAL_StatusTypeDef printOutdoorWeather(uint8_t weather, bool enable);

	/*
		Function to print Dust/Air Quality Value on the display
		- (Humidity)
		- Address of Humidity Value,
		-
	*/
	HAL_StatusTypeDef printOutdoorAirQualityIndex(uint16_t airQuality);

	/*
			Function to print Sunrise Time on the display
			- (Hour, Minute)
			- Address of Hour,
			- Address of Minute
	*/
	HAL_StatusTypeDef printSunriseTime(uint8_t hours, uint8_t minutes);

	/*
			Function to print Sunset Time on the display
			- (Hour, Minute)
			- Address of Hour,
			- Address of Minute
	*/
	HAL_StatusTypeDef printSunsetTime(uint8_t hours, uint8_t minutes);
	
	/*
			Function to print Date on the display
			- (Day, Month, Day_Name)
			- Address of Day,
			- Address of Month,
			- Address of DayName
	*/
	HAL_StatusTypeDef printDate(uint8_t day, uint8_t month, uint8_t dayName);

	/*
			Function to print Weekday Name on the display
			- Day Enumeration
			- Address of the Weekday to 14 Segments Array.
			-
	*/
	HAL_StatusTypeDef dayTo14Segment(uint8_t day, uint8_t (&dayDisplay)[6]);

	/*
			Function to print Time on the display
			- (Hour, Minute, MERIDIEM)
			- Address of Hour,
			- Address of Minute,
			- Address of MERIDIEM
	*/
	HAL_StatusTypeDef printTime(uint8_t hours, uint8_t minutes, meridiem_t meridiem);

	/*
			Function to print Time on the display
			- (Hour, Minute, MERIDIEM)
			- Read Register Address Pointer,
			- Read Data Pointer,
			- Size of the read Data.
	*/
	HAL_StatusTypeDef readRegister(const uint8_t& regAddr, uint8_t& regData, size_t size);

	/*
			Function to read "Selective RAM" contents
			- Pointer to Register Address to be read,
			- Pointer to the Register that is used to Store read Data,
			- Size of the Data Register.
			-
	*/
	HAL_StatusTypeDef readRAM(const uint8_t& regAddr, uint8_t& regData, size_t size);
	
//	HAL_StatusTypeDef writeDataToI2C(CONST uint8_t* regAddr, uint8_t* regData, size_t size);

};

#endif // DisplayDriver_CNKD1103_HT16C24AH
