//Sensor1_Board_Definitions.h

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

  This is the hardware definitions for the Sensor1 board.

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

#define SupplyAD  A0                 //measure supply voltage here
#define MB1_AN A1
#define DISPLAYTX A1                 //for driving serial displays
#define MB2_TX  A2
#define MB2_RX  A3
#define BUZZ A2                      //some test programs use this pin for a buzzer
#define SDA A4
#define SCL A5

#define ADMultiplier 10              //multiplier for supply volts calculation

#define Bluetooth_RX  A3
#define Bluetooth_TX  A2

#ifdef GPS_in_MB2

#define GPSTX MB2_TX
#define GPSRX MB2_RX

#endif


#ifdef LoRa_Device_in_MB1            //if the LoRa device is in MB1
#define lora_TonePin MB1_PWM
#define Audio_Out MB1_PWM            //pin number for Audio tone generation (AFSK) may be same as LoRa tone pin
#define lora_NReset MB1_RESET
#define lora_NSS MB1_CS
#define lora_DIO0 MB1_INT
#endif

