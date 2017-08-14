//Generic_SerialGPS.h
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

  This program reads the GPS via serial, can be hardware of softserial.

  To Do:

*******************************************************************************************************************************
*/


void GPS_GetProcessChar();
void GPS_StartRead();
void GPS_On();
void GPS_Off();
boolean GPS_WaitAck(unsigned long waitms, byte length);
void GPS_Send_Config(unsigned long Progmem_ptr, byte length, byte replylength);
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

byte config_attempts;

boolean GPS_Config_Error;

byte GPS_Reply[GPS_Reply_Size];             //Byte array for storing GPS reply to UBX commands


#include <TinyGPS++.h>
TinyGPSPlus gps;                            //Create the TinyGPS++ object



void GPS_GetProcessChar()                   //get and process output from GPS
{
  while (GPSserial.available() > 0)
    gps.encode(GPSserial.read());
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
  GPSonTime = millis();
  GPSserial.begin(GPSBaud);

  if (powercontrol)
  {
    digitalWrite(GPSPOWER, LOW);           //force GPS power on
    GPSserial.println();                   //wakeup gps, in case software power down is in use
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
  GPSserial.end();
}


boolean GPS_WaitAck(unsigned long waitms, byte length)
{
  return true;
}


void GPS_Send_Config(unsigned long Progmem_ptr, byte length, byte replylength, byte attempts)
{
  byte byteread, i;
  unsigned long ptr;

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

  delay(100);                                         //GPS can sometimes be a bit slow getting ready for next config
}



void GPS_Setup()
{
  GPSserial.begin(GPSBaud);                           //Startup soft serial
}


boolean GPS_CheckNavigation()
{
  //null routine, in case a program uses the same routine for a UBLOX GPS
  return true;
}


void GPS_ClearConfig()
{
  //null routine, in case a program uses the same routine for a UBLOX GPS
}


void GPS_SetGPMode()
{
  //null routine, in case a program uses the same routine for a UBLOX GPS
}



void GPS_StopMessages()
{
  //null routine, in case a program uses the same routine for a UBLOX GPS
}

void GPS_SetNavigation()
{
  //null routine, in case a program uses the same routine for a UBLOX GPS
}


void GPS_SaveConfig()
{
  //null routine, in case a program uses the same routine for a UBLOX GPS
}


void GPS_PollNavigation()
{
  //null routine, in case a program uses the same routine for a UBLOX GPS
}


void GPS_SetCyclicMode()
{
  //null routine, in case a program uses the same routine for a UBLOX GPS
}

void GPS_SoftwareBackup()
{
  //null routine, in case a program uses the same routine for a UBLOX GPS
}





