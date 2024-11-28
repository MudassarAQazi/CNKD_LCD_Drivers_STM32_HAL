// Test Code
/*
    Name:           Wuxi.ino
    Created:	    12/13/2023 11:20:05 PM
    Author:         Mudasssar
    Description:    This test code is written for Arduino Uno Microcontroller.
                    It can be migrated to any other microcontroller with I2C function Alteration.
*/

// Define User Types below here or use a .h file
//
#include "DisplayDriver_AiP16C22.h"
#define serial Serial

// Define Function Prototypes that use User Types below here or use a .h file
const uint8_t lcdAddress = 0x3F;

// Define Functions below here or use other .ino or cpp files
//
DisplayDriver_AiP16C22 lcd(lcdAddress);

// The setup() function runs once each time the micro-controller starts
void setup()
{
    serial.begin(9600);
    while (!Serial)
        delay(10);
    
    serial.println(lcd.displayInit(0x10)? "LCD Failed": "LCD Success");
    delay(10);
    
    /*
        Select Bias the Display
        [Enable]   [Bias]
         - 0         1/3
         - 1         1/2
    */
    serial.print("Bias Set: \t\t\t");                       serial.println(lcd.biasOfDisplay(true)          ? "Fail" : "Success");
    
    /*
        Function to Select Frame Frequency of Display
        [Enable]   [Frame Frequency]
         - 0         80 Hz
         - 1         160 Hz
    */
    serial.print("Frequency Set: \t\t\t");                  serial.println(lcd.frequency(false)             ? "Fail" : "Success");
    
    /*
        Function to Select SEG/VLCD Settings
        [DE]    [VE]    [Pin Selected]  [Internal Voltage Adjestment]
        - 0      0        VLCD Pin          off
        - 0      1        VLCD Pin          on
        - 1      0        SEG Pin           off
        - 1      1        SEG Pin           on
        -
    */
    serial.print("Internal Voltage Adjustnent Enable: ");   serial.println(lcd.segVlcdSetting(3)            ? "Fail" : "Success");
    
    /*
      Function to OFF the Display
      [Enable]   [Lcd Display]
       - 0         off
       - 1         on
   */
    serial.print("LCD Display Enable \t\t");                serial.println(lcd.display(true)                ? "Fail" : "Success");
    
    /*
        Function to Disable/Enable Display Driver IC (AiP16C22)
        [Enable]   [Internal System Oscillator]
         - 0         off
         - 1         on
    */
    serial.print("Display Driver Enable: \t\t");            serial.println(lcd.disableDisplayDriver(true)   ? "Fail" : "Success");
    
    /*  Function to set Brightness of the LCD
        [Bright]    [Display]
        - 0          Low Brightness
        - .          .
        - .          .
        - 15         Full Brightness
        -
    */
    serial.print("Brightness Setting: \t\t");               serial.println(lcd.brightness(3)                ? "Fail" : "Success");

    serial.print("Clear Display: \t\t\t\t\t\t");          serial.println(lcd.displayClear()               ? "Fail" : "Success");

    serial.println("LCD Device is Ready to Print!\n");
}


// Add the main program code into the continuous loop() function
void loop()
{
    if (serial.available())
    {
        byte read = serial.read();
        /*serial.write(read);
        serial.print('\t');*/
        switch (read)
        {
        case '0':   serial.print("Clear Display: \t\t");        serial.println(lcd.displayClear()   ? "Fail" : "Success");  break;
        case '1':   serial.print("Bluetooth ON: \t\t");         serial.println(lcd.icon(1, true)    ? "Fail" : "Success");  break;
        case '!':   serial.print("Bluetooth OFF: \t\t");        serial.println(lcd.icon(1, false)   ? "Fail" : "Success");  break;
        case '2':   serial.print("Wifi ON: \t\t");              serial.println(lcd.icon(2, true)    ? "Fail" : "Success");  break;
        case '@':   serial.print("Wifi OFF: \t\t");             serial.println(lcd.icon(2, false)   ? "Fail" : "Success");  break;
        case '3':   serial.print("Batery Empty: \t\t");         serial.println(lcd.batteryStatus(0) ? "Fail" : "Success");  break;
        case '4':   serial.print("Battery 1 Cell: \t");         serial.println(lcd.batteryStatus(1) ? "Fail" : "Success");  break;
        case '5':   serial.print("Battery 2 Cell: \t");         serial.println(lcd.batteryStatus(2) ? "Fail" : "Success");  break;
        case '6':   serial.print("Battery 3 Cell: \t");         serial.println(lcd.batteryStatus(3) ? "Fail" : "Success");  break;
        case '7':   serial.print("Battery 4 Cell: \t");         serial.println(lcd.batteryStatus(4) ? "Fail" : "Success");  break;
        case '8':   serial.print("Battery Full: \t\t");         serial.println(lcd.batteryStatus(5) ? "Fail" : "Success");  break;
        case '9':   serial.print("Battery ON: \t\t");           serial.println(lcd.icon(3, true)    ? "Fail" : "Success");  break;
        case '(':   serial.print("Battery OFF: \t\t");          serial.println(lcd.icon(3, false)   ? "Fail" : "Success");  break;
        case 'a':   serial.print("Degree Farenheit ON: \t");    serial.println(lcd.icon(4, true)    ? "Fail" : "Success");  break;
        case 'A':   serial.print("Degree Farenheit OFF: \t");   serial.println(lcd.icon(4, false)   ? "Fail" : "Success");  break;
        case 'b':   serial.print("Degree Celcius ON: \t");      serial.println(lcd.icon(5, true)    ? "Fail" : "Success");  break;
        case 'B':   serial.print("Degree Celcius OFF: \t");     serial.println(lcd.icon(5, false)   ? "Fail" : "Success");  break;
        case 'c':   serial.print("Ice ON: \t\t");               serial.println(lcd.icon(6, true)    ? "Fail" : "Success");  break;
        case 'C':   serial.print("Ice OFF: \t\t");              serial.println(lcd.icon(6, false)   ? "Fail" : "Success");  break;
        case 'd':   serial.print("Fire ON: \t\t");              serial.println(lcd.icon(7, true)    ? "Fail" : "Success");  break;
        case 'D':   serial.print("Fire OFF: \t\t");             serial.println(lcd.icon(7, false)   ? "Fail" : "Success");  break;
        case 'e':   serial.print("Humidity ON: \t\t");          serial.println(lcd.icon(8, true)    ? "Fail" : "Success");  break;
        case 'E':   serial.print("Humidity OFF: \t\t");         serial.println(lcd.icon(8, false)   ? "Fail" : "Success");  break;
        case 'f':   serial.print("Air ON: \t\t");               serial.println(lcd.icon(9, true)    ? "Fail" : "Success");  break;
        case 'F':   serial.print("Air OFF: \t\t");              serial.println(lcd.icon(9, false)   ? "Fail" : "Success");  break;
        case 'g':   serial.print("Percent ON: \t\t");           serial.println(lcd.icon(10, true)   ? "Fail" : "Success");  break;
        case 'G':   serial.print("Percent OFF: \t\t");          serial.println(lcd.icon(10, false)  ? "Fail" : "Success");  break;
        case 'h': 
        {
            for (float i = 0.0; i <= 200.0; i += 0.1) {
                serial.print("Print: " + String(i) + '\t');
                serial.println(lcd.printToDisplay(i, i) ? "Fail" : "Success");
                delay(50);
                if (serial.available() && (serial.read() == 's')) break;
            }
            break;
        }
        case '\0':; break;
        default:    serial.println("Oops! Please Enter the Valid Choice...");
        }
    }
}

///*
    //    Function to enable or disable specified icon
    //    Options:
    //    - BLE_ICON     =    1  (uint8_t)
    //    - WIFI_ICON    =    2  (uint8_t)
    //    - BAT_ICON     =    3  (uint8_t)
    //    - DEG_F_ICON   =    4  (uint8_t)
    //    - DEG_C_ICON   =    5  (uint8_t)
    //    - ICE_ICON     =    6  (uint8_t)
    //    - FIRE_ICON    =    7  (uint8_t)
    //    - HUMID_ICON   =    8  (uint8_t)
    //    - AIR_ICON     =    9  (uint8_t)
    //    - PERCENT_ICON =    10 (uint8_t)
    //    -
    //*/
