// DisplayDriver_AiP16C22

// Header Files of the Libraries required
#include "DisplayDriver_AiP16C22.h"
#include <Wire.h>

// Consturcutor for LCD Object Creation
DisplayDriver_AiP16C22::DisplayDriver_AiP16C22(uint8_t address)
{
	// Slave Address Assignment
	i2cAddress = address;
}

// Use this function in the Setup Block
uint8_t DisplayDriver_AiP16C22::displayInit(uint8_t address)
{
	// Implementation for I2C RAM based display initialization
	// 
	// Master Address Assignment

	/*Wire.beginTransmission(0x55);
	uint8_t error = Wire.endTransmission();
	Serial.print(error? "NodeMCU Failed error: ": "NodeMCU Success");
	delay(10);
	Serial.println(error);
	delay(10);*/

	Wire.begin();					//Wire.begin(address);
	Wire.beginTransmission(i2cAddress);
	return Wire.endTransmission();
}


// Function to set bias Display values
uint8_t DisplayDriver_AiP16C22::biasOfDisplay(bool enable)
{
	/*
		LCD display off address 80H
		- {1 0 0 F S E 0 M0}LSB
		- Control [M0] here
	*/
	if (enable) modeSettings |= BIAS_DISP_Mask; else modeSettings &= (~BIAS_DISP_Mask);
	//writeToI2C(modeSettings);
	return writeToDisplayI2C(modeSettings);
}

// Function to Set SEG/VLCD pins settings
uint8_t DisplayDriver_AiP16C22::segVlcdSetting(uint8_t settings)
{
	/*
		Birghtness of LCD display address 70H
		- {0 1 DE VE DA3 DA2 DA1 DA0}LSB
		- Control [DE VE] here
	*/

	uint8_t intVoltageCtrlValue = (settings & BRIGT_EN_Mask) | brightCtrlEnAddress;
	//writeToI2C(intVoltageCtrlValue);
	return writeToDisplayI2C(intVoltageCtrlValue);
}

// Function to Set Frame frequency
uint8_t DisplayDriver_AiP16C22::frequency(bool freq)
{
	/*
		Frequency of LCD display driver address 80H
		- {1 0 0 F S E 0 M0}LSB
		- Control [F] bit here
	*/

	if (freq) modeSettings |= FREQ_DISP_Mask; else modeSettings &= (~FREQ_DISP_Mask);
	//writeToI2C(modeSettings);
	return writeToDisplayI2C(modeSettings);
}


// Function to Turn OFF the LCD Display
uint8_t DisplayDriver_AiP16C22::display(bool enable)
{
	/*
		LCD display off address 80H
		- {1 0 0 F S E 0 M0}LSB
		- Control [E] here
	*/

	if (enable) modeSettings |= OFF_DISP_Mask; else modeSettings &= (~OFF_DISP_Mask);
	//writeToI2C(modeSettings);
	return writeToDisplayI2C(modeSettings);
}

// Function to Stop working of Display Driver IC (AiP16C22)
uint8_t DisplayDriver_AiP16C22::disableDisplayDriver(bool enable)
{
	/*
		Disable LCD display driver address 80H
		- {1 0 0 F S E 0 M0}LSB
		- Control [S] bit here
	*/

	if (enable) modeSettings |= OSC_DISP_Mask; else modeSettings &= (~OSC_DISP_Mask);
	//writeToI2C(modeSettings);
	return writeToDisplayI2C(modeSettings);
}

// Function to Control LCD Display Brightness
uint8_t DisplayDriver_AiP16C22::brightness(uint8_t bright)
{
	/*
		Birghtness of LCD display address 70H
		- {0 1 DE VE DA3 DA2 DA1 DA0}LSB
		- Control [DA3 DA2 DA1 DA0] here
	*/

	uint8_t brightnessValue = (bright & BRIGT_DISP_Mask) | intVoltAdjAddress;
	//writeToI2C(brightnessValue);
	return writeToDisplayI2C(brightnessValue);
}

// Function to Control blinking of Display
uint8_t DisplayDriver_AiP16C22::blinkDisplay(uint8_t blinkFreq)
{
	/*
		Blinking Frequency Command address C0H
		- {1 1 0 0 0 0 BK1 BK0}LSB
	*/

	uint8_t blinkValue = (blinkFreq & BLNK_DISP_Mask) | blinkRegAddress;
	//writeToI2C(blinkValue);
	return writeToDisplayI2C(blinkValue);
}

// Use this function in the Loop Block
uint8_t DisplayDriver_AiP16C22::displayClear()
{
	// Implementation for clearing the display
	for (uint8_t i = 0; i < memSize; i++) memoryMap[i] = 0x00; //Clearing all the memory map
	lineEnable(true);
	return updateDisplay();
}

// Use this function to set and clear icon in the Loop Block
uint8_t  DisplayDriver_AiP16C22::icon(uint8_t iconType, bool enable)
{
	// Icon cases declarations for accessing settings of icon function 
	static const uint8_t BLE_ICON		= 1;
	static const uint8_t WIFI_ICON		= 2;
	static const uint8_t BAT_ICON		= 3;
	static const uint8_t DEG_F_ICON		= 4;
	static const uint8_t DEG_C_ICON		= 5;
	static const uint8_t ICE_ICON		= 6;
	static const uint8_t FIRE_ICON		= 7;
	static const uint8_t HUMID_ICON		= 8;
	static const uint8_t AIR_ICON		= 9;
	static const uint8_t PERCENT_ICON	= 10;

	// Implementation for enabling or disabling specified icon
	switch (iconType) {
	case BLE_ICON:		if (enable) memoryMap[0] |= BLE_ICON_Mask;							else memoryMap[0] &= (~BLE_ICON_Mask);		break;
	case WIFI_ICON:		if (enable) memoryMap[0] |= WIFI_ICON_Mask;							else memoryMap[0] &= (~WIFI_ICON_Mask);		break;
	case BAT_ICON:		if (enable) memoryMap[0] |= (BAT_ICON_Mask & lastBatStatus);		else memoryMap[0] &= (~BAT_ICON_Mask);		break;
	case DEG_F_ICON:	if (enable) memoryMap[1] = (memoryMap[1] & 0xEC) | DEG_F_ICON_Mask;	else memoryMap[1] &= (~DEG_F_ICON_Mask);	break;
	case DEG_C_ICON:	if (enable)	memoryMap[1] = (memoryMap[1] & 0xEC) | DEG_C_ICON_Mask;	else memoryMap[1] &= (~DEG_C_ICON_Mask);	break;
	case ICE_ICON:		if (enable)	memoryMap[1] |= ICE_ICON_Mask;							else memoryMap[1] &= (~ICE_ICON_Mask);		break;
	case FIRE_ICON:		if (enable)	memoryMap[1] |= FIRE_ICON_Mask;							else memoryMap[1] &= (~FIRE_ICON_Mask);		break;
	case HUMID_ICON:	if (enable)	memoryMap[7] |= HUMID_ICON_Mask;						else memoryMap[7] &= (~HUMID_ICON_Mask);	break;
	case AIR_ICON:		if (enable)	memoryMap[7] |= AIR_ICON_Mask;							else memoryMap[7] &= (~AIR_ICON_Mask);		break;
	case PERCENT_ICON:	if (enable)	memoryMap[4] |= PERCENT_ICON_Mask;						else memoryMap[4] &= (~PERCENT_ICON_Mask);	break;
	default: ;
	}
	return updateDisplay();
}

uint8_t  DisplayDriver_AiP16C22::batteryStatus(uint8_t batteryCells)
{
	
	switch (batteryCells) {
	case 0:	 memoryMap[0] = (memoryMap[0] &= 0x03) | BAT0_Mask;	lastBatStatus = BAT0_Mask;  break;
	case 1:	 memoryMap[0] = (memoryMap[0] &= 0x03) | BAT1_Mask;	lastBatStatus = BAT1_Mask;  break;
	case 2:	 memoryMap[0] = (memoryMap[0] &= 0x03) | BAT2_Mask;	lastBatStatus = BAT2_Mask;  break;
	case 3:	 memoryMap[0] = (memoryMap[0] &= 0x03) | BAT3_Mask;	lastBatStatus = BAT3_Mask;  break;
	case 4:	 memoryMap[0] = (memoryMap[0] &= 0x03) | BAT4_Mask;	lastBatStatus = BAT4_Mask;  break;
	case 5:	 memoryMap[0] = (memoryMap[0] &= 0x03) | BAT5_Mask;	lastBatStatus = BAT5_Mask;  break;
	}
	return updateDisplay();
}

// Function to Print values to 7-Segements Displays
uint8_t  DisplayDriver_AiP16C22::printToDisplay(float temperatureValue, float humidValue)
{
	// Implementation for printing values on the display
	uint8_t temperatureDisplay[3] = { 0x00,0x00,0x00 };
	uint8_t humidDisplay[3] = { 0x00,0x00,0x00 };

	if (temperatureValue >= 200)	temperatureValue = 199.9;
	if (humidValue >= 100)			humidValue = 99.9;

	// Generationg 7-Segment values from floating point number
	//Serial.println(); Serial.print("Temperature : \t");
	floatTo7Segment(&temperatureValue, temperatureDisplay);
	//delay(100);
	//Serial.print("Humidity : \t");
	floatTo7Segment(&humidValue, humidDisplay);

	for (uint8_t i = 1; i <= 6; i++)	memoryMap[i] &= (~sSeg_upNibble_Mask);
	for(uint8_t j = 2; j<=7; j++)		memoryMap[j] &= (~sSeg_downNibble_Mask);
	// Updating corresponding bytes of temperature on Memory Map
	if (temperatureValue >= 100.0) memoryMap[3] |= tSeg_S3_Mask;   else	memoryMap[3] &= (~tSeg_S3_Mask);
	memoryMap[3] |= (temperatureDisplay[0] & sSeg_upNibble_Mask);	memoryMap[4] |= (temperatureDisplay[0] & sSeg_downNibble_Mask);
	memoryMap[2] |= (temperatureDisplay[1] & sSeg_upNibble_Mask);	memoryMap[3] |= (temperatureDisplay[1] & sSeg_downNibble_Mask);
	memoryMap[1] |= (temperatureDisplay[2] & sSeg_upNibble_Mask);	memoryMap[2] |= (temperatureDisplay[2] & sSeg_downNibble_Mask);
	memoryMap[2] |= Point_Mask;

	// Updating corresponding bytes of humidity value on Memory Map
	memoryMap[6] |= (humidDisplay[0] & sSeg_upNibble_Mask);			memoryMap[7] |= (humidDisplay[0] & sSeg_downNibble_Mask);
	memoryMap[5] |= (humidDisplay[1] & sSeg_upNibble_Mask);			memoryMap[6] |= (humidDisplay[1] & sSeg_downNibble_Mask);
	memoryMap[4] |= (humidDisplay[2] & sSeg_upNibble_Mask);			memoryMap[5] |= (humidDisplay[2] & sSeg_downNibble_Mask);
	memoryMap[5] |= Point_Mask;

	return updateDisplay();
}

// Sub Function to convert a floating point number to 7-segment display format
uint8_t DisplayDriver_AiP16C22::floatTo7Segment(float* number, uint8_t* display) {

	// Extract the whole number and decimal parts
	uint8_t wholePart	= (uint8_t)*number;
	uint8_t decimalPart = (uint8_t)((*number - wholePart) * 10);

	// Extract individual digits
	uint8_t tens		=	(wholePart	/ 10) % 10;
	uint8_t units		=	wholePart	% 10;

	// Convert each digit to 7-segment display format
	if (tens >= (uint8_t)1 || wholePart >= 100) 
		display[0] = bcdToSegments(&tens);
	display[1] = bcdToSegments(&units);
	display[2] = bcdToSegments(&decimalPart);

	/*for (int i = 0; i < 3; i++) { Serial.print('\t'); Serial.print(display[i]); }
	Serial.println();
	Serial.print("Number: ");			Serial.print(*number);
	Serial.print("\tWhole Part: ");		Serial.print(wholePart);
	Serial.print("\tTens: ");			Serial.print(tens);
	Serial.print("\tUnits: ");			Serial.print(units);
	Serial.print("\tDecimal Part: ");	Serial.println(decimalPart);*/


}

// Sub Function to convert a BCD digit to 7-segment display format
uint8_t DisplayDriver_AiP16C22::bcdToSegments(uint8_t* bcdDigit) {
	switch (*bcdDigit) {// CGB0DEFA			  GFEDCBA
	case 0:		return	 0b10101111;	//	0b0111111;	//	Actual 7 Segments should looks like ---
	case 1:		return	 0b10100000;	//	0b0000110;	//	<-- this but I had replaced it with ---
	case 2:		return	 0b01101101;	//	0b1011011;	//	the one that matches our RAM maping ---
	case 3:		return	 0b11101001;	//	0b1001111;	//	And to decrease data manipulation complexity.
	case 4:		return	 0b11100010;	//	0b1100110;
	case 5:		return	 0b11001011;	//	0b1101101;
	case 6:		return	 0b11001111;	//	0b1111101;
	case 7:		return	 0b10100001;	//	0b0000111;
	case 8:		return	 0b11101111;	//	0b1111111;
	case 9:		return	 0b11101011;	//	0b1101111;
	default:	return	 0b00000000;	//	0b0000000;	// Invalid BCD digit
	}
}
// Funtion to Enable/Disble Division Line on LCD 
uint8_t  DisplayDriver_AiP16C22::lineEnable(bool enable)
{
	if (enable) memoryMap[7] |= LINE_ICON_Mask; else memoryMap[7] &= (~LINE_ICON_Mask);
	return updateDisplay();
}

// Function to Send updated LCD Display values to RAM (AiP16C22) 
uint8_t DisplayDriver_AiP16C22::updateDisplay()
{
	/*	
		Implementation for printing values on the display
		AiP16C22 has 5 - pin address pointer at 00H and overflow at 15H
		- {0 0 0 A4 A3 A2 A1 A0}LSB
		-
	*/
	uint8_t error = 0;
	/*if (Wire.availableForWrite())
	{*/
		// Start Writing Data to LCD Driver.
		Wire.beginTransmission(i2cAddress);
		// Start Address for segments part in RAM
		Wire.write(0x00);
		// Write whole Memory Map to RAM Memory. The address will update automatically in this scenario. 
		for(uint8_t i = 0; i < memSize; i++) Wire.write(memoryMap[i]);
		// End Writing Data to LCD Driver.
		error = Wire.endTransmission(true);
	//}
	return error;
}

// Function to Write control Registers settings through I2C 
uint8_t DisplayDriver_AiP16C22::writeToI2C(uint8_t data)
{
	/*if (Wire.availableForWrite())
	{*/
		// Start Writing Controls to LCD Driver.
		Wire.beginTransmission(0x55);
		// Write Data of the Control Register.
		Serial.print("\tNodeMCU\t"); delay(10); Serial.print(data); delay(10);	Serial.print('\t'); delay(10); Serial.print(Wire.write(data)); delay(10); Serial.print('\t'); delay(50);
		// End Writing Controls to LCD Driver.
		return Wire.endTransmission(true);
	/*}*/
}
uint8_t DisplayDriver_AiP16C22::writeToDisplayI2C(uint8_t data)
{
	/*if (Wire.availableForWrite())
	{*/
	// Start Writing Controls to LCD Driver.
	Wire.beginTransmission(i2cAddress);
	// Write Data of the Control Register.
	Serial.print("\tLCD\t"); delay(10); Serial.print(data); delay(10); Serial.print('\t');	delay(10);
	Wire.write(data);
	// End Writing Controls to LCD Driver.
	return Wire.endTransmission(true);
	/*}*/
}