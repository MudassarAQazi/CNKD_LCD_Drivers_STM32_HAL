// DisplayDriver_AiP16C22

// Header Files of the Libraries required
#include <DRV_DisplayDriver_CNKD1103_HT16C24A.h>
//#include <Wire.h>

/// Constructor for LCD Object Creation
//DisplayDriver_CNKD1103_HT16C24A::DisplayDriver_CNKD1103_HT16C24A()//uint8_t address)
//{
//}
DisplayDriver_CNKD1103_HT16C24A::DisplayDriver_CNKD1103_HT16C24A(
		I2C_HandleTypeDef&		hi2c,
		const uint16_t&			address,
		UART_HandleTypeDef&		huart)//uint8_t address)

//:i2cPort(hi2c), i2cAddress(address), Uart(huart)
{
	i2cPort		=	hi2c;
	i2cAddress	=	address;
	Uart		=	huart;
}

/// Use this function at the start of the program in Main Subroutine.
HAL_StatusTypeDef DisplayDriver_CNKD1103_HT16C24A::lcdPortInit()//I2C_HandleTypeDef* hi2c, const uint16_t* address, UART_HandleTypeDef* UART)
{
	// Slave Write and Read Address Initialization
	i2cWriteAddress = {(uint16_t)(i2cAddress << 1)};
	i2cReadAddress = {(uint16_t)(i2cWriteAddress | (uint16_t)0x01)};

	//i2cPort = {*hi2c};

	//Uart = {*UART};

	status = readDisplayRAM();

	return status;
}
/// Use this function after the lcdPortInit function.
HAL_StatusTypeDef DisplayDriver_CNKD1103_HT16C24A::displayInit()
{
	// Implementation for I2C RAM based display initialization

	status = biasOfDisplay(0x01); 			HAL_Delay(1);	if(status != HAL_OK) return status;
	status = dutyOfDisplay(0x01); 			HAL_Delay(1);	if(status != HAL_OK) return status;
	status = frequency(false); 				HAL_Delay(1);	if(status != HAL_OK) return status;
	status = segVlcdSetting(0x00); 			HAL_Delay(1);	if(status != HAL_OK) return status;
	status = brightness(0x00);				HAL_Delay(1);	if(status != HAL_OK) return status;
	status = display(true); 				HAL_Delay(1);	if(status != HAL_OK) return status;
	status = enableDisplayDriver(true);		HAL_Delay(1);	if(status != HAL_OK) return status;

	status = displayClear();				HAL_Delay(1);	if(status != HAL_OK) return status;

	status = icon(HUB_HOUSE_ICON,			true);			if(status != HAL_OK) return status;
	status = icon(HUB_BATT_ICON,			true);			if(status != HAL_OK) return status;
	status = icon(HUB_THERMO_ICON,			true);			if(status != HAL_OK) return status;
	status = icon(HUB_HUMID_ICON,			true);			if(status != HAL_OK) return status;
	status = icon(PERCENT_HUB_HUMID_ICON,	true);			if(status != HAL_OK) return status;
	status = icon(D_ICON,					true);			if(status != HAL_OK) return status;
	status = icon(M_ICON,					true);			if(status != HAL_OK) return status;

	status = icon(INDOOR_ICON,				true);			if(status != HAL_OK) return status;
	status = icon(INDOOR_AQ_ICON,			true);			if(status != HAL_OK) return status;
	status = icon(HUB_AQI_ICON,				true);			if(status != HAL_OK) return status;
	status = icon(PM2P5_ICON,				true);			if(status != HAL_OK) return status;
	status = icon(CO_PPM_ICON,				true);			if(status != HAL_OK) return status;
	status = icon(FORECAST_ICON,			true);			if(status != HAL_OK) return status;
	status = icon(AQI_OUT_ICON,				true);			if(status != HAL_OK) return status;
	status = icon(SUNRISE_ICON,				true);			if(status != HAL_OK) return status;
	status = icon(SUNSET_ICON,				true);			if(status != HAL_OK) return status;

	status = icon(NODE_HOUSE_ICON,			true);			if(status != HAL_OK) return status;
	status = icon(NODE_OUT_ICON,			true);			if(status != HAL_OK) return status;
	status = icon(NODE_BATT_ICON,			true);			if(status != HAL_OK) return status;
	status = icon(NODE_THERMO_ICON,			true);			if(status != HAL_OK) return status;
	status = icon(NODE_HUMID_ICON,			true);			if(status != HAL_OK) return status;
	status = icon(PERCENT_NODE_HUMID_ICON,	true);			if(status != HAL_OK) return status;
	status = icon(DAY_ICON,					true);			if(status != HAL_OK) return status;

	status = linesEnable(true);								if(status != HAL_OK) return status;

	status = printNodeNumber(nullSegment);					if(status != HAL_OK) return status;
	status = printHubTemperature(200.0, noDegree);			if(status != HAL_OK) return status;
	status = printNodeTemperature(200.0, noDegree);			if(status != HAL_OK) return status;

	status = printHubHumidity(100);							if(status != HAL_OK) return status;
	status = printNodeHumidity(100);						if(status != HAL_OK) return status;

	status = printSunriseTime(25, 60);						if(status != HAL_OK) return status;
	status = printSunsetTime(25, 60);						if(status != HAL_OK) return status;
	status = printDate(32, 13, Monday);						if(status != HAL_OK) return status;
	status = printTime(25, 60, noMeridiem);					if(status != HAL_OK) return status;

	status = printIndoorAirQualityIndex(1000);				if(status != HAL_OK) return status;
	status = printIndoorCoLevel(1000);						if(status != HAL_OK) return status;
	status = printOutdoorAirQualityIndex(1000);				if(status != HAL_OK) return status;

	return status;
}

/// Function to Set Duty settings of the display  
HAL_StatusTypeDef DisplayDriver_CNKD1103_HT16C24A::dutyOfDisplay(uint8_t mode)// = (uint8_t)0x01)
{
	/*
		LCD display off address 80H
		- { 0	0	0	0	Duty1	Bias1	Duty0	Bias0 }	LSB
		Drive	Mode Selection
		[Mode]	[Duty]
		- 0		 1/4
		- 1		 1/8	(default for CNKD1103 LCD)
		- 2		 1/16
	*/
	switch (mode)
	{
		case 0: // 1/4 Duty:	4 COM's
			driveModeSettings = (driveModeSettings & ~DUTY_DISP_Mask) | 0x00;
			break;
		case 1: // 1/8 Duty:	8 COM's
			driveModeSettings = (driveModeSettings & ~DUTY_DISP_Mask) | 0x02;
			break;
		case 2: // 1/16 Duty:	16 COM's
			driveModeSettings = (driveModeSettings & ~DUTY_DISP_Mask) | 0x08;
			break;
		default: // 1/8 Duty:	8 COM's specific for the Display Hub Design Version T2SV
			driveModeSettings = (driveModeSettings & ~DUTY_DISP_Mask) | 0x02;
	}

	return writeCommandToI2C(&driveModeRegAddress , &driveModeSettings, sizeof(driveModeSettings));
}

/// Function to set bias Display values
HAL_StatusTypeDef DisplayDriver_CNKD1103_HT16C24A::biasOfDisplay(uint8_t value)// = (uint8_t)0x01)
{
	/*
		LCD display off address 80H
		- { 0	0	0	0	Duty1	Bias1	Duty0	Bias0 }	LSB
		Select		Bias the Display
		[Value]		[Bias]
		 - 0		  1/3
		 - 1		  1/4
		 - 2		  1/5
	*/
	switch (value)
	{
		case 0: // 1/3 Bias.
			driveModeSettings = (driveModeSettings & ~BIAS_DISP_Mask) | 0x00;
			break;
		case 1: // 1/4 Bias.
			driveModeSettings = (driveModeSettings & ~BIAS_DISP_Mask) | 0x01;
			break;
		case 2: // 1/5 Bias.
			driveModeSettings = (driveModeSettings & ~BIAS_DISP_Mask) | 0x04;
			break;
		default: // 1/3 Bias.
			driveModeSettings = (driveModeSettings & ~BIAS_DISP_Mask) | 0x00;
	}
	//writeToI2C(modeSettings);
	return writeCommandToI2C(&driveModeRegAddress, &driveModeSettings, sizeof(driveModeSettings));
}

/// Function to Enable/Disable Display Driver
HAL_StatusTypeDef DisplayDriver_CNKD1103_HT16C24A::enableDisplayDriver(bool enable = true)
{

	/*
		Function to Disable/Enable Display Driver IC (AiP16C22)
		- { 0	0	0	0	0	0	S	E }	LSB
		[Enable]   [Internal System Oscillator(S)]
		 - 0         off
		 - 1         on
	*/
	if (enable) systemModeSettings |= OSC_DISP_Mask; else systemModeSettings &= (~OSC_DISP_Mask);
	//writeToI2C(modeSettings);
	return writeCommandToI2C(&systemModeRegAddress, &systemModeSettings, sizeof(systemModeSettings));
}

/// Function to Enable/Disable LCD Display
HAL_StatusTypeDef DisplayDriver_CNKD1103_HT16C24A::display(bool enable = true)
{

	/*
		Function to turn ON/OFF the Display
		- { 0	0	0	0	0	0	S	E }	LSB
		[Enable]   [LCD Display]
		 - 0         off
		 - 1         on
	*/
	if (enable) systemModeSettings |= OFF_DISP_Mask; else systemModeSettings &= (~OFF_DISP_Mask);
	//writeToI2C(modeSettings);
	return writeCommandToI2C(&systemModeRegAddress, &systemModeSettings, sizeof(systemModeSettings));

}

/// Function to Set Frame frequency
HAL_StatusTypeDef DisplayDriver_CNKD1103_HT16C24A::frequency(bool freq = false)
{
	/*
		Function to Select Frame Frequency of Display
		- { 0	0	0	0	0	0	0	F }	LSB
		[Frequency]	[Frame Frequency]
		 - 0         80 Hz
		 - 1         160 Hz
	*/
	if (freq) frameFrequency |= FREQ_DISP_Mask; else frameFrequency &= (~FREQ_DISP_Mask);
	//writeToI2C(modeSettings);
	return writeCommandToI2C(&framFrequencyRegAddress, &frameFrequency, sizeof(frameFrequency));
}

/// Function to Blink Display
HAL_StatusTypeDef DisplayDriver_CNKD1103_HT16C24A::blinkDisplay(uint8_t mode = (uint8_t)0x00)
{

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
	blinkFrequency = (blinkFrequency & ~BLNK_DISP_Mask) | mode;
	//writeToI2C(blinkValue);
	return writeCommandToI2C(&blinkRegAddress, & blinkFrequency, sizeof(blinkFrequency));
}

/// Function to Set SEG/VLCD pins settings
HAL_StatusTypeDef DisplayDriver_CNKD1103_HT16C24A::segVlcdSetting(uint8_t settings)// = (uint8_t)0x01)
{
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
	segVlcdSelect	&=	~IVA_VLCD_DISP_PIN_EN_Mask;
	segVlcdSelect	|=	(settings << 4);
//	segVlcdSelect |= brightnessValue;
	//writeToI2C(intVoltageCtrlValue);
	return writeCommandToI2C(&vlcdSegEnableAddress, &segVlcdSelect, sizeof(segVlcdSelect));
}

/// Function to Control LCD Display Brightness
HAL_StatusTypeDef DisplayDriver_CNKD1103_HT16C24A::brightness(uint8_t bright)
{
	/*  Function to set Brightness of the LCD
	    [Bright]    [Display]
	    - 0          Low Brightness
	    - .          .
	    - .          .
	    - 15         Full Brightness
	    -
	*/
	brightnessValue	&=	~BRIGT_DISP_Mask;
	brightnessValue	|=	bright;
//	brightnessValue |= segVlcdSelect;
	//writeToI2C(brightnessValue);
	return writeCommandToI2C(&brightCtrlEnAddress, &brightnessValue, sizeof(brightnessValue));
}

/// Use this function to clear content of the whole display
HAL_StatusTypeDef DisplayDriver_CNKD1103_HT16C24A::displayClear()
{
	// Implementation for clearing the display
	for (uint8_t i = 0; i < memSize; i++) memoryMap[i] = 0x00; //Clearing all the memory map
//	linesEnable(true);
	return updateDisplay();
}

/// Use this function to Turn on All the Segments.
HAL_StatusTypeDef DisplayDriver_CNKD1103_HT16C24A::displayFill()
{
	// Implementation for clearing the display
	for (uint8_t i = 0; i < memSize; i++) memoryMap[i] = 0xFF; //Populating all the memory map
//	linesEnable(true);
	return updateDisplay();
}

/// Use this function to turn on all the Lines
HAL_StatusTypeDef DisplayDriver_CNKD1103_HT16C24A::linesEnable(bool enable)
{
	/*
		Function to Set/Reset Division Lines
		- Enables/Disables Lines Separators..
	*/
	if (enable)
	{
		memoryMap[linesAddress[0]]	|=	linesMasks[0];
		memoryMap[linesAddress[1]]	|=	linesMasks[1];
		memoryMap[linesAddress[2]]	|=	linesMasks[2];
		memoryMap[linesAddress[3]]	|=	linesMasks[3];
		memoryMap[linesAddress[4]]	|=	linesMasks[4];
		memoryMap[linesAddress[5]]	|=	linesMasks[5];
		memoryMap[linesAddress[6]]	|=	linesMasks[6];
		memoryMap[linesAddress[7]]	|=	linesMasks[7];
		memoryMap[linesAddress[8]]	|=	linesMasks[8];
		memoryMap[linesAddress[9]]	|=	linesMasks[9];
		memoryMap[linesAddress[10]]	|=	linesMasks[10];
		memoryMap[linesAddress[11]]	|=	linesMasks[11];
	}
	else
	{
		memoryMap[linesAddress[0]]	&=	(~linesMasks[0]);
		memoryMap[linesAddress[1]]	&=	(~linesMasks[1]);
		memoryMap[linesAddress[2]]	&=	(~linesMasks[2]);
		memoryMap[linesAddress[3]]	&=	(~linesMasks[3]);
		memoryMap[linesAddress[4]]	&=	(~linesMasks[4]);
		memoryMap[linesAddress[5]]	&=	(~linesMasks[5]);
		memoryMap[linesAddress[6]]	&=	(~linesMasks[6]);
		memoryMap[linesAddress[7]]	&=	(~linesMasks[7]);
		memoryMap[linesAddress[8]]	&=	(~linesMasks[8]);
		memoryMap[linesAddress[9]]	&=	(~linesMasks[9]);
		memoryMap[linesAddress[10]]	&=	(~linesMasks[10]);
		memoryMap[linesAddress[11]]	&=	(~linesMasks[11]);
	}
	return updateDisplay();
}

/// Use this function to Set/Clear icon in the Loop Block
HAL_StatusTypeDef  DisplayDriver_CNKD1103_HT16C24A::icon(uint8_t iconType, bool enable)
{
	//// Implementation for enabling or disabling specified icon
	if (enable) memoryMap[iconAddress[iconType]] |= iconMasks[iconType];	else memoryMap[iconAddress[iconType]] &= (~iconMasks[iconType]);
	//uint8_t data[] = {0x80, iconAddress[iconType], memoryMap[iconAddress[iconType]]};
	status = writeDataToI2C(&iconAddress[iconType], &memoryMap[iconAddress[iconType]], sizeof(memoryMap[iconAddress[iconType]]));
	return status;
}

/// Function to display Hub Battery Level
HAL_StatusTypeDef DisplayDriver_CNKD1103_HT16C24A::hubBatteryStatus(uint8_t batteryCells)
{
	/*  Function to set battery cells status
		[Cells]     [Status]
		- 0          Empty
		- .          .
		- .          .
		- 6          Full
		-
	*/
	if(batteryCells <= 6)
	{
		memoryMap[hubBatteryAddress]	&=	~hubBatteryMasks[6];
		memoryMap[hubBatteryAddress]	|=	hubBatteryMasks[batteryCells];
		lastHubBatStatus = hubBatteryMasks[batteryCells];
	}
	else
	{
		memoryMap[hubBatteryAddress]	&=	~hubBatteryMasks[6];
		memoryMap[hubBatteryAddress]	|=	hubBatteryMasks[6];
		lastHubBatStatus = hubBatteryMasks[6];
	}

	return writeDataToI2C(&hubBatteryAddress, &memoryMap[hubBatteryAddress], sizeof(memoryMap[hubBatteryAddress]));
}

/// Function to Display Hub Temperature Level
HAL_StatusTypeDef DisplayDriver_CNKD1103_HT16C24A::printHubTemperature(float temperatureValue, degree_t degree)
{
	/*
		Function to print Hub Temperature Value on the display
		- (Temperature)
		- Address of Temperature Value,
		-
	*/
	// Setting Negative Sign for the Temperature Value.
	if(temperatureValue < 0)
	{
		memoryMap[hubTempSignAddress] |= HUB_TEMP_NEG_SIGN_Mask;
		status =  writeDataToI2C(&hubTempSignAddress, &memoryMap[hubTempSignAddress], sizeof(memoryMap[hubTempSignAddress]));
		if(status != HAL_OK) return status;
	}
	else
	{
		memoryMap[hubTempSignAddress] &= ~HUB_TEMP_NEG_SIGN_Mask;
		status =  writeDataToI2C(&hubTempSignAddress, &memoryMap[hubTempSignAddress], sizeof(memoryMap[hubTempSignAddress]));
		if(status != HAL_OK) return status;
	}

	// Printing Null Segment " - " for the Value Greater than the Range.
	if (abs(&temperatureValue) >= 200.0)
	{
		displayValue[0] = bcdTo7Segments(&nullSegment);
		displayValue[1] = displayValue[0];
		displayValue[2] = displayValue[0];
		memoryMap[hubTempPointAddress] &= ~POINT_Mask;
	}
	else
	{
		// Generating 7-Segment values from floating point number
		status = floatTo7Segment(&temperatureValue, displayValue, false);
		memoryMap[hubTempPointAddress] |= POINT_Mask;
	}

	// Temperature Degree Type Selection.
	if(degree == degreeCelcius)
	{
		memoryMap[hubDegreeSymbolsAddress] &= ~DEG_FAHRENHEIT_Mask;
		memoryMap[hubDegreeSymbolsAddress] |= DEG_CELCIUS_Mask;
	}
	else if(degree == degreeFahrenheit)
	{
		memoryMap[hubDegreeSymbolsAddress] &= ~DEG_CELCIUS_Mask;
		memoryMap[hubDegreeSymbolsAddress] |= DEG_FAHRENHEIT_Mask;
	}

	// Updating Screen RAM connected on I2C.
	if(status == HAL_OK)
	{
		if((abs(&temperatureValue) >= 100.0) && (abs(&temperatureValue) < 200.0)) memoryMap[hubTempMsdAddress] |= HUB_TEMP_MSD_Mask;
		else	memoryMap[hubTempMsdAddress] &= ~HUB_TEMP_MSD_Mask;

		memoryMap[hubTemperatureAddress[0]] &= ~sSeg_Mask_D1_D12; memoryMap[hubTemperatureAddress[0]] |= displayValue[0];
		memoryMap[hubTemperatureAddress[1]] &= ~sSeg_Mask_D1_D12; memoryMap[hubTemperatureAddress[1]] |= displayValue[1];
		memoryMap[hubTemperatureAddress[2]] &= ~sSeg_Mask_D1_D12; memoryMap[hubTemperatureAddress[2]] |= displayValue[2];

		status = writeDataToI2C(&hubTempPointAddress, &memoryMap[hubTempPointAddress], sizeof(memoryMap[hubTempPointAddress]));
		if(status != HAL_OK) return status;
		status = writeDataToI2C(&hubTempMsdAddress, &memoryMap[hubTempMsdAddress], sizeof(memoryMap[hubTempMsdAddress]));
		if(status != HAL_OK) return status;
		status = writeDataToI2C(&hubTemperatureAddress[0], &memoryMap[hubTemperatureAddress[0]], sizeof(memoryMap[hubTemperatureAddress[0]]));
		if(status != HAL_OK) return status;
		status = writeDataToI2C(&hubTemperatureAddress[1], &memoryMap[hubTemperatureAddress[1]], sizeof(memoryMap[hubTemperatureAddress[1]]));
		if(status != HAL_OK) return status;
		status = writeDataToI2C(&hubTemperatureAddress[2], &memoryMap[hubTemperatureAddress[2]], sizeof(memoryMap[hubTemperatureAddress[2]]));
		if(status != HAL_OK) return status;

		status = writeDataToI2C(&hubDegreeSymbolsAddress, &memoryMap[hubDegreeSymbolsAddress], sizeof(memoryMap[hubDegreeSymbolsAddress]));
		if(status != HAL_OK) return status;
	}
	else return status;

//	for (uint8_t i = 1; i <= 6; i++)	memoryMap[i] &= (~sSeg_upNibble_Mask);
//	for (uint8_t j = 2; j <= 7; j++)		memoryMap[j] &= (~sSeg_downNibble_Mask);
//	// Updating corresponding bytes of temperature on Memory Map
//	if (temperatureValue >= 100.0) memoryMap[3] |= tSeg_S3_Mask;   else	memoryMap[3] &= (~tSeg_S3_Mask);
//	memoryMap[3] |= (temperatureDisplay[0] & sSeg_upNibble_Mask);	memoryMap[4] |= (temperatureDisplay[0] & sSeg_downNibble_Mask);
//	memoryMap[2] |= (temperatureDisplay[1] & sSeg_upNibble_Mask);	memoryMap[3] |= (temperatureDisplay[1] & sSeg_downNibble_Mask);
//	memoryMap[1] |= (temperatureDisplay[2] & sSeg_upNibble_Mask);	memoryMap[2] |= (temperatureDisplay[2] & sSeg_downNibble_Mask);
//	memoryMap[2] |= POINT_Mask;
//
//	// Updating corresponding bytes of humidity value on Memory Map
//	memoryMap[6] |= (humidDisplay[0] & sSeg_upNibble_Mask);			memoryMap[7] |= (humidDisplay[0] & sSeg_downNibble_Mask);
//	memoryMap[5] |= (humidDisplay[1] & sSeg_upNibble_Mask);			memoryMap[6] |= (humidDisplay[1] & sSeg_downNibble_Mask);
//	memoryMap[4] |= (humidDisplay[2] & sSeg_upNibble_Mask);			memoryMap[5] |= (humidDisplay[2] & sSeg_downNibble_Mask);
//	memoryMap[5] |= Point_Mask;
//
//	return updateDisplay();
	return HAL_OK;

}

/// Function to Display Hub Humidity Level
HAL_StatusTypeDef DisplayDriver_CNKD1103_HT16C24A::printHubHumidity(uint8_t humidityValue)
{
	/*
		Function to print Hub Humidity Value on the display
		- (Humidity)
		- Address of Humidity Value,
		-
	*/
	if (humidityValue >= 100)
	{
		displayValue[0] = bcdTo7Segments(&nullSegment) << 1;
		displayValue[1] = displayValue[0];
		displayValue[2] = displayValue[0];
	}
	else
	{
		value = (float) humidityValue;
		// Generating 7-Segment values from floating point number.
		status = floatTo7Segment(&value, displayValue, false);

		// Shifting Values to left due to shift in segments position.
		displayValue[0] <<= 1;
		displayValue[1] <<= 1;
	}
	//delay(100);
	//Serial.print("Humidity : \t");

	// Updating Screen RAM connected on I2C.
	if(status == HAL_OK)
	{
		// Humidity Label Selection based on Humidity input Level.
		if(humidityValue <= humidityDryLevel)
		{
			memoryMap[hubHumidityIconsAddress] &= ~HUB_HUMID_ICONS_CLEAR_Mask;
			memoryMap[hubHumidityIconsAddress] |= hubHumidityIconsMasks[0];
		}
		else if((humidityValue >= humidityComfortLowerLevel) && (humidityValue <= humidityComfortUpperLevel))
		{
			memoryMap[hubHumidityIconsAddress] &= ~HUB_HUMID_ICONS_CLEAR_Mask;
			memoryMap[hubHumidityIconsAddress] |= hubHumidityIconsMasks[1];
		}
		else if((humidityValue >= humidityWetLowerLevel) && (humidityValue <= humidityWetUpperLevel))
		{
			memoryMap[hubHumidityIconsAddress] &= ~HUB_HUMID_ICONS_CLEAR_Mask;
			memoryMap[hubHumidityIconsAddress] |= hubHumidityIconsMasks[2];
		}
		else
			memoryMap[hubHumidityIconsAddress] &= ~HUB_HUMID_ICONS_CLEAR_Mask;

		memoryMap[hubHumidityAddress[0]] &= ~sSeg_Mask_D13_D35; memoryMap[hubHumidityAddress[0]] |= displayValue[0];
		memoryMap[hubHumidityAddress[1]] &= ~sSeg_Mask_D13_D35; memoryMap[hubHumidityAddress[1]] |= displayValue[1];

		// Label Updates.
		status = writeDataToI2C(&hubHumidityIconsAddress, &memoryMap[hubHumidityIconsAddress], sizeof(memoryMap[hubHumidityIconsAddress]));
		if(status != HAL_OK) return status;

		// Levels Updates.
		status = writeDataToI2C(&hubHumidityAddress[0], &memoryMap[hubHumidityAddress[0]], sizeof(memoryMap[hubHumidityAddress[0]]));
		if(status != HAL_OK) return status;
		status = writeDataToI2C(&hubHumidityAddress[1], &memoryMap[hubHumidityAddress[1]], sizeof(memoryMap[hubHumidityAddress[1]]));
		if(status != HAL_OK) return status;
	}
	else return status;
	return HAL_OK;
}

/// Function to Display Indoor Air Quality Index
HAL_StatusTypeDef DisplayDriver_CNKD1103_HT16C24A::printIndoorAirQualityIndex(uint16_t airQuality)
{

	/*
		Function to print Dust/Air Quality Value on the display
		- (Humidity)
		- Address of Humidity Value,
		-
	*/
	if (airQuality >= 1000)
	{
		displayValue[0] = bcdTo7Segments(&nullSegment);
		displayValue[1] = displayValue[0];
		displayValue[2] = displayValue[0];
	}
	else
	{
		value = (float)airQuality/10;
		// Generating 7-Segment values from floating point number.
		status = floatTo7Segment(&value, displayValue, false);

		// Removing 7-Segments Display of "0" to "Empty Digit" Segments and Adding when MSB is present.
		if((displayValue[1] == bcdTo7Segments(&zeroSegment)) && (airQuality <= 9))
			displayValue[1] = bcdTo7Segments(&emptyDigit);

		// Shifting Digit towards Left i.e. Left Justified.
		if(airQuality <= 9)
		{
			displayValue[0] = bcdTo7Segments(&zeroSegment);
			displayValue[1] = displayValue[2];
			displayValue[2] = bcdTo7Segments(&emptyDigit);
		}
		else if(airQuality<=99)
		{
			displayValue[0] = displayValue[1];
			displayValue[1] = displayValue[2];
			displayValue[2] = bcdTo7Segments(&emptyDigit);
		}
	}

	// Updating Screen RAM connected on I2C.
	if(status == HAL_OK)
	{
		// Air Quality Index Label Selection based on AQI Level.
		if(airQuality <= aqiGoodLevel)
		{
			memoryMap[hubAqiIconsAddress[1]] &= ~HUB_AQI_ICONS_CLEAR_Mask;
			memoryMap[hubAqiIconsAddress[0]] |= hubAqiIconsMasks[0];
		}
		else if((airQuality > aqiGoodLevel) && (airQuality <= aqiModerateLevel))
		{
			memoryMap[hubAqiIconsAddress[0]] &= ~hubAqiIconsMasks[0];
			memoryMap[hubAqiIconsAddress[1]] &= ~HUB_AQI_ICONS_CLEAR_Mask;
			memoryMap[hubAqiIconsAddress[1]] |= hubAqiIconsMasks[1];
		}
		else if((airQuality > aqiModerateLevel) && (airQuality <= aqiUsgLevel))
		{
			memoryMap[hubAqiIconsAddress[0]] &= ~hubAqiIconsMasks[0];
			memoryMap[hubAqiIconsAddress[2]] &= ~HUB_AQI_ICONS_CLEAR_Mask;
			memoryMap[hubAqiIconsAddress[2]] |= hubAqiIconsMasks[2];
		}
		else if((airQuality > aqiUsgLevel) && (airQuality <= aqiPoorLevel))
		{
			memoryMap[hubAqiIconsAddress[0]] &= ~hubAqiIconsMasks[0];
			memoryMap[hubAqiIconsAddress[3]] &= ~HUB_AQI_ICONS_CLEAR_Mask;
			memoryMap[hubAqiIconsAddress[3]] |= hubAqiIconsMasks[3];
		}
		else if((airQuality > aqiPoorLevel) && (airQuality <= aqiVeryPoorLevel))
		{
			memoryMap[hubAqiIconsAddress[0]] &= ~hubAqiIconsMasks[0];
			memoryMap[hubAqiIconsAddress[4]] &= ~HUB_AQI_ICONS_CLEAR_Mask;
			memoryMap[hubAqiIconsAddress[4]] |= hubAqiIconsMasks[4];
		}
		else if((airQuality >= aqiHazardousLevel))
		{
			memoryMap[hubAqiIconsAddress[0]] &= ~hubAqiIconsMasks[0];
			memoryMap[hubAqiIconsAddress[5]] &= ~HUB_AQI_ICONS_CLEAR_Mask;
			memoryMap[hubAqiIconsAddress[5]] |= hubAqiIconsMasks[5];
		}
		else
		{
			memoryMap[hubAqiIconsAddress[0]] &= ~hubAqiIconsMasks[0];
			memoryMap[hubAqiIconsAddress[1]] &= ~HUB_AQI_ICONS_CLEAR_Mask;
		}


		memoryMap[hubAqiAddress[0]] &= ~sSeg_Mask_D1_D12; memoryMap[hubAqiAddress[0]] |= displayValue[0];
		memoryMap[hubAqiAddress[1]] &= ~sSeg_Mask_D1_D12; memoryMap[hubAqiAddress[1]] |= displayValue[1];
		memoryMap[hubAqiAddress[2]] &= ~sSeg_Mask_D1_D12; memoryMap[hubAqiAddress[2]] |= displayValue[2];

		// Label Updates.
		status = writeDataToI2C(&hubAqiIconsAddress[0], &memoryMap[hubAqiIconsAddress[0]], sizeof(memoryMap[hubAqiIconsAddress[0]]));
		if(status != HAL_OK) return status;
		status = writeDataToI2C(&hubAqiIconsAddress[1], &memoryMap[hubAqiIconsAddress[1]], sizeof(memoryMap[hubAqiIconsAddress[1]]));
		if(status != HAL_OK) return status;

		// Levels Updates.
		status = writeDataToI2C(&hubAqiAddress[0], &memoryMap[hubAqiAddress[0]], sizeof(memoryMap[hubAqiAddress[0]]));
		if(status != HAL_OK) return status;
		status = writeDataToI2C(&hubAqiAddress[1], &memoryMap[hubAqiAddress[1]], sizeof(memoryMap[hubAqiAddress[1]]));
		if(status != HAL_OK) return status;
		status = writeDataToI2C(&hubAqiAddress[2], &memoryMap[hubAqiAddress[2]], sizeof(memoryMap[hubAqiAddress[2]]));
		if(status != HAL_OK) return status;

	}
	else return status;
	return HAL_OK;
}

/// Function to Display Indoor CO Level
HAL_StatusTypeDef DisplayDriver_CNKD1103_HT16C24A::printIndoorCoLevel(uint16_t coLevel)
{

	/*
		Function to print Dust/Air Quality Value on the display
		- (Humidity)
		- Address of Humidity Value,
		-
	*/
	if (coLevel >= 1000)
	{
		displayValue[0] = bcdTo7Segments(&nullSegment);
		displayValue[1] = displayValue[0];
		displayValue[2] = displayValue[0];
	}
	else
	{
		value = (float)coLevel/10;
		// Generating 7-Segment values from floating point number.
		status = floatTo7Segment(&value, displayValue, false);

		// Removing 7-Segments Display of "0" to "Empty Digit" Segments and Adding when MSB is present.
		if((displayValue[1] == bcdTo7Segments(&zeroSegment)) && (coLevel <= 9))
			displayValue[1] = bcdTo7Segments(&emptyDigit);

		// Shifting Digit towards Left i.e. Left Justified.
		if(coLevel <= 9)
		{
			displayValue[0] = bcdTo7Segments(&zeroSegment);
			displayValue[1] = displayValue[2];
			displayValue[2] = bcdTo7Segments(&emptyDigit);
		}
		else if(coLevel<=99)
		{
			displayValue[0] = displayValue[1];
			displayValue[1] = displayValue[2];
			displayValue[2] = bcdTo7Segments(&emptyDigit);
		}
	}

	if(status == HAL_OK)
	{
		memoryMap[hubCoAddress[0]] &= ~sSeg_Mask_D1_D12; memoryMap[hubCoAddress[0]] |= displayValue[0];
		memoryMap[hubCoAddress[1]] &= ~sSeg_Mask_D1_D12; memoryMap[hubCoAddress[1]] |= displayValue[1];
		memoryMap[hubCoAddress[2]] &= ~sSeg_Mask_D1_D12; memoryMap[hubCoAddress[2]] |= displayValue[2];

		status = writeDataToI2C(&hubCoAddress[0], &memoryMap[hubCoAddress[0]], sizeof(memoryMap[hubCoAddress[0]]));
		if(status != HAL_OK) return status;
		status = writeDataToI2C(&hubCoAddress[1], &memoryMap[hubCoAddress[1]], sizeof(memoryMap[hubCoAddress[1]]));
		if(status != HAL_OK) return status;
		status = writeDataToI2C(&hubCoAddress[2], &memoryMap[hubCoAddress[2]], sizeof(memoryMap[hubCoAddress[2]]));
		if(status != HAL_OK) return status;
	}
	else return status;
	return HAL_OK;
}

/// Function to Display Node Number
HAL_StatusTypeDef DisplayDriver_CNKD1103_HT16C24A::printNodeNumber(uint8_t nodeNumber)
{

	/*
			Function to print Outdoor Node Number on the display
			- (Node_Number)
			- Address of Node Number,
			-
	*/
	value = (float)nodeNumber;
	displayValue[0] = 0;
	status = floatTo7Segment(&value, &displayValue[0], true);
	memoryMap[nodeNumberAddress]	&=	~NODE_NUMBER_MASK;
	memoryMap[nodeNumberAddress]	|=	displayValue[0];
	if(status == HAL_OK)
	{
		return writeDataToI2C(&nodeNumberAddress, &memoryMap[nodeNumberAddress], sizeof(memoryMap[nodeNumberAddress]));
	}
	else
		return status;
}

/// Function to Display Node Signals Strength Level
HAL_StatusTypeDef DisplayDriver_CNKD1103_HT16C24A::nodeRfSignals(uint8_t strength)
{
	/*  Function to set battery cells status
		[Signals]	[Strength]
		- 0          Weak
		- .          .
		- .          .
		- 4          Strong
		-
	*/
	if(strength <= 4)
	{
		memoryMap[nodeRfSignalsAddress]	&=	~nodeRfSignalsMasks[strength];
		memoryMap[nodeRfSignalsAddress]	|=	nodeRfSignalsMasks[strength];
	}
	else
	{
		memoryMap[nodeRfSignalsAddress]	&=	~nodeRfSignalsMasks[4];
		memoryMap[nodeRfSignalsAddress]	|=	nodeRfSignalsMasks[4];
	}
	return writeDataToI2C(&nodeRfSignalsAddress, &memoryMap[nodeRfSignalsAddress], sizeof(memoryMap[nodeRfSignalsAddress]));
}

/// Function to Display Node Battery Level
HAL_StatusTypeDef DisplayDriver_CNKD1103_HT16C24A::nodeBatteryStatus(uint8_t batteryCells)
{
	/*  
		Function to set battery cells status
		[Cells]     [Status]
		- 0          Empty
		- .          .
		- .          .
		- 5          Full
		-
	*/
	if(batteryCells <= 7)
	{
		memoryMap[nodeBatteryAddress]	&=	~nodeBatteryMasks[batteryCells];
		memoryMap[nodeBatteryAddress]	|=	nodeBatteryMasks[batteryCells];
	}
	else
	{
		memoryMap[nodeBatteryAddress]	&=	~nodeBatteryMasks[6];
		memoryMap[nodeBatteryAddress]	|=	nodeBatteryMasks[6];
	}
	return writeDataToI2C(&nodeBatteryAddress, &memoryMap[nodeBatteryAddress], sizeof(memoryMap[nodeBatteryAddress]));

	/*switch (batteryCells) {
	case 0:	 memoryMap[0] = (memoryMap[0] &= 0x03) | BAT0_Mask;	lastBatStatus = BAT0_Mask;  break;
	case 1:	 memoryMap[0] = (memoryMap[0] &= 0x03) | BAT1_Mask;	lastBatStatus = BAT1_Mask;  break;
	case 2:	 memoryMap[0] = (memoryMap[0] &= 0x03) | BAT2_Mask;	lastBatStatus = BAT2_Mask;  break;
	case 3:	 memoryMap[0] = (memoryMap[0] &= 0x03) | BAT3_Mask;	lastBatStatus = BAT3_Mask;  break;
	case 4:	 memoryMap[0] = (memoryMap[0] &= 0x03) | BAT4_Mask;	lastBatStatus = BAT4_Mask;  break;
	case 5:	 memoryMap[0] = (memoryMap[0] &= 0x03) | BAT5_Mask;	lastBatStatus = BAT5_Mask;  break;
	}*/
}

/// Function to Display Node Temperature Level
HAL_StatusTypeDef DisplayDriver_CNKD1103_HT16C24A::printNodeTemperature(float temperatureValue, degree_t degree)
{
	/*
		Function to print Node Temperature Value on the display
		- (Temperature)
		- Address of Temperature Value,
		-
	*/
	// Setting Negative Sign for the Temperature Value.
	if(temperatureValue < 0)
	{
		memoryMap[nodeTempSignAddress] |= NODE_TEMP_NEG_SIGN_Mask;
		status =  writeDataToI2C(&nodeTempSignAddress, &memoryMap[nodeTempSignAddress], sizeof(memoryMap[nodeTempSignAddress]));
		if(status != HAL_OK) return status;
	}
	else
	{
		memoryMap[nodeTempSignAddress] &= ~NODE_TEMP_NEG_SIGN_Mask;
		status =  writeDataToI2C(&nodeTempSignAddress, &memoryMap[nodeTempSignAddress], sizeof(memoryMap[nodeTempSignAddress]));
		if(status != HAL_OK) return status;

	}

	// Printing Null Segment " - " for the Value Greater than the Range.
	if (abs(&temperatureValue) >= 200)
	{
		displayValue[0] = bcdTo7Segments(&nullSegment);
		displayValue[1] = displayValue[0];
		displayValue[2] = displayValue[0];
		memoryMap[nodeTempPointAddress] &= ~POINT_Mask;
	}
	else
	{
		// Generating 7-Segment values from floating point number.
		memoryMap[nodeTempPointAddress] |= POINT_Mask;
		status = floatTo7Segment(&temperatureValue, displayValue, false);
	}

	// Temperature Degree Type Selection.
	if(degree == degreeCelcius)
	{
		memoryMap[nodeDegreeSymbolsAddress] &= ~DEG_FAHRENHEIT_Mask;
		memoryMap[nodeDegreeSymbolsAddress] |= DEG_CELCIUS_Mask;
	}
	else if(degree == degreeFahrenheit)
	{
		memoryMap[nodeDegreeSymbolsAddress] &= ~DEG_CELCIUS_Mask;
		memoryMap[nodeDegreeSymbolsAddress] |= DEG_FAHRENHEIT_Mask;
	}

	// Updating Screen RAM connected on I2C.
	if(status == HAL_OK)
	{
		if((abs(&temperatureValue) >= 100.0) && (abs(&temperatureValue) < 200.0)) memoryMap[nodeTempMsdAddress] |= NODE_TEMP_MSD_Mask;
		else	memoryMap[nodeTempMsdAddress] &= ~NODE_TEMP_MSD_Mask;

		memoryMap[nodeTemperatureAddress[0]] &= ~sSeg_Mask_D1_D12; memoryMap[nodeTemperatureAddress[0]] |= displayValue[0];
		memoryMap[nodeTemperatureAddress[1]] &= ~sSeg_Mask_D1_D12; memoryMap[nodeTemperatureAddress[1]] |= displayValue[1];
		memoryMap[nodeTemperatureAddress[2]] &= ~sSeg_Mask_D1_D12; memoryMap[nodeTemperatureAddress[2]] |= displayValue[2];

		status = writeDataToI2C(&nodeTempPointAddress, &memoryMap[nodeTempPointAddress], sizeof(memoryMap[nodeTempPointAddress]));
		if(status != HAL_OK) return status;
		status = writeDataToI2C(&nodeTempMsdAddress, &memoryMap[nodeTempMsdAddress], sizeof(memoryMap[nodeTempMsdAddress]));
		if(status != HAL_OK) return status;
		status = writeDataToI2C(&nodeTemperatureAddress[0], &memoryMap[nodeTemperatureAddress[0]], sizeof(memoryMap[nodeTemperatureAddress[0]]));
		if(status != HAL_OK) return status;
		status = writeDataToI2C(&nodeTemperatureAddress[1], &memoryMap[nodeTemperatureAddress[1]], sizeof(memoryMap[nodeTemperatureAddress[1]]));
		if(status != HAL_OK) return status;
		status = writeDataToI2C(&nodeTemperatureAddress[2], &memoryMap[nodeTemperatureAddress[2]], sizeof(memoryMap[nodeTemperatureAddress[2]]));
		if(status != HAL_OK) return status;

		status = writeDataToI2C(&nodeDegreeSymbolsAddress, &memoryMap[nodeDegreeSymbolsAddress], sizeof(memoryMap[nodeDegreeSymbolsAddress]));
		if(status != HAL_OK) return status;
	}
	else return status;
	return HAL_OK;
}

/// Function to Display Node Humidity Level
HAL_StatusTypeDef DisplayDriver_CNKD1103_HT16C24A::printNodeHumidity(uint8_t humidityValue)
{
	/*
		Function to print Node Humidity Value on the display
		- (Humidity)
		- Address of Node Humidity Value,
		-
	*/
	// Printing Null Segment " - " for the Value Greater than the Range.
	if (humidityValue >= 100)
	{
		displayValue[0] = bcdTo7Segments(&nullSegment) << 1;
		displayValue[1] = displayValue[0];
		displayValue[2] = displayValue[0];
	}
	else
	{
		value = (float) humidityValue;
		// Generating 7-Segment values from floating point number.
		status = floatTo7Segment(&value, displayValue, false);

		// Shifting Values to left due to shift in segments position.
		displayValue[0] <<= 1;
		displayValue[1] <<= 1;
	}
	//delay(100);
	//Serial.print("Humidity : \t");

	// Updating Screen RAM connected on I2C.
	if(status == HAL_OK)
	{
		// Humidity Label Selection based on Humidity input Level.
		if(humidityValue <= humidityDryLevel)
		{
			memoryMap[nodeHumidityIconsAddress] &= ~NODE_HUMID_ICONS_CLEAR_MASK;
			memoryMap[nodeHumidityIconsAddress] |= nodeHumidityIconsMasks[0];
		}
		else if((humidityValue >= humidityComfortLowerLevel) && (humidityValue <= humidityComfortUpperLevel))
		{
			memoryMap[nodeHumidityIconsAddress] &= ~NODE_HUMID_ICONS_CLEAR_MASK;
			memoryMap[nodeHumidityIconsAddress] |= nodeHumidityIconsMasks[1];
		}
		else if((humidityValue >= humidityWetLowerLevel) && (humidityValue <= humidityWetUpperLevel))
		{
			memoryMap[nodeHumidityIconsAddress] &= ~NODE_HUMID_ICONS_CLEAR_MASK;
			memoryMap[nodeHumidityIconsAddress] |= nodeHumidityIconsMasks[2];
		}
		else
			memoryMap[nodeHumidityIconsAddress] &= ~NODE_HUMID_ICONS_CLEAR_MASK;

		memoryMap[nodeHumidityAddress[0]] &= ~sSeg_Mask_D13_D35; memoryMap[nodeHumidityAddress[0]] |= displayValue[0];
		memoryMap[nodeHumidityAddress[1]] &= ~sSeg_Mask_D13_D35; memoryMap[nodeHumidityAddress[1]] |= displayValue[1];

		status = writeDataToI2C(&nodeHumidityIconsAddress, &memoryMap[nodeHumidityIconsAddress], sizeof(memoryMap[nodeHumidityIconsAddress]));
		if(status != HAL_OK) return status;
		status = writeDataToI2C(&nodeHumidityAddress[0], &memoryMap[nodeHumidityAddress[0]], sizeof(memoryMap[nodeHumidityAddress[0]]));
		if(status != HAL_OK) return status;
		status = writeDataToI2C(&nodeHumidityAddress[1], &memoryMap[nodeHumidityAddress[1]], sizeof(memoryMap[nodeHumidityAddress[1]]));
		if(status != HAL_OK) return status;
	}
	else return status;
	return HAL_OK;
}

/// Function to Turn Weather Icons ON/OFF on the Display
HAL_StatusTypeDef DisplayDriver_CNKD1103_HT16C24A::printOutdoorWeather(uint8_t weather, bool enable)
{
	/*
		Function to print Outdoor Weather on the display
		- (Weather)
		-
	*/
	if(enable)	memoryMap[weatherAddress[weather]] |= weatherMasks[weather];
	else		memoryMap[weatherAddress[weather]] &= (~weatherMasks[weather]);

//	for(uint8_t i = 0; i < 9; i++)	memoryMap[weatherAddress[i]] &= (~weatherMasks[i]);
//	memoryMap[weatherAddress[weather]] |= weatherMasks[weather];
//	for(uint8_t i = 0; i < 9; i++)
//	{
		status = writeDataToI2C(&weatherAddress[weather], &memoryMap[weatherAddress[weather]], sizeof(memoryMap[weatherAddress[weather]]));
		if(status != HAL_OK)
		{
			return status;
		}
//	}
	return HAL_OK;
}

/// Function to Display Outdoor Air Quality Index
HAL_StatusTypeDef DisplayDriver_CNKD1103_HT16C24A::printOutdoorAirQualityIndex(uint16_t airQuality)
{
	/*
		Function to print Dust/Air Quality Value on the display
		- (Humidity)
		- Address of Humidity Value,
		-
	*/
	// Printing Null Segment " - " for the Value Greater than the Range.
	if (airQuality >= 1000)
	{
		displayValue[0] = bcdTo7Segments(&nullSegment) << 1;
		displayValue[1] = displayValue[0];
		displayValue[2] = displayValue[0];
	}
	else
	{
		value = (float)airQuality/10;
		// Generating 7-Segment values from floating point number.
		status = floatTo7Segment(&value, displayValue, false);

		// Removing 7-Segments Display of "0" to "Empty Digit" Segments and Adding when MSB is present.
		if((displayValue[1] == bcdTo7Segments(&zeroSegment)) && (airQuality <= 9))
			displayValue[1] = bcdTo7Segments(&emptyDigit);

		// Shifting Digit towards Left i.e. Left Justified.
		if(airQuality <= 9)
		{
			displayValue[0] = bcdTo7Segments(&zeroSegment);
			displayValue[1] = displayValue[2];
			displayValue[2] = bcdTo7Segments(&emptyDigit);
		}
		else if(airQuality<=99)
		{
			displayValue[0] = displayValue[1];
			displayValue[1] = displayValue[2];
			displayValue[2] = bcdTo7Segments(&emptyDigit);
		}

		// Shifting Values to left due to shift in segments position.
		displayValue[0] <<= 1;
		displayValue[1] <<= 1;
		displayValue[2] <<= 1;


	}

	// Updating Screen RAM connected on I2C.
	if(status == HAL_OK)
	{
		memoryMap[aqiOutAddress[0]] &= ~sSeg_Mask_D13_D35; memoryMap[aqiOutAddress[0]] |= displayValue[0];
		memoryMap[aqiOutAddress[1]] &= ~sSeg_Mask_D13_D35; memoryMap[aqiOutAddress[1]] |= displayValue[1];
		memoryMap[aqiOutAddress[2]] &= ~sSeg_Mask_D13_D35; memoryMap[aqiOutAddress[2]] |= displayValue[2];

		status = writeDataToI2C(&aqiOutAddress[0], &memoryMap[aqiOutAddress[0]], sizeof(memoryMap[aqiOutAddress[0]]));
		if(status != HAL_OK) return status;
		status = writeDataToI2C(&aqiOutAddress[1], &memoryMap[aqiOutAddress[1]], sizeof(memoryMap[aqiOutAddress[1]]));
		if(status != HAL_OK) return status;
		status = writeDataToI2C(&aqiOutAddress[2], &memoryMap[aqiOutAddress[2]], sizeof(memoryMap[aqiOutAddress[2]]));
		if(status != HAL_OK) return status;
	}
	else return status;
	return HAL_OK;
}

/// Function to Display Sunrise Time
HAL_StatusTypeDef DisplayDriver_CNKD1103_HT16C24A::printSunriseTime(uint8_t hours, uint8_t minutes)
{
	/*
		Function to print Sunrise Time on the display
		- (Hour, Minute, Meridiem)
		- Address of Hour,
		- Address of Minute,
		- Address of Meridiem
	*/

	/// Hours Updating Functionality
	// Limiting Hours
	if (hours >= 24)
	{
		displayValue[0] = bcdTo7Segments(&nullSegment) << 1;
		displayValue[1] = displayValue[0];
	}
	else
	{
		value = (float) hours;
		// Generating 7-Segment values from floating point number.
		status = floatTo7Segment(&value, displayValue, false);

		// Shifting Values to left due to shift in segments position.
		displayValue[0] <<= 1;
		displayValue[1] <<= 1;
	}

	// Updating Screen RAM connected on I2C.
	if(status == HAL_OK)
	{
		memoryMap[sunriseTimeAddress[0]] &= ~sSeg_Mask_D13_D35; memoryMap[sunriseTimeAddress[0]] |= displayValue[0];
		memoryMap[sunriseTimeAddress[1]] &= ~sSeg_Mask_D13_D35; memoryMap[sunriseTimeAddress[1]] |= displayValue[1];
		memoryMap[sunriseTimeAddress[2]] |= TIME_DATE_SEPARATOR_Mask;

		status = writeDataToI2C(&sunriseTimeAddress[0], &memoryMap[sunriseTimeAddress[0]], sizeof(memoryMap[sunriseTimeAddress[0]]));
		if(status != HAL_OK) return status;
		status = writeDataToI2C(&sunriseTimeAddress[1], &memoryMap[sunriseTimeAddress[1]], sizeof(memoryMap[sunriseTimeAddress[1]]));
		if(status != HAL_OK) return status;
		status = writeDataToI2C(&sunriseTimeAddress[2], &memoryMap[sunriseTimeAddress[2]], sizeof(memoryMap[sunriseTimeAddress[2]]));
		if(status != HAL_OK) return status;
	}
	else return status;

	/// Hours Updating Functionality
	// Limiting Minutes
	if (minutes >= 60)
	{
		displayValue[0] = bcdTo7Segments(&nullSegment) << 1;
		displayValue[1] = displayValue[0];
	}
	else
	{
		value = (float) minutes;
		// Generating 7-Segment values from floating point number.
		status = floatTo7Segment(&value, displayValue, false);

		// Shifting Values to left due to shift in segments position.
		displayValue[0] <<= 1;
		displayValue[1] <<= 1;
	}

	// Updating Screen RAM connected on I2C.
	if(status == HAL_OK)
	{
		memoryMap[sunriseTimeAddress[3]] &= ~sSeg_Mask_D13_D35; memoryMap[sunriseTimeAddress[3]] |= displayValue[0];
		memoryMap[sunriseTimeAddress[4]] &= ~sSeg_Mask_D13_D35; memoryMap[sunriseTimeAddress[4]] |= displayValue[1];

		status = writeDataToI2C(&sunriseTimeAddress[3], &memoryMap[sunriseTimeAddress[3]], sizeof(memoryMap[sunriseTimeAddress[3]]));
		if(status != HAL_OK) return status;
		status = writeDataToI2C(&sunriseTimeAddress[4], &memoryMap[sunriseTimeAddress[4]], sizeof(memoryMap[sunriseTimeAddress[4]]));
		if(status != HAL_OK) return status;
	}
	else return status;
	return HAL_OK;
}

///// Function to Display Sunset Time
HAL_StatusTypeDef DisplayDriver_CNKD1103_HT16C24A::printSunsetTime(uint8_t hours, uint8_t minutes)
{
	/*
		Function to print Sunset Time on the display
		- (Hour, Minute, Meridiem)
		- Address of Hour,
		- Address of Minute,
		- Address of Meridiem
	*/
	/// Hours Updating Functionality
	// Limiting Hours
	if (hours >= 24)
	{
		displayValue[0] = bcdTo7Segments(&nullSegment) << 1;
		displayValue[1] = displayValue[0];
	}
	else
	{
		value = (float) hours;
		// Generating 7-Segment values from floating point number.
		status = floatTo7Segment(&value, displayValue, false);

		// Shifting Values to left due to shift in segments position.
		displayValue[0] <<= 1;
		displayValue[1] <<= 1;
	}

	// Updating Screen RAM connected on I2C.
	if(status == HAL_OK)
	{
		memoryMap[sunsetTimeAddress[0]] &= ~sSeg_Mask_D13_D35; memoryMap[sunsetTimeAddress[0]] |= displayValue[0];
		memoryMap[sunsetTimeAddress[1]] &= ~sSeg_Mask_D13_D35; memoryMap[sunsetTimeAddress[1]] |= displayValue[1];
		memoryMap[sunsetTimeAddress[2]] |= TIME_DATE_SEPARATOR_Mask;

		status = writeDataToI2C(&sunsetTimeAddress[0], &memoryMap[sunsetTimeAddress[0]], sizeof(memoryMap[sunsetTimeAddress[0]]));
		if(status != HAL_OK) return status;
		status = writeDataToI2C(&sunsetTimeAddress[1], &memoryMap[sunsetTimeAddress[1]], sizeof(memoryMap[sunsetTimeAddress[1]]));
		if(status != HAL_OK) return status;
		status = writeDataToI2C(&sunsetTimeAddress[2], &memoryMap[sunsetTimeAddress[2]], sizeof(memoryMap[sunsetTimeAddress[2]]));
		if(status != HAL_OK) return status;
	}
	else return status;

	/// Hours Updating Functionality
	// Limiting Minutes
	if (minutes >= 60)
	{
		displayValue[0] = bcdTo7Segments(&nullSegment) << 1;
		displayValue[1] = displayValue[0];
	}
	else
	{
		value = (float) minutes;
		// Generating 7-Segment values from floating point number.
		status = floatTo7Segment(&value, displayValue, false);

		// Shifting Values to left due to shift in segments position.
		displayValue[0] <<= 1;
		displayValue[1] <<= 1;
	}

	// Updating Screen RAM connected on I2C.
	if(status == HAL_OK)
	{
		memoryMap[sunsetTimeAddress[3]] &= ~sSeg_Mask_D13_D35; memoryMap[sunsetTimeAddress[3]] |= displayValue[0];
		memoryMap[sunsetTimeAddress[4]] &= ~sSeg_Mask_D13_D35; memoryMap[sunsetTimeAddress[4]] |= displayValue[1];

		status = writeDataToI2C(&sunsetTimeAddress[3], &memoryMap[sunsetTimeAddress[3]], sizeof(memoryMap[sunsetTimeAddress[3]]));
		if(status != HAL_OK) return status;
		status = writeDataToI2C(&sunsetTimeAddress[4], &memoryMap[sunsetTimeAddress[4]], sizeof(memoryMap[sunsetTimeAddress[4]]));
		if(status != HAL_OK) return status;
	}
	else return status;
	return HAL_OK;

}

///// Function to Display Date and Day Name
HAL_StatusTypeDef DisplayDriver_CNKD1103_HT16C24A::printDate(uint8_t day, uint8_t month, uint8_t dayName)
{
	/*
		Function to print Date on the display
		- (Day, Month, Day_Name)
		- Address of Day,
		- Address of Month,
		- Address of DayName
	*/
	/// Variable array to get 14-Segments Day Data.
	uint8_t
		dayDisplayValue[6] = { 0 };

	/// Day Updating Functionality
	// Limiting Hours
	if (day >= 32)
	{
		displayValue[0] = bcdTo7Segments(&nullSegment) << 1;
		displayValue[1] = displayValue[0];
	}
	else
	{
		value = (float) day;
		// Generating 7-Segment values from floating point number.
		status = floatTo7Segment(&value, displayValue, false);

		// Shifting Values to left due to shift in segments position.
		displayValue[0] <<= 1;
		displayValue[1] <<= 1;
	}

	// Updating Screen RAM connected on I2C.
	if(status == HAL_OK)
	{
		memoryMap[dateAddress[0]] &= ~sSeg_Mask_D13_D35; memoryMap[dateAddress[0]] |= displayValue[0];
		memoryMap[dateAddress[1]] &= ~sSeg_Mask_D13_D35; memoryMap[dateAddress[1]] |= displayValue[1];
		memoryMap[dateAddress[2]] |= TIME_DATE_SEPARATOR_Mask;

		status = writeDataToI2C(&dateAddress[0], &memoryMap[dateAddress[0]], sizeof(memoryMap[dateAddress[0]]));
		if(status != HAL_OK) return status;
		status = writeDataToI2C(&dateAddress[1], &memoryMap[dateAddress[1]], sizeof(memoryMap[dateAddress[1]]));
		if(status != HAL_OK) return status;
		status = writeDataToI2C(&dateAddress[2], &memoryMap[dateAddress[2]], sizeof(memoryMap[dateAddress[2]]));
		if(status != HAL_OK) return status;
	}
	else return status;

	/// Month Updating Functionality
	// Limiting Minutes
	if (month >= 13)
	{
		displayValue[0] = bcdTo7Segments(&nullSegment) << 1;
		displayValue[1] = displayValue[0];
	}
	else
	{
		value = (float) month;
		// Generating 7-Segment values from floating point number.
		status = floatTo7Segment(&value, displayValue, false);

		// Shifting Values to left due to shift in segments position.
		displayValue[0] <<= 1;
		displayValue[1] <<= 1;
	}

	status = dayTo14Segment(dayName, dayDisplayValue);
	// Updating Screen RAM connected on I2C.
	if(status == HAL_OK)
	{
		memoryMap[dateAddress[3]] &= ~sSeg_Mask_D13_D35; memoryMap[dateAddress[3]] |= displayValue[0];
		memoryMap[dateAddress[4]] &= ~sSeg_Mask_D13_D35; memoryMap[dateAddress[4]] |= displayValue[1];

		memoryMap[weekdayAddress[0]] &= ~WEEKDAY_DIGIT_Mask;	memoryMap[weekdayAddress[0]] |= dayDisplayValue[0];
		memoryMap[weekdayAddress[1]] &= ~WEEKDAY_DIGIT_Mask;	memoryMap[weekdayAddress[1]] |= dayDisplayValue[1];
		memoryMap[weekdayAddress[2]] &= ~WEEKDAY_DIGIT_Mask;	memoryMap[weekdayAddress[2]] |= dayDisplayValue[2];
		memoryMap[weekdayAddress[3]] &= ~WEEKDAY_DIGIT_Mask;	memoryMap[weekdayAddress[3]] |= dayDisplayValue[3];
		memoryMap[weekdayAddress[4]] &= ~WEEKDAY_DIGIT_Mask;	memoryMap[weekdayAddress[4]] |= dayDisplayValue[4];
		memoryMap[weekdayAddress[5]] &= ~WEEKDAY_DIGIT_Mask;	memoryMap[weekdayAddress[5]] |= dayDisplayValue[5];

		status = writeDataToI2C(&dateAddress[3], &memoryMap[dateAddress[3]], sizeof(memoryMap[dateAddress[3]]));
		if(status != HAL_OK) return status;
		status = writeDataToI2C(&dateAddress[4], &memoryMap[dateAddress[4]], sizeof(memoryMap[dateAddress[4]]));
		if(status != HAL_OK) return status;

		status = writeDataToI2C(&weekdayAddress[0], &memoryMap[weekdayAddress[0]], sizeof(memoryMap[weekdayAddress[0]]));
		if(status != HAL_OK) return status;
		status = writeDataToI2C(&weekdayAddress[1], &memoryMap[weekdayAddress[1]], sizeof(memoryMap[weekdayAddress[1]]));
		if(status != HAL_OK) return status;
		status = writeDataToI2C(&weekdayAddress[2], &memoryMap[weekdayAddress[2]], sizeof(memoryMap[weekdayAddress[2]]));
		if(status != HAL_OK) return status;
		status = writeDataToI2C(&weekdayAddress[3], &memoryMap[weekdayAddress[3]], sizeof(memoryMap[weekdayAddress[3]]));
		if(status != HAL_OK) return status;
		status = writeDataToI2C(&weekdayAddress[4], &memoryMap[weekdayAddress[4]], sizeof(memoryMap[weekdayAddress[4]]));
		if(status != HAL_OK) return status;
		status = writeDataToI2C(&weekdayAddress[5], &memoryMap[weekdayAddress[5]], sizeof(memoryMap[weekdayAddress[5]]));
		if(status != HAL_OK) return status;
	}
	else return status;
	return HAL_OK;

}

///// Function to Display Time
HAL_StatusTypeDef DisplayDriver_CNKD1103_HT16C24A::printTime(uint8_t hours, uint8_t minutes, meridiem_t MERIDIEM)
{
	/*
		Function to print Time on the display
		- (Hour, Minute, MERIDIEM)
		- Address of Hour,
		- Address of Minute,
		- Address of MERIDIEM
	*/
	/// Hours Updating Functionality
	// Limiting Hours
	if (hours >= 24)
	{
		displayValue[0] = bcdTo7Segments(&nullSegment) << 1;
		displayValue[1] = displayValue[0];
	}
	else
	{
		value = (float) hours;
		// Generating 7-Segment values from floating point number.
		status = floatTo7Segment(&value, displayValue, false);

		// Shifting Values to left due to shift in segments position.
		displayValue[0] <<= 1;
		displayValue[1] <<= 1;
	}

	// Updating Screen RAM connected on I2C.
	if(status == HAL_OK)
	{
		memoryMap[timeAddress[0]] &= ~sSeg_Mask_D13_D35; memoryMap[timeAddress[0]] |= displayValue[0];
		memoryMap[timeAddress[1]] &= ~sSeg_Mask_D13_D35; memoryMap[timeAddress[1]] |= displayValue[1];
		memoryMap[timeAddress[2]] |= TIME_DATE_SEPARATOR_Mask;

		status = writeDataToI2C(&timeAddress[0], &memoryMap[timeAddress[0]], sizeof(memoryMap[timeAddress[0]]));
		if(status != HAL_OK) return status;
		status = writeDataToI2C(&timeAddress[1], &memoryMap[timeAddress[1]], sizeof(memoryMap[timeAddress[1]]));
		if(status != HAL_OK) return status;
		status = writeDataToI2C(&timeAddress[2], &memoryMap[timeAddress[2]], sizeof(memoryMap[timeAddress[2]]));
		if(status != HAL_OK) return status;
	}
	else return status;

	/// Hours Updating Functionality
	// Limiting Minutes
	if (minutes >= 60)
	{
		displayValue[0] = bcdTo7Segments(&nullSegment) << 1;
		displayValue[1] = displayValue[0];
	}
	else
	{
		value = (float) minutes;
		// Generating 7-Segment values from floating point number.
		status = floatTo7Segment(&value, displayValue, false);

		// Shifting Values to left due to shift in segments position.
		displayValue[0] <<= 1;
		displayValue[1] <<= 1;
	}

	// Updating Screen RAM connected on I2C.
	if(status == HAL_OK)
	{
		// AM / PM Selection.
		if(MERIDIEM == AM)
		{
			memoryMap[AMAddress] |= AM_PM_Mask; memoryMap[PMAddress] &= ~AM_PM_Mask;
		}
		else if(MERIDIEM == PM)
		{
			memoryMap[PMAddress] |= AM_PM_Mask; memoryMap[AMAddress] &= ~AM_PM_Mask;
		}
		else
		{
			memoryMap[PMAddress] &= ~AM_PM_Mask;
			memoryMap[AMAddress] &= ~AM_PM_Mask;
		}
		memoryMap[timeAddress[3]] &= ~sSeg_Mask_D13_D35; memoryMap[timeAddress[3]] |= displayValue[0];
		memoryMap[timeAddress[4]] &= ~sSeg_Mask_D13_D35; memoryMap[timeAddress[4]] |= displayValue[1];

		status = writeDataToI2C(&timeAddress[3], &memoryMap[timeAddress[3]], sizeof(memoryMap[timeAddress[3]]));
		if(status != HAL_OK) return status;
		status = writeDataToI2C(&timeAddress[4], &memoryMap[timeAddress[4]], sizeof(memoryMap[timeAddress[4]]));
		if(status != HAL_OK) return status;

		status = writeDataToI2C(&AMAddress, &memoryMap[AMAddress], sizeof(memoryMap[AMAddress]));
		if(status != HAL_OK) return status;
		status = writeDataToI2C(&PMAddress, &memoryMap[PMAddress], sizeof(memoryMap[PMAddress]));
		if(status != HAL_OK) return status;
	}
	else return status;
	return HAL_OK;

}


/// Function to Print Hub Temperature value to 7-Segments Displays


float DisplayDriver_CNKD1103_HT16C24A::abs(float* number)
{
	if(*number < 0)
		return (-(float)(*number));
	else return ((float)*number);
}

// Sub Function to convert a floating point number to 7-segment display format
HAL_StatusTypeDef DisplayDriver_CNKD1103_HT16C24A::floatTo7Segment(float* number, uint8_t* display, bool node) {

	// Extract the whole number and decimal parts
	uint8_t wholePart = (uint8_t)(abs(number));
	uint8_t decimalPart = (uint8_t)((abs(number) - wholePart) * 10);

	// Extract individual digits
	uint8_t tens = (wholePart / 10) % 10;
	uint8_t units = wholePart % 10;

	//if(wholePart < 10) tens = 0;
	// Convert each digit to 7-segment display format
	if(node)
	{
		*display = nodeBcdTo7Segments(&wholePart);
	}
	else
	{
		if (tens >= (uint8_t)1 || wholePart >= 100)
			display[0] = bcdTo7Segments(&tens);
		else display[0] = bcdTo7Segments(&zeroSegment); // emptyDigit.
		display[1] = bcdTo7Segments(&units);
		display[2] = bcdTo7Segments(&decimalPart);
	}
	/*for (int i = 0; i < 3; i++) { Serial.print('\t'); Serial.print(display[i]); }
	Serial.println();
	Serial.print("Number: ");			Serial.print(*number);
	Serial.print("\tWhole Part: ");		Serial.print(wholePart);
	Serial.print("\tTens: ");			Serial.print(tens);
	Serial.print("\tUnits: ");			Serial.print(units);
	Serial.print("\tDecimal Part: ");	Serial.println(decimalPart);*/
	return HAL_OK;
}

// Sub Function to convert Day into 14-segment display format
HAL_StatusTypeDef DisplayDriver_CNKD1103_HT16C24A::dayTo14Segment(uint8_t day, uint8_t* dayDisplay) {
	switch (day) {			//b0AFHGELM							0b0IJBKCND
	case Monday:
		dayDisplay[0]	=	 0b00110100;	dayDisplay[1]	=	0b00110100; // Digit-A	->	'M'.
		dayDisplay[2]	=	 0b01100100;	dayDisplay[3]	=	0b00010101; // Digit-B	->	'O'.
		dayDisplay[4]	=	 0b00110100;	dayDisplay[5]	=	0b00010110; // Digit-C	->	'N'.
		break;
	case Tuesday:
		dayDisplay[0]	=	 0b01000001;	dayDisplay[1]	=	0b01000000; // Digit-A	->	'T'.
		dayDisplay[2]	=	 0b00100100;	dayDisplay[3]	=	0b00010101; // Digit-B	->	'U'.
		dayDisplay[4]	=	 0b01101100;	dayDisplay[5]	=	0b00000001; // Digit-C	->	'E'.
		break;
	case Wednesday:
		dayDisplay[0]	=	 0b00100110;	dayDisplay[1]	=	0b00010110; // Digit-A	->	'W'.
		dayDisplay[2]	=	 0b01101100;	dayDisplay[3]	=	0b00000001; // Digit-B	->	'E'.
		dayDisplay[4]	=	 0b01000001;	dayDisplay[5]	=	0b01010101; // Digit-C	->	'D'.
		break;
	case Thursday:
		dayDisplay[0]	=	 0b01000001;	dayDisplay[1]	=	0b01000000; // Digit-A	->	'T'.
		dayDisplay[2]	=	 0b00101100;	dayDisplay[3]	=	0b00011100; // Digit-B	->	'H'.
		dayDisplay[4]	=	 0b00100100;	dayDisplay[5]	=	0b00010101; // Digit-C	->	'U'.
		break;
	case Friday:
		dayDisplay[0]	=	 0b01101100;	dayDisplay[1]	=	0b00000000; // Digit-A	->	'F'.
		dayDisplay[2]	=	 0b01101100;	dayDisplay[3]	=	0b00011010; // Digit-B	->	'R'.
		dayDisplay[4]	=	 0b01000001;	dayDisplay[5]	=	0b01000001; // Digit-C	->	'I'.
		break;
	case Saturday:
		dayDisplay[0]	=	 0b01101000;	dayDisplay[1]	=	0b00001101; // Digit-A	->	'S'.
		dayDisplay[2]	=	 0b01101100;	dayDisplay[3]	=	0b00011100; // Digit-B	->	'A'.
		dayDisplay[4]	=	 0b01000001;	dayDisplay[5]	=	0b01000000; // Digit-C	->	'T'.
		break;
	case Sunday:
		dayDisplay[0]	=	 0b01101000;	dayDisplay[1]	=	0b00001101; // Digit-A	->	'S'.
		dayDisplay[2]	=	 0b00100100;	dayDisplay[3]	=	0b00010101; // Digit-B	->	'U'.
		dayDisplay[4]	=	 0b00110100;	dayDisplay[5]	=	0b00010110; // Digit-C	->	'N'.
		break;
	default:
		dayDisplay[0]	=	 0b00001000;	dayDisplay[1]	=	0b00001000; // Digit-A	->	'--'.
		dayDisplay[2]	=	 0b00001000;	dayDisplay[3]	=	0b00001000; // Digit-B	->	'--'.
		dayDisplay[4]	=	 0b00001000;	dayDisplay[5]	=	0b00001000; // Digit-C	->	'--'.
		break;
	}
	return HAL_OK;
}
// Sub Function to convert a BCD digit to 7-segment display format
uint8_t DisplayDriver_CNKD1103_HT16C24A::bcdTo7Segments(uint8_t* bcdDigit) {
	switch (*bcdDigit) {//b0DECGFBA		0bCGB0DEFA		0bGFEDCBA
	case 0:		return	 0b01110111;//	0b10101111;	//	0b0111111;	//	Actual 7 Segments should looks like ---
	case 1:		return	 0b00010010;//	0b10100000;	//	0b0000110;	//	<-- this but I had replaced it with ---
	case 2:		return	 0b01101011;//	0b01101101;	//	0b1011011;	//	the one that matches our RAM maping ---
	case 3:		return	 0b01011011;//	0b11101001;	//	0b1001111;	//	And to decrease data manipulation complexity.
	case 4:		return	 0b00011110;//	0b11100010;	//	0b1100110;
	case 5:		return	 0b01011101;//	0b11001011;	//	0b1101101;
	case 6:		return	 0b01111101;//	0b11001111;	//	0b1111101;
	case 7:		return	 0b00010011;//	0b10100001;	//	0b0000111;
	case 8:		return	 0b01111111;//	0b11101111;	//	0b1111111;
	case 9:		return	 0b01011111;//	0b11101011;	//	0b1101111;
	case 10:	return	 0b00000000;//	0b00000000;	//	0b0000000;
	default:	return	 0b00001000;//	0b01000000;	//	0b1000000;	// Invalid BCD digit
	}
}

// Sub Function to convert a BCD digit to 7-segment display format
uint8_t DisplayDriver_CNKD1103_HT16C24A::nodeBcdTo7Segments(uint8_t* bcdDigit) {
	switch (*bcdDigit) {//bABFGCED0		0bCGB0DEFA		0bGFEDCBA
	//case 0:		return	 0b11101110;//	0b10101111;	//	0b0111111;	//	Actual 7 Segments should looks like ---
	case 1:		return	 0b01001000;//	0b10100000;	//	0b0000110;	//	<-- this but I had replaced it with ---
	case 2:		return	 0b11010110;//	0b01101101;	//	0b1011011;	//	the one that matches our RAM maping ---
	case 3:		return	 0b11011010;//	0b11101001;	//	0b1001111;	//	And to decrease data manipulation complexity.
	case 4:		return	 0b01111000;//	0b11100010;	//	0b1100110;
	case 5:		return	 0b10111010;//	0b11001011;	//	0b1101101;
	case 6:		return	 0b10111110;//	0b11001111;	//	0b1111101;
	case 7:		return	 0b11001000;//	0b10100001;	//	0b0000111;
	case 8:		return	 0b11111110;//	0b11101111;	//	0b1111111;
	case 9:		return	 0b11111010;//	0b11101011;	//	0b1101111;
	default:	return	 0b00010000;//	0b00000000;	//	0b0000000;	// Invalid BCD digit
	}
}
// Function to Send updated LCD Display values to RAM (AiP16C22) 
HAL_StatusTypeDef DisplayDriver_CNKD1103_HT16C24A::updateDisplay()
{
	uint8_t writeCommand[54] = {0x80, 0x00};
	for(uint8_t i = 0; i < sizeof(memoryMap); i++)
	{
		writeCommand[i + 2] = memoryMap[i];
	}
	i2cState = HAL_I2C_Master_Transmit(&i2cPort, i2cWriteAddress, writeCommand, sizeof(writeCommand), 7);
	//i2cState = HAL_I2C_Master_Transmit(&i2cPort, i2cAddress, memoryMap, sizeof(memoryMap), 100);
	return i2cState;
}

// Function to Write control Registers settings through I2C 
HAL_StatusTypeDef DisplayDriver_CNKD1103_HT16C24A::writeCommandToI2C(const uint8_t* regAddr, uint8_t* regData, size_t size)
{
	uint8_t commandByte[] = {*regAddr, *regData};
	i2cState = HAL_I2C_Master_Transmit(&i2cPort, i2cWriteAddress, commandByte, sizeof(commandByte), 1);
//	i2cState = HAL_I2C_Master_Transmit(&i2cPort, i2cAddress, (uint8_t*)regAddr, (uint8_t)1, (uint32_t)10);
//	i2cState = HAL_I2C_Master_Transmit(&i2cPort, i2cAddress, regData, size, 100);
	return i2cState;
}

// Function to Write Whole Data Memory Settings through I2C
HAL_StatusTypeDef DisplayDriver_CNKD1103_HT16C24A::writeDataToI2C(const uint8_t* regAddr, uint8_t* regData, size_t size)
{
	uint8_t writeCommand[] = {0x80, *regAddr, *regData};
	i2cState = HAL_I2C_Master_Transmit(&i2cPort, i2cWriteAddress, writeCommand, sizeof(writeCommand), 1);
//	i2cState = HAL_I2C_Master_Transmit(&i2cPort, i2cAddress, regData, size, 100);
	return i2cState;
}

// Function to Read Registers settings through I2C
HAL_StatusTypeDef DisplayDriver_CNKD1103_HT16C24A::readRAM(const uint8_t* regAddr, uint8_t* regData, size_t size)
{
	uint8_t writeCommand[] = {0x80, *regAddr};

	i2cState = HAL_I2C_Master_Transmit(&i2cPort, i2cWriteAddress, writeCommand, sizeof(writeCommand), 7); // Actual Time is 6 MillisSeconds.
	if(i2cState == HAL_OK)
		i2cState = HAL_I2C_Master_Receive(&i2cPort, i2cReadAddress, regData, size, 1000);
#ifdef debug
	char str[100] = {'\0'};
	size_t Size = sprintf((char*)str, "I2c Read Address: 0x%x, I2C Write Address: 0x%x,  Register Address: 0x%x,\tRegister Data: 0x%x\r\n", i2cReadAddress, i2cWriteAddress, *regAddr, *regData);
	HAL_UART_Transmit(&Uart, (uint8_t*)str, Size, 2000); memset(str, 0, sizeof(str));
#endif
	return i2cState;
}

// Function to Read RAM Registers settings through I2C
HAL_StatusTypeDef DisplayDriver_CNKD1103_HT16C24A::readDisplayRAM(void)
{
	uint8_t writeCommand[] = {0x80, 0x00};

	status = HAL_I2C_Master_Transmit(&i2cPort, i2cWriteAddress, writeCommand, sizeof(writeCommand), 7); // Actual Time is 6 MillisSeconds.
	HAL_Delay(10);
	if(i2cState == HAL_OK)
		i2cState = HAL_I2C_Master_Receive(&i2cPort, i2cReadAddress, memoryMap, sizeof(memoryMap), 1000);
#ifdef debug
	char str[100] = {'\0'};
	size_t Size = sprintf((char*)str, "I2c Read Address: 0x%x, I2C Write Address: 0x%x,  Register Address: 0x%x,\tRegister Data: 0x%x\r\n", i2cReadAddress, i2cWriteAddress, *regAddr, *regData);
	HAL_UART_Transmit(&Uart, (uint8_t*)str, Size, 2000); memset(str, 0, sizeof(str));
#endif
	return i2cState;
}

//// Function to Write Data Registers settings through I2C
//HAL_StatusTypeDef DisplayDriver_CNKD1103_HT16C24A::writeToI2C(const uint8_t* regAddr, uint8_t* regData, size_t size)
//{
//
//	i2cState = HAL_I2C_Master_Transmit(&i2cPort, (uint16_t)i2cWriteAddress, (uint8_t*)regData, size, 100);
//	return i2cState;
//}
//
//// Function to Write Registers settings through I2C (Currently, Not in Use).
//HAL_StatusTypeDef DisplayDriver_CNKD1103_HT16C24A::writeToDisplayI2C(const uint8_t* regAddr, uint8_t* regData, size_t size)
//{
//	i2cState = HAL_I2C_Master_Transmit(&i2cPort, i2cWriteAddress, (uint8_t*)regData, size, 100);
//	return i2cState;
//}
//
//// Function to Read control Registers settings through I2C
//HAL_StatusTypeDef DisplayDriver_CNKD1103_HT16C24A::readRegister(const uint8_t* regAddr, uint8_t* regData, size_t size)
//{
//	uint8_t writeCommand[] = {*regAddr};
//
//		i2cState = HAL_I2C_Master_Transmit(&i2cPort, i2cWriteAddress, writeCommand, sizeof(writeCommand), 100);
//	if(i2cState == HAL_OK)
//		i2cState = HAL_I2C_Master_Receive(&i2cPort, i2cReadAddress, regData, size, 100);
//
//	char str[100] = {'\0'};
//#ifdef debug
//	size_t Size = sprintf((char*)str, "I2c Read Address: 0x%x, I2C Write Address: 0x%x,  Register Address: 0x%x,\tRegister Data: 0x%x\r\n", i2cReadAddress, i2cWriteAddress, *regAddr, *regData);
//	HAL_UART_Transmit(&Uart, (uint8_t*)str, Size, 2000); memset(str, 0, sizeof(str));
//#endif
//	return i2cState;
//}
