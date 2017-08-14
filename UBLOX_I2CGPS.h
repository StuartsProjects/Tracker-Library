//UBLOX_I2CGPS.h
/*
*******************************************************************************************************************************
  Easy Build LoRaTracker Programs for Arduino

  Copyright of the author Stuart Robinson - 14/08/17

  http://www.LoRaTracker.uk

  These programs may be used free of charge for personal, recreational and educational purposes only.

  This program, or parts of it, may not be used for or in connection with any commercial purpose without the explicit permission
  of the author Stuart Robinson.

  The programs are supplied as is, it is up to individual to decide if the programs are suitable for the intended purpose and
  free from errors.

  This program reads the GPS via serial, can be hardware of softserial. Stores the config settings for UBLOX GPS in Flash to
  save on RAM memory.

  To Do:

  Check GPS_Send_Config((unsigned int)

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

unsigned long GPSonTime;
unsigned long GPSoffTime;
unsigned long GPSFixTime;

const int GPSI2CAddress = 0x42;

byte config_attempts;

boolean GPS_Config_Error;

byte GPS_Reply[GPS_Reply_Size];             //byte array for storing GPS reply to UBX commands


#include <Wire.h>
#include "UBX_Commands.h"
#define USE_I2CGPS                          //so the rest of the program knows I2C GPS is in use
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
  Serial.println(F("GPSOn"));
  GPSonTime = millis();

  if (powercontrol)
  {
    digitalWrite(GPSPOWER, LOW);            //force GPS power on
    digitalWrite(GPSTX, LOW);               //pulse GPS datain pin to wake it up
    delay(1);
    digitalWrite(GPSTX, HIGH);
  }
}



void GPS_Off(boolean powercontrol)
{
  //power down GPS, prepare to go to sleep
  //has to deal with software power control (UBLOX) and hardware power control, for tracker boards with that option

  if (powercontrol)
  {
    digitalWrite(GPSPOWER, HIGH);          //force GPS power off

#ifdef Use_GPS_SoftwareBackup
    GPS_SoftwareBackup();
#endif

    GPSoffTime = millis();
    Serial.print(F("GPSOff at "));
    GPSFixTime = (GPSoffTime - GPSonTime);
    Serial.print(GPSFixTime);
    Serial.println(F("mS"));
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
  byte byteread1, byteread2, i;
  unsigned int ptr;

  config_attempts = attempts;

  do
  {

    if (config_attempts == 0)
    {
      Serial.println(F("No Response from GPS"));
      GPS_Config_Error = true;
      break;
    }

    ptr = Progmem_ptr;
    length = length / 2;                     //we are sending messages 2 bytes at a time

    for (i = 1; i <= length; i++)
    {

      byteread1 = pgm_read_byte(ptr++);      //must be at least 2 reads for UBLOX to respond correctly
      byteread2 = pgm_read_byte(ptr++);
      Wire.beginTransmission(GPSI2CAddress);
      Wire.write(byteread1);
      Wire.write(byteread2);
      Wire.endTransmission();
    }

    if (replylength == 0)
    {
      Serial.println(F("Reply not required"));
      break;
    }

    config_attempts--;
  } while (!GPS_WaitAck(GPS_WaitAck_mS, replylength));

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

  Serial.print(F("GPS GPGSV_Off "));
  GPS_Send_Config((unsigned int) GPGSV_Off.access(), GPGSV_Off.count(), 10, GPS_attempts);
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
  Serial.println();
}


void GPS_SoftwareBackup()
{

  Serial.print(F("GPS SoftwareBackup "));
  GPS_Send_Config((unsigned int) SoftwareBackup.access(), SoftwareBackup.count(), 0, GPS_attempts);
  Serial.println();

}





