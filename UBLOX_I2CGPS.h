//UBLOX_I2CGPS.h
/*
*******************************************************************************************************************************
  Easy Build Tracker Programs for Arduino

  Copyright of the author Stuart Robinson - 2/10/17

  

  These programs may be used free of charge for personal, recreational and educational purposes only.

  This program, or parts of it, may not be used for or in connection with any commercial purpose without the explicit permission
  of the author Stuart Robinson.

  The programs are supplied as is, it is up to individual to decide if the programs are suitable for the intended purpose and
  free from errors.

  This program reads the GPS via serial, can be hardware of softserial. Stores the config settings for UBLOX GPS in Flash to
  save on RAM memory.

  To Do:

  Check GPS_Send_Config((unsigned int)
  Check if issue with multiple Wire.begin()

*******************************************************************************************************************************
*/


byte GPS_GetByte();
void GPS_StartRead();
void GPS_On();
void GPS_Off();
boolean GPS_WaitAck(unsigned long waitms, byte length);
void GPS_Send_Config(unsigned int Progmem_ptr, byte length, byte replylength);
void GPS_Setup();
void GPS_ClearConfig();
void GPS_SetGPMode();
void GPS_StopMessages();
void GPS_SetNavigation();
void GPS_SaveConfig();
void GPS_PollNavigation();
boolean GPS_CheckNavigation();
void GPS_SetCyclicMode();
void GPS_SoftwareBackup();
void GPS_PMREQBackup();
void GPS_LowCurrent();

const int GPSI2CAddress = 0x42;

byte GPS_Reply[GPS_Reply_Size];             //byte array for storing GPS reply to UBX commands

#include <Wire.h>
#include "UBX_Commands.h"
#define USING_I2CGPS                        //so the rest of the program knows I2C GPS is in use
#define UBLOX                               //so the rest of the program knows UBLOX GPS is in use


byte GPS_GetByte()                          //get and process output from GPS
{

  byte i;

  Wire.requestFrom(GPSI2CAddress, 1);
  i = Wire.read();

  return i;

}


void GPS_StartRead()
{
  Wire.beginTransmission(GPSI2CAddress);
  Wire.write(0xFF);
}


void GPS_On(boolean powercontrol)
{
  //turns on the GPS
  //has to deal with software power control (UBLOX) and hardware power control, for tracker boards with that option
  byte i;
  Serial.println(F("GPSOn"));

  if (powercontrol)
  {
    digitalWrite(GPSPOWER, LOW);            //force GPS power on
    for (i=0 ; i<= 10; i++)                 //simulate sending a character to serial port of GPS, to wake it up  
    {
    digitalWrite(GPSTX, HIGH);              //pulse GPS datain pin to wake it up
    delayMicroseconds(104);
    digitalWrite(GPSTX, LOW);               //pulse GPS datain pin to wake it up
    delayMicroseconds(104);
    }
    delay(100);                              //give the GPS a little time to go active  
  }
}



void GPS_Off(boolean powercontrol)
{
  //power down GPS, prepare to go to sleep
  //has to deal with software power control (UBLOX) and hardware power control, for tracker boards with that option
  
  if (powercontrol)
  {

#ifdef Remove_GPS_Power
    digitalWrite(GPSPOWER, HIGH);          //force GPS power off
#endif

#ifdef Use_GPS_SoftwareBackup
    GPS_PMREQBackup();
    GPS_LowCurrent();
#endif

  }

    
}


boolean GPS_WaitAck(unsigned long waitms, byte length)
{
  //wait for Ack from GPS
  byte i, j;
  unsigned long endms;
  endms = millis() + waitms;
   
  byte ptr = 0;                             //used as pointer to store GPS reply

  Wire.beginTransmission(GPSI2CAddress);
  Wire.write(0xFF);

  do
  {
    Wire.requestFrom(GPSI2CAddress, 1);
    i = Wire.read();
  }
  while ((i != 0xb5) && (millis() < endms));

  if (i != 0xb5)
  {
    Serial.print(F("Timeout "));
    return false;
  }
  else
  {
    Serial.print(F("Ack "));
    Serial.print(i, HEX);

    length--;

    for (j = 1; j <= length; j++)
    {
      Serial.print(F(" "));

      Wire.requestFrom(GPSI2CAddress, 1);
      i = Wire.read();

      if (j < 12)
      {
        GPS_Reply[ptr++] = i;                    //save reply in buffer, but no more than 10 characters
      }

      if (i < 0x10)
      {
        Serial.print(F("0"));
      }
      Serial.print(i, HEX);
    }

  }
  Serial.println();
  return true;
}


void GPS_Send_Config(unsigned int Progmem_ptr, byte length, byte replylength, byte attempts)
{
  byte byteread1, byteread2, temp_length, i;
  unsigned int ptr;

  byte config_attempts = attempts;

  do
  {

    if (config_attempts == 0)
    {
      Serial.println(F("No Response from GPS"));
      GPS_Config_Error = true;
      break;
    }

    ptr = Progmem_ptr;
    temp_length = length / 2;                     //we are sending messages 2 bytes at a time

    for (i = 1; i <= temp_length; i++)
    {

      byteread1 = pgm_read_byte(ptr++);      //we will read and write 2 bytes at a time 
      byteread2 = pgm_read_byte(ptr++);
      Wire.beginTransmission(GPSI2CAddress);
      Wire.write(byteread1);
      Wire.write(byteread2);
      Wire.endTransmission();
      Serial.print(byteread1, HEX);
      Serial.print(" ");
      Serial.print(byteread2, HEX);
      Serial.print(" ");
    }

    Serial.println();

    if (replylength == 0)
    {
      Serial.println(F("Reply not required"));
      break;
    }

    config_attempts--;
  } while (!GPS_WaitAck(GPS_WaitAck_mS, replylength));
  
  delay(50);                                  //GPS can sometimes be a bit slow getting ready for next config
}



void GPS_Setup()
{
  Wire.begin();
  GPS_ClearConfig();
  GPS_SetGPMode();
  GPS_StopMessages();
  GPS_SetNavigation();
  GPS_SaveConfig();
  pinMode(GPSTX, OUTPUT);
}


boolean GPS_CheckNavigation()
{
  byte j;
  GPS_Reply[7] = 0xff;

  GPS_PollNavigation();

  j = GPS_Reply[7];

  Serial.print(F("Dynamic Model "));
  Serial.println(j);

  if (GPS_Reply[7] != 6)
  {
    Serial.println(F("Dynamic Model 6 not Set !"));
    return false;
  }
  else
  {
    return true;
  }
}


void GPS_ClearConfig()
{
  Serial.print(F("GPS Clear "));
  GPS_Send_Config((unsigned int) ClearConfig.access(), ClearConfig.count(), 10, GPS_attempts);
}


void GPS_SetGPMode()
{
  Serial.print(F("GPS GLONASS_Off "));
  GPS_Send_Config((unsigned int) GLONASS_Off.access(), GLONASS_Off.count(), 10, GPS_attempts);
}


void GPS_StopMessages()
{
  Serial.print(F("GPS GPGLL_Off "));
  GPS_Send_Config((unsigned int) GPGLL_Off.access(), GPGLL_Off.count(), 10, GPS_attempts);

  Serial.print(F("GPS GPGLS_Off "));
  GPS_Send_Config((unsigned int) GPGLS_Off.access(), GPGLS_Off.count(), 10, GPS_attempts);

  Serial.print(F("GPS GPGSA_Off "));
  GPS_Send_Config((unsigned int) GPGSA_Off.access(), GPGSA_Off.count(), 10, GPS_attempts);

  #ifndef GPS_ALLOW_GPGSV
  Serial.print(F("GPS GPGSV_Off "));
  GPS_Send_Config((unsigned int) GPGSV_Off.access(), GPGSV_Off.count(), 10, GPS_attempts);
  #endif
}


void GPS_SetNavigation()
{
  Serial.print(F("GPS SetNavigation "));
  GPS_Send_Config((unsigned int) SetNavigation.access(), SetNavigation.count(), 10, GPS_attempts);
}


void GPS_SaveConfig()
{
  Serial.print(F("GPS Save "));
  GPS_Send_Config((unsigned int) SaveConfig.access(), SaveConfig.count(), 10, GPS_attempts);
}


void GPS_PollNavigation()
{
  Serial.print(F("GPS PollNavigation "));
  GPS_Send_Config((unsigned int) PollNavigation.access(), PollNavigation.count(), 44, GPS_attempts);
}


void GPS_SetCyclicMode()
{
  Serial.print(F("GPS SetCyclic "));
  GPS_Send_Config((unsigned int) SetCyclicMode.access(), SetCyclicMode.count(), 10, GPS_attempts);
}


void GPS_SoftwareBackup()
{
  Serial.print(F("GPS SoftwareBackup "));
  GPS_Send_Config((unsigned int) SoftwareBackup.access(), SoftwareBackup.count(), 0, GPS_attempts);
}

void GPS_PMREQBackup()
{
  Serial.print(F("GPS PMREQBackup "));
  GPS_Send_Config((unsigned int) PMREQBackup.access(), PMREQBackup.count(), 0, GPS_attempts);
}


void GPS_LowCurrent()
{
//null routine
}



