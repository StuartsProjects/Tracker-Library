//UBLOX_SerialGPS.h
/*
*******************************************************************************************************************************
  Easy Build LoRaTracker Programs for Arduino

  Copyright of the author Stuart Robinson - 26/1/18

  http://www.LoRaTracker.uk

  These programs may be used free of charge for personal, recreational and educational purposes only.

  This program, or parts of it, may not be used for or in connection with any commercial purpose without the explicit permission
  of the author Stuart Robinson.

  The programs are supplied as is, it is up to individual to decide if the programs are suitable for the intended purpose and
  free from errors.

  This program reads a UBLOX GPS via serial. Uses Flash arrays stored in program memory.

  To Do:   

  Changes: 
  141017 Revised the method of saving arrays to configure GPS in memory avoiding the need for the FLASH-5 Library
  260118 Changes to ensure repeat send of config messages are correct
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


byte GPS_Reply[GPS_Reply_Size];             //byte array for storing GPS reply to UBX commands
  
#include "UBX_Commands2.h"                  //arrays that have the command sequences
#define USING_SERIALGPS                     //so the rest of the program knows serial GPS is in use
#define UBLOX                               //so the rest of the program knows a UBLOX GPS is in use


byte GPS_GetByte()                          //get and process output from GPS
{
  if (GPSserial.available() ==  0)
  {
    return 0xFF;
  }
  else
  {
    return GPSserial.read();
  }
}


void GPS_StartRead()
{
  //left empty for future use
}


void GPS_On(boolean powercontrol)
{
  //turns on the GPS
  //has to deal with software power control (UBLOX) and hardware power control, for tracker boards with that option
  Serial.println(F("GPSOn"));
  GPSserial.begin(GPSBaud);

  if (powercontrol)
  {
    digitalWrite(GPSPOWER, LOW);            //force GPS power on, if its not in use has no effect
    GPSserial.write('0');                   //wakeup gps, in case software power down is in use
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

  GPSserial.end();
  
}




boolean GPS_WaitAck(unsigned long waitms, byte length)
{
  //wait for Ack from GPS
  byte i, j;
  unsigned long endms;
  endms = millis() + waitms;
  byte ptr = 0;                             //used as pointer to store GPS reply
  
  do
  {
    while (GPSserial.available() > 0)
      i = GPSserial.read();
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

      while (GPSserial.available() == 0);
      i = GPSserial.read();

      if (j < 12)
      {
        GPS_Reply[ptr++] = i;                  //save reply in buffer, but no more than 10 characters
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


void GPS_Send_Config(const uint8_t *Progmem_ptr, byte arraysize, byte replylength, byte attempts)
{
  byte byteread,index;

  byte config_attempts = attempts;

  Serial.print(F("("));
  Serial.print(arraysize); 
  Serial.print(F(") "));
  
  do
  {

    if (config_attempts == 0)
    {
      Serial.println(F("No Response from GPS"));
      GPS_Config_Error = true;
      break;
    }

   for (index = 0; index < arraysize; index++)
    {
      byteread = pgm_read_byte_near(Progmem_ptr++);
      GPSserial.write(byteread);
      Serial.print(byteread, HEX);
      Serial.print(" ");
    }

    Progmem_ptr = Progmem_ptr - arraysize;     //put Progmem_ptr back to start value in case we need to re-send the config
 
    Serial.println();
    
    if (replylength == 0)
    {
      Serial.println(F("Reply not required"));
      break;
    }

    config_attempts--;
  } while (!GPS_WaitAck(GPS_WaitAck_mS, replylength));

  delay(50);                                         //GPS can sometimes be a bit slow getting ready for next config
}


void GPS_Send_Config_old(unsigned int Progmem_ptr, byte length, byte replylength, byte attempts)
{
  byte byteread, i;
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

    for (i = 1; i <= length; i++)
    {
      byteread = pgm_read_byte(ptr++);

      GPSserial.write(byteread);

    }

    if (replylength == 0)
    {
      Serial.println(F("Reply not required"));
      break;
    }

    config_attempts--;
  } while (!GPS_WaitAck(GPS_WaitAck_mS, replylength));

  delay(50);                                         //GPS can sometimes be a bit slow getting ready for next config
}



void GPS_Setup()
{
  GPS_ClearConfig();
  GPS_SetGPMode();
  GPS_StopMessages();
  GPS_SetNavigation();
  GPS_SaveConfig();
}


boolean GPS_CheckNavigation()
{
  byte j;
  GPS_Reply[7] = 0xff;

  GPS_PollNavigation();

  j = GPS_Reply[7];

  Serial.print(F("Dynamic Model is "));
  Serial.println(j);

  if (j != 6)
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
  Serial.print(F("GPS ClearConfig "));
  size_t SIZE = sizeof(ClearConfig);  
  GPS_Send_Config(ClearConfig,SIZE,10,GPS_attempts);
  Serial.println(F("Wait clear"));
  delay(GPS_Clear_DelaymS);                            //wait a while for GPS to clear its settings 
}


void GPS_SetGPMode()
{
  Serial.print(F("GPS GLONASS_Off "));
  size_t SIZE = sizeof(GLONASS_Off);  
  GPS_Send_Config(GLONASS_Off, SIZE, 10, GPS_attempts);
}


void GPS_StopMessages()
{
  size_t SIZE;
  Serial.print(F("GPS GPGLL_Off "));
  SIZE = sizeof(GPGLL_Off); 
  GPS_Send_Config(GPGLL_Off, SIZE, 10, GPS_attempts);

  Serial.print(F("GPS GPGLS_Off "));
  SIZE = sizeof(GPGLS_Off); 
  GPS_Send_Config(GPGLS_Off, SIZE, 10, GPS_attempts);

  Serial.print(F("GPS GPGSA_Off "));
  SIZE = sizeof(GPGSA_Off); 
  GPS_Send_Config(GPGSA_Off, SIZE, 10, GPS_attempts);

  #ifndef GPS_ALLOW_GPGSV
  Serial.print(F("GPS GPGSV_Off "));
  SIZE = sizeof(GPGSV_Off); 
  GPS_Send_Config(GPGSV_Off, SIZE, 10, GPS_attempts);
  #endif
}


void GPS_SetNavigation()
{
  Serial.print(F("GPS SetNavigation "));
  size_t SIZE = sizeof(SetNavigation); 
  GPS_Send_Config(SetNavigation, SIZE, 10, GPS_attempts);
}


void GPS_SaveConfig()
{
  Serial.print(F("GPS Save "));
  size_t SIZE = sizeof(SaveConfig); 
  GPS_Send_Config(SaveConfig, SIZE, 10, GPS_attempts);
}


void GPS_PollNavigation()
{
  Serial.print(F("GPS PollNavigation "));
  size_t SIZE = sizeof(PollNavigation); 
  GPS_Send_Config(PollNavigation, SIZE, 44, GPS_attempts);
}


void GPS_SetCyclicMode()
{
  Serial.print(F("GPS SetCyclic "));
  size_t SIZE = sizeof(SetCyclicMode); 
  GPS_Send_Config(SetCyclicMode, SIZE, 10, GPS_attempts);
}

void GPS_SoftwareBackup()
{
  Serial.print(F("GPS SoftwareBackup "));
  size_t SIZE = sizeof(SoftwareBackup); 
  GPS_Send_Config(SoftwareBackup, SIZE, 0, GPS_attempts);
  //GPS_Send_Config(SoftwareBackup, SIZE, 10, 10);
}


void GPS_PMREQBackup()
{
  Serial.print(F("GPS PMREQBackup "));
  size_t SIZE = sizeof(PMREQBackup); 
  GPS_Send_Config(PMREQBackup, SIZE, 0, GPS_attempts);
  //GPS_Send_Config(PMREQBackup, SIZE, 10, 10);
}

void GPS_LowCurrent()
{
pinMode(GPSTX, INPUT);           //GPS Output pin
pinMode(GPSRX, INPUT);           //GPS Input pin
}



