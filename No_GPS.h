//No_GPS.h
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

  This program is for uses when the is a requirement to operate a program without a GPS.

  To Do:

*******************************************************************************************************************************
*/


void GPS_GetProcessChar();
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

byte config_attempts;

boolean GPS_Config_Error;

byte GPS_Reply[GPS_Reply_Size];               //Byte array for storing GPS reply to UBX commands


byte GPS_GetByte()                            //get and process output from GPS
{
  return 0xFF;
}


void GPS_StartRead()
{
  //null routine, in case a program uses the same routine
}


void GPS_On(boolean powercontrol)
{
  //null routine, in case a program uses the same routine
}


void GPS_Off(boolean powercontrol)
{
  //null routine, in case a program uses the same routine
}


boolean GPS_WaitAck(unsigned long waitms, byte length)
{
  return true;
}


void GPS_Send_Config(unsigned int Progmem_ptr, byte length, byte replylength, byte attempts)
{
  //null routine, in case a program uses the same routine
}



void GPS_Setup()
{

}


boolean GPS_CheckNavigation()
{
  return true;
}


void GPS_ClearConfig()
{
  //null routine, in case a program uses the same routine
}


void GPS_SetGPMode()
{
  //null routine, in case a program uses the same routine
}


void GPS_StopMessages()
{
  //null routine, in case a program uses the same routine
}


void GPS_SetNavigation()
{
  //null routine, in case a program uses the same routine
}


void GPS_SaveConfig()
{
  //null routine, in case a program uses the same routine
}


void GPS_PollNavigation()
{
  //null routine, in case a program uses the same routine
}


void GPS_SetCyclicMode()
{
  //null routine, in case a program uses the same routine
}


void GPS_SoftwareBackup()
{
  //null routine, in case a program uses the same routine
}





