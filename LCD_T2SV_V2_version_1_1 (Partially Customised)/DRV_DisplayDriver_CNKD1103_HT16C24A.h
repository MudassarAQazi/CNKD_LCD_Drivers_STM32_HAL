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

const uint8_t memSize = 52; // 52 Bytes of LCD Segments Data.

class DisplayDriver_CNKD1103_HT16C24A {
public:

	// Object of the LCD Display
	DisplayDriver_CNKD1103_HT16C24A(
			I2C_HandleTypeDef&		hi2c,
			const uint16_t&			address,
			UART_HandleTypeDef&		huart); //uint8_t address););//uint8_t address);

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
		- LCD I2C Address
		-
	*/
	HAL_StatusTypeDef lcdPortInit();//I2C_HandleTypeDef* hi2c, const uint16_t* address, UART_HandleTypeDef* UART);

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
		/- GOOD_AQI_ICON				=	11	(uint8_t)
		/- MODERATE_AQI_ICON			=	12	(uint8_t)
		/- USG_AQI_ICON				=	13	(uint8_t)
		/- POOR_AQI_ICON				=	14	(uint8_t)
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
		/- MOON_ICON					=	28	(uint8_t)
		/- STARS_ICON				=	29	(uint8_t)
		/- SNOWY_CLOUD_ICON			=	30	(uint8_t)
		/- SNOW_ICON					=	31	(uint8_t)
		/- SUNNY_ICON				=	32	(uint8_t)
		/- PARTIALY_SUNNY_ICON		=	33	(uint8_t)
		/- RAINY_CLOUD_ICON			=	34	(uint8_t)
		/- RAIN_ICON					=	35	(uint8_t)
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
	HAL_StatusTypeDef dayTo14Segment(uint8_t day, uint8_t* dayDisplay);

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
	HAL_StatusTypeDef readRegister(const uint8_t* regAddr, uint8_t* regData, size_t size);

	/*
			Function to read "Selective RAM" contents
			- Pointer to Register Address to be read,
			- Pointer to the Register that is used to Store read Data,
			- Size of the Data Register.
			-
	*/
	HAL_StatusTypeDef readRAM(const uint8_t* regAddr, uint8_t* regData, size_t size);
	
//	HAL_StatusTypeDef writeDataToI2C(CONST uint8_t* regAddr, uint8_t* regData, size_t size);

private:
	/// Memory Map of the LCD Screen
	/*
		Formating for AT16C24A for CNKD1103 LCD
		-
		- memoryMap[0]      {	S25		S24		S23		S22		S27		S51		S50		S29	} LSB	1. Hub Humidity 'Humid Icon', 'Dry|Comfort|Wet Icon'.							2. 'Forecast Icon', 'Sunny Icon', 'Moon Icon', and 'Stars Icon'.
		- memoryMap[1]      {	13D		13E		13C		13G		13F		13B		13A		--	}		1. Hub Humidity 'Tenth Digit'.
		- memoryMap[2]      {	14D		14E		14C		14G		14F		14B		14A		S26	}		1. Hub Humidity 'Unit Digit', and '% Icon'.
		- memoryMap[3]      {	28D		28E		28C		28G		28F		28B		28A		S39	}		1. Date 'Day Tenth Digit', 'D Icon'.
		- memoryMap[4]      {	29D		29E		29C		29G		29F		29B		29A		L6	}		1. Date 'Day Unit Digit'.																					3. Line 'L6'.
		- memoryMap[5]      {	30D		30E		30C		30G		30F		30B		30A		D9	}		1. Date 'Month Tenth Digit', '- Icon'.
		- memoryMap[6]      {	31D		31E		31C		31G		31F		31B		31A		S40	}		1. Date 'Month Unit Digit', 'M Icon'.
		- memoryMap[7]      {	32D		32E		32C		32G		32F		32B		32A		--	}		1. Time 'Hours Tenth Digit'.
		- memoryMap[8]      {	33D		33E		33C		33G		33F		33B		33A		D10	}		1. Time 'Hours Unit Digit', and ': Icon'.
		- memoryMap[9]      {	34D		34E		34C		34G		34F		34B		34A		S42	}		1. Time 'Minutes Tenth Digit', and 'PM Icon'.
		- memoryMap[10]     {	35D		35E		35C		35G		35F		35B		35A		S41	}		1. Time 'Minutes Unit Digit', and 'AM Icon'.
		- memoryMap[11]     {	15D		15E		15C		15G		15F		15B		15A		L7	}		1. AQI Out 'Hundredth Digit'.																				3. Line 'L7'.
		- memoryMap[12]     {	16D		16E		16C		16G		16F		16B		16A		L9	}		1. AQI Out 'Tenth Digit'.																					3. Line 'L9'.
		- memoryMap[13]     {	17D		17E		17C		17G		17F		17B		17A		S28	}		1. AQI Out 'Unit Digit'.														2. 'Snowy Cloud Icon'.
		- memoryMap[14]     {	22D		22E		22C		22G		22F		22B		22A		S33	}		1. Sunset 'Hours Tenth Digit'.													2. 'Sunset Icon'.
		- memoryMap[15]     {	23D		23E		23C		23G		23F		23B		23A		S31	}		1. Sunset 'Hours Unit Digit'.													2. 'AQI Out Icon'.
		- memoryMap[16]     {	24D		24E		24C		24G		24F		24B		24A		D8	}		1. Sunset 'Minutes Tenth Digit'.												2. ': Icon'.
		- memoryMap[17]     {	25D		25E		25C		25G		25F		25B		25A		S32	}		1. Sunset 'Minutes Unit Digit'.													2. 'Sunrise Icon'.
		- memoryMap[18]     {	18D		18E		18C		18G		18F		18B		18A		S44	}		1. Sunrise 'Hours Tenth Digit'.													2. 'Snow Icon'.
		- memoryMap[19]     {	19D		19E		19C		19G		19F		19B		19A		S46	}		1. Sunrise 'Hours Unit Digit'.													2. 'Prtialy Sunny Icon'.
		- memoryMap[20]     {	20D		20E		20C		20G		20F		20B		20A		D7	}		1. Sunrise 'Minutes Tenth Digit'.												2. ': Icon'.
		- memoryMap[21]     {	21D		21E		21C		21G		21F		21B		21A		S45	}		1. Sunrise 'Minutes Unit Digit'.												2. 'Rain Icon'.
		- memoryMap[22]     {	L8		L10		S37		S36		S35		S34		S49		--	}		1. Node Humidity 'Humid Icon', 'Dry|Comfort|Wet Icons', and 'Thunder Icon'.									3. Line 'L8', and 'L10'.
		- memoryMap[23]     {	26D		26E		26C		26G		26F		26B		26A		S30	}		1. Node Humidity 'Tenth Digit'.													2. Rainy Cloud Icon.
		- memoryMap[24]     {	27D		27E		27C		27G		27F		27B		27A		S38	}		1. Node Humidity 'Unit Digit' and '% Sign'.
		- memoryMap[25]     {	--		36A		36F		36H		36G		36E		36L		36M	}		1. Day '1st Digit Part-2'.
		- memoryMap[26]     {	--		36I		36J		36B		36K		36C		36N		36D	}		1. Day '1st Digit Part-1'.
		- memoryMap[27]     {	--		37A		37F		37H		37G		37E		37L		37M	}		1. Day '2nd Digit Part-2'.
		- memoryMap[28]     {	--		37I		37J		37B		37K		37C		37N		37D	}		1. Day '2nd Digit Part-1'.
		- memoryMap[29]     {	S43		38A		38F		38H		38G		38E		38L		38M	}		1. Day '3rd Digit Part-2'.														2. 'Day Icon'.
		- memoryMap[30]     {	--		38I		38J		38B		38K		38C		38N		38D	}		1. Day '3rd Digit Part-1'.
		- memoryMap[31]     {	39A		39B		39F		39G		39C		39E		39D		S5	}		1. Node 'Node Number'.															2. 'Out House Icon'.
		- memoryMap[32]     {	--		--		X1		X2		X3		X4		X5		S6	}		1. Node 'RF Signals'.															2. 'Out Icon'.
		- memoryMap[33]     {	T8		T9		T10		T11		T12		T13		T14		L2	}		1. Node 'Battery Cells'.																					3. Line 'L2'.
		- memoryMap[34]     {	D6		12D		12E		12C		12G		12F		12B		12A	}		1. Node Temperature 'Decimal Digit', and 'Decimal Point'.
		- memoryMap[35]     {	--		--		--		--		--		--		S21		S20	}		1. Node Temperature 'DegreeFahrenheit', and 'DegreeCelsius' Signs.
		- memoryMap[36]     {	L5		11D		11E		11C		11G		11F		11B		11A	}		1. Node Temperature 'Unit Digit'.																			3. Line 'L5'.
		- memoryMap[37]     {	--		10D		10E		10C		10G		10F		10B		10A	}		1. Node Temperature 'Tenth Digit', and 'Decimal Point'.
		- memoryMap[38]     {	--		--		--		--		D4		D5		S19		L11	}		1. Node Temperature 'ThermoIcon', 'Negative Sign', and 'Hundredth Position'.								3. Line 'L11'.
		- memoryMap[39]     {	L4		9D		9E		9C		9G		9F		9B		9A	}		1. Hub 'CO Unit Digit'.																						3. Line 'L4'.
		- memoryMap[40]     {	S12		8D		8E		8C		8G		8F		8B		8A	}		1. Hub 'CO Tenth Digit'.														2. AQI Indoor 'Good Icon'.
		- memoryMap[41]     {	S15		7D		7E		7C		7G		7F		7B		7A	}		1. Hub 'CO Hundredth Digit'.													2. 'AQI Icon'.
		- memoryMap[42]     {	--		6D		6E		6C		6G		6F		6B		6A	}		1. Hub 'AQI Unit Digit'.
		- memoryMap[43]     {	S47		5D		5E		5C		5G		5F		5B		5A	}		1. Hub 'AQI Tenth Digit'.														2. 'CO Icon'.
		- memoryMap[44]     {	S10		4D		4E		4C		4G		4F		4B		4A	}		1. Hub 'AQI Hundredth Digit'.													2. 'PM2.5 Icon'.
		- memoryMap[45]     {	S16		S17		S18		S14		S13		S2		S3		--	}		1. Hub 'Indoor Icon', 'Indoor Air Quality Icon', AQI Indoor 'Moderate|USG|Poor|Very Poor|Hazardous Icon'.
		- memoryMap[46]     {	--		T1		T2		T3		T4		T5		T6		T7	}		1. Hub 'Battery Cells'.
		- memoryMap[47]     {	L12		3D		3E		3C		3G		3F		3B		3A	}		1. Hub Temperature 'Decimal Digit'.																			3. Line 'L12'.
		- memoryMap[48]     {	--		--		--		--		--		--		S9		S8	}		1. Hub Temperature 'DegreeFahrenheit', and 'DegreeCelsius' Signs.
		- memoryMap[49]     {	D3		2D		2E		2C		2G		2F		2B		2A	}		1. Hub Temperature 'Tenth Digit', and 'Decimal Point'.
		- memoryMap[50]     {	L3		1D		1E		1C		1G		1F		1B		1A	}		1. Hub Temperature 'Unit Digit'.																			3. Line 'L3'.
		- memoryMap[51]     {	--		--		--		D1		D2		S7		L1		S1	}		1. Hub Temperature 'ThermoIcon', 'Negative Sign', and 'Hundredth Position'.	2. 'In House Icon'.			3. Line 'L1'.
		-
	*/
	uint8_t memoryMap[memSize] = {
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00
	}; /// 52 Bytes of LCD Formating Data.

	/// Communication Sequence
	//		3-Bytes are required to Setup Successful Data Read and Write Operation.
	//		1.	Slave I2C Address (With Write Mode).
	//		2.	Command Byte.
	//		3.	Register Address.

	/// LCD I2C Address storage for use after initialization
	uint16_t	i2cReadAddress		=	0x0000;
	uint16_t	i2cWriteAddress		=	0x0000;
	uint8_t		commandByte			=	0x80;
	uint8_t		addressPointer		=	0x00;

	UART_HandleTypeDef	Uart;
	I2C_HandleTypeDef	i2cPort;
	uint16_t		i2cAddress;
	HAL_StatusTypeDef	i2cState	=	HAL_OK;

/// -------------------------------------------- Registers Addresses ---------------------------------------------
	
	/// Control Registers Addresses
	const uint8_t
		driveModeRegAddress		=	0x82,
		systemModeRegAddress	=	0x84,
		framFrequencyRegAddress	=	0x86,
		blinkRegAddress			=	0x88,
		vlcdSegEnableAddress	=	0x8A,
		brightCtrlEnAddress		=	0x8A;

	/// Segments Registers Addresses
	const uint8_t

		hubBatteryAddress		=	0x2E,
		hubTempSignAddress		=	0x33,
		hubTempMsdAddress		=	0x33,
		hubTempPointAddress		=	0x31,
		hubDegreeSymbolsAddress	=	0x30,
		hubHumidityIconsAddress	=	0x00,

		nodeNumberAddress		=	0x1F,
		nodeRfSignalsAddress	=	0x20,
		nodeBatteryAddress		=	0x21,
		nodeTempSignAddress		=	0x26,
		nodeTempMsdAddress		=	0x26,
		nodeTempPointAddress	=	0x22,
		nodeDegreeSymbolsAddress=	0x23,
		nodeHumidityIconsAddress=	0x16,

		AMAddress				=	0x0A,
		PMAddress				=	0x09;

	
	/// Lines Location Addresses
	/*
		LCD Lines Separator Addresses
		- L1RegAddr		=	0x51,
		- L2RegAddr		=	0x33,
		- L3RegAddr		=	0x50,
		- L4RegAddr		=	0x39,
		- L5RegAddr		=	0x36,
		- L6RegAddr		=	0x04,
		- L7RegAddr		=	0x11,
		- L8RegAddr		=	0x22,
		- L9RegAddr		=	0x12,
		- L10RegAddr	=	0x22,
		- L11RegAddr	=	0x38,
		- L12RegAddr	=	0x47
		Total of 12 Lines Addresses.
	*/
	const uint8_t linesAddress[12] =
	{ 
		0x33, 0x21, 0x32, 0x27, 0x24,
		0x04, 0x0B, 0x16, 0x0C, 0x16,
		0x26, 0x2F
	};
	
	/// Icons Location Addresses
	/*
		Addresses for Icons
		- hubHouseIconAddr			=	0x51,
		- hubBatteryIconAddr		=	0x46,
		- indoorIconAddr			=	0x45,
		- indoorAQIconAddr			=	0x45,
		- nodeHouseIconAddr			=	0x31,
		- nodeIconAddr				=	0x32,
		- nodeBattIconAddr			=	0x33,
		- hubhermoIconAddr			=	0x51,
		~/- hubDegFIconAddr			=	0x48,
		~/- hubDegCIconAddr			=	0x48,
		- aqiIconAddr				=	0x41,
		~/- goodAqiIconAddr			=	0x40,
		~/- moderateAqiIconAddr		=	0x45,
		~/- usgAqiIconAddr			=	0x45,
		~/- poorAqiIconAddr			=	0x45,
		~/- vPoorAqiIconAddr			=	0x45,
		~/- hazardAqiIconAddr			=	0x45,
		- pm2p5IconAddr				=	0x44,
		- nodeThermoIconAddr		=	0x38,
		~/- nodeDegFIconAddr			=	0x35,
		~/- nodeDegCIconAddr			=	0x35,
		- coPpmIconAddr				=	0x43,
		- hubHumidIconAddr			=	0x0,
		~/- dryHubHumidIconAddr		=	0x0,
		~/- comfortHumidIconAddr		=	0x0,
		~/- webHubHumidIconAddr		=	0x0,
		- percentHubHumidIconAddr	=	0x2,
		- forcastIconAddr			=	0x0,
		~/- moonIconAddr				=	0x0,
		~/- starsIconAddr				=	0x0,
		~/- snowyCloudIconAddr		=	0x13,
		~/- snowIconAddr				=	0x18,
		~/- sunnyIconAddr				=	0x0,
		~/- partialySunnyIconAddr		=	0x19,
		~/- rainyCloudIconAddr		=	0x23,
		~/- thunderIconAddr			=	0x22,
		~/- rainIconAddr				=	0x21,
		- aqiOutIconAddr			=	0x15,
		- sunriseIconAddr			=	0x17,
		- sunsetIconAddr			=	0x14,
		- nodeHumidIconAddr			=	0x22,
		~/- dryNodeHumidIconAddr		=	0x22,
		~/- comfortNodeHumidIconAddr	=	0x22,
		~- wetNodeHumidIconAddr		=	0x22,
		- percentNodeHumidIconAddr	=	0x24,
		- dIconAddr					=	0x03,
		- mIconAddr					=	0x06,
		~/- amIconAddr				=	0x10,
		~/- pmIconAddr				=	0x09,
		- dayIconAddr				=	0x29
		Total of 50 Icon Addresses.
	*/
	const uint8_t iconAddress[50] =  
	{ 
		0x33,	0x2E,	0x2D,	0x2D,	0x1F,
		0x20,	0x21,	0x33,	//0x30,	0x30,
		0x29,	//0x28,	0x2D,	0x2D,	0x2D,
		//0x2D,	0x2D,
						0x2C,	0x26,	//0x23,
		//0x23,
				0x2B,	0x0,	//0x0,	0x0,
		//0x0,
				0x02,	0x0,	//0x0,	0x0,
		//0x0D,	0x12,	0x0,	0x13,	0x17,
		//0x16,	0x15,
						0x0F,	0x11,	0x0E,
		0x16,	//0x16,	0x16,	0x16,
										0x18,
		0x03,	0x06,	//0x0A,	0x09,
										0x1D
	};

	/// 7-Segments Addresses
	//	Hub Temperature
	const uint8_t hubTemperatureAddress[3] =
	{
		0x32,	0x31,	0x2F
	};

//	// Hub Degree Symbols
//	const uint8_t hubDegreeSymbolsAddress[2] =
//	{
//
//	};

	//	Hub Humidity
	const uint8_t hubHumidityAddress[2] = 
	{
		0x01,	0x02
	};

	//	Node Temperature
	const uint8_t nodeTemperatureAddress[3] =
	{
		0x25,	0x24,	0x22
	};

	//	Node Humidity
	const uint8_t nodeHumidityAddress[2] =
	{
		0x17,	0x18
	};

	//	Hub AQI
	const uint8_t hubAqiAddress[3] =
	{
		0x2C,	0x2B,	0x2A
	};

	//	Hub AQI Labels
	const uint8_t hubAqiIconsAddress[6] =
	{
		0x28,	0x2D,	0x2D,	0x2D,	0x2D,	0x2D
	};

	//	Hub CO
	const uint8_t hubCoAddress[3] =
	{
		0x29,	0x28,	0x27
	};

	//	AQI out
	const uint8_t aqiOutAddress[3] =
	{
		0x0B,	0x0C,	0x0D
	};

	//	Weather out Address
	const uint8_t weatherAddress[9] =
	{
		0x0,	0x0,	0x0D,	0x12,	0x0,
		0x13,	0x17,	0x16,	0x15
	};

	//	Sunrise Time
	const uint8_t sunriseTimeAddress[5] =
	{
		0x12,	0x13,	0x14,	0x14,	0x15
	};

	//	Sunset Time
	const uint8_t sunsetTimeAddress[5] =
	{
		0x0E,	0x0F,	0x10,	0x10,	0x11
	};

	//	Date
	const uint8_t dateAddress[5] =
	{
		0x03,	0x04,	0x05,	0x05,	0x06
	};

	//	Time
	const uint8_t timeAddress[5] =
	{
		0x07,	0x08,	0x08,	0x09,	0x0A
	};

	//	Weekday Digits
	const uint8_t weekdayAddress[6] =
	{
		0x19,	0x1A,	0x1B,	0x1C,	0x1D,	0x1E
	};

	/// ------------------------------------------------ Icons Masks -------------------------------------------------
	
	/// Control Function Masks
	/*
		Control Functions
		- {0	0	0	0	Duty1	Bias1	Duty0	Bias1	} LSB	82H
		- {0	0	0   0   0		0		S		E		} LSB	84H		System Mode
		- {0	0	0   0   0		0		0		F		} LSB	86H		Frame Frequency
		- {0	0	0   0   0		0		BK1		BK0		} LSB	88H		Blinking Frequency  
		- {0	0	DE  VE  DA3		DA2		DA1		DA0		} LSB	8AH
	*/
	const uint8_t
		BIAS_DISP_Mask				=	0x05,   // Use it for 82H	Bias Select
		DUTY_DISP_Mask				=	0x0A,   // Use it for 82H	Duty Select e.g. 1/8 for 8 COM's
		OSC_DISP_Mask				=	0x02,   // Use it for 84H	Oscillator Select
		OFF_DISP_Mask				=	0x01,   // Use it for 84H	LCD Display ON/OFF Select
		FREQ_DISP_Mask				=	0x01,   // Use it for 86H	LCD Display Update Frequency Select
		BLNK_DISP_Mask				=	0x03,   // Use it for 88H	Blinking
		BRIGT_DISP_Mask				=	0x0F,   // Use it for 8AH	VLCD output Voltage for Brightness
		IVA_DISP_EN_Mask			=	0x10,   // Use it for 8AH	Internal Voltage Adjustment OFF/ON
		IVA_VLCD_DISP_PIN_EN_Mask	=	0x30;   // Use it for 8AH	VLCD/Segment71 Select

	/// Icons & 7 Segments Masks
	/*
		Icons Masks for Turning an Icon ON or OFF.
		- HUB_HOUSE_ICON_Mask			=	0x01,	//	S1 Mask		->	Use it on memoryMap[51]
		- HUB_BATT_ICON_Mask			=	0x40,	//	T1 Mask		->	Use it on memoryMap[46]
		- INDOOR_ICON_Mask				=	0x04,	//	S2 Mask		->	Use it on memoryMap[45]
		- INDOOR_AQ_ICON_Mask			=	0x02,	//	S3 Mask		->	Use it on memoryMap[45]
		- NODE_HOUSE_ICON_Mask			=	0x01,	//	S5 Mask		->	Use it on memoryMap[31]
		- NODE_ICON_Mask				=	0x01,	//	S6 Mask		->	Use it on memoryMap[32]
		- NODE_BATT_ICON_Mask			=	0x80,	//	T8 Mask		->	Use it on memoryMap[33]
		- HUB_THERMO_ICON_Mask			=	0x04,	//	S7 Mask		->	Use it on memoryMap[51]
		- HUB_DEG_F_ICON_Mask			=	0x01,	//	S8 Mask		->	Use it on memoryMap[48]
		- HUB_DEG_C_ICON_Mask			=	0x02,	//	S9 Mask		->	Use it on memoryMap[48]
		- HUB_AQI_ICON_Mask				=	0x80,	//	S15 Mask	->	Use it on memoryMap[41]
		- GOOD_AQI_ICON_Mask			=	0x80,	//	S12 Mask	->	Use it on memoryMap[40]
		- MODERATE_AQI_ICON_Mask		=	0x08,	//	S13 Mask	->	Use it on memoryMap[45]
		- USG_AQI_ICON_Mask				=	0x10,	//	S14 Mask	->	Use it on memoryMap[45]
		- POOR_AQI_ICON_Mask			=	0x80,	//	S16 Mask	->	Use it on memoryMap[45]
		- V_POOR_AQI_ICON_Mask			=	0x40,	//	S17 Mask	->	Use it on memoryMap[45]
		- HAZARD_AQI_ICON_Mask			=	0x20,	//	S18 Mask	->	Use it on memoryMap[45]
		- PM2P5_ICON_Mask				=	0x80,	//	S10 Mask	->	Use it on memoryMap[44]
		- Node_THERMO_ICON_Mask			=	0x02,	//	S19 Mask	->	Use it on memoryMap[38]
		- Node_DEG_F_ICON_Mask			=	0x01,	//	S20 Mask	->	Use it on memoryMap[35]
		- Node_DEG_C_ICON_Mask			=	0x02,	//	S21 Mask	->	Use it on memoryMap[35]
		- CO_PPM_ICON_Mask				=	0x80,	//	S47 Mask	->	Use it on memoryMap[43]
		- HUB_HUMID_ICON_Mask			=	0x10,	//	S22 Mask	->	Use it on memoryMap[0]
		- DRY_HUB_HUMID_ICON_Mask		=	0x20,	//	S23 Mask	->	Use it on memoryMap[0]
		- COMFORT_HUB_HUMID_ICON_Mask	=	0x40,	//	S24 Mask	->	Use it on memoryMap[0]
		- WET_HUB_HUMID_ICON_Mask		=	0x80,	//	S25 Mask	->	Use it on memoryMap[0]
		- PERCENT_HUB_HUMID_ICON_Mask	=	0x01,	//	S26 Mask	->	Use it on memoryMap[2]
		- FORECAST_ICON_Mask			=	0x08,	//	S27 Mask	->	Use it on memoryMap[0]
		- MOON_ICON_Mask				=	0x02,	//	S50 Mask	->	Use it on memoryMap[0]
		- STARS_ICON_Mask				=	0x04,	//	S51 Mask	->	Use it on memoryMap[0]
		- SNOWY_CLOUD_ICON_Mask			=	0x01,	//	S28 Mask	->	Use it on memoryMap[13]
		- SNOW_ICON_Mask				=	0x01,	//	S44 Mask	->	Use it on memoryMap[18]
		- SUNNY_ICON_Mask				=	0x01,	//	S29 Mask	->	Use it on memoryMap[0]
		- PARTIALY_SUNNY_ICON_Mask		=	0x01,	//	S46 Mask	->	Use it on memoryMap[19]
		- RAINY_CLOUD_ICON_Mask			=	0x01,	//	S30 Mask	->	Use it on memoryMap[23]
		- THUNDER_ICON_Mask				=	0x02,	//	S49 Mask	->	Use it on memoryMap[22]
		- RAIN_ICON_Mask				=	0x01,	//	S45 Mask	->	Use it on memoryMap[21]
		- AQI_OUT_ICON_Mask				=	0x01,	//	S31 Mask	->	Use it on memoryMap[15]
		- SUNRISE_ICON_Mask				=	0x01,	//	S32 Mask	->	Use it on memoryMap[17]
		- SUNSET_ICON_Mask				=	0x01,	//	S33 Mask	->	Use it on memoryMap[14]
		- NODE_HUMID_ICON_Mask			=	0x04,	//	S34 Mask	->	Use it on memoryMap[22]
		- DRY_NODE_HUMID_ICON_Mask		=	0x08,	//	S35 Mask	->	Use it on memoryMap[22]
		- COMFORT_NODE_HUMID_ICON_Mask	=	0x10,	//	S36 Mask	->	Use it on memoryMap[22]
		- WET_NODE_HUMID_ICON_Mask		=	0x20,	//	S37 Mask	->	Use it on memoryMap[22]
		- PERCENT_NODE_HUMID_ICON_Mask	=	0x01,	//	S38 Mask	->	Use it on memoryMap[24]
		- D_ICON_Mask					=	0x01,	//	S39 Mask	->	Use it on memoryMap[3]
		- M_ICON_Mask					=	0x01,	//	S40 Mask	->	Use it on memoryMap[6]
		- AM_ICON_Mask					=	0x01,	//	S41 Mask	->	Use it on memoryMap[10]
		- PM_ICON_Mask					=	0x01,	//	S42 Mask	->	Use it on memoryMap[9]
		- DAY_ICON_Mask					=	0x80,	//	S43 Mask	->	Use it on memoryMap[29]
		Total of 50 Masks Available. 
	*/
	const uint8_t iconMasks[50] = 
	{
		0x01,	0x40,	0x04,	0x02,	0x01,
		0x01,	0x80,	0x04,	//0x01,	0x02,
		0x80,	//0x80,	0x08,	0x10,	0x80,
		//0x40,	0x20,
						0x80,	0x02,	//0x01,
		//0x02,
				0x80,	0x10,	//0x20,	0x40,
		//0x80,
				0x01,	0x08,	//0x02,	0x04,
		//0x01,	0x01,	0x01,	0x01,	0x01,
		//0x02,	0x01,
						0x01,	0x01,	0x01,
		0x04,	//0x08,	0x10,	0x20,
										0x01,
		0x01,	0x01,	//0x01,	0x01,
										0x80
	};

	/// Lines Masks
	/*
		Lines Masks for Turning Lines ON/OFF.
		- LINE1_Mask	=	0x02,	//	L1 Mask		->	Use it on memoryMap[51]
		- LINE2_Mask	=	0x01,	//	L2 Mask		->	Use it on memoryMap[33]
		- LINE3_Mask 	=	0x80,	//	L3 Mask		->	Use it on memoryMap[50]
		- LINE4_Mask	=	0x80,	//	L4 Mask		->	Use it on memoryMap[39]
		- LINE5_Mask	=	0x80,	//	L5 Mask		->	Use it on memoryMap[36]
		- LINE6_Mask	=	0x01,	//	L6 Mask		->	Use it on memoryMap[4]
		- LINE7_Mask	=	0x01,	//	L7 Mask		->	Use it on memoryMap[11]
		- LINE8_Mask	=	0x80;	//	L8 Mask		->	Use it on memoryMap[22]
		- LINE9_Mask	=	0x80;	//	L9 Mask		->	Use it on memoryMap[12]
		- LINE10_Mask	=	0x80;	//	L10 Mask	->	Use it on memoryMap[22]
		- LINE11_Mask	=	0x80;	//	L11 Mask	->	Use it on memoryMap[38]
		- LINE12_Mask	=	0x80;	//	L12 Mask	->	Use it on memoryMap[47]
		-	
		Total of 12 Lines Masks.
	*/
	const uint8_t linesMasks[12] = 
	{
		0x02,	0x01,	0x80,	0x80,	0x80,
		0x01,	0x01,	0x80,	0x01,	0x40,
		0x01,	0x80
	};

	/// RF Signals Masks
	/*	
		RF Signals Masks to Turn Signal ON/OFF.
		- NODE_RF_SIGNAL0_Mask		=	0x20,		//	X1 Mask		->	Use it on memoryMap[32]
		- NODE_RF_SIGNAL1_Mask		=	0x30,		//	X2 Mask		->	Use it on memoryMap[32]
		- NODE_RF_SIGNAL2_Mask		=	0x38,		//	X3 Mask		->	Use it on memoryMap[32]
		- NODE_RF_SIGNAL3_Mask		=	0x3D,		//	X4 Mask		->	Use it on memoryMap[32]
		- NODE_RF_SIGNAL4_Mask		=	0x3E,		//	X5 Mask		->	Use it on memoryMap[32]
		Total of 5 RF Signal Masks
	*/
	const uint8_t nodeRfSignalsMasks[5] =
	{
		0x20,	0x30,	0x38,	0x3C,	0x3E
	};

	/// Hub Battery Masks
	/*
		Hub Battery Cell ON/OFF
		- HUB_BAT0_Mask		=	0x01,		//	T7 Mask		->	Use it on memoryMap[46]
		- HUB_BAT1_Mask		=	0x03,		//	T6 Mask		->	Use it on memoryMap[46]
		- HUB_BAT2_Mask		=	0x07,		//	T5 Mask		->	Use it on memoryMap[46]
		- HUB_BAT3_Mask		=	0x0F,		//	T4 Mask		->	Use it on memoryMap[46]
		- HUB_BAT4_Mask		=	0x1F,		//	T3 Mask		->	Use it on memoryMap[46]
		- HUB_BAT5_Mask		=	0x3F,		//	T2 Mask		->	Use it on memoryMap[46] // It should be used during re-enabling HUB BAT icon
		Total of 6 Battery Cells Masks.
	*/
	const uint8_t hubBatteryMasks [7] =
	{
		0x00,	0x01,	0x03,	0x07,	0x0F,	0x1F,	0x3F
	};

	/// Node Battery Masks
	/*
		Node Battery Cell ON/OFF
		- NODE_BAT0_Mask	=	0x02,		//	T14 Mask	->	Use it on memoryMap[33]
		- NODE_BAT1_Mask	=	0x06,		//	T13 Mask	->	Use it on memoryMap[33]
		- NODE_BAT2_Mask	=	0x0E,		//	T12 Mask	->	Use it on memoryMap[33]
		- NODE_BAT3_Mask	=	0x1E,		//	T11 Mask	->	Use it on memoryMap[33]
		- NODE_BAT4_Mask	=	0x3E,		//	T10 Mask	->	Use it on memoryMap[33]
		- NODE_BAT5_Mask	=	0x7E,		//	T9	Mask	->	Use it on memoryMap[33] // It should be used during re-enabling NODE BAT icon
		Total of 6 Battery Cells Masks.
	*/
	const uint8_t nodeBatteryMasks[7] =
	{
		0x00,	0x02,	0x06,	0x0E,	0x1E,	0x3E,	0x7E
	};

	//	Hub AQI Icons Masks
	const uint8_t hubAqiIconsMasks[6] =
	{
		0x80,	0x08,	0x10,	0x80,	0x40,	0x20
	};

//	// Hub/Node Degree Symbols
//	const uint8_t degreeSymbolsMasks[2] =
//	{
//		0x02,	0x01
//	};

	//	Hub Humidity Icons Masks
	const uint8_t hubHumidityIconsMasks[3] =
	{
		0x20,	0x40,	0x80
	};

	//	Node Humidity Icons Masks
	const uint8_t nodeHumidityIconsMasks[3] =
	{
		0x08,	0x10,	0x20
	};

	//	Node Humidity Icons Masks
	const uint8_t weatherMasks[9] =
	{
		0x02,	0x04,	0x01,	0x01,	0x01,
		0x01,	0x01,	0x02,	0x01
	};

	/// 7-Segment Digits and Separator Masks.
	const uint8_t
		sSeg_Mask_D1_D12			=	0x7F,	//	Digit 1 - 12				->	Use it on memoryMap[34, 36, 37, 39, 40, 41, 42, 43, 44, 47, 49, 50]
		sSeg_Mask_D13_D35			=	0xFE,	//	Digit 13 - 35, & 39 		->	Use it on memoryMap[1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 ,15, 16, 17, 18, 19, 20 ,21, 23, 24]

//		sSeg_upNibble_Mask_D1_D12		=	0x7F,	//	Digit 1 - 12			->	Use it on memoryMap[34, 36, 37, 39, 40, 41, 42, 43, 44, 47, 49, 50]
//		sSeg_downNibble_Mask_D1_D12		=	0x0F,	//	Digit 1 - 12			->	Use it on memoryMap[34, 36, 37, 39, 40, 41, 42, 43, 44, 47, 49, 50]
//		sSeg_upNibble_Mask_D13_D35		=	0xFE,	//	Digit 13 - 35, & 39 	->	Use it on memoryMap[1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 ,15, 16, 17, 18, 19, 20 ,21, 23, 24]
//		sSeg_downNibble_Mask_D13_D35	=	0x0E,	//	Digit 13 - 35, & 39 	->	Use it on memoryMap[1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 ,15, 16, 17, 18, 19, 20 ,21, 23, 24]

		NODE_NUMBER_MASK			=	0xFE,	//	Digit 39					->	Use it on memoryMap[31]

		WEEKDAY_DIGIT_Mask			=	0x7F,	//	Digit 36 - 38				->	Use it on memoryMap[25, 26, 27, 28, 29, 30] e.g. {MON, TUE, WED, THU, FRI, SAT, SUN}
		
		HUB_TEMP_NEG_SIGN_Mask		=	0x10,	//	D1 Mask						->	Use it on memoryMap[51]
		HUB_TEMP_MSD_Mask			=	0x08,	//	D2 Mask						->	Use it on memoryMap[51]		MSD Most Significant Digit
		HUB_HUMID_ICONS_CLEAR_Mask	=	0xE0,	//	S23 - S25 Clear Mask		->	Use it on memoryMap[00]		MSD Most Significant Digit
		HUB_AQI_ICONS_CLEAR_Mask	=	0xF8,	//	S14 - S18 Clear Mask		->	Use it on memoryMap[45]		MSD Most Significant Digit

		POINT_Mask					=	0x80,	//	D3, D6 Mask					->	Use it on memoryMap[34, 49]
		DEG_FAHRENHEIT_Mask			=	0x01,	//	S8, s20 Mask				->	Use it on memoryMap[35, 48]
		DEG_CELCIUS_Mask			=	0x02,	//	S9, s21 Mask				->	Use it on memoryMap[35, 48]

		NODE_TEMP_NEG_SIGN_Mask		=	0x08,	//	D4 Mask						->	Use it on memoryMap[38]		MSD Most Significant Digit
		NODE_TEMP_MSD_Mask			=	0x04,	//	D5 Mask						->	Use it on memoryMap[38]		MSD Most Significant Digit
		NODE_HUMID_ICONS_CLEAR_MASK	=	0x38,	//	S35 - S37 Clear Mask		->	Use it on memoryMap[22]		MSD Most Significant Digit

		TIME_DATE_SEPARATOR_Mask	=	0x01,	//	D7, D8, D9, & D10 Mask		-> Use it on memoryMap[5, 8, 16, 20]
		AM_PM_Mask					=	0x01;	//	S41, & S42 Mask				->	Use it on memoryMap[9 ,10]		MSD Most Significant Digit

//		WEATHER_CLEAR_1_Mask		=	0x07,	//	S29, S50, & S51 Mask		-> Use it on memoryMap[00]
//		WEATHER_CLEAR_2_Mask		=	0x01;	//	S28, S30, S40, & S44-46 Mask-> Use it on memoryMap[6, 13, 18, 19, 21, 23]

	/// ------------------------------------------ Class Private Variables -------------------------------------------
	/// This variable will store Last status of Battery upon disabling event for re-enabling.
	uint8_t 
		lastHubBatStatus	=	0x00,
		lastNodeBatStauts	=	0x00,
	// Drive Mode settings storing variable.
		driveModeSettings	=	0x03,
	// System Mode Settings storing variable.
		systemModeSettings	=	0x02,
	// Frame Frequency settings storing variable.
		frameFrequency		=	0x01,
	// Blinking Frequency settings storing variable.
		blinkFrequency		=	0x00,
	// VLCD/Segment71 selector settings storing variable.
		segVlcdSelect		=	0x00,
	// Brightness Level storing variable.
		brightnessValue		=	0x08,
	// Battery Level storing variable.
		lastBatStatus		=	0x02,
	// Null Segment ( - ) value storing variable.
		nullSegment			=	0x0B,
	// Zero Segment ( 0 ) value storing variable.
		zeroSegment			=	0x0,
	// Empty Digit for 7-Segments Display.
		emptyDigit			=	0x0A;

	// Air Quality Index Icons Levels.
	uint16_t
		aqiGoodLevel 			=	50,  // Air Quality Index (AQI) of 50.
		aqiModerateLevel		=	100, // Air Quality Index (AQI) of 100.
		aqiUsgLevel				=	150, // Air Quality Index (AQI) of 150.
		aqiPoorLevel			=	200, // Air Quality Index (AQI) of 200.
		aqiVeryPoorLevel		=	300, // Air Quality Index (AQI) of 250.
		aqiHazardousLevel		=	301; // Air Quality Index (AQI) of 300.
	// Humidity Labels Levels.
	uint8_t
		humidityDryLevel 			=	39,
		humidityComfortLowerLevel	=	40, // Relative Humidity of 40%
		humidityComfortUpperLevel	=	60, // Relative Humidity of 60%
		humidityWetLowerLevel		=	61, // Relative Humidity of 61%
		humidityWetUpperLevel		=	99; // Relative Humidity of 61%

	// Variable array to get 7-Segments data.
	uint8_t
		displayValue[3] = { 0 };

	// Variable array to get 14-Segments Day Data.
//	uint8_t
//		dayDisplayValue[6] = { 0 };

	// Variable to store communication status of the functions.
	HAL_StatusTypeDef status = HAL_OK;

	// Variable for passing value to floatTo7Segments Converter.
	float value = 0;
	/// 7-Segment data storing variables.
	/*
	float
		hubTemperatrue	=	0.0,
		hubHumidity		=	0.0,
		nodeTemperature	=	0.0,
		nodeHumidity	=	0.0,

		hubAqiLevel		=	0.0,
		coLevel			=	0.0,

		aqiOutLevel		=	0.0;

	uint8_t 
		sunriseHours	=	0,
		surnriseMinutes	=	0,
		sunsetHours		=	0,
		sunsetMinutes	=	0,

		day				=	0,
		month			=	0,

		timeHour		=	0,
		timeMinute		=	0;
	*/

	/// Function to calculate absolute value for floating point number
	float abs(float* number);

	/// Function to convert a floating point number to 7-segment display format
	HAL_StatusTypeDef floatTo7Segment(float* number, uint8_t* display, bool node);

	/// Function to convert a BCD number to 7-segment display format
	uint8_t bcdTo7Segments(uint8_t* bcdDigit);
	uint8_t nodeBcdTo7Segments(uint8_t* bcdDigit);

	/// ------------------------------------------ Class Private Functions -------------------------------------------
	/*
		Helper Function to update display
		- Use this function into the main loop to maintain segments consistency
		-
	*/
	HAL_StatusTypeDef updateDisplay();

	/*
		Private helper function for I2C communication with AiP16C22
		- I2C Address
		- Data Memory Array
		-
	*/
	HAL_StatusTypeDef writeCommandToI2C(const uint8_t* regAddr, uint8_t* regData, size_t size);
	HAL_StatusTypeDef writeDataToI2C(const uint8_t* regAddr, uint8_t* regData, size_t size);
	//	HAL_StatusTypeDef writeToDisplayI2C(const uint8_t* regAddr, uint8_t* regData, size_t size);
	//	HAL_StatusTypeDef writeToI2C(const uint8_t* regAddr, uint8_t* regData, size_t size);

	/*
			Function to read "Entire RAM" contents after wake up from deep sleep.
			- No arguments.
			-
	*/
	HAL_StatusTypeDef readDisplayRAM(void);

};

#endif // DisplayDriver_CNKD1103_HT16C24AH
