//SerialGPS1.h
/*

*******************************************************************************************************************************
Easy Build LoRaTracker Programs for Arduino

Copyright of the author Stuart Robinson - 04/06/17

http://www.LoRaTracker.uk

These programs may be used free of charge for personal, recreational and educational purposes only.

This program, or parts of it, may not be used for or in connection with any commercial purpose without the explicit permission
of the author Stuart Robinson.

The programs are supplied as is, it is up to individual to decide if the programs are suitable for the intended purpose and
free from errors.
  
To Do:
  
*******************************************************************************************************************************
*/


/*
void process_GPSchar();
void start_GPSRead();
void gpsOn();
void gpsOff();
void gpsSetup();
void setupGPMode();
void sendConfig(unsigned char *Config, int Length);
void p(char x);
void clearCurrentCFG();
void saveCurrentCFG();
*/

unsigned long GPSonTime = 0;
unsigned long GPSoffTime = 0;
unsigned long GPSFixTime = 0;
boolean GLONASS_Active = false;


void p(byte x)
{
  Serial.print(" 0x");
  if (x < 16) {
    Serial.print("0");
  }
  Serial.print(x, HEX);
}


void sendConfig(unsigned char *Config, int Length)
{
  byte i;
  for (i = 0; i < Length; i++)
  {
    p(Config[i]);
    GPSSerial.write(Config[i]);
  }
}


void clearCurrentCFG()
{
  //clear current GPS configuration
  Serial.print(F("ClearCurrentCFG  "));
  unsigned char clearCFG[] = {0xB5, 0x62, 0x06, 0x09, 0x0D, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x01, 0x19, 0x98};
  sendConfig(clearCFG, sizeof(clearCFG));
  Serial.println();
}


void saveCurrentCFG()
{
  //save GPS configuration
  Serial.print(F("SaveCurrentCFG  "));
  unsigned char saveCFG[] = {0xB5, 0x62, 0x06, 0x09, 0x0D, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x1B, 0xA9};
  sendConfig(saveCFG, sizeof(saveCFG));
  Serial.println();
}


void process_GPSchar()                          //get and process output from GPS
{
  byte i;
  while (GPSSerial.available() > 0)
  {
    i = GPSSerial.read();
    gps.encode(i);
  }
}


void start_GPSRead()
{

}


void GPS_On()
{
  //turns on the GPS
  Serial.println(F("GPSOn"));
  digitalWrite(GPSPOWER, LOW);                   //in case GPS on\off power control is in use
  GPSonTime = millis();
}


void GPS_Off()
{
  //power down GPS, prepare to go to sleep
  GPSoffTime = millis();
  Serial.print(F("GPSOff at "));
  GPSFixTime = (GPSoffTime - GPSonTime) + GPSShutdownTimemS;
  Serial.print(GPSFixTime);
  Serial.println(F("mS"));
}


void setup_GPS()
{
  Serial.println("GPS Setup");
  GPSSerial.begin(GPSBaud);                    //Startup soft serial for GPS
#ifdef UBLOX
  clearCurrentCFG();
  delay(100);
  setupGPMode();
#endif
}



void setupGPMode()
{
  //Turn off GLONASS Mode
  Serial.print(F("UBLOX Set GPMode  "));
  unsigned char setGP[] = {0xB5, 0x62, 0x06, 0x3E, 0x0C, 0x00, 0x00, 0x00, 0x20, 0x01, 0x06, 0x08, 0x0E, 0x00, 0x00, 0x00, 0x01, 0x01, 0x8F, 0xB2};
  sendConfig(setGP, sizeof(setGP));
  Serial.println();
}


