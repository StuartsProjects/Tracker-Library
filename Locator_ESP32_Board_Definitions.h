//ESP32_LCD_Receiver_Board_Definitions.h

/*
*******************************************************************************************************************************
  Easy Build Tracker Programs for Arduino

  Copyright of the author Stuart Robinson - 18/08/18

  

  These programs may be used free of charge for personal, recreational and educational purposes only.

  This program, or parts of it, may not be used for or in connection with any commercial purpose without the explicit permission
  of the author Stuart Robinson.

  The programs are supplied as is, it is up to individual to decide if the programs are suitable for the intended purpose and
  free from errors.

  This is the hardware definitions for the ESP32_Mikrobus_Shield

  To Do:

*******************************************************************************************************************************
*/

#define UsingESP32                   //some drivers need to be different for the ESP32

#define SWITCH1 0
#define SD_CS 13
#define Audio_Out 15                 //pin number for Audio tone generation (AFSK) on MB1_PWM
#define LED1 2                       //pin number for LED
#define SupplyAD  36                 //measure supply voltage here
#define VCC2_Power 4
#define ADMultiplier 10              //multiplier for supply volts calculation

#define lora_NSS 5
#define lora_NReset 27
#define SCK 18
#define MISO 19
#define MOSI 23
#define SS -1
#define lora_DIO0 35
#define lora_DIO1 34
#define lora_DIO2 15
#define lora_TonePin 15
#define SCL 22
#define SDA 21
#define BAT 36