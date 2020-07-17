//Sensor1_Board_Definitions.h

/*
*******************************************************************************************************************************
  Easy Build Tracker Programs for Arduino

  Copyright of the author Stuart Robinson - 2/1/18

  

  These programs may be used free of charge for personal, recreational and educational purposes only.

  This program, or parts of it, may not be used for or in connection with any commercial purpose without the explicit permission
  of the author Stuart Robinson.

  The programs are supplied as is, it is up to individual to decide if the programs are suitable for the intended purpose and
  free from errors.

  This is the hardware definitions for the Microbit single Mikrobus socket board.

  To Do:

*******************************************************************************************************************************
*/
//SDA on P20
//SCL on P19
//MOSI on P15
//MISO on P14
//SCK on P13

#define Audio_Out 0                  //pin number for Audio tone generation (AFSK)
#define LED1 0                       //pin number for LED
#define MB1_PWM 0
#define MB1_DIG1 1
#define MB1_INT1 2
#define DISPTX 3
#define BUZZER 4
#define SWITCH1 5                    //Button A  
#define BUTTONA 5                    //Button A        
#define Bluetooth_RX 6             
#define Bluetooth_TX 7   
#define MB1_RX  8
#define SD_CS 9
#define SupplyAD  10                 //measure supply voltage here
#define MB1_AN 10                                 
#define BUTTONB 11                    //Button B
#define DATA 11                       //Sensors
#define MB1_TX 12
#define MB1_CS  16

#define GPSPOWER - 1                 //not used
#define ADMultiplier 10              //multiplier for supply volts calculation
#define WDI -1                       // not used

#define GPSTX MB1_TX
#define GPSRX MB1_RX

#define lora_TonePin MB1_PWM
#define lora_NReset - 1
#define lora_NSS MB1_CS
#define lora_DIO0 MB1_INT1


