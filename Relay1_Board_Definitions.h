//PIHTracker3_Board_Definitions.h

/*
*******************************************************************************************************************************
  Easy Build LoRaTracker Programs for Arduino

  Copyright of the author Stuart Robinson - 2/10/17

  http://www.LoRaTracker.uk

  These programs may be used free of charge for personal, recreational and educational purposes only.

  This program, or parts of it, may not be used for or in connection with any commercial purpose without the explicit permission
  of the author Stuart Robinson.

  The programs are supplied as is, it is up to individual to decide if the programs are suitable for the intended purpose and
  free from errors.

  Hardware definitions for the PIHTracker3 board.

  To Do:

*******************************************************************************************************************************
*/

#define lora_DIO0 2                   //pin connected to DIO0 on LoRa device
#define SWITCH1 3                     //pin for switch
#define lora_DIO5 4                   //pin connected to DIO5 on LoRa device
#define RCPulse 5                     //pin used to read RC pulse
#define lora_DIO2 6                   //pin connected to DIO2 on LoRa device
#define lora_TonePin 6                //pin connected to DIO2 on LoRa device
#define Audio_Out 6                   //pin number for Audio tone generation (AFSK) may be same as LoRa tone pin
#define lora_DIO1 7                   //pin connected to DIO1 on LoRa device
#define lora_DIO4 8                   //pin connected to DIO4 on LoRa device
#define lora_DIO3 9                   //pin connected to DIO3 on LoRa device
#define lora_NSS 10	                  //pin number where the NSS line for the LoRa device is connected
#define LED2 13                       //pin number for standard LED on pin 13 of Pro Mini
  
#define lora_NReset A0                //pin where LoRa device reset line is connected
#define SupplyAD A1                   //pin for supply AD
#define WDI A2                        //pin for using a watchdog device
#define LED1 A3                       //pin number for LED on Tracker
#define GPSTX A4                      //pin number for TX output - RX into GPS
#define GPSRX A5                      //pin number for RX input - TX from GPS
#define Bluetooth_TX  A4              //shared with GPS 
#define Bluetooth_RX  A5              //shared with GPS 
#define DisplayTX A5                  //soft serial TX pin for Digole Serial LCD
#define Audio_Out -1                  //Unused pin
#define GPSPOWER -1                   //Unused pin
#define GPSBaud 9600                  //GPS baud rate
#define SupplyAD -1                   //unused pin
#define TimePulse -1                  //unused pin

#define ADMultiplier 10               //multiplier for supply volts calculation


