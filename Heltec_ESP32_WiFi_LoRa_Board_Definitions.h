//Heltec_ESP32_WiFi_LoRa_Board_Definitions.h

/*
*******************************************************************************************************************************

  Copyright of the author Stuart Robinson - 10/1/18

  http://www.LoRaTracker.uk

  These programs may be used free of charge for personal, recreational and educational purposes only.

  This program, or parts of it, may not be used for or in connection with any commercial purpose without the explicit permission
  of the author Stuart Robinson.

  The programs are supplied as is, it is up to individual to decide if the programs are suitable for the intended purpose and
  free from errors.

  This is the hardware definitions for the Heltec ESP32 WiFi LoRa board

  To Do:

*******************************************************************************************************************************
*/


#define lora_NSS 18                  //Arduino pin number for device select on LoRa device
#define lora_NReset 14               //Arduino pin number for reset pin on LoRa device, can be left not connected
#define lora_TonePin -1              //Not used 
#define lora_DIO0 26                 //Arduino pin number connceted to DIO0 pin on LoRa device,  can be left not connected
#define LED1 25                      //Arduino pin number for LED, when high LED should be on.  
#define BUZZ 33                      //Arduino pin number for buzzer, when high buzzer should sound