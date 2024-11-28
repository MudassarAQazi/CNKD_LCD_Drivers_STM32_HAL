// DisplayDriver_AiP16C22.h

/**
*   This display driver covers All the functionality of the provided LCD 
*   connected with AiP16C22 RAM for the LCD Segment driver
*/
#include<Arduino.h>


#ifndef DisplayDriver_AiP16C22_H
#define DisplayDriver_AiP16C22_H

const uint8_t memSize = 8;

class DisplayDriver_AiP16C22 {
public:
    
    // Object of the LCD Display
    DisplayDriver_AiP16C22(uint8_t address);

    /*
        Function to initialize the display
        - LCD I2C Address
        -
    */
    uint8_t displayInit(uint8_t address);

    /*
        Select Bias the Display
        [Enable]   [Bias]
         - 0         1/3
         - 1         1/2
    */
    uint8_t biasOfDisplay(bool enable);

    /*
        Function to Select Frame Frequency of Display
        [Enable]   [Frame Frequency]
         - 0         80 Hz
         - 1         160 Hz
    */
    uint8_t frequency(bool freq);

    /*
        Function to Select SEG/VLCD Settings
        [DE]    [VE]    [Pin Selected]  [Internal Voltage Adjestment]
        - 0      0        VLCD Pin          off
        - 0      1        VLCD Pin          on
        - 1      0        SEG Pin           off
        - 1      1        SEG Pin           on
        -
    */
    uint8_t segVlcdSetting(uint8_t settings);

    /*
        Function to OFF the Display
        [Enable]   [Lcd Display]
         - 0         off
         - 1         on
    */
    uint8_t display(bool enable);

    /*
        Function to Disable/Enable Display Driver IC (AiP16C22)
        [Enable]   [Internal System Oscillator]
         - 0         off
         - 1         on 
    */
    uint8_t disableDisplayDriver(bool enable);

    /*  Function to set Brightness of the LCD
        [Bright]    [Display]
        - 0          Low Brightness
        - .          .
        - .          .
        - 15         Full Brightness
        -
    */
    uint8_t brightness(uint8_t bright);

    /*
        Function to Blink Display
        [Mode]     [Blinking Frequency]
        - 0          Blink off
        - 1          2 Hz
        - 2          1 Hz
        - 3          0.5 Hz
        -
    */
    uint8_t blinkDisplay(uint8_t blinkFreq);

    /*
        Function to clear the whole screen

    */
    uint8_t displayClear();

    /*
        Function to enable or disable specified icon
        Options:
        - BLE_ICON     =    1  (uint8_t)
        - WIFI_ICON    =    2  (uint8_t)
        - BAT_ICON     =    3  (uint8_t)
        - DEG_F_ICON   =    4  (uint8_t)
        - DEG_C_ICON   =    5  (uint8_t)
        - ICE_ICON     =    6  (uint8_t)
        - FIRE_ICON    =    7  (uint8_t)
        - HUMID_ICON   =    8  (uint8_t)
        - AIR_ICON     =    9  (uint8_t)
        - PERCENT_ICON =    10 (uint8_t)
        -
    */
    uint8_t icon(uint8_t iconType, bool enable);

    /*  Function to set battery cells status
        [Cells]     [Status]
        - 0          Empty
        - .          .
        - .          .
        - 5          Full
        -
    */
    uint8_t batteryStatus(uint8_t batteryCells);

    /*
        Function to print values on the display
        - (Humidity, Temperature)
        - Address of Temperature Value,
        - Address of Humidity Value
        -
    */
    uint8_t printToDisplay(float tempratureValue, float humidValue);


private:

    /*
        Formating of AiP16C22 RAM Memory
        -
        - memoryMap[0]	{B3	   B2	B1	B0	B4	B5	S2	S1}LSB
        - memoryMap[1]	{3C	   3G	3B	S6	S8	S7	S5	S4}
        - memoryMap[2]	{2C	   2G	2B	P1	3D	3E	3F	3A}
        - memoryMap[3]	{1C	   1G	1B	S3	2D	2E	2F	2A}
        - memoryMap[4]	{6C	   6G	6B	S12	1D	1E	1F	1A}
        - memoryMap[5]	{5C	   5G	5B	P2	6D	6E	6F	6A}
        - memoryMap[6]	{4C	   4G	4B	--	5D	5E	5F	5A}
        - memoryMap[7]	{S11   S10	S9	--	4D	4E	4F	4A}
        -
    */
    uint8_t memoryMap[memSize] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

    // LCD I2C Address storage for use after initialization
    uint8_t i2cAddress      = 0x00;

    // This veriable will store Last status of Battery upon disabling event for re-enabling
    uint8_t lastBatStatus   = 0x00;

    // Mode settings storing variable
    uint8_t modeSettings    = 0x80;

    // Icons & 7 Segments Masks
    const uint8_t   BLE_ICON_Mask       =   0x01,     //Use it on memoryMap[0]
                    WIFI_ICON_Mask      =   0x02,     //Use it on memoryMap[0]
                    BAT_ICON_Mask       =   0xFC,     //Use it on memoryMap[0]
                    DEG_F_ICON_Mask     =   0x03,     //Use it on memoryMap[1]
                    DEG_C_ICON_Mask     =   0x11,     //Use it on memoryMap[1]
                    ICE_ICON_Mask       =   0x04,     //Use it on memoryMap[1]
                    FIRE_ICON_Mask      =   0x08,     //Use it on memoryMap[1]
                    LINE_ICON_Mask      =   0x20,     //Use it on memoryMap[7]
                    HUMID_ICON_Mask     =   0x40,     //Use it on memoryMap[7]
                    AIR_ICON_Mask       =   0x80,     //Use it on memoryMap[7]
                    PERCENT_ICON_Mask   =   0x10,     //Use it on memoryMap[4]
                    
                    BAT0_Mask       =   0x10,     //Use it on memoryMap[0]
                    BAT1_Mask       =   0x14,     //Use it on memoryMap[0]
                    BAT2_Mask       =   0x1C,     //Use it on memoryMap[0]
                    BAT3_Mask       =   0x9C,     //Use it on memoryMap[0]
                    BAT4_Mask       =   0xDC,     //Use it on memoryMap[0]
                    BAT5_Mask       =   0xFC,     //Use it on memoryMap[0] // It should be used during re-enabling BAT icon
                                
                    tSeg_S3_Mask            =   0x10,     //Use it on memoryMap[4]
                    sSeg_upNibble_Mask      =   0xE0,     //Use it on memoryMap[1,2,3,4,5,6]
                    sSeg_downNibble_Mask    =   0x0F,     //Use it on memoryMap[2,3,4,5,6,7]
                    Point_Mask              =   0x10;
    /*
        Control Functions
        - {1    0   0   F   S   E   0   M0}LSB      80H
        - {1    1   0   0   0   0   BK1 BK0}LSB     C0H
        - {0    1   DE  VE  DA3 DA2 DA1 DA0}LSB     70H
    */
    // Control Function Masks
    const uint8_t   BIAS_DISP_Mask      =   0x01,   // Use it for 80H
                    OFF_DISP_Mask       =   0x04,   // Use it for 80H
                    OSC_DISP_Mask       =   0x08,   // Use it for 80H
                    FREQ_DISP_Mask      =   0x10,   // Use it for 80H
                    BLNK_DISP_Mask      =   0x03,   // Use it for C0H
                    BRIGT_DISP_Mask     =   0x0F,   // Use it for 70H
                    BRIGT_EN_Mask       =   0x30;   // Use it for 70H

    const uint8_t   modeRegAddress      =   0x80,
                    blinkRegAddress     =   0xC0,
                    intVoltAdjAddress   =   0x70,
                    brightCtrlEnAddress =   0x40;
                    

    // Function to convert a floating point number to 7-segment display format
    uint8_t floatTo7Segment(float* number, uint8_t* display);

    // Function to convert a BCD number to 7-segment display format
    uint8_t bcdToSegments(uint8_t* bcdDigit);

    // Function to Enable Division Line on LCD Display
    uint8_t lineEnable(bool enable);

    /*
        Helper Function to update display
        - Use this funtion into the main loop to maintain segments consistancy
        -
    */
    uint8_t updateDisplay();

    /* 
        Private helper function for I2C communication with AiP16C22
        - I2C Address
        - Data Memory Array
        -
    */
    uint8_t writeToDisplayI2C(uint8_t data);
    uint8_t writeToI2C(uint8_t data);
};

#endif // DISPLAY_DRIVER_H