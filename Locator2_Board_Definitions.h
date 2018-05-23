//Locator2_Board_Definitions.h

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

  Hardware definitions for the Locator2 board.

  To Do:

*******************************************************************************************************************************
*/


#define lora_DIO0 2                   //pin connected to DIO0 on LoRa device
#define lora_DIO5 3                   //pin connected to DIO5 on LoRa device
#define lora_DIO3 4                   //pin connected to DIO3 on LoRa device
#define lora_DIO1 5                   //pin connected to DIO1 on LoRa device
#define lora_DIO2 6                   //pin connected to DIO2 on LoRa device
#define lora_TonePin 6                //pin number for radio tone generation, connects to LoRa device pin DIO2
#define GPSPOWER 7                    //pin controls power to GPS
#define WDI 8                         //pin for using a watchdog device
#define LED1 8                        //pin number for LED on Tracker
#define lora_NReset 9                 //pin where LoRa device reset line is connected
#define lora_NSS 10                   //pin number where the NSS line for the LoRa device is connected
#define SupplyAD A0                   //pin for supply AD
#define RCPulse A1                    //pin used to read RC pulse
#define SWITCH1 A1                    //some programs use this pin for a switch 
#define Audio_Out A1                  //pin number for external tone generation
#define GPSTX A2                      //pin number for TX output - RX into GPS
#define GPSRX A3                      //pin number for RX input - TX from GPS
#define BUZZ A2                       //some test programs use this pin for a buzzer
#define DisplayTX A5                  //soft serial TX pin for Digole Serial LCD

#define ADMultiplier 10               //multiplier for supply volts calculation

#define Bluetooth_RX  A3
#define Bluetooth_TX  A2

#define DISP_CS -1                    //pin not used 
#define DISP_RESET -1                 //pin not used 
#define DISP_DC -1                    //pin not used
#define SD_CS -1                      //pin not used  

