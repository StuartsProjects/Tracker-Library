//PIHTracker3_Board_Definitions.h

/*
*******************************************************************************************************************************
  Easy Build Tracker Programs for Arduino

  Copyright of the author Stuart Robinson - 2/10/17

  

  These programs may be used free of charge for personal, recreational and educational purposes only.

  This program, or parts of it, may not be used for or in connection with any commercial purpose without the explicit permission
  of the author Stuart Robinson.

  The programs are supplied as is, it is up to individual to decide if the programs are suitable for the intended purpose and
  free from errors.

  Hardware definitions for the PIHTracker3 board.

  To Do:

*******************************************************************************************************************************
*/


#define SWITCH1 2                    //pin for switch input
#define lora_DIO0 3                  //pin connected to DIO0 on LoRa device
#define Audio_Out 5                  //pin number for Audio tone generation (AFSK) may be same as LoRa tone pin
#define lora_TonePin 5               //pin number for radio tone generation, connects to LoRa device pin DIO2
#define MEMORY_CS 6                  //pin for FRAM CS
#define GPSPOWER 7                   //pin controls power to GPS 
#define LED1 8                       //pin number for LED on Tracker
#define lora_NReset 9                //pin where LoRa device reset line is connected
#define lora_NSS 10                  //pin number where the NSS line for the LoRa device is connected
#define LED2 13                      //pin number for standard LED on pin 13 of Pro Mini


#define GPS3DFIX A0
#define GPSRX A2                     //pin number for TX output - RX into GPS
#define GPSTX A3                     //pin number for RX input - TX from GPS
#define SupplyAD A7                  //pin for supply AD

#define ADMultiplier 10              //multiplier for supply volts calculation



/*
#define lora_DIO0 2                  //pin connected to DIO0 on LoRa device
#define Audio_Out 3                  //pin number for external tone generation
#define lora_TonePin 4               //pin number for radio tone generation, connects to LoRa device pin DIO2
#define WDI 5                        //pin for using a watchdog device
#define SWITCH1 6                    //pin for switch input
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

#define ADMultiplier 10               //multiplier for supply volts calculation

#define DISP_CS -1                    //pin not used 
#define DISP_RESET -1                 //pin not used 
#define DISP_DC -1                    //pin not used 
#define Bluetooth_TX -1               //pin not used 

#define Bluetooth_RX  A3
#define Bluetooth_TX  A2
*/
