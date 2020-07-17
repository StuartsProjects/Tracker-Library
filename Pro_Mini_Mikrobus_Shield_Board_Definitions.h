//LCD_Receiver_Board_Definitions.h

/*
*******************************************************************************************************************************
  Easy Build Tracker Programs for Arduino

  Copyright of the author Stuart Robinson - 29/06/18
  

  

  These programs may be used free of charge for personal, recreational and educational purposes only.

  This program, or parts of it, may not be used for or in connection with any commercial purpose without the explicit permission
  of the author Stuart Robinson.

  The programs are supplied as is, it is up to individual to decide if the programs are suitable for the intended purpose and
  free from errors.

  This is the hardware definitions for the Pro Mini Mikrobus shield

  To Do:

*******************************************************************************************************************************
*/


#define MB1_RX A3
#define MB1_TX A2
#define MB1_INT1 2
#define SWITCH1 3
#define SD_CS 4
#define MB1_INT2 5
#define MB1_PWM  6
#define LED1 8                       //pin number for LED
#define WDI 8                        //pin for using a watchdog device
#define MB1_RESET 9
#define MB1_CS  10
#define BUZZ A1                      //a buzzer can be fitted to connector D centre pins

#define MB1_AN A1
#define SupplyAD  A7                 //measure supply voltage here

#define ADMultiplier 10              //multiplier for supply volts calculation

#define GPSTX A3
#define GPSRX A2

#define lora_TonePin MB1_PWM
#define Audio_Out MB1_PWM            //pin number for Audio tone generation (AFSK) may be same as LoRa tone pin
#define lora_NReset MB1_RESET
#define lora_NSS MB1_CS
#define lora_DIO0 MB1_INT1
#define lora_DIO1 MB1_INT2
#define lora_DIO2 MB1_PWM


#define GPSPOWER -1
#define UNUSED_PIN -1



