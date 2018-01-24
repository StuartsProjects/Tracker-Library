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


#define MB1_RX 0
#define Bluetooth_RX 0
#define MB1_TX 1
#define Bluetooth_TX 1
#define MB1_INT1 2
#define SWITCH1 3
#define MB2_CS  4
#define SD_CS 4
#define MB1_INT2 5
#define MB1_PWM  6
#define Audio_Out 6                  //pin number for Audio tone generation (AFSK)
#define GPSPOWER 7
#define LED1 8                       //pin number for LED
#define WDI 8                        //pin for using a watchdog device
#define MB1_RESET 9
#define MB1_CS  10

#define MB2_INT1 A0
#define MB1_AN A1
#define MB2_TX  A2
#define MB2_RX  A3
#define BUZZ A2                      //some test programs use this pin for a buzzer
#define SupplyAD  A6                 //measure supply voltage here
#define MB2_AN A7

#define ADMultiplier 10              //multiplier for supply volts calculation

#ifdef GPS_in_MB2
#define GPSTX MB2_TX
#define GPSRX MB2_RX
#endif

#ifdef GPS_in_MB1
#define GPSTX MB1_TX
#define GPSRX MB1_RX
#endif


#ifdef LoRa_Device_in_MB1            //if the LoRa device is in MB1
#define lora_TonePin MB1_PWM
//#define Audio_Out MB1_PWM            //pin number for Audio tone generation (AFSK) may be same as LoRa tone pin
#define lora_NReset MB1_RESET
#define lora_NSS MB1_CS
#define lora_DIO0 MB1_INT1
#endif

#ifdef LoRa_Device_in_MB2            //if the LoRa device is in MB1
#define lora_TonePin MB2_PWM
#define lora_NReset -1               //pin not used
#define lora_NSS MB2_CS
#define lora_DIO0 MB1_INT1
#endif

