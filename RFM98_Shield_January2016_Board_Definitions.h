//RFM98_Shield_January2016_Board_Definitions.h

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

  Hardware definitions for the RFM98 shield PCB with the date January 2016
  
  To Do:

*******************************************************************************************************************************
*/


#define RXD 0
#define TXD 1
#define SWITCH1 2                     //pin for switch
#define lora_DIO0 3                   
#define RCPulse 4                     //External RC Pulse sense

#define lora_TonePin 6                //pin number for tone generation, connects to LoRa device DIO2.
#define Audio_Out 6                   //pin number for Audio tone generation (AFSK) may be same as LoRa tone pin
#define lora_AFSKRTTYPin 6            //pin number for outputing AFSK RTTY, may be the same as lora_TonePin
#define MEMORY_CS 7                   //Select for FRAM\RAM
#define Buzzer 7                      //Buzzer for receiver
#define DISPLAYTX 8                   //Soft serial TX pin for Digole Serial LCD
#define LED1 9                        //pin number for LED on Tracker
#define SWITCH2 9                     //pin for switch2
#define GPSPOWER 10                   //Controls power to GPS
#define MOSI 11
#define MISO 12
#define SCK 13
#define LED2 13                       //pin number for LED fitted to most shield bases

#define lora_NSS A0
#define lora_NReset A1                //pin where LoRa device reset line is connected
#define GPSRX A2
#define GPSTX A3
#define SDA A4
#define SCL A5
#define SupplyAD A6                   //pin for supply AD

#define Bluetooth_RX  A3              //for when the Bluetooth device is not on the hardware serial port 
#define Bluetooth_TX  A2              //for when the Bluetooth device is not on the hardware serial port

#define GPSBaud 9600                  //GPS baud rate
#define ADMultiplier 10               //multiplier for supply volts calculation
