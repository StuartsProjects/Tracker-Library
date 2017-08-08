//Program_Definitions.h

/*
*******************************************************************************************************************************
Easy Build LoRaTracker Programs for Arduino

Copyright of the author Stuart Robinson - 04/06/17

http://www.LoRaTracker.uk

These programs may be used free of charge for personal, recreational and educational purposes only.

This program, or parts of it, may not be used for or in connection with any commercial purpose without the explicit permission
of the author Stuart Robinson.

The programs are supplied as is, it is up to individual to decide if the programs are suitable for the intended purpose and
free from errors.

For boards; LoRaTrackerHAB1, LoRaTracker_Locator1, PIHTracker3, PIHTracker2, LoRaTracker_Relay1, LoRaTracker_Receiver1 (1284P),
MikrobusShieldV3, MikrobusShield2560,
  
To Do:
  
*******************************************************************************************************************************

/*
**************************************************************************************************
  LoRa Static definitions
**************************************************************************************************
*/


#define lora_DIO0 2                  //pin connected to DIO0 on LoRa device
#define Audio_Out 3                  //pin number for external tone generation
#define lora_TonePin 4               //pin number for radio tone generation, connects to LoRa device pin DIO2
#define WDI 5                        //pin for using a watchdog device
#define Switch1 6                    //pin for switch input
#define lora_NSS 8                   //pin number where the NSS line for the LoRa device is connected
#define lora_NReset 9                //pin where LoRa device reset line is connected
#define LED1 10                      //pin number for LED on Tracker
#define LED2 13                      //pin number for standard LED on pin 13 of Pro Mini

#define GPSPOWER 7                    //pin controls power to GPS
#define GPSBACKUP A1                  //use for GPS backup power
#define CON2_1 A1                     //connected to CON2 pin 1 on external header
#define GPSTX A2                      //pin number for TX output - RX into GPS
#define GPSRX A3                      //pin number for RX input - TX from GPS
#define RCPulse A4                    //pin used to read RC pulse
#define DisplayTX A5                  //soft serial TX pin for Digole Serial LCD
#define SupplyAD A0                   //pin for supply AD
#define TimePulse 3                   //For reading the GPS timepulse signal

#define GPSBaud 9600                  //GPS baud rate
#define ADMultiplier 10               //multiplier for supply volts calculation

#include <NeoSWSerial.h>              //more relaible at GPS init than software serial  
NeoSWSerial GPSserial(GPSRX, GPSTX);
