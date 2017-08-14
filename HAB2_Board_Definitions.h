//HAB2_Board_Definitions.h

/*
*******************************************************************************************************************************
  Easy Build LoRaTracker Programs for Arduino

  Copyright of the author Stuart Robinson - 14/08/17

  http://www.LoRaTracker.uk

  These programs may be used free of charge for personal, recreational and educational purposes only.

  This program, or parts of it, may not be used for or in connection with any commercial purpose without the explicit permission
  of the author Stuart Robinson.

  The programs are supplied as is, it is up to individual to decide if the programs are suitable for the intended purpose and
  free from errors.

  Hardware definitions for the HAB2 tracker board.

  To Do:

*******************************************************************************************************************************
*/


#define lora_DIO0 2                  //pin connected to DIO0 on LoRa device
#define lora_DIO5 3                  //pin connected to DIO5 on LoRa device
#define lora_DIO3 4                  //pin connected to DIO3 on LoRa device
#define lora_DIO1 5                  //pin connected to DIO1 on LoRa device
#define lora_DIO2 6                  //pin connected to DIO2 on LoRa device
#define lora_TonePin 6               //pin number for radio tone generation, connects to LoRa device pin DIO2
#define lora_DIO4 7                  //pin connected to DIO4 on LoRa device
#define LED1 8                       //pin number for LED on Tracker
#define WDI 8                        //pin for using a watchdog device
#define lora_NReset 9                //pin where LoRa device reset line is connected
#define lora_NSS 10                  //pin number where the NSS line for the LoRa device is connected
#define LED2 13                      //pin number for standard LED on pin 13 of Pro Mini

#define GPSPOWER -1                   //pin controls power to GPS
#define GPSBACKUP -1                  //use for GPS backup power
#define CON2_1 -1                     //connected to CON2 pin 1 on external header
#define SupplyAD A0                   //pin for supply AD
#define TimePulse A1                  //For reading the GPS timepulse signal
#define GPSTX A2                      //pin number for TX output - RX into GPS
#define GPSRX A3                      //pin number for RX input - TX from GPS
#define RCPulse -1                    //unused pin
#define DisplayTX -1                  //unused pin
#define MEMORY_CS -1                  //unused pin          

#define GPSBaud 9600                  //GPS baud rate
#define ADMultiplier 10               //multiplier for supply volts calculation

