//HAB2_Definitions.h

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
*/


#define RXD 0
#define TXD 1
#define MB1_INT 2
#define SWITCH1 3
#define MB2_CS  4
#define SD_CS 4
#define MB2_INT 5
#define MB1_PWM  6
#define GPSPOWER 7
#define LED1 8                       //pin number for LED
#define WDI 8                        //pin for using a watchdog device
#define MB1_RESET 9
#define MB1_CS  10
#define MOSI 11
#define MISO 12
#define SCK 13

#define SupplyAD  A0
#define MB1_AN A1
#define MB2_TX  A2
#define MB2_RX  A3
#define SDA
#define SCL

#define GPSBaud 9600                  //GPS baud rate
#define ADMultiplier 10               //multiplier for supply volts calculation


#ifdef GPS_in_MB2
#define GPSTX A2
#define GPSRX A3
#include <NeoSWSerial.h>              //more relaible at GPS init than software serial  
NeoSWSerial GPSserial(GPSRX, GPSTX);
#endif


#ifdef LoRa_Device_in_MB1       //if the LoRa device is in MB1
#define lora_TonePin MB1_PWM
#define lora_NReset MB1_RESET
#define lora_NSS MB1_CS
#define lora_DIO0 MB1_INT
#endif

