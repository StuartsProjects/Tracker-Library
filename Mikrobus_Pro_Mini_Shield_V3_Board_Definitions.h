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


#define MB1_RX 2
#define MB1_TX 3
#define MB1_INT1 5
#define SWITCH1 4
#define SD_CS 24
#define MB1_INT2 7
#define MB1_PWM  9
#define LED1 8                       //pin number for LED
#define WDI 8                        //pin for using a watchdog device
#define MB1_RESET 6
#define MB1_CS  10
#define BUZZ A6                      //a buzzer can be fitted to connector D centre pins

#define MB1_AN A6
#define SupplyAD  A7                 //measure supply voltage here

#define ADMultiplier 10              //multiplier for supply volts calculation

#define GPSTX 2
#define GPSRX 3

#define lora_TonePin MB1_PWM
#define Audio_Out MB1_PWM            //pin number for Audio tone generation (AFSK) may be same as LoRa tone pin
#define lora_NReset MB1_RESET
#define lora_NSS MB1_CS
#define lora_DIO0 MB1_INT1
#define lora_DIO1 MB1_INT2
#define lora_DIO2 MB1_PWM

#define SX1280_RFBUSY A3
#define SX1280_NSS 10
#define SX1280_NRESET 6
#define SX1280_DIO1 5
#define SX1280_DIO2 9
#define SX1280_DIO3 7
#define SX1280_RXEN A0
#define SX1280_TXEN A0


